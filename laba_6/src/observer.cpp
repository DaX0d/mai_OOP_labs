#include "../include/observer.hpp"
#include <iostream>
#include <fstream>
#include <ctime>


void ConsoleObserver::update(const std::string& event) {
    std::time_t now = std::time(nullptr);
    std::cout << std::ctime(&now) << " [LOG] " << event << std::endl;
}

FileObserver::FileObserver(const std::string& filename) : filename(filename) {}

void FileObserver::update(const std::string& event) {
    std::ofstream file(filename, std::ios::app);
    if (file) {
        std::time_t now = std::time(nullptr);
        file << std::ctime(&now) << " " << event << std::endl;
    }
}
