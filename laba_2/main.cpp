#include <iostream>
#include "thirteen.h"

static void print_menu() {
    using namespace std;

    cout << "\n1) Ввести число как десятичное\n";
    cout << "2) Ввести число как тринадцатеричное\n";
    cout << "3) Вывести число как тринадцатеричное\n";
    cout << "4) Вывести число как десятичное\n";
    cout << "5) Вывести сумму с десятичным числом\n";
    cout << "6) Вывести сумму с тринадцатеричным числом\n";
    cout << "7) Прибавить десятичное число\n";
    cout << "8) Прибавить тринадцатеричное число\n";
    cout << "0) Выход\n";
    cout << "\nДействие: ";
}

int main() {
    Thirteen* number = new Thirteen();
    std::string tmp_str;
    ULL_T tmp_int;
    char choice;
    print_menu();
    std::cin >> choice;

    while (choice != '0') {
        switch (choice) {
            case '1':
                std::cout << "\nВведите число: ";
                std::cin >> tmp_str;
                tmp_int = std::stoull(tmp_str);
                delete number;
                number = new Thirteen(tmp_int);
            break;
            case '2':
                std::cout << "\nВведите число: ";
                std::cin >> tmp_str;
                delete number;
                number = new Thirteen(tmp_str);
            break;
            case '3':
                std::cout << number->get_as_string() << "\n";
            break;
            case '4':
                std::cout << number->get_as_int10() << "\n";
            break;
            case '5':
                std::cout << "\nВведите число: ";
                std::cin >> tmp_str;
                tmp_int = std::stoull(tmp_str);
                {
                    Thirteen tmp = number->plus(Thirteen(tmp_int));
                    std::cout << tmp.get_as_string() << " (";
                    std::cout << tmp.get_as_int10() << ")\n";
                }
            break;
            case '6':
                std::cout << "\nВведите число: ";
                std::cin >> tmp_str;
                {
                    Thirteen tmp = number->plus(Thirteen(tmp_str));
                    std::cout << tmp.get_as_string() << " (";
                    std::cout << tmp.get_as_int10() << ")\n";
                }
            break;
            case '7':
                std::cout << "\nВведите число: ";
                std::cin >> tmp_str;
                tmp_int = std::stoull(tmp_str);
                number->pluseq(Thirteen(tmp_int));
            break;
            case '8':
                std::cout << "\nВведите число: ";
                std::cin >> tmp_str;
                number->pluseq(Thirteen(tmp_str));
            break;
        }
        print_menu();
        std::cin >> choice;
    }

    delete number;
    return 0;
}
