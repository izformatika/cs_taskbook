#include <ctime>
#include <set>
#include <random>
#include <iostream>
#include <sstream>
#include <fstream>
#include <clocale>

#define moodle false

using namespace std;


int main()
{
    #if moodle
    ofstream ofs("data.txt");
    #endif
    setlocale(LC_ALL,"Russian");
    enum mode {memory_resol, memory_levels, time_resol, time_levels};
    mode m=time_resol;
    mt19937 mt(time(0));
    uniform_int_distribution<> uid(0, 4);
    uniform_int_distribution<> uid_1(1, 16);
    set <int> szs;
    int chan[]={1,2,4,6,8};
    string chan_s[]={" (моно)", " (стерео)", " (квадро)", " (Surround 5.1)", " (Surround 7.1)"};

    //int task_qtty=100;
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
            //if (!nice(filesize)) continue;

            szs.insert(filesize);
            i++;
            //cout << i << endl;

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
        if (m==time_resol)
        {
            task_txt << "(Текст этого вопроса сгенерирован автоматически, поэтому может содержать ошибки согласования)<br/><br/>Сколько времени в минутах длится аудиозапись, если известно, что количество каналов записи - " << chan[chan_i] << chan_s[chan_i]
                << ", запись велась с частотой дискретизации " << freq << " килогерц, с разрешением " << resolution << " бит, сжатие не производилось, и получившийся аудиофайл занимает на диске " << filesize << " мебибайт? В ответе укажите целое число минут, единицы измерения указывать не нужно.<br/><br/>Примечание. 1 мебибайт - 1024 кибибайта, 1 кибибайт - 1024 байта. Это технически более корректные термины, чем 'килобайт' и 'мегабайт'. Приняты в 1999 году Международной электротехнической комиссией в стандарте IEC 60027-2, в России в ГОСТ 8.417-2002.";
            answer_txt << time;
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
        //cout << task_txt.str() << endl <<answer_txt.str() <<endl;


        #endif
        }
        cout << endl << endl;
        for (auto i: szs) cout << i << endl;
    }
    return 0;
}
