#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <memory>

using namespace std;

class expr
{
public:
    virtual bool value()=0;
    virtual string str(bool hide=true)=0;
    virtual string type(){return "logic";}
    virtual ~expr(){};
    virtual string wrap(bool hide=true, bool walpha=false)=0;
    virtual int priority()=0;
    virtual void populate(int depth, float cut_chance)=0;
    virtual shared_ptr<expr> clone()=0;
};
vector<shared_ptr<expr> > catalogue;
class var:public expr
{
public:
    virtual bool value()
    {
        return *m_a;
    }
    virtual string str(bool hide=true)
    {
        if (hide) return m_name;
        if (m_a) return "1";
        return "0";
    }
    virtual string wrap(bool hide=true, bool walpha=false) {return str(hide);}
    var(bool *a, string name):m_a(a),m_name(name){}
    var(shared_ptr<bool>a, string name):m_a(a),m_name(name){}
    virtual ~var(){}
    virtual int priority() {return 6;}
    virtual void populate(int depth, float cut_chance) {};
    virtual shared_ptr<expr> clone(){return make_shared<var>(m_a,m_name);};
private:
    shared_ptr<bool> m_a;
    string m_name;
    var(){};
    var(const var&){};
    //var operator=(const var){return *this;}
};
vector<shared_ptr<var> > vars;

shared_ptr<var> choose_var()
{
    if (rand()%5>0 and rand()%3<vars.size())
    {
        int which=rand()%(vars.size());
        return vars[which];
    }
    else
    {
        vars.push_back(make_shared<var>(new bool(rand()%2), string(1,vars.size()+'a')));
        return (vars[vars.size()-1]);
    }
}

shared_ptr<expr> pop_one(int depth, float cut_chance)
{
    if ((rand()%100)<(cut_chance*100) or depth==0)
    {
        return choose_var();
    }
    else//not the time to stop, we need to generate deeper
    {
        shared_ptr<expr> tmp=catalogue[rand()%catalogue.size()]->clone();
        tmp->populate(depth-1, cut_chance);
        return tmp;
    }
}


class disj:public expr
{
public:
    virtual bool value()
    {
        return m_a->value() or m_b->value();
    }
    virtual string str(bool hide=true)
    {
        return "("+m_a->str(hide)+") \\/ ("+m_b->str(hide)+")";
    }
    virtual string wrap(bool hide=true, bool walpha=false)
    {
        return (m_a->priority()<priority()?"(":"")+m_a->wrap(hide)+(m_a->priority()<priority()?")":"")
        +(walpha?" or ":" \\/ ")
        +(m_b->priority()<priority()?"(":"")+m_b->wrap(hide)+(m_b->priority()<priority()?")":"");
    }
    disj(expr * a, expr * b):m_a(a),m_b(b){}
    disj(shared_ptr<expr> a, shared_ptr<expr> b):m_a(a),m_b(b){}
    virtual ~disj(){}
    virtual int priority() {return 2;}
    virtual void populate(int depth, float cut_chance)
    {
        m_a=pop_one(depth, cut_chance);
        m_b=pop_one(depth, cut_chance);
    }
    virtual shared_ptr<expr> clone() {return make_shared<disj>(m_a,m_b);};
private:
    shared_ptr<expr> m_a;
    shared_ptr<expr> m_b;
    disj(){};
    disj(const disj&){};
    //disj operator=(const disj){}
};
class conj:public expr
{
public:
    virtual bool value()
    {
        return m_a->value() and m_b->value();
    }
    virtual string str(bool hide=true)
    {
        return "("+m_a->str(hide)+") /\\ ("+m_b->str(hide)+")";
    }
    virtual string wrap(bool hide=true, bool walpha=false)
    {
        return (m_a->priority()<priority()?"(":"")+m_a->wrap(hide)+(m_a->priority()<priority()?")":"")
        +(walpha?" and ":" /\\ ")
        +(m_b->priority()<priority()?"(":"")+m_b->wrap(hide)+(m_b->priority()<priority()?")":"");
    }
    conj(expr * a, expr * b):m_a(a),m_b(b){}
    conj(shared_ptr<expr> a, shared_ptr<expr> b):m_a(a),m_b(b){}
    ~conj(){}
    virtual int priority() {return 4;}
    virtual void populate(int depth, float cut_chance)
    {
        m_a=pop_one(depth, cut_chance);
        m_b=pop_one(depth, cut_chance);
    }
    virtual shared_ptr<expr> clone() {return make_shared<conj>(m_a,m_b);};
private:
    shared_ptr<expr> m_a;
    shared_ptr<expr> m_b;
    conj();
    conj(const conj&){};
    //conj operator=(const conj){}
};
class impl:public expr
{
public:
    virtual bool value()
    {
        return not m_a->value() or m_b->value();
    }
    virtual string str(bool hide=true)
    {
        return "("+m_a->str(hide)+") -> ("+m_b->str(hide)+")";
    }
    virtual string wrap(bool hide=true, bool walpha=false)
    {
        //cout << "\t" << m_a->priority() << " " << priority() << endl;
        return (m_a->priority()<priority()?"(":"")+m_a->wrap(hide)+(m_a->priority()<priority()?")":"")
        +(walpha?" implies ":" -> ")
        +(m_b->priority()<priority()?"(":"")+m_b->wrap(hide)+(m_b->priority()<priority()?")":"");
    }
    impl(expr * a, expr * b):m_a(a),m_b(b){};
    impl(shared_ptr<expr> a, shared_ptr<expr> b):m_a(a),m_b(b){};
    virtual ~impl(){}
    virtual int priority() {return 3;}
    virtual void populate(int depth, float cut_chance)
    {
        m_a=pop_one(depth, cut_chance);
        m_b=pop_one(depth, cut_chance);
    }
    virtual shared_ptr<expr> clone() {return make_shared<impl>(m_a,m_b);};
private:
    shared_ptr<expr> m_a;
    shared_ptr<expr> m_b;
    impl(){};
    impl(const impl&){};
    //impl operator=(const impl){};
};
class eq:public expr
{
public:
    virtual bool value()
    {
        return m_a->value() and m_b->value() or (not m_a->value() and not m_b->value());
    }
    virtual string str(bool hide=true)
    {
        return "("+m_a->str(hide)+") = ("+m_b->str(hide)+")";
    }
    virtual string wrap(bool hide=true, bool walpha=false)
    {
        //cout << "\t" << m_a->priority() << " " << priority() << endl;
        return (m_a->priority()<priority()?"(":"")+m_a->wrap(hide)+(m_a->priority()<priority()?")":"")
        +(walpha?" equals ":" = ")
        +(m_b->priority()<priority()?"(":"")+m_b->wrap(hide)+(m_b->priority()<priority()?")":"");
    }
    eq(expr * a, expr * b):m_a(a),m_b(b){};
    eq(shared_ptr<expr> a, shared_ptr<expr> b):m_a(a),m_b(b){};
    virtual ~eq(){}
    virtual int priority() {return 3;}
    virtual void populate(int depth, float cut_chance)
    {
        m_a=pop_one(depth, cut_chance);
        m_b=pop_one(depth, cut_chance);
    }
    virtual shared_ptr<expr> clone() {return make_shared<eq>(m_a,m_b);};
private:
    shared_ptr<expr> m_a;
    shared_ptr<expr> m_b;
    eq(){};
    eq(const impl&){};

};
class neg:public expr
{
public:
    virtual bool value()
    {
        return not m_a->value();
    }
    virtual string str(bool hide=true)
    {
        return "(!"+m_a->str(hide)+")";
    }
    virtual string wrap(bool hide=true, bool walpha=false)
    {
        return (m_a->priority()<priority()?"(":"")+string((walpha?"not ":"!"))+m_a->wrap(hide)+(m_a->priority()<priority()?")":"");
    }
    neg(expr * a):m_a(a){};
    neg(shared_ptr<expr> a):m_a(a){};
    virtual ~neg(){}
    virtual int priority() {return 5;}
    virtual void populate(int depth, float cut_chance)
    {
        m_a=pop_one(depth, cut_chance);
    }
    virtual shared_ptr<expr> clone() {return make_shared<neg>(m_a);};
private:
    shared_ptr<expr> m_a;
    neg(){};
    neg(const neg&){};
    //neg operator=(const neg){};
};




int main()
{
    srand(time(0));
    catalogue.push_back(make_shared<conj>(new var(NULL, ""), new var(NULL, "")));
    catalogue.push_back(make_shared<disj>(new var(NULL, ""), new var(NULL, "")));
    catalogue.push_back(make_shared<impl>(new var(NULL, ""), new var(NULL, "")));
    catalogue.push_back(make_shared<eq>(new var(NULL, ""), new var(NULL, "")));
    catalogue.push_back(make_shared<neg>(new var(NULL, "")));
    bool a=false;
    bool b=true;
    bool c=true;
    //(a or b) and (c -> a)
    shared_ptr<expr> e(new conj(new disj(new var(&a,"a"), new var(&b,"b")), new impl(new var(&c,"c"),new var(&a,"a"))));
    //cout << e->str(true) << " = " << e->value() << endl;
    a=true;
    //cout << e->str(true) << " = " << e->value() << endl;
    cout << e->wrap(true) << endl;
    shared_ptr<conj> root=make_shared<conj>(new var(NULL, ""), new var(NULL, ""));
    root->populate(3,0.1);
    cout << root->wrap(true,true) << endl;

    return 0;
}
