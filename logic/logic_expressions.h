#ifndef LOGIC_EXPRESSIONS_H_INCLUDED
#define LOGIC_EXPRESSIONS_H_INCLUDED
#include "global.h"
enum op_style {slashes, words, typo, math, ampersand};
enum op {op_and, op_or, op_not, op_eq, op_impl, op_fake};
extern map<op, string> op_symb;

extern op_style style;

extern bool allbraces;

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
    virtual int count_rotations()=0;
    virtual void make_rot(dynamic_bitset<>cur_mask, int from, int to)=0;
    expr(){}
    virtual shared_ptr<expr>clone()=0;
private:
    expr(const expr&){}
};

extern vector<shared_ptr<expr> > catalogue;
shared_ptr<expr> pop_one(int depth, float cut_chance);
class bin_op: public expr
{
public:
    virtual int count_rotations() {return m_a->count_rotations()+m_b->count_rotations();}
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
    virtual void make_rot(dynamic_bitset<>cur_mask, int from, int to);
    virtual shared_ptr<expr>clone()=0;
protected:
    shared_ptr<expr> m_a;
    shared_ptr<expr> m_b;
    bin_op(){};
private:
    bin_op(const bin_op&){}
};

class commut_op: public bin_op
{
public:
    virtual bool value()=0;
    virtual int count_rotations() {return (m_a->str()==m_b->str()?0:1/*TODO: make better comparisons*/)+m_a->count_rotations()+m_b->count_rotations();}
    commut_op(shared_ptr<expr> a, shared_ptr<expr> b):bin_op(a, b){};
    virtual op m_symb()=0;
    virtual void make_rot(dynamic_bitset<>cur_mask, int from, int to);
    virtual shared_ptr<expr>clone()=0;
private:
    commut_op(const commut_op&){};
protected:
    commut_op(){};
};

class var:public expr
{
public:
    virtual void make_rot(dynamic_bitset<>cur_mask, int from, int to);
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
        return "vars[" + to_string(int(m_name[0])-int('a')) + "]";
    }
    virtual string wrap(bool hide=true) {return str(hide);}
    var(shared_ptr<bool>a, string name):m_a(a),m_name(name){}
    var(bool a, string name):m_a(make_shared<bool>(a)),m_name(name){}
    virtual ~var(){}
    virtual int priority() {return 6;}
    virtual void populate(int depth, float cut_chance){};
    var& operator=(var a) {*m_a = a.value(); return *this;}
    var& operator=(bool a){*m_a = a; return *this;}
    virtual int count_rotations() {return 0;}

    virtual shared_ptr<expr>clone()
    {
        auto r = shared_ptr<var>(new var(m_a, m_name));
        return dynamic_pointer_cast<expr>(r);
    }
private:
    var(const var&){};
    shared_ptr<bool> m_a;
    string m_name;
    var(){};
};

class disjunction:public commut_op
{
public:
    virtual bool value()
    {
        return m_a->value() or m_b->value();
    }

    disjunction(shared_ptr<expr>  a, shared_ptr<expr>  b):commut_op(a,b){};
    //disjunction(shared_ptr<expr> a, shared_ptr<expr> b):m_a(a),m_b(b){}
    //virtual ~disjunction(){}
    virtual int priority() {return 3;}
    virtual string fulltext()
    {
        return "make_shared<disjunction>(" + m_a->fulltext()+", " + m_b->fulltext()+")";
    }
    virtual shared_ptr<expr>clone()
    {
        auto r = shared_ptr<disjunction>(new disjunction(m_a->clone(), m_b->clone()));
        return dynamic_pointer_cast<expr>(r);
    }
    virtual op m_symb() {return op_or;};
private:
    disjunction(){};
    disjunction(const disjunction&){};
    //disjunction operator=(const disjunction){}
};
class conjunction:public commut_op
{
public:
    virtual bool value()
    {
        return m_a->value() and m_b->value();
    }
    virtual string fulltext()
    {
        return "make_shared<conjunction>(" + m_a->fulltext()+", " + m_b->fulltext()+")";
    }
    virtual int priority() {return 4;}
conjunction(shared_ptr<expr>  a, shared_ptr<expr>  b):commut_op(a,b){};
 //   conjunction(shared_ptr<expr> a, shared_ptr<expr> b):m_a(a),m_b(b){}
 //   ~conjunction(){}
    virtual shared_ptr<expr>clone()
    {
        auto r = shared_ptr<conjunction>(new conjunction(m_a->clone(), m_b->clone()));
        return dynamic_pointer_cast<expr>(r);
    }
    virtual op m_symb() {return op_and;};
private:

  //  conjunction();
    conjunction(const conjunction&){};
    //conjunction operator=(const conjunction){}
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
        return "make_shared<impl>(" + m_a->fulltext()+", " + m_b->fulltext()+")";
    }
    impl(shared_ptr<expr>  a, shared_ptr<expr>  b):bin_op(a,b){};
    virtual op m_symb() {return op_impl;};
//    impl(expr * a, expr * b):m_a(a),m_b(b){};
 //   impl(shared_ptr<expr> a, shared_ptr<expr> b):m_a(a),m_b(b){};
  //  virtual ~impl(){}
    virtual int priority() {return 2;}
    virtual shared_ptr<expr>clone()
    {
        auto r = shared_ptr<impl>(new impl(m_a->clone(), m_b->clone()));
        return dynamic_pointer_cast<expr>(r);
    }
private:
    impl(const impl&){};
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
        return "make_shared<eq>(" + m_a->fulltext()+", " + m_b->fulltext()+")";
    }
//    eq(expr * a, expr * b):m_a(a),m_b(b){};
    eq(shared_ptr<expr> a, shared_ptr<expr> b):commut_op(a,b) {}
  //  virtual ~eq(){}
    virtual int priority() {return 1;}
    virtual shared_ptr<expr>clone()
    {
        auto r = shared_ptr<eq>(new eq(m_a->clone(), m_b->clone()));
        return dynamic_pointer_cast<expr>(r);
    }
private:
    eq(const impl&){};

};
class neg:public expr
{
public:
    virtual void make_rot(dynamic_bitset<>cur_mask, int from, int to);
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
        return "make_shared<neg>(" + m_a->fulltext()+")";
    }
    neg(expr * a):m_a(a){};
    neg(shared_ptr<expr> a):m_a(a){};
    virtual ~neg(){}
    virtual int priority() {return 5;}
    virtual void populate(int depth, float cut_chance)
    {
        m_a=pop_one(depth, cut_chance);
    }
    virtual shared_ptr<expr>clone()
    {
        auto r = shared_ptr<neg>(new neg(m_a->clone()));
        return dynamic_pointer_cast<expr>(r);
    }
private:
    shared_ptr<expr> m_a;
    neg(const neg&){};
    //neg operator=(const neg){};
};


extern vector<shared_ptr<var> > vars;
void make_vars(int n);
shared_ptr<expr> pop_one(int depth, float cut_chance);
shared_ptr<var> choose_var();
void fill_op_symb();
int get_solutions(shared_ptr<expr> root, vector<vector<bool>> &sol);
#endif // LOGIC_EXPRESSIONS_H_INCLUDED
