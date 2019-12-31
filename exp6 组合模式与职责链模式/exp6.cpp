#include<iostream>
#include<list>
#include <typeinfo>

using namespace std;

class Component{
public:
    Component(string name){
        this->name = name;
    }
    virtual void Add(Component* c) = 0;
    virtual void Remove(Component* c) = 0;
    virtual void Display(int depth) = 0;
    void SetSuccessor(Component* s){
        this->successor = s;
    }
    void SetBound(int low, int high){
        this->low = low;
        this->high = high;
    }
    virtual void HandleReauest(int request) = 0;
protected:
    string name;
    int low, high;
    Component* successor;
};

class Subcom : public Component{
public:
    Subcom(string name) : Component(name){}
    void Add(Component* c){
        cout<<"Cannot add to a leaf";
    }
    void Remove(Component* c){
        cout<<"Cannot remove from a leaf";
    }
    void Display(int depth){
        for(int i = 0; i <= depth; i++)
            cout<<"--";
        cout<<name<<endl;
    }
    void HandleReauest(int request){
        
    }
};

class ConcreteCompany: public Component{
private:
    list<Component*> children;
public:
    ConcreteCompany(string name): Component(name){}
    void Add(Component *c){
        children.push_back(c);
    }
    void Remove(Component *c){
        children.remove(c);
    }
    void Display(int depth){
        for(int i = 0; i <= depth; i++)
            cout<<"--";
        cout<<name<<endl;
        for(Component* child : children){
            child->Display(depth + 1);
        }
    }
    void HandleReauest(int request){
        if(request >= low && request <= high){
            cout<<this->name<<"处理请求: "<<request<<endl;
        }else if(successor != NULL){
            cout<<this->name<<"处理失败"<<endl;
            successor->HandleReauest(request);
        }else{
            cout<<this->name<<"加薪拒绝"<<request<<endl;
        }
    }
};

/* 
即总公司下设上海华东分公司，华东分公司下设南京办事处和杭州办事处。其中，各级分公司均设有人力资源部和财务部。

用组合模式构建好该结构后，利用职责链模式处理各地员工加薪请求。

例如，一南京员工提出加薪请求，如果加薪不超过1000元，南京办事处即可批准；如果超过1000元，则上报华东分公司，如果2000元以内，则批准；超过则上报北京总公司，如果不超过3000元，则总公司批准，否则拒绝。、

实验报告内容:	

 */


int main(){
    Component *root = new ConcreteCompany("总公司");
    root->Add(new Subcom("人力资源部"));
    root->Add(new Subcom("财务部"));
    root->SetBound(2000, 3000);

    Component *huadong = new ConcreteCompany("上海华东分公司");
    huadong->Add(new Subcom("人力资源部"));
    huadong->Add(new Subcom("财务部"));
    huadong->SetBound(1000, 2000);


    Component *nanjing = new ConcreteCompany("南京办事处");
    nanjing->Add(new Subcom("人力资源部"));
    nanjing->Add(new Subcom("财务部"));
    nanjing->SetBound(0, 1000);

    Component *hanzhou = new ConcreteCompany("杭州办事处");
    hanzhou->Add(new Subcom("人力资源部"));
    hanzhou->Add(new Subcom("财务部"));
    hanzhou->SetBound(0, 1000);

    nanjing->SetSuccessor(huadong);
    hanzhou->SetSuccessor(huadong);
    huadong->SetSuccessor(root);
    root->SetSuccessor(NULL);
    huadong->Add(nanjing);
    huadong->Add(hanzhou);

    root->Add(huadong);
    root->Display(1);
    cout<<"*********************"<<endl;
    nanjing->HandleReauest(100);
    cout<<"*********************"<<endl;
    hanzhou->HandleReauest(1500);
    cout<<"*********************"<<endl;
    hanzhou->HandleReauest(2100);
    cout<<"*********************"<<endl;
    hanzhou->HandleReauest(3100);
    return 0;
}
//