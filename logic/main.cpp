#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <memory>
#include <boost/dynamic_bitset/dynamic_bitset.hpp>

using boost::dynamic_bitset;
using namespace std;

class task
{
public:
    task(vector<string> s, bool (*v)(dynamic_bitset<>)):out(s),val(v){};
    vector<string> out;
    bool (*val)(dynamic_bitset<>);
    int len(){return out.size()-1;};
};

vector<task> tasks;

void populate_tasks()
{
    //tasks.push_back(task(vector<string>{""," v "," = 1"},[](dynamic_bitset<>db){return (db[0] or db[1]==1);}));
    ///this only works if we have ONLY xs. x1x2x3y1 shifts not to x2x3x4y2 but to x2x3y1x4
    tasks.push_back(task(vector<string>{"("," v ",") & ("," & "," -> ",") & (!"," v ",") = 1" },[](dynamic_bitset<>db){return ((db[0] or db[1]) and (not (db[0] and db[1]) or db[2]) and (not db[0] or db[4]) ==1);}));
}

string print_whole(vector<string>names,int shift, int extra, int t)
{
    ostringstream os;
    for (int j=0; j<baselines; j++)
    {
        for (int k=0; k<db.size(); k++) db[k]=gdb[ind[k]++];
        for (int i=0; i<tasks[t].len(); i++) os << tasks[t].out[i] << names[ind[i]];
        os<<tasks[t].out[tasks[t].len()] <<endl;
    }


    os << names[extra] << " = 1" <<endl;
    return os.str();
}
/*
class var
{
public:
    int cur=0;
    dynamic_bitset<> * db;

}*/

int main()
{
    int t=0;
    populate_tasks();
    vector<string> names={"x1","x2","x3","x4", "x5", "y1", "y2", "y3","y4","y5","y6"};
    vector<int> orig_ind={0,1,2,6};
    vector<int> ind=orig_ind;
    int baselines=6;
    bool (*F)(dynamic_bitset<>)=tasks[t].val;
    int maxval=pow(2,names.size())-1;
    int shift=1;
    //bool (*G)(dynamic_bitset<>,int)=[](dynamic_bitset<> db, int s){return (bool)db[s];};

    set<int> sol_hist;
    for (int extra=0; extra<names.size(); extra++)
    {
        int solutions=0;

        for (int i=0; i<=maxval; i++)
        {
            bool solves=true;
            dynamic_bitset<> gdb{names.size(),i};
            dynamic_bitset<> db{ind.size(),i};
            //if (!G(gdb,extra)) continue;
            for (int j=0; j<baselines; j++)
            {
                for (int k=0; k<db.size(); k++) {db[k]=gdb[ind[k]];ind[k]+=shift;}
                if (!F(db)) {solves=false; break;}
            }
            if (solves) solutions++;
        }
        //if (sol_hist.find(solutions)==sol_hist.end())
        {
            cout << print_whole(names,shift,extra,t);
            cout << solutions <<endl;
            sol_hist.insert(solutions);
        }

    }


    return 0;
}
