#pragma once

#include <string>
#include <memory>

enum class NpcType {
    Squirrel,
    Werewolf,
    Druid
};


class NPC {
public:
    NPC(const std::string& name, int x, int y);
    virtual ~NPC() = default;

    std::string getName() const;
    NpcType getType() const;
    virtual std::string getTypeName() const = 0;

    int getX() const;
    int getY() const;
    bool isAlive() const;
    void kill();

    double distanceTo(const NPC& other) const;

    virtual bool accept(const std::shared_ptr<NPC>& attacker) const = 0;

    friend std::ostream& operator<<(std::ostream& os, const NPC& npc);
protected:
    std::string name;
    int x;
    int y;
    bool alive;
};


class Squirrel: public NPC {
public:
    Squirrel(const std::string& name, int x, int y);

    std::string getTypeName() const override;
    bool accept(const std::shared_ptr<NPC>& attacker) const override;
};


class Werewolf: public NPC {
public:
    Werewolf(const std::string& name, int x, int y);

    std::string getTypeName() const override;
    bool accept(const std::shared_ptr<NPC>& attacker) const override;
};


class Druid: public NPC {
public:
    Druid(const std::string& name, int x, int y);

    std::string getTypeName() const override;
    bool accept(const std::shared_ptr<NPC>& attacker) const override;
};
