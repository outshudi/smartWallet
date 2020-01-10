#ifndef RICORRENTE_H
#define RICORRENTE_H

#include "uscita.h"

class abbonamento: public uscita{
private:
    QDate dRinnovo;
public:
    abbonamento(double=0.0, string="none", QDate=QDate::currentDate(), string="unknown", QDate=QDate::currentDate());
    abbonamento(const abbonamento&);
    QDate getDataRin()const;
    bool operator==(const transazione& )const;
    bool operator!=(const transazione& )const;
    virtual operator std::string() const;
    virtual string getTipo()const;
    virtual abbonamento* clone() const;
};

#endif // RICORRENTE_H
