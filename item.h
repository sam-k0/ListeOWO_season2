#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <iostream>
using namespace std;
template <typename T>

class Item
{
private:

    T data;
    Item<T>* next;
    Item<T>* prev;

public:
    /*Item();
    Item(T passedData, Item<T>* passedNext, Item<T>* passedPrev);*/

    Item()
    {
        next = nullptr;
        prev = nullptr;
    }

    Item( Item<T>* old)
    {
        next = old->getNext();
        prev = old->getPrev();
        data = old->getData();
    }


// Getter setter

    T getData()
    {
        return data;
    }


    void setData(T value)
    {
        data = value;
    }


    Item<T>* getNext()
    {
        return next;
    }

    //void setNext(Item<T>* item);

    void setNext(Item *item)
    {
        next = item;
    }


    Item<T>* getPrev()
    {
        return prev;
    }


    void setPrev(Item<T>* item)
    {
        prev = item;
    }

    void print(Item<T>* currptr)
    {

        std::cout << "Value: " << data;
        if(currptr == this)
        {
            std::cout << " <";
        }
        std::cout << std::endl;


        if(next != nullptr) // recursive calling
        {
            next->print(currptr);
        }
    }

    void printme()
    {
        cout<<"has data:: " <<data<<endl;

        if(prev != nullptr)
        {
            //cout << "has prev: "<< prev->getData() << endl;
        }
        if (next != nullptr)
        {
            //cout << "has next" << next->getData() << endl;
        }


    }

    bool isLast()
    {
        if(next == nullptr)
        {
            return true;
        }
        return false;
    }

    void delme()
    {
        if(next != nullptr)
        {
            next->delme();
        }
        delete this;
    }



};
// Operatoren
template<typename T>
bool operator==(Item<T> a, Item<T> b)
{
    return a.getData()==b.getData();
}

template<typename T>
bool operator<(Item<T> a, Item<T> b)
{
    return a.getData()<b.getData();
}

template<typename T>
bool operator>(Item<T> a, Item<T> b)
{
    return a.getData()>b.getData();
}

template<typename T>
bool operator<=(Item<T> a, Item<T> b)
{
    return a.getData()<=b.getData();
}

template<typename T>
bool operator>=(Item<T> a, Item<T> b)
{
    return a.getData()>=b.getData();
}

#endif // ITEM_H
