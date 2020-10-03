#include "product/storage_text.hpp"
#include <sstream>

using std::string;
using std::fstream;
using std::istringstream;
using std::vector;

StorageText::StorageText(string file) :file_name_(file) {};

bool StorageText::Open() {
    if (!fs_.is_open())
        fs_.open(file_name_, std::ifstream::in);
    return fs_.is_open();
};

void StorageText::Close() {
    fs_.close();
};

bool StorageText::Save() { return true; };

bool StorageText::Update() { return true; };

bool StorageText::Add() { return true; };

bool StorageText::Delete() { return true; };

void StorageText::Select(std::vector<std::vector<std::string>>& records) {
    records.clear();
    string line;
    if (fs_.is_open()) {
        while (getline(fs_, line)) {
            istringstream iss(line);
            vector<string> tokens(std::istream_iterator<string>{iss}, std::istream_iterator<string>());
            records.push_back(tokens);
        }
        fs_.seekg(0);
    }
    fs_.close();
};

StorageText::~StorageText() {};