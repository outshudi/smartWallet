#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QWidget>
#include "./views/mainwindow.h"
#include "./views/addview.h"
#include "./views/modview.h"
#include <QFileDialog>
#include "model.h"
class Controller : public QWidget{
    Q_OBJECT
private:
    mainwindow *view;
    addview *addWindow;
    modview *modWindow;
    QFileDialog *filePrompt;
    Model *model;
    QFileInfo configFile;
//    unsigned int filterOffset;

    QString file;
public:
   explicit Controller(const QString path="",QWidget *parent=nullptr);
    ~Controller();
public slots:
    void SaveState();
    void RemoveMovement(const unsigned int index);
    void openAddView();
    void openModView(const unsigned int index);
    void OpenSavingFileDialog();
    void RequestList(const QString tipo,const QDate &dateStart,const QDate&dateEnd);
    void ModMovement(const unsigned int index,const QStringList& dataToSet,unsigned int checkSate);
    void ChangeFilePath();
    void UpdateView();
    void Message(const QString&);
    void EmptyList();
signals:
    void mRemoveMovement(unsigned int index);
    void mAddMovement(const QStringList& dataToAdd);
    void Insertion(const QStringList&,unsigned int);
    void SetList(const QStringList& data,const QStringList& resume);
};

#endif // CONTROLLER_H
