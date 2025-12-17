#include "../include/npc.hpp"
#include <cmath>
#include <sstream>


NPC::NPC(const std::string& name, int x, int y):
    name(name), x(x), y(y), alive(true) {
    if (x < 0 || x > 500 || y < 0 || y > 500) {
        throw std::invalid_argument("Coordinates must be in range [0, 500]");
    }
}

std::string NPC::getName() const { return name; }

int NPC::getX() const { return x; }
int NPC::getY() const { return y; }
bool NPC::isAlive() const { return alive; }
void NPC::kill() { alive = false; }

double NPC::distanceTo(const NPC& other) const {
    int dx = x - other.x;
    int dy = y - other.y;
    return std::sqrt(dx*dx + dy*dy);
}

std::ostream& operator<<(std::ostream& os, const NPC& npc) {
    os << npc.getTypeName() << " '" << npc.name << "' at (" 
       << npc.x << ", " << npc.y << ")";
    return os;
}

Squirrel::Squirrel(const std::string& name, int x, int y):
    NPC(name, x, y) {}

std::string Squirrel::getTypeName() const { return "Squirrel"; }

bool Squirrel::accept(const std::shared_ptr<NPC>& attacker) const {
    if (!attacker->isAlive()) return false;

    if (auto werewolf = std::dynamic_pointer_cast<Werewolf>(attacker)) {
        return false;
    }
    if (auto druid = std::dynamic_pointer_cast<Druid>(attacker)) {
        return false;
    }
    if (auto squirrel = std::dynamic_pointer_cast<Squirrel>(attacker)) {
        return false;
    }
    return false;
}

Werewolf::Werewolf(const std::string& name, int x, int y):
    NPC(name, x, y) {}

std::string Werewolf::getTypeName() const { return "Werewolf"; }

bool Werewolf::accept(const std::shared_ptr<NPC>& attacker) const {
    if (!attacker->isAlive()) return false;

    if (auto druid = std::dynamic_pointer_cast<Druid>(attacker)) {
        return true;
    }
    if (auto squirrel = std::dynamic_pointer_cast<Squirrel>(attacker)) {
        return true;
    }
    if (auto werewolf = std::dynamic_pointer_cast<Werewolf>(attacker)) {
        return false;
    }
    return false;
}

Druid::Druid(const std::string& name, int x, int y):
    NPC(name, x, y) {}

std::string Druid::getTypeName() const { return "Druid"; }

bool Druid::accept(const std::shared_ptr<NPC>& attacker) const {
    if (!attacker->isAlive()) return false;

    if (auto squirrel = std::dynamic_pointer_cast<Squirrel>(attacker)) {
        return true;
    }
    if (auto werewolf = std::dynamic_pointer_cast<Werewolf>(attacker)) {
        return true;
    }
    if (auto druid = std::dynamic_pointer_cast<Druid>(attacker)) {
        return false;
    }
    return false;
}

NpcType NPC::getType() const {
    if (dynamic_cast<const Squirrel*>(this)) return NpcType::Squirrel;
    if (dynamic_cast<const Werewolf*>(this)) return NpcType::Werewolf;
    if (dynamic_cast<const Druid*>(this)) return NpcType::Druid;
    throw std::runtime_error("Unknown NPC type");
}
