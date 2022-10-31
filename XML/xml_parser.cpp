#include <fstream>

#include "xml_parser.h"

XmlParser* XmlParser::GetInstance() {
    static XmlParser* instance = new XmlParser();
    if(instance == nullptr) {
        instance = new XmlParser();
    }
    return instance;
}

XmlParser::XmlParser() : file_buffer_{ nullptr }, root_{ nullptr } {
    
}

void XmlParser::PrintFileBuffer() {
    std::cout << file_buffer_ << std::endl;
}

bool XmlParser::LoadFile(const char* filename) {
    bool isLoaded = false;
    
    FILE* f = fopen(filename, "r");
    
    // Determine file size_t
    fseek(f, 0, SEEK_END);
    size_t size = ftell(f);
    
    char* where = new char[size];
    
    rewind(f);
    fread(where, sizeof(char), size, f);
    
    file_buffer_ = where;
    
    delete[] where;
    
    
    
    return true;
}