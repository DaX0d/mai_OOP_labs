#pragma once

template<typename T>
class Array {
private:
    std::unique_ptr<T[]> data;
    size_t size;
    size_t capacity;

    void resize(size_t newCapacity) {
        auto newData = std::make_unique<T[]>(newCapacity);
        for (size_t i = 0; i < size; ++i) {
            newData[i] = std::move(data[i]);
        }

        data = std::move(newData);
        capacity = newCapacity;
    }

public:
    Array() : data(nullptr), size(0), capacity(0) {}

    explicit Array(size_t initialCapacity)
        : data(std::make_unique<T[]>(initialCapacity)),
          size(0),
          capacity(initialCapacity) {}

    Array(const Array&) = delete;
    Array& operator=(const Array&) = delete;

    Array(Array&& other) noexcept
        : data(std::move(other.data)),
          size(other.size),
          capacity(other.capacity) {
        other.size = 0;
        other.capacity = 0;
    }

    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
            size = other.size;
            capacity = other.capacity;
            other.size = 0;
            other.capacity = 0;
        }
        return *this;
    }

    void pushBack(T&& value) {
        if (size >= capacity) {
            size_t newCapacity = (capacity == 0) ? 1 : capacity * 2;
            resize(newCapacity);
        }
        data[size++] = std::move(value);
    }

    void pushBack(const T& value) {
        if (size >= capacity) {
            size_t newCapacity = (capacity == 0) ? 1 : capacity * 2;
            resize(newCapacity);
        }
        data[size++] = value;
    }

    void remove(size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }

        for (size_t i = index; i < size - 1; ++i) {
            data[i] = std::move(data[i + 1]);
        }
        --size;
    }

    void clear() {
        size = 0;
    }

    T& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    size_t getSize() const { return size; }
    size_t getCapacity() const { return capacity; }
    bool isEmpty() const { return size == 0; }

    ~Array() = default;
};
