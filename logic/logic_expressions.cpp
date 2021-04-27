#include "logic_expressions.h"
map<op, string> op_symb;
op_style style;
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

void neg::make_rot(dynamic_bitset<>cur_mask, int from, int to)
{
    m_a->make_rot(cur_mask,from+1,to);
}
void var::make_rot(dynamic_bitset<>cur_mask, int from, int to)
{
    //cout << "";
    /*nothing*/
    }
void bin_op::make_rot(dynamic_bitset<>cur_mask, int from, int to)
{
    //cout << m_a->wrap() << " # " << m_b->wrap() << endl;
    int rot_a=m_a->count_rotations();
    m_a->make_rot(cur_mask,from,from+rot_a-1);
    m_b->make_rot(cur_mask,from+rot_a,to);
}

void commut_op::make_rot(dynamic_bitset<>cur_mask, int from, int to)
{
    //cout << m_a->wrap() << " # " << m_b->wrap() << endl;
    int rot_a=m_a->count_rotations();
    m_a->make_rot(cur_mask,from,from+rot_a-1);
    m_b->make_rot(cur_mask,from+rot_a+1,to);
    if (cur_mask[from+rot_a]) swap(m_a, m_b);
}

int get_solutions(shared_ptr<expr> root, vector<vector<bool>> &sol)
{
    sol = vector<vector<bool>>(pow(2, vars.size()), vector<bool>(vars.size() + 1, false));
    int res(0);
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
        if (root->value()==1) {res++;sol[mask][vars.size()] = true;}
    }
    return res;
}

