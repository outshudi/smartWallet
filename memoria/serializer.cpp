#include "serializer.h"



Container<deepPtr<transazione>> Serializer::Unserialize(const QFileInfo &path)
{
    Container<deepPtr<transazione>> tmp;
    QFile stream(path.absoluteFilePath());
    if(path.exists() && path.isReadable())
    {
        deepPtr<transazione> dpt;
        QXmlStreamReader reader(&stream);
        stream.open(QIODevice::ReadOnly);
        QDate date, datesubs;
        double import;
        string desc, sender, reciver;
        if(reader.readNextStartElement())
        {
            if(reader.name() == "smartWallet")
            {
                QXmlStreamAttributes attr;
                while(reader.readNextStartElement())
                {
                    if(reader.name()=="Transazione"){
                        attr= reader.attributes();
                        date = attr.hasAttribute("data")?QDate::fromString(attr.value("data").toString()):QDate();
                        import = attr.hasAttribute("importo")?attr.value("importo").toDouble():0.0;
                        desc = attr.hasAttribute("descrizione")?attr.value("descrizione").toString().toStdString():"";
                        if(attr.hasAttribute("tipo") && attr.value("tipo").toString()=="Entrata")
                        {
                            sender = attr.hasAttribute("mittente")?attr.value("mittente").toString().toStdString():"";
                            dpt = new entrata(import,desc,date,sender);
                        } else if(attr.hasAttribute("tipo") && attr.value("tipo").toString()=="Uscita"){
                            reciver = attr.hasAttribute("destinatario")?attr.value("destinatario").toString().toStdString():"";
                            dpt = new uscita(import,desc,date,reciver);
                        } else if (attr.hasAttribute("tipo") && attr.value("tipo").toString()=="Abbonamento") {
                            reciver = attr.hasAttribute("destinatario")?attr.value("destinatario").toString().toStdString():"";
                            datesubs = attr.hasAttribute("datarinnovo")?QDate::fromString(attr.value("datarinnovo").toString()):QDate();
                            dpt = new abbonamento(import,desc,date,sender,datesubs);
                        } else if(attr.hasAttribute("tipo") && attr.value("tipo").toString()=="Risparmio"){
                            dpt = new risparmio(import,desc,date);
                        }
                        tmp.pushBack(dpt);

                    }
                    reader.skipCurrentElement();
                }
            }
        }
        stream.close();
    }
    return tmp;
}

bool Serializer::Serialize(const Container<deepPtr<transazione> > list, const QFileInfo &path)
{
    QFile stream(path.absoluteFilePath());
    if(!path.exists())
    {
        QDir().mkpath((path.path()));
    }
    if(!stream.open(QIODevice::WriteOnly))
        return false;
    else{
      deepPtr<transazione> tmp;
      QXmlStreamWriter writer(&stream);
      writer.setAutoFormatting(true);
      writer.writeStartDocument();
      writer.writeComment("Non modificare");
      writer.writeStartElement("smartWallet");
      for(auto it = list.cbegin(); it!=list.cend(); ++it)
      {
          tmp= *it;
          writer.writeStartElement("Transazione");
          QString tipo = QString::fromStdString(tmp->getTipo());
          QString data = (tmp->getData()).toString();
          QString importo = QString::number(tmp->getImporto());
          QString desc = QString::fromStdString(tmp->getCausa());
          writer.writeAttribute("tipo",tipo);
          writer.writeAttribute("data",data);
          writer.writeAttribute("importo",importo);
          writer.writeAttribute("descrizione",desc);
          if(tipo == "Entrata")
          {
              deepPtr<entrata> tmpEntry = dynamic_cast<entrata*>(&tmp);
              QString mitt = QString::fromStdString(tmpEntry->getMittente());
              writer.writeAttribute("mittente",mitt);
          } else if (tipo == "Uscita") {
              deepPtr<uscita> tmpExit = dynamic_cast<uscita*>(&tmp);
              QString dest = QString::fromStdString(tmpExit->getDestinatario());
              writer.writeAttribute("destinatario",dest);
          } else if (tipo == "Abbonamento") {
              deepPtr<abbonamento> tmpSubs = dynamic_cast<abbonamento*>(&tmp);
              QString dest = QString::fromStdString(tmpSubs->getDestinatario());
              QString datar = (tmpSubs->getDataRin()).toString();
              writer.writeAttribute("destinatario",dest);
              writer.writeAttribute("datarinnovo",datar);
         }
         writer.writeEndElement();
      }
      writer.writeEndElement();
      writer.writeEndDocument();
      stream.close();
      return true;
    }
}
