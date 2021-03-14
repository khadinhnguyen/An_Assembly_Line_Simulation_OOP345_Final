#include "Utilities.h"

namespace sdds {

   void Utilities::setFieldWidth(size_t newWidth)
   {
      m_widthField = newWidth;
   }

   size_t Utilities::getFieldWidth() const
   {
      return m_widthField;
   }

   // why need bool& more?
   std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
   {
      std::string extractedStr{};
      if (m_delimiter == str.at(next_pos)) {
         more = false;
         throw "a delimiter is found at next_pos";
      }
      std::string::size_type endChar = str.find(m_delimiter, next_pos);
      if (endChar == std::string::npos) more = false;
      extractedStr = str.substr(next_pos, endChar - next_pos);
      next_pos = endChar + 1;
      if (m_widthField < extractedStr.length()) setFieldWidth(extractedStr.length());
 

      
      return extractedStr;
   }

   void Utilities::setDelimiter(char newDelimiter)
   {
      m_delimiter = newDelimiter;
   }

   char Utilities::getDelimiter()
   {
      return m_delimiter;
   }

   char Utilities::m_delimiter = {};


}