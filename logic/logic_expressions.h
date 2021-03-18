#ifndef LOGIC_EXPRESSIONS_H_INCLUDED
#define LOGIC_EXPRESSIONS_H_INCLUDED
#include <vector>
#include <cstdlib>
#include <map>
using namespace std;

enum op_style {slashes, words, typo, math, ampersand};
enum op {op_and, op_or, op_not, op_eq, op_impl};
map<op, string> op_symb;

extern op_style style;

bool allbraces = false;

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
    //virtual var operator=(const var){return *this;}
};
vector<shared_ptr<expr> > catalogue;
shared_ptr<expr> pop_one(int depth, float cut_chance);
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
        if (*m_a) return "1";
        return "0";
    }
    virtual string wrap(bool hide=true, bool walpha=false) {return str(hide);}
    var(bool *a, string name):m_a(a),m_name(name){}
    var(shared_ptr<bool>a, string name):m_a(a),m_name(name){}
    virtual ~var(){}
    virtual int priority() {return 6;}
    virtual void populate(int depth, float cut_chance) {};
    virtual shared_ptr<expr> clone(){return make_shared<var>(m_a,m_name);};
    var& operator=(var a) {*m_a = a.value(); return *this;}
    var& operator=(bool a){*m_a = a; return *this;}
private:
    shared_ptr<bool> m_a;
    string m_name;
    var(){};
    var(const var&){};
};

class disj:public expr
{
public:
    virtual bool value()
    {
        return m_a->value() or m_b->value();
    }
    virtual string str(bool hide=true)
    {
        return "("+m_a->str(hide)+") " + op_symb[op_or] + " ("+m_b->str(hide)+")";
    }
    virtual string wrap(bool hide=true, bool walpha=false)
    {
        return (m_a->priority()<priority() or allbraces?"(":"")+m_a->wrap(hide, walpha)+(m_a->priority()<priority() or allbraces?")":"")
        +op_symb[op_or]
        +(m_b->priority()<=priority() or allbraces?"(":"")+m_b->wrap(hide, walpha)+(m_b->priority()<=priority() or allbraces?")":"");
    }
    disj(expr * a, expr * b):m_a(a),m_b(b){}
    disj(shared_ptr<expr> a, shared_ptr<expr> b):m_a(a),m_b(b){}
    virtual ~disj(){}
    virtual int priority() {return 3;}
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
        return "("+m_a->str(hide)+") " +op_symb[op_and]+" ("+m_b->str(hide)+")";
    }
    virtual string wrap(bool hide=true, bool walpha=false)
    {
        return (m_a->priority()<priority() or allbraces?"(":"")+m_a->wrap(hide, walpha)+(m_a->priority()<priority() or allbraces?")":"")
        +op_symb[op_and]
        +(m_b->priority()<=priority() or allbraces?"(":"")+m_b->wrap(hide, walpha)+(m_b->priority()<=priority() or allbraces?")":"");
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
        return "("+m_a->str(hide)+") "+op_symb[op_impl]+" ("+m_b->str(hide)+")";
    }
    virtual string wrap(bool hide=true, bool walpha=false)
    {
        //cout << "\t" << m_a->priority() << " " << priority() << endl;
        return (m_a->priority()<priority() or allbraces?"(":"")+m_a->wrap(hide, walpha)+(m_a->priority()<priority() or allbraces?")":"")
        +op_symb[op_impl]
        +(m_b->priority()<=priority() or allbraces?"(":"")+m_b->wrap(hide, walpha)+(m_b->priority()<=priority() or allbraces?")":"");
    }
    impl(expr * a, expr * b):m_a(a),m_b(b){};
    impl(shared_ptr<expr> a, shared_ptr<expr> b):m_a(a),m_b(b){};
    virtual ~impl(){}
    virtual int priority() {return 2;}
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
        return ((m_a->value() and m_b->value()) or ((not m_a->value() and not m_b->value())));
    }
    virtual string str(bool hide=true)
    {
        return "("+m_a->str(hide)+") "+op_symb[op_eq]+" ("+m_b->str(hide)+")";
    }
    virtual string wrap(bool hide=true, bool walpha=false)
    {
        //cout << "\t" << m_a->priority() << " " << priority() << endl;
        return (m_a->priority()<priority() or allbraces?"(":"")+m_a->wrap(hide, walpha)+(m_a->priority()<priority() or allbraces?")":"")
        +op_symb[op_eq]
        +(m_b->priority()<=priority() or allbraces?"(":"")+m_b->wrap(hide, walpha)+(m_b->priority()<=priority() or allbraces?")":"");
    }
    eq(expr * a, expr * b):m_a(a),m_b(b){};
    eq(shared_ptr<expr> a, shared_ptr<expr> b):m_a(a),m_b(b){};
    virtual ~eq(){}
    virtual int priority() {return 1;}
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
        return op_symb[op_not]+"("+m_a->str(hide)+")";
    }
    virtual string wrap(bool hide=true, bool walpha=false)
    {
        return op_symb[op_not]+(m_a->priority()<=priority() or allbraces?"(":"")+m_a->wrap(hide, walpha)+(m_a->priority()<=priority() or allbraces?")":"");
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


void fill_op_symb()
{
    if (style == slashes)
    {
        op_symb[op_and] = " /\\ ";
        op_symb[op_or] = " \\/ ";
        op_symb[op_eq] = " = ";
        op_symb[op_impl] = " -> ";
        op_symb[op_not] = "!";
    }
    else if (style == words)
    {
        op_symb[op_and] = " and ";
        op_symb[op_or] = " or ";
        op_symb[op_eq] = " equals ";
        op_symb[op_impl] = " implies ";
        op_symb[op_not] = "not ";
    }
    else if (style == typo)
    {
        op_symb[op_and] = "∧";
        op_symb[op_or] = "∨";
        op_symb[op_eq] = "≡";
        op_symb[op_impl] = "→";
        op_symb[op_not] = "¬";
    }
    else if (style == math)
    {
        op_symb[op_and] = "*";
        op_symb[op_or] = "+";
        op_symb[op_eq] = "=";
        op_symb[op_impl] = "-";
        op_symb[op_not] = "!";
    }
    else if (style == ampersand)
    {
        op_symb[op_and] = " & ";
        op_symb[op_or] = " v ";
        op_symb[op_eq] = " = ";
        op_symb[op_impl] = " -> ";
        op_symb[op_not] = "!";
    }
}
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

#endif // LOGIC_EXPRESSIONS_H_INCLUDED
