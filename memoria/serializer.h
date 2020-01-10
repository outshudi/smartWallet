#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <QString>
//#include <QMap>
#include <QDir>
#include <QStringList>
#include <QDate>
#include <QXmlStreamReader>
#include "./memoria/container.h"
#include "./memoria/deepptr.h"
#include "./gerarchia/entrata.h"
#include "./gerarchia/uscita.h"
#include "./gerarchia/abbonamento.h"
#include "./gerarchia/risparmio.h"


class Serializer: QObject
{
    Q_OBJECT
public:
    static Container<deepPtr<transazione>> Unserialize(const QFileInfo &paht);
    static bool Serialize(const Container<deepPtr<transazione>>, const QFileInfo &path);
//    static bool CreatePath(const QDir directory);
};

#endif // SERIALIZER_H
