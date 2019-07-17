
/* -------------------------------
 Name: Ryniere dos Santos Silva
 Student number: 138888185
 Email: rdos-santos-silva@mysenca.ca
 Section: SAB
 Date: 07/15/2019
 ----------------------------------
 Assignment: 1
 ---------------------------------------------------------------------*/

#include "Error.h"
#include <cstring>

namespace aid
{

Error::Error(const char *errorMessage)
{
    this->clear();
    this->message(errorMessage);
}

Error::~Error()
{

    delete[] this->m_message;
    this->m_message = nullptr;
}

void Error::clear()
{
    this->m_message = new char[1];
    this->m_message[0] = '\0';
}

bool Error::isClear() const
{
    return strlen(this->m_message) == 0;
}

void Error::message(const char *str)
{
    delete[] this->m_message;
    this->m_message = nullptr;

    if (str != nullptr)
    {
        int size = strlen(str);

        if (size > 0)
        {
            this->m_message = new char[size + 1];
            strncpy(this->m_message, str, size);
            this->m_message[size] = '\0';
        }
        else
        {

            this->m_message = new char[1];
            this->m_message[0] = '\0';
        }
    }
    else
    {
        this->clear();
    }
}

const char *Error::message() const
{
    return this->m_message;
}

} // namespace aid

std::ostream &operator<<(std::ostream &output, const aid::Error &error)
{

    if (!error.isClear())
    {
        output << error.message();
    }

    return output;
}