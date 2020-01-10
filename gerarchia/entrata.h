#ifndef ENTRATA_H
#define ENTRATA_H

#include <iostream>
#include "transazione.h"
using std::string;

class entrata: public transazione{
private:
    string mittente;
public:
    entrata(double=0.0, string="none", QDate=QDate::currentDate(), string="unknown");
    entrata(const entrata&);
    string getMittente()const;
    virtual bool operator==(const transazione&)const;
    virtual bool operator!=(const transazione&)const;
    virtual operator std::string()const;
    virtual string getTipo()const;
    virtual entrata* clone() const;
};

#endif // ENTRATA_H
