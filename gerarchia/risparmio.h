#ifndef RISPARMIO_H
#define RISPARMIO_H

#include "uscita.h"

class risparmio: public transazione{

public:
    risparmio(double, string, QDate);
    risparmio(const risparmio&);
    virtual bool operator==(const transazione&)const;
    virtual bool operator!=(const transazione&)const;
    virtual operator std::string()const;
    void updateImporto(double);
    void updateCausa(string);
    virtual string getTipo()const;
    virtual risparmio* clone() const;

};

#endif // RISPARMIO_H
