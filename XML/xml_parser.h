#include <fstream>
#include <cstdio>

#include "xml_parser.h"

XmlParser* XmlParser::GetInstance() {
    static XmlParser* instance = new XmlParser();
    if(instance == nullptr) {
        instance = new XmlParser();
    }
    return instance;
}

XmlParser::XmlParser() : file_buffer_{ "" }, root_{ nullptr } {
    
}

void XmlParser::PrintFileBuffer() {
    std::cout << "size: " << file_buffer_.size() << std::endl;
    std::cout << "capacity: " << file_buffer_.capacity() << std::endl;
    std::cout << file_buffer_ << std::endl;
}

bool XmlParser::LoadFile(const char* filename) {
    bool isLoaded = false;
    
    FILE* f = fopen(filename, "r");
    
    if (f == NULL) {
        std::cout << "File cannot be opened." << std::endl;
    } else {
        // Determine file size_t
        fseek(f, 0, SEEK_END);
        size_t size = ftell(f);
        
        std::cout << size << std::endl;
        
        char* where = new char[size];
        
        rewind(f);
        fread(where, sizeof(char), size, f);
        file_buffer_.reserve(size);
        
        file_buffer_.assign(where, size);
        
        delete[] where;
        
        fclose(f);
    }
    
    return true;
}