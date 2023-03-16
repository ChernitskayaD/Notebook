#ifndef NOTEBOOK_H
#define NOTEBOOK_H

#include <string>
#include <list>


class TNoteBook {
public:
    struct Note {
        size_t id;
        std::string name;
        std::string content;
    };

    TNoteBook();

    void clear();
    void addNote(std::string name, std::string content);
    void editNote(size_t id, std::string newName, std::string newContent);

    std::list<Note>::const_iterator begin() const;
    std::list<Note>::const_iterator end() const;

private:
    std::list<Note> notes_;

    void loadNote(const std::string& noteName);
    void sync() const;
};

#endif // NOTEBOOK_H

