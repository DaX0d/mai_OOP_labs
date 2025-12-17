#include "../include/battle.hpp"
#include <algorithm>
#include <random>
#include <memory>


BattleVisitor::BattleVisitor(std::shared_ptr<NPC> attacker, EventManager& eventManager):
    attacker(attacker), eventManager(eventManager) {}

void BattleVisitor::visit(const Squirrel& squirrel) {
    if (!attacker->isAlive() || !squirrel.isAlive()) return;

    bool canKill = squirrel.accept(attacker);

    if (canKill) {
        const_cast<Squirrel&>(squirrel).kill();
        std::string event = attacker->getName() + " (" + attacker->getTypeName() 
                          + ") killed " + squirrel.getName() + " (Squirrel)";
        eventManager.notify(event);
    }
}

void BattleVisitor::visit(const Werewolf& werewolf) {
    if (!attacker->isAlive() || !werewolf.isAlive()) return;

    bool canKill = werewolf.accept(attacker);

    if (canKill) {
        const_cast<Werewolf&>(werewolf).kill();
        std::string event = attacker->getName() + " (" + attacker->getTypeName() 
                          + ") killed " + werewolf.getName() + " (Werewolf)";
        eventManager.notify(event);
    }
}

void BattleVisitor::visit(const Druid& druid) {
    if (!attacker->isAlive() || !druid.isAlive()) return;

    bool canKill = druid.accept(attacker);

    if (canKill) {
        const_cast<Druid&>(druid).kill();
        std::string event = attacker->getName() + " (" + attacker->getTypeName() 
                          + ") killed " + druid.getName() + " (Druid)";
        eventManager.notify(event);
    }
}

void Battle::addConsoleObserver() {
    eventManager.addObserver(std::make_shared<ConsoleObserver>());
}

void Battle::addFileObserver(const std::string& filename) {
    eventManager.addObserver(std::make_shared<FileObserver>(filename));
}

void Battle::fight(std::vector<std::shared_ptr<NPC>>& npcs, double range) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(npcs.begin(), npcs.end(), g);

    bool battleOccurred = true;

    while (battleOccurred) {
        battleOccurred = false;
    
        for (size_t i = 0; i < npcs.size(); ++i) {
            if (!npcs[i]->isAlive()) continue;

            for (size_t j = 0; j < npcs.size(); ++j) {
                if (i == j || !npcs[j]->isAlive()) continue;

                if (npcs[i]->distanceTo(*npcs[j]) > range) continue;

                BattleVisitor visitor(npcs[i], eventManager);

                if (auto target = std::dynamic_pointer_cast<Squirrel>(npcs[j])) {
                    visitor.visit(*target);
                    if (!target->isAlive()) battleOccurred = true;
                }
                else if (auto target = std::dynamic_pointer_cast<Werewolf>(npcs[j])) {
                    visitor.visit(*target);
                    if (!target->isAlive()) battleOccurred = true;
                }
                else if (auto target = std::dynamic_pointer_cast<Druid>(npcs[j])) {
                    visitor.visit(*target);
                    if (!target->isAlive()) battleOccurred = true;
                }

                if (!npcs[i]->isAlive()) break;
            }
        }

        auto new_end = std::remove_if(npcs.begin(), npcs.end(), 
            [](const std::shared_ptr<NPC>& npc) { return !npc->isAlive(); });
        npcs.erase(new_end, npcs.end());
    }
}
