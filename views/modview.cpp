#include "modview.h"

modview::modview(QWidget *parent): addview (parent)
{
    addview::buttonAdd->setText("Modifica");
    setMinimumSize(200,200);
}

void modview::SetFields(const QStringList &record, const unsigned int oldDataIndex)
{

    index= oldDataIndex;
    if(record[0]=="Entrata"){
        comboAddTipo->setCurrentIndex(0);
        addview::lineAddRightMitt->setEnabled(true);
        addview::lineAddRightDest->setEnabled(false);
        addview::checkLeftAddRisp->setEnabled(false);
        addview::checkLeftAddRisp->setChecked(false);
        addview::checkLeftAddFull->setEnabled(false);
        addview::checkLeftAddFull->setChecked(false);
        addview::addRightDRinn->setEnabled(false);
    }else if (record[0]=="Uscita") {
        comboAddTipo->setCurrentIndex(1);
        addview::lineAddRightDest->setEnabled(true);
        addview::lineAddRightMitt->setEnabled(false);
        addview::checkLeftAddRisp->setEnabled(true);
        addview::checkLeftAddFull->setEnabled(false);
        addview::addRightDRinn->setEnabled(false);
    }else if(record[0]=="Abbonamento"){
        comboAddTipo->setCurrentIndex(2);
        addview::lineAddRightDest->setEnabled(true);
        addview::lineAddRightMitt->setEnabled(false);
        addview::checkLeftAddRisp->setEnabled(true);
        addview::checkLeftAddFull->setEnabled(false);
        addview::addRightDRinn->setEnabled(true);
    }else if (record[0]=="Risparmio") {
        comboAddTipo->setCurrentIndex(3);
        addview::lineAddRightMitt->setEnabled(false);
        addview::lineAddRightDest->setEnabled(false);
        addview::checkLeftAddRisp->setEnabled(false);
        addview::checkLeftAddRisp->setChecked(false);
        addview::checkLeftAddFull->setEnabled(false);
        addview::checkLeftAddFull->setChecked(false);
        addview::addRightDRinn->setEnabled(false);
    }
    lineAddRightImpt->setText(record[1]);
    addRightData->setDate(QDate::fromString(record[2]));
    lineAddRightDesc->setText(record[3]);
    lineAddRightMitt->setText(record[4]);
    lineAddRightDest->setText(record[5]);
    addRightDRinn->setDate(QDate::fromString(record[6]));
}

void modview::sltGenerateQStringList()
{

    GeneratorQStringList();
    unsigned int cbState=0;//0 nessuno è check, 1 è risp, 2 è full
    if(record[0]=="Abbonamento"){
        if(QDate::fromString(record[1])>QDate::fromString(record[6])){
            emit Message("Dati non corretti");
        }else {
            if(checkLeftAddRisp->isChecked()){
                cbState=1;
                if(checkLeftAddFull->isChecked())
                    cbState=2;
            }
            emit signModMovement(index,record,cbState);
            emit Message("Modifica completata");
            this->close();
        }
    } else if(record[0]=="Uscita"){
        if(checkLeftAddRisp->isChecked()){
            cbState=1;
            if(checkLeftAddFull->isChecked())
                cbState=2;
        }
        emit signModMovement(index,record,cbState);
        emit Message("Modifica completata");
        this->close();
    }else {
        emit signModMovement(index,record,cbState);
        emit Message("Modifica completata");
        this->close();
    }

}


