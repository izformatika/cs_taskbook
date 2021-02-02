#ifndef PERSON_HPP_INCLUDED
#define PERSON_HPP_INCLUDED
#include "includes.hpp"

extern std::string alphabet;
extern std::string snames[];
extern std::mt19937 mt;
extern std::uniform_int_distribution<> genid;
extern std::uniform_int_distribution<> dif;
extern std::uniform_int_distribution<> d1;
struct person;
extern std::vector<person> pers;
extern bool rand_fname;
struct person
{
int id;
int gender;
std::string to_str(){return sname+" "+name+"."+patr+".";}
std::string sname;
char name;
char patr;
void getid();
void getname();
void patronymic()
{
    //std::cout << to_str() << ">>"<<parents.size() <<std::endl;
    if (parents.size()==0) {patr=alphabet[d1(mt)];/*cout<<"0:"<<patr<<endl;*/return;}
    for (auto i:parents)
    {
        if (pers[i].gender==-1) {patr=pers[i].name;if(!rand_fname) {sname = pers[i].sname;}/*cout<<"father:"<<patr<<endl;*/return;}
    }
    patr=alphabet[d1(mt)];

}
void gender_bender()
{
    //std::cout << sname << std::endl;
if (gender==1 and (sname[sname.size()-1]=='í' or sname[sname.size()-1]=='â')) {sname=sname+"à";}
if (gender==-1 and sname[sname.size()-1]=='à') {sname=sname.substr(0,sname.size()-1);}
}
person(int g,std::vector<int> c,int y=0):gender(g),children(c),byear(y),id(0),name('Û'),patr('Ú'){getname(); getid();}
std::vector<int> children;
std::vector<int> parents;
int byear;
};

#endif
