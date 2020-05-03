#include <ctime>
#include <map>
#include <set>
#include <tuple>
#include <random>
#include <iostream>
#include <sstream>
#include <fstream>
#include <clocale>
#include <conio.h>

#define moodle true

using namespace std;

enum cases {nom,gen,dat,acc,instr,prep};

enum units {mins,khz,bits,kibs,mibs};

map<units, vector<tuple<int,int,int,cases,string>>> dict;

void dict_init()
{
    dict[mins].push_back(make_tuple(100,5,20,gen,"минут"));
    dict[mins].push_back(make_tuple(10,1,1,gen,"минута"));
    dict[mins].push_back(make_tuple(10,2,4,gen,"минуты"));
    dict[mins].push_back(make_tuple(1,0,0,gen,"минут"));

    dict[khz].push_back(make_tuple(100,5,20,gen,"килогерц"));
    dict[khz].push_back(make_tuple(10,2,4,gen,"килогерца"));
    dict[khz].push_back(make_tuple(1,0,0,gen,"килогерц"));

    dict[bits].push_back(make_tuple(100,5,20,gen,"бит"));
    dict[bits].push_back(make_tuple(10,2,4,gen,"бита"));
    dict[bits].push_back(make_tuple(1,0,0,gen,"бит"));

    dict[kibs].push_back(make_tuple(100,5,20,gen,"кибибайт"));
    dict[kibs].push_back(make_tuple(10,2,4,gen,"кибибайта"));
    dict[kibs].push_back(make_tuple(1,0,0,gen,"кибибайт"));

    dict[mibs].push_back(make_tuple(100,5,20,gen,"мебибайт"));
    dict[mibs].push_back(make_tuple(10,2,4,gen,"мебибайта"));
    dict[mibs].push_back(make_tuple(1,0,0,gen,"мебибайт"));
}

string get_unit(units u, int m, cases c)
{
    for (auto i:dict[u])
    {
        if (m%get<0>(i)>=get<1>(i) and m%get<0>(i)<=get<2>(i) and c==get<3>(i)) return to_string(m)+ " " +get<4>(i);
    }
    return "ERROR";

}

bool nice(int sz)
{
    int prime_fac=0;
    //if (sz%2==0) prime_fac++;
    if (sz%3==0) prime_fac++;
    //if (sz%5==0) prime_fac++;
    if (sz%7==0) prime_fac++;

    if (prime_fac>1) return false;
    return true;
}

int main()
{
    setlocale(LC_ALL,"Russian");
    dict_init();
    #if moodle
    ofstream ofs("data.txt");
    #endif

    enum mode {memory_resol, memory_levels, time_resol, time_levels};
    mode m=memory_resol;
    mt19937 mt(time(0));
    uniform_int_distribution<> uid(0, 4);
    uniform_int_distribution<> uid_1(1, 16);
    set <int> szs;
    int chan[]={1,2,4,6,8};
    string chan_s[]={" (моно)", " (стерео)", " (квадро)", " (Surround 5.1)", " (Surround 7.1)"};

    int task_qtty=100;
    int i=0;
    //for (int i=0; i<task_qtty; i++)
    {
        int chan_i, time, resolution, levels, freq;
        long long filesize;

        for (chan_i=0; chan_i<5; chan_i++)
        for (time=1; time<=256; time*=2)
        for (resolution=4; resolution<=16; resolution++)
        for (freq=1; freq<=64; freq*=2)
        {
            filesize=time*60*resolution;
            filesize*=freq*1000;
            filesize*=chan[chan_i];
            if (filesize%(8388608)>0) continue;
            filesize/=8388608;

            i++;

        /*do
        {
        chan_i=uid(mt);
        time=pow(2,uid_1(mt));
        resolution=pow(2,uid(mt)+2);
        levels=pow(2,resolution);
        freq=pow(2,uid(mt)+uid(mt));
        filesize=time*60*resolution;
        filesize*=freq*1000;
        filesize*=chan[chan_i];//if in one line - multiplication result is int, overflows
        cout << endl;
        }
        while (filesize%(8388608)>0);//8*1024^2, to mebibytes
        filesize/=8388608;
*/

        ostringstream task_txt;
        ostringstream answer_txt;
        if (m==memory_resol)
        {
            task_txt //<< "(Текст этого вопроса сгенерирован автоматически, поэтому может содержать ошибки согласования)<br/><br/>"
            <<"Аудиозапись длиной "<<get_unit(mins,time,gen)<<" закодирована с частотой дискретизации "<<get_unit(khz,freq,gen)<<" с разрешением "<<get_unit(bits,resolution,gen)<<". Количество каналов - "<<chan[chan_i]<<chan_s[chan_i] << ". Сжатие данных не производилось. Сколько мебибайт занимает эта запись в памяти компьютера? В ответе укажите целое число и через пробел единицу измерения."
            <<"<br/><br/>Примечание. 1 мебибайт - 1024 кибибайта, 1 кибибайт - 1024 байта. Это технически более корректные термины, чем 'килобайт' и 'мегабайт'. Приняты в 1999 году Международной электротехнической комиссией в стандарте IEC 60027-2, в России в ГОСТ 8.417-2002.";
            answer_txt << get_unit(mibs,filesize,gen);
        }

        #if moodle
            ofs << "<question type=\"shortanswer\">" << endl
                <<"<name>" << endl
                <<"<text>" << i << "</text>" << endl
                <<"</name>" << endl
                <<"<questiontext format=\"html\">" << endl
                <<"<text><![CDATA[<p>" << task_txt.str()
                <<"</p>]]></text>" << endl
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
                <<"<text>" << answer_txt.str() << "</text>" << endl
                  <<"<feedback format=\"html\">"<<endl
                    <<"<text></text>" << endl
                  <<"</feedback>" << endl
                <<"</answer>" <<endl
              <<"</question>" <<endl;
        #else
        cout << task_txt.str() << endl <<answer_txt.str() <<endl;


        #endif
        if (i==task_qtty) return 0;
        }

    }
    return 0;
}
