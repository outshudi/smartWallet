#include "movementlistview.h"

movementListView::movementListView(QWidget *parent): QListWidget (parent){}

unsigned int movementListView::getIndex() const
{
    return uint(indexFromItem(currentItem()).row());
}





