#include "../include/MyMemoryResource.hpp"
#include <cstring>
#include <stdexcept>

MyMemoryResource::MyMemoryResource(std::size_t pool_size) 
    : pool_size(pool_size) {
    memory_pool = new char[pool_size];
    block_map[memory_pool] = {pool_size, true};
}

MyMemoryResource::~MyMemoryResource() {
    delete[] memory_pool;
}

void* MyMemoryResource::do_allocate(std::size_t bytes, std::size_t alignment) {
    for (auto it = block_map.begin(); it != block_map.end(); ++it) {
        if (it->second.is_free && it->second.size >= bytes) {
            void* ptr = it->first;
            std::size_t remaining = it->second.size - bytes;
            
            it->second = {bytes, false};
            
            if (remaining > 0) {
                void* new_free_ptr = static_cast<char*>(ptr) + bytes;
                block_map[new_free_ptr] = {remaining, true};
            }
            
            return ptr;
        }
    }
    throw std::bad_alloc();
}

void MyMemoryResource::do_deallocate(void* p, std::size_t bytes, std::size_t alignment) {
    auto it = block_map.find(p);
    if (it != block_map.end() && !it->second.is_free) {
        it->second.is_free = true;
        merge_free_blocks();
    }
}

bool MyMemoryResource::do_is_equal(const memory_resource& other) const noexcept {
    return this == &other;
}

void MyMemoryResource::merge_free_blocks() {
    auto it = block_map.begin();
    while (it != block_map.end()) {
        if (it->second.is_free) {
            auto next_it = std::next(it);
            while (next_it != block_map.end() && next_it->second.is_free) {
                void* current_end = static_cast<char*>(it->first) + it->second.size;
                if (current_end == next_it->first) {
                    it->second.size += next_it->second.size;
                    block_map.erase(next_it);
                    next_it = std::next(it);
                } else {
                    break;
                }
            }
        }
        ++it;
    }
}
