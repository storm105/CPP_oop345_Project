// Name:  Kai Yu Man
// Seneca Student ID:  162280218
// Seneca email:  kman2@myseneca.ca
// Date of completion: 5 Apr 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Workstation.h"

namespace sdds {

    std::deque<CustomerOrder> g_pending{};
    std::deque<CustomerOrder> g_completed{};
    std::deque<CustomerOrder> g_incomplete{};

    Workstation::Workstation(const std::string & input) : Station(input) {
    }

    void Workstation::fill(std::ostream & os) {
        if(!m_orders.empty()){
            m_orders.front().fillItem(*this, os);
        }
    }

    bool Workstation::attemptToMoveOrder() {
        bool isOrderMoved {false};

        if (!m_orders.empty()) {
            if ( m_orders.front().isItemFilled(this->getItemName()) || this->getQuantity() <= 0) {

                if (m_pNextStation) {  // there IS a next station, move it there!
                    *m_pNextStation += std::move(m_orders.front());
                } else {  // there is NO next station...
                    if (m_orders.front().isOrderFilled()) {
//                        std::cout << " ###### debug:  push back m_orders to g completed ######\n";
                        g_completed.push_back(std::move(m_orders.front()));
                    } else {
//                        std::cout << " ******* debug:  push back m_orders to g INcompleted *******\n";
                        g_incomplete.push_back(std::move(m_orders.front()));
                    }
                }
                m_orders.pop_front();
                isOrderMoved = true;
            }
        }
        return isOrderMoved;
    }


    void Workstation::setNextStation(Workstation * station = nullptr) {
        m_pNextStation = station;
    }

    Workstation *Workstation::getNextStation() const {
        return m_pNextStation;
    }

    void Workstation::display(std::ostream & os) const {
        os << this->getItemName() << " --> ";
        if(getNextStation()){
            os << getNextStation()->getItemName() << '\n';
        } else {
            os << "End of Line\n";
        }
    }

    Workstation &Workstation::operator+=(CustomerOrder &&newOrder) {
        m_orders.push_back(std::move(newOrder));
        return *this;
    }

}