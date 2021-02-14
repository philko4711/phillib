#include "WrapperTinyXML.h"
#include <iostream>

namespace phillib
{
namespace utils
{

tinyxml2::XMLElement& WrapperTinyXML::getTinyxmlChildElement(const std::string& tag, tinyxml2::XMLElement* rootElement) 
{
  tinyxml2::XMLElement* element = rootElement->FirstChildElement(tag.c_str());
  if(!element)
  {
    std::cout << __PRETTY_FUNCTION__ << " error malformed config. " << tag << " is missing" << std::endl;
    throw std::string("Invalid data file");
  }
  return *element;
}

void WrapperTinyXML::loadTinyXmlAttribute(unsigned int& param, const std::string& tag, tinyxml2::XMLElement& element)
 {
  tinyxml2::XMLError result = element.QueryUnsignedAttribute(tag.c_str(), &param);
  if(result != tinyxml2::XMLError::XML_SUCCESS)
    throw std::string("Error loading " + tag + " in " + element.Value());
 }

void WrapperTinyXML::loadTinyXmlAttribute(float& param, const std::string& tag, tinyxml2::XMLElement& element)
 {
  tinyxml2::XMLError result = element.QueryFloatAttribute(tag.c_str(), &param);
  if(result != tinyxml2::XMLError::XML_SUCCESS)
  {
    std::cout << __PRETTY_FUNCTION__ << std::string("Error loading " + tag + " in " + element.Value()) << std::endl;
    throw std::string("Error loading " + tag + " in " + element.Value());
  }
  //std::cout << __PRETTY_FUNCTION__ << " " << tag << " : " << param << std::endl;
 }

void WrapperTinyXML::loadTinyXmlAttribute(std::string& param, const std::string& tag, tinyxml2::XMLElement& element)
 {
   const char* attribute = nullptr;
  attribute = element.Attribute(tag.c_str());
  if(!attribute)
  {
    std::cout << __PRETTY_FUNCTION__ << std::string("Error loading " + tag + " in " + element.Value()) << std::endl;
    throw std::string("Error loading " + tag + " in " + element.Value());
  }
  
  param = std::string(attribute);
  if(param.empty())
  {
    std::cout << __PRETTY_FUNCTION__ << std::string("Error loading " + tag + " in " + element.Value()) << std::endl;
    throw std::string("Error loading " + tag + " in " + element.Value());
  }
 }

// const ITreeObject::TreeObjectType WrapperTinyXML::childElementType(tinyxml2::XMLElement* root) 
// {
//    tinyxml2::XMLElement* node = root->FirstChildElement("Node");
//   tinyxml2::XMLElement* leaf = root->FirstChildElement("Leaf");
//   if(node)
//     return ITreeObject::TreeObjectType::NODE;
//   else if(leaf)
//     return ITreeObject::TreeObjectType::LEAF;
//   else
//     throw  std::string(std::string(__PRETTY_FUNCTION__) + " error invalid element type " + root->FirstChildElement()->Value());
  
// }

// const ITreeObject::TreeObjectType WrapperTinyXML::elementType(tinyxml2::XMLElement* element) 
// {
//   const std::string value = element->Value();
//   if(value == "Node")
//     return ITreeObject::TreeObjectType::NODE;
//   else if(value == "Leaf")
//     return ITreeObject::TreeObjectType::LEAF;
//   else
//     throw  std::string(std::string(__PRETTY_FUNCTION__) + " error invalid element name " + value.c_str());
  
// }

tinyxml2::XMLElement& WrapperTinyXML::getChildElement(const std::string& tag, tinyxml2::XMLElement& parent) 
{
  tinyxml2::XMLElement* element = parent.FirstChildElement(tag.c_str());
  if(element == nullptr)
    throw  std::string(__PRETTY_FUNCTION__) + " error. No " + tag + " found.";
  return *element;
}

bool WrapperTinyXML::xmlElementContains(tinyxml2::XMLElement* element, const std::string& tag) 
{
  tinyxml2::XMLElement* child = element->FirstChildElement(tag.c_str());
  // std::cout << __PRETTY_FUNCTION__ << element->Value() << " contains:" << std::endl;
  //   utils::listChildNodeAttributes(element);
  if(child)
    return true;
  else
    return false;  
}

void WrapperTinyXML::loadTinyXmlElementContent(unsigned int& val, tinyxml2::XMLElement& element) 
{
  tinyxml2::XMLError result = element.QueryUnsignedText(&val);
  if(result != tinyxml2::XMLError::XML_SUCCESS)
    throw std::string(std::string(__PRETTY_FUNCTION__) + " error. Cant read unsigned val in element " + element.Value());
}

void WrapperTinyXML::loadTinyXmlElementContent(int& val, tinyxml2::XMLElement& element) 
{
  tinyxml2::XMLError result = element.QueryIntText(&val);
  if(result != tinyxml2::XMLError::XML_SUCCESS)
    throw std::string(std::string(__PRETTY_FUNCTION__) + " error. Cant read int val in element " + element.Value());
}


void WrapperTinyXML::loadTinyXmlElementContent(float& val, tinyxml2::XMLElement& element)
 {
   tinyxml2::XMLError result = element.QueryFloatText(&val);
  if(result != tinyxml2::XMLError::XML_SUCCESS)
    throw std::string(std::string(__PRETTY_FUNCTION__) + " error. Cant read float val in element " + element.Value());
 }

void WrapperTinyXML::listChildNodeAttributes(tinyxml2::XMLElement* element) 
{
  std::cout << __PRETTY_FUNCTION__ << " element " << element->Value() << " contains:" << std::endl;
  for(auto childElement = element->FirstChildElement(); childElement != nullptr; childElement = childElement->NextSiblingElement())
    std::cout   << "\t" << childElement->Value() << std::endl;
}

} // namespace utils

} // namespace phros_traversability