#include "risparmio.h"

risparmio::risparmio(double i, string de, QDate da):transazione (i, de, da){}

risparmio::risparmio(const risparmio &r):transazione (r)
{}

bool risparmio::operator==(const transazione& t)const{
    return  dynamic_cast<const risparmio*>(&t) &&
            transazione::operator==(t);

}

bool risparmio::operator!=(const transazione & t) const{
    return dynamic_cast<const risparmio*>(&t) &&
            transazione::operator==(t);
}

risparmio::operator std::string() const
{
    return transazione::operator std::string()+
            " | Risparmio= "+
            std::to_string(importo)+
            " | Causa= "+
            causa;
}

void risparmio::updateImporto(double x){importo += x;}

void risparmio::updateCausa(string x){causa = x;}

string risparmio::getTipo() const
{
    return string("Risparmio");
}

risparmio* risparmio::clone() const{return new risparmio(*this);}
