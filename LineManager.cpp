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
      size_t lineIndex = 0;
      bool keepReading = true;
      std::string fromFile = "";
      std::string frontStation = "";
      std::string nextStation = "";
      //Workstation* tempWS = nullptr;
      std::ifstream f(file);
      if (!f) {
         std::cerr << "ERROR: Cannot open file [" << file << "]." << std::endl;
         return;
      }
      while (!f.eof()) {
         keepReading = true;         
         std::getline(f, fromFile);
         frontStation = U.extractToken(fromFile, readPosition, keepReading);
         auto i = std::find_if(stations.begin(), stations.end(), [=](Workstation* W) {return (W->getItemName() == frontStation); });
         activeLine.push_back(*i);
         if (keepReading) {
            nextStation = U.extractToken(fromFile, readPosition, keepReading);
            i = std::find_if(stations.begin(), stations.end(), [=](Workstation* W) {return (W->getItemName() == nextStation); });
            activeLine[lineIndex]->setNextStation(*i);
         }
         lineIndex++;

               //std::cout << (*i)->getItemName();
               //for (auto i = stations.begin(); i != stations.end(); i++) {
               //   (*i)->display(std::cout);
               //}
               //tempWS->setNextStation(*(std::find(stations.begin(), stations.end(), [&](Workstation* W) {return (nextStation.compare(W->getItemName()) == 0); })));
            

      }
      f.close();
      m_firstStation = activeLine.front();
      m_cntCustomerOrder = pending.size();
   }
   void LineManager::linkStations()
   {
      std::sort(activeLine.begin(), activeLine.end(), [](Workstation* left, Workstation* right) {return (left->getNextStation() == right || right->getNextStation() == nullptr); });
      m_firstStation = activeLine.front();
   }
   bool LineManager::run(std::ostream& os)
   {
      bool allfilled = false;
      noOfIterationRun++;
      os << "Line Manager Iteration: " << noOfIterationRun << std::endl;
      if (!pending.empty()) {
         *m_firstStation += std::move(pending.front());
         pending.pop_front();
      }
      if (m_cntCustomerOrder > 0u){
         //for (auto i = activeLine.begin(); i != activeLine.end() && j < noOfIterationRun; i++) {
         //   (*i)->fill(os);
         //   (*i)->attemptToMoveOrder();
         //   j++;
         //}
         std::for_each(activeLine.begin(), activeLine.end(), [&](Workstation* W) {W->fill(os); });
         std::for_each(activeLine.rbegin(), activeLine.rend(), [&](Workstation* W) {if (W->attemptToMoveOrder()) { m_cntCustomerOrder--;} });
      }
      if (m_cntCustomerOrder == 0u) allfilled = true;    
      return allfilled;
   }
   void LineManager::display(std::ostream& os) const
   {
      for (const auto station : activeLine)
         station->display(std::cout);
   }
}