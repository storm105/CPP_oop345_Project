// Name:  Kai Yu Man
// Seneca Student ID:  162280218
// Seneca email:  kman2@myseneca.ca
// Date of completion: 5 Apr 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef WORKSTATION_H
#define WORKSTATION_H

#include <deque>
#include <algorithm>
#include "CustomerOrder.h"

namespace sdds {

    extern std::deque<CustomerOrder> g_pending;
    extern std::deque<CustomerOrder> g_completed;
    extern std::deque<CustomerOrder> g_incomplete;

    class Workstation : public Station{
        std::deque<CustomerOrder> m_orders;
        Workstation * m_pNextStation{};

    public:
        Workstation() = default;
        Workstation(const std::string& input);

        Workstation(const Workstation& src) = delete;
        Workstation& operator=(const Workstation& src) = delete;
        Workstation(Workstation&& src) noexcept = delete;
        Workstation& operator=(Workstation&& src) noexcept = delete;

        void fill(std::ostream& os);
        bool attemptToMoveOrder();
        void setNextStation(Workstation* station);
        Workstation* getNextStation() const;
        void display(std::ostream& os) const;
        Workstation& operator+=(CustomerOrder&& newOrder);

    };


}


#endif