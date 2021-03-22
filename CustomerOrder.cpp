#include "CustomerOrder.h"
#include "Utilities.h"

namespace sdds {
   size_t CustomerOrder::m_widthField = 0u;
   void CustomerOrder::listResize()
   {
      Item** temp = new Item* [m_cntItem];
      int i = 0;
      for (; i < (int)m_cntItem; i++) {
         temp[i] = m_lstItem[i];
      }
      delete[] m_lstItem;
      m_lstItem = new Item * [m_cntItem + 1];
      for (i = 0; i < (int)m_cntItem; i++) {
         m_lstItem[i] = temp[i];
      }
      delete[] temp;
   }
   CustomerOrder::CustomerOrder(const std::string& str){
      m_cntItem = 0;
      m_lstItem = new Item*[1];
      size_t extractPosition = 0;
      bool keepGoing = true;
      Utilities U;
      //Utilities::setDelimiter('|');
      m_name = U.extractToken(str, extractPosition, keepGoing);
      m_product = U.extractToken(str, extractPosition, keepGoing);
      Item* temp = new Item(U.extractToken(str, extractPosition, keepGoing));
      m_lstItem[0] = temp;
      m_cntItem++;
      temp = nullptr;
      while (keepGoing) {
         temp = new Item(U.extractToken(str, extractPosition, keepGoing));
         listResize();
         m_lstItem[m_cntItem] = temp;
         temp = nullptr;
         m_cntItem++;
      }
      if (m_widthField < U.getFieldWidth()) { m_widthField = U.getFieldWidth(); }
   }

   CustomerOrder::~CustomerOrder()
   {
      for (int i = 0; i < (int)m_cntItem; i++) {
         delete m_lstItem[i];
      }
      delete[] m_lstItem;
   }

   bool CustomerOrder::isFilled() const
   {
      bool allFilled = true;
      for (int i = 0; i < (int)m_cntItem; i++) {
         if (!m_lstItem[i]->m_isFilled) allFilled = false;
      }
      return allFilled;
   }

   bool CustomerOrder::isItemFilled(const std::string& itemName) const
   {
      bool isFilled = true;
      for (int i = 0; i < (int)m_cntItem; i++) {
         if (m_lstItem[i]->m_itemName.compare(itemName) == 0) {
            if (!m_lstItem[i]->m_isFilled) isFilled = false;
         }
      }
      return isFilled;
   }

   void CustomerOrder::fillItem(Station& station, std::ostream& os)
   {
      bool found = false;
      bool filled = false;
      for (int i = 0; i < (int)m_cntItem; i++) {
         if (station.getItemName().compare(m_lstItem[i]->m_itemName) == 0) {
            found = true;
            if (isItemFilled(m_lstItem[i]->m_itemName)) {
               filled = true;
            }
            else if (!m_lstItem[i]->m_isFilled && station.getQuantity() > 0) {
               m_lstItem[i]->m_isFilled = true;
               m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
               station.updateQuantity();
               filled = true;
            }
         }
      }
      if (found) {      
         if (filled) os << "    Filled " << m_name << ", " << m_product << " [" << station.getItemName() << ']' << std::endl;
         else os << "    Unable to fill " << m_name << ", " << m_product << " [" << station.getItemName() << ']' << std::endl;
      }
   }

   void CustomerOrder::display(std::ostream& os) const
   {
      os << m_name << " - " << m_product << std::endl;
      for (int i = 0; i < (int)m_cntItem; i++) {
         os << '[' << std::setw(6) << std::setfill('0') << std::right << m_lstItem[i]->m_serialNumber << "] " << std::setfill(' ');
         os << std::setw(m_widthField) << std::left << m_lstItem[i]->m_itemName << " - ";
         if (m_lstItem[i]->m_isFilled) os << "FILLED";
         else os << "TO BE FILLED";
         os << std::endl;
      }

   }



   CustomerOrder::CustomerOrder(CustomerOrder&& C) noexcept
   {
      operator=(std::move(C));
   }

   CustomerOrder::CustomerOrder(const CustomerOrder& C)
   {
      throw "ERROR: Cannot make copies";
   }

   //CustomerOrder& CustomerOrder::operator=(const CustomerOrder& C)
   //{
   //   if (this != &C) {
   //      m_name = C.m_name;
   //      m_product = C.m_product;
   //      m_cntItem = C.m_cntItem;
   //      delete[] m_lstItem;
   //      m_lstItem = new Item * [m_cntItem];
   //      for (int i = 0; i < (int)m_cntItem; i++) {
   //         m_lstItem[i] = C.m_lstItem[i];
   //      }
   //   }
   //   return *this;
   //}

   CustomerOrder& CustomerOrder::operator=(CustomerOrder&& C) noexcept
   {
      if (this != &C) {
         m_name = C.m_name;
         m_product = C.m_product;
         m_cntItem = C.m_cntItem;
         m_lstItem = C.m_lstItem;
         C.m_name = "";
         C.m_product = "";
         C.m_cntItem = 0;
         C.m_lstItem = nullptr;
      }
      return *this;
   }

   

}