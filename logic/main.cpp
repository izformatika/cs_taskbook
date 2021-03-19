#include <iostream>
#include <fstream>
#include <cmath>
#include <time.h>
#include <memory>
#include "logic_expressions.h"
//#include <boost/dynamic_bitset.hpp>

using namespace std;

const bool all_parentheses = true;
op_style style = typo;


bool check_table(vector<vector<bool>> sol, int solutions)
{
    int nos = pow(2, vars.size()) - solutions;
    bool needed = (solutions < nos);

    for (size_t c1(0); c1<sol[0].size()-1; c1++)
    for (size_t c2(c1+1); c2<sol[0].size()-1; c2++)
    {
        bool same_col = true;
        for (size_t r(0); r<sol.size(); r++)
        if (sol[r][sol[0].size()-1] == needed and sol[r][c1]!=sol[r][c2]) {same_col = false; break;}
        if (same_col) return false;

    }
    return true;
//TODO
//a table is bad if it has two cols where either all cells are the same or contain different values only in rows that are otherwise the same (hence we cant tell between these two variables)
}



int main()
{
    ofstream ofs("data.txt");
    fill_op_symb();
    srand(time(0));
    catalogue.push_back(make_shared<conj>(new var(NULL, ""), new var(NULL, "")));
    catalogue.push_back(make_shared<disj>(new var(NULL, ""), new var(NULL, "")));
    catalogue.push_back(make_shared<impl>(new var(NULL, ""), new var(NULL, "")));
    catalogue.push_back(make_shared<eq>(new var(NULL, ""), new var(NULL, "")));
    catalogue.push_back(make_shared<neg>(new var(NULL, "")));
    //bool a=false;
    //bool b=true;
    //bool c=true;
    //(a or b) and (c -> a)
    //shared_ptr<expr> e(new conj(new disj(new var(&a,"a"), new var(&b,"b")), new impl(new var(&c,"c"),new var(&a,"a"))));
    //cout << e->str(true) << " = " << e->value() << endl;
    //a=true;
    //cout << e->str(true) << " = " << e->value() << endl;
    //cout << e->wrap(false) << endl;
    shared_ptr<conj> root=make_shared<conj>(new var(NULL, ""), new var(NULL, ""));
    while (true)
    {
        vars.clear();
        root->populate(3,0.1);
        int solutions(0);
        vector<vector<bool>> sol(pow(2, vars.size()), vector<bool>(vars.size() + 1, false));
        for (int mask(0); mask<pow(2, vars.size());mask++)
        {
            int curmask = mask;
            for (size_t j(0); j<vars.size(); j++)
            {
                *vars[j] = curmask%2;
                sol[mask][j] = curmask%2;
                curmask /= 2;
            }
            //cout << root->wrap(false,false) << " = " << root->value() << endl;
            if (root->value()==1) {solutions++;sol[mask][vars.size()] = true;}
        }
        int nos = pow(2, vars.size()) - solutions;
        if (vars.size() == 5 and (solutions == 4 or solutions == 5 or solutions == 6 or nos == 4 or nos == 5 or nos == 6) and check_table(sol, solutions))
        {
            ofs << root->wrap(true,false) << endl;
            ofs << root->str() << endl;
            ofs << solutions << " " << nos << endl;
            for (auto i: vars)
            {
                ofs << i->str(true) << " ";
            }
            ofs << endl;
            bool yes = (solutions<nos);
            for (auto i: sol)
            {
                if (i[vars.size()] == yes){
                for (auto j: i)
                    ofs << j << " ";
                ofs << endl;}
            }
            break;
        }
    }
    return 0;
}
