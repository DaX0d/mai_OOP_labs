#include "../include/npc_factory.hpp"
#include "../include/battle.hpp"
#include <iostream>
#include <vector>
#include <memory>


void printNPCs(const std::vector<std::shared_ptr<NPC>>& npcs) {
    std::cout << "\n=== Current NPCs ===" << std::endl;
    for (const auto& npc: npcs) {
        if (npc->isAlive()) {
            std::cout << *npc << std::endl;
        }
    }
    std::cout << "Total: " << npcs.size() << " NPCs" << std::endl;
}

int main() {
    std::vector<std::shared_ptr<NPC>> npcs;

    try {
        npcs.push_back(NPCFactory::createNPC(NpcType::Squirrel, "Squirrel1", 10, 20));
        npcs.push_back(NPCFactory::createNPC(NpcType::Squirrel, "Squirrel2", 30, 40));
        npcs.push_back(NPCFactory::createNPC(NpcType::Werewolf, "Werewolf1", 50, 60));
        npcs.push_back(NPCFactory::createNPC(NpcType::Werewolf, "Werewolf2", 70, 80));
        npcs.push_back(NPCFactory::createNPC(NpcType::Druid, "Druid1", 90, 100));
        npcs.push_back(NPCFactory::createNPC(NpcType::Druid, "Druid2", 110, 120));
    } catch (const std::exception& e) {
        std::cerr << "Error creating NPC: " << e.what() << std::endl;
        return 1;
    }

    printNPCs(npcs);

    try {
        NPCFactory::saveToFile(npcs, "npcs.txt");
        std::cout << "\nNPCs saved to npcs.txt" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error saving to file: " << e.what() << std::endl;
    }

    try {
        auto loadedNpcs = NPCFactory::loadFromFile("npcs.txt");
        std::cout << "\nLoaded " << loadedNpcs.size() << " NPCs from file" << std::endl;
        printNPCs(loadedNpcs);

        npcs = loadedNpcs;
    } catch (const std::exception& e) {
        std::cerr << "Error loading from file: " << e.what() << std::endl;
    }

    Battle battle;
    battle.addConsoleObserver();
    battle.addFileObserver("log.txt");

    std::cout << "\n=== Starting Battle (range: 150) ===" << std::endl;
    battle.fight(npcs, 150.0);

    printNPCs(npcs);

    try {
        NPCFactory::saveToFile(npcs, "survivors.txt");
        std::cout << "\nSurvivors saved to survivors.txt" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error saving survivors: " << e.what() << std::endl;
    }

    return 0;
}
