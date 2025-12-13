#pragma once

#include <memory_resource>
#include <map>
#include <cstddef>
#include <iostream>
#include <cstdint>

class MyMemoryResource : public std::pmr::memory_resource {
private:
    struct BlockInfo {
        std::size_t size;
        bool is_free;
    };

    char* memory_pool;                     // большой фиксированный блок
    std::size_t pool_size;
    std::map<void*, BlockInfo> block_map;  // ключ: адрес, значение: размер + флаг

    void* allocate_from_free_block(std::size_t bytes, std::size_t alignment);
    void merge_free_blocks();

public:
    explicit MyMemoryResource(std::size_t pool_size = 1024 * 1024); // 1 МБ
    ~MyMemoryResource();

    MyMemoryResource(const MyMemoryResource&) = delete;
    MyMemoryResource& operator=(const MyMemoryResource&) = delete;

protected:
    void* do_allocate(std::size_t bytes, std::size_t alignment) override;
    void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) override;
    bool do_is_equal(const memory_resource& other) const noexcept override;
};
