#include <iomanip>
#include "person.hpp"
#include "searchers.hpp"
#include "tasks.hpp"

using namespace std;


uniform_int_distribution<> born(1950,1970);
uniform_int_distribution<> tid(1,10000);
struct person;
vector<person> pers;
int main()
{
    setlocale(LC_ALL, "Russian");


    /*pers.push_back(person(1,{18,22}));
    pers.push_back(person(-1,{5,6},born(mt)));
    pers.push_back(person(1,{5,7,8},born(mt)));
    pers.push_back(person(1,{6},born(mt)));
    pers.push_back(person(-1,{8},born(mt)));
    pers.push_back(person(-1,{15,16,17}));
    pers.push_back(person(-1,{}));
    pers.push_back(person(1,{}));
    pers.push_back(person(1,{14}));
    pers.push_back(person(-1,{11},born(mt)));
    pers.push_back(person(1,{11,23},born(mt)));
    pers.push_back(person(1,{13,16}));
    pers.push_back(person(-1,{13,21},born(mt)));
    pers.push_back(person(-1,{}));
    pers.push_back(person(1,{}));
    pers.push_back(person(-1,{20}));
    pers.push_back(person(1,{21}));
    pers.push_back(person(-1,{18,19}));
    pers.push_back(person(-1,{}));
    pers.push_back(person(1,{}));
    pers.push_back(person(-1,{22}));
    pers.push_back(person(-1,{}));
    pers.push_back(person(1,{}));
    pers.push_back(person(-1,{0,14}));*/
    ofstream ofs("data.txt");
for (int taski=0; taski<100; taski++)
{
    int errors=0;
    do
    {
        errors=0;
    pers.clear();
    pers.push_back(person(1,{}));
    pers.push_back(person(-1,{5,6,12},born(mt)));
    pers.push_back(person(1,{5,7,8},born(mt)));
    pers.push_back(person(1,{6}));
    pers.push_back(person(-1,{8},born(mt)));
    pers.push_back(person(-1,{15}));
    pers.push_back(person(-1,{}));
    pers.push_back(person(1,{}));
    pers.push_back(person(1,{14}));
    pers.push_back(person(-1,{3,11},born(mt)));
    pers.push_back(person(1,{0,11},born(mt)));
    pers.push_back(person(1,{13}));
    pers.push_back(person(-1,{13}));
    pers.push_back(person(-1,{14}));
    pers.push_back(person(1,{}));
    pers.push_back(person(-1,{0}));


    for (size_t i=0; i<pers.size(); i++)
    {
        for (auto j:pers[i].children)
            pers[j].parents.push_back(i);
    }
    for (size_t i=0; i<pers.size(); i++)
        pers[i].patronymic();

    /*for (auto i:pers){
            cout << i.name << ":";
            for (auto j:i.parents)
                cout << pers[j].name<<" ";
        cout << endl;
    }*/

    while(true)
    {
        bool added=false;
        for (size_t j=0; j<pers.size(); j++)
        {
            if (pers[j].byear==0){
                if (pers[j].parents.size()==1 and pers[pers[j].parents[0]].byear>0)
                {
                    pers[j].byear=dif(mt)+pers[pers[j].parents[0]].byear;
                    added=true;
                }
                if (pers[j].parents.size()==2 and pers[pers[j].parents[0]].byear>0 and pers[pers[j].parents[1]].byear>0)
                {
                    pers[j].byear=dif(mt)+max(pers[pers[j].parents[0]].byear, pers[pers[j].parents[1]].byear);
                    added=true;
                }
            }
        }
        if (!added) break;
    }
    errors=check();
    }
    while (errors>0);

    //generated successfully!

    vector<string>desc1,desc2;
    for (size_t i=0; i<pers.size(); i++){
        desc1.push_back(string("<tr><td>"+to_string(pers[i].id)+"</td><td>"+pers[i].to_str()+"</td><td>"+(pers[i].gender==-1?"М":"Ж")+"</td><td>"+to_string(pers[i].byear)+"</td></tr>"));
        for (auto j:pers[i].children)
            desc2.push_back(string("<tr><td>"+to_string(pers[j].id)+"</td><td>"+to_string(pers[i].id)+"</td></tr>"));
    }
    random_shuffle(desc1.begin(),desc1.end());
    random_shuffle(desc2.begin(),desc2.end());

    desc1.insert(desc1.begin(),"<table border=\"2\"><tr><th>ID</th><th>ФИО</th><th>пол</th><th>год рождения</th></tr>");
    desc1.push_back("</table><br>");
    desc2.insert(desc2.begin(), "<table border=\"2\"><tr><th>ID ребёнка</th><th>ID родителя</th></tr>");
    desc2.push_back("</table>");

    ofs << "<question type=\"shortanswer\">" << endl
                <<"<name>" << endl
                <<"<text>" << setw(2) << setfill('0')<<taski << "</text>" << endl
                <<"</name>" << endl
                <<"<questiontext format=\"html\">" << endl
                <<"<text><![CDATA[<p>";
    ofs << "Дан фрагмент базы данных:" <<endl;
    for (auto i:desc1) ofs<< i << endl;
    ofs << endl;
    for (auto i:desc2) ofs<< i << endl;
    int ans=pers[age_between_f(ofs)].id;
    ofs <<"</p>]]></text>" << endl
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
                <<"<text>"<<ans<< "</text>" << endl
                  <<"<feedback format=\"html\">"<<endl
                    <<"<text></text>" << endl
                  <<"</feedback>" << endl
                <<"</answer>" <<endl
              <<"</question>" <<endl <<endl;
}
/*
    auto a=parents(1);
    for (auto i:a)
        cout <<pers[i.first].id <<" " << pers[i.second].id<<endl;

    cout << endl;
    auto b=best_age(a,false);
    for (auto i:b)
        cout << pers[i].id << endl;
*/
    return 0;
}
