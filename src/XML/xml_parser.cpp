#include <cstdio>
#include <memory>
#include <functional>

#include "xml_parser.h"

XmlParser* XmlParser::GetInstance() {
    static XmlParser* instance = new XmlParser();
    if(instance == nullptr) {
        instance = new XmlParser();
    }
    return instance;
}


XmlParser::XmlParser() : file_buffer_{ "" } {
    
}




bool XmlParser::LoadFile(const char* filename) {
  bool file_read = false;
  this->file_buffer_ = "";
    
  auto close_file = [](FILE* f){fclose(f);};
  auto file_holder = std::unique_ptr<FILE, decltype(close_file)>(
      fopen(filename,"rb"),
      close_file
    );
    
  // File exists?
  if(file_holder) {
    FILE* f = file_holder.get();
    // Read succesfully?
    if(fseek(f, 0, SEEK_END) >= 0) {
      const long size = ftell(f);
       
      // Has any content?
      if(size >= 0){
        // Stream position correct?
        if(fseek(f, 0, SEEK_SET) >= 0) {
          // set size of string buffer
          file_buffer_.resize(size);
          // Read data to string
          fread(const_cast<char*>(file_buffer_.data()), 1, size, f);
          file_read = true;
        }
      }
    }
  }
  return file_read;    
}




XmlNode* XmlParser::Parse() {
  //XmlNode* = document("#document");
  
  PrintTokens(this->Tokenize());

  
  
  return new XmlNode("Ele");
}

void XmlParser::PushToken(std::vector<XmlToken>& tokens, XmlToken& token) {
    if(token.type != XmlTokenType::kWhitespace && token.data.size() > 0) tokens.push_back(token);
    token.data = "";
    token.type = XmlTokenType::kWhitespace;
}

std::vector<XmlParser::XmlToken> XmlParser::Tokenize() {
    std::vector<XmlToken> tokens;
    XmlToken curr;
    
    char_pos = 0;
    line_pos = 0;
    
    std::function<void(char)> TokenizingMethod = [](char ch){};
    
    auto TokenizeTag = [=, &curr, &tokens](char ch) {
        curr.data.append(1, ch);
    };
    
    auto TokenizeText = [=, &curr, &tokens](char ch) {
        static bool append_allowed = false;
        
        switch(ch) {
          case '\f':
          case '\n':
          case '\r':
          case '\t':
          case '\v':
            break;
            
          case ' ':
            if(append_allowed) curr.data.append(1, ch);
            break;
            
          case '&':
            PushToken(tokens, curr);
            curr.data.append(1, ch);
            curr.type = XmlTokenType::kReference;
            append_allowed = false;
            break;
            
          case ';':
            curr.data.append(1, ch);
            PushToken(tokens, curr);
            curr.type = XmlTokenType::kText;
            append_allowed = true;
            break;
          case '<':
            append_allowed = false;
            break;
          default:
            append_allowed = true;
            curr.data.append(1, ch);
            break;
        }
    };
    
    for(auto ch : file_buffer_) {
      switch(ch) {
        case '\n':
          line_pos++;
        case '<':
          TokenizingMethod(ch); //To disallow append trailing whitespaces
          PushToken(tokens, curr);
          curr.data.append(1, ch);
          TokenizingMethod = TokenizeTag;
          curr.type = XmlTokenType::kOpenTag;
          break;
          
        case '>':
          curr.data.append(1, ch);
          PushToken(tokens, curr);
          TokenizingMethod = TokenizeText;
          curr.type = XmlTokenType::kText;
          break;
          
        default:
          TokenizingMethod(ch);
          break;
      }
      char_pos++;
    }
    
  return tokens;
}


/* --- General Tools -------------------------------------------------------- */

void XmlParser::PrintFileBuffer() {
    std::cout << file_buffer_ << std::endl;
}

std::string XmlParser::ToString(XmlTokenType type) {
  std::string temp;
    
  switch(type) {
    case XmlTokenType::kWhitespace:
      temp = "WSPACE";
      break;
    case XmlTokenType::kOpenTag:
      temp = "OPEN_TAG";
      break;
    case XmlTokenType::kCloseTag:
      temp = "CLOSE_TAG";
      break;
    case XmlTokenType::kElementName:
      temp = "ELEM_NAME";
      break;
    case XmlTokenType::kAttribName:
      temp = "ATTR_NAME";
      break;
    case XmlTokenType::kAttribValue:
      temp = "ATTR_VAL";
      break;
    case XmlTokenType::kAttribAssign:
      temp = "ATTR_ASSIGN";
      break;
    case XmlTokenType::kText:
      temp = "TEXT";
      break;
    case XmlTokenType::kReference:
      temp = "TEXT_REF";
      break;
    case XmlTokenType::kAttribValueQuote:
      temp = "ATTR_QUOTE";
      break;
    default:
      temp = "UNDEFINED";
      break;
  }
    
  return temp;
}

void XmlParser::PrintTokens(std::vector<XmlToken> tokens) {
  for(auto token : tokens) {
    std::cout << "[ " << token.data << ", " << ToString(token.type) << " ]\n";
  }
}
