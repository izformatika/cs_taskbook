#include <ctime>
#include <map>
#include <random>
#include <iostream>
#include <sstream>
#include <fstream>
#include <clocale>
#include <set>

#define moodle false
#include "../../moodle_meta_cpp_functions/moodle_question.hpp"

using namespace std;

void g7_1_1_2_2_1(int task_qtty, ofstream &ofs, int solution_time=0)
{
    mt19937 mt(time(0));
    //uniform_int_distribution<> uid(0, 2);
    //uniform_int_distribution<> uid_1(8, 1023);
    set<int> ans;

    int done(0);
    //array<int,3> small_primes=[3,5,7];
    int users_qtty, pass_len,add_user_info, bits_per_symbol, alph_len;
    long long total_mem;
    for (users_qtty=16; users_qtty<=4096; users_qtty*=2)
    for (pass_len=8; pass_len<=20; pass_len++)
    for (add_user_info=4; add_user_info<=4096; add_user_info*=2)
    for (bits_per_symbol=3; bits_per_symbol<=7; bits_per_symbol++)
    {
        uniform_int_distribution<> uid(ceil(pow(2,bits_per_symbol-1)*1.5), floor(pow(2,bits_per_symbol)*0.8));
        alph_len=uid(mt);
        if (bits_per_symbol*pass_len % 8 == 0) continue;
        total_mem = (ceil((bits_per_symbol * pass_len)/8.0)*8 + add_user_info*8) * users_qtty;
        if (total_mem%8192>0 or total_mem < 8192) continue;
        total_mem/=8192;
        if (ans.find(int(total_mem))!=ans.end() or total_mem<32 or total_mem>256) continue;
        done++;
        ans.insert(total_mem);

        ostringstream task_txt;
        ostringstream answer_txt;
        task_txt << "В базе данных хранится информация о " << users_qtty << " пользовател" << (users_qtty%10 == 1 and users_qtty%100!=11?"е":"ях")<< " информационной системы. "
                <<"Длина пароля одинакова для всех пользователей и составляет " << pass_len << " символ" << (pass_len%10==1 and pass_len%100!=11?"":(pass_len%10>=2 and pass_len%10<=4 and (pass_len%100<11 or pass_len%100>14)?"а":"ов"))
                << ". Каждый символ пароля кодируется одинаковым минимально возможным количеством бит (единым для всех пользователей), а на весь пароль отводится минимально возможное целое количество байт. "
                << "Также для каждого пользователя зарезервировано " << add_user_info << " байт" << (add_user_info%10>=2 and add_user_info%10<=4 and (add_user_info%100<11 or add_user_info%100>14)?"а":"") << " дополнительной информации.<br/>" << endl
                << "Какой наименьший объём в Кбайт будет занимать информация обо всех пользователях в базе данных, если для пароля используется алфавит из "<<alph_len<<" символ"<<(alph_len%10==1 and alph_len%100!=11?"а":"ов")<<"?<br/><br/>" << endl
                <<"Примечание. 1 мебибайт - 1024 кибибайта, 1 кибибайт - 1024 байта. Это технически более корректные термины, чем 'килобайт' и 'мегабайт'. Приняты в 1999 году Международной электротехнической комиссией в стандарте IEC 60027-2, в России в ГОСТ 8.417-2002.";
            answer_txt << total_mem;

        #if moodle

        moodle_write_question(ofs,done,task_txt.str(), answer_txt.str());
        #else
        cout << task_txt.str() << endl <<answer_txt.str() <<endl;
        #endif
        if (done==task_qtty)
        {
            #if moodle
            ofs << "</quiz>" << endl;
            #endif
                return;
        }
    }
    #if moodle
    ofs << "</quiz>" << endl;
    #endif
}

void g7_3_2_1_1(int task_qtty, ofstream &ofs, int solution_time=0)
{
    mt19937 mt(time(0));
    set<int> ans;

    int done(0);
    array<int,3> small_primes={3,5,7};
    uniform_int_distribution<>uid1_10(1, 10);
    uniform_int_distribution<>uid0_2(0,2);
    uniform_int_distribution<>uid0_1(0,1);
    uniform_int_distribution<>uid1_16(1,16);
    uniform_int_distribution<>uid1_200(1,200);
    uniform_int_distribution<>uid_primes(0, small_primes.size()-1);
    while(done<task_qtty)
    {
        int t1(uid1_10(mt)*10);
        int ch1(pow(2, uid0_2(mt)));
        int freq1(uid1_16(mt)*2);
        int sz1(uid1_200(mt));
        double i1=double(sz1)/(t1*ch1*freq1*1000);
        if (((int(i1*1000))%10)==((int((i1*1000))%100)/10)) continue;//bits per symbol - too simple for a number

        int td(pow(2,uid0_2(mt)+1));
        int ch2;
        do{ ch2=pow(2, uid0_2(mt));}while(ch2==ch1);
        int freqd(pow(2,uid0_2(mt)+1));
        if(uid0_1(mt)==0) {td*=-1;freqd*=small_primes[uid_primes(mt)];}
        else {freqd*=-1;td*=small_primes[uid_primes(mt)];}

        int sz2=sz1;
        if (td<0) sz2/=-td;
        else sz2*=td;
        if (freqd<0) sz2/=-freqd;
        else sz2*=freqd;
        sz2=sz2/ch1*ch2;

        int chk=sz2;
        if (td<0) chk*=-td;
        else chk/=td;
        if (freqd<0) chk*=-freqd;
        else chk/=freqd;
        chk=chk/ch2*ch1;
        if (chk!=sz1) continue;//divisions spoiled the answer

        if (ans.find(int(sz2))!=ans.end()) continue;

        ostringstream task_txt;
        ostringstream answer_txt;
        map<int, string> channel_desc;
        channel_desc[1]= "моно (1 канал)";
        channel_desc[2]= "стерео (2 канала)";
        channel_desc[4]= "квадро (4 канала)";
        task_txt << "Звукозапись длительностью " << t1 << " секунд сохранили в формате " << channel_desc[ch1] << " с частотой дискретизации "
            << freq1 << " килогерц" << (freq1%10>=2 and freq1%10<=4 and (freq1%100<11 or freq1%100>15)?"а":"")
            << ". Размер файла оказался равным " << sz1 << " кибибайт" << (sz1%10==1 and sz1%100!=11?"у":"ам")
            << ". Сжатие данных не производилось, другой информации кроме звука в файле не было. Пользователь ";
        int t2;
        if (td<0) {task_txt << "скопировал фрагмент звукозаписи длительностью " ; t2=t1/(-td);}
        else {task_txt << "добавил к записи фрагмент длительностью "; t2=t1*td-t1; if (t2>t1/2) continue;}

        done++;
        ans.insert(sz2);

        int freq2((freqd<0?freq1/(-freqd):freq1*freqd));
        task_txt << t2 << " секунд" << (t2%10>=2 and t2%10<=4 and (t2%100<11 or t2%100>15)?"ы":"")
            << ", перекодировал его в формат " << channel_desc[ch2] << ", "
            << (freqd<0?"уменьшил":"увеличил") << " частоту дискретизации до " << freq2
            << " килогерц" << (freq2%10>=2 and freq2%10<=4 and (freq2%100<11 or freq2%100>15)?"а":"")
            << " и сохранил полученный результат в новом файле без сжатия данных и без дополнительных данных кроме звука. <br/>"
            << "Определите объём полученного файла в кибибайтах. В ответе укажите только число, округлённое до целых в большую сторону, без единиц измерения.<br/><br/>";
                task_txt <<"Примечание. 1 мебибайт - 1024 кибибайта, 1 кибибайт - 1024 байта. Это технически более корректные термины, чем 'килобайт' и 'мегабайт'. Приняты в 1999 году Международной электротехнической комиссией в стандарте IEC 60027-2, в России в ГОСТ 8.417-2002.";
            answer_txt << sz2;

        #if moodle

        moodle_write_question(ofs,done,task_txt.str(), answer_txt.str());
        #else
        cout << task_txt.str() << endl <<answer_txt.str() <<endl;
        #endif
        if (done==task_qtty)
        {
            #if moodle
            ofs << "</quiz>" << endl;
            #endif
                return;
        }
    }
    #if moodle
    ofs << "</quiz>" << endl;
    #endif
}


int factorial(int a)
{
    int ans(1);
    for (int i(2); i<=a; i++) ans*=i;
    return ans;
}
void g10_1_1(int task_qtty, ofstream &ofs, int solution_time=0)
{
    mt19937 mt(time(0));
    //uniform_int_distribution<> uid(0, 2);
    //uniform_int_distribution<> uid_1(8, 1023);
    set<int> ans;

    int done(0);
    //array<int,3> small_primes=[3,5,7];
    for (int devs_need=3; devs_need<=9; devs_need++)
    for (int people=devs_need+3; people<15; people++)
    {
        int res = people*factorial(people-1)/factorial(devs_need)/factorial(people-1-devs_need);
        if (res < 10 or res > 200 or ans.find(res)!=ans.end()) continue;
        done++;
        ans.insert(res);

        ostringstream task_txt;
        ostringstream answer_txt;
        task_txt << "Для работы над новым проектом из сотрудников отдела необходимо сформировать команду, состоящую из 1 тимлида и " << devs_need << " разработчиков. Запишите количество различных способов сформировать команду, если в отделе работает " << people << " человек. В ответе укажите только число. Примечание: в качестве тимлида может выступать любой сотрудник; команды, в которых состоят одни и те же сотрудники, но в которых позицию тимлида занимают разные люди, считаются разными командами.";
        #if moodle

        moodle_write_question(ofs,done,task_txt.str(), res);
        #else
        cout << task_txt.str() << endl <<res <<endl;
        #endif
        if (done==task_qtty)
        {
            #if moodle
            ofs << "</quiz>" << endl;
            #endif
                return;
        }
    }
    #if moodle
    ofs << "</quiz>" << endl;
    #endif
}

int main()
{
    ofstream ofs("data.txt");
    #if moodle
    moodle_header(ofs);
    #endif
    setlocale(LC_ALL,"Russian");

    //g10_1_1(50, ofs);
    g7_3_2_1_1(10, ofs);

    return 0;
}
