// Name:  Kai Yu Man
// Seneca Student ID:  162280218
// Seneca email:  kman2@myseneca.ca
// Date of completion:  10 Mar 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <sstream>

namespace sdds {

    class Utilities{
        size_t m_widthField = 1;
        static char m_delimiter;

    public:
        Utilities() = default;
        void setFieldWidth(size_t newWidth);
        size_t getFieldWidth() const;
        std::string extractToken(const std::string& str, size_t& next_pos, bool& more);

        static void setDelimiter(char newDelimiter);
        static char getDelimiter();
    };

    std::string trim(const std::string& strInput); // self-defined:  string trim function
}

#endif