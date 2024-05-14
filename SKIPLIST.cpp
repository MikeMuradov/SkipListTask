#include <iostream>
#include <vector>
#include "Skiplist.h"

int main() {
    SkipList<int> list(3); // Максимальный уровень 3
    int choice, value;

    do {
        std::cout << "Menu:\n";
        std::cout << "1. Insert an element\n";
        std::cout << "2. Search for an element\n";
        std::cout << "3. Print list size\n";
        std::cout << "4. Print list\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Enter the value to insert: ";
            std::cin >> value;
            list.insert(value);
            break;
        case 2:
            std::cout << "Enter the value to search: ";
            std::cin >> value;
            if (list.search(value)) {
                std::cout << "Value " << value << " found in the list.\n";
            }
            else {
                std::cout << "Value " << value << " not found in the list.\n";
            }
            break;
        case 3:
            std::cout << "Size of the list: " << list.getSize() << std::endl;
            break;
        case 4:
            std::cout << "Skip list: " << list << std::endl;
            break;
        case 5:
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}