#ifndef PHILLIB_UTILS_WRAPPER_TINY_XML_H_
#define PHILLIB_UTILS_WRAPPER_TINY_XML_H_

#include <string>
#include <tinyxml2.h>

namespace phillib
{

namespace utils
{

class WrapperTinyXML
{
public:
  WrapperTinyXML() {}
  virtual ~WrapperTinyXML() {}
  static tinyxml2::XMLElement&             getTinyxmlChildElement(const std::string& tag, tinyxml2::XMLElement* rootElement);
  static void                              loadTinyXmlAttribute(unsigned int& param, const std::string& tag, tinyxml2::XMLElement& element);
  static void                              loadTinyXmlAttribute(float& param, const std::string& tag, tinyxml2::XMLElement& element);
  static void                              loadTinyXmlAttribute(std::string& param, const std::string& tag, tinyxml2::XMLElement& element);
  static tinyxml2::XMLElement&             getChildElement(const std::string& tag, tinyxml2::XMLElement& parent);
  static bool                              xmlElementContains(tinyxml2::XMLElement* element, const std::string& tag);
  static void                              loadTinyXmlElementContent(unsigned int& val, tinyxml2::XMLElement& element);
  static void                              loadTinyXmlElementContent(int& val, tinyxml2::XMLElement& element);
  static void                              loadTinyXmlElementContent(float& val, tinyxml2::XMLElement& element);
  static void                              listChildNodeAttributes(tinyxml2::XMLElement* element);
};

} // namespace utils

} // namespace phros_traversability

#endif