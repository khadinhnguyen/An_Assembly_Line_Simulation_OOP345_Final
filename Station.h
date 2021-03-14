#ifndef SDDS_STATION_H_
#define SDDS_STATION_H_
#include <string>
#include <sstream>
#include <iomanip>
#include "Utilities.h"

namespace sdds {

   class Station {
      int m_station_id;
      std::string m_item_name;
      std::string m_description;
      size_t m_serialNumber;
      //size_t m_next_serial_number;
      size_t m_quantity;
      static size_t m_widthField;
      static unsigned id_generator;
   public:
      Station(const std::string str);
      const std::string& getItemName();
      size_t getNextSerialNumber();
      size_t getQuantity() const;
      void updateQuantity();
      void display(std::ostream& os, bool full) const;
   };


}
#endif // !SDDS_STATION_H_
