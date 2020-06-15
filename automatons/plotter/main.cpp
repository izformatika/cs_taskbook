#include <iostream>
#include <fstream>
#include <vector>


using namespace std;

vector<vector<int>> field;
int x,y;


std::vector<std::string> split(std::string stringToBeSplitted, std::string delimeter)
{
     std::vector<std::string> splittedString;
     int startIndex = 0;
     int  endIndex = 0;
     while( (endIndex = stringToBeSplitted.find(delimeter, startIndex)) < stringToBeSplitted.size() )
    {
       std::string val = stringToBeSplitted.substr(startIndex, endIndex - startIndex);
       splittedString.push_back(val);
       startIndex = endIndex + delimeter.size();
     }
     if(startIndex < stringToBeSplitted.size())
     {
       std::string val = stringToBeSplitted.substr(startIndex);
       splittedString.push_back(val);
     }
     return splittedString;
}

void move(string s)
{
    vector<string> sub=split(s," ");
    int xd(0),yd(0);
    for (auto i: sub)
    {
        xd=0;
        yd=0;
        if (i[0]=='U') yd=-1;
        if (i[0]=='D') yd=1;
        if (i[0]=='R') xd=-1;
        if (i[0]=='L') xd=1;
        int n=stoi(i.substr(1));
        for (int j=0 ;j<n; j++)
        {
            x+=xd;
            y+=yd;
            field[y][x]++;
        }
    }
}

void loop(int times, string s)
{
    vector<string> sub=split(s," ");

    for (int i=0; i<times; i++)
    {
        for (auto i: sub) move(i);
    }
}

int main()
{
    ofstream fs("data.txt");
    field=vector<vector<int>>(50,vector<int>(50,0));
    x=field[0].size()/2;
    y=field.size()/2;
    field[y][x]++;
    loop(3, "U2 R7 D4 L5");
    int k(0);
    for (auto i:field)
    {
        for (auto j:i)
        {
            fs << j <<" ";
            if (j==2)k++;
        }
        fs << endl;
    }
    cout << k << endl;
    return 0;
}
