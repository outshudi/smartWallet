#ifndef MOVEMENTLISTVIEW_H
#define MOVEMENTLISTVIEW_H

#include <QListWidget>
#include <QListWidgetItem>


class movementListView: public QListWidget
{
    Q_OBJECT
public:
    movementListView(QWidget *parent =nullptr);
    ~movementListView() override =default;
    unsigned int getIndex() const;
};

#endif // MOVEMENTLISTVIEW_H
