#pragma once

#include "observer.hpp"
#include <vector>
#include <memory>


class EventManager {
public:
    void addObserver(const std::shared_ptr<Observer>& observer);
    void removeObserver(const std::shared_ptr<Observer>& observer);
    void notify(const std::string& event);
private:
    std::vector<std::shared_ptr<Observer>> observers;
};
