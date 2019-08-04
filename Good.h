/* -------------------------------
 Name: Ryniere dos Santos Silva
 Student number: 138888185
 Email: rdos-santos-silva@myseneca.ca
 Section: SAB
 Date: 07/21/2019
 ----------------------------------
 Assignment: 1
 ---------------------------------------------------------------------*/



#ifndef NAMESPACE_GOOD_H
#define NAMESPACE_GOOD_H

#include "Error.h"
#include "iGood.h"

namespace aid {

    const int max_sku_length = 7;
    const int max_unit_length = 10;
    const int max_name_length = 75;
    const double tax_rate = 0.13;

    class Good : public iGood {
        private:
        /* data */
        char m_type;
        char m_sku[max_sku_length+1];
        char m_unit[max_unit_length+1];
        char *m_name = nullptr;
        int m_quantityOnHand;
        int m_quantityNeeded;
        double m_price;
        Error m_error;
        bool m_isTaxable;

        protected:
        void name(const char*);
        const char* name() const;
        const char* sku() const;
        const char* unit() const;
        bool taxed() const;
        double itemPrice() const;
        double itemCost() const;
        void message(const char*);
        bool isClear() const;
        void setGood(const char *sku, const char *name, const char *unit, int qtyOnHand, bool isTaxable, double priceBeforeTax, int qtyNeeded);
        void setEmptyState();


        public:
            Good(char type = 'N');
            Good(const char *sku, const char *name, const char *unit, int qtyOnHand = 0, bool isTaxable = true, double priceBeforeTax = 0, int qtyNeeded = 0);
            Good(const Good &good);
            Good& operator=(const Good &good);
            ~Good();
            std::fstream& store(std::fstream& file, bool newLine = true) const;
            std::fstream& load(std::fstream& file);
            std::ostream& write(std::ostream& os, bool linear) const;
            std::istream& read(std::istream& is);
            bool operator==(const char*) const;
            double total_cost() const;
            void quantity(int);
            bool isEmpty() const;
            int qtyNeeded() const;
            int quantity() const;
            bool operator>(const char*) const;
            bool operator>(const iGood&) const;
            int operator+=(int);
    };

    std::ostream& operator<<(std::ostream&, const iGood&);
    std::istream& operator>>(std::istream&, iGood&);
    double operator+=(double&, const iGood&);

} // namespace aid


#endif
