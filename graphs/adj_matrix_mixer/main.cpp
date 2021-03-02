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

void fill_matrix_4_1(vector<vector<int>> &matrix, vector<string> &labels, int &pic)
{
    int n=10;
    int a=0,b=1,c=2,d=3,e=4,f=5,g=6,h=7,i=8,j=9;
    labels.push_back("ABCDEFGHIJ");
    pic=3;
    matrix=vector<vector<int>>(n,vector<int>(n,0));
    matrix[a][b]=1;
    matrix[a][c]=2;
    matrix[a][f]=3;
    matrix[b][e]=4;
    matrix[b][j]=1;
    matrix[c][d]=2;
    matrix[d][f]=3;
    matrix[d][e]=4;
    matrix[d][g]=1;
    matrix[e][i]=2;
    matrix[e][j]=3;
    matrix[f][g]=4;
    matrix[f][h]=1;
    matrix[g][h]=2;
    matrix[h][i]=3;
    matrix[i][j]=10;
    for (size_t i=0;i<matrix.size(); i++)
    for (size_t j=0;j<matrix.size(); j++)
        if (matrix[i][j]>0) matrix[j][i]=matrix[i][j];
}

void fill_matrix_5(vector<vector<int>> &matrix, vector<string> &labels, int &pic)
{
    int n=10;
    int a=0,b=1,c=2,d=3,e=4,f=5,g=6,h=7,i=8,j=9;
    labels.push_back("ABCDEFGHIJ");//TODO: two answers!
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

void reweight(vector<vector<int>> &matrix)
{
    for (int i(0); i<matrix.size(); i++)
        for (int j(i+1); j<matrix[0].size(); j++)
            if (matrix[i][j]>0)
            {
                int r(rand()%9+1);
                matrix[i][j] = r;
                matrix[j][i] = r;
            }
}

void corresp()
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
        ofs << "ѕриведЄнна€ матрица смежности описывает граф, изображенный на рисунке. ≈диница соответствует ребру, ноль - отсутствию ребра. ќпределите, в каком пор€дке выстроены вершины дл€ построени€ матрицы смежности. ¬ ответе укажите буквенное обозначение вершины на графе, котора€ соответствует вершине V1 в матрице, потом буквенное обозачение вершины на графе, котора€ соответствует вершине V2 в матрице, и так далее дл€ всех вершин. Ѕуквенные обозначени€ указывайте без пробелов и разделителей. ≈сли соответствий между графом и матрицей можно составить несколько, выберите любое. " << endl;
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
}

struct path
{
    int len = 999999999;
    vector<int> vertices;
    bool done = false;
    int runner_up = 999999999;
    path(int l, vector<int> v):len(l),vertices(v){}
    path():len(-1),vertices(0){}
    show(string labels)
    {
        cout << "\t"; for (int l(0); l<vertices.size(); l++) cout << labels[vertices[l]]; cout << endl << "\t" << len << endl;
    }
    size_t size() {return vertices.size();}
};

void show_paths(vector<path> path_to, string labels)
{
for (int k(0); k<path_to.size(); k++) {cout << labels[*(path_to[k].vertices.end()-1)] << ": " << path_to[k].len << "(+" << path_to[k].runner_up << "): ";for (int l(0); l<path_to[k].size(); l++) cout << labels[path_to[k].vertices[l]]; cout << endl;}
}

void all_paths(vector<path> &p, vector<vector<int>> matrix, string labels)
{/*
    for (int i(0); i<matrix.size(); i++)
        for (int j(i+1); j<matrix.size(); j++)*/int i = 2; int j = 5;
 //       {
            //clog << "finding path " << labels[i] << " -> " << labels[j] << endl;
            vector<path> path_to(matrix.size());
            for (int k(0); k<path_to.size(); k++) path_to[k] = path(999999, vector<int>(1, k));
            path_to[i] = path(0, vector<int>(1, i));
            //show_paths(path_to, labels);

            //while (*(path_here[0].vertices.end())!=j)
//            {
                //sort(path_to.begin(), path_to.end(), [](path a, path b){return a.len < b.len;});
                //cout << endl;
                //show_paths(path_to, labels);
                for (int v(0); v<matrix.size(); v++)
                {
                    int cur_from = -1;//*(path_to[0].vertices.end()-1);
                    for (int l(0); l<path_to.size(); l++)
                        if (!path_to[l].done)
                            if (cur_from == -1 or path_to[cur_from].len > path_to[l].len) cur_from = l;
                    //cout << cur_from;
                    for (int cur_to(0);cur_to<matrix.size();cur_to++)
                    {
                        if (matrix[cur_from][cur_to]>0)
                        {
                            clog<<"found " << labels[cur_from] << " - " << labels[cur_to] << endl;
                            //for (int l(0); l<path_to[0].vertices.size(); l++) cout << labels[path_to[0].vertices[l]]; cout << endl;
                            path cand_path = path(path_to[cur_from]);
                            //for (int l(0); l<cand_path.vertices.size(); l++) cout << labels[cand_path.vertices[l]]; cout << endl;
                            cand_path.vertices.push_back(cur_to);
                            cand_path.len += matrix[cur_from][cur_to];
                            int better = path_to[cur_to].len - cand_path.len;
                            if (path_to[cur_to].len<999999 and better<0 and -better<path_to[cur_to].runner_up) {bool good(true); for (int m(0);m<cand_path.vertices.size(); m++) if (cand_path.vertices[m]==cur_to) {good=false; break;} if (good) path_to[cur_to].runner_up = -better;}
                            if (path_to[cur_to].len==999999 or better>0)
                                        {path_to[cur_to] = cand_path; path_to[cur_to].runner_up = better;}
                        }
                    }
                    path_to[cur_from].done = true;

                    cout << endl;
                    show_paths(path_to, labels);
                }
  /*
                active_queue.erase(active_queue.begin());
                for (int cur_to(0); cur_to<matrix.size(); cur_to++)
                {
                    if (matrix[cur_from][cur_to]>0)
                    {

                        active_queue.push_back(cur_to);
                    }
                }
            }
            for (int k(0); k<matrix.size(); k++) {cout << labels[k] << ": ";for (int l(0); l<path_here[k].size(); l++) cout << labels[path_here[k].vertices[l]]; cout << endl;}
        }*/
}

void min_path()
{
    ofstream ofs("data.txt");
    srand(time(NULL));
    vector<string> labels;
    vector<vector<int>> matrix;
    int pic;
    fill_matrix_4_1(matrix,labels,pic);
    vector<vector<int>> matrix_1(matrix.size(),vector<int>(matrix.size(),0));
    vector<int> order(matrix.size());
    int tasks=1;
    for (int taski=0; taski<tasks;taski++)
    {
        ofs << "<question type=\"shortanswer\">" << endl
                <<"<name>" << endl
                <<"<text>" << setw(2) << setfill('0')<<taski << "</text>" << endl
                <<"</name>" << endl
                <<"<questiontext format=\"html\">" << endl
                <<"<text><![CDATA[<p>";
        ofs << "ѕриведЄнна€ матрица смежности описывает граф, изображенный на рисунке. ѕоложительное число соответствует стоимости перехода по ребру из вершины в вершину, ноль - отсутствию ребра. ”кажите наименьшую стоимость пути из ";
        vector<path> p;
        all_paths(p, matrix, labels[0]);
        matrix_1.clear();
        for (size_t i=0; i<order.size(); i++) order[i]=i;
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
}



int main()
{
    min_path();
    return 0;
}
