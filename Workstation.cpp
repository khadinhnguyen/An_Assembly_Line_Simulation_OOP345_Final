#include "Workstation.h"
#include <algorithm>

namespace sdds {
   std::deque<CustomerOrder> pending; // holds the orders to be placed onto the assembly line at the first station
   std::deque<CustomerOrder> completed; // holds the orders that have been removed from the last station and have been completely filled
   std::deque<CustomerOrder> incomplete;

   //Workstation::~Workstation()
   //{
   //   delete m_pNextStation;
   //   m_pNextStation = nullptr;
   //}
 /*  bool Workstation::operator==(const std::string& str)
   {
      bool found = false;
      if (Station::getItemName() == str) found = true;
      return found;
   }*/
   void Workstation::fill(std::ostream& os)
   {
      if (!m_order.empty()) {
         std::for_each(m_order.begin(), m_order.end(), [&](CustomerOrder& C) {C.fillItem(*this, os); });
      }
   }
   bool Workstation::attemptToMoveOrder()
   {
      bool success = false;
      // this->getItemName()
      if (!m_order.empty()) {
         if (m_order.front().isItemFilled(Station::getItemName())) {
            if (m_pNextStation == nullptr) {
               completed.push_back(std::move(m_order.front()));
               m_order.pop_front();
               success = true;
            }
            else {
               m_pNextStation->m_order.push_back(std::move(m_order.front()));
               m_order.pop_front();
            }

         }
         else {
            if (m_pNextStation == nullptr) {
               incomplete.push_back(std::move(m_order.front()));
               m_order.pop_front();
               success = true;
            }
            else {
               m_pNextStation->m_order.push_back(std::move(m_order.front()));
               m_order.pop_front();
            }
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
   void Workstation::display(std::ostream& os)
   {
      os << Station::getItemName() << " --> "; // check why no ()
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
      m_order.push_back(std::move(newOrder)); // check
      return *this;
   }
}