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
    void SetMonitor(string monitor){
        this->monitor = monitor;
    }
    IBM* Clone(){
        IBM* obj = new IBM();
        obj->monitor = monitor;
        obj->keyboard = keyboard;
        obj->mouse = mouse;
        obj->MB = MB->Clone();
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
    };
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
    void CreateIBM(Builder* _ib){
        _ib->BuildMotherboard();
        _ib->BuildMonitor();
        _ib->BuildKeyboard();
        _ib->BuildMouse();
    }

};

int main(){
    IBMDirector* director = new IBMDirector();
    Builder* b1 = new IBMBuilder();
    director->CreateIBM(b1);
    IBM* ibm1 = b1->GetResult();
    //ibm1->display();

    IBM* clone1 = ibm1->Clone();
    clone1->SetMonitor("Clone1 IBM Monitor");

    IBM* clone2 = ibm1->Clone();
    clone2->SetMonitor("Clone2 IBM Monitor");

    ibm1->display();
    clone1->display();
    clone2->display();

    return 0;
}

