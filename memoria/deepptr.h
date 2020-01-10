#ifndef DEEPPTR_H
#define DEEPPTR_H

template<class T>
class deepPtr{
private:
    T* pointed;
public:
    deepPtr(T* p =nullptr);
    deepPtr(const deepPtr&);
    ~deepPtr();
    deepPtr& operator=(const deepPtr&);
    deepPtr& operator=(const T*);
    T& operator*() const;
    T* operator->() const;
    T* operator&() const;
    operator  bool() const;
    bool isPointing() const;

};

template<class T>
deepPtr<T>::deepPtr(T*p){
    if(p)
        pointed=p->clone();
    else {
        pointed=nullptr;
    }
}

template<class T>
deepPtr<T>::deepPtr(const deepPtr& d)
    :pointed((d.pointed) != nullptr ? (d.pointed)->clone() : nullptr)
{}

template<class T>
deepPtr<T>::~deepPtr(){if(pointed) delete pointed;}

template<class T>
deepPtr<T>& deepPtr<T>::operator=(const deepPtr<T>& d){
    if(pointed != d.pointed){
        if(pointed)
            delete pointed;
        if(d.isPointing())
            pointed = d->clone();
        else
            pointed = nullptr;
    }
    return *this;
}

template<class T>
deepPtr<T>& deepPtr<T>::operator=(const T* t){
    if(pointed != t){
        if(pointed)
            delete pointed;
        if(t)
            pointed = t->clone();
        else {
            pointed = nullptr;
        }
    }
    return *this;
}

template<class T>
T& deepPtr<T>::operator*() const
{
    return *pointed;
}

template<class T>
T* deepPtr<T>::operator->() const
{
    return pointed;
}

template<class T>
T* deepPtr<T>::operator&() const
{
    return pointed;
}

template<class T>
deepPtr<T>::operator bool() const
{
    return pointed != nullptr;
}

template<class T>

bool deepPtr<T>::isPointing() const{
    return pointed;
}

#endif // DEEPPTR_H
