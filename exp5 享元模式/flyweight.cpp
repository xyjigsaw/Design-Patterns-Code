#include<iostream>
#include<map>
#include<vector>
using namespace std;

/* 
假设成立一个外包公司，主要给一些私营业主建网站。商家客户要求的功能包括信息发布、产品展示、博客留言等功能。
共有a-j 10个客户，其中a-c客户需要信息发布，d-f需要产品展示，g-j客户需要博客功能。
利用享元模式模拟该公司建立网站，输出如下：

客户a: 信息发布
客户b：信息发布
。。。

网站分类总数为：3
 */

class Website{
public:
    virtual void Operation(char extrinsicstate) = 0;
};

class ConcreteWebsite: public Website {
public:
    ConcreteWebsite(string function){
        this->function = function;
    }
    void Operation(char extrinsicstate){
        cout<<"客户"<<extrinsicstate<<": "<<function<<endl;
    }
private:
    string function;
};

class FlyweightFactory{
private:
    map<string, ConcreteWebsite*> flyweights;
public:
    FlyweightFactory(){
        flyweights.insert(make_pair("信息发布", new ConcreteWebsite("信息发布")));
        flyweights.insert(make_pair("产品展示", new ConcreteWebsite("产品展示")));
        flyweights.insert(make_pair("博客功能", new ConcreteWebsite("博客功能")));
    }
    Website* GetFlyweight(string key){
        if(! flyweights.count(key)){
            flyweights.insert(make_pair(key, new ConcreteWebsite(key)));
            cout<<"添加状态: "<<key<<"成功"<<endl;
        }
        return (Website*) flyweights[key];
    }
    int getSize(){
        return flyweights.size();
    }
};

int main(){
    FlyweightFactory *factory = new FlyweightFactory();
    vector<Website*> pool;
    for(char i = 'a'; i <= 'j'; i++){
        Website *f;
        if(i >= 'a' && i <= 'c'){
            f = factory->GetFlyweight("信息发布");
            f->Operation(i);
        }else if(i >= 'd' && i <= 'f'){
            f = factory->GetFlyweight("产品展示");
            f->Operation(i);
        }else{
            f = factory->GetFlyweight("博客功能");
            f->Operation(i);
        }
        pool.push_back(f);
    }
    cout<<"网站分类总数为："<<factory->getSize()<<endl;
    //if(pool[0] == pool[1])cout<<"THEY ARE THE SAME!"<<endl;
    return 0;
}
