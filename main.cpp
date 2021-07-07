#include "item.h"
#include "itemlist.h"
#include <iostream>

using namespace std;


void showMenu()
{
    std::cout << "-------------\nWelcome to list:" << std::endl;
    std::cout << "1: print \n"
                 "2: advance \n"
                 "3: get current \n"
                 "4: del current \n"
                 "5: printme (Debug)\n"
                 "6: retreat \n"
                 "7: getlast (Debug)\n"
                 "8: create new and set value \n"
                 "9: set data \n"
                 "10: exit \n"
                 "11: wipe (Debug)\n"
                 "12: insert new data sorted \n"
                    << std::endl;
}


int getInput()
{
    string input;
    int inputConverted;

    while(true)
    {
        std::cout << "What do you want to do?"<<endl;
        std::cin >> input;


        try
        { // Try to convert stoi
            inputConverted = stoi(input);
            return inputConverted;

        }  catch (invalid_argument)
        { // If not successfull, try again
            std::cout << "Invalid input. Try again."<<endl;
        }
    }

}


ItemList<int>* mergeLists( ItemList<int>& one, ItemList<int>& two )// <--------------------------- Change datatypes here aswell ItemList<int>* mergedList,
{

    ItemList<int>*mergedList = new ItemList<int>;
    int data;
    Item<int>* temp;

    one.reset();
    two.reset();

    bool success1=true;   
    bool success2=true;

    while (success1 == success2)
    {
        if(one.get()->getData() < two.get()->getData())
        {
            temp = new Item<int>;
            data = one.get()->getData();
            temp->setData(data);
            mergedList->push_back(temp);
            success1 = one.adv();
        }
        else
        {
            temp = new Item<int>;
            data = two.get()->getData();
            temp->setData(data);
            mergedList->push_back(temp);
            success2 = two.adv();
        }
    }

    if(success1 == false)
    {
        while(success2)
        {
            temp = new Item<int>;
            data = two.get()->getData();
            temp->setData(data);
            mergedList->push_back(temp);
            success2 = two.adv();
        }
    }

    if(success2 == false)
    {
        while(success1)
        {
            temp = new Item<int>;
            data = one.get()->getData();
            temp->setData(data);
            mergedList->push_back(temp);
            success1 = one.adv();
        }
    }

    return mergedList;

}

void splitList(ItemList<int>& list, ItemList<int>& one, ItemList<int>& two)
{
    list.reset();
    Item<int> * element;
    bool success = true;
    bool owo =true;
    int val = -1;

    while(success)
    {
        if(owo)
        {
            element = new Item<int>;
            val = list.get()->getData();
            element->setData(val);
            one.ins(element);
            owo = !owo;
        }
        else
        {
            element = new Item<int>;
            val = list.get()->getData();
            element->setData(val);
            two.ins(element);
            owo = !owo;
        }
        success = list.adv();
    }

}


void mergeSort(ItemList<int>& list){
    ItemList<int>* listChildEins=new ItemList<int>;
    ItemList<int>* listChildZwei=new ItemList<int>;

    list.reset();
    if(list.get() != list.getLast()){ //für mehr als 1 element
        splitList(list,*listChildEins,*listChildZwei);
        mergeSort(*listChildEins);
        mergeSort(*listChildZwei);

        list = *mergeLists(*listChildEins,*listChildZwei);
    }
}


int main() // merge sort debug main
{
    ItemList<int>* one = new ItemList<int>;

    ItemList<int>* two = new ItemList<int>;

    ItemList<int>* merged = new ItemList<int>;
    // temps
    Item<int>* element;

    // first list
    // quicksort list
    /*element = new Item<int>;
    element->setData(13);
    one->ins(element);

    element = new Item<int>;
    element->setData(12);
    one->ins(element);

    element = new Item<int>;
    element->setData(9999);
    one->ins(element);

    element = new Item<int>;
    element->setData(10);
    one->ins(element);

    element = new Item<int>;
    element->setData(9);
    one->ins(element);

    // mergesort list
   // element = new Item<int>;
   // element->setData(10);
   // one->ins(element);
*/
/*
   element = new Item<int>;
    element->setData(5);
    one->ins(element);

    element = new Item<int>;
    element->setData(1);
    one->ins(element);

    element = new Item<int>;
    element->setData(12);
    one->ins(element);

    element = new Item<int>;
    element->setData(11);
    one->ins(element);

    element = new Item<int>;
    element->setData(7);
    one->ins(element);

    element = new Item<int>;
    element->setData(6);
    one->ins(element);

    element = new Item<int>;
    element->setData(999);
    one->ins(element);


*/
   // merged = mergeLists(*one,*two);
    //merged->print();

  //  mergeSort(*one);

  //  one->print();

    cout<<"E"<<endl;

/*
    splitList(*one,*two,*merged);

    merged->print();
    two->print();*/ // Split list funktioniert

    //merged = mergeLists(*one,*two);
    //merged->print();

//Quicksort test
// one->quicksort(0,one->size()-1);

 // Mergesort test
    //mergeSort(*one);
    //one->print();



/// Heapsort

    int rand;
     for(int i = 0; i<200; i++)
     {
         rand = one->Num_random(1,1000);
         element = new Item<int>;
         element->setData(rand);
         one->ins(element);

         element = new Item<int>;
         element->setData(rand);
         two->ins(element);

     }

   auto _start = std::chrono::system_clock::now();
   one->heapsort();

   auto _end = std::chrono::system_clock::now();

   std::chrono::duration<double> elapsed_seconds = _end-_start;

   std::cout << elapsed_seconds.count() << std::endl;

   one->print();

   //  one->print();

   auto __start = std::chrono::system_clock::now();
   mergeSort(*two);
   auto __end = std::chrono::system_clock::now();
   std::chrono::duration<double> _elapsed_seconds = __end-__start;


   std::cout << "heapsort" << elapsed_seconds.count() << std::endl;
   std::cout <<"mergesort"<< _elapsed_seconds.count() << std::endl;


   cout << "ende."<<endl;
}

/*
 *
 *
 *
*/
/*
int main()
{

    ItemList<char> OWO; // Change to datatype-----------------------------|



    int input = 0;

    bool success = false; // return value from functions
    while(true)
    {
        showMenu();
        input = getInput();

        Item<char>* switchelement; // Change to datatype------------------|
        char data;                  // Here aswell------------------------|
        std::cout << "-----------------"<<std::endl;
        switch(input)
        {
            case 1: // print
            OWO.print();
            break;

            case 2: // advance          
            success = OWO.adv();
            if(!success)
            {
                // Successfull
                std::cout << "Could not advance: Either list is empty or last element is reached."<<std::endl;
            }
            else
            {
                std::cout << "Advanced pointer to next element with value: "<< OWO.get() <<std::endl;
            }
            break;

            case 3: // print
            OWO.get();
            break;

            case 4:  // del curr
            OWO.del();
            break;

            case 5: // printme
            OWO.printcurr();
            break;

            case 6: // printme
            OWO.back();
            break;

            case 7: // printme
            if(OWO.getLast() != nullptr)
            {
                OWO.getLast()->printme();
            }else
            {
                std::cout << "Empty." << std::endl;
            }
            break;

            case 8: // create new and setval
            OWO.insnew();
            break;

            case 9: // set data
            switchelement = OWO.get();


            std::cout << "Data?"<<std::endl;
            std::cin >> data;

            switchelement->setData(data);

            break;

            case 10: // create new and setval
            std::cout << "Exiting...";
            exit(0);
            break;

            case 11: // create new and setval
            OWO.wipeList();
            break;

            case 12: // create new sorted
            switchelement = new Item<char>;

            std::cout << "Data?"<<std::endl;
            std::cin >> data;
            switchelement->setData(data);

            OWO.insSorted(switchelement);

            break;

        default:
            cout << "Invalid input" << endl;
        }

        switchelement = nullptr;

    }
    return 0;
}
*/

