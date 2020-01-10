#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QDateEdit>
#include <QComboBox>
#include <QLayout>
#include <QPushButton>
#include <QMenuBar>
#include <QAction>
#include <QMessageBox>
#include <QCheckBox>
#include "movementlistview.h"


class mainwindow : public QMainWindow
{
    Q_OBJECT

private:
    QComboBox* comboTipo;
    QDateEdit* fromData, *toData;
    QLineEdit* importoLine;
    QLineEdit *descLine;
    movementListView *operazioniList;
    QLabel *totEntrate;
    QLabel *totUscite;
    QLabel *totRisparmio;
    QLabel *Saldo;

public:
    explicit mainwindow(QWidget *parent = nullptr);
    ~mainwindow() = default;

    QDate *GetFilters();
    QString GetType()const;
    unsigned int getCurrentItemIndex() const;
public slots:
    void checkFilterState();
    void EditMovement();
    void setResume(const QStringList &param);//slot per settare i totali parziali
    void setMovementList(const QStringList &param);//slot per la listview
    void SetData(const QStringList& data,const QStringList& resume);
    void removeMovement();
    void EventClose();

signals:
    void Message(const QString &message);
    void FilterChanged();
    void signDataFilterChange();
    void signOpenAddWindow();
    void signOpenModWindow(unsigned int);
    void signRemoveMovement(unsigned int);
    void signFilterChanged(const QString tipo,const QDate start, const QDate end);
    void signEmptyList();
    void signOpenFileDialog();
    void signSaveFile();
    void signSaveFileAs();
    void closed();
};

#endif // MAINVIEW_H
