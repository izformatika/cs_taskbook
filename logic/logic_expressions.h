#ifndef LOGIC_EXPRESSIONS_H_INCLUDED
#define LOGIC_EXPRESSIONS_H_INCLUDED
#include <vector>
#include <cstdlib>
#include <map>
using namespace std;

enum op_style {slashes, words, typo, math, ampersand};
enum op {op_and, op_or, op_not, op_eq, op_impl, op_fake};
map<op, string> op_symb;

extern op_style style;

bool allbraces = false;

class expr
{
public:
    virtual bool value()=0;
    virtual string str(bool hide=true)=0;
    virtual string fulltext()=0;
    virtual string type(){return "logic";}
    virtual ~expr(){};
    virtual string wrap(bool hide=true)=0;
    virtual int priority()=0;
    virtual void populate(int depth, float cut_chance)=0;
    virtual shared_ptr<expr> clone()=0;
    virtual int count_rotations()=0;
    //virtual var operator=(const var){return *this;}
};
vector<shared_ptr<expr> > catalogue;
shared_ptr<expr> pop_one(int depth, float cut_chance);
class bin_op: public expr
{
public:
    virtual int count_rotations() {return m_a->count_rotations()*m_b->count_rotations();}
    virtual bool value()=0;
    virtual string str(bool hide=true)
    {
        return "("+m_a->str(hide)+") " + op_symb[m_symb()] + " ("+m_b->str(hide)+")";
    }
    virtual string wrap(bool hide=true)
    {
        return (m_a->priority()<priority() or allbraces?"(":"")+m_a->wrap(hide)+(m_a->priority()<priority() or allbraces?")":"")
        +op_symb[m_symb()]
        +(m_b->priority()<=priority() or allbraces?"(":"")+m_b->wrap(hide)+(m_b->priority()<=priority() or allbraces?")":"");
    }
    virtual void populate(int depth, float cut_chance)
    {
        m_a=pop_one(depth, cut_chance);
        m_b=pop_one(depth, cut_chance);
    }
    virtual int priority()=0;
    virtual string fulltext()=0;
    bin_op(expr * a, expr * b):m_a(a),m_b(b){}
    bin_op(shared_ptr<expr> a, shared_ptr<expr> b):m_a(a),m_b(b){}
    virtual ~bin_op(){}
    virtual op m_symb()=0;
protected:
    shared_ptr<expr> m_a;
    shared_ptr<expr> m_b;

protected:
    bin_op(){};
};

class commut_op: public bin_op
{
public:
    virtual bool value()=0;
    virtual int count_rotations() {return (m_a->str()==m_b->str()?1:2)*m_a->count_rotations()*m_b->count_rotations();}
    commut_op(shared_ptr<expr> a, shared_ptr<expr> b):bin_op(a, b){};
    virtual op m_symb()=0;
protected:
    commut_op(){};
};

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
    virtual string fulltext()
    {
        return "new var(&" + m_name + ", \"" + m_name + "\")";
    }
    virtual string wrap(bool hide=true) {return str(hide);}
    var(shared_ptr<bool>a, string name):m_a(a),m_name(name){}
    var(bool a, string name):m_a(make_shared<bool>(a)),m_name(name){}
    virtual ~var(){}
    virtual int priority() {return 6;}
    virtual void populate(int depth, float cut_chance){};
    virtual shared_ptr<expr> clone(){return make_shared<var>(m_a,m_name);};
    var& operator=(var a) {*m_a = a.value(); return *this;}
    var& operator=(bool a){*m_a = a; return *this;}
    virtual int count_rotations() {return 1;}
private:
    shared_ptr<bool> m_a;
    string m_name;
    var(){};
    var(const var&){};
};

class disj:public commut_op
{
public:
    virtual bool value()
    {
        return m_a->value() or m_b->value();
    }

    disj(shared_ptr<expr>  a, shared_ptr<expr>  b):commut_op(a,b){};
    //disj(shared_ptr<expr> a, shared_ptr<expr> b):m_a(a),m_b(b){}
    //virtual ~disj(){}
    virtual int priority() {return 3;}
    virtual string fulltext()
    {
        return "new disj(" + m_a->fulltext()+", " + m_b->fulltext()+")";
    }
    virtual shared_ptr<expr> clone() {return make_shared<disj>(m_a,m_b);};
    virtual op m_symb() {return op_or;};
private:
    //disj(){};
//    disj(const disj&){};
    //disj operator=(const disj){}
};
class conj:public commut_op
{
public:
    virtual bool value()
    {
        return m_a->value() and m_b->value();
    }
    virtual string fulltext()
    {
        return "new conj(" + m_a->fulltext()+", " + m_b->fulltext()+")";
    }
    virtual int priority() {return 4;}
conj(shared_ptr<expr>  a, shared_ptr<expr>  b):commut_op(a,b){};
 //   conj(shared_ptr<expr> a, shared_ptr<expr> b):m_a(a),m_b(b){}
 //   ~conj(){}
    virtual shared_ptr<expr> clone() {return make_shared<conj>(m_a,m_b);};
    virtual op m_symb() {return op_and;};
private:
  //  conj();
   // conj(const conj&){};
    //conj operator=(const conj){}
};
class impl:public bin_op
{
public:
//    virtual int count_rotations() {return}
    virtual bool value()
    {
        return not m_a->value() or m_b->value();
    }
    virtual string fulltext()
    {
        return "new impl(" + m_a->fulltext()+", " + m_b->fulltext()+")";
    }
    impl(shared_ptr<expr>  a, shared_ptr<expr>  b):bin_op(a,b){};
    virtual op m_symb() {return op_impl;};
//    impl(expr * a, expr * b):m_a(a),m_b(b){};
 //   impl(shared_ptr<expr> a, shared_ptr<expr> b):m_a(a),m_b(b){};
  //  virtual ~impl(){}
    virtual int priority() {return 2;}
    virtual shared_ptr<expr> clone() {return make_shared<impl>(m_a,m_b);};
private:
    //impl(){};
    //impl(const impl&){};
    //impl operator=(const impl){};
};
class eq:public commut_op
{
public:
    virtual bool value()
    {
        return ((m_a->value() and m_b->value()) or ((not m_a->value() and not m_b->value())));
    }
    virtual op m_symb() {return op_eq;};
    virtual string fulltext()
    {
        return "new eq(" + m_a->fulltext()+", " + m_b->fulltext()+")";
    }
//    eq(expr * a, expr * b):m_a(a),m_b(b){};
    eq(shared_ptr<expr> a, shared_ptr<expr> b):commut_op(a,b) {}
  //  virtual ~eq(){}
    virtual int priority() {return 1;}
    virtual shared_ptr<expr> clone() {return make_shared<eq>(m_a,m_b);};
private:
    //eq(){};
    //eq(const impl&){};

};
class neg:public expr
{
public:
    virtual int count_rotations() {return m_a->count_rotations();}
    virtual bool value()
    {
        return not m_a->value();
    }
    virtual string str(bool hide=true)
    {
        return op_symb[op_not]+"("+m_a->str(hide)+")";
    }
    virtual string wrap(bool hide=true)
    {
        return op_symb[op_not]+(m_a->priority()<=priority() or allbraces?"(":"")+m_a->wrap(hide)+(m_a->priority()<=priority() or allbraces?")":"");
    }
    virtual string fulltext()
    {
        return "new neg(" + m_a->fulltext()+")";
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
        op_symb[op_fake] = "#";
    }
    else if (style == words)
    {
        op_symb[op_and] = " and ";
        op_symb[op_or] = " or ";
        op_symb[op_eq] = " equals ";
        op_symb[op_impl] = " implies ";
        op_symb[op_not] = "not ";
        op_symb[op_fake] = "#";
    }
    else if (style == typo)
    {
        op_symb[op_and] = "∧";
        op_symb[op_or] = "∨";
        op_symb[op_eq] = "≡";
        op_symb[op_impl] = "→";
        op_symb[op_not] = "¬";
        op_symb[op_fake] = "#";
    }
    else if (style == math)
    {
        op_symb[op_and] = "*";
        op_symb[op_or] = "+";
        op_symb[op_eq] = "=";
        op_symb[op_impl] = "-";
        op_symb[op_not] = "!";
        op_symb[op_fake] = "#";
    }
    else if (style == ampersand)
    {
        op_symb[op_and] = " & ";
        op_symb[op_or] = " v ";
        op_symb[op_eq] = " = ";
        op_symb[op_impl] = " -> ";
        op_symb[op_not] = "!";
        op_symb[op_fake] = "#";
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
        vars.push_back(make_shared<var>(bool(rand()%2), string(1,vars.size()+'a')));
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
