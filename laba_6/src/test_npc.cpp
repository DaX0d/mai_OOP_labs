#include <gtest/gtest.h>
#include "../include/npc.hpp"
#include "../include/npc_factory.hpp"
#include "../include/battle.hpp"


TEST(NPCTest, Creation) {
    auto squirrel = std::make_shared<Squirrel>("TestSquirrel", 100, 200);
    EXPECT_EQ(squirrel->getName(), "TestSquirrel");
    EXPECT_EQ(squirrel->getX(), 100);
    EXPECT_EQ(squirrel->getY(), 200);
    EXPECT_TRUE(squirrel->isAlive());
    EXPECT_EQ(squirrel->getTypeName(), "Squirrel");
}

TEST(NPCTest, DistanceCalculation) {
    auto npc1 = std::make_shared<Squirrel>("N1", 0, 0);
    auto npc2 = std::make_shared<Werewolf>("N2", 3, 4);

    EXPECT_DOUBLE_EQ(npc1->distanceTo(*npc2), 5.0);
}

TEST(NPCTest, FactoryCreation) {
    auto npc = NPCFactory::createNPC(NpcType::Druid, "DruidTest", 50, 50);
    EXPECT_EQ(npc->getTypeName(), "Druid");
    EXPECT_EQ(npc->getName(), "DruidTest");
}

TEST(NPCTest, Serialization) {
    auto npc = std::make_shared<Werewolf>("Wolfy", 123, 456);
    std::string data = NPCFactory::npcToString(*npc);

    auto loaded = NPCFactory::createNPCFromString(data);
    EXPECT_EQ(loaded->getName(), "Wolfy");
    EXPECT_EQ(loaded->getX(), 123);
    EXPECT_EQ(loaded->getY(), 456);
    EXPECT_EQ(loaded->getTypeName(), "Werewolf");
}

TEST(BattleTest, Fight) {
    std::vector<std::shared_ptr<NPC>> npcs;
    npcs.push_back(std::make_shared<Squirrel>("Sq1", 0, 0));
    npcs.push_back(std::make_shared<Werewolf>("Ww1", 10, 10));
    npcs.push_back(std::make_shared<Druid>("Dr1", 20, 20));

    Battle battle;
    battle.addConsoleObserver();

    EXPECT_EQ(npcs.size(), 3);

    battle.fight(npcs, 100.0);

    EXPECT_LE(npcs.size(), 3);
}

TEST(FileIOTest, SaveLoad) {
    std::vector<std::shared_ptr<NPC>> original;
    original.push_back(std::make_shared<Squirrel>("Test1", 111, 222));
    original.push_back(std::make_shared<Werewolf>("Test2", 333, 444));
    original.push_back(std::make_shared<Druid>("Test3", 500, 500));

    NPCFactory::saveToFile(original, "test_save.txt");

    auto loaded = NPCFactory::loadFromFile("test_save.txt");

    EXPECT_EQ(loaded.size(), 3);

    std::remove("test_save.txt");
}
