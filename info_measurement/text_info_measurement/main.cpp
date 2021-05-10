#include <ctime>
#include <random>
#include <iostream>
#include <sstream>
#include <fstream>
#include <clocale>
#include <set>

#define moodle true
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

void g10_1_1(int task_qtty, ofstream &ofs, int solution_time=0)
{

}

int main()
{
    #if moodle
    ofstream ofs("data.txt");
    moodle_header(ofs);
    #endif
    setlocale(LC_ALL,"Russian");

    g7_1_1_2_2_1(50, ofs);

    return 0;
}
