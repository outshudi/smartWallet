#include "entrata.h"

entrata::entrata(double i, string c, QDate d, string m): transazione(i,c,d), mittente(m){}

entrata::entrata(const entrata &e):transazione (e),mittente(e.mittente)
{}

entrata* entrata::clone() const{return new entrata(*this);}

string entrata::getMittente()const{return mittente;}

bool entrata::operator==(const transazione &t)const{
    return dynamic_cast<const entrata*>(&t)
           && transazione::operator==(t)
           && mittente== static_cast<const entrata&>(t).mittente;
}

bool entrata::operator!=(const transazione &t)const{
    return dynamic_cast<const entrata*>(&t)
           && transazione::operator!=(t)
            && mittente!= static_cast<const entrata&>(t).mittente;
}

entrata::operator std::string() const
{
    return transazione::operator std::string()+
            " | Entrata= "+
            std::to_string(importo)+
            " | Mittente= "+
            mittente+
            " | Causa= "+
            causa;
}

string entrata::getTipo() const
{
    return string("Entrata");
}

