#ifndef CONTAINER_H
#define CONTAINER_H

template<class T>
class Container{
        friend class constIterator;
        friend class Iterator;
private:
    class nodo{
        public:
        T info;
        nodo *prev, *next;
        nodo(const T&, nodo*p=nullptr, nodo*n=nullptr);
        ~nodo();
    };

    nodo *first, *last; //primo e ulimo nodo della lista
    unsigned int count; //contatore numero elementi

    nodo *copia(const nodo*);
    nodo *lastNode(const nodo*);

public:
    //---Container---
    //Costruttore
    Container();
    Container(const Container& c);
    Container &operator=(const Container&);
    unsigned int size() const;
    void pushFront(const T&);
    void pushBack(const T&);
    void popFront();
    void popBack();
    bool Push(const T&);
    bool Remove(const T&);
    bool Remove(unsigned int);
    void toEmpty();
    ~Container();

    //---CONSTITERATOR---
    class constIterator{
        friend class Container;
    private:
        const Container::nodo* punt;
        bool pte;
    public:
        constIterator();
        constIterator(const nodo*,bool=true);
        constIterator& operator++();
        const T& operator*() const;
        const T* operator->() const;
        bool operator==(const constIterator&) const;
        bool operator!=(const constIterator&) const;
        bool isPastToEnd() const;
        ~constIterator() =default;
    };

    //---Iterator---
    class Iterator{
        friend class Container;
    private:
        Container::nodo* punt;
        bool pte;
    public:
        Iterator();
        Iterator(nodo*,bool e);
        Iterator& operator++();
        const T& operator*() const;
        const T* operator->() const;
        bool operator==(const Iterator&) const;
        bool operator!=(const Iterator&) const;
        bool isPastToEnd() const;
        ~Iterator() =default;

    };
    constIterator cbegin() const;
    constIterator cend() const;
    Iterator begin() const;
    Iterator end() const;
    Iterator Search(const T&) const;
    Iterator Search(unsigned int) const;
};

//-------------------------------------IMPLEMENTAZIOONE METODI--------------------------
//---METODI CLASSE NODO---

template<class T>
Container<T>::nodo::nodo(const T& t, nodo *p, nodo *n):info(t), prev(p), next(n){}

template<class T>
Container<T>::nodo::~nodo(){if(next) delete next;}

template<class T>
typename Container<T>::nodo* Container<T>::copia(const nodo* n){
    nodo* tmp=nullptr;
    if(n){
        tmp=new nodo(n->info, nullptr, copia(n->next));
        if(tmp->next)
            tmp->next->prev = tmp;
    }
    return tmp;
}


template<class T>
typename Container<T>::nodo* Container<T>::lastNode(const nodo*){
    nodo* tmp= first;
    if(tmp)
        while(tmp->next)
            tmp = tmp->next;
    return tmp;
}

//---METODI CLASSE CONSTITERATOR---
template<class T>
Container<T>::constIterator::constIterator():punt(nullptr){}

template<class T>
Container<T>::constIterator::constIterator(const nodo* p,bool e):
    punt(p), pte(e)
{}

template<class T>
typename Container<T>::constIterator& Container<T>::constIterator::operator++()
{
    if(punt){
        if(punt->next)
        {
            punt=punt->next;
        } else {
            punt=punt+1;
            pte=true;
        }
    }
    return *this;
}

template<class T>
const T& Container<T>::constIterator::operator*() const
{
    return punt->info;
}

template<class T>
const T* Container<T>::constIterator:: operator->() const
{
    return &(punt->info);
}

template<class T>
bool Container<T>::constIterator::operator==(const constIterator& cit) const
{
    return (pte&&cit.pte)||((!pte&&!cit.pte)&&(punt==cit.punt));
}

template<class T>
bool Container<T>::constIterator::operator!=(const constIterator& cit) const
{
    return !(*this == cit);
}

//---METODI ITERATOR---
template<class T>
Container<T>::Iterator::Iterator():punt(nullptr),pte(false){}

template<class T>
Container<T>::Iterator::Iterator(nodo* p,bool e)
    :punt(p),pte(e)
{}

template<class T>
typename Container<T>::Iterator& Container<T>::Iterator::operator++()
{
    if(punt){
        if(punt->next)
            punt=punt->next;
        else {
            punt+=1;
        }
    }
    return *this;
}

template<class T>
const T& Container<T>::Iterator::operator*() const
{
    return punt->info;
}

template<class T>
const T* Container<T>::Iterator:: operator->() const
{
    return &(punt->info);
}

template<class T>
bool Container<T>::Iterator::operator==(const Iterator& cit) const
{
    return (punt == cit.punt);
}

template<class T>
bool Container<T>::Iterator::operator!=(const Iterator& cit) const
{
    return (punt != cit.punt);
}

//---METODI CONTAINER---
//costruttore
template<class T>
Container<T>::Container():
    first(nullptr),last(nullptr),count(0)
{}

//costruzione di copia
template<class T>
Container<T>::Container(const Container& c)
    :first(copia(c.first)),
      last(lastNode(first)),
      count(c.count)
{}

template<class T>
Container<T> &Container<T>::operator=(const Container & c)
{
    if(first)
        delete first;
    first=copia(c.first);
    last=lastNode(first);
    count=c.count;
    return *this;
}

template<class T>
unsigned int Container<T>::size() const
{
    return count;
}

template<class T>
void Container<T>::pushFront(const T& t)
{
    if(t.isPointing()){
        if(first)
        {
            first->prev= new nodo(t,nullptr,first);
            first= first->prev;
        }
        else
            first = last = new nodo(t, nullptr, nullptr);
        count++;
    }
}

template<class T>
void Container<T>::pushBack(const T& t)
{
    if(t.isPointing()){
        if(last){
            last->next = new nodo(t, last, nullptr);
            last  = last->next;
        }
        else
            first = last = new nodo(t,nullptr,nullptr);
        count++;
    }
}

template<class T>
void Container<T>::popFront()
{
    if(first && count){
        nodo* tmp=first->next;
        if(!tmp)
        {
            first= last= nullptr;
        }else
        {
            first->next = nullptr;
            tmp->prev= nullptr;
            delete first;
            first = tmp;
        }
        count--;
    }
}

template<class T>
void Container<T>::popBack()
{
    if(last && count){
        nodo* tmp = last->prev;
        if(!tmp)
        {
            first= last= nullptr;
        }else {
            last->prev= nullptr;
            tmp->next= nullptr;
            delete last;
            last = tmp;

        }
        count--;
     }
}

template<class T>
typename Container<T>::Iterator Container<T>::Search(const T& t) const
{
    nodo*tmp=first;
    while(tmp && tmp->info != t)
        tmp=tmp->next;
    if(tmp)
        return Iterator(tmp,false);
    return Iterator(nullptr,true);
}

template<class T>
typename Container<T>::Iterator Container<T>::Search(unsigned int i) const
{
    Iterator it = this->begin();
    if(i <= this->size())
    {
        unsigned int k = 0;
        it = this->begin();
        for(; k < i; k++)
            ++it;
    }
    return it;
}

template<class T>
bool Container<T>::Push(const T& t)
{
    if(!first || (*t)<=(*(first->info))){
        this->pushFront(t);
    } else{
        nodo*tmp=first;
        while(tmp->next&&((*t)>=(*(tmp->info)))){
            tmp=tmp->next;
        }

        if((tmp->next)&&((*t)>=(*(tmp->info))))
        {
            tmp->next->prev= new nodo(t,tmp,tmp->next);
            tmp->next= tmp->next->prev;
            count++;
        }else if(tmp->prev && (*t)<=*(tmp->info)){
            tmp->prev->next= new nodo(t,tmp->prev,tmp);
            tmp->prev= tmp->prev->next;
            count++;
        }else
            this->pushBack(t);
    }
    return true;
}

template<class T>
bool Container<T>::Remove(const T& t)
{
    Iterator it = Search(t);
    nodo*aux = it.punt;
    if(aux && (aux == first))
    {
        this->popFront();
        return true;
    } else if (aux && (aux == last)) {
        this->popBack();
        return true;
    } else if(aux){
        nodo* tmp = aux;
        aux = aux->next;
        aux->prev = tmp->prev;
        tmp->prev->next = aux;
        tmp->next = nullptr;
        tmp->prev = nullptr;
        delete tmp;
        count--;
        return true;
    }
    return false;
}

template<class T>
bool Container<T>::Remove(unsigned int i)
{
    Iterator it = Search(i);
    nodo*aux = it.punt;
    if(aux && (aux == first))
    {
        this->popFront();
        return true;
    } else if (aux && (aux == last)) {
        this->popBack();
        return true;
    } else if(aux){
        nodo* tmp = aux;
        aux = aux->next;
        aux->prev = tmp->prev;
        tmp->prev->next = aux;
        tmp->next = nullptr;
        tmp->prev = nullptr;
        delete tmp;
        count--;
        return true;
    }
    return false;
}

template<class T>
void Container<T>::toEmpty()
{
    while(first && count)
        this->popBack();
}

template<class T>
Container<T>::~Container()
{
    if(first) delete first;
}

template<class T>
typename Container<T>::constIterator Container<T>::cbegin() const
{
    if(first){
        return constIterator(first,false);
    }else {
        return constIterator(last+1,true);
    }
}

template<class T>
typename Container<T>::constIterator Container<T>::cend() const
{
    return constIterator(last+1,true);
}

template<class T>
typename Container<T>::Iterator Container<T>::begin() const
{
    if(first){
        return Iterator(first,false);
    }else {
        return Iterator(last+1,true);
    }
}

template<class T>
typename Container<T>::Iterator Container<T>::end() const
{
    return Iterator(last+1);
}

#endif // CONTAINER_H





