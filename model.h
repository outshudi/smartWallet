#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include "memoria/container.h"
#include "memoria/deepptr.h"
#include "memoria/serializer.h"
#include "gerarchia/abbonamento.h"
#include "gerarchia/entrata.h"
#include "gerarchia/risparmio.h"
#include "gerarchia/uscita.h"


class Model: public QObject
{
    Q_OBJECT
private:
    Container<deepPtr<transazione>> list;
    QFileInfo filePath;
    //per generare un elemento della list view da deeppointer
    QStringList MakeTransaction(const deepPtr<transazione>&record) const;
    //per generare un deeppointer da unrecord della list view
    deepPtr<transazione> recordGenerator(const QStringList& transfert) const;
    //funzione per calcolare il "Risparmio Cent"
    deepPtr<transazione> CalcSaveCent(const deepPtr<transazione>&record) const;
    //funzione per calcolare il "Risparmio Full"
    deepPtr<transazione> CalcSaveFull(const deepPtr<transazione>&record) const;
public:
    Model(const QFileInfo& path, QObject *parent =nullptr);
    ~Model() =default;
    //funzione per estrapolare la QStringList corrispondente al nodo in posizione index
    QStringList GetRecord(const unsigned int index);
    //funzione per ottenere la lista di QStringList dei nodi che soddisfano i parametri
    const QStringList MovementList(const QString tipo,const QDate &start, const QDate &end, QStringList &results) const;
    QString GetFilePath() const;
    QString GetFileDir() const;
public slots:
    //aggiunta nodo alla lista
    void Add(const QStringList &movement,unsigned int checkState);
    //set del record in posizione index
    void SetRecord(const unsigned int index, const QStringList &record);
    //rimozione del nodo in posizione index
    void RemoveRecord(const unsigned int index);
    //Rimozione di tutti i nodi del container
    void EmptyList();
    void SaveToFile() const;
    void ChangeFilePath(const QString path);
    void LoadFromFile();
signals:
    void RecordChange();
    void DateError(QString &message);
    void FileError();
    void Message(const QString &);

};

#endif // MODEL_H
