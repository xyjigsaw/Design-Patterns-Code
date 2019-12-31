#include<iostream>
using namespace std;


class User{
    int id;
};

class Department{
    int id;
};

class Project{
    int id;
};




class IUser{
public:
    virtual void Insert(User* user) = 0;
    virtual User* GetUser(int id) = 0;
};

class IDepartment{
public:
    virtual void Insert(Department* department) = 0;
    virtual Department* GetDepartment(int id) = 0;
};

class IProject{
public:
    virtual void Insert(Project* project) = 0;
    virtual Project* GetProject(int id) = 0;
};

class IFactory{
public:
    virtual ~IFactory(){cout<<"抽象工厂实例删除！"<<endl;}
    virtual IUser* CreateUser()=0;
    virtual IDepartment* CreateDepartment()=0;
    virtual IProject* CreateProject()=0;    
};

class SqlserverUser: public IUser{
public:
    void Insert(User* user){
        cout<<"增加一个用户"<<endl;
    }
    User* GetUser(int id){
        cout<<"得到一个用户"<<endl;
        return NULL;
    }
};

class SqlserverDepartment: public IDepartment{
public:
    void Insert(Department* department){
        cout<<"增加一个部门"<<endl;
    }
    Department* GetDepartment(int id){
        cout<<"得到一个部门"<<endl;
        return NULL;
    }
};

class SqlserverProject: public IProject{
public:
    void Insert(Project* project){
        cout<<"增加一个项目"<<endl;
    }
    Project* GetProject(int id){
        cout<<"得到一个项目"<<endl;
        return NULL;
    }
};

class MysqlUser: public IUser{
public:
    void Insert(User* user){
        cout<<"增加一个用户"<<endl;
    }
    User* GetUser(int id){
        cout<<"得到一个用户"<<endl;
        return NULL;
    }
};

class MysqlDepartment: public IDepartment{
public:
    void Insert(Department* department){
        cout<<"增加一个部门"<<endl;
    }
    Department* GetDepartment(int id){
        cout<<"得到一个部门"<<endl;
        return NULL;
    }
};

class MysqlProject: public IProject{
public:
    void Insert(Project* project){
        cout<<"增加一个项目"<<endl;
    }
    Project* GetProject(int id){
        cout<<"得到一个项目"<<endl;
        return NULL;
    }
};


class SqlserverFactory: public IFactory{
public:
    ~SqlserverFactory(){cout<<"SQL Server抽象工厂实例删除！"<<endl;}
    IUser* CreateUser(){
        return new SqlserverUser();
    }
    IDepartment* CreateDepartment(){
        return new SqlserverDepartment();
    }
    IProject* CreateProject(){
        return new SqlserverProject();
    }
    static IFactory *GetInstance(){
        if (factory == NULL ){
                return new SqlserverFactory();
                cout<<"抽象工厂实例生成！"<<endl;
        
        }else cout<<"Error, 抽象工厂实例已有！"<<endl;
        return factory;
    }
private:
    
    SqlserverFactory(){}
    static SqlserverFactory* factory;
};
SqlserverFactory* SqlserverFactory::factory = NULL;



class MysqlFactory: public IFactory{
public:
    ~MysqlFactory(){cout<<"SQL Server抽象工厂实例删除！"<<endl;}
    IUser* CreateUser(){
        return new MysqlUser();
    }
    IDepartment* CreateDepartment(){
        return new MysqlDepartment();
    }
    IProject* CreateProject(){
        return new MysqlProject();
    }
    static IFactory *GetInstance(){
        if (factory == NULL ){
            cout<<"抽象工厂实例生成！"<<endl;
            factory =  new MysqlFactory();
                
        }else cout<<"Error, 抽象工厂实例已有！"<<endl;
        return factory;
    }
private:
    MysqlFactory(){}
    static MysqlFactory* factory;
};
MysqlFactory* MysqlFactory::factory = NULL;

int main(){
    User* user = new User();
    Department* dept = new Department();
    Project* pro = new Project();


    cout<<endl<<"MySQL"<<endl;
    IFactory *factory1 = MysqlFactory::GetInstance();
    IFactory *factory2 = MysqlFactory::GetInstance();
    //生成第二个失败
    IUser* iu = factory1->CreateUser();
    iu->Insert(user);
    iu->GetUser(1);
    
    IDepartment* idept = factory1->CreateDepartment();
    idept->Insert(dept);
    idept->GetDepartment(1);

    IProject* ipro = factory1->CreateProject();
    ipro->Insert(pro);
    ipro->GetProject(1);

    cout<<endl<<"SQL Server"<<endl;
    IFactory *factory12 = MysqlFactory::GetInstance();
    IFactory *factory22 = MysqlFactory::GetInstance();
    //生成第二个失败
    IUser* iu2 = factory12->CreateUser();
    iu->Insert(user);
    iu->GetUser(1);
    
    IDepartment* idept2 = factory12->CreateDepartment();
    idept->Insert(dept);
    idept->GetDepartment(1);

    IProject* ipro2 = factory12->CreateProject();
    ipro->Insert(pro);
    ipro->GetProject(1);
    return 0;
}