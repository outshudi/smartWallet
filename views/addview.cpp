#include "addview.h"

addview::addview(QWidget *parent) : QDialog (parent)
{

    QVBoxLayout* mainLayout = new QVBoxLayout();
    QHBoxLayout* upBoxLayout = new QHBoxLayout();
    QHBoxLayout* lowBoxLayout = new QHBoxLayout();

    //add left layout
    QVBoxLayout* leftAddLayout = new QVBoxLayout();
    QLabel* labelLeftAddTipo = new QLabel("Tipo",this);
    QLabel* labelLeftAddImporto = new QLabel("Importo",this);
    QLabel* labelLeftAddData = new QLabel("Data",this);
    QLabel* labelLetfAddDesc = new QLabel("Descrizione",this);
    QLabel* labelLeftAddMitt = new QLabel("Mittente",this);
    QLabel* labelLeftAddDest = new QLabel("Destinatario",this);

    //mid add layout
    QHBoxLayout* midAddLayout = new QHBoxLayout();
    checkRicorr = new QCheckBox("Abbonamento");
//    checkRicorr->setEnabled(false);
    checkLeftAddRisp = new QCheckBox("Risparmio",this);
    checkLeftAddRisp->setEnabled(false);
    checkLeftAddFull = new QCheckBox("Full");
    checkLeftAddFull->setEnabled(false);

    //add right layout
    QVBoxLayout* rightAddLayout = new QVBoxLayout();
    comboAddTipo = new QComboBox(this);
    comboAddTipo->addItem("Entrata");
    comboAddTipo->addItem("Uscita");
    comboAddTipo->addItem("Abbonamento");
    comboAddTipo->addItem("Risparmio");

    lineAddRightImpt = new QLineEdit("",this);
    lineAddRightImpt->setValidator(new QDoubleValidator(0.0,99999999.9,2,this));
    addRightData = new QDateEdit(QDate::currentDate(),this);
    addRightData->setCalendarPopup(true);
    lineAddRightDesc = new QLineEdit("",this);
    //
    lineAddRightMitt = new QLineEdit("",this);
    lineAddRightMitt->setEnabled(true);
    lineAddRightDest = new QLineEdit("",this);
    lineAddRightDest->setEnabled(false);

    //bottom layout
    QHBoxLayout* addBottomLayout = new QHBoxLayout();
    QLabel* labelLeftAddDRinn = new QLabel("Data Rinnovo",this);
    addRightDRinn = new QDateEdit(QDate::currentDate(),this);
    addRightDRinn->setCalendarPopup(true);
    addRightDRinn->setEnabled(false);

    //end layout
    QHBoxLayout* addEndLayout = new QHBoxLayout();
    buttonAdd = new QPushButton("Aggiungi");
    QPushButton* buttonCancel = new QPushButton("Annulla");

    setMinimumSize(200,200);

    //setup add Left view
    leftAddLayout->addWidget(labelLeftAddTipo);
    leftAddLayout->addWidget(labelLeftAddImporto);
    leftAddLayout->addWidget(labelLeftAddData);
    leftAddLayout->addWidget(labelLetfAddDesc);
    leftAddLayout->addWidget(labelLeftAddMitt);
    leftAddLayout->addWidget(labelLeftAddDest);

    //setup add right layout
    rightAddLayout->addWidget(comboAddTipo);
    rightAddLayout->addWidget(lineAddRightImpt);
    rightAddLayout->addWidget(addRightData);
    rightAddLayout->addWidget(lineAddRightDesc);
    rightAddLayout->addWidget(lineAddRightMitt);
    rightAddLayout->addWidget(lineAddRightDest);

    //setup mid layout
//    midAddLayout->addWidget(checkRicorr);
    midAddLayout->addWidget(checkLeftAddRisp);
    midAddLayout->addWidget(checkLeftAddFull);

    //setup bottom layout
    addBottomLayout->addWidget(labelLeftAddDRinn);
    addBottomLayout->addWidget(addRightDRinn);
    //
    //setup end layout
    addEndLayout->addWidget(buttonAdd);
    addEndLayout->addWidget(buttonCancel);
    //
    upBoxLayout->addLayout(leftAddLayout);
    upBoxLayout->addLayout(rightAddLayout);
    //
    lowBoxLayout->addLayout(addBottomLayout);
    //mainview
    mainLayout->addLayout(upBoxLayout);
    mainLayout->addLayout(midAddLayout);
    mainLayout->addLayout(lowBoxLayout);
    mainLayout->addLayout(addEndLayout);
    this->setLayout(mainLayout);

    //connect
    connect(buttonCancel, SIGNAL(clicked()), this, SLOT(close()));
    connect(comboAddTipo, SIGNAL(currentIndexChanged(int)), this, SLOT(comboSelection()));
    connect(checkLeftAddRisp, SIGNAL(stateChanged(int)), this, SLOT(enableCheckFull()));
    connect(buttonAdd,SIGNAL(clicked()),this,SLOT(sltGenerateQStringList()));
}

void addview::comboSelection(){

    if (addview::comboAddTipo->currentIndex() == 0) {//entrata
        addview::lineAddRightMitt->setEnabled(true);
        addview::lineAddRightDest->setEnabled(false);
        addview::checkLeftAddRisp->setEnabled(false);
        addview::checkLeftAddRisp->setChecked(false);
        addview::checkLeftAddFull->setEnabled(false);
        addview::checkLeftAddFull->setChecked(false);
        addview::addRightDRinn->setEnabled(false);
    }else if(addview::comboAddTipo->currentIndex() == 1){ //uscita
        addview::lineAddRightDest->setEnabled(true);
        addview::lineAddRightMitt->setEnabled(false);
        addview::checkLeftAddRisp->setEnabled(true);
        addview::checkLeftAddFull->setEnabled(false);
        addview::addRightDRinn->setEnabled(false);
    }else if (addview::comboAddTipo->currentIndex() == 2) {//abbonamento
        addview::lineAddRightDest->setEnabled(true);
        addview::lineAddRightMitt->setEnabled(false);
        addview::checkLeftAddRisp->setEnabled(true);
        addview::checkLeftAddFull->setEnabled(false);
        addview::addRightDRinn->setEnabled(true);
    }else if (addview::comboAddTipo->currentIndex()==3) {
        addview::lineAddRightMitt->setEnabled(false);
        addview::lineAddRightDest->setEnabled(false);
        addview::checkLeftAddRisp->setEnabled(false);
        addview::checkLeftAddRisp->setChecked(false);
        addview::checkLeftAddFull->setEnabled(false);
        addview::checkLeftAddFull->setChecked(false);
        addview::addRightDRinn->setEnabled(false);
    }
}

void addview::enableCheckFull(){
    if(checkLeftAddRisp->checkState())
        checkLeftAddFull->setEnabled(true);
    else
    {
        checkLeftAddFull->setEnabled(false);
        checkLeftAddFull->setChecked(false);
    }
}

void addview::sltGenerateQStringList()
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
            emit addMovement(record,cbState);
            emit Message("Inserimento completato");
            this->close();
        }
    } else if(record[0]=="Uscita"){
        if(checkLeftAddRisp->isChecked()){
            cbState=1;
            if(checkLeftAddFull->isChecked())
                cbState=2;
        }
        emit addMovement(record,cbState);
        emit Message("Inserimento completato");
        this->close();
    }else {
        emit addMovement(record,cbState);
        emit Message("Inserimento completato");
        this->close();
    }
}


void addview::enableDataRinn(){
    if(checkRicorr->isChecked())
        addview::addRightDRinn->setEnabled(true);
    else
        addview::addRightDRinn->setEnabled(false);
}

void addview::GeneratorQStringList()
{
    record.clear();
    QString tipo = comboAddTipo->currentText();
    record.push_back(tipo);
    record.push_back(addRightData->date().toString());
    record.push_back(lineAddRightImpt->text());
    record.push_back(lineAddRightDesc->text());
    record.push_back(lineAddRightMitt->text());
    record.push_back(lineAddRightDest->text());
    record.push_back(addRightDRinn->date().toString());
}

void addview::Clear()
{
    lineAddRightImpt->clear();
    lineAddRightDesc->clear();
    lineAddRightMitt->clear();
    lineAddRightDest->clear();
    addRightData->setDate(QDate::currentDate());
    addRightDRinn->setDate(QDate::currentDate());
    checkRicorr->setChecked(false);
    checkLeftAddRisp->setChecked(false);
    checkLeftAddFull->setChecked(false);
}

