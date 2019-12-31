#include <iostream>
using namespace std;

class Node{
private:
    int val1;
    double val2;
    Node *next;
    Node *pre;
public:
    Node(){
        next = NULL;
        pre = NULL;
    };
    Node(int x1, double x2){
        next = NULL;
        pre = NULL;
        val1 = x1;
        val2 = x2;
    }
    void SetNext(Node *n){
        next = n;
    };
    Node *GetNext(){
        return next;
    }
    void SetPre(Node *n){
        pre = n;
    }
    Node *GetPre(){
        return pre;
    }
    int getVal1(){
        return val1;
    }
    double getVal2(){
        return val2;
    }
};

template<class Node>
class Iterator{
public:
    Iterator() {};
    virtual ~Iterator() {};
    virtual Node* first() = 0;
    virtual Node* last() = 0;
    virtual Node* next() = 0;
    virtual Node* pre() = 0;
    virtual Node* nowPos() = 0;
    virtual int len() = 0;
    virtual void SetDirect(bool s) = 0;
};

template<class Node>
class Aggregate{
public:
    Aggregate() {};
    virtual ~Aggregate() {};
    virtual Iterator<Node>* createIterator() = 0;
    virtual Node* GetFirst() = 0;
    virtual Node* GetLast() = 0;
    virtual int GetSum() = 0;
    virtual void Insert(int a, double b) = 0;
    virtual void Init() = 0;
}; 


template<class Node>
class ConcreteIterator : public Iterator<Node>{
public:
    ConcreteIterator(Aggregate<Node> *a) :aggr(a){
        cur = aggr->GetFirst()->GetNext();
    };
    ~ConcreteIterator() {};
    Node* first(){
        Node * p = new Node();
        p = aggr->GetFirst()->GetNext();
        return p;
    }

    Node* last(){
        Node * p = new Node();
        p = aggr->GetLast();
        return p;
    }

    Node* pre(){
        Node * p = cur->GetPre();
        cur = cur->GetPre();
        return p;
    }

    Node* nowPos(){
        return cur;
    }

    Node* next(){
        Node * p =  cur->GetNext();
        cur = cur->GetNext();
        return p;
    }

    void SetDirect(bool s){
        if(s){
            cur = aggr->GetFirst()->GetNext();
        }else{
            cur = aggr->GetLast();
        }
    }

    int len(){
        return aggr->GetSum();
    }

private:
    Aggregate<Node> *aggr;
    Node* cur;
};


template<class Node>
class LinkList : public Aggregate<Node>{
private:
    Node* first;
    Node* last;
    int sum;
public:
    Iterator<Node>* createIterator(){
        return new ConcreteIterator<Node>(this);
    }
    LinkList(){
        first = NULL;
        last = NULL;
        sum = 0;
    }
    Node* GetFirst(){
        return first;
    }
    Node* GetLast(){
        return last;
    }
    int GetSum(){
        return sum;
    }
    void Init(){
        first = new Node();
    }
    void Insert(int a, double b){
        Node *p = first;
        Node *s = new Node(a, b);
        for (int i = 0; i < sum; i++){
            p = p->GetNext();
        }
        s->SetNext(NULL);
        s->SetPre(p);
        p->SetNext(s);
        last = s;
        sum++;
    }
    ~LinkList(){}
};





int main(){
    Aggregate<Node> * aggr = new LinkList<Node>();
    aggr->Init();
    aggr->Insert(1, 2.1);
    aggr->Insert(2, 4.2);
    aggr->Insert(3, 6.3);
    aggr->Insert(4, 8.4);
    aggr->Insert(8, 16.5);
    
    

    Iterator<Node> * it = aggr->createIterator();
    
    cout<<"正序"<<endl;
    it->SetDirect(true);
    while(it->nowPos()!= NULL){
        cout<<it->nowPos()->getVal1()<<"  "<<it->nowPos()->getVal2()<<endl;
        it->next();
    }
    cout<<"倒序"<<endl;
    it->SetDirect(false);
    do{
        cout<<it->nowPos()->getVal1()<<"  "<<it->nowPos()->getVal2()<<endl;
        it->pre();
    }while(it->nowPos()!= it->first()->GetPre());
    return 0;
}


/*
    cout<<"正序"<<endl;
    for(Node *p = it->first(); p != NULL; p = it->next()){
        cout<<p->getVal1()<<"  "<<p->getVal2()<<endl;
    }


    cout<<endl<<"倒序"<<endl;
    for(Node *p = it->last(); p != it->first(); p = it->pre()){
        cout<<p->getVal1()<<"  "<<p->getVal2()<<endl;
    }
    
    Iterator<Node> * it2 = aggr->createIterator();
*/