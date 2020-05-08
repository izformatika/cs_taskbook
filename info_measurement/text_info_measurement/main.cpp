#include <ctime>
#include <random>
#include <iostream>
#include <sstream>
#include <fstream>
#include <clocale>

#define moodle true

using namespace std;

int main()
{
    #if moodle
    ofstream ofs("data.txt");
    #endif
    setlocale(LC_ALL,"Russian");
    enum mode {memory_symbols, memory_bits, symbols_memory, letters_memory};
    mode m=symbols_memory;
    mt19937 mt(time(0));
    uniform_int_distribution<> uid(0, 4);
    uniform_int_distribution<> uid_1(8, 1023);

    //int task_qtty=1;
    int i=0;
    //for (int i=0; i<task_qtty; i++)
    {
        int symb,pages,lines,symbols_per_line,bit_per_symbol;
        long long filesize;
        for (symb=32; symb<=1024; symb*=2)
        for (pages=32; pages<=2048; pages*=2)
        for (lines=16; lines<=128; lines*=2)
        for (symbols_per_line=16; symbols_per_line<=128; symbols_per_line*=2)
        {
            bit_per_symbol=ceil(log(symb)/log(2));
            filesize=bit_per_symbol*pages;
            filesize*=lines*symbols_per_line;
        /*do
        {
        symb=uid_1(mt);
        pages=pow(2,uid(mt)+4)*(uid(mt)+1);
        lines=pow(2,uid(mt)+4)*(uid(mt)+1);
        symbols_per_line=pow(2,uid(mt)+4)*(uid(mt)+1);
        bit_per_symbol=ceil(log(symb)/log(2));
        filesize=bit_per_symbol*pages;
        filesize*=lines*symbols_per_line;
        cout << endl;
        }
        while (filesize%8388608>0);
        filesize/=8388608;
*/
if (filesize%8388608>0) continue;
filesize/=8388608;
i++;
cout << i << endl;
        ostringstream task_txt;
        ostringstream answer_txt;
        if (m==symbols_memory)
        {
            task_txt << "(Текст этого вопроса сгенерирован автоматически, поэтому может содержать ошибки согласования)<br/><br/>";
            task_txt << "Текст книги занимает в памяти компьютера " << filesize << " мебибайт. Известно, что в книге "
                << pages << " страниц, на каждой странице в среднем "<< lines << " строк, в каждой строке в среднем "<< symbols_per_line<< " символов. Какова максимально возможная мощность используемого алфавита, то есть сколько максимум символов может использоваться в этой книге? В ответе укажите целое число символов, единицы измерения указывать не нужно.<br/><br/>Примечание. 1 мебибайт - 1024 кибибайта, 1 кибибайт - 1024 байта. Это технически более корректные термины, чем 'килобайт' и 'мегабайт'. Приняты в 1999 году Международной электротехнической комиссией в стандарте IEC 60027-2, в России в ГОСТ 8.417-2002.";
            answer_txt << symb;
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
    }
    }
    return 0;
}
