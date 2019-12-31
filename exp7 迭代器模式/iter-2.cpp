#include<iostream>
#include<vector>
using namespace std;

class Item{
public:
    int val1;
    double val2;
    Item *next;
};

template<class Item>
class Iterator{
public:
    Iterator() {};
    virtual ~Iterator() {};
    virtual void first() = 0;
    virtual void next() = 0;
    virtual Item *curItem() = 0;
    virtual bool isDone() = 0;
};


template<class Item>
class Aggregate{
public:
    Aggregate() {};
    virtual ~Aggregate() {};
    virtual void pushData(Item item) = 0;
    virtual Iterator<Item>* createIterator() = 0;
    virtual Item& operator[](int index) = 0;
    virtual int getSize() = 0;
}; 


template<class Item>
class ConcreteIterator : public Iterator <Item>{
public:
    ConcreteIterator(Aggregate<Item> *a) :aggr(a), cur(0) {};
    ~ConcreteIterator() {};
    void first(){
        cur = 0;
    }
    void next(){
        if (cur < aggr->getSize())
            cur++;
    }
    Item *curItem(){
        if (cur < aggr->getSize()){
            return &(*aggr)[cur];
        }else{
            return NULL;
        }
    }
    bool isDone(){
        return cur >= aggr->getSize();
    }
private:
    Aggregate<Item> *aggr;
    int cur;
};


template <class Item>
class ConcreteAggregate : public Aggregate<Item>{
public:
    ConcreteAggregate() {};
    ~ConcreteAggregate() {};
    void pushData(Item item){
        data.push_back(item);
    }
    Iterator<Item>* createIterator(){
        return new ConcreteIterator<Item>(this);
    }

    Item& operator[](int index){
        return data[index];
    }

    int getSize(){
        return data.size();
    }
private:
    Item* head;
    vector<Item> data;
};


int main(){
    Aggregate<int> * aggr = new ConcreteAggregate<int>();
    aggr->pushData(3);
    aggr->pushData(2);
    aggr->pushData(1);
    Iterator<int> * it = aggr->createIterator();
    for (it->first(); !it->isDone(); it->next()){
        std::cout << *it->curItem() << std::endl;
    }
    delete it;
    delete aggr;
}
