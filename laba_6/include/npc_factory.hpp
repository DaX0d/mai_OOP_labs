#pragma once

#include "npc.hpp"
#include <memory>
#include <string>
#include <vector>

class NPCFactory {
public:
    static std::shared_ptr<NPC> createNPC(NpcType type, const std::string& name, int x, int y);
    static std::shared_ptr<NPC> createNPCFromString(const std::string& data);
    static std::string npcToString(const NPC& npc);
    
    static void saveToFile(const std::vector<std::shared_ptr<NPC>>& npcs, const std::string& filename);
    static std::vector<std::shared_ptr<NPC>> loadFromFile(const std::string& filename);
};
