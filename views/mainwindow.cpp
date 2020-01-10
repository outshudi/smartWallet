#include "mainwindow.h"
#include <QMessageBox>

mainwindow::mainwindow(QWidget *parent) : QMainWindow(parent)
{
    QWidget *main=new QWidget(this);

    //Layout
    QVBoxLayout* mainLayout = new QVBoxLayout();

    //menu
    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *meFile = new QMenu("File",this);
    menuBar->addMenu(meFile);
    QAction *maOpen = new QAction("Apri",this);
    meFile->addAction(maOpen);
    QAction *maSave = new QAction("Salva",this);
    meFile->addAction(maSave);
    QAction *maSaveAs = new QAction("Salva con nome",this);
    meFile->addAction(maSaveAs);
    QAction *maExit = new QAction("Esci",this);
    meFile->addAction(maExit);

    //image layout
    QHBoxLayout* imageLayout = new QHBoxLayout();
    QPixmap*  pix = new QPixmap(":/logo/logo/swLogo.png");
    QLabel* image = new QLabel(this);
    image->setPixmap(*pix);
    image->setAlignment(Qt::AlignCenter);

    //top Layout
    QHBoxLayout* topLayout = new QHBoxLayout();
    QLabel* labelOperazioni = new QLabel("Operazioni:",this);
    labelOperazioni->setStyleSheet("font: 12pt;");
    QLabel* labelTotali = new QLabel("Totali:",this);
    labelTotali->setStyleSheet("font: 12pt;");


    //research Layout
    QGridLayout* researchLayout = new QGridLayout();

    QLabel* labelRicerca = new QLabel("Ricerca operazioni:",this);
    labelRicerca->setStyleSheet("font: 12pt");
    comboTipo= new QComboBox(this);
    comboTipo->addItem("");
    comboTipo->addItem("Entrata");
    comboTipo->addItem("Uscita");
    comboTipo->addItem("Abbonamento");
    comboTipo->addItem("Risparmio");
    QLabel* labelDataFrom = new QLabel("Da",this);
    QDate today= QDate::currentDate();
    fromData = new QDateEdit(today.addDays(1-today.day()),this);
    fromData->setCalendarPopup(true);
    QLabel *labelDataTo = new QLabel("A",this);
    toData = new QDateEdit(today.addDays(today.daysInMonth()-today.day()),this);
    toData->setCalendarPopup(true);

    //mid layout
    QGridLayout* gridMid = new QGridLayout();

    //mid left layout
    QVBoxLayout* midleftLayout = new QVBoxLayout();

    //widget mid left
    operazioniList = new movementListView(this);

    //mid right layout
    QVBoxLayout* midRightLayout = new QVBoxLayout();

    //mid label tot layout
    QHBoxLayout* EntrateLayout = new QHBoxLayout();
    QHBoxLayout* UsciteLayout = new QHBoxLayout();
    QHBoxLayout* RisparmiLayout = new QHBoxLayout();
    QHBoxLayout* SaldoLayout = new QHBoxLayout();

    QLabel* labelTotEntrate = new QLabel("Entrate:    ",this);
    QLabel* labelTotUscite = new QLabel("Uscite:      ",this);
    QLabel* labelTotRisp = new QLabel("Risparmio:",this);
    QLabel* labelSaldo = new QLabel("Saldo:      ",this);

    //mid line tot
    totEntrate = new QLabel("0.0",this);
    totUscite = new QLabel("0.0",this);
    totRisparmio = new QLabel("0.0",this);
    Saldo = new QLabel("0.0",this);

    //bottom layout
    QHBoxLayout* bottomLayout = new QHBoxLayout();
    //pulsanti bottomLayout
    QPushButton* addButton = new QPushButton("Aggiungi",this);
    QPushButton* modButton = new QPushButton("Modifica",this);
    QPushButton* removeButton = new QPushButton("Rimuovi",this);
    QPushButton* emptyButton = new QPushButton("Svuota",this);

    //------------------------INIZIO SETUP LAYOUT-----------------------------
    //
    //setup image Layout
    imageLayout->addWidget(image);

    //setup gridMid layout
    gridMid->addWidget(labelOperazioni,0,0,1,1);
    gridMid->addWidget(labelTotali,0,1,1,1);
    gridMid->addLayout(midleftLayout,1,0,1,1);
    gridMid->addLayout(midRightLayout,1,1,1,1);


    //setup research layout
    researchLayout->addWidget(labelRicerca,0,0,1,1);
    researchLayout->addWidget(new QLabel("Tipo",this),0,1,1,1);
    researchLayout->addWidget(comboTipo,0,2,1,1);
    researchLayout->addWidget(labelDataFrom,0,3,1,1);
    researchLayout->addWidget(fromData,0,4,1,1);
    researchLayout->addWidget(labelDataTo,0,5,1,1);
    researchLayout->addWidget(toData,0,6,1,1);

    //setup Entrate Layout
    EntrateLayout->addWidget(labelTotEntrate);
    EntrateLayout->addWidget(totEntrate);

    //setup Uscite Layout
    UsciteLayout->addWidget(labelTotUscite);
    UsciteLayout->addWidget(totUscite);


    //setup Risp Layout
    RisparmiLayout->addWidget(labelTotRisp);
    RisparmiLayout->addWidget(totRisparmio);

    //setup Saldo Layout
    SaldoLayout->addWidget(labelSaldo);
    SaldoLayout->addWidget(Saldo);

    //setup midLeftLayout
    midleftLayout->addWidget(operazioniList);
    midleftLayout->addLayout(researchLayout);

    //setup midRightLayout
    midRightLayout->addLayout(EntrateLayout);
    midRightLayout->addLayout(UsciteLayout);
    midRightLayout->addLayout(RisparmiLayout);
    midRightLayout->addLayout(SaldoLayout);

    //setup bottomLayout
    bottomLayout->addWidget(addButton);
    bottomLayout->addWidget(modButton);
    bottomLayout->addWidget(removeButton);
    bottomLayout->addWidget(emptyButton);

    //setup mainLayout
    mainLayout->addWidget(menuBar);
    mainLayout->addLayout(imageLayout);
    mainLayout->addLayout(topLayout);
    //mainLayout->addLayout(midLayout);
    mainLayout->addLayout(gridMid);
    mainLayout->addLayout(bottomLayout);

    //----------------FINE MAINVIEW----------------

    main->setLayout(mainLayout);
    this->setCentralWidget(main);

    operazioniList->setContextMenuPolicy(Qt::CustomContextMenu);
    //------------------------CONNECT-----------------------------------------
    connect(fromData,SIGNAL(dateChanged(const QDate&)),this,SLOT(checkFilterState()));
    connect(toData,SIGNAL(dateChanged(const QDate&)),this,SLOT(checkFilterState()));
    connect(comboTipo,SIGNAL(currentIndexChanged(int)),this,SLOT(checkFilterState()));
    connect(addButton, SIGNAL(clicked()), this, SIGNAL(signOpenAddWindow()));
    connect(modButton, SIGNAL(clicked()), this, SLOT(EditMovement()));
    connect(removeButton, SIGNAL(clicked()), this, SLOT(removeMovement()));
    connect(emptyButton,SIGNAL(clicked()),this,SIGNAL(signEmptyList()));
    connect(maOpen,SIGNAL(triggered()),this,SIGNAL(signOpenFileDialog()));
    connect(maSave, SIGNAL(triggered()), this, SIGNAL(signSaveFile()));
    connect(maSaveAs, SIGNAL(triggered()), this, SIGNAL(signSaveFileAs()));
    connect(maExit, SIGNAL(triggered()), this, SLOT(EventClose()));
}

QDate *mainwindow::GetFilters()
{
    QDate *tmp=new QDate[2];
    tmp[0]=fromData->date();
    tmp[1]=toData->date();
    return tmp;
}

QString mainwindow::GetType() const
{
    return comboTipo->currentText();
}

void mainwindow::EventClose()
{
    emit closed();
    this->close();
}

//slot ausiliario per la modifica di un setting errato delle date dei parametri di ricerca
void mainwindow::checkFilterState()
{
    if(toData->date()<fromData->date())
        toData->setDate(fromData->date());
    QDate* tmp= GetFilters();
    emit signFilterChanged(comboTipo->currentText(),tmp[0],tmp[1]);
}

void mainwindow::EditMovement()
{
    if(!operazioniList->selectedItems().isEmpty())
        emit signOpenModWindow(operazioniList->getIndex());
    else {
        emit Message("Nessun elemento selezionato");
    }
}

//slot per settare i totali
void mainwindow::setResume(const QStringList &param)
{
    totEntrate->setText(param[0]);
    totUscite->setText(param[1]);
    totRisparmio->setText(param[2]);
    Saldo->setText(param[3]);
}

//slot per settare la lista delle transazioni
void mainwindow::setMovementList(const QStringList &param)
{
    operazioniList->clear();
    operazioniList->insertItems(0,param);
}

//settaggio dei valori mostrati dalla view
void mainwindow::SetData(const QStringList &list, const QStringList &tots)
{
    setResume(tots);
    setMovementList(list);
}

//rimozione elemento selezionato
void mainwindow::removeMovement()
{
    if(!operazioniList->selectedItems().isEmpty())
    {
        emit signRemoveMovement(operazioniList->getIndex());
    } else{
        emit Message("Nessun elemento selezionato");
    }
}






