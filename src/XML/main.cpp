#include <iostream>

#include "xml_node.h"
#include "xml_parser.h"

int main()
{
  XmlParser* parser = XmlParser::GetInstance();
    
  parser->LoadFile("example.xml");
  parser->PrintFileBuffer();  
  parser->Parse();  
    
  return 0;
}

/* ========================================================================== */


