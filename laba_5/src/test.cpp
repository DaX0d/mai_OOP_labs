#include <gtest/gtest.h>
#include "../include/MyMemoryResource.hpp"
#include "../include/MyList.hpp"
#include <vector>
#include <algorithm>


TEST(MyMemoryResourceTest, BasicAllocationDeallocation) {
    constexpr std::size_t POOL_SIZE = 1024;
    MyMemoryResource mr(POOL_SIZE);
    
    void* ptr1 = mr.allocate(100, 1);
    ASSERT_NE(ptr1, nullptr);
    
    void* ptr2 = mr.allocate(200, 1);
    ASSERT_NE(ptr2, nullptr);
    
    mr.deallocate(ptr1, 100, 1);
    mr.deallocate(ptr2, 200, 1);
    
    void* ptr3 = mr.allocate(300, 1);
    ASSERT_NE(ptr3, nullptr);
    mr.deallocate(ptr3, 300, 1);
}

TEST(MyMemoryResourceTest, ThrowsOnOutOfMemory) {
    MyMemoryResource mr(100);
    
    void* ptr1 = mr.allocate(80, 1);
    ASSERT_NE(ptr1, nullptr);
    
    ASSERT_THROW(mr.allocate(50, 1), std::bad_alloc);
    
    mr.deallocate(ptr1, 80, 1);
}

TEST(MyMemoryResourceTest, ReuseFreedMemory) {
    MyMemoryResource mr(512);
    
    void* blocks[10];
    for (int i = 0; i < 10; ++i) {
        blocks[i] = mr.allocate(32, 1);
    }
    
    for (int i = 0; i < 10; i += 2) {
        mr.deallocate(blocks[i], 32, 1);
    }
    
    for (int i = 0; i < 5; ++i) {
        void* ptr = mr.allocate(32, 1);
        ASSERT_NE(ptr, nullptr);
        mr.deallocate(ptr, 32, 1);
    }
}

TEST(MyListTest, BasicOperationsInt) {
    MyMemoryResource mr(1024);
    MyList<int> list(&mr);
    
    ASSERT_TRUE(list.empty());
    ASSERT_EQ(list.size(), 0);
    
    list.push_front(1);
    ASSERT_FALSE(list.empty());
    ASSERT_EQ(list.size(), 1);
    
    list.push_front(2);
    list.push_front(3);
    ASSERT_EQ(list.size(), 3);
    
    auto it = list.begin();
    ASSERT_EQ(*it, 3);
    ++it;
    ASSERT_EQ(*it, 2);
    ++it;
    ASSERT_EQ(*it, 1);
    
    list.pop_front();
    ASSERT_EQ(list.size(), 2);
    ASSERT_EQ(*list.begin(), 2);
    
    list.clear();
    ASSERT_TRUE(list.empty());
    ASSERT_EQ(list.size(), 0);
}

TEST(MyListTest, EmplaceFront) {
    MyMemoryResource mr(1024);
    MyList<std::pair<int, double>> list(&mr);
    
    list.emplace_front(1, 3.14);
    list.emplace_front(2, 2.71);
    
    ASSERT_EQ(list.size(), 2);
    
    auto it = list.begin();
    ASSERT_EQ(it->first, 2);
    ASSERT_DOUBLE_EQ(it->second, 2.71);
    
    ++it;
    ASSERT_EQ(it->first, 1);
    ASSERT_DOUBLE_EQ(it->second, 3.14);
}

TEST(MyListTest, IteratorRequirements) {
    MyMemoryResource mr(1024);
    MyList<int> list(&mr);
    
    for (int i = 0; i < 5; ++i) {
        list.push_front(i);
    }
    
    auto it1 = list.begin();
    auto it2 = list.begin();
    
    ASSERT_EQ(it1, it2);
    
    ++it1;
    ASSERT_NE(it1, it2);
    
    int sum = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
        sum += *it;
    }
    ASSERT_EQ(sum, 10);
    
    auto it = list.begin();
    auto old_it = it++;
    ASSERT_NE(old_it, it);
    ASSERT_EQ(*old_it, 4);
    ASSERT_EQ(*it, 3);
}

TEST(MyListTest, RangeBasedForLoop) {
    MyMemoryResource mr(1024);
    MyList<int> list(&mr);
    
    std::vector<int> values = {5, 4, 3, 2, 1};
    for (int val : values) {
        list.push_front(val);
    }
    
    std::vector<int> result;
    for (int val : list) {
        result.push_back(val);
    }
    
    std::reverse(values.begin(), values.end());
    ASSERT_EQ(result, values);
}

struct ComplexType {
    int id;
    std::string name;
    
    ComplexType(int i, const std::string& n) : id(i), name(n) {}
    
    bool operator==(const ComplexType& other) const {
        return id == other.id && name == other.name;
    }
};

TEST(MyListTest, ComplexType) {
    MyMemoryResource mr(2048);
    MyList<ComplexType> list(&mr);
    
    list.emplace_front(1, "Alice");
    list.emplace_front(2, "Bob");
    list.emplace_front(3, "Charlie");
    
    ASSERT_EQ(list.size(), 3);
    
    std::vector<ComplexType> expected = {
        {3, "Charlie"},
        {2, "Bob"},
        {1, "Alice"}
    };
    
    size_t i = 0;
    for (const auto& item : list) {
        ASSERT_EQ(item.id, expected[i].id);
        ASSERT_EQ(item.name, expected[i].name);
        ++i;
    }
}

TEST(MyListTest, UsesCustomMemoryResource) {
    MyMemoryResource mr(128);
    
    MyList<int> list(&mr);
    
    try {
        for (int i = 0; i < 100; ++i) {
            list.push_front(i);
        }
        FAIL() << "Expected std::bad_alloc";
    } catch (const std::bad_alloc&) {
        SUCCEED();
    }
}

TEST(MyMemoryResourceTest, NoCopy) {
    MyMemoryResource mr1(1024);
    MyMemoryResource mr2(2048);
    
    ASSERT_TRUE(mr1.is_equal(mr1));
    ASSERT_FALSE(mr1.is_equal(mr2));
}

TEST(MyListTest, DestructorCleansUp) {
    MyMemoryResource mr(1024);
    
    {
        MyList<int> list(&mr);
        for (int i = 0; i < 10; ++i) {
            list.push_front(i);
        }
    }
    
    void* ptr = mr.allocate(512, 1);
    ASSERT_NE(ptr, nullptr);
    mr.deallocate(ptr, 512, 1);
}

TEST(MyListTest, EmptyListIterator) {
    MyMemoryResource mr(1024);
    MyList<int> list(&mr);
    
    ASSERT_EQ(list.begin(), list.end());
    
    list.push_front(42);
    list.pop_front();
    
    ASSERT_EQ(list.begin(), list.end());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
