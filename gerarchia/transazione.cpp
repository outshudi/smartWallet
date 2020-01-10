#include "transazione.h"

transazione::transazione(double i, string c, QDate da):importo(i),causa(c), data(da){}

transazione::transazione(const transazione& t):importo(t.importo),causa(t.causa), data(t.data){}

double transazione::getImporto() const{return importo;}

string transazione::getCausa() const{return causa;}

QDate transazione::getData() const{return data;}

bool transazione::operator<=(const transazione &t) const
{
    return data <= t.data;
}

bool transazione::operator>=(const transazione &t) const
{
    return data >= t.data;
}

bool transazione::operator==(const transazione& t)const{
    return int(100*importo) == int(100*t.importo) &&
            causa == t.causa &&
            data == t.data;
}

bool transazione::operator!=(const transazione& t)const{
    return int(100*importo) != int(100*t.importo) &&
            causa != t.causa &&
            data != t.data;
}

transazione::operator std::string() const{
    return "Data= "+data.toString().toStdString();
}

