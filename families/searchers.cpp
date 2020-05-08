#include "includes.hpp"
#include "person.hpp"


//struct person;
//extern std::vector<person> pers;
int check()
{
    int errors=0;
    for (size_t i=0; i<pers.size(); i++)
    {
        for (size_t j=i+1;j<pers.size(); j++)
            if (i!=j and pers[i].id==pers[j].id)
                {
                    //cout << "FAIL: same id" <<endl;
                    errors++;
                }
        if (pers[i].parents.size()==2)
            if (pers[pers[i].parents[0]].gender==pers[pers[i].parents[1]].gender)
            {
                //cout << "FAIL: gay couple" <<endl;
        errors++;}
        ///possible checks: patronymic
        for (auto j:pers[i].parents)
        {
            if (pers[i].byear-pers[j].byear<18)
                {
                    //cout << "FAIL: too small age difference" <<endl;
                    errors++;}
            if (pers[i].byear-pers[j].byear>60)
            {
                //cout << "FAIL: too big age difference" <<endl;
                errors++;}
        }
    }
    return errors;
}

std::vector<std::pair<int,int>> parents(int g)
{
    std::vector<std::pair<int,int>> res;
    for (size_t i=0; i<pers.size(); i++) for (auto j:pers[i].parents) if (pers[j].gender==g) res.push_back(std::pair<int,int>(i,j));
    return res;
}
std::vector<std::pair<int,int>> fathers() {return parents(-1);}
std::vector<std::pair<int,int>> mothers() {return parents(1);}
std::vector<std::pair<int,int>> gparents(int g)
{
    std::vector<std::pair<int,int>> res;
    for (size_t i=0; i<pers.size(); i++)
    if (pers[i].gender==g)
        for (auto j:pers[i].children)
            for (auto l:pers[j].children)
                {
                    //cout << pers[i].id<<" "<< pers[j].id<<" "<< pers[l].id<<endl;
                res.push_back(std::pair<int,int>(l,i));
                }
    return res;

}
std::vector<std::pair<int,int>> gfathers() {return gparents(-1);}
std::vector<std::pair<int,int>> gmothers() {return gparents(1);}

std::vector<std::pair<int,int>> sibling(int g)
{
    std::vector<std::pair<int,int>> res;
    for (size_t i=0; i<pers.size(); i++)
    if (pers[i].gender==g)
        for (auto j:pers[i].parents)
            for (auto l:pers[j].children)
                {
                    if (l!=i){
                    //cout << pers[i].id<<" "<< pers[j].id<<" "<< pers[l].id<<endl;
                    res.push_back(std::pair<int,int>(l,i));}
                }
    return res;
}

std::vector<std::pair<int,int>> uncleaunt(int g)
{
    std::vector<std::pair<int,int>> res;
    for (size_t i=0; i<pers.size(); i++)
        if (pers[i].gender==g)
            for (auto j:pers[i].parents)
                for (auto k:pers[j].children)
                    if (k!=i)
                        for (auto l:pers[k].children)
                        {

                            //cout << pers[i].id<<" "<< pers[j].id<<" "<< pers[l].id<<endl;
                            res.push_back(std::pair<int,int>(l,i));
                        }
    return res;
}

std::vector<std::pair<int,int>> aunts() {return uncleaunt(1);}
std::vector<std::pair<int,int>> uncles() {return uncleaunt(-1);}

std::set<int> best_age(std::vector<std::pair<int,int>> p, bool youngest=true, bool scnd=true)
{
    int m=pers[(scnd?p[0].second:p[0].first)].byear-pers[(scnd?p[0].first:p[0].second)].byear;
    for (auto i:p)
    {
        int dif=pers[(scnd?i.second:i.first)].byear-pers[(scnd?i.first:i.second)].byear;
        if ((youngest and dif>m) or (!youngest and dif<m))
            m=dif;
    }
    std::set<int> res;
    for (auto i:p)
    {
        int dif=pers[(scnd?i.second:i.first)].byear-pers[(scnd?i.first:i.second)].byear;
        if (dif==m) res.insert((scnd?i.second:i.first));
    }
    return res;

}

std::set<int> most_often(std::vector<std::pair<int,int>> p, bool scnd=true)
{
    std::vector<int> freq(pers.size(),0);
    for (auto i:p)
        freq[(scnd?i.second:i.first)]++;
    int m=*max_element(freq.begin(),freq.end());
    std::set<int> res;
    for (size_t i=0; i<pers.size(); i++)
        if (freq[i]==m) res.insert(i);
    return res;
}

std::vector<std::pair<int,int>> age_by_birth(std::vector<std::pair<int,int>> p, int from, int to)
{
    std::vector<std::pair<int,int>> res;
    for (auto i:p)
    {
        if (((pers[i.first].byear-pers[i.second].byear)>=from or from==0) and (to==0 or (pers[i.first].byear-pers[i.second].byear)<=to))
            res.push_back(i);
    }
    return res;
}
