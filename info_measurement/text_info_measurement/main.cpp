#include <ctime>
#include <map>
#include <random>
#include <iostream>
#include <sstream>
#include <fstream>
#include <clocale>
#include <set>
#include <cmath>
#include <algorithm>
#define uid uniform_int_distribution<>

#define moodle true
#include "../../moodle_meta_cpp_functions/moodle_question.hpp"

using namespace std;
mt19937 mt;
string alphabet("абвгдеёжзийклмнопрстуфхцчшщъыьэюя");

void no_adj_letters()
{
    ifstream ifs("vow 2 cons 3 spec 1.txt");
    string cur_word;
    while (!ifs.eof())
    {
        ifs >> cur_word;
        bool bad(false);
        for (int i(0); i<cur_word.size() and !bad; i++)
        for (int j(i+1); j<cur_word.size() and !bad; j++)
            if (abs(int(alphabet.find(cur_word[i])-alphabet.find(cur_word[j])))<3) bad=true;
        if (bad) continue;
        cout << cur_word << endl;
    }
}

void all_adj_letters()
{
    ifstream ifs("vow 2 cons 3 spec 1.txt");
    string cur_word;
    int maxfar(13);
    while (!ifs.eof())
    {
        ifs >> cur_word;
        int far(0);
        for (int i(0); i<cur_word.size() and far<maxfar; i++)
        for (int j(i+1); j<cur_word.size() and far<maxfar; j++)
            if (abs(int(alphabet.find(cur_word[i])-alphabet.find(cur_word[j]))>=3)) far++;
        if (far>=maxfar) continue;
        cout << cur_word << endl;
    }
}

int min_dist(string wrd, char c)
{
    int res(wrd.size());
    for (auto i:wrd)
        res=min(res, abs(int(alphabet.find(c)-alphabet.find(i))));
    return res;
}
string encode(string src, int a, int c)
{
    string res;
    int nlet(0);
    for (auto i: src)
    {
        nlet = (a*(alphabet.find(i)+1)+c)%33+1;
        //cout << i << ":" <<(alphabet.find(i)+1)<<":"<< nlet << ' ';
        res+=alphabet[nlet-1];
    }
    //cout << endl;
    return res;
}
void g8_1_1_2(int task_qtty, ofstream &ofs, int solution_time=0)
{
//    if (solution_time!=5 and solution_time!=8) return;
    vector<string> words;
  //  if (solution_time == 5)
        words={"альбом", "голень", "гоньба", "деньга", "дизель", "ельник", "жердьё", "залежь", "комель", "копань", "линька", "лопарь", "модель", "мозель", "мольба", "мольва", "мораль", "морель", "мотыль", "мыльня", "нельма", "немочь", "немощь", "никель", "носарь", "обсыпь", "охрипь", "пароль", "письмо", "полынь", "помесь", "портье", "порубь", "потесь", "сеньор", "синьор", "сухарь", "участь", "юность", "ярость"};
  //  else//it doesnt give anything, given consecutive source letters the encoded letters will not be consecutive anyway
  //      words = {"курьёз", "лазурь", "лошадь", "льгота", "марьяж", "объект", "отбель", "память", "печать", "пищаль", "платье", "разъём", "рубель", "сальдо", "сафьян", "сельцо", "сольца", "тильда", "тканьё", "фасоль", "фильер", "фольга", "чекань", "шпильё", "щёголь", "щитень"};
    vector<int> primes = {7, 11, 13, 17, 19, 23, 29, 31};
    int done(0);
    int max_attempts(1000);
    uniform_int_distribution<> uid_words(0, words.size()-1);
    uniform_int_distribution<> uid_primes(0, primes.size()-1);
    set<string> ans;
    stringstream task_txt;
    while (max_attempts--)
    {
        int a(0), c(0);
        string tgt_word(words[uid_words(mt)]);

        do
        {
        a = primes[uid_primes(mt)];
        c = primes[uid_primes(mt)];
        }
        while (a==c);

        char let('я');
        while (let>='а' and min_dist(tgt_word, let)<4) let--;
        if (let<'а') {/*clog << tgt_word << endl; */continue;}//all letters too close, cannot find a hint that wouldnt make task too easy
        //cout << tgt_word << " [" << let << "]" << endl;
        string res_word(encode(tgt_word, a, c));
        if (ans.find(res_word)!=ans.end()) continue;
        int wtfs(0);//encoding works like shit when a = 11 :) should either exclude 11 from a... or force this shit to happen to make students doubt themselves
        //also probably should enforce a*n <= 200 to ease manual calculations
        for (size_t i(0); i<tgt_word.size(); i++)
        for (size_t j(i+1); j<tgt_word.size(); j++)
            if ((tgt_word[i]==tgt_word[j]) != (res_word[i]==res_word[j])) wtfs++;
        if (wtfs == 0) continue;
        ans.insert(res_word);
        task_txt.str("");
        task_txt << a << " " << c << endl;
        task_txt << "Для шифрования слов русского языка используется следующий метод. Каждая буква заменяется на букву, номер которой вычисляется по формуле"
            << " Xn = (q * N + p) % 33 + 1, где N - номер буквы по алфавиту, q и p - предопределённые коэффициенты, одинаковые для всего сеанса кодирования, и % - операция взятия остатка от деления. "
            << "<br><i>Например, если q = 3 и p = 4, то буква \"д\" будет заменяться буквой \"т\" ((3*5+4)%33+1 = 20), буква \"и\" - буквой \"б\" ((3*10+4)%33+1 = 2) etc."
            << "</i><br>Определите, как будет зашифровано слово \"" << tgt_word << "\", если q = " << a
            << ", а p вычисляется, если знать, что буква \"" << let << "\" заменяется на \"" << encode(string(1, let), a, c) << "\". В ответе укажите шифрованный текст в нижнем регистре."
            << "<br><br>Русский алфавит с порядковыми номерами для справки:<br><table>"
            << "<tr><td>1: а</td><td>&nbsp;&nbsp;</td><td>10: и</td><td>&nbsp;&nbsp;</td><td>19: с</td><td>&nbsp;&nbsp;</td><td>28: ъ </td></tr>" << endl
            << "<tr><td>2: б</td><td>&nbsp;&nbsp;</td><td>11: й</td><td>&nbsp;&nbsp;</td><td>20: т</td><td>&nbsp;&nbsp;</td><td>29: ы </td></tr>" << endl
            << "<tr><td>3: в</td><td>&nbsp;&nbsp;</td><td>12: к</td><td>&nbsp;&nbsp;</td><td>21: у</td><td>&nbsp;&nbsp;</td><td>30: ь </td></tr>" << endl
            << "<tr><td>4: г</td><td>&nbsp;&nbsp;</td><td>13: л</td><td>&nbsp;&nbsp;</td><td>22: ф</td><td>&nbsp;&nbsp;</td><td>31: э </td></tr>" << endl
            << "<tr><td>5: д</td><td>&nbsp;&nbsp;</td><td>14: м</td><td>&nbsp;&nbsp;</td><td>23: х</td><td>&nbsp;&nbsp;</td><td>32: ю </td></tr>" << endl
            << "<tr><td>6: е</td><td>&nbsp;&nbsp;</td><td>15: н</td><td>&nbsp;&nbsp;</td><td>24: ц</td><td>&nbsp;&nbsp;</td><td>33: я </td></tr>" << endl
            << "<tr><td>7: ё</td><td>&nbsp;&nbsp;</td><td>16: о</td><td>&nbsp;&nbsp;</td><td>25: ч</td><td>&nbsp;&nbsp;</td><td></td><td></td></tr>" << endl
            << "<tr><td>8: ж</td><td>&nbsp;&nbsp;</td><td>17: п</td><td>&nbsp;&nbsp;</td><td>26: ш</td><td>&nbsp;&nbsp;</td><td></td><td></td></tr>" << endl
            << "<tr><td>9: з</td><td>&nbsp;&nbsp;</td><td>18: р</td><td>&nbsp;&nbsp;</td><td>27: щ</td><td>&nbsp;&nbsp;</td><td></td></tr></table>" << endl;
        //cout << a << " " << c << " " << tgt_word << " " << encode(tgt_word, a, c) << endl;
        //cout << " " << let << " " << encode(string(1, let), a, c) << endl << endl;
//        cout<< task_txt.str();
        #if moodle
        moodle_write_question(ofs,done,task_txt.str(), res_word);
        #else
        cout << task_txt.str() << endl <<a << " " << c << endl <<res_word <<endl << endl;
        #endif
        done++;
        if (done==task_qtty)
        {
            break;
        }
    }
    #if moodle
    ofs << "</quiz>" << endl;
    #endif
    return;
}

void g8_1_1_1(int task_qtty, ofstream &ofs, int solution_time=5)
{
    if (solution_time < 4 or solution_time>5) return;
    vector<int> primes = {11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
    uid u(0, primes.size()-1);
    int max_attempts(1000);
    int done(0);
    vector<int> ans;
    while (max_attempts--)
    {
        int a, b, product;
        do
        {
            a = primes[u(mt)];
            b = primes[u(mt)];
            product = a*b;
        }
        while (not ((solution_time == 5 and (product%10 == 1 or product%10 == 9) and product > 300 and product < 600) or (solution_time == 4 and (product%10 == 7 or product%10 == 3) and product > 200 and product < 300)));
        if (find(ans.begin(), ans.end(), product)!=ans.end()) continue;
        ans.push_back(product);
        ostringstream task_txt;
        ostringstream answer_txt;
        task_txt << "В алгоритме RSA для формирования пары ключей вычисляется модуль – число n, являющееся произведением двух простых чисел p и q. "
        << "При этом как правило используются достаточно большие простые числа - до 2^2048. Модуль передаётся открыто и требуется для шифрования сообщений. Без знания исходных множителей (а подобрать их обычно сложно из-за большой величины модуля) расшифровать сообщение не получится. "
        << "\nВ некотором сеансе передачи данных с использованием RSA модуль n оказался преступно мал - его значение равно " << product
        << ". Проведите атаку на этот сеанс: определите единственно возможные исходные простые множители для данного модуля. В ответе укажите сумму этих множителей.";
        answer_txt << a+b;
        done++;
        #if moodle
        moodle_write_question(ofs,done,task_txt.str(), answer_txt.str());
        #else
        cout << task_txt.str() << endl <<answer_txt.str() <<endl << endl;
        #endif
        if (done==task_qtty)
        {
            break;
        }
    }
    #if moodle
    ofs << "</quiz>" << endl;
    #endif
        return;
}

void g7_1_1_2_2_1(int task_qtty, ofstream &ofs, int solution_time=0)
{
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
        uid u(ceil(pow(2,bits_per_symbol-1)*1.5), floor(pow(2,bits_per_symbol)*0.8));
        alph_len=u(mt);
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

void g06_03_02_01_01(int task_qtty, ofstream &ofs, int solution_time=0)
{
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
        if (freqd>0) sz2*=freqd;
        if (td>0) sz2*=td;//not else! have to make all multiplications  first!
        if (td<0) sz2/=-td;
        if (freqd<0) sz2/=-freqd;
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
        task_txt << "<i>Задание 06.03.02.01.01#" << done+1 << "</i></p><p>Звукозапись длительностью " << t1 << " секунд сохранили в формате " << channel_desc[ch1] << " с частотой дискретизации "
            << freq1 << " килогерц" << (freq1%10>=2 and freq1%10<=4 and (freq1%100<11 or freq1%100>15)?"а":"")
            << ". Размер файла оказался равным " << sz1 << " кибибайт" << (sz1%10==1 and sz1%100!=11?"у":"ам")
            << ". Использовался некоторый алгоритм сжатия данных, который предполагает равномерное кодирование, но разрядность кодирования не обязательно будет выражаться целым количеством бит. Другой информации кроме звуковой в файле не было. <br/>Пользователь ";
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
            << " и сохранил полученный результат в новом файле с использованием того же алгоритма сжатия с той же разрядностью и без дополнительных данных кроме звука. <br/>"
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

void g7_2_1_1_1(int task_qtty, ofstream &ofs, int solution_time=0)
{
    set<int> ans;

    int done(0);
    array<int,3> small_primes={3,5,7};
    array<array<int,2>, 9> aspect_ratios = {array<int, 2>{16, 9}, array<int, 2>{4, 3}, array<int, 2>{5, 4}, array<int, 2>{3, 2}, array<int, 2>{14, 9}, array<int, 2>{16, 10}, array<int, 2>{19, 9}, array<int, 2>{7, 3}, array<int, 2>{11, 4}};
    uniform_int_distribution<>uid5_10(5, 10);
    //uniform_int_distribution<>uid0_2(0,2);
    //uniform_int_distribution<>uid0_1(0,1);
    uniform_int_distribution<>uid11_16(11,16);
    //uniform_int_distribution<>uid1_200(1,200);
    uniform_int_distribution<>uid_primes(0, small_primes.size()-1);
    uniform_int_distribution<>uid_ratio(0, aspect_ratios.size()-1);
    while(done<task_qtty)
    {
        int photos_qtty(uid5_10(mt));
        array<int, 2> aratio(aspect_ratios[uid_ratio(mt)]);

        int q=small_primes[uid_primes(mt)];
        int sidepart=uid5_10(mt);
        int long_side(q*pow(2, sidepart)*aratio[0]);
        if (long_side>65536) continue;
        int short_side(q*pow(2, sidepart)*aratio[1]);
        int colors_power(uid11_16(mt));
        int colors(pow(2, colors_power));

        long long total_memory(colors_power*short_side*long_side*photos_qtty);
        if (total_memory%(8*1024)!=0) continue;
        total_memory/=(8*1024);

        if (total_memory > 4096 or total_memory < 1024 or ans.find(total_memory)!=ans.end()) continue;
        done++;
        ans.insert(total_memory);

        ostringstream task_txt;
        ostringstream answer_txt;
        task_txt << "Требуется сохранить " << photos_qtty << " фотографий, имеющих соотношение сторон " << aratio[0] << ":" <<aratio[1]
            << ". Длинная сторона каждой фотографии имеет длину " << long_side << " пиксел"
            << (long_side%10>=2 and long_side%10<=4 and (long_side%100<12 or long_side%100>14)?"я":(long_side%10 == 1 and long_side%100!=11?"ь":"ей"))
            << ", а палитра содержит " << colors << " цвет" << (colors%10>=2 and colors%10<=4 and (colors%100<11 or colors%100>15)?"а":"ов")
            << ". Определите наименьший возможный объём всех фотографий. В ответе укажите количество кибибайт, при необходимости округлённое до целых в большую сторону. Единицы измерения указывать не нужно.<br/><br/>"
                   <<"Примечание. 1 мебибайт - 1024 кибибайта, 1 кибибайт - 1024 байта. Это технически более корректные термины, чем 'килобайт' и 'мегабайт'. Приняты в 1999 году Международной электротехнической комиссией в стандарте IEC 60027-2, в России в ГОСТ 8.417-2002.";
            answer_txt << total_memory;

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
        answer_txt<<res;
        task_txt << "Для работы над новым проектом из сотрудников отдела необходимо сформировать команду, состоящую из 1 тимлида и " << devs_need << " разработчиков. Запишите количество различных способов сформировать команду, если в отделе работает " << people << " человек. В ответе укажите только число. Примечание: в качестве тимлида может выступать любой сотрудник; команды, в которых состоят одни и те же сотрудники, но в которых позицию тимлида занимают разные люди, считаются разными командами.";
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

int g06_04_01(int type,string &q)
{
    if (type<1 or type>4) {q = "ERROR"; return -1;}
    (time(0));
    int pages_text(0);
    int text_img_ratio(0);
    int pages_img(0);
    int pages_total(0);
    int bytes_per_symbol(0);
    int lines(0), symbols_per_line(0);
    array<int, 3> primes = {3,5,7};
    int w(0), h(0);
    int bits_per_pixel(0);
    long long int total_memory(0);
    long long int bits_per_mb(1<<23);
    long long int total_mb(0);
    int attempts(100);
    while (attempts--)
    {
        ostringstream os;
        pages_text = (1<<uid(7,9)(mt));
        text_img_ratio = (1<<uid(3,4)(mt));
        pages_img = pages_text/text_img_ratio;
        bytes_per_symbol = uid(2,4)(mt);
        pages_total = pages_text+pages_img;
        lines = (1<<uid(3,5)(mt))*primes[uid(0, primes.size()-1)(mt)];
        symbols_per_line = (1<<uid(6,8)(mt));
        if (uid(0,1)(mt)==0) swap(lines, symbols_per_line);
        w = (1<<uid(9,11)(mt));
        h = (1<<uid(9,11)(mt));

        bits_per_pixel = uid(11,15)(mt);
        long long int a = ((long long)bits_per_pixel)*w*h*pages_img;
        long long int b = (((long long)bytes_per_symbol)*lines*symbols_per_line*pages_text<<3);
        total_memory = a + b;
        if (total_memory % bits_per_mb != 0) continue;
        //cout << a << " " << b << endl;
        //cout << total_memory << endl;
        total_mb = total_memory/bits_per_mb;//10-20 символов, 1 символ, 2-4 символа
        if (total_mb>1000 or total_mb < 100) continue;

        if (type == 1)
        {
            os << "Книга, состоящая из " << pages_total << " страниц" << (pages_total%100!=11 and pages_total%10==1?"ы":"");
            os << ", занимает объем " << total_mb << " мебибайт" << (((total_mb%100>10 and total_mb%100<20) or total_mb%10<2 or total_mb%10>4)?"":"а");
            os << ". Часть страниц книги полностью заняты текстом. Каждая такая страница содержит ровно ";
            os << lines << " строк" << (lines%100>10 and lines%100<20?"":(lines%10==1?"а":(lines%10>1 and lines%10<5?"и":"")));
            os <<", в каждой строке ровно "<< symbols_per_line <<" символ" << (symbols_per_line%100>10 and symbols_per_line%100<20?"ов":(symbols_per_line%10==1?"":(symbols_per_line%10>1 and symbols_per_line%10<5?"а":"ов"))) << ". ";
            os << "Другая часть страниц полностью заполнена изображениями с разрешением " << w << " на " << h << " точек. ";
            os << "Известно, что страниц с текстом в " << text_img_ratio << " раз больше, чем страниц с изображениями. ";
            os << "Сколько цветов максимально может быть в палитре изображений, если известно, что кодировка предполагает, что для хранения каждого текстового символа отводится " << bytes_per_symbol << " байта? Используется попиксельное кодирование, для хранения каждого пикселя отводится одинаковое целое число бит. Ответ запишите в виде целого числа." << endl;
            q = os.str();
            return (1<<bits_per_pixel);
        }
        else if (type == 2)
        {
            os << "Книга, состоящая из " << pages_total << " страниц" << (pages_total%100!=11 and pages_total%10==1?"ы":"");
            os << ", занимает объем " << total_mb << " мебибайт" << (((total_mb%100>10 and total_mb%100<20) or total_mb%10<2 or total_mb%10>4)?"":"а");
            os << ". Часть страниц книги полностью заняты текстом. Каждая такая страница содержит ровно ";
            os << lines << " строк" << (lines%100>10 and lines%100<20?"":(lines%10==1?"а":(lines%10>1 and lines%10<5?"и":"")));
            os << ". Другая часть страниц полностью заполнена изображениями с разрешением " << w << " на " << h << " точек. ";
            os << "Максимальное возможное количество цветов в палитре каждого изображения - " << (1<<bits_per_pixel);
            os << ". Используется попиксельное кодирование, для хранения каждого пикселя отводится одинаковое целое число бит. ";
            os << "Известно, что страниц с текстом в " << text_img_ratio << " раз больше, чем страниц с изображениями. ";
            os << "Сколько символов в каждой строке книги, если известно, что кодировка предполагает, что для хранения каждого текстового символа отводится " << bytes_per_symbol << " байта? Ответ запишите в виде целого числа." << endl;
            q = os.str();
            return symbols_per_line;
        }
        else if (type == 3)
        {
            os << "Книга, состоящая из " << pages_total << " страниц" << (pages_total%100!=11 and pages_total%10==1?"ы":"");
            os << ", занимает объем " << total_mb << " мебибайт" << (((total_mb%100>10 and total_mb%100<20) or total_mb%10<2 or total_mb%10>4)?"":"а");
            os << ". Часть страниц книги полностью заняты текстом. Каждая такая страница содержит ровно ";
            os << lines << " строк" << (lines%100>10 and lines%100<20?"":(lines%10==1?"а":(lines%10>1 and lines%10<5?"и":"")));
            os <<", в каждой строке ровно "<< symbols_per_line <<" символ" << (symbols_per_line%100>10 and symbols_per_line%100<20?"ов":(symbols_per_line%10==1?"":(symbols_per_line%10>1 and symbols_per_line%10<5?"а":"ов"))) << ". ";
            os << ". Другая часть страниц полностью заполнена изображениями с разрешением " << w << " на " << h << " точек. ";
            os << "Максимальное возможное количество цветов в палитре каждого изображения - " << (1<<bits_per_pixel);
            os << ". Используется попиксельное кодирование, для хранения каждого пикселя отводится одинаковое целое число бит. ";
            os << "Кодировка предполагает, что для хранения каждого текстового символа отводится " << bytes_per_symbol << " байта. Во сколько раз страниц с текстом больше, чем страниц с изображениями? Ответ запишите в виде целого числа." << endl;
            q = os.str();
            return text_img_ratio;
        }
        return 0;

    }

}

int g06_04_01_01(int task_qtty, ofstream &ofs)
{


    int done(0);
    string q;
    int a;
    while(done<task_qtty)
    {
        a = g06_04_01(1, q);

        #if moodle

        moodle_write_question(ofs,done,q, to_string(a));
        #else
        cout << q << endl <<a <<endl;
        #endif
        done++;
    }
    #if moodle
    ofs << "</quiz>" << endl;
    #endif
}
int g06_04_01_02(int task_qtty, ofstream &ofs)
{


    int done(0);
    string q;
    int a;
    while(done<task_qtty)
    {
        a = g06_04_01(2, q);

        #if moodle

        moodle_write_question(ofs,done,q, to_string(a));
        #else
        cout << q << endl <<a <<endl;
        #endif
        done++;
    }
    #if moodle
    ofs << "</quiz>" << endl;
    #endif
}
int g06_04_01_03(int task_qtty, ofstream &ofs)
{


    int done(0);
    string q;
    int a;
    while(done<task_qtty)
    {
        a = g06_04_01(3, q);

        #if moodle

        moodle_write_question(ofs,done,q, to_string(a));
        #else
        cout << q << endl <<a <<endl;
        #endif
        done++;
    }
    #if moodle
    ofs << "</quiz>" << endl;
    #endif
}

int main()
{
    mt = mt19937(time(0));
    ofstream ofs("data.xml");
    #if moodle
    moodle_header(ofs);
    #endif
    setlocale(LC_ALL,"Russian");
    g06_03_02_01_01(50,ofs);
    //g10_1_1(50, ofs);
    //g7_2_1_1_1(10, ofs);
    //g8_1_1_2(10,ofs,5);
    //cout << alphabet.find("ё") - alphabet.find("е") << endl;

    return 0;
}
