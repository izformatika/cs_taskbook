#include "logic_expressions.h"
map<op, string> op_symb;
op_style style;
bool allbraces = false;
vector<shared_ptr<expr> > catalogue;
vector<shared_ptr<var> > vars;

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
void make_vars(int n)
{
    vars.clear();
    for (int i(0);i<n; i++)
        vars.push_back(make_shared<var>(true, string(1,vars.size()+'a')));
}

void neg::make_rot(dynamic_bitset<>cur_mask, int from, int to){}
void var::make_rot(dynamic_bitset<>cur_mask, int from, int to)
{}
//TODO
void bin_op::make_rot(dynamic_bitset<>cur_mask, int from, int to)
{}

void commut_op::make_rot(dynamic_bitset<>cur_mask, int from, int to)
{}

