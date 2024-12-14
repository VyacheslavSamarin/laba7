#include <shared_mutex> // Добавляем этот заголовок
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>
#include <random>
#include <iostream>
#include "NPC.hpp"
#include "Elf.hpp"
#include "Druid.hpp"
#include "Dragon.hpp"
#include "NPCFactory.hpp"
#include "NPCSaver.hpp"
#include "NPCLoader.hpp"
#include "ElfFactory.hpp" // Добавляем заголовки фабрик
#include "DruidFactory.hpp"
#include "DragonFactory.hpp"

// Объявления мьютексов и очереди боев
std::shared_mutex npc_mutex;
std::mutex cout_mutex;
std::mutex battle_queue_mutex;
std::condition_variable battle_condition;
std::queue<std::pair<NPC*, NPC*>> battle_tasks;

// Поток для перемещения NPC
void movement_thread_func(std::vector<std::unique_ptr<NPC>>& npcs, int map_width, int map_height, int killing_range) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-5, 5); // Диапазон перемещения

    while (true) {
        std::shared_lock<std::shared_mutex> lock(npc_mutex);
        for (auto& npc : npcs) {
            if (npc && npc->isAlive()) {
                int new_x = npc->getX() + dis(gen);
                int new_y = npc->getY() + dis(gen);
                npc->setX(std::max(0, std::min(map_width, new_x)));
                npc->setY(std::max(0, std::min(map_height, new_y)));
            }
        }
        // Проверка на возможность боя
        for (size_t i = 0; i < npcs.size(); ++i) {
            if (!npcs[i] || !npcs[i]->isAlive()) continue;
            for (size_t j = i + 1; j < npcs.size(); ++j) {
                if (!npcs[j] || !npcs[j]->isAlive()) continue;
                int dx = npcs[i]->getX() - npcs[j]->getX();
                int dy = npcs[i]->getY() - npcs[j]->getY();
                if (std::sqrt(dx * dx + dy * dy) <= killing_range) {
                    std::unique_lock<std::mutex> battle_lock(battle_queue_mutex);
                    battle_tasks.push({npcs[i].get(), npcs[j].get()});
                    battle_condition.notify_one();
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

// Поток для обработки боев
void battle_thread_func(std::vector<std::unique_ptr<NPC>>& npcs) {
    while (true) {
        std::unique_lock<std::mutex> battle_lock(battle_queue_mutex);
        battle_condition.wait(battle_lock, [] { return !battle_tasks.empty(); });
        auto task = battle_tasks.front();
        battle_tasks.pop();
        battle_lock.unlock();

        std::lock_guard<std::shared_mutex> lock(npc_mutex);
        if (task.first->isAlive() && task.second->isAlive()) {
            int attack = std::rand() % 6 + 1;
            int defense = std::rand() % 6 + 1;
            if (attack > defense) {
                task.second->setAlive(false);
                std::lock_guard<std::mutex> cout_lock(cout_mutex);
                std::cout << task.first->getName() << " убил " << task.second->getName() << "!\n";
            }
        }
    }
}

int main() {
    const int MAP_WIDTH = 100;
    const int MAP_HEIGHT = 100;
    const int KILLING_RANGE = 10;
    std::vector<std::unique_ptr<NPC>> npcs;

    // Регистрация фабрик NPC
    NPCFactory::registerFactory("Druid", new DruidFactory());
    NPCFactory::registerFactory("Elf", new ElfFactory());
    NPCFactory::registerFactory("Dragon", new DragonFactory());

    // Инициализация 50 NPC в случайных локациях
    std::srand(std::time(0));
    for (int i = 0; i < 50; ++i) {
        int type_rand = std::rand() % 3;
        std::string type;
        switch (type_rand) {
            case 0: type = "Elf"; break;
            case 1: type = "Druid"; break;
            case 2: type = "Dragon"; break;
        }
        std::string name = type + std::to_string(i);
        int x = std::rand() % MAP_WIDTH;
        int y = std::rand() % MAP_HEIGHT;
        npcs.emplace_back(NPCFactory::create(type, name, x, y));
    }

    // Запуск потоков
    std::thread movement_thread(movement_thread_func, std::ref(npcs), MAP_WIDTH, MAP_HEIGHT, KILLING_RANGE);
    std::thread battle_thread(battle_thread_func, std::ref(npcs));

    // Основной цикл
    auto start_time = std::chrono::high_resolution_clock::now();
    while (true) {
        auto current_time = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time).count();
        if (elapsed >= 30) break;

        // Печать карты
        std::shared_lock<std::shared_mutex> lock(npc_mutex);
        std::lock_guard<std::mutex> cout_lock(cout_mutex);
        std::cout << "Карта на " << elapsed << " секунд:\n";
        for (const auto& npc : npcs) {
            if (npc && npc->isAlive()) {
                std::cout << npc->getName() << " на (" << npc->getX() << ", " << npc->getY() << ")\n";
            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // Ожидание завершения потоков
    movement_thread.join();
    battle_thread.join();

    // Печать выживших
    std::lock_guard<std::mutex> cout_lock(cout_mutex);
    std::cout << "Выжившие:\n";
    for (const auto& npc : npcs) {
        if (npc && npc->isAlive()) {
            std::cout << npc->getName() << " на (" << npc->getX() << ", " << npc->getY() << ")\n";
        }
    }

    return 0;
}