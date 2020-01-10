#include "uscita.h"

uscita::uscita(double i, string c, QDate d, string de): transazione(i,c,d), destinatario(de){}

uscita::uscita(const uscita& u): transazione (u), destinatario(u.destinatario){}

string uscita::getDestinatario() const{return destinatario;}

bool uscita::operator==(const transazione &t) const{
    return dynamic_cast<const uscita*>(&t) &&
            transazione::operator==(t) &&
            destinatario == static_cast<const uscita&>(t).destinatario;
}

bool uscita::operator!=(const transazione &t) const{
    return dynamic_cast<const uscita*>(&t) &&
            transazione::operator!=(t) &&
            destinatario != static_cast<const uscita&>(t).destinatario;
}

double uscita::getRisparmioCent() const{
    int cent = int(100*importo)%100;
    int rest = 100 - cent;
    double aux = double(rest)/100.0;
    return aux;
}

double uscita::getRisparmioFull() const{
    int cent = (int(100*importo))%1000;
    int rest = 1000 - cent;
    return double(rest/100.0);
}

uscita::operator std::string() const
{
    return transazione::operator std::string()+
            " | Uscita= "+
            std::to_string(importo)+
            " | Destinatario= "+
            destinatario+
            " | Causa= "+
            causa;
}

string uscita::getTipo() const
{
    return string("Uscita");
}

uscita* uscita::clone() const{return new uscita(*this);}
