#ifndef USCITA_H
#define USCITA_H

#include "transazione.h"

class uscita: public transazione{
private:
    string destinatario;
public:
    uscita(double=0.0, string="none", QDate=QDate::currentDate(), string="unknown");
    uscita(const uscita& u);
    string getDestinatario()const;
    virtual bool operator==(const transazione& t)const;
    virtual bool operator!=(const transazione& t)const;
    virtual double getRisparmioCent()const;
    virtual double getRisparmioFull()const;
    virtual operator std::string()const;
    virtual string getTipo()const;
    virtual uscita* clone() const;
};

#endif // USCITA_H
