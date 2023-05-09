// Name:  Kai Yu Man
// Seneca Student ID:  162280218
// Seneca email:  kman2@myseneca.ca
// Date of completion:  10 Mar 2023 (This module)
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef STATION_H
#define STATION_H

#include <iostream>
#include <iomanip>
#include "Utilities.h"

namespace sdds {

    class Station {
        int m_id{};
        std::string m_itemName{};
        std::string m_desc{};
        size_t m_nextSN{};
        size_t m_qty{};

        static size_t m_widthField;
        static size_t id_generator;

    public:
        Station(const std::string oneRecord);
        const std::string& getItemName() const;
        size_t getNextSerialNumber();
        size_t getQuantity() const;
        void updateQuantity();
        void display(std::ostream& os, bool full) const;
    };

}

#endif
