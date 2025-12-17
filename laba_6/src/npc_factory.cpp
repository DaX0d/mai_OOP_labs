#include "../include/npc_factory.hpp"
#include <fstream>
#include <sstream>


std::shared_ptr<NPC> NPCFactory::createNPC(NpcType type, const std::string& name, int x, int y) {
    switch (type) {
        case NpcType::Squirrel:
            return std::make_shared<Squirrel>(name, x, y);
        case NpcType::Werewolf:
            return std::make_shared<Werewolf>(name, x, y);
        case NpcType::Druid:
            return std::make_shared<Druid>(name, x, y);
        default:
            throw std::invalid_argument("Unknown NPC type");
    }
}

std::shared_ptr<NPC> NPCFactory::createNPCFromString(const std::string& data) {
    std::istringstream iss(data);
    std::string typeStr, name;
    int x, y;

    if (!(iss >> typeStr >> name >> x >> y)) {
        throw std::invalid_argument("Invalid NPC data format");
    }

    NpcType type;
    if (typeStr == "Squirrel") type = NpcType::Squirrel;
    else if (typeStr == "Werewolf") type = NpcType::Werewolf;
    else if (typeStr == "Druid") type = NpcType::Druid;
    else throw std::invalid_argument("Unknown NPC type: " + typeStr);

    return createNPC(type, name, x, y);
}

std::string NPCFactory::npcToString(const NPC& npc) {
    std::ostringstream oss;
    oss << npc.getTypeName() << " " << npc.getName() 
        << " " << npc.getX() << " " << npc.getY();
    return oss.str();
}

void NPCFactory::saveToFile(const std::vector<std::shared_ptr<NPC>>& npcs, const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    for (const auto& npc : npcs) {
        if (npc->isAlive()) {
            file << npcToString(*npc) << "\n";
        }
    }
}

std::vector<std::shared_ptr<NPC>> NPCFactory::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    std::vector<std::shared_ptr<NPC>> npcs;
    std::string line;

    while (std::getline(file, line)) {
        if (!line.empty()) {
            npcs.push_back(createNPCFromString(line));
        }
    }

    return npcs;
}
