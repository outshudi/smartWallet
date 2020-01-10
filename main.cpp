#include <QApplication>
#include "controller.h"
//#include "./views/mainwindow.h"

//---PROVA VIEWS---
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Controller w(nullptr);
    return a.exec();
}

//---PROVA CONTAINER---
//int main()
//{
//    Container<int>* c = new Container<int>();
//    c->pushBack(1);
//    c->pushBack(2);
//    c->pushBack(3);
//    c->Remove(2);
//    for(auto it = c->begin(); it != c->end(); ++it)
//        cout<<*it<<" ";
//    Container<deepPtr<transazione>>* d= new Container<deepPtr<transazione>>();
//    auto bit = d->cbegin();
//    auto eit = d->cend();
//    if(bit == eit)
//        cout<<"ok"<<std::endl;
//    cout<<c->size()<<std::endl;
//    cout<<"FINE";
//}
