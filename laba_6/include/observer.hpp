#pragma once

#include <string>
#include <memory>


class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const std::string& event) = 0;
};


class ConsoleObserver: public Observer {
public:
    void update(const std::string& event) override;
};


class FileObserver: public Observer {
public:
    FileObserver(const std::string& filename);
    
    void update(const std::string& event) override;

private:
    std::string filename;
};
