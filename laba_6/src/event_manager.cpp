#include "../include/event_manager.hpp"
#include <algorithm>

void EventManager::addObserver(const std::shared_ptr<Observer>& observer) {
    observers.push_back(observer);
}

void EventManager::removeObserver(const std::shared_ptr<Observer>& observer) {
    observers.erase(
        std::remove_if(observers.begin(), observers.end(),
            [&observer](const std::shared_ptr<Observer>& obs) {
                return obs == observer;
            }),
        observers.end()
    );
}

void EventManager::notify(const std::string& event) {
    for (const auto& observer : observers) {
        observer->update(event);
    }
}
