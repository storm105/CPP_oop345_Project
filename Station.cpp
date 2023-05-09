// Name:  Kai Yu Man
// Seneca Student ID:  162280218
// Seneca email:  kman2@myseneca.ca
// Date of completion:  10 Mar 2023 (This module)
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Station.h"

namespace sdds {
    // static (class) variables initialization:
    size_t Station::m_widthField = 0;
    size_t Station::id_generator = 0;

    Station::Station(const std::string oneRecord) {
        size_t nextPos = 0;
        bool anyMore = true;
        Utilities tempObj{};

        m_id = ++id_generator;
        m_itemName = tempObj.extractToken(oneRecord, nextPos, anyMore);
        m_nextSN = stoi(tempObj.extractToken(oneRecord, nextPos, anyMore));
        m_qty = stoi(tempObj.extractToken(oneRecord, nextPos, anyMore));
        m_widthField = std::max(m_widthField, tempObj.getFieldWidth());
        m_desc = tempObj.extractToken(oneRecord, nextPos, anyMore);
    }

    const std::string &Station::getItemName() const {
        return m_itemName;
    }

    size_t Station::getNextSerialNumber() {
        return m_nextSN++;  // return m_nextSH THEN increment it by 1
    }

    size_t Station::getQuantity() const {
        return m_qty;
    }

    void Station::updateQuantity() {
        if(m_qty-1 >=0)
            m_qty--;
    }

    void Station::display(std::ostream &os, bool full) const {
        os << std::setfill('0') << std::setw(3) << std:: right << m_id  << " | ";
        os << std::setfill(' ') << std::setw(m_widthField) << std::left << m_itemName << " | ";
        os << std::setfill('0') << std::setw(6) << std:: right << m_nextSN << " | ";
        if(full){
            os << std::setfill(' ') << std::setw(4) << std::right << m_qty << " | " << m_desc;
        }
        os << "\n";
    }

}