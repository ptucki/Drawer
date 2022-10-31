#include "xml_node.h"

/* --- PUBLIC --------------------------------------------------------------- */

XmlNode::XmlNode(std::string_view name) :
  name_{ name },
  value_{ "" },
  type_{ XmlNodeType::kElement }
{   
  this->AddTextNode("");
  //std::cout << "New node" << std::endl;
}

XmlNode::~XmlNode() {
  for (size_t i = 0; i < subnodes_.size(); ++i) {
    delete subnodes_[i];
  }
    //std::cout << "Node deleted" << std::endl;
}

XmlNode* XmlNode::AddElement(std::string_view name) {
  XmlNode* temp = new XmlNode(XmlNodeType::kElement, name, "");
  //To change -> maybe unique pointers
  subnodes_.push_back(temp);
    
  return temp;
}

XmlNode* XmlNode::AddAttribute(std::string_view name, std::string_view value) {
  XmlNode* temp = new XmlNode(XmlNodeType::kAttribute, name, value);
  subnodes_.insert(subnodes_.begin() + 1, temp);
    
  return temp;
}

void XmlNode::PrintXmlDoc(int indent) {
  static int indent_ = 0;
  std::cout << std::string(indent_, ' ') <<
  "["<< GetNodeType(type_) << "; " << name_ << "; " << value_ << "]\n";
  
  indent_ += indent;
  for(int i = 0; i < subnodes_.size(); ++i) {
    subnodes_[i]->PrintXmlDoc(indent_);
  }
  indent_ -= indent;
}

/* --- PRIVATE -------------------------------------------------------------- */

XmlNode::XmlNode(
  XmlNode::XmlNodeType type,
  std::string_view     name,
  std::string_view     value)
  :
  type_{ type },
  name_{ name },
  value_{ value }
{
  if(type_ == XmlNodeType::kElement) {
    this->AddTextNode("");
  }
  std::cout << "New node" << std::endl;
}

XmlNode* XmlNode::AddTextNode(std::string_view value_) {
  subnodes_.insert(subnodes_.begin(), new XmlNode(XmlNodeType::kText,"#text",""));
}

std::string XmlNode::GetNodeType(XmlNodeType type) {
  std::string returnValue;
    
  switch(type) {
    case XmlNodeType::kUndefined:
      returnValue = "U";
      break;
    case XmlNodeType::kElement:
      returnValue = "E";
      break;
    case XmlNodeType::kAttribute:
      returnValue = "A";
      break;                
    case XmlNodeType::kText:
      returnValue = "T";
      break;
    default:
      returnValue = "ERROR";
      break;
  }
  return returnValue;
}
