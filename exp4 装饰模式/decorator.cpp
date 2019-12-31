#include<iostream>
using namespace std;

/*
给定两种初始的汽车类，例如丰田和沃尔沃，
利用装饰模式分别给它们添加新的功能，
其中丰田可以导航和自动驾驶，沃尔沃可以导航和语音控制。
*/

class Car{//Component
public:
    virtual void showInfo() = 0;
};

class TOYOTA: public Car{
public:
    TOYOTA(){}
    TOYOTA(string name){
        this->name = name;
    }
    void showInfo(){
        cout<<name<<endl;
    }
private:
    string name;
};

class  VOLOVO: public Car{
public:
    VOLOVO(){}
    VOLOVO(string name){
        this->name = name;
    }
    void showInfo(){
        cout<<name<<endl;
    }
private:
    string name;
};

class Function: public Car{//Decorator
protected:
    Car* car;
public:
    void Decorate(Car* car){
        this->car = car;
    }
    void showInfo(){
        if(car != NULL)car->showInfo();
    }
};

//其中丰田可以导航和自动驾驶，沃尔沃可以导航和语音控制。

class Navigator: public Function{
public:
    void showInfo(){
        cout<<"导航 ";
        Function::showInfo();
    }
};

class SelfDrive: public Function{
public:
    void showInfo(){
        cout<<"自动驾驶 ";
        Function::showInfo();
    }
};

class VoiceControl: public Function{
public:
    void showInfo(){
        cout<<"语音控制 ";
        Function::showInfo();
    }
};


//其中丰田可以导航和自动驾驶，沃尔沃可以导航和语音控制。
int main(){
    Car* toyota = new TOYOTA("丰田卡罗拉");
    Navigator* na = new Navigator();
    SelfDrive* sd = new SelfDrive();
    na->Decorate(toyota);
    sd->Decorate(na);
    sd->showInfo();
    cout<<endl;
    
    Car* volovo = new VOLOVO("沃尔沃S90");
    Navigator* na2 = new Navigator();
    VoiceControl* vc = new VoiceControl();
    na2->Decorate(volovo);
    vc->Decorate(na2);
    vc->showInfo();

    return 0;
}