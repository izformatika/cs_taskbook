#include <iostream>
#include <vector>
#include "person.hpp"
#include "searchers.hpp"

std::uniform_int_distribution<> dif_1(20,60);
int youngest_mom(std::ostream &fs)
{
    int res=-1;
    auto a=mothers();
    auto b=best_age(a);
    if (b.size()==1) res=*b.begin();
    else
    {
        res=*b.begin();
        for (size_t i=0; i<b.size(); i++)
            if (pers[res].id>pers[i].id) res=i;
    }
    fs << "Укажите ID женщины, у которой первый ребёнок появился в самом раннем возрасте. Если таких людей несколько, укажите наименьший ID." << std::endl;

    return res;
}

int oldest_mom(std::ostream &fs)
{
    int res=-1;
    auto a=mothers();
    auto b=best_age(a,false);
    if (b.size()==1) res=*b.begin();
    else
    {
        res=*b.begin();
        for (size_t i=0; i<b.size(); i++)
            if (pers[res].id>pers[i].id) res=i;
    }
    fs << "Укажите ID женщины, у которой последний ребёнок появился в самом позднем возрасте. Если таких людей несколько, укажите наименьший ID." << std::endl;

    return res;
}

int youngest_dad(std::ostream &fs)
{
    int res=-1;
    auto a=fathers();
    auto b=best_age(a);
    if (b.size()==1) res=*b.begin();
    else
    {
        res=*b.begin();
        for (size_t i=0; i<b.size(); i++)
            if (pers[res].id>pers[i].id) res=i;
    }
    fs << "Укажите ID мужчины, у которого первый ребёнок появился в самом раннем возрасте. Если таких людей несколько, укажите наименьший ID." << std::endl;

    return res;
}

int oldest_dad(std::ostream &fs)
{
    int res=-1;
    auto a=fathers();
    auto b=best_age(a,false);
    if (b.size()==1) res=*b.begin();
    else
    {
        res=*b.begin();
        for (size_t i=0; i<b.size(); i++)
            if (pers[res].id>pers[i].id) res=i;
    }
    fs << "Укажите ID мужчины, у которого последний ребёнок появился в самом позднем возрасте. Если таких людей несколько, укажите наименьший ID." << std::endl;

    return res;
}

int youngest_gmom(std::ostream &fs)
{
    int res=-1;
    auto a=gmothers();
    auto b=best_age(a);
    if (b.size()==1) res=*b.begin();
    else
    {
        res=*b.begin();
        for (size_t i=0; i<b.size(); i++)
            if (pers[res].id>pers[i].id) res=i;
    }
    fs << "Укажите ID женщины, у которой первый внук/внучка появился в самом раннем возрасте. Если таких людей несколько, укажите наименьший ID." << std::endl;

    return res;
}

int oldest_gmom(std::ostream &fs)
{
    int res=-1;
    auto a=gmothers();
    auto b=best_age(a,false);
    if (b.size()==1) res=*b.begin();
    else
    {
        res=*b.begin();
        for (size_t i=0; i<b.size(); i++)
            if (pers[res].id>pers[i].id) res=i;
    }
    fs << "Укажите ID женщины, у которой последний внук/внучка появилась в самом позднем возрасте. Если таких людей несколько, укажите наименьший ID." << std::endl;

    return res;
}

int youngest_gdad(std::ostream &fs)
{
    int res=-1;
    auto a=gfathers();
    auto b=best_age(a);
    if (b.size()==1) res=*b.begin();
    else
    {
        res=*b.begin();
        for (size_t i=0; i<b.size(); i++)
            if (pers[res].id>pers[i].id) res=i;
    }
    fs << "Укажите ID мужчины, у которого первый внук/внучка появился в самом раннем возрасте. Если таких людей несколько, укажите наименьший ID." << std::endl;

    return res;
}

int oldest_gdad(std::ostream &fs)
{
    int res=-1;
    auto a=gfathers();
    auto b=best_age(a,false);
    if (b.size()==1) res=*b.begin();
    else
    {
        res=*b.begin();
        for (size_t i=0; i<b.size(); i++)
            if (pers[res].id>pers[i].id) res=i;
    }
    fs << "Укажите ID мужчины, у которого последний внук/внучка появился в самом позднем возрасте. Если таких людей несколько, укажите наименьший ID." << std::endl;

    return res;
}

int most_gchildren_m(std::ostream &fs)
{
    int res=-1;
    auto a=gfathers();
    auto b=most_often(a);
    if (b.size()==1) res=*b.begin();
    else
    {
        res=*b.begin();
        for (size_t i=0; i<b.size(); i++)
            if (pers[res].id>pers[i].id) res=i;
    }
    fs << "Укажите ID мужчины, у которого в этом фрагменте перечислено больше всего внуков и внучек. Если таких людей несколько, укажите наименьший ID." << std::endl;

    return res;
}


int most_gchildren_f(std::ostream &fs)
{
    int res=-1;
    auto a=gmothers();
    auto b=most_often(a);
    if (b.size()==1) res=*b.begin();
    else
    {
        res=*b.begin();
        for (size_t i=0; i<b.size(); i++)
            if (pers[res].id>pers[i].id) res=i;
    }
    fs << "Укажите ID женщины, у которой в этом фрагменте перечислено больше всего внуков и внучек. Если таких людей несколько, укажите наименьший ID." << std::endl;

    return res;
}

int youngest_aunt(std::ostream &fs)
{
    int res=-1;
    auto a=aunts();
    auto b=best_age(a);
    if (b.size()==1) res=*b.begin();
    else
    {
        res=*b.begin();
        for (size_t i=0; i<b.size(); i++)
            if (pers[res].id>pers[i].id) res=i;
    }
    fs << "Укажите ID женщины, у которой появился родной племянник/родная племянница в самом раннем возрасте. Если таких людей несколько, укажите наименьший ID." << std::endl;

    return res;
}

int oldest_aunt(std::ostream &fs)
{
    int res=-1;
    auto a=aunts();
    auto b=best_age(a,false);
    if (b.size()==1) res=*b.begin();
    else
    {
        res=*b.begin();
        for (size_t i=0; i<b.size(); i++)
            if (pers[res].id>pers[i].id) res=i;
    }
    fs << "Укажите ID женщины, у которой появился родной племянник/родная племянница в самом позднем возрасте. Если таких людей несколько, укажите наименьший ID." << std::endl;

    return res;
}

int youngest_uncle(std::ostream &fs)
{
    int res=-1;
    auto a=uncles();
    auto b=best_age(a);
    if (b.size()==1) res=*b.begin();
    else
    {
        res=*b.begin();
        for (size_t i=0; i<b.size(); i++)
            if (pers[res].id>pers[i].id) res=i;
    }
    fs << "Укажите ID мужчины, у которого появился родной племянник/родная племянница в самом раннем возрасте. Если таких людей несколько, укажите наименьший ID." << std::endl;

    return res;
}

int oldest_uncle(std::ostream &fs)
{
    int res=-1;
    auto a=uncles();
    auto b=best_age(a,false);
    if (b.size()==1) res=*b.begin();
    else
    {
        res=*b.begin();
        for (size_t i=0; i<b.size(); i++)
            if (pers[res].id>pers[i].id) res=i;
    }
    fs << "Укажите ID мужчины, у которого появился родной племянник/родная племянница в самом позднем возрасте. Если таких людей несколько, укажите наименьший ID." << std::endl;

    return res;
}
int age_between_f(std::ostream &fs)
{
    auto a=mothers();
    std::vector<std::pair<int,int>> d;
    int age_f,age_t;
    do{
    int b=dif_1(mt), c=dif_1(mt);
    age_f=std::min(b,c);
    age_t=std::max(b,c);
    d=age_by_birth(a,age_f,age_t);
    }while (d.size()<2 or d.size()>=(a.size()*0.75));
    /*std::cout << age_f <<" "<<age_t<<std::endl;
    for (auto i:d) std::cout << pers[i.first].id <<" "<<pers[i.second].id <<std::endl;
    std::cout << std::endl;*/
    int res=d[0].first;
    for (auto i:d) if (pers[i.first].id<pers[res].id) res=i.first;
    fs << "Укажите ID такого человека, что на момент его рождения его матери было от "<<age_f<<(age_f%10==1?" полного года":" полных лет")<<" включительно до " << age_t<<(age_t%10==1?" полного года":" полных лет") << " включительно. Месяцем и днём можно пренебречь - считайте, что все люди родились в один день. Если таких людей несколько, укажите наименьший ID." << std::endl;
    return res;
}
int age_between_m(std::ostream &fs)
{
    auto a=fathers();
    std::vector<std::pair<int,int>> d;
    int age_f,age_t;
    do{
    int b=dif_1(mt), c=dif_1(mt);
    age_f=std::min(b,c);
    age_t=std::max(b,c);
    d=age_by_birth(a,age_f,age_t);
    }while (d.size()<2 or d.size()>=(a.size()*0.75));
    /*std::cout << age_f <<" "<<age_t<<std::endl;
    for (auto i:d) std::cout << pers[i.first].id <<" "<<pers[i.second].id <<std::endl;
    std::cout << std::endl;*/
    int res=d[0].first;
    for (auto i:d) if (pers[i.first].id<pers[res].id) res=i.first;
    fs << "Укажите ID такого человека, что на момент его рождения его отцу было от "<<age_f<<(age_f%10==1?" полного года":" полных лет")<<" включительно до " << age_t<<(age_t%10==1?" полного года":" полных лет") << " включительно. Месяцем и днём можно пренебречь - считайте, что все люди родились в один день. Если таких людей несколько, укажите наименьший ID." << std::endl;
    return res;
}
int exact_descendants_age(std::ostream &fs)
{
    using std::cout; using std::endl;
    int res=-1;
    int res_desc = -1;
    int age = (std::uniform_int_distribution<>(40, 80))(mt);
    for (int i=0;i<pers.size(); i++)
    {
    auto a=descendants(i, age);
    if (a.size() > res_desc) {res = i; res_desc = a.size();}
    else if (a.size() == res_desc and res > i) res = i;
    }
    fs << "Укажите ID человека, у которого в этом фрагменте родилось больше всего потомков к моменту достижения им " << age << (age%10==1?" года":" лет") << ". Если таких людей несколько, укажите наименьший ID." << std::endl;
    return res;
}
