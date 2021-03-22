//==============================================
// Name:           Kha Nguyen
// Student Number: 165869199
// Email:          knguyen93@myseneca.ca
// Date:           Mar 21,2021
// I confirm that I am the only author of this file and the content was created entirely by me
//==============================================
#ifndef SDDS_CUSTOMERORDER_H_
#define SDDS_CUSTOMERORDER_H_
#include <string>
#include "Station.h"

namespace sdds {
   struct Item {
      std::string m_itemName;
      size_t m_serialNumber{ 0 };
      bool m_isFilled{ false };
      Item(const std::string& src) : m_itemName(src) {};
   };


   class CustomerOrder {
      std::string m_name; // name of the customer
      std::string m_product; // name of the product being assembled
      size_t m_cntItem; // a count of the number of items in the customer's order
      Item** m_lstItem; // pointer to array of pointers
      static size_t m_widthField;
      void listResize();
   public:
      CustomerOrder() : m_name{}, m_product{}, m_cntItem{}, m_lstItem{ nullptr }{}
      CustomerOrder(const std::string& str);
      CustomerOrder(const CustomerOrder& C);
      CustomerOrder(CustomerOrder&& C) noexcept;
      CustomerOrder& operator=(const CustomerOrder& C) = delete;
      CustomerOrder& operator=(CustomerOrder&& C) noexcept;
      ~CustomerOrder();
      bool isFilled()const;
      bool isItemFilled(const std::string& itemName) const;
      void fillItem(Station& station, std::ostream& os);
      void display(std::ostream& os)const;


   };
}
#endif // !SDDS_CUSTOMERORDER_H_
