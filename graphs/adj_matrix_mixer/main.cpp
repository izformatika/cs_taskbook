#include <iostream>
#include <clocale>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <vector>
#include "pics.hpp"

using namespace std;

void fill_matrix_1(vector<vector<int>> &matrix, vector<string> &labels, int &pic)
{
    int n=10;
    int a=0,b=1,c=2,d=3,e=4,f=5,g=6,h=7,i=8,j=9;
    labels.push_back("ABCDEFGHIJ");
    labels.push_back("FEDCBAJIHG");
    pic=0;
    matrix=vector<vector<int>>(n,vector<int>(n,0));
    matrix[a][b]=1;
    matrix[a][c]=1;
    matrix[a][j]=1;
    matrix[b][c]=1;
    matrix[b][h]=1;
    matrix[c][d]=1;
    matrix[d][e]=1;
    matrix[d][f]=1;
    matrix[e][i]=1;
    matrix[e][f]=1;
    matrix[f][g]=1;
    matrix[g][h]=1;
    matrix[h][i]=1;
    matrix[i][j]=1;
    for (size_t i=0;i<matrix.size(); i++)
    for (size_t j=0;j<matrix.size(); j++)
        if (matrix[i][j]==1) matrix[j][i]=1;
}

void fill_matrix_2(vector<vector<int>> &matrix, vector<string> &labels, int &pic)
{
    int n=10;
    int a=0,b=1,c=2,d=3,e=4,f=5,g=6,h=7,i=8,j=9;
    labels.push_back("ABCDEFGHIJ");
    pic=1;
    matrix=vector<vector<int>>(n,vector<int>(n,0));
    matrix[a][b]=1;
    matrix[a][c]=1;
    matrix[a][j]=1;
    matrix[b][d]=1;
    matrix[b][j]=1;
    matrix[b][h]=1;
    matrix[c][d]=1;
    matrix[c][e]=1;
    matrix[d][f]=1;
    matrix[e][i]=1;
    matrix[e][f]=1;
    matrix[f][g]=1;
    matrix[g][h]=1;
    matrix[h][i]=1;
    matrix[i][j]=1;
    for (size_t i=0;i<matrix.size(); i++)
    for (size_t j=0;j<matrix.size(); j++)
        if (matrix[i][j]==1) matrix[j][i]=1;
}

void fill_matrix_3(vector<vector<int>> &matrix, vector<string> &labels, int &pic)
{
    int n=10;
    int a=0,b=1,c=2,d=3,e=4,f=5,g=6,h=7,i=8,j=9;
    labels.push_back("ABCDEFGHIJ");
    labels.push_back("HGIEDJBACF");
    pic=2;
    matrix=vector<vector<int>>(n,vector<int>(n,0));
    matrix[a][b]=1;
    matrix[a][c]=1;
    matrix[a][j]=1;
    matrix[b][e]=1;
    matrix[b][j]=1;
    matrix[c][d]=1;
    matrix[c][f]=1;
    matrix[d][e]=1;
    matrix[d][g]=1;
    matrix[e][i]=1;
    matrix[f][g]=1;
    matrix[f][h]=1;
    matrix[g][h]=1;
    matrix[h][i]=1;
    matrix[i][j]=1;
    for (size_t i=0;i<matrix.size(); i++)
    for (size_t j=0;j<matrix.size(); j++)
        if (matrix[i][j]==1) matrix[j][i]=1;
}

void fill_matrix_4(vector<vector<int>> &matrix, vector<string> &labels, int &pic)
{
    int n=10;
    int a=0,b=1,c=2,d=3,e=4,f=5,g=6,h=7,i=8,j=9;
    labels.push_back("ABCDEFGHIJ");
    pic=3;
    matrix=vector<vector<int>>(n,vector<int>(n,0));
    matrix[a][b]=1;
    matrix[a][c]=1;
    matrix[a][f]=1;
    matrix[b][e]=1;
    matrix[b][j]=1;
    matrix[c][d]=1;
    matrix[d][f]=1;
    matrix[d][e]=1;
    matrix[d][g]=1;
    matrix[e][i]=1;
    matrix[e][j]=1;
    matrix[f][g]=1;
    matrix[f][h]=1;
    matrix[g][h]=1;
    matrix[h][i]=1;
    matrix[i][j]=1;
    for (size_t i=0;i<matrix.size(); i++)
    for (size_t j=0;j<matrix.size(); j++)
        if (matrix[i][j]==1) matrix[j][i]=1;
}

void fill_matrix_5(vector<vector<int>> &matrix, vector<string> &labels, int &pic)
{
    int n=10;
    int a=0,b=1,c=2,d=3,e=4,f=5,g=6,h=7,i=8,j=9;
    labels.push_back("ABCDEFGHIJ");
    pic=4;
    matrix=vector<vector<int>>(n,vector<int>(n,0));
    matrix[a][b]=1;
    matrix[a][c]=1;
    matrix[a][g]=1;
    matrix[b][e]=1;
    matrix[b][j]=1;
    matrix[c][d]=1;
    matrix[c][f]=1;
    matrix[d][h]=1;
    matrix[d][g]=1;
    matrix[e][i]=1;
    matrix[e][j]=1;
    matrix[e][h]=1;
    matrix[f][g]=1;
    matrix[f][h]=1;
    matrix[h][i]=1;
    matrix[i][j]=1;
    for (size_t i=0;i<matrix.size(); i++)
    for (size_t j=0;j<matrix.size(); j++)
        if (matrix[i][j]==1) matrix[j][i]=1;
}


int main()
{
    ofstream ofs("data.txt");
    srand(time(NULL));
    vector<string> labels;
    vector<vector<int>> matrix;
    int pic;
    fill_matrix_5(matrix,labels,pic);
    vector<vector<int>> matrix_1(matrix.size(),vector<int>(matrix.size(),0));
    vector<int> order(matrix.size());
    int tasks=20;
    for (int taski=0; taski<tasks;taski++)
    {
        ofs << "<question type=\"shortanswer\">" << endl
                <<"<name>" << endl
                <<"<text>" << setw(2) << setfill('0')<<taski << "</text>" << endl
                <<"</name>" << endl
                <<"<questiontext format=\"html\">" << endl
                <<"<text><![CDATA[<p>";
        ofs << "ѕриведЄнна€ матрица смежности описывает граф, изображенный на рисунке. ≈диница соответствует ребру, ноль - отсутствию ребра. ќпределите, в каком пор€дке выстроены вершины дл€ построени€ матрицы смежности. ¬ ответе укажите буквенное обозначение вершины на графе, котора€ соответствует вершине V1 в матрице, потом буквенное обозачение вершины на графе, котора§ соответствует вершине V2 в матрице, и так далее дл€ всех вершин. Ѕуквенные обозначени€ указывайте без пробелов и разделителей. ≈сли соответствий между графом и матрицей можно составить несколько, выберите любое. " << endl;
        matrix_1.clear();
        for (size_t i=0; i<order.size(); i++) order[i]=i;
        random_shuffle(order.begin(),order.end());
        ofs << "  ";
        ofs << "<table border=\"1\"><tr><td></td>" <<endl;
        for (size_t i=1; i<=order.size(); i++)
            ofs << "<th>V"<<i<<"</th>";
        ofs << "</tr>"<<endl;
        for (size_t i=0; i<order.size(); i++)
        {
            ofs << "<tr><th>V"<<i+1 << "</th>";
            for (size_t j=0; j<order.size(); j++) ofs << "<td>"<<matrix[order[i]][order[j]] << "</td>";
            ofs << "</tr>"<<endl;
        }
        ofs << "</table></p>" <<endl;
        ofs << "<p><img src=\"@@PLUGINFILE@@/1.png\" alt=\"\" role=\"presentation\" class=\"img-responsive atto_image_button_text-bottom\" width=\"458\" height=\"433\"><br></p>" <<endl;
        ofs << "]]></text>";
        ofs << "<file name=\"1.png\" path=\"/\" encoding=\"base64\">" <<endl;
        ofs << pics[pic] <<endl;
        ofs << "</file>" <<endl;
        ofs << "</questiontext><generalfeedback format=\"html\"><text></text></generalfeedback><defaultgrade>1.0000000</defaultgrade><penalty>0.3333333</penalty><hidden>0</hidden><idnumber></idnumber><usecase>0</usecase>";
        for (int i=0;i<labels.size(); i++)
        {
            ofs << "<answer fraction=\"100\" format=\"moodle_auto_format\"><text>";
            for (auto j:order) ofs << labels[i][j];
            ofs << "</text><feedback format=\"html\"><text></text></feedback></answer>"<<endl;
        }
        ofs << "</question>"<<endl<<endl;

    }
    return 0;
}
