/* -------------------------------
 Name: Ryniere dos Santos Silva
 Student number: 138888185
 Email: rdos-santos-silva@myseneca.ca
 Section: SAB
 Date: 07/21/2019
 ----------------------------------
 Assignment: 1
 ---------------------------------------------------------------------*/

#include "Perishable.h"
#include <iomanip>
#include <cstring>
#define SEPARATOR '|'
#define COMMA ','

using namespace std;

namespace aid
{

// constructors

Perishable::Perishable(char type) : Good(type) {
    this->m_expiryDate.setDate(0, 0, 0);
}

// Public

const Date &Perishable::expiry() const
{
    return m_expiryDate;
}

std::fstream &Perishable::store(std::fstream &file, bool newLine) const
{
    Good::store(file, false);
    if (!this->isEmpty() && file.is_open())
    {
        file << COMMA << this->m_expiryDate;
        if (newLine)
        {
            file << endl;
        }
        file.clear();
        file.close();
    }

    return file;
}

std::fstream &Perishable::load(std::fstream &file)
{

    Good::load(file);
    
    this->m_expiryDate.read(file);
    char c;
    
    file.get(c);
    
    return file;
}

std::ostream &Perishable::write(std::ostream &os, bool linear) const
{
    
    Good::write(os, linear);
    
    if (!isEmpty() && !Good::isClear() )
    {
        if (linear)
        {
            this->m_expiryDate.write(os);
        }
        else
        {
            os << endl << "Expiry date: ";
            this->m_expiryDate.write(os);
        }
    }

    return os;
}

std::istream &Perishable::read(std::istream &is)
{
    
    Good::read(is);
    
    if (!is.fail()) {
        
        Date date;
        cout << "Expiry date (YYYY/MM/DD): ";
        date.read(is);
        
        if (date.bad()) {
            
            switch (date.errCode()) {
                case CIN_FAILED:
                    Good::message("Invalid Date Entry");
                    break;
                case YEAR_ERROR:
                    Good::message("Invalid Year in Date Entry");
                    break;
                case MON_ERROR:
                    Good::message("Invalid Month in Date Entry");
                    break;
                case DAY_ERROR:
                    Good::message("Invalid Day in Date Entry");
                    break;
                case PAST_ERROR:
                    Good::message("Invalid Expiry Date in Date Entry");
                    break;
                default:
                    break;
            }
            is.setstate(std::ios::failbit);
        } else {
            this->m_expiryDate = date;
        }
    }

    return is;
}

iGood *CreateProduct(char tag)
{

    iGood *product = nullptr;
    if (tag == 'n' || tag == 'N')
    {
        product = new Good();
    } else if (tag == 'p' || tag == 'P')
    {
        product = new Perishable();
    }

    return product;
}

} // namespace aid
