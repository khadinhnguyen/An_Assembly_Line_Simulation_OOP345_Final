#include "Station.h"

namespace sdds {


   size_t Station::m_widthField = 0u;
   unsigned Station::id_generator = 0;

   Station::Station(const std::string str)
   {
      m_station_id = ++id_generator;
      std::stringstream buf;
      Utilities U;
      size_t scanPos = 0;
      bool keepGoing = true;
      m_item_name = U.extractToken(str, scanPos, keepGoing);
      //buf << U.extractToken(str, scanPos, keepGoing);
      //buf >> m_serialNumber;
      //buf << U.extractToken(str, scanPos, keepGoing);
      //buf >> m_quantity;
      m_serialNumber = std::stoi(U.extractToken(str, scanPos, keepGoing));
      m_quantity = std::stoi(U.extractToken(str, scanPos, keepGoing));
      //m_serialNumber = 12345;
      //m_quantity = 6;
      if (m_widthField < U.getFieldWidth()) m_widthField = U.getFieldWidth();
      m_description = U.extractToken(str, scanPos, keepGoing);

   }

   const std::string& Station::getItemName()
   {
      return m_item_name;
   }

   size_t Station::getNextSerialNumber()
   {
      return m_serialNumber++;
   }

   size_t Station::getQuantity() const
   {
      return m_quantity;
   }

   void Station::updateQuantity()
   {
      if (m_quantity > 0) {
         m_quantity--;
      }
   }

   void Station::display(std::ostream& os, bool full) const
   {
      os << '[' << std::setw(3) << std::setfill('0') << std::right << m_station_id << ']' << std::setfill(' ');
      os << " Item: " << std::setw(m_widthField) << std::left << m_item_name;
      os << " [" << std::setw(6) << std::setfill('0') << m_serialNumber << "] " << std::setfill(' ');
      if (full) {
         os << "Quantity: " << std::setw(m_widthField) << std::left << m_quantity;
         os << "Description: " << m_description;
         
      }
      os << std::endl;
   }

}