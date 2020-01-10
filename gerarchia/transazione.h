#ifndef TRANSAZIONE_H
#define TRANSAZIONE_H

#include <iostream>
#include <string>
#include <QDate>

using std::cout;
using std::endl;
using std::string;


class transazione{

protected:

    double importo;
    string causa;
    QDate data;

public:
    transazione(double =0.0, string="none", QDate=QDate::currentDate());
    transazione(const transazione&);
    double getImporto()const;
    string getCausa()const;
    QDate getData()const;
    virtual bool operator<=(const transazione &t)const;
    virtual bool operator>=(const transazione &t)const;
    virtual bool operator==(const transazione&)const;
    virtual bool operator!=(const transazione&)const;
    virtual operator std::string()const;
    virtual string getTipo()const = 0;
    virtual transazione* clone() const = 0;
    virtual ~transazione()=default;
};


#endif // TRANSAZIONE_H
