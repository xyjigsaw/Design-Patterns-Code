#include<iostream>
#include<vector>
#include<map>
using namespace std;

class Context;
class Variable;

class Expression{
private: 
    
public: 
    virtual double interpret(Context *con) = 0;
    virtual void display(Context *con) = 0;
};

class Bracket :public Expression{
public:
	Bracket(Expression * n){
		exp = n;
	}
	double interpret(Context *con){
		return exp->interpret(con);
	}
	void display(Context *con){
		cout << "(";
		exp->display(con);
		cout << ")";
	}
private:
	Expression * exp;
};



class Context{
private: 
    map<Variable*, double> valueMap;
public: 
    void addValue(Variable *x, double y){
        double yi = y;
        valueMap[x]  = yi;
    }
    
    double LookupValue(Variable *x){
        double i = valueMap[x];
        return i;
    }
};

class Variable : public  Expression{
public:  
    void display(Context *con){
        cout<<con->LookupValue(this);
    }
    double interpret(Context *con){
        return con->LookupValue(this);
    }
};


class Add : public Expression{
private: 
    Expression *left, *right;
public: 
    Add(Expression *leftx, Expression *rightx){
        left =  leftx;
        right = rightx;
    }
    void display(Context *con){
        left->display(con);
        cout<<" + ";
        right->display(con);
    }
    double interpret(Context *con){
        return left->interpret(con) + right->interpret(con);
    }
};

class Substract : public Expression{
private: 
    Expression *left, *right;
public: 
    Substract(Expression *leftx, Expression *rightx){
        left =  leftx;
        right = rightx;
    }
    void display(Context *con){
        left->display(con);
        cout<<" - ";
        right->display(con);
    }
    double interpret(Context *con){
        return left->interpret(con) - right->interpret(con);
    }
};

class Multiply : public Expression{
private: 
    Expression *left, *right;
public: 
    Multiply(Expression *leftx, Expression *rightx){
        left =  leftx;
        right = rightx;
    }
    void display(Context *con){
        left->display(con);
        cout<<" * ";
        right->display(con);
    }
    double interpret(Context *con){
        return left->interpret(con) * right->interpret(con);
    }
};

class Division : public Expression{
private: 
    Expression *left, *right;
public: 
    Division(Expression *leftx, Expression *rightx){
        left =  leftx;
        right = rightx;
    }
    void display(Context *con){
        left->display(con);
        cout<<" / ";
        right->display(con);
    }
    double interpret(Context *con){
        return left->interpret(con) / right->interpret(con);
    }
};



class Constant : public Expression{
private: 
    int i;
public: 
    Constant(int a){
        i = a;
    }
    double interpret(Context *con){
        return i;
    }
};


//3 + ((4*6) - (7/2))
int main(){
    Expression *ex;
    Context  *con  =  new Context();
    Variable *a = new Variable();
    Variable *b = new Variable();
    Variable *c = new Variable();
    Variable *d = new Variable();
    Variable *e = new Variable();
    con->addValue(a, 3);
    con->addValue(b, 4);
    con->addValue(c, 6);
    con->addValue(d, 7);
    con->addValue(e, 2);
    ex = new Add(a, new Bracket(new Substract(new Bracket(new Multiply(b, c)), new Bracket(new Division(d, e)))));
    ex->display(con);
    cout<<" =  "<<ex->interpret(con)<<endl;
    return 0;
}
