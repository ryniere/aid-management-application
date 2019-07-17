/* -------------------------------
 Name: Ryniere dos Santos Silva
 Student number: 138888185
 Email: rdos-santos-silva@mysenca.ca
 Section: SAB
 Date: 07/15/2019
 ----------------------------------
 Assignment: 1
 ---------------------------------------------------------------------*/



#ifndef NAMESPACE_ERROR_H
#define NAMESPACE_ERROR_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

namespace aid {

    class Error {
        private:
        /* data */
        char *m_message;
        bool isEmpty = false;

        public:
            explicit Error(const char* errorMessage = nullptr);
            ~Error();
            void clear();
            bool isClear() const;
            void message(const char* str);
            const char* message() const;
    };

    

} // namespace aid

std::ostream& operator<<(std::ostream &output, const aid::Error& error);


#endif