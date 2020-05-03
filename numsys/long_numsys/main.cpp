#include <algorithm>
#include <iomanip>
#include <fstream>
#include <time.h>
#include <cstdlib>
#include "longnum.hpp"
#define moodle true

using namespace std;


//TODO: argebraic graph tree, repositioning, common multipliers

void direct_gen_pair(longnum& afrom, longnum& ato, int lvl=0, int split=true)
{//TODO: 8 - 16; 4-8,4-32,8-32,16-32,
    vector<vector<int> > collection;
    if (lvl==0)//склеить/разделить 0
    {
        collection.push_back({2,8,23});
        collection.push_back({2,16,23});
    }
    else if (lvl==1)//посредник 0
    {
    collection.push_back({8,16,7});
    collection.push_back({4,8,11});
    }
    else if (lvl==2)//склеить/разделить 1
    {
        collection.push_back({2,4,23});
        collection.push_back({3,9,23});
        collection.push_back({4,16,17});
    }
    else if (lvl==3)//склеить/разделить 2
    {
        collection.push_back({2,32,23});
        collection.push_back({3,27,19});
        collection.push_back({5,25,11});
    }
    else if (lvl==4)//посредник 1
    {
        collection.push_back({4,32,11});
        collection.push_back({8,32,7});
        collection.push_back({16,32,6});
        collection.push_back({9,27,11});
    }
    int choice=rand()%collection.size();
    int base_from=collection[choice][(split?1:0)];
    int base_to=collection[choice][(split?0:1)];

    afrom=longnum("",base_from);
    ato=longnum("",base_to);
    float r=log(collection[choice][1])/log(collection[choice][0]);
    if (floor(r)==r)
    {
        afrom.rand_digs((split?collection[choice][2]/r:collection[choice][2]));
        ato.direct(afrom);
    }
    else
    {
        //lvls 1 or 4, need medium
        int medium_base=1;
        for (int i=2; i<=5; i++)
        {
            float r1=log(base_from)/log(i);
            float r2=log(base_to)/log(i);
            if (floor(r1)==r1 and floor(r2)==r2) {medium_base=i;break;}
        }
        if (medium_base==1)
        {cerr << "cannot find common base for " << base_from << " and " << base_to <<", direct conversion impossible, exiting" <<endl; return;}
        longnum med_num("",medium_base);
        int digs=collection[choice][2]*log(collection[choice][0])/log(medium_base);
        //cout << digs <<endl;
        med_num.rand_digs(digs);
        afrom.direct(med_num);
        ato.direct(med_num);
    }
}

void direct_between()
{//TODO: students can cheat and convert only lowest digits. then well have to harden the task.
    //pick a medium base. generate a number, make a copy, decrement two digits on positions a and b. convert original number and modified to target bases. there's base^a+base^b-1 numbers between them. answer: a+b.
    //the question verbalization would be rather complicated though
    int tasks=50;
    int lvl=4;
    #if moodle
    ofstream ofs("direct_between_"+to_string(lvl)+".txt");
    #endif


    for (int i=0; i<tasks; i++)
    {
        longnum ato("",2);
        longnum afrom("",2);
        direct_gen_pair(afrom,ato,lvl);
        int ans_dec=rand()%30+20;
        longnum ans(ans_dec+1, ato.base());
        ato=ato+ans;
        #if moodle
            ofs << "<question type=\"shortanswer\">" << endl
                <<"<name>" << endl
                <<"<text>" << setw(2)<<setfill('0')<< i << "</text>" << endl
                <<"</name>" << endl
                <<"<questiontext format=\"html\">" << endl
                <<"<text><![CDATA[<p>Сколько чисел находится между \\(" << afrom.str() << "_{" << afrom.base()
                <<"}\\) и \\("<<ato.str()<<"_{" << ato.base() <<"}\\), исключая сами эти числа? Ответ дайте в десятичной системе счисления, основание указывать не надо.</p>]]></text>" << endl
                <<"</questiontext>" << endl
                <<"<generalfeedback format=\"html\">" << endl
                <<"<text></text>" << endl
                <<"</generalfeedback>" << endl
                <<"<defaultgrade>1.0000000</defaultgrade>" << endl
                <<"<penalty>0.3333333</penalty>" << endl
                <<"<hidden>0</hidden>" << endl
                <<"<idnumber></idnumber>" << endl
                <<"<usecase>0</usecase>" << endl
                <<"<answer fraction=\"100\" format=\"moodle_auto_format\">" << endl
                <<"<text>" << ans_dec << "</text>" << endl
                  <<"<feedback format=\"html\">"<<endl
                    <<"<text></text>" << endl
                  <<"</feedback>" << endl
                <<"</answer>" <<endl
              <<"</question>" <<endl;
        #else
        cout << afrom.str() <<"_"<<afrom.base() << " to " << ato.str() << "_"<<ato.base() << ": " << ans_dec<<endl;
        #endif
    }

}

void direct_conversion()
{
    int tasks=50;
    int lvl=4;
    bool split=false;//2->4 or 4->2
    #if moodle
    string fname="direct_";
    fname+=(split?"split":"merge");
    fname+="_"+to_string(lvl)+".txt";
    ofstream ofs(fname);
    #endif


    for (int i=0; i<tasks; i++)
    {
        longnum ato("",2);
        longnum afrom("",2);
        direct_gen_pair(afrom,ato,lvl,split);
        #if moodle
            ofs << "<question type=\"shortanswer\">" << endl
                <<"<name>" << endl
                <<"<text>" << setw(2)<<setfill('0')<< i << "</text>" << endl
                <<"</name>" << endl
                <<"<questiontext format=\"html\">" << endl
                <<"<text><![CDATA[<p>Переведите число \\(" << afrom.str() << "_{" << afrom.base()
                <<"}\\) в систему счисления с основанием \\(" << ato.base() << "\\). Основание в ответе указывать не надо, только цифры числа.</p>]]></text>" << endl
                <<"</questiontext>" << endl
                <<"<generalfeedback format=\"html\">" << endl
                <<"<text></text>" << endl
                <<"</generalfeedback>" << endl
                <<"<defaultgrade>1.0000000</defaultgrade>" << endl
                <<"<penalty>0.3333333</penalty>" << endl
                <<"<hidden>0</hidden>" << endl
                <<"<idnumber></idnumber>" << endl
                <<"<usecase>0</usecase>" << endl
                <<"<answer fraction=\"100\" format=\"moodle_auto_format\">" << endl
                <<"<text>" << ato.str() << "</text>" << endl
                  <<"<feedback format=\"html\">"<<endl
                    <<"<text></text>" << endl
                  <<"</feedback>" << endl
                <<"</answer>" <<endl
              <<"</question>" <<endl;
        #else
        cout << afrom.str() <<"_"<<afrom.base() << " to " << ato.str() << "_"<<ato.base() <<endl;
        #endif
    }

}


int main()
{
    srand(time(0));
    //numbers_between();
    direct_between();
    //direct_conversion();
    //what_base();
}
