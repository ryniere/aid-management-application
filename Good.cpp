
/* -------------------------------
 Name: Ryniere dos Santos Silva
 Student number: 138888185
 Email: rdos-santos-silva@myseneca.ca
 Section: SAB
 Date: 07/21/2019
 ----------------------------------
 Assignment: 1
 ---------------------------------------------------------------------*/

#include "Good.h"
#include <iomanip>
#include <iostream>
#include <fstream>

#include <cstring>
#define SEPARATOR '|'
#define COMMA ','

using namespace std;

namespace aid
{

// constructors

Good::Good(char type)
{
    m_type = type;
    setEmptyState();
}

Good::Good(const char *sku, const char *name, const char *unit, int qtyOnHand, bool isTaxable, double priceBeforeTax, int qtyNeeded)
{
    strcpy(m_sku, sku);
    strcpy(m_unit, unit);
    this->name(name);
    m_isTaxable = isTaxable;
    m_price = priceBeforeTax;
    m_quantityOnHand = qtyOnHand;
    m_quantityNeeded = qtyNeeded;
}

Good::Good(const Good &good)
{
    m_name = nullptr;
    *this = good;
}

//protected:

void Good::setGood(const char *sku, const char *name, const char *unit, int qtyOnHand, bool isTaxable, double priceBeforeTax, int qtyNeeded)
{

    strcpy(m_sku, sku);
    strcpy(m_unit, unit);
    this->name(name);
    m_isTaxable = isTaxable;
    m_price = priceBeforeTax;
    m_quantityOnHand = qtyOnHand;
    m_quantityNeeded = qtyNeeded;
}

void Good::setEmptyState()
{
    m_name = nullptr;
    m_sku[0] = '\0';
    m_unit[0] = '\0';
    m_quantityOnHand = 0;
    m_quantityNeeded = 0;
    m_price = 0.0;
    m_isTaxable = true;
    message("");
}

void Good::name(const char *prodName)
{
    
    if (prodName != nullptr && !(strcmp("", prodName) == 0))
    {
        //size_t size = strlen(prodName);
        m_name = new char[strlen(prodName) + 1];
        strcpy(m_name, prodName);
    }
    else
    {
        delete[] this->m_name;
        m_name = nullptr;
    }
}

const char *Good::name() const
{
    return m_name;
}

const char *Good::sku() const
{
    return m_sku;
}
const char *Good::unit() const
{
    return m_unit;
}

bool Good::taxed() const
{
    return m_isTaxable;
}

double Good::itemPrice() const
{
    return m_price;
}

double Good::itemCost() const
{
    return taxed() ? m_price + (m_price * tax_rate) : m_price;
}

void Good::message(const char *message)
{
    m_error.message(message);
}

bool Good::isClear() const
{
    return m_error.isClear();
}

//public:

Good &Good::operator=(const Good &good)
{
    if (this != &good)
    {
        this->m_type = good.m_type;
        setGood(good.m_sku, good.m_name, good.m_unit, good.m_quantityOnHand, good.m_isTaxable, good.m_price, good.m_quantityNeeded);
    }

    return *this;
}

Good::~Good()
{
    delete[] m_name;
}

std::fstream &Good::store(std::fstream &file, bool newLine) const
{
    if (!this->isEmpty() && file.is_open())
    {
        file << m_type << COMMA << this->sku() << COMMA << this->name() << COMMA << this->unit() << COMMA << (this->taxed() ? 1 : 0) << COMMA << fixed << setprecision(2) << this->itemPrice() << COMMA << this->quantity() << COMMA << this->qtyNeeded();
    }
    if (newLine)
    {
        file << endl;
    }

    return file;
}

std::fstream &Good::load(std::fstream &file)
{
    Good good;
    file.getline(good.m_sku, max_sku_length, ',');
    good.m_name = new char[max_name_length + 1];
    file.getline(good.m_name, max_name_length, ',');
    file.getline(good.m_unit, max_unit_length, ',');
    file >> good.m_isTaxable;
    file.ignore();
    file >> good.m_price;
    file.ignore();
    file >> good.m_quantityOnHand;
    file.ignore();
    file >> good.m_quantityNeeded;
    file.ignore();
    
    *this = good;

    return file;
}

std::ostream &Good::write(std::ostream &os, bool linear) const
{
    
    if (isClear()) {
        
        if (!isEmpty()) {
            
            if (linear)
            {
                os << setw(max_sku_length) << setfill(' ') << left << m_sku << SEPARATOR
                << setw(20) << left << name() << SEPARATOR
                << setw(7) << right << fixed << setprecision(2) << itemCost() << SEPARATOR
                << setw(4) << right << m_quantityOnHand << SEPARATOR
                << setw(10) << left << m_unit << SEPARATOR
                << setw(4) << right << m_quantityNeeded << SEPARATOR;
            }
            else
            {
                os << " Sku: " << m_sku << endl
                << " Name (no spaces): " << m_name << endl
                << " Price: " << m_price << endl;
                os << " Price after tax: ";
                if (m_isTaxable)
                {
                    os << itemCost() << endl;
                }
                else
                {
                    os << "N/A" << endl;
                }
                os << " Quantity on Hand: " << m_quantityOnHand << " " << m_unit << endl
                << " Quantity needed: " << m_quantityNeeded;
            }
        }
        
        
    } else {
        os << this->m_error.message();
    }

    

    return os;
}

std::istream &Good::read(std::istream &is)
{
    setEmptyState();
    char sku[max_sku_length + 1];
    char name[max_name_length + 1];
    char unit[max_unit_length + 1];
    int quantity = 0, qtyNeeded = 0;
    double price = 0;
    char isTaxChar;
    bool isTaxable = true;

    cout << " Sku: ";
    is >> sku;

    cout << " Name (no spaces): ";
    is >> name;

    cout << " Unit: ";
    is >> unit;

    cout << " Taxed? (y/n): ";
    is >> isTaxChar;

    if (isTaxChar == 'Y' || isTaxChar == 'y')
    {
        isTaxable = true;
    }
    else if (isTaxChar == 'N' || isTaxChar == 'n')
    {
        isTaxable = false;
    }
    else
    {
        is.setstate(std::ios::failbit);
        m_error.message("Only (Y)es or (N)o are acceptable");
    }

    if (!is.fail())
    {
        cout << " Price: ";
        is >> price;
        if (is.fail())
        {
            m_error.message("Invalid Price Entry");
        }
    }

    if (!is.fail())
    {
        cout << " Quantity on hand: ";
        is >> quantity;
        if (is.fail())
        {
            m_error.message("Invalid Quantity Entry");
        }
    }

    if (!is.fail())
    {
        cout << " Quantity needed: ";
        is >> qtyNeeded;
        if (is.fail())
        {
            m_error.message("Invalid Quantity Needed Entry");
        }
    }

    if (!is.fail())
    {
        setGood(sku, name, unit, quantity, isTaxable, price, qtyNeeded);
    }

    return is;
}

bool Good::operator==(const char *sku) const
{
    return strcmp(this->m_sku, sku) == 0;
}

double Good::total_cost() const
{
    return this->itemCost() * this->m_quantityOnHand;
}

void Good::quantity(int qty)
{
    if (qty > 0)
    {
        this->m_quantityOnHand = qty;
    }
}

bool Good::isEmpty() const
{
    return m_name == nullptr;
}

int Good::qtyNeeded() const
{
    return m_quantityNeeded;
}

int Good::quantity() const
{
    return m_quantityOnHand;
}

bool Good::operator>(const char *sku) const
{
    return strcmp(m_sku, sku) > 0;
}

bool Good::operator>(const iGood &good) const
{
    return strcmp(m_name, good.name()) > 0;
}

int Good::operator+=(int qty)
{
    if (qty > 0)
    {
        m_quantityOnHand += qty;
    }

    return m_quantityOnHand;
}

std::ostream &operator<<(std::ostream &os, const iGood &good)
{
    good.write(os, true);
    return os;
}

std::istream &operator>>(std::istream &is, iGood &good)
{
    good.read(is);
    return is;
}

double operator+=(double &total, const iGood &good)
{
    total += good.total_cost();
    return total;
}

} // namespace aid
