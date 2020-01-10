#include "abbonamento.h"

abbonamento::abbonamento(double i, string c, QDate d, string de, QDate dr): uscita(i,c,d,de), dRinnovo(dr){}

abbonamento::abbonamento(const abbonamento &a):uscita(a),dRinnovo(a.dRinnovo)
{}

QDate abbonamento::getDataRin()const{return dRinnovo;}

abbonamento* abbonamento::clone() const{return new abbonamento(*this);}

bool abbonamento::operator==(const transazione& t)const{
    return dynamic_cast<const abbonamento*>(&t) &&
        uscita::operator==(t) &&
        dRinnovo == static_cast<const abbonamento&>(t).dRinnovo;
}
bool abbonamento::operator!=(const transazione& t)const{
    return dynamic_cast<const abbonamento*>(&t) &&
		uscita::operator!=(t) &&
            dRinnovo != static_cast<const abbonamento&>(t).dRinnovo;
}

abbonamento::operator std::string() const
{
    return uscita::operator std::string()+
            " | Data Rinnovo= "+
            dRinnovo.toString().toStdString();
}

string abbonamento::getTipo() const
{
    return string("Abbonamento");
}



