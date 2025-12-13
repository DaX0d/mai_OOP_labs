#include "../include/MyMemoryResource.hpp"
#include "../include/MyList.hpp"
#include <iostream>

struct ComplexType {
    int id;
    double value;
    std::string name;

    ComplexType(int i, double v, const std::string& n):
        id(i), value(v), name(n) {}
};

int main() {
    MyMemoryResource mr(1024);
    
    MyList<int> int_list(&mr);
    
    for (int i = 0; i < 5; ++i) {
        int_list.push_front(i);
    }
    
    std::cout << "Int list size: " << int_list.size() << "\n";
    for (auto it = int_list.begin(); it != int_list.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";
    
    MyList<ComplexType> complex_list(&mr);
    complex_list.emplace_front(1, 3.14, "Pi");
    complex_list.emplace_front(2, 2.71, "E");
    
    std::cout << "\nComplex list:\n";
    for (const auto& item : complex_list) {
        std::cout << "ID: " << item.id 
                  << ", Value: " << item.value 
                  << ", Name: " << item.name << "\n";
    }
    
    int_list.clear();
    complex_list.clear();
    
    std::cout << "\nAfter clear:\n";
    std::cout << "Int list empty: " << int_list.empty() << "\n";
    std::cout << "Complex list empty: " << complex_list.empty() << "\n";
    
    return 0;
}
