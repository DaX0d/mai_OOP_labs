#pragma once

#include "npc.hpp"
#include "event_manager.hpp"
#include "npc_visitor.hpp"
#include <vector>
#include <memory>


class BattleVisitor: public NPCVisitor {
public:
    BattleVisitor(std::shared_ptr<NPC> attacker, EventManager& eventManager);

    void visit(const Squirrel& squirrel) override;
    void visit(const Werewolf& werewolf) override;
    void visit(const Druid& druid) override;
private:
    std::shared_ptr<NPC> attacker;
    EventManager& eventManager;
};


class Battle { 
public:
    void addConsoleObserver();
    void addFileObserver(const std::string& filename);

    void fight(std::vector<std::shared_ptr<NPC>>& npcs, double range);
private:
    EventManager eventManager;
};
