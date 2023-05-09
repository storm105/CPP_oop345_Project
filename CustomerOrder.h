// Name:  Kai Yu Man
// Seneca Student ID:  162280218
// Seneca email:  kman2@myseneca.ca
// Date of completion:  5 Apr 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef CUSTOMERORDER_H
#define CUSTOMERORDER_H

#include <iostream>
#include "Station.h"

namespace sdds {

    struct Item {
        std::string m_itemName{};
        size_t m_serialNumber{0};
        bool m_isFilled{false};

        Item(const std::string& src) : m_itemName(src) {};
    };

    class CustomerOrder {
        std::string m_name{};
        std::string m_product{};
        size_t m_cntItem{};
        Item ** m_lstItem{};

        static size_t m_widthField;

    public:
        CustomerOrder() = default;
        CustomerOrder(const std::string input);

        // Rule of 5:
        CustomerOrder(const CustomerOrder& src);  // this one 100% throws an exception
        CustomerOrder& operator=(const CustomerOrder& src) = delete;  // this one is deleted

        CustomerOrder(CustomerOrder&& src) noexcept;
        CustomerOrder& operator=(CustomerOrder&& src) noexcept;

        virtual ~CustomerOrder();

        bool isOrderFilled() const;
        bool isItemFilled(const std::string& itemName) const;
        void fillItem(Station& station, std::ostream& os);
        void display(std::ostream& os) const;
    };

}

#endif
