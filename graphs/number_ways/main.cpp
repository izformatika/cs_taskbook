#include <iostream>
#include <fstream>
#include <algorithm>
#include <conio.h>
#include <vector>
#include <random>
#include <ctime>
#include "moodle_texts.hpp"
#define moodle false
using namespace std;

string alphabet="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
mt19937 mt(time(0));
uniform_int_distribution<> letter(0,alphabet.size());
class vertex;
vector<vertex> graph;

class vertex
{
public:
    char label;
    vector<int> to;
    vector<int> from;
    vertex(char l, vector<int>t):label(l),to(t){};
    vector<vector<int>> ways;
    bool finished=false;
};

void show_ways()
{
    for (size_t k=0; k<graph.size(); k++)
    {
        cout << "[" << graph[k].label<<"]:"<<graph[k].ways.size() <<endl;
        for (auto l:graph[k].ways)
        {
            for (auto m:l)
                cout << graph[m].label<< " ";
            cout << endl;
        }
        cout <<endl;
    }
    getch();
}

void populate()
{
    for  (size_t i=0; i<graph.size(); i++)
    {
        for (auto j: graph[i].to)
            graph[j].from.push_back(i);
        /*while (true)
        {
            bool found=false;
            graph[i].label=alphabet[letter(mt)];
            for (auto j:graph)
                if (j.label==graph[i].label) {found=true;break;}
            if (!found) break;
        }*/
    }
}

void append_and_send(int obj)
{
    for (int i=0; i<graph[obj].ways.size(); i++)
    {
        graph[obj].ways[i].push_back(obj);
        for (auto j:graph[obj].to)
        {
            graph[j].ways.push_back(graph[obj].ways[i]);
        }
    }
    graph[obj].finished=true;
}

void ways(int start)
{
    for (size_t i=0; i<graph.size(); i++){graph[i].ways.clear(); graph[i].finished=false;}
    graph[start].ways.push_back(vector<int>{});
    //show_ways();
    append_and_send(start);
    //show_ways();
    bool added=true;
    while (added)
    {
        added=false;
        for (size_t i=0; i<graph.size(); i++)
        {
            if (graph[i].finished==false)
            {
                bool ready=true;
                for (auto j:graph[i].from)
                {
                    if (!graph[j].finished) {ready=false;break;}
                }
                if (ready)
                {
                    //cout << "sending " <<graph[i].label << endl;
                    append_and_send(i);
                    added=true;
                    //show_ways();
                }
            }
        }
    }
}

vector<vector<int>> filter(vector<vector<int>> where, vector<int> what, bool has=true/*true - has, false - avoids*/)
{
    vector<vector<int>> res;
    for (size_t i=0; i<where.size(); i++)
    {
        int gotem=0;
        for (auto j:where[i])
            for (auto k:what)
                if (j==k) gotem++;
        if (gotem==(has?what.size():0)) res.push_back(where[i]);
    }
    return res;
}

int picno=0;
void init_graph_1()
{
    picno=1;
    graph.push_back(vertex('A', vector<int>{1,4}));
    graph.push_back(vertex('B', vector<int>{2,7,12}));
    graph.push_back(vertex('C', vector<int>{11}));
    graph.push_back(vertex('D', vector<int>{2,14,11}));
    graph.push_back(vertex('E', vector<int>{2,12}));
    graph.push_back(vertex('F', vector<int>{2,6,9}));
    graph.push_back(vertex('G', vector<int>{9,13}));
    graph.push_back(vertex('H', vector<int>{4,10}));
    graph.push_back(vertex('I', vector<int>{3,5,12,14}));
    graph.push_back(vertex('J', vector<int>{13}));
    graph.push_back(vertex('K', vector<int>{3,4,8}));
    graph.push_back(vertex('L', vector<int>{9,13}));
    graph.push_back(vertex('M', vector<int>{5,6}));
    graph.push_back(vertex('N', vector<int>{}));
    graph.push_back(vertex('O', vector<int>{6}));
}






void init_graph_2()
{
    picno=2;
    graph.push_back(vertex('A', vector<int>{1,4}));
    graph.push_back(vertex('B', vector<int>{2,4,9,3}));
    graph.push_back(vertex('C', vector<int>{10,11}));
    graph.push_back(vertex('D', vector<int>{5}));
    graph.push_back(vertex('E', vector<int>{2,9}));
    graph.push_back(vertex('F', vector<int>{4,6,8}));
    graph.push_back(vertex('G', vector<int>{2,4,7,8,9,10}));
    graph.push_back(vertex('H', vector<int>{2,13}));
    graph.push_back(vertex('I', vector<int>{7,11,15}));
    graph.push_back(vertex('J', vector<int>{2,10}));
    graph.push_back(vertex('K', vector<int>{12,13,15}));
    graph.push_back(vertex('L', vector<int>{12,14}));
    graph.push_back(vertex('M', vector<int>{14}));
    graph.push_back(vertex('N', vector<int>{12,14,15}));
    graph.push_back(vertex('O', vector<int>{}));
    graph.push_back(vertex('P', vector<int>{14}));
}


void init_graph_3()
{
    picno=3;
    graph.push_back(vertex('A', vector<int>{1,2,4}));
    graph.push_back(vertex('B', vector<int>{2,6,7}));
    graph.push_back(vertex('C', vector<int>{3,5,6}));
    graph.push_back(vertex('D', vector<int>{4,5}));
    graph.push_back(vertex('E', vector<int>{5,8,11}));
    graph.push_back(vertex('F', vector<int>{6,7,9}));
    graph.push_back(vertex('G', vector<int>{10,11,14}));
    graph.push_back(vertex('H', vector<int>{6,14}));
    graph.push_back(vertex('I', vector<int>{7,9,14}));
    graph.push_back(vertex('J', vector<int>{11}));
    graph.push_back(vertex('K', vector<int>{11,12}));
    graph.push_back(vertex('L', vector<int>{13}));
    graph.push_back(vertex('M', vector<int>{11,13,14}));
    graph.push_back(vertex('N', vector<int>{14}));
    graph.push_back(vertex('O', vector<int>{}));
}
enum tasktypes {both_or_neither,one_or_another};
int main()
{/*
    graph.push_back(vector<int>{1,2,3});
    graph.push_back(vector<int>{2,3});
            graph.push_back(vector<int>{3});
    graph.push_back(vector<int>{});
    */
    #if moodle
    ofstream fs("data.txt");
    #endif

    tasktypes type=both_or_neither;
    init_graph_2();
    populate();
    for (size_t from=0; from<graph.size(); from++)
    {
        //cout << "================="<<endl<<"from " <<from << endl;
//        cout << "WAYS " << graph[3].ways.size() <<endl;
        ways(from);

//        cout << "WAYS " << graph[3].ways.size() <<endl;
        for (size_t to=0; to<graph.size(); to++)
        {
            //cout << "to " <<to<< endl;
            if (from!=to and graph[to].ways.size()>20)
            {
                for (size_t a=0; a<graph.size(); a++)
                    for (size_t b=a+1; b<graph.size(); b++)
                        {
                            if (a!=from and a!=to and b!=from and b!=to)
                            {
                                if (type==both_or_neither)
                                {
                                    auto r=filter(graph[to].ways,{a,b},true);
                                    auto q=filter(graph[to].ways,{a,b},false);
                                    if (r.size()>=7 and r.size()<=20 and q.size()>=7 and q.size()<=20 and r.size()+q.size()>20)
                                    {
                                        #if moodle
                                            fs << txts[0] << graph[from].label << graph[to].label << " both " << graph[a].label << graph[b].label;
                                            fs << txts[1] << "Сколькими способами можно попасть из вершины "<<graph[from].label << " в вершину "<<graph[to].label << ", если по рёбрам можно двигаться только в направлениях, указанных стрелками, и при этом путь должен либо содержать обе вершины "<<graph[a].label << " и "<<graph[b].label << ", либо не содержать ни одну из них?";
                                            fs << txts[2] << pics[picno] << txts[3] << r.size() + q.size() << txts[4] <<endl <<endl;
                                        #else
                                            cout << graph[from].label << "->" << graph[to].label << " with both " << graph[a].label << ", " << graph[b].label << " - " << r.size() <<", without both - " << q.size() <<", total " << r.size()+q.size()<<endl;
                                        #endif
                                    }
                                }

                                else
                                if (type==one_or_another)
                                {
                                    auto r=filter(filter(graph[to].ways,{a},true),{b},false);
                                    auto q=filter(filter(graph[to].ways,{b},true),{a},false);
                                    if (r.size()>=7 and r.size()<=20 and q.size()>=7 and q.size()<=20 and r.size()+q.size()>20)
                                    {
                                        #if moodle
                                            fs << txts[0] << graph[from].label << graph[to].label << " xor " << graph[a].label << graph[b].label;
                                            fs << txts[1] << "Сколькими способами можно попасть из вершины "<<graph[from].label << " в вершину "<<graph[to].label << ", если по рёбрам можно двигаться только в направлениях, указанных стрелками, и при этом путь должен либо содержать вершину "<<graph[a].label << ", либо содержать вершину "<<graph[b].label << ", но не обе вершины одновременно?";
                                            fs << txts[2] << pics[picno] << txts[3] << r.size() + q.size() << txts[4] <<endl <<endl;
                                        #else
                                        cout << graph[from].label << "->" << graph[to].label << " +" << graph[a].label << ", -" << graph[b].label << " - " << r.size() <<", reverse - " << q.size() <<", total " << r.size()+q.size()<<endl;
                                        #endif
                                    }
                                }
                            }

                        }


            }
        }
    }
    //ways(12);
    //cout << graph[14].ways.size() <<endl;
    //for (size_t g=0; g<graph.size(); g++) {cout << g <<":"<<endl;for (auto i:graph[g].ways) {for (auto j:i) cout << j <<" ";cout<<endl;}}
    return 0;
}
