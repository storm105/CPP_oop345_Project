// Name:  Kai Yu Man
// Seneca Student ID:  162280218
// Seneca email:  kman2@myseneca.ca
// Date of completion:  5 Apr 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "CustomerOrder.h"

namespace sdds {
    // static (class) variable initialization
    size_t CustomerOrder::m_widthField{};

    CustomerOrder::CustomerOrder(const std::string oneOrder) {
        size_t nextPos{};
        size_t firstItemPos{};
        bool anyMore = true;
        Utilities tempUti{};

        m_name = tempUti.extractToken(oneOrder, nextPos, anyMore);
        m_product = tempUti.extractToken(oneOrder, nextPos, anyMore);

        firstItemPos = nextPos;  // 1 of 2 (For later: move back read-in position to firstItemPosition)

        // find number of items first
        std::string itemsStr{};
        size_t n{};
        itemsStr = oneOrder.substr(firstItemPos);

        while(itemsStr[n]){
            if(itemsStr[n]==tempUti.getDelimiter()){
                m_cntItem++;
            }
            n++;
        }
        m_cntItem++;  // +1 needed as above only counted delimiter['|'] BETWEEN items

        // DMA for m_lstItem
        m_lstItem = new Item * [m_cntItem];

        nextPos = firstItemPos;   // 2 of 2  (move back read-in position to firstItemPosition)

        for(auto i=0u; i<m_cntItem; ++i){
            m_lstItem[i] = new Item(tempUti.extractToken(oneOrder, nextPos, anyMore));
        }

        if(m_widthField < tempUti.getFieldWidth())
            m_widthField = tempUti.getFieldWidth();

    }

    CustomerOrder::CustomerOrder(const CustomerOrder &src) {
        throw "Copy Constructor is called";
    }

    CustomerOrder::CustomerOrder(CustomerOrder && src) noexcept {
        *this = std::move(src);
    }

    CustomerOrder & CustomerOrder::operator=(CustomerOrder && src) noexcept {
        // 1. check self assignment
        if(this!=&src){
        // 2. ALWAYS delete current instance
            for(auto i=0u; i<m_cntItem; ++i){
                delete m_lstItem[i];
            }
            delete[] m_lstItem;

        // 3. ALWAYS MOVE it! no need check if src points to something or not!
            // 3a shallow copy
            m_name = src.m_name;
            m_product = src.m_product;
            m_cntItem = src.m_cntItem;
            src.m_name.clear();
            src.m_product.clear();
            src.m_cntItem = 0;
            // 3b deep copy
            m_lstItem = src.m_lstItem;
            src.m_lstItem = nullptr;
        }
        return *this;
    }

    CustomerOrder::~CustomerOrder() {
        for(auto i=0u; i<m_cntItem; ++i){
            delete m_lstItem[i];
        }
        delete[] m_lstItem;
    }

    bool CustomerOrder::isOrderFilled() const {
        bool allFilled{true};
        for(auto i=0u; i<m_cntItem && allFilled; ++i){
            if(!m_lstItem[i]->m_isFilled){
                allFilled = false;
            }
        }
        return allFilled;
    }

    bool CustomerOrder::isItemFilled(const std::string & itemName) const {
        bool allSelectedFilled{true};
        for(auto i=0u; i<m_cntItem && allSelectedFilled; ++i){
            if(m_lstItem[i]->m_itemName == itemName){
                if(!m_lstItem[i]->m_isFilled)
                    allSelectedFilled = false;
            }
        }
        return allSelectedFilled;
    }

    void CustomerOrder::fillItem(Station & station, std::ostream & os) {
        bool itemFilled{false};

        for(auto i=0u; i<m_cntItem && !itemFilled ; ++i){
            if( m_lstItem[i]->m_itemName == station.getItemName() ) {
                if(!m_lstItem[i]->m_isFilled && station.getQuantity()>0){
                    station.updateQuantity();  // this function performs m_qty--
                    m_lstItem[i]->m_isFilled = true;
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]\n";
                    itemFilled = true;
                }
                else if (station.getQuantity() <=0 ){
                    os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]\n";
                }
            }
        }
    }

    void CustomerOrder::display(std::ostream & os) const {
        os << m_name << " - " << m_product << '\n';
        for(auto i=0u; i<m_cntItem; ++i){
            os << '[' << std::setw(6) << std::setfill('0')  << std::right << m_lstItem[i]->m_serialNumber << "] ";
            os << std::setw(m_widthField) << std::setfill(' ') << std::left << m_lstItem[i]->m_itemName << " - ";
            m_lstItem[i]->m_isFilled ? os << "FILLED\n" : os << "TO BE FILLED\n";
        }
    }


}