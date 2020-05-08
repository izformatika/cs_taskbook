#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <array>
#include <bitset>
#include <cmath>
#include <cstdlib>
#include <ctime>

#define moodle true
using namespace std;

bool net(bitset<8> ip[4], bitset<8> mask[4])
{
    for (int i=0; i<4; i++) if (ip[i]!=(ip[i]&mask[i])) return false;
    return true;
}

bool broad(bitset<8> ip[4], bitset<8> mask[4])
{
    for (int i=0; i<4; i++) if (ip[i]!=(ip[i]|(~mask[i]))) return false;
    return true;
}

    bitset<8> a[4];
    bitset<8> b[4];
    bitset<8> mask[4];

void gen(bool mask_important=true)
{
    array<int,4> decip;
    do
    {
        decip={rand()%64+1, rand()%64+65, rand()%64+129, rand()%64+192};
        random_shuffle(decip.begin(),decip.end());
        for (int i=0; i<4; i++)
            {a[i]=decip[i];mask[i]=0;}
        int dmask=0;
        while (dmask%8==0) dmask=rand()%16+10;
        //cout << dmask << endl;
        for (int i=0; i<dmask; i++)
            mask[i/8][7-i%8]=1;
    }
    while (net(a,mask) or broad(a,mask));

}

pair<int,int> genmask(bool minimum=true)
{
    int from=0;
    from=rand()%6+1+(rand()%3)*8;
    int to=(ceil(from/8.0))*8+rand()%5;
    //cout << from << " " << to << endl;
    a[(from-1)/8][7-(from-1)%8]=1;
    for (int i=from; i<=to; i++) a[i/8][7-i%8]=0;
    a[(to+1)/8][7-(to+1)%8]=1;
    for (int i=0; i<(minimum?from:to+1); i++) mask[i/8][7-i%8]=1;
    for (int i=(minimum?from:to+1); i<32; i++) mask[i/8][7-i%8]=0;
    return pair<int,int>(from,to);
}

int main()
{
    #if moodle
    ofstream ofs("data.txt");
    #endif
    srand(time(0));
    enum tasks {network,broadcast,nodenumber,minmask,maxmask,onesegment};
    tasks task=onesegment;
    int task_qtty=100;

    for (int i=0; i<task_qtty; i++)
    {
        gen();
        string name, text, answer;
        switch (task)
        {
            case network:
                #if not moodle
                {
                for (int i=0; i<4; i++) cout << a[i]<<".";
                cout <<endl;
                for (int i=0; i<4; i++) cout << mask[i]<<".";
                cout <<endl;
                cout << "network address: ";
                for (int i=0; i<4; i++) cout << (a[i]&mask[i])<<".";
                }
                #else
                {
                ostringstream os;
                os << a[0].to_ulong()<<"."<<a[1].to_ulong()<<"."<<a[2].to_ulong()<<"."<<a[3].to_ulong();
                name=os.str();
                os.str("");
                os << "Определите адрес сети для узла, собственный адрес которого "<<a[0].to_ulong()<<"."<<a[1].to_ulong()<<"."<<a[2].to_ulong()<<"."<<a[3].to_ulong()<<" при маске сети "<<mask[0].to_ulong()<<"."<<mask[1].to_ulong()<<"."<<mask[2].to_ulong()<<"."<<mask[3].to_ulong()<<". В ответе укажите адрес сети в десятичном виде.";
                text=os.str();
                os.str("");
                bitset<8>res[4];
                for (int i=0; i<4; i++) res[i]=a[i]&mask[i];
                os<<res[0].to_ulong()<<"."<<res[1].to_ulong()<<"."<<res[2].to_ulong()<<"."<<res[3].to_ulong();
                answer=os.str();
                os.str("");
                }
                #endif
                break;
           case broadcast:
               //TODO: fix! 128 or 254 only
                #if not moodle
                {
                for (int i=0; i<4; i++) cout << a[i]<<".";
                cout <<endl;
                for (int i=0; i<4; i++) cout << mask[i]<<".";
                cout << endl << "broadcast address: ";
                for (int i=0; i<4; i++) cout << (a[i]|(~mask[i]))<<".";}
                #else
                {
                ostringstream os;
                os << a[0].to_ulong()<<"."<<a[1].to_ulong()<<"."<<a[2].to_ulong()<<"."<<a[3].to_ulong();
                name=os.str();
                os.str("");
                os << "Определите широковещательный адрес для узла, собственный адрес которого "<<a[0].to_ulong()<<"."<<a[1].to_ulong()<<"."<<a[2].to_ulong()<<"."<<a[3].to_ulong()<<" при маске сети "<<mask[0].to_ulong()<<"."<<mask[1].to_ulong()<<"."<<mask[2].to_ulong()<<"."<<mask[3].to_ulong()<<". В ответе укажите широковещательный адрес в десятичном виде.";
                text=os.str();
                os.str("");
                bitset<8>res[4];
                for (int i=0; i<4; i++) res[i]=a[i]|~mask[i];
                os<<res[0].to_ulong()<<"."<<res[1].to_ulong()<<"."<<res[2].to_ulong()<<"."<<res[3].to_ulong();
                answer=os.str();
                os.str("");}
                #endif
                break;
            case nodenumber:
                {
                int number=0;
                do{
                int dmask=0;
                while (dmask%8==0) dmask=rand()%13+18;
                for (int i=0; i<4; i++) mask[i]=0;
                for (int i=0; i<dmask; i++)
                    mask[i/8][7-i%8]=1;

                for (int i=0; i<4; i++) number+=pow(256,3-i)*(a[i].to_ulong()-(a[i]&mask[i]).to_ulong());
                }
                while(number==a[3].to_ulong());
                #if not moodle
                {
                for (int i=0; i<4; i++) cout << mask[i]<<".";
                cout <<endl;
                cout << endl << "number: ";
                cout << number << endl;}
                #else
                {
                ostringstream os;
                os << a[0].to_ulong()<<"."<<a[1].to_ulong()<<"."<<a[2].to_ulong()<<"."<<a[3].to_ulong();
                name=os.str();
                os.str("");
                os << "Определите порядковый номер в его сегменте сети для узла, собственный адрес которого "<<a[0].to_ulong()<<"."<<a[1].to_ulong()<<"."<<a[2].to_ulong()<<"."<<a[3].to_ulong()<<" при маске сети "<<mask[0].to_ulong()<<"."<<mask[1].to_ulong()<<"."<<mask[2].to_ulong()<<"."<<mask[3].to_ulong()<<". В ответе укажите только число.";
                text=os.str();
                os.str("");
                os<<number;
                answer=os.str();
                os.str("");}
                #endif
                }
                break;
            case minmask:
                {
                genmask(true);
                #if not moodle
                for (int i=0; i<4; i++) cout << a[i]<<".";
                cout << endl;
                cout << "network address:" << endl;
                for (int i=0; i<4; i++) cout << (a[i]&mask[i])<<".";
                cout << endl;
                for (int i=0; i<4; i++) cout << mask[i]<<".";
                #else
                ostringstream os;
                os << a[0].to_ulong()<<"."<<a[1].to_ulong()<<"."<<a[2].to_ulong()<<"."<<a[3].to_ulong();
                name=os.str();
                os.str("");
                for (int i=0; i<4; i++) b[i]=(a[i]&mask[i]);
                os << "Определите наименьшее возможное значение маски сети для узла, собственный адрес которого "<<a[0].to_ulong()<<"."<<a[1].to_ulong()<<"."<<a[2].to_ulong()<<"."<<a[3].to_ulong()<<" при адресе сети "<<b[0].to_ulong()<<"."<<b[1].to_ulong()<<"."<<b[2].to_ulong()<<"."<<b[3].to_ulong()<<". В ответе укажите маску в полном десятичном формате.";
                text=os.str();
                os.str("");
                os << mask[0].to_ulong()<<"."<<mask[1].to_ulong()<<"."<<mask[2].to_ulong()<<"."<<mask[3].to_ulong();
                answer=os.str();
                os.str("");
                #endif
                }
                break;
            case maxmask:
                {
                genmask(false);
                #if not moodle
                for (int i=0; i<4; i++) cout << a[i]<<".";
                cout << endl;
                cout << "network address:" << endl;
                for (int i=0; i<4; i++) cout << (a[i]&mask[i])<<".";
                cout << endl;
                for (int i=0; i<4; i++) cout << mask[i]<<".";
                #else
                ostringstream os;
                os << a[0].to_ulong()<<"."<<a[1].to_ulong()<<"."<<a[2].to_ulong()<<"."<<a[3].to_ulong();
                name=os.str();
                os.str("");
                for (int i=0; i<4; i++) b[i]=(a[i]&mask[i]);
                os << "Определите наибольшее возможное значение маски сети для узла, собственный адрес которого "<<a[0].to_ulong()<<"."<<a[1].to_ulong()<<"."<<a[2].to_ulong()<<"."<<a[3].to_ulong()<<" при адресе сети "<<b[0].to_ulong()<<"."<<b[1].to_ulong()<<"."<<b[2].to_ulong()<<"."<<b[3].to_ulong()<<". В ответе укажите маску в полном десятичном формате.";
                text=os.str();
                os.str("");
                os << mask[0].to_ulong()<<"."<<mask[1].to_ulong()<<"."<<mask[2].to_ulong()<<"."<<mask[3].to_ulong();
                answer=os.str();
                os.str("");
                #endif
                }
                break;
            case onesegment:
                {
                    int commask;
                    do
                        commask=rand()%15+9;
                    while (commask%8==0);
                    for (int i=0; i<4; i++) mask[i]=0;
                    for (int i=0; i<commask; i++) mask[i/8][7-i%8]=1;
                    array<int,4> decip={rand()%64+1, rand()%64+65, rand()%64+129, rand()%64+192};
                    random_shuffle(decip.begin(),decip.end());
                    for (int i=0; i<4; i++)
                    {
                        b[i]=a[i];
                        b[i]=b[i]&mask[i];
                        b[i]=b[i]|(~mask[i]&bitset<8>(decip[i]));
                    }
                    b[commask/8][7-commask%8]=not a[commask/8][7-commask%8];
                    #if not moodle
                    cout << commask << endl;
                    for (int i=0; i<4; i++) cout << a[i]<<".";
                    cout << endl;
                    for (int i=0; i<4; i++) cout << b[i]<<".";
                    cout << endl;
                    for (int i=0; i<4; i++) cout << mask[i]<<".";
                    #else
                    ostringstream os;
                    os << a[0].to_ulong()<<"."<<a[1].to_ulong()<<"."<<a[2].to_ulong()<<"."<<a[3].to_ulong();
                    name=os.str();
                    os.str("");
                    os << "Узлы "<<a[0].to_ulong()<<"."<<a[1].to_ulong()<<"."<<a[2].to_ulong()<<"."<<a[3].to_ulong()<<" и "<<b[0].to_ulong()<<"."<<b[1].to_ulong()<<"."<<b[2].to_ulong()<<"."<<b[3].to_ulong()<<" находятся в одном сегменте сети, причём его размер минимально возможный. Определите маску сети и укажите её в полном десятичном формате.";
                    text=os.str();
                    os.str("");
                    os << mask[0].to_ulong()<<"."<<mask[1].to_ulong()<<"."<<mask[2].to_ulong()<<"."<<mask[3].to_ulong();
                    answer=os.str();
                    os.str("");
                    #endif
                }
                break;
            default:
                cout << "error" << endl;
        }
        #if moodle
        ofs << "<question type=\"shortanswer\">" << endl
                <<"<name>" << endl
                <<"<text>" << name << "</text>" << endl
                <<"</name>" << endl
                <<"<questiontext format=\"html\">" << endl
                <<"<text><![CDATA[<p>"<<text<<"</p>]]></text>" << endl
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
                <<"<text>" << answer << "</text>" << endl
                  <<"<feedback format=\"html\">"<<endl
                    <<"<text></text>" << endl
                  <<"</feedback>" << endl
                <<"</answer>" <<endl
              <<"</question>" <<endl;
              #endif
    }
    return 0;
}
