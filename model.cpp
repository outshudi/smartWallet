#include "model.h"
#include <QDate>

QStringList Model::MakeTransaction(const deepPtr<transazione> &record) const
{
      QStringList tmp;
      QString tipo, importo, data, desc, mitt, dest, dataR;
      tipo= QString::fromStdString(record->getTipo());
      importo= QString::number(record->getImporto());
      data= record->getData().toString();
      desc= QString::fromStdString(record->getCausa());
      if(tipo=="Entrata"){
          mitt= QString::fromStdString(static_cast<entrata*>(&record)->getMittente());
      }else if(tipo=="Uscita"){
          dest= QString::fromStdString(static_cast<uscita*>(&record)->getDestinatario());
      }else if(tipo=="Abbonamento"){
          dest= QString::fromStdString(static_cast<abbonamento*>(&record)->getDestinatario());
          dataR= (static_cast<abbonamento*>(&record)->getDataRin()).toString();
      }
      tmp<<tipo
        <<importo
       <<data
      <<desc
      <<mitt
      <<dest
      <<dataR;
      return tmp;
}

deepPtr<transazione> Model::recordGenerator(const QStringList &transfert) const
{
    deepPtr<transazione> tmp;
    double import= transfert[2].toDouble();
    QDate data = QDate::fromString(transfert[1]);
    std::string desc= transfert[3].toStdString();
    if(transfert[0]=="Entrata"){
        tmp= new entrata(import,desc,data,transfert[4].toStdString());
    } else if (transfert[0]=="Uscita") {
        tmp= new uscita(import,desc,data,transfert[5].toStdString());
    } else if(transfert[0]=="Abbonamento"){
        QDate r= QDate::fromString(transfert[6]);
        tmp= new abbonamento(import,desc,data,transfert[5].toStdString(),r);
    } else {
        tmp= new risparmio(import, desc, data);
    }
    return tmp;
}

deepPtr<transazione> Model::CalcSaveCent(const deepPtr<transazione> &record) const
{
    if(dynamic_cast<const uscita*>(&record))
    {
        const uscita* aux= static_cast<const uscita*>(&record);
        return deepPtr<transazione>(new risparmio(aux->getRisparmioCent(),record->getCausa(),record->getData()));
    }else {
        return deepPtr<transazione>();
    }
}

deepPtr<transazione> Model::CalcSaveFull(const deepPtr<transazione> &record) const
{
    if(dynamic_cast<const uscita*>(&record))
    {
        const uscita* aux= static_cast<const uscita*>(&record);
        return deepPtr<transazione>(new risparmio(aux->getRisparmioFull(),record->getCausa(),record->getData()));
    }else {
        return deepPtr<transazione>();
    }
}

Model::Model(const QFileInfo &pathToSet, QObject*parent):
    QObject (parent), list(Container<deepPtr<transazione>>()), filePath(pathToSet)
{
}

QStringList Model::GetRecord(const unsigned int index)
{
    if(index<list.size()){
        unsigned int i=0;
        for(auto it= list.cbegin(); it!=list.cend();++it){
            if(i==index)
                return MakeTransaction(*it);
            else {
                i++;
            }
        }
    }
    return QStringList();
}

const QStringList Model::MovementList(const QString tipo,const QDate &start, const QDate &end, QStringList &results) const
{
    QStringList tmp;
    double entries=0.0, exits=0.0, saves=0.0;
    for(auto it= list.cbegin(); it!=list.cend(); ++it){
        if((*it)->getData()>=start)
        {
            if((*it)->getData()<=end)
            {
                if(tipo=="" || (*it)->getTipo()==tipo.toStdString())
                {
                    tmp<<QString::fromStdString(**it);
                    if(dynamic_cast<entrata*>(&(*it)))
                        entries+=(*it)->getImporto();
                    if(dynamic_cast<uscita*>(&(*it)))
                        exits+=(*it)->getImporto();
                    if(dynamic_cast<risparmio*>(&(*it)))
                        saves+=(*it)->getImporto();
                }
            }
        }
    }
    results<<QString::number(entries)
          <<QString::number(exits)
         <<QString::number(saves)
        <<QString::number(entries-exits-saves);
    return tmp;
}

QString Model::GetFilePath() const
{
    return filePath.absoluteFilePath();
}

QString Model::GetFileDir() const
{
    return filePath.absolutePath();
}

void Model::Add(const QStringList &movement,unsigned int checkState)
{
    deepPtr<transazione> tmp=recordGenerator(movement);
    list.Push(tmp);
    if(checkState==1){

        list.Push(CalcSaveCent(tmp));
    }else if(checkState==2){
        list.Push(CalcSaveFull(tmp));
    }
    emit RecordChange();
}

void Model::SetRecord(const unsigned int index, const QStringList &record){
    RemoveRecord(index);
    Add(record,0);//il checkState è settato a 0 perché nella modifica non è necessario generare un risparmio
    emit RecordChange();
}

void Model::RemoveRecord(const unsigned int index)
{
    list.Remove(index);
    emit RecordChange();
}

void Model::EmptyList()
{
    list.toEmpty();
    emit RecordChange();
}

void Model::SaveToFile() const
{
    Serializer::Serialize(list,filePath.absoluteFilePath());
}

void Model::ChangeFilePath(const QString path){
    SaveToFile();
    QFileInfo tmp(path);
    if(!tmp.isReadable() || !tmp.isWritable()){
        if(!tmp.exists()){
            QFile newFile(tmp.absoluteFilePath());
            newFile.open(QFile::WriteOnly);
            newFile.close();
            tmp.setFile(newFile);
        }
    }
    if(!tmp.isReadable() || !tmp.isWritable())
    {
        emit Message("Problemi con la directory");
    }else {
        filePath=tmp;
    }
}

void Model::LoadFromFile()
{
    list=Serializer::Unserialize(filePath);
    emit RecordChange();
}
