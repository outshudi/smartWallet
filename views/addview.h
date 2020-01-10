#ifndef ADDVIEW_H
#define ADDVIEW_H

#include <QMainWindow>
#include <QWidget>
#include "qlabel.h"
#include <QDateEdit>
#include <QSpinBox>
#include <QListView>
#include <QComboBox>
#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QLineEdit>
#include <QCheckBox>
#include <QDialog>


class addview: public QDialog
{
    friend class modview;
    Q_OBJECT
protected:
    QStringList record;
    QPushButton *buttonAdd;
    QComboBox* comboAddTipo;
    QLineEdit* lineAddRightMitt, *lineAddRightDest, *lineAddRightImpt, *lineAddRightDesc ;
    QCheckBox *checkRicorr, *checkLeftAddRisp, *checkLeftAddFull;
    QDateEdit *addRightData, *addRightDRinn;
    virtual void GeneratorQStringList();

public:
    explicit addview(QWidget *parent = nullptr);
    virtual void Clear();
    ~addview() = default;

public slots:
    virtual void comboSelection();
    void enableDataRinn();
    void enableCheckFull();
    virtual void sltGenerateQStringList();
signals:
    void addMovement(const QStringList &record, unsigned int checkState);
//    void signCloseAdd();
    void Message(const QString&);
};

#endif // ADDVIEW_H
