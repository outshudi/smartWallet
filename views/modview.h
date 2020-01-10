#ifndef MODVIEW_H
#define MODVIEW_H

#include <QDialog>
#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include <QDateEdit>
#include <QDate>
#include "addview.h"

class modview: public addview
{
    Q_OBJECT
private:
    unsigned int index;
public:
    explicit modview(QWidget *parent = nullptr);
    ~modview() = default;
    void SetFields(const QStringList &oldData, const unsigned int oldDataIndex);
public slots:
    virtual void sltGenerateQStringList();
signals:
    void signModMovement(const unsigned int index,const QStringList& dataToSet,unsigned int chackState);
};

#endif // MODVIEW_H
