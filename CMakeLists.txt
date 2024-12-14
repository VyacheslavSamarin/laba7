cmake_minimum_required(VERSION 3.10)

project(BalagurFate3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

set(SOURCES
    include/NPC.hpp
    include/NPCFactory.hpp
    include/BattleVisitor.hpp
    include/LoggingVisitior.hpp
    include/Druid.hpp
    include/Dragon.hpp
    include/Elf.hpp
    include/NPCLoader.hpp
    include/NPCSaver.hpp
    include/ElfFactory.hpp
    include/DruidFactory.hpp
    include/DragonFactory.hpp

    src/NPC.cpp
    src/main.cpp
    src/NPCFactory.cpp
    src/BattleVIsitor.cpp
    src/LoggingVisitor.cpp
    src/Druid.cpp
    src/Dragon.cpp
    src/Elf.cpp
    src/NPCLoader.cpp
    src/NPCSaver.cpp
)

add_executable(BalagurFate3 ${SOURCES})