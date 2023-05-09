// Name:  Kai Yu Man
// Seneca Student ID:  162280218
// Seneca email:  kman2@myseneca.ca
// Date of completion:  10 Mar 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Utilities.h"

namespace sdds {

    char Utilities::m_delimiter{};  // static (class) variable initialization

    void Utilities::setFieldWidth(size_t newWidth) {
        m_widthField = newWidth;
    }

    size_t Utilities::getFieldWidth() const {
        return m_widthField;
    }

    std::string Utilities::extractToken(const std::string & str, size_t & next_pos, bool & more) {
        std::string tempStr{};
        std::stringstream ss(str);

        ss.seekg(next_pos);
        getline(ss, tempStr, m_delimiter);

        if(tempStr.empty()){    // case1: empty because str == delimiter!
            more = false;
            throw "delimiter is found at next_pos";   //
        }
        else if(ss.tellg() == -1) {   // case2: -1 means has reached to the end of str!
            more = false;
        }
        else {     // case3: "should be" not end of str yet! extract again!
            next_pos = ss.tellg();
            more = true;   // true means extract again
        }

        if(m_widthField < tempStr.length())
            m_widthField = tempStr.length();

        tempStr = trim(tempStr);

        return tempStr;
    }

    void Utilities::setDelimiter(char newDelimiter) {
        m_delimiter = newDelimiter;
    }

    char Utilities::getDelimiter() {
        return m_delimiter;
    }

    // self-defined:  string trim function:
    std::string trim(const std::string & strInput) {
        unsigned int n1{}, n2{};
        n1 = strInput.find_first_not_of(" ");
        n2 = strInput.find_last_not_of(" ");
        return strInput.substr(n1, n2-n1+1);
    }

}