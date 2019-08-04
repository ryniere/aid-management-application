/* -------------------------------
 Name: Ryniere dos Santos Silva
 Student number: 138888185
 Email: rdos-santos-silva@myseneca.ca
 Section: SAB
 Date: 08/03/2019
 ----------------------------------
 Assignment: 1
 ---------------------------------------------------------------------*/



#ifndef NAMESPACE_PERISHABLE_H
#define NAMESPACE_PERISHABLE_H

#include "Good.h"
#include "Date.h"

namespace aid {
    
    
    class Perishable : public Good {
    private:
        /* data */
        Date m_expiryDate;
        
    protected:
        
        
    public:
        Perishable(char type = 'P');
        std::fstream& store(std::fstream& file, bool newLine = true) const;
        std::fstream& load(std::fstream& file);
        std::ostream& write(std::ostream& os, bool linear) const;
        std::istream& read(std::istream& is);
        const Date& expiry() const;
    };
    
    std::ostream& operator<<(std::ostream&, const iGood&);
    std::istream& operator>>(std::istream&, iGood&);
    double operator+=(double&, const iGood&);
    
} // namespace aid


#endif
