#include "person.hpp"
std::string snames[]={"��������", "�������", "��������", "��������", "�����", "�������", "��������", "�������", "����", "�������", "���������",
    "������������", "���������", "���������", "����������", "����", "�������", "�������", "��������", "�������", "������",
    "���������", "����������", "������", "��������", "�����", "�����", "������"};
std::string alphabet="��������������������";
std::mt19937 mt(time(0));
std::uniform_int_distribution<> genid(102,987);
std::uniform_int_distribution<> dif(18,25);
std::uniform_int_distribution<> d1(0,alphabet.size()-1);
void person::getid()
{
    while (true)
    {
        id=genid(mt);
        if (id%10==(id/10)%10 or id%10==id/100 or id/100==(id/10)%10) continue;
        bool found=false;
        for (auto i:pers)
            if (id==i.id) {found=true; break;}
        if (found) continue;
        break;
    }
}

void person::getname()
{
    sname=snames[d1(mt)];
    if (gender==1) {gender_bender();}
    name=alphabet[d1(mt)];

}
