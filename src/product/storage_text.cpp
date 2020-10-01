#include "product/storage_text.hpp"

using std::string;

StorageText::StorageText(string file):file_name_(file) {};

bool StorageText::Open(){ return true; };

bool StorageText::Close(){ return true; };

bool StorageText::Save(){ return true; };

bool StorageText::Update(){ return true; };

bool StorageText::Add() { return true; };

bool StorageText::Delete() { return true; };

StorageText::~StorageText(){};