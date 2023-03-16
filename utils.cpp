#include "utils.h"
#include "notebook.h"

#include <iostream>

int runApp() {
    bool isExit = false;
    TNoteBook noteBook;
    while (!isExit) {
        std::cout << "1. List notes\n"
            "2. Delete notes\n"
            "3. Add new note\n"
            "4. Edit note\n"
            "5. Exit\n"
            "> ";
        size_t num;
        std::cin >> num;
        std::cin.ignore();
        switch (num) {
        case 1: {
            for (auto note : noteBook) {
                std::cout << note.id << ". " << note.name << ": " << note.content << '\n';
            }
            std::cout << std::endl;
            break;
        } case 2: {
            noteBook.clear();
            break;
        } case 3: {
            std::cout << "Note name: ";
            std::string name;
            std::getline(std::cin, name);
            std::cout << "Note content: ";
            std::string content;
            std::getline(std::cin, content);
            noteBook.addNote(std::move(name), std::move(content));
            break;
        } case 4: {
            std::cout << "Enter note id: ";
            size_t id;
            std::cin >> id;
            std::cin.ignore();
            std::cout << "Enter new name (empty for save old): ";
            std::string name;
            std::getline(std::cin, name);
            std::cout << "Enter new content (empty for save old): ";
            std::string content;
            std::getline(std::cin, content);
            noteBook.editNote(id, std::move(name), std::move(content));
            break;
        } case 5: {
            isExit = true;
            break;
        }
        default: {
            break;
        }
        }
    }

    return 0;
}