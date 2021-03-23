#include "Workstation.h"

namespace sdds {
   Workstation::~Workstation()
   {
      delete m_pNextStation;
   }
   void Workstation::fill(std::ostream& os)
   {
      if(!m_order.empty()) m_order.front().fillItem(*this, os);
   }
   bool Workstation::attemptToMoveOrder()
   {
      bool success = false;
      // this->getItemName()
      if (m_order.front().isItemFilled(Station::getItemName())) {
         if (m_pNextStation == nullptr) {
            completed.push(m_order.front());
            m_order.pop();
         }
         else {
            m_pNextStation->m_order.push(m_order.front());
            m_order.pop();
         }
         success = true;
      }
      else {
         if (m_pNextStation == nullptr) {
            incompleted.push(m_order.front());
            m_order.pop();
         }
         else {
            m_pNextStation->m_order.push(m_order.front());
            m_order.pop();
         }
      }

      return success;
   }
   void Workstation::setNextStation(Workstation* station)
   {
      m_pNextStation = station;
   }
   const Workstation* Workstation::getNextStation() const
   {
      return m_pNextStation;
   }
   void Workstation::display(std::ostream& os) const
   {
      os << &Station::getItemName << "-->"; // check why no ()
      if (m_pNextStation == nullptr) {
         os << "END OF LINE";
      }
      else {
         os << m_pNextStation->getItemName();
      }
      os << std::endl;
   }
   Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
   {
      m_order.push(std::move(newOrder)); // check
      return *this;
   }
}