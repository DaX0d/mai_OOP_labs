#pragma once

#include "npc.hpp"
#include <memory>

class NPCVisitor {
public:
    virtual ~NPCVisitor() = default;
    virtual void visit(const Squirrel& squirrel) = 0;
    virtual void visit(const Werewolf& werewolf) = 0;
    virtual void visit(const Druid& druid) = 0;
};
