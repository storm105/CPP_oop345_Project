// Name:  Kai Yu Man
// Seneca Student ID:  162280218
// Seneca email:  kman2@myseneca.ca
// Date of completion: 5 Apr 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "LineManager.h"

namespace sdds {

    LineManager::LineManager(const std::string & file, const std::vector<Workstation*> & stations) {
        std::ifstream fp(file);
        if(!fp){
            throw std::string("LineManager constructor cannot open the file.");
        }

        std::string oneLine{};
        Utilities tempUti{};
        size_t tempPos{0u};
        bool tempMore{false};

        // Task 1: load the content (stations) from txt and place into m_activeLine vector
        // self note: while(getline...) can AVOID using EOF, which usually causes error due to last record being invalid.
        while(getline(fp, oneLine)) {
            std::string wsItem{};
            std::string nextWsItem{};

            wsItem = tempUti.extractToken(oneLine, tempPos, tempMore);

            if (tempMore) {
                nextWsItem = tempUti.extractToken(oneLine, tempPos, tempMore);
            }

            for_each(stations.begin(), stations.end(), [=](Workstation * x){
                if (x->getItemName() == wsItem){
                    for_each(stations.begin(), stations.end(), [=](Workstation * y){
                        if(y->getItemName() == nextWsItem) {
                            x->setNextStation(y);
                        }
                    });
                    m_activeLine.push_back(x);
                }
            });

//            std::cout << " DEBUG wsItem =" << wsItem << "  nextWsItem =" << nextWsItem << '\n';
            wsItem.clear();
            nextWsItem.clear();
            tempPos = 0u;
        }

        // Task 2: locate and set m_firstStation
        // lamdba is to search if activeWs (from m_activeLine) is NOT being "next station" in stations vector
        for_each(m_activeLine.begin(), m_activeLine.end(), [=](Workstation* activeWs) {
            // none_of, true MEANS this activeWs is NOT a next station at all, so activeWs must be the FIRST station
            if( none_of(stations.begin(), stations.end(), [=](Workstation* ws){return ws->getNextStation() == activeWs;}))
                m_firstStation = activeWs;
        });

        // Task 3: set m_cntCustomerOrder
        m_cntCustomerOrder = g_pending.size();

    }

    void LineManager::reorderStations() {   // sort
        std::vector<Workstation*> tempLine{};

        Workstation * thisStation = m_firstStation;
        tempLine.push_back(thisStation);

        while(thisStation->getNextStation()) {
            thisStation = thisStation->getNextStation();
            tempLine.push_back(thisStation);
        }

        m_activeLine = tempLine;
    }

    bool LineManager::run(std::ostream & os) {
        // keeps track of the current iteration number:
        static unsigned int counter = 1;
        os << "Line Manager Iteration: " << counter++ << '\n';

        if(!g_pending.empty()){
            // moves the order at the front of the g_pending queue to the m_firstStation
            *m_firstStation += std::move(g_pending.front());
            // remove front order from g_pending queue
            g_pending.pop_front();
        }

        // for each station on the line:
        // a. executes one fill operation
        for(auto& i : m_activeLine)
            i->fill(os);

        // b. attempts to move an order down the line
        for(auto& i : m_activeLine)
            i->attemptToMoveOrder();

        return (m_cntCustomerOrder == g_completed.size() + g_incomplete.size());
    }

    void LineManager::display(std::ostream & os) const {
         for(auto& i : m_activeLine)
            i->display(os);
    }

}