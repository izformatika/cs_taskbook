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


bool check_table(vector<vector<bool>> sol)
{
    for (size_t c1(0); c1<sol[0].size()-1; c1++)
    for (size_t c2(c1+1); c2<sol[0].size()-1; c2++)
    {
        //vector<bool> same(sol.size(), true);
        int diff(0);
        for (size_t r(0); r<sol.size(); r++)
        if (sol[r][c1]!=sol[r][c2]) {diff++;}
        if (diff == 0) return false;
        /*
        //a table is bad if it has two cols where either all cells are the same or contain different values only in rows that are otherwise the same (hence we cant tell between these two variables)
            //actually no, that should be checked only after removing some lines...
        if (diff%2 == 0)
        {
            vector<pair<int,int>> dangerous_row_couples;
            for (size_t r1(0); r1<sol.size(); r1++)
            {
                for (size_t r2(0); r2<sol.size(); r2++)
                {
                    bool enough(false);
                    for (size_t c(0); c<sol[0].size(); c++)
                        if (sol[r1][c]!=sol[r2][c] and (c!=c1 or c!=c2)) {enough = true; break;}
                    if (enough) break;
                    cout << r1 << " " << r2 << endl;
                    dangerous_row_couples.push_back(pair<int,int>(r1,r2));
                }
            }
        }*/

    }
    return true;
}

void gen_func_with_sparse_table()
{
    ofstream ofs("data.txt");
    shared_ptr<conj> root=make_shared<conj>(make_shared<var>(NULL, ""), make_shared<var>(NULL, ""));
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
        bool needed = (solutions < nos);
        for (int i(0); i<sol.size(); i++)
        {
            if (sol[i][sol[0].size()-1] != needed)
            {sol.erase(sol.begin()+i); i--;}
        }

        if (vars.size() == 5 and (solutions == 4 or solutions == 5 or solutions == 6 or nos == 4 or nos == 5 or nos == 6) and check_table(sol))
        {
            ofs << root->wrap(true) << endl;
            ofs << root->fulltext() << endl;
            ofs << root->count_rotations() << endl;
            ofs << solutions << " " << nos << endl;
            for (auto i: vars)
            {
                ofs << i->str(true) << " ";
            }
            ofs << endl;
            for (auto i: sol)
            {
                for (auto j: i)
                    ofs << j << " ";
                ofs << endl;
            }
            break;
        }
    }
    /*TODO: generate smaller table as well. drop rows and digits one-by-one.
    check if the remaining table is recognizeable, i.e. if it has a unique row\col:
    only number of 1 or 0 that fits the original qtty. then check the rest of the table
    for recognizeability considering rows\cols left

    */
}

void shuffle_table()
{
//line 1 - ignore
//line 2 - get min number - n
//line 3 - get labels
//n lines - ignore
//until the end:
    //1 line - empty, ignore
    //several (<=n) nonempty lines - shuffle lines and cols

}

int main()
{

    fill_op_symb();
    srand(time(0));
    catalogue.push_back(make_shared<conj>(make_shared<var>(NULL, ""), make_shared<var>(NULL, "")));
    catalogue.push_back(make_shared<disj>(make_shared<var>(NULL, ""), make_shared<var>(NULL, "")));
    catalogue.push_back(make_shared<impl>(make_shared<var>(NULL, ""), make_shared<var>(NULL, "")));
    catalogue.push_back(make_shared<eq>(make_shared<var>(NULL, ""), make_shared<var>(NULL, "")));
    catalogue.push_back(make_shared<neg>(make_shared<var>(NULL, "")));

    gen_func_with_sparse_table();

    return 0;
}
