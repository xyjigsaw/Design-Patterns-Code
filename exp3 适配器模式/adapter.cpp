#include<iostream>
using namespace std;


/*
分别利用类版本和对象版本的适配器模式模拟实现ps2接口和usb接口的转换。
我们手中有个ps2插头的设备，但是主机上只有usb插头的接口，实现一个适配器将ps2接口转换为usb接口。其中，ps2接口表示为：
class Ps2{
    virtual void isPs2();
}
Usb接口表示为：
class Usb{
    Virtual void isusb();
}。
*/


class Usb{ //target
public:
    virtual void isusb(){
        cout<<"USB接口"<<endl;
    };
};

class Ps2{ //adaptee
public:
    void isPs2(){
        cout<<"Ps2"<<endl;
    };
};

class Adapter: public Usb, private Ps2{
    void isusb(){
        isPs2();
    }
};



int main(){
    Usb* usb = new Adapter();
    usb->isusb();
    return 0;
}