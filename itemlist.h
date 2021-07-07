#ifndef ITEMLIST_H
#define ITEMLIST_H
#include "item.h"
#include <iostream>
#include <cassert>
#include "math.h"
#include <chrono>
#include <random>
#include <string>
using namespace std;

template <typename T>
class ItemList
{
private:

    Item<T>* first;
    Item<T>* currentptr;
    Item<T>* last;


public:
    ItemList()
    {
        first = nullptr;
        currentptr = nullptr;
        last = nullptr;
    }
    //Item<T>* get(); // Returns pointer to current Element
    Item<T>* get()// Returns pointer to current Element
    {
       // std::cout  << "Returning current with : " << currentptr->getData() << std::endl;
        return currentptr;
    }

    int size()
    {
        int s = 0;
        Item<T>* p = currentptr;
        reset();
        if(first == nullptr)
        {
            return 0;
        }
        else
        {
            s=1;
        }
        while(adv())
        {
            s++;
        }


        currentptr = p;
        return s;
    }

    Item<T>* getFirst()// Returns pointer to first Element
    {
        return first;
    }

    Item<T>* getLast()// Returns pointer to last Element
    {
        return last;
    }

    //bool empty(); // Checks if list empty (aka: first is noone)
    bool empty()// Checks if list empty (aka: first is noone)
    {
        if(first == nullptr && last == nullptr)
        {
            return true;
        }
        return false;
    }

    //bool end(); // Checks if the current pointer points to the last element
    bool end()// Checks if the current pointer points to the last element
    {
        if(currentptr->getNext() == nullptr || empty())
        {
            return true;
        }
        return false;
    }



    //bool adv(); // Tries to advance the current pointer to next element : True if successful, false if not, i.e. last element has been reached
    bool adv()// Tries to advance the current pointer to next element : True if successful, false if not, i.e. last element has been reached
    {
        //std::cout << "INFO : Trying to advance"<<endl;
        if(currentptr == nullptr) // Check if last element has been reached
        {
            //std::cout << ">> currentptr is nullptr!"<<endl;
            // cant advance
            return false;
        }

        if(currentptr->getNext() == nullptr)
        {
            //std::cout << ">> next element does not exist!"<<endl;
            return false;
        }

        //std::cout << ">> successfully advanced!"<<endl;
        currentptr = currentptr->getNext();
        return true;
    }

    bool back() // Tries to go back one element: Returns false if there is no prev.
    {
        //std::cout << "INFO : Trying to retreat!"<<endl;
        if(currentptr == nullptr)
        {
            //std::cout << ">> currentptr is nullptr!"<<endl;
            return false;
        }

        if(currentptr->getPrev() == nullptr)
        {
            //std::cout << ">> prev element does not exist!"<<endl;
            return false;
        }

        //std::cout << ">> successfully retreated!"<<endl;
        currentptr = currentptr->getPrev();
        //std::cout << ">> Now sitting at element: " << currentptr->getData()<< std::endl;
        return true;

    }
    //bool reset(); // Tries to reset the pointer to the first element : True if successful, false if list empty
    bool reset()// Tries to reset the pointer to the first element : True if successful, false if list empty (current gets set to NULLPTR)
    {
        if(!empty())
        {
            currentptr = first;
            return true;
        }
        return false;

    }

    //void ins(Item<T>* toAdd); // Inserts a new element at the current pointers position
    void ins(Item<T> *toAdd)// Inserts a new element at the current pointers position
    {
        std::cout << "INFO : Trying to insert:"<<endl;
        // is it the first element?
        if(first == nullptr)
        {
            std::cout << ">> Element is first in list! (case1)"<<endl;
            first = toAdd;
            first->setPrev(nullptr);

            first->setPrev(nullptr);
            last = first;

            currentptr = first;
            return;
        }


        Item<T>* currentptrPrev = currentptr->getPrev(); // Get the current pointer's prev and next so it isnt lost
        //Item<T>* currentptrNext = currentptr->getNext();

        if(currentptr == first)
        {
            cout << ">> Inserting to front (case2)"<<endl;

            first = toAdd;
            first->setNext(currentptr);

            currentptr->setPrev(toAdd);
            currentptr = toAdd;
            first->setPrev(nullptr);
            return;
        }

        // if its anywhere in the list:
       currentptrPrev = currentptr->getPrev();
       currentptrPrev->setNext(toAdd);

       toAdd->setPrev(currentptrPrev);
       toAdd->setNext(currentptr);

       currentptr->setPrev(toAdd);
       currentptr = toAdd;




    }

    //void del(); // Deletes the element at the current pointer
    void del()// Deletes the element at the current pointer
    {

        // Case 1: The element is the first and only in the list:
        if(currentptr == first && first->getNext() == nullptr) // just delete the current
        {
            delete currentptr;
            first = nullptr;
            last = nullptr;
            currentptr = nullptr;
            return;
        }

        // Case 2: The element is the first and we have next elements
        if(currentptr == first && first->getNext() != nullptr)
        {
            // keep the deleted in currentptr for now.
            first = currentptr->getNext();
            first->setPrev(nullptr);

            delete currentptr;
            currentptr = first;
            return;
        }

        // Case 3: We delete at the end of the list (and have prev)
        if(currentptr == last && currentptr->getPrev() != nullptr)
        {
            // we keep the to be deleted one in currentptr for now.

            last = currentptr->getPrev();
            last->setNext(nullptr);

            delete currentptr;
            currentptr = last;
            return;
        }

        // Case 4: We delete in middle of the list
        if(currentptr != first && currentptr->getPrev() != nullptr && currentptr->getNext() != nullptr && currentptr != last)
        {
            // lets keep the to be deleted one in currentptr for now

            Item<T>* currPrev = currentptr->getPrev();
            Item<T>* currNext = currentptr->getNext();

            currPrev->setNext(currNext);
            currNext->setPrev(currPrev);

            //assert(currentptr != nullptr);

            delete currentptr;

            currentptr = currNext;
            return;

        }

    }

    //void print(); // Prints the list
    void print()
    {
        if(first == nullptr)
        {
            std::cout << "Is empty." << std::endl;
            return;
        }
        std::cout << "Printing list:" << std::endl;
        first->print(currentptr);
    }

    void printcurr()
    {
        if(currentptr != nullptr)
        {
            currentptr->printme();
        }
    }

    void insnew()
    {
        Item<T>* newElement = new Item<T>;
        T data;
        std::cout << "Data?"<<std::endl;

        std::cin >> data;

        newElement->setData(data);

        ins(newElement);

    }

    void wipeList()
    {
        std::cout << "Wiping list..."<<std::endl;
        if (first != nullptr)
        {
            first->delme();
        }

        first = nullptr;
        last = nullptr;
        currentptr = nullptr;
    }

    void compare()
    {
        if(currentptr > currentptr->getNext())
        {
            cout << "A is bigger than B";
        }
        else
        {
            cout << "b is bigger than a";
        }
    }

    void insSorted(Item<T> *toAdd)// Inserts a new element at the correct position
    {
       if(first == nullptr)
       {
            // list is empty
            first = toAdd;
            currentptr = toAdd;
            last = toAdd;
            return;
       }


       if(*first >= *toAdd) // the toadd is smaller than anything
       {
           Item<T>* t = first;
           first = toAdd;

           toAdd->setPrev(nullptr);
           toAdd->setNext(t);

           t->setPrev(toAdd);
           return;
       }


       Item<T>* iterator = first;

       while(true)
       {
           if(*iterator < *toAdd)
           {
               if(iterator->getNext() == nullptr)
               {
                   iterator->setNext(toAdd);
                   toAdd->setPrev(iterator);
                   return;

               }
               else
               {
                   iterator = iterator->getNext();
               }
           }
           else
           {
               Item<T>* preiterator = iterator->getPrev();

               preiterator->setNext(toAdd);
               toAdd->setNext(iterator);

               toAdd->setPrev(preiterator);
               iterator->setPrev(toAdd);
               return;
           }
       }
    }

    void pushFront(Item<T> *toAdd)
    {
        Item<T>* t = first;
        first = toAdd;
        first->setNext(t);
        t->setPrev(first);
    }

    void push_back(Item<T>* toAdd)
    {
        if(first == nullptr && last == nullptr)
        {
            ins(toAdd);
            return;
        }

        //Item<T>* temp = last;
        last->setNext(toAdd);
        toAdd->setPrev(last);
        toAdd->setNext(nullptr);
        last = toAdd;


    }


    Item<T>* getByPos(int i)
    {
        if(i == 0)
        {
            return first;
        }

        Item<T>* currptr_old = currentptr;
        reset();
        Item<T>* it = first;

        if(i > size())
        {
             return nullptr;
        }
        for(int j = 0; j<i; j++)
        {
            //cout << "Iterating: "<<it->getData()<<endl;
            it = it->getNext();
        }
        currentptr = currptr_old;
        return it;
    }

    Item<T>* byPos(int ind)
    {
        reset();

        Item<T>* it = first;
        for(int i = 1; i<ind; i++)
        {
            it = it->getNext();
        }
        return it;
    }

    void swap(Item<T>* one, Item<T>* two)
    {
        T temp;
        temp = one->getData();
        one->setData(two->getData());
        two->setData(temp);
    }

    int returnPosByItem(Item<T>* searched)
    {
        Item<T>* oldCurrentptr = currentptr;
        reset();


        if(first == searched)// Check for first element
        {
            return 0;
        }

        int i = 0;

        while(adv())
        {
            i++;
            if(searched == currentptr)
            {
                currentptr = oldCurrentptr;
                return i;
            }
        }

        currentptr = oldCurrentptr;
        return -1;
    }

    Item<T>* getParent(int listpos)
    {
        if(listpos > size())
        {
            cout << "List too short // Get parent err."<<endl;
            return nullptr;
        }



        Item<T>* oc = currentptr;
        Item<T>* toRet;

        reset();

        for(int i = 0; i<listpos/2 -1; i++)
        {
            adv();
        }

        toRet = currentptr;
        toRet->printme();
        currentptr = oc;
        return toRet;

    }

    Item<T>* getLeftChild(int listpos)
    {
        return getByPos(listpos*2-1);
    }

    Item<T>* getRightChild(int listpos)
    {
        return getByPos(listpos*2+1-1);
    }

    void quicksort(int left, int right)  //sortiere von a bis b
    {
        Item<T>* pivot;
        int pivotI;

        if(empty() || left==right || right < left)
        {
            return;
        }

        pivotI = Num_random(right,left);
        reset();

        for(int i=0; i!=pivotI; ++i)
        {
            adv();
        }
        pivot = currentptr;

        Item<T>* i = first;
        Item<T>* j = last;

        while(i!= pivot || j!=pivot) // If one reaches pivot, stop
        {
            if(pivot->getData() < i->getData() && j->getData() <= pivot->getData())
            {
                swap(i,j);
                i = i->getNext();
                j = j->getPrev();
            }
            else if(pivot->getData() < i->getData() && pivot->getData() <= j->getData())
            {
                currentptr = pivot;
                Item<T>* temp = new Item<T>;
                temp->setData(i->getData());
                if(adv())
                {

                    ins(temp);
                }else
                {
                    push_back(temp);
                }

                currentptr = i;
                i=i->getNext();

                if(j!=pivot)
                {
                    j = j->getPrev();
                }

                del();
                --pivotI;
                currentptr = pivot;
            }
            else if(i->getData() <= pivot->getData() && j->getData() < pivot->getData())
            {
                currentptr = pivot;

                Item<T>* temp2 = new Item<T>;
                temp2->setData(j->getData());

                ins(temp2);

                ++pivotI;

                if(i!= pivot)
                {
                    i = i->getNext();
                }
                currentptr=j;
                j=j->getPrev();

                del();
                currentptr = pivot;

            }
            else
            {
                if(i!=pivot)
                {
                    i=i->getNext();
                }
                if(j!= pivot)
                {
                    j=j->getPrev();
                }
            }
        }
        quicksort(left,pivotI-1);
        quicksort(pivotI+1,right);

        reset();
        return;
    }

    void heapsort()
    {
        for(int i=size(); 0<=i; --i)  //Baumindex max. i
        {
            //std::cout<<print_tree();

            currentptr=byPos(i);
            //Baum zu Maxheap umwandeln
            for(int j=i; 0<j; --j, back())   //von unten alle Elemente außer Wurzel mit Eltern vergleichen, größere Richtung Wurzel
            {
                if(getParent(j)->getData()<currentptr->getData()) //wenn Elternwert < Kinderwert:
                    swap(getParent(j), currentptr);       //tauschen
            }


            swap(first, byPos(i));
        }
    }

    std::string print_tree()
    {
        std::string display;                //Ausgabe
        Item<T>* current_before=currentptr;    //Element aktuell vorher merken
        int list_size=size();               //Listengröße bzw. Elementenanzahl

        currentptr=first;

        if(currentptr==nullptr)                //wenn Liste leer:
            return "-\nsize: "+std::to_string(size())+"\n";

        int i=0;
        do
        {
            switch(i)
            {
            case 0:
                display+="        -----------"+std::to_string(get()->getData())+"-----------";
                if(1<list_size)
                {
                    display+="\n       /                       \\";
                }
                break;

            case 1:
                display+="\n   ----"+std::to_string(get()->getData())+"----";
                break;

            case 2:
                display+="               ----"+std::to_string(get()->getData())+"----";
                if(3<list_size)
                {
                    display+="\n  /         \\             /         \\";
                }
                break;

            case 3:
                display+="\n -"+std::to_string(get()->getData())+"-";
                break;

            case 4:
                display+="       -"+std::to_string(get()->getData())+"-";
                break;

            case 5:
                display+="           -"+std::to_string(get()->getData())+"-";
                break;

            case 6:
                display+="       -"+std::to_string(get()->getData())+"-";
                if(7<list_size)
                {
                    display+="\n/   \\     /   \\         /   \\     /   \\";
                }
                break;

            case 7:
                display+="\n"+std::to_string(get()->getData());
                break;

            case 8:
                display+="   "+std::to_string(get()->getData());
                break;

            case 9:
                display+="     "+std::to_string(get()->getData());
                break;

            case 10:
                display+="   "+std::to_string(get()->getData());
                break;

            case 11:
                display+="         "+std::to_string(get()->getData());
                break;

            case 12:
                display+="   "+std::to_string(get()->getData());
                break;

            case 13:
                display+="     "+std::to_string(get()->getData());
                break;

            case 14:
                display+="   "+std::to_string(get()->getData());
                break;
            case 15:
                display+="\n"+std::to_string(list_size-15)+" elements are not displayed.";
            default:
                break;
            }
            ++i;
        }while(adv()==true);
        display+="\nsize: "+std::to_string(size())+"\n";

        currentptr=current_before;
        return display;
    }








/// EXTERN

//Variablen
bool RandomGen_initialised=false;
std::default_random_engine Generator;
std::uniform_int_distribution<int> Distribution;


//Funktionen von extern
int Num_random(int Min, int Max) noexcept
{
    if(Max<Min)
        std::swap(Min, Max);

    if(RandomGen_initialised==false)
    {
        unsigned int Seed=std::chrono::system_clock::now().time_since_epoch().count();
        Generator=std::default_random_engine(Seed);
        RandomGen_initialised=true;
    }

    if(std::uniform_int_distribution<int>(Min, Max)!=Distribution)
    {
        Distribution=std::uniform_int_distribution<int>(Min, Max);
    }

    return Distribution(Generator);
}

//Quelle: https://www.cplusplus.com/reference/random/linear_congruential_engine/seed/


};



#endif // ITEMLIST_H
