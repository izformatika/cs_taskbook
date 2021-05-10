#ifndef MOODLE_QUESTION_HPP_INCLUDED
#define MOODLE_QUESTION_HPP_INCLUDED
#include <fstream>
#include <iomanip>
using std::ofstream;
using std::string;
using std::endl;

void moodle_write_question(ofstream &ofs, int id, string qtext, string ans)
{
    ofs << "<question type=\"shortanswer\">" << endl
                <<"<name>" << endl
                <<"<text>" << std::fixed << std::setw(2) <<std::setfill('0')<< id << "</text>" << endl
                <<"</name>" << endl
                <<"<questiontext format=\"html\">" << endl
                <<"<text><![CDATA[<p>" << qtext
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
                <<"<text>" << ans << "</text>" << endl
                  <<"<feedback format=\"html\">"<<endl
                    <<"<text></text>" << endl
                  <<"</feedback>" << endl
                <<"</answer>" <<endl
              <<"</question>" <<endl << endl;

}

void moodle_header(ofstream &ofs)
{
    ofs<< "<?xml version=\"1.0\" encoding=\"UTF-8\"?><quiz><question type=\"category\"><category>"
      << "<text>top/!!импорт-экспорт Скорцезе</text>"
    <<"</category><info format=\"moodle_auto_format\"><text></text></info></question>" << endl;
}

#endif
