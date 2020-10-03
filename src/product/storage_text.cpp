#include "product/storage_text.hpp"

using std::string;
using std::fstream;

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

StorageText::~StorageText() {};