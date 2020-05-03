#include <math.h>
#include <algorithm>
 #include <cstdlib>
 #include <iostream>
 #include <bitset>
 #include <sstream>
 #include <iomanip>
 #include <fstream>
#include <ctime>
#include <locale.h>

 #undef dbg
 #define difdig
 #undef math
 #define moodle
 #undef cstw

 using namespace std;

ofstream ofs;
ifstream ifs;


 int digit(int num, int pos, int base)
 {
 	int res=(num/(int)pow(base,(pos)))%base;
 	#ifdef dbg
 		ofs << num << "[" << pos << "]: " << res << endl;
 	#endif
 	return res;
 }

 bool different_digits(int num, int length, int base)
 {
 	#ifndef difdig
 		return true;
 	#endif
    bool has_letter=false;
 	for (int j=1; j<length; j++)
 	{
 		if (num%base == digit(num,j, base)) return false;
 	}
 	for (int i=1; i<length; i++)
 	{
 	    if (base>10 and digit(num, i, base)>9) has_letter=true;
 		for (int j=i+1; j<length; j++)
 		{
 			if (digit(num, i, base) == digit(num,j, base))
 			{
 				#ifdef dbg
 					ofs << i << " : " << j << endl;
 				#endif
 				return false;
 			}
 		}
 	}
 	if (base >10 and !has_letter) return false;
 	return true;
 }


string l_text(int length)
{
    string answer[]={"ОШИБКА", "ОШИБКА", "Двузначное", "Трёхзначное", "Четырёхзначное", "Пятизначное", "Шестизначное", "Семизначное", "Восьмизначное"};
    if (length>=9) return "ОШИБКА";
    else return answer[length];
}

string numsys_text(int numsys)
{
string answer[]={"ОШИБКА", "ОШИБКА", "двоичное", "троичное", "четверичное", "пятеричное", "шестеричное", "семеричное", "восьмеричное", "девятеричное", "десятичное", "одиннадцатеричное", "двенадцатеричное", "тринадцатеричное", "четырнадцатеричное", "пятнадцатеричное", "шестнадцатеричное"};
    if (numsys>=17) return "ОШИБКА";
    else return answer[numsys];
}
std::string alphabet("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ");

 int print_tasks(int length, int startfrom=0, int threshold=30, int numsys=10)
 {
     string base_oy=numsys_text(numsys);
     base_oy[base_oy.length()-1]='й';
 	int min_n=pow(numsys,length-1);
 	int max_n=pow(numsys, length)-1;
 	for (int i=min_n;i<max_n; i++)
 	{
 		for (int j=2; j<10; j++)
 		{
 			int reposnd=(i%numsys)*pow(numsys,length-1) + ceil(i/numsys);

 			if (abs(i*j-reposnd)<threshold && i*j!=reposnd && reposnd>min_n && different_digits(i, length, numsys))
 			{
 			    //cout << i << " " << (i%numsys)*pow(numsys,length-1) << " " << ceil(i/numsys) << " " << reposnd << endl;
 			    #ifdef cstw
                ofs << "</div>" << endl << "<div title=\"Переставить в начало - " << numsys << " №" << startfrom << "\" modifier=\"YourName\" created=\"201808141700\" tags=\"[[Переставить в начало - "<<numsys<<"]]\" changecount=\"0\">" << endl <<
                "<pre>" << endl;
                #else
                #ifdef moodle
                ofs<<"<question type=\"shortanswer\">"<<endl<<
    "<name>" << endl <<
      "<text>" << i << "</text>" << endl <<
    "</name>" << endl <<
    "<questiontext format=\"html\">" << endl <<
      "<text><![CDATA[<p>";
                #else
                ofs << startfrom << ".	";
                #endif
                #endif
 				#ifdef math
 					ofs << i << " * " << j << " = " << reposnd << " + " << i*j-reposnd << endl;
 				#endif

 				ofs << l_text(length) << " " << numsys_text(numsys) << " число оканчивается цифрой "<<alphabet[i%numsys]
 				<<". Если эту цифру переставить в начало числа, то получившееся в результате перестановки число будет на "
 				<< abs(i*j-reposnd) << (i*j<reposnd?" больше":" меньше") << " умноженного на " << j
 				<< " исходного числа. Укажите исходное число в десятичной форме"<<(numsys!=10?" и через пробел в "+base_oy+" форме":"")<<". Основание указывать не надо." << endl;
 				startfrom++;
 				#ifdef cstw
 				ofs << "</pre>" << endl;
 				#else
 				#ifdef moodle
 				ofs << "<br></p>]]></text>" << endl <<
    "</questiontext>" << endl <<
    "<generalfeedback format=\"html\">" << endl <<
      "<text></text>" << endl <<
    "</generalfeedback>" << endl <<
    "<defaultgrade>1.0000000</defaultgrade>" << endl <<
    "<penalty>0.3333333</penalty>" << endl <<
    "<hidden>0</hidden>" << endl <<
    "<idnumber></idnumber>" << endl <<
    "<usecase>0</usecase>" << endl <<
    "<answer fraction=\"100\" format=\"moodle_auto_format\">" << endl <<
    "<text>" << i <<(numsys!=10?" TODO: CONVERT HERE":"") << "</text>" << endl <<
      "<feedback format=\"html\">" << endl <<
      "<text></text>" << endl <<
      "</feedback>" << endl <<
      "</answer>" << endl <<
      "</question>" << endl << endl;
 				#endif
 				#endif
 			}
 		}
 	}
 	return startfrom;
 }

string tobase(int num, int base)
{
    vector<int> digits;
    while (num>0)
    {
        digits.push_back(num%base);
        num/=base;

    }
    string res="";
    for (int i=digits.size()-1; i>=0; i--)
    {
        res+=alphabet[digits[i]];
    }
    return res;
}

 int main()
 {
    //cout << tobase(255,16) <<endl;
  /*  srand(time(NULL));
    int numbers=5;
    int maxdeg=100;
    int base=5;
    vector<int>deg;
    vector<int>hid_deg;
    vector<int>quot;
    int between=maxdeg/(numbers+1);
    cout << between <<endl;
    for (int i=0; i<numbers; i++)
    {
        deg.push_back(between*(i+1)+rand()%(int)ceil(between*0.5));
        int cur_hid_deg=4;
        while (deg[deg.size()-1]%cur_hid_deg!=0)
        {
            cur_hid_deg--;
        }
        deg[deg.size()-1]/=cur_hid_deg;
        hid_deg.push_back(cur_hid_deg);
        quot.push_back((base>2?rand()%(base-2)+1:1));
        //cout << hid_deg[hid_deg.size()-1] << endl;
    }
    for (int i=0; i<numbers; i++) cout << quot[i]<<" " << hid_deg[i]<<" " << deg[i] <<endl;
    for (int i=numbers-1; i>=0; i--)
    {
        if (i<numbers-1) if ((numbers-1-i)%2==0) cout << " + "; else cout <<" - ";
        if (quot[i]>1) cout << quot[i]<<"*";
        cout<<pow(base,hid_deg[i]);
        if (deg[i]>1) cout << "^"<<deg[i];
    }

*/















//31 28|29 31 30 31 31 30 31 30 31 30 31

/*
вывести даты сред в январе 1900 года
вывести даты сред в 1900 году
количество сред в 1900 году
количество сред с 1900 по 1999
вывести количество сред 30-х с 1900 по 1999
*/
  string weekday[] = { "Sunday", "Monday",
                             "Tuesday", "Wednesday",
                             "Thursday", "Friday", "Saturday"};
    for(int i=3;i<=31;i+=7)
    {
    printf("%d\n",i);

    }


    return(0);
 }
