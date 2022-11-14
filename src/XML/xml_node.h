#ifndef XML_NODE_H
#define XML_NODE_H

#include <iostream>
#include <vector>
#include <string_view>

class XmlNode {
public:
/* --- +Constructors and destructors ---------------------------------------- */ 
  XmlNode(std::string_view name);
  ~XmlNode();
    
/* --- +Methods ------------------------------------------------------------- */    
  XmlNode* AddElement(std::string_view name);
  XmlNode* AddAttribute(std::string_view name, std::string_view value);

/* --- -Tools --------------------------------------------------------------- */
  void PrintXmlDoc(int indent);

private:

  enum class XmlNodeType {
    // https://developer.mozilla.org/en-US/docs/Web/API/Node/nodeType
    kUndefined = 0,
    kElement,
    kAttribute,
    kText,
  };

/* --- -Constructors -------------------------------------------------------- */    
  XmlNode(XmlNodeType type, std::string_view name, std::string_view value);

/* --- -Methods------- ------------------------------------------------------ */
  XmlNode* AddTextNode(std::string_view value);

/* --- -Tools --------------------------------------------------------------- */
  std::string GetNodeType(XmlNodeType type);

/* --- -Members ------------------------------------------------------------- */
  std::string name_;
  std::string value_;
  XmlNodeType type_{ XmlNodeType::kUndefined };
  std::vector<XmlNode*> subnodes_;

};

#endif // !XML_NODE_H