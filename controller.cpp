#include "controller.h"
#include <QMessageBox>
#include <QSettings>
Controller::Controller(const QString path, QWidget *parent)
    : QWidget(parent),
      view(new mainwindow(this)),
      addWindow(new addview(view)),
      modWindow(new modview(view)),
      filePrompt(new QFileDialog(view)),
      configFile("./data/config.ini")
{
    QSettings initSettings(configFile.absoluteFilePath(),QSettings::NativeFormat);
    QString tmp=path!=""?path:initSettings.value("filePath").toString();
    model=new Model(tmp!=""?QFileInfo(tmp):QFileInfo("./data/saving.sw"),this);
    //connect
    //connect(this,SIGNAL(Message(const QString&)),view,SLOT(Message(const QString&)));
    //connect(this,SIGNAL(UpdateView()),view,SLOT(GetFilters()));
    connect(this,SIGNAL(SetList(const QStringList&,const QStringList&)),view,SLOT(SetData(const QStringList&,const QStringList&)));
    connect(this,SIGNAL(Insertion(const QStringList&,unsigned int)),model,SLOT(Add(const QStringList&,unsigned int)));

    connect(view,SIGNAL(signFilterChanged(const QString,const QDate,const QDate)),this,SLOT(RequestList(const QString,const QDate&,const QDate&)));//     <==
    connect(view,SIGNAL(signRemoveMovement(unsigned int)),this,SLOT(RemoveMovement(const unsigned int)));
    connect(view,SIGNAL(closed()),this,SLOT(SaveState()));
    connect(view,SIGNAL(signOpenAddWindow()),this,SLOT(openAddView()));
    connect(view,SIGNAL(signOpenModWindow(unsigned int)),this,SLOT(openModView(unsigned int)));
    connect(view,SIGNAL(signSaveFile()),this,SLOT(SaveState()));
    connect(view,SIGNAL(signSaveFileAs()),this,SLOT(OpenSavingFileDialog()));
    connect(view,SIGNAL(signOpenFileDialog()),this,SLOT(ChangeFilePath()));
    connect(view,SIGNAL(Message(const QString&)),this,SLOT(Message(const QString&)));
    connect(view,SIGNAL(signEmptyList()),this,SLOT(EmptyList()));

    connect(addWindow,SIGNAL(Message(const QString&)),view,SIGNAL(Message(const QString&)));
    connect(addWindow,SIGNAL(addMovement(const QStringList &,unsigned int)),model,SLOT(Add(const QStringList &,unsigned int)));

    connect(modWindow,SIGNAL(signModMovement(const unsigned int,const QStringList&,unsigned int)),this,SLOT(ModMovement(const unsigned int,const QStringList&,unsigned int)));
    connect(modWindow,SIGNAL(Message(const QString&)),view,SIGNAL(Message(const QString&)));

    connect(model,SIGNAL(RecordChange()),this,SLOT(UpdateView()));
    connect(model,SIGNAL(Message(const QString&)),this,SLOT(Message(const QString&)));
    model->LoadFromFile();
    view->show();
}

Controller::~Controller(){}

void Controller::SaveState(){
    model->SaveToFile();
    QSettings nStart("./data/config.ini",QSettings::NativeFormat);
    nStart.setValue("filePath",model->GetFilePath());
}


void Controller::RemoveMovement(const unsigned int index)
{
    model->RemoveRecord(index);
}

void Controller::ModMovement(const unsigned int index, const QStringList &dataToSet,unsigned int checkState)
{
    model->RemoveRecord(index);
    emit Insertion(dataToSet,checkState);
}

void Controller::EmptyList()
{
    model->EmptyList();
}

void Controller::openAddView()
{
    addWindow->Clear();
    addWindow->setModal(true);
    addWindow->show();
}

void Controller::openModView(unsigned int index)
{
    QStringList oldData= model->GetRecord(index);
    modWindow->SetFields(oldData,index);
    modWindow->setModal(true);
    modWindow->show();
}

void Controller::OpenSavingFileDialog()
{
    QString path= QFileDialog::getSaveFileName(view,"Salva con nome",model->GetFileDir(),"SmartWallet file (*.sw)");
    if(path!="")
    {
        if(!path.endsWith(".sw"))
            path.append((".sw"));
        model->ChangeFilePath(path);
        model->SaveToFile();
    }
}

void Controller::RequestList(const QString tipo,const QDate &dateStart, const QDate &dateEnd)
{
    QStringList resume;
    QStringList mvntList= model->MovementList(tipo,dateStart,dateEnd,resume);
    emit SetList(mvntList,resume);
}



void Controller::ChangeFilePath()
{
    QString p= QFileDialog::getOpenFileName(view,"Apri file",QFileInfo(model->GetFilePath()).dir().dirName(),"smartWallet file (*.sw)");
    if(p!="")
    {
        model->ChangeFilePath(p);
        model->LoadFromFile();
    }
}

void Controller::UpdateView()
{
    QDate *filters=view->GetFilters();
    QString tipo= view->GetType();
    QStringList resume;
    const QStringList filteredRecords=model->MovementList(tipo,filters[0],filters[1],resume);
    emit SetList(filteredRecords,resume);
}

void Controller::Message(const QString &message)
{
    QMessageBox *mb = new QMessageBox(view);
    mb->setText(message);
    mb->show();
}

