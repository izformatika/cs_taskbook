#include <locale>
#include <iostream>
#include <set>
#include <algorithm>
#include <fstream>

using namespace std;


bool dif_letters(wstring s)
{
    for (int i=0; i<s.size(); i++)
    for (int j=i+1; j<s.size(); j++)
    if (s[i]==s[j]) return false;
    return true;
}

bool has(wstring s, wchar_t l)
{
    for (int i=0; i<s.size(); i++)
        if (s[i]==l) return true;
    return false;
}
int vowels(wstring s)
{
    int res=0;
    for (int i=0; i<s.size(); i++)
        if (s[i]=='¸' or s[i]=='ó' or s[i]=='å' or s[i]=='û' or s[i]=='à' or s[i]=='î' or s[i]=='ý' or s[i]=='ÿ' or s[i]=='è' or s[i]=='þ') res++;
    return res;
}
int consonants(wstring s)
{
    return s.size()-vowels(s);
}


bool myfilter(wstring s)
{
    return s.length()!=6 or !dif_letters(s) or vowels(s)!=2 or consonants(s)!=3;
}

int main()
{
    setlocale(LC_ALL,"ru_RU.utf8");
    std::wcout << std::hex << L"à";
    /*int a=int('ü');
    cout << a << endl;
    */
    wchar_t a(-4);
    wcout << a << endl;

    wifstream ifs("russian_nouns.txt");
    wofstream ofs("data.txt");
    vector<wstring> words;
    wstring tmp;
    while (ifs>>tmp ) {words.push_back(tmp);}
    auto del=remove_if(words.begin(),words.end(),myfilter);
    words.erase(del,words.end());
    for (auto i:words)
        ofs << i << endl;
    return 0;
}
