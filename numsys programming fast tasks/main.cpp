#include <iostream>
#include <chrono>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <locale>
#include <random>

using namespace std;

#define random 1
#define all 2
#define mode all

int main()
{
    mt19937 r(time(0));
    setlocale(LC_ALL,"Russian");
    srand(time(0));
    int num=0;
    int base;
    vector<vector<string>> a;
    a.push_back(vector<string>{"максимум среди ", "минимум среди "});
    a.push_back(vector<string>{"среднее арифметическое ", "среднее геометрическое "});
    vector<vector<string>> b;
    b.push_back(vector<string>{ "цифр кратных ",
                                "цифр не кратных "});
    b.push_back(vector<string>{ "цифр больших ",
                                "цифр меньших "});

    #if mode==all
    for (int a1=0;a1<a.size();a1++)
    for (int a2=a1+1;a2<a.size();a2++)
    for (int a11=0; a11<a[a1].size(); a11++)
    for (int a21=0; a21<a[a2].size(); a21++)
    for (int b1=0;b1<b.size();b1++)
    for (int b2=b1+1;b2<b.size();b2++)
    for (int b11=0; b11<b[b1].size(); b11++)
    for (int b21=0; b21<b[b2].size(); b21++)
    #endif
    {
        do base=(rand()%10+2)*2;
        while (base==10);
        #if mode == random
        int a1,a2,a11,a21,b1,b2,b11,b21;
        do
        {
        a1=rand()%a.size();
        a2=rand()%a.size();
        } while (a1==a2);
        a11=rand()%a[a1].size();
        a21=rand()%a[a2].size();

        do
        {
        b1=rand()%b.size();
        b2=rand()%b.size();
        } while (b1==b2);
        b11=rand()%b[b1].size();
        b21=rand()%b[b2].size();
        #endif
        uniform_int_distribution<> dist(base*0.25, base*0.75);
        int c1=dist(r), c2;
        do c2=dist(r);
        while (c1==c2);
        cout << endl << endl << num << ". Напишите программу, которая получает на вход число и выводит на экран: " << endl
            << a[a1][a11] << b[b1][b11] << c1 << endl
            << a[a2][a21] << b[b2][b21] << c2 << endl
            <<"из записи этого числа в системе счисления с основанием " << base;
        num++;
    }
    /*int n=0;
    cin >> n;
    auto start = chrono::high_resolution_clock::now();
    for (int i=0; i<20000; i++)
    for (int j=0; j<10000; j++)
        int t=i*j;
    auto finish = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = finish - start;
    cout << endl << "Elapsed time: " << elapsed.count() << " s" << endl;
    */
    return 0;


}


/*#include <iostream>
using namespace std;
int main()
{
    int a[]={0,0,0,0,0,0,0,1,0,2};
    int b[]={0,0,0,0,0,0,0,0,15,15};
    int c[]={0,0,0,0,0,0,0,0,0,0};
    int base=16;

    int up=0;
    for (int i=9; i>=0; i--)
    {
        int value=a[i]+b[i]+up;
        c[i]=value%base;
        up=value/base;
    }
    string alphabet="0123456789abcdef";
    int start=0;
    while (c[start]==0) start++;
    for (; start<10; start++)
    {
        cout << alphabet[c[start]];
    }
    return 0;
}

*/
