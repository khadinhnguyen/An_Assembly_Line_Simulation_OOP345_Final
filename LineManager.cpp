#include "LineManager.h"
#include "Workstation.h"
#include <fstream>
#include <algorithm>
#include <string>
//#include "Utilities.h"

namespace sdds {
   unsigned LineManager::noOfIterationRun = 0;

   LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
   {
      Utilities U;
      size_t readPosition = 0;
      bool keepReading = true;
      std::string fromFile = "";
      std::string frontStation = "";
      std::string nextStation = "";
      Workstation* tempWS = nullptr;
      std::ifstream f(file);
      if (!f) {
         std::cerr << "ERROR: Cannot open file [" << file << "]." << std::endl;
         return;
      }
      while (!f.eof()) {
     
               std::getline(f, fromFile);
               frontStation = U.extractToken(fromFile, readPosition, keepReading);
               nextStation = U.extractToken(fromFile, readPosition, keepReading);
               tempWS = *(std::find(stations.begin(), stations.end(), [=](Workstation* W) {return frontStation.compare(W->getItemName()) == 0; }));
               tempWS->setNextStation(*(std::find(stations.begin(), stations.end(), [=](Workstation* W) {return nextStation.compare(W->getItemName()) == 0; })));
               activeLine.push_back(tempWS);            

      }
      f.close();
      m_firstStation = activeLine.front();
      m_cntCustomerOrder = pending.size();
   }
   //void LineManager::linkStations()
   //{
   //   //std::sort(activeLine.begin(), activeLine.end(), [](Workstation* left, Workstation* right) {return left->getNextStation() == right; });
   //   //m_firstStation = activeLine.front();
   //   std::cout << "LinkStations is called";
   //}
   //bool LineManager::run(std::ostream& os)
   //{
   //   bool allfilled = false;
   //   noOfIterationRun++;
   //   unsigned j = 0;
   //   os << "Line Manager Iteration: " << noOfIterationRun << std::endl;
   //   if (!pending.empty()) {
   //      *m_firstStation += std::move(pending.front());
   //      pending.pop_front();
   //      for (auto i = activeLine.begin(); i != activeLine.end(); i++) {
   //         (*i)->fill(os);
   //         (*i)->attemptToMoveOrder();
   //      }
   //   }
   //   m_cntCustomerOrder = pending.size();
   //   if (m_cntCustomerOrder == 0) allfilled = true;    
   //   return allfilled;
   //}
   //void LineManager::display(std::ostream& os) const
   //{
   //   for (const auto* station : activeLine)
   //      station->Station::display(std::cout, true);
   //   std::cout << std::endl << std::endl;
   //}
}