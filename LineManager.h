// Name:  Kai Yu Man
// Seneca Student ID:  162280218
// Seneca email:  kman2@myseneca.ca
// Date of completion: 5 Apr 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef LINEMANAGER_H
#define LINEMANAGER_H

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "Workstation.h"

namespace sdds {

    class LineManager {
        std::vector<Workstation*> m_activeLine{};
        size_t m_cntCustomerOrder{};
        Workstation* m_firstStation{};

    public:
        LineManager(const std::string& file, const std::vector<Workstation*>& stations);
        void reorderStations();
        bool run(std::ostream& os);
        void display(std::ostream& os) const;
    };
}

#endif
