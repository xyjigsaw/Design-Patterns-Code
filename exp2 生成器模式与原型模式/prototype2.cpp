#include<iostream>
using namespace std;

/*
使用生成器模式模拟实现IBM电脑的生产，其中IBM电脑的主要结构用如下表示：
class IBM{
  string monitor=”IBM的显示器”;
  string keyboard=”IBM的键盘”;
  string mouse=”IBM的鼠标”;
  Motherboard* MB;
  void display();
}
其中MB是一个主板类，其主要结构如下：
class Motherboard{
string CPU;
string RAM;
}
即主板包含CPU和RAM。display是一个打印各个组件的函数，主要用于检查是否生产正确。
建造顺序为先生产主板，再依次生产显示器、键盘和鼠标。
使用生成器模式生产出第一台IBM电脑后，利用原型模式，将该电脑再复制两台。
*/

class Motherboard{
public:
    string CPU;
    string RAM;
    Motherboard* Clone(){
        return new Motherboard(*this);
    }
};

class IBM{
public:
    IBM(){
        MB = new Motherboard();
    }
    string monitor;
    string keyboard;
    string mouse;
    Motherboard* MB;
    void display(){
        cout<<"-------------------------"<<endl;
        cout<<"IBM电脑配置："<<endl;
        cout<<"主板："<<MB->CPU<<" "<<MB->RAM<<endl;
        cout<<"显示器："<<monitor<<endl;
        cout<<"键盘："<<keyboard<<endl;
        cout<<"鼠标："<<mouse<<endl;
        cout<<"-------------------------"<<endl<<endl;
    }

    void SetMotherboard(string CPU, string RAM){
        this->MB->CPU = CPU;
        this->MB->RAM = RAM;
    }

    void SetMonitor(string monitor){
        this->monitor = monitor;
    }

    void SetKeyboard(string keyboard){
        this->keyboard = keyboard;
    }

    void SetMouse(string mouse){
        this->mouse = mouse;
    }

    IBM* Clone(){
        IBM* obj = new IBM();
        obj->MB = MB->Clone();
        obj->monitor = monitor;
        obj->keyboard = keyboard;
        obj->mouse = mouse;
        return obj;
    }
private:
    /*IBM(Motherboard* mo){
        this->MB = mo->Clone();
    }*/
};

class Builder{
public:
    virtual void BuildMotherboard() = 0;
    virtual void BuildMonitor() = 0;
    virtual void BuildKeyboard() = 0;
    virtual void BuildMouse() = 0;
    virtual IBM* GetResult(){
        return NULL;
    }
};

class IBMBuilder: public Builder{
public:
    IBMBuilder(){
        _IBM = new IBM();
    }
    void BuildMotherboard(){
        _IBM->MB->CPU = "IBM的CPU";
        _IBM->MB->RAM = "IBM的RAM";
        cout<<"安装"<<"IBM的主板"<<endl;
    }
    void BuildMonitor(){
        _IBM->monitor = "IBM的显示器";
        cout<<"安装"<<_IBM->monitor<<endl;
    }
    void BuildKeyboard(){
        _IBM->keyboard = "IBM的键盘";
        cout<<"安装"<<_IBM->keyboard<<endl;
    }
    void BuildMouse(){
        _IBM->mouse = "IBM的鼠标";
        cout<<"安装"<<_IBM->mouse<<endl<<endl;
    }
    IBM* GetResult(){
        return _IBM;
    }
private:
    IBM* _IBM;
};

class IBMDirector{
public:
    void Construct(Builder* builder){
        builder->BuildMotherboard();
        builder->BuildMonitor();
        builder->BuildKeyboard();
        builder->BuildMouse();
    }
};


int main(){
    cout<<endl<<endl;
    IBMDirector* director = new IBMDirector();
    Builder* b1 = new IBMBuilder();
    director->Construct(b1);
    IBM* ibm1 = b1->GetResult();
    
    
    //实验下面两个为克隆部分，为了验证是深拷贝，对clone出来的结果进行更改
    IBM* ibm_clone1 = ibm1->Clone();
    ibm_clone1->SetMotherboard("ibm_clone1 CPU", "ibm_clone1 RAM");
    ibm_clone1->SetMonitor("ibm_clone1 显示器");
    ibm_clone1->SetKeyboard("ibm_clone1 键盘");
    ibm_clone1->SetMouse("ibm_clone1 鼠标");

    IBM* ibm_clone2 = ibm1->Clone();
    ibm_clone2->SetMotherboard("ibm_clone2 CPU", "ibm_clone2 RAM");
    ibm_clone2->SetMonitor("ibm_clone2 显示器");
    ibm_clone2->SetKeyboard("ibm_clone2 键盘");
    ibm_clone2->SetMouse("ibm_clone2 鼠标");

    ibm1->display();
    ibm_clone1->display();
    ibm_clone2->display();
    return 0;
}
