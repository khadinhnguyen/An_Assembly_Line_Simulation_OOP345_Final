#ifndef SDDS_LINEMANAGER_H_
#define SDDS_LINEMANAGER_H_
#include "Workstation.h"
#include <vector>

namespace sdds {

   class LineManager {
      std::vector<Workstation*> activeLine;
      size_t m_cntCustomerOrder = 0u; // total number of CustomerOrder objects
      Workstation* m_firstStation = nullptr;
      static unsigned noOfIterationRun;

   public:
      LineManager(const std::string& file, const std::vector<Workstation*>& stations);
      void linkStations();
      bool run(std::ostream& os);
      void display(std::ostream& os) const;

   };
}
#endif // !SDDS_LINEMANAGER_H_
