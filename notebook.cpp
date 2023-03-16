#include "notebook.h"

#include <fstream>
#include <cassert>

const std::string NOTE_LIST_FILE_NAME = "NoteList.txt";

TNoteBook::TNoteBook() {
    std::ifstream fin(NOTE_LIST_FILE_NAME);
    assert(fin.is_open());
    std::string line;
    while (std::getline(fin, line)) {
        loadNote(line + ".txt");
    }
    fin.close();
}

std::list<TNoteBook::Note>::const_iterator TNoteBook::begin() const {
    return notes_.cbegin();
}

std::list<TNoteBook::Note>::const_iterator TNoteBook::end() const {
    return notes_.cend();
}

void TNoteBook::clear() {
    notes_.clear();
    sync();
}

void TNoteBook::addNote(std::string name, std::string content) {
    Note newNote{ notes_.size(), std::move(name), std::move(content) };
    notes_.emplace_back(std::move(newNote));
    sync();
}

void TNoteBook::editNote(size_t id, std::string newName, std::string newContent) {
    for (auto note : notes_) {
        if (note.id == id) {
            if (!newName.empty()) {
                note.name = std::move(newName);
            }
            if (!newContent.empty()) {
                note.content = std::move(newContent);
            }
            break;
        }
    }
    sync();
}

void TNoteBook::loadNote(const std::string& noteName) {
    std::ifstream fin(noteName);
    assert(fin.is_open());
    Note loadedNote;
    loadedNote.id = notes_.size();
    std::getline(fin, loadedNote.name);
    std::string partContent;
    while (std::getline(fin, partContent)) {
        loadedNote.content += partContent + '\n';
    }
    notes_.emplace_back(std::move(loadedNote));
    fin.close();
}

void TNoteBook::sync() const {
    std::ofstream fout(NOTE_LIST_FILE_NAME);
    assert(fout.is_open());
    for (auto note : notes_) {
        fout << note.id << '\n';
        std::ofstream fNote(std::to_string(note.id) + ".txt");
        assert(fNote.is_open());
        fNote << note.name << '\n' << note.content;
        fNote.close();
    }
    fout.close();
}
