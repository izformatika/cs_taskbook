#include <fstream>
#include <set>
#include <sstream>
#include <cmath>
#include <algorithm>
#include "longnum.hpp"
void generate_plus_minus_digsum()
{
    using namespace std;
    ofstream ofs("data.txt");
    ///----------------config here
    vector<int>bases={3,4,5};
    dig_sz_t maxlen=100;
    int numbers=5;
    int tasks=100;
    ///----------------config here
    for (int t=0; t<tasks; t++)
    {
        int base=bases[rand()%bases.size()];
        vector<longnum> nums;
        vector<int> high_digs;
        vector<dig_sz_t> lens;
        dig_sz_t between=maxlen/(numbers+1);
        for (int i=0; i<numbers; i++)
        {
            nums.push_back(longnum("",base));
            high_digs.push_back(rand()%(base-1)+1);
            lens.push_back(between*(i+1)+rand()%(dig_sz_t)ceil(between*0.5));
            nums[nums.size()-1].setdigit(*(lens.end()-1), *(high_digs.end()-1));
            //cout << nums[nums.size()-1].str() << endl;
        }
        reverse(nums.begin(), nums.end());
        reverse(lens.begin(), lens.end());
        reverse(high_digs.begin(), high_digs.end());//TODO: insert instead
        longnum res("", base);
        ostringstream num_form;
        ostringstream txt_form;
        res=nums[0];
        num_form<< nums[0].str();
        if (high_digs[0]!=1) txt_form<<high_digs[0]<<"*";
        txt_form<<base;
        if (lens[0]!=1)txt_form<<"^"<<lens[0];
        for (size_t i=1; i<nums.size(); i++)
        {
    //        cout << "{" << res.str() << "}" << endl;
            if (i%2==1) {num_form<<" - "; txt_form<<" - "; res=res-nums[i];} else {num_form<<" + "; txt_form<<" + "; res=res+nums[i];}
            num_form<<nums[i].str();
            if (high_digs[i]!=1) txt_form<<high_digs[i]<<"*";
            txt_form<<base;
            if (lens[i]!=1)txt_form<<"^"<<lens[i];

        }
        map<unsigned char, dig_sz_t> stat=res.digit_stat();
        int sumdig=0;
        for (auto i:stat)
        {
            sumdig+=i.second*i.first;
        }
        #if moodle
            ofs << "<question type=\"shortanswer\">" << endl
                <<"<name>" << endl
                <<"<text>" << txt_form.str() << "</text>" << endl
                <<"</name>" << endl
                <<"<questiontext format=\"html\">" << endl
                <<"<text><![CDATA[<p>Вычислите значение выражения " << txt_form.str()
                <<" в системе счисления с основанием " << base << ". В ответе укажите десятичную сумму цифр получившегося числа.</p>]]></text>" << endl
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
                <<"<text>" << sumdig << "</text>" << endl
                  <<"<feedback format=\"html\">"<<endl
                    <<"<text></text>" << endl
                  <<"</feedback>" << endl
                <<"</answer>" <<endl
              <<"</question>" <<endl;

        #else
            cout << txt_form.str() << endl;
            cout << res.str() <<": " <<sumdig<< endl;
        #endif
    }
}
void numbers_between()
{
    using namespace std;
    #if moodle
    ofstream ofs("data.txt");
    #endif
    vector<int>bases_a={3,4,5,6,7,9};
    vector<int>bases_b={11,12,13,14,15};
    int tasks=100;
    for (int i=0; i<tasks; i++)
    {
        int base_a=bases_a[rand()%bases_a.size()];
        int base_b=bases_b[rand()%bases_b.size()];
        int min_a=pow(base_a,2);
        int max_a=pow(base_a,3)-1;
        int a=rand()%(max_a-min_a+1)+min_a;
        longnum aa(a,base_a);

        int min_b=max((int)pow(base_b,2),a);
        int max_b=max((int)pow(base_b,3)-1, min_b*2);
        int b,c,base_c,min_c,max_c;
        longnum bb(0,base_b);
        longnum cc(0,base_b);
        do base_c=bases_b[rand()%bases_b.size()];
        while (base_c==base_b);
        min_c=pow(base_c,2);
        max_c=pow(base_c,3)-1;
        do
        {
            c=rand()%(max_c-min_c-a)+min_c+a;
            b=a+c+1;
            bb=longnum(b,base_b);

            //cout << a << "_" << base_a <<" " << c << "_" << base_c << " " << b << "_" << base_b << endl;
            cc=longnum(c,base_c);
        }
        while (!bb.has_letters() or !cc.has_letters());
        #if moodle
            ofs << "<question type=\"shortanswer\">" << endl
                <<"<name>" << endl
                <<"<text>" << i << "</text>" << endl
                <<"</name>" << endl
                <<"<questiontext format=\"html\">" << endl
                <<"<text><![CDATA[<p>Сколько существует чисел в промежутке между " << aa.str() << "_" << base_a
                <<" и " << bb.str() << "_" << base_b << ", исключая сами эти числа? Ответ дайте в системе счисления с основанием "<<base_c <<". Основание в ответе указывать не надо, только цифры числа.</p>]]></text>" << endl
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
                <<"<text>" << cc.str() << "</text>" << endl
                  <<"<feedback format=\"html\">"<<endl
                    <<"<text></text>" << endl
                  <<"</feedback>" << endl
                <<"</answer>" <<endl
              <<"</question>" <<endl;
        #else
            cout << aa.str() <<"_"<<base_a<<" [" << b-a << "("<<cc.str()<<"_"<< base_c<<")] "<< bb.str() <<"_"<<base_b<<endl;
        #endif
    }

}
void what_base()
{
    using namespace std;
    #if moodle
    ofstream ofs("data.txt");
    #endif
    vector<int>bases_a={3,4,5,6,7,9};
    int tasks=100;
    std::set<std::vector<std::string> > s;
    while (s.size()<tasks)
    {
        int base_a;
        int base_b;

        int b;
        longnum bb(0,base_b);
        do
        {
            base_a=bases_a[rand()%bases_a.size()];
            base_b=rand()%20+17;
            int min_a=pow(base_a,2);
            int max_a=pow(base_a,3)-1;
            int min_b=(int)pow(base_b,2);
            int max_b=(int)pow(base_a,4)-1;
            if (max_b<min_b) continue;
            b=rand()%(max_b-min_b)+min_b;
            bb=longnum(b,base_b);
        }
        while (!bb.has_big_letters());
        longnum aa(b,base_a);
        vector<string> tmp;
        tmp.push_back((string)(aa.str()+"_"+to_string(base_a)));
        tmp.push_back(bb.str());
        tmp.push_back(to_string(base_b));
        s.insert(tmp);
        //clog << s.size() << endl;
    }
        #if moodle
        for (auto i:s)
            ofs << "<question type=\"shortanswer\">" << endl
                <<"<name>" << endl
                <<"<text>" << i[0] << "</text>" << endl
                <<"</name>" << endl
                <<"<questiontext format=\"html\">" << endl
                <<"<text><![CDATA[<p>В системе счисления с каким основанием число " << i[0]
                <<" выглядит как " << i[1] << "? В ответе укажите только число - основание.</p>]]></text>" << endl
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
                <<"<text>" << i[2] << "</text>" << endl
                  <<"<feedback format=\"html\">"<<endl
                    <<"<text></text>" << endl
                  <<"</feedback>" << endl
                <<"</answer>" <<endl
              <<"</question>" <<endl;
        #else
        for (auto i:s)
            cout << i[0] <<" " <<i[1] << " " << i[2] << endl;
        #endif

}
