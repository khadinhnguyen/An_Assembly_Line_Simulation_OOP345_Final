#ifndef SDDS_WORKSTATION_H_
#define SDDS_WORKSTATION_H_
#include <queue>
#include <iostream>
#include "CustomerOrder.h"
#include "Station.h"
namespace sdds {

   extern std::queue<CustomerOrder> pending; // holds the orders to be placed onto the assembly line at the first station
   extern std::queue<CustomerOrder> completed; // holds the orders that have been removed from the last station and have been completely filled
   extern std::queue<CustomerOrder> incompleted; // holds the orders that have been removed from the last station and could not be filled completely

   class Workstation : public Station {
      std::queue<CustomerOrder> m_order;
      Workstation* m_pNextStation;

   public:
      Workstation(const std::string& str) : m_pNextStation(nullptr), Station(str) {}
      ~Workstation();
      void operator=(const Workstation& W) = delete;
      void operator=(Workstation&& W) = delete;
      void fill(std::ostream& os);
      bool attemptToMoveOrder();
      void setNextStation(Workstation* station);
      const Workstation* getNextStation() const;
      void display(std::ostream& os) const;
      Workstation& operator+=(CustomerOrder && newOrder);

   };
}

#endif // !SDDS_WORKSTATION_H_
