#include<iostream>

using namespace std;

class Ps2{ //adaptee
public:
    void isPs2(){
        cout<<"Ps2"<<endl;
    };
};

class Usb{ //target
public:
    virtual void isusb(){
        cout<<"USB接口"<<endl;
    };
};

class Adapter: public Usb{
public:
    void isusb(){
        ps2->isPs2();
    }
private:
    Ps2 * ps2 = new Ps2();
};

int main(){
    Usb* usb = new Adapter();
    usb->isusb();
    return 0;
}