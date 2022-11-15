#ifndef XML_PARSER_H
#define XML_PARSER_H

#include <vector>

#include "xml_node.h"

class XmlParser {
public:

/* --- +Constructors and destructors ---------------------------------------- */ 
  XmlParser(XmlParser &other) = delete;
  
/* --- +Methods ------------------------------------------------------------- */    
  static XmlParser* GetInstance();
  bool LoadFile(const char* filename);
  
/* --- +Overloaded operators ------------------------------------------------ */      
  void operator=(const XmlParser &other) = delete;
  
/* --- +Tools --------------------------------------------------------------- */
  void PrintFileBuffer();
  XmlNode* Parse(); //<--- usunac po rozwijaniu
  
protected:
/* --- #Constructors and destructors ---------------------------------------- */ 
  XmlParser();
  
private:

/* --- -Parser -------------------------------------------------------------- */
  enum class XmlTokenType {
    kWhitespace,         // ' '
    kOpenTag,            // '<', '</'
    kCloseTag,           // '>', '/>'
    kElementName,        // <'ElemenName'>...</'ElemenName'>, <'ElemenName' />
    kAttribName,         // 'AttribName'="AttribValue"
    kAttribValue,        // AttribName="'AttribValue'"
    kAttribAssign,       // AttribName'='"AttribValue"
    kAttribValueQuote,   // AttribName='"'AttribValue'"'
    kText,                // <element>'Text'</element>
    kReference           // '&lt;' or '&#23'
  };
  
  struct XmlToken {
      XmlTokenType type{ XmlTokenType::kWhitespace };
      std::string data{ "" };
  };

  std::vector<XmlToken> Tokenize();
  void PushToken(std::vector<XmlToken>& tokens, XmlToken& token);
  //XmlNode* Parse(); <--- To jest jego miejsce
  
/* --- -Tools --------------------------------------------------------------- */
  void PrintTokens(std::vector<XmlToken> tokens);
  std::string ToString(XmlTokenType type);

/* --- -Data members -------------------------------------------------------- */
  std::string file_buffer_;
};


#endif // !XML_NODE_H