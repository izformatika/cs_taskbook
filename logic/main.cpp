#include <iostream>
#include <cmath>
#include <time.h>
#include <memory>
#include "logic_expressions.h"

using namespace std;

const bool all_parentheses = true;

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





int main()
{
    fill_op_symb();
    srand(time(0));
    catalogue.push_back(make_shared<conj>(new var(NULL, ""), new var(NULL, "")));
    catalogue.push_back(make_shared<disj>(new var(NULL, ""), new var(NULL, "")));
    catalogue.push_back(make_shared<impl>(new var(NULL, ""), new var(NULL, "")));
    catalogue.push_back(make_shared<eq>(new var(NULL, ""), new var(NULL, "")));
    catalogue.push_back(make_shared<neg>(new var(NULL, "")));
    /*bool a=false;
    bool b=true;
    bool c=true;
    //(a or b) and (c -> a)
    shared_ptr<expr> e(new conj(new disj(new var(&a,"a"), new var(&b,"b")), new impl(new var(&c,"c"),new var(&a,"a"))));
    cout << e->str(true) << " = " << e->value() << endl;
    a=true;
    cout << e->str(true) << " = " << e->value() << endl;
    cout << e->wrap(false) << endl;*/
    shared_ptr<conj> root=make_shared<conj>(new var(NULL, ""), new var(NULL, ""));
    while (true)
    {
        vars.clear();
        root->populate(3,0.1);
        int solutions(0);
        for (int mask(0); mask<pow(2, vars.size());mask++)
        {
            int curmask = mask;
            for (size_t j(0); j<vars.size(); j++)
            {
                *vars[j] = curmask%2;
                curmask /= 2;
            }
            //cout << root->wrap(false,false) << " = " << root->value() << endl;
            if (root->value()==1) solutions++;
        }
        int nos = pow(2, vars.size()) - solutions;
        if (vars.size() == 5 and (solutions == 4 or solutions == 5 or solutions == 6 or nos == 4 or nos == 5 or nos == 6))
        {
            cout << root->wrap(true,false) << endl;
            cout << root->str() << endl;
            cout << solutions << " " << nos << endl;
            for (int mask(0); mask<pow(2, vars.size());mask++)
            {
                int curmask = mask;
                for (size_t j(0); j<vars.size(); j++)
                {
                    *vars[j] = curmask%2;
                    curmask /= 2;
                }
                if (root->value()==1)
                    cout << root->wrap(false,false) << " = " << root->value() << endl;
            }
            break;
        }
    }
    return 0;
}
