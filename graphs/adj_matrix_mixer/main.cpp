#include <iostream>
#include <set>
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
        if (matrix[i][j]>0) matrix[j][i]=matrix[i][j];
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
        if (matrix[i][j]>0) matrix[j][i]=matrix[i][j];
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
        if (matrix[i][j]>0) matrix[j][i]=matrix[i][j];
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
        if (matrix[i][j]>0) matrix[j][i]=matrix[i][j];
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
    void show(string labels) const
    {
        for (int l(0); l<vertices.size(); l++) cout << labels[vertices[l]]; cout << endl << len << endl;
    }
    size_t size() {return vertices.size();}
    bool const operator<(const path a) const {return vertices< a.vertices;}
};

void show_paths(vector<set<path>> paths_to, string labels)
{
    for (int p(0); p<paths_to.size(); p++)
    {
        cout << labels[*((*paths_to[p].begin()).vertices.end()-1)]<< ": " << endl;
        auto it = paths_to[p].begin();
        while (it!=paths_to[p].end())
            {
                (*it).show(labels);
                it++;
            }
        cout << endl;
    }
}

void all_paths(vector<path> &res, vector<vector<int>> matrix, string labels)
{
    for (int i(0); i<matrix.size(); i++)
        for (int j(i+1); j<matrix.size(); j++)

        {
            //clog << "finding path " << labels[i] << " -> " << labels[j] << endl;
            vector<set<path>> paths_to(matrix.size());
            paths_to[i].insert(path(0, vector<int>(1, i)));
            //show_paths(path_to, labels);

            for (int v(0); v<matrix.size(); v++)
            {
                for (int cur_from(0); cur_from<matrix.size(); cur_from++)
                for (int cur_to(0);cur_to<matrix.size();cur_to++)
                {
                    if (matrix[cur_from][cur_to]>0)
                    {
                        //clog<<"found " << labels[cur_from] << " - " << labels[cur_to] << endl;
                        auto it = paths_to[cur_from].begin();
                        while (it!=paths_to[cur_from].end())
                        {
                            bool add = true;
                            for (int q(0); q<(*it).vertices.size(); q++)
                            if ((*it).vertices[q]==cur_to) {add=false; break;}
                            if (add)
                            {
                                path cand_path = path(*it);
                                cand_path.vertices.push_back(cur_to);
                                cand_path.len += matrix[cur_from][cur_to];
                                paths_to[cur_to].insert(cand_path);
                            }
                            it++;
                        }
                    }
                }
            }
            for (int p(0); p<paths_to.size(); p++)
            {
                if (*((*(paths_to[p].begin())).vertices.end()-1) != j) continue;
                vector<path> paths (paths_to[p].begin(), paths_to[p].end());
                sort(paths.begin(), paths.end(), [](path a, path b){return a.len < b.len;});
                if ((paths[1].len - paths[0].len == 1 or paths[1].len - paths[0].len == 2) and paths[0].vertices.size() > 5 and paths[0].vertices.size() > paths[1].vertices.size() and paths[1].vertices.size() > 4)
                {
                    //cout << labels[*((*paths_to[p].begin()).vertices.end()-1)] << ": ";
                    //paths[0].show(labels);
                    //paths[1].show(labels);
                    //cout << endl;
                    res.push_back(paths[0]);
                }
            }
        }
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
    int tasks=30;
    for (int taski=0; taski<tasks;taski++)
    {
        ofs << "<question type=\"shortanswer\">" << endl
                <<"<name>" << endl
                <<"<text>" << setw(2) << setfill('0')<<taski << "</text>" << endl
                <<"</name>" << endl
                <<"<questiontext format=\"html\">" << endl
                <<"<text><![CDATA[<p>";
        ofs << "ѕриведЄнна€ матрица смежности описывает граф, изображенный на рисунке. ѕоложительное число соответствует стоимости перехода по ребру из вершины в вершину. ";
        vector<path> p;
        while (p.size()==0)
        {
            reweight(matrix);
            all_paths(p, matrix, labels[0]);
        }
        //p[0].show(labels[0]);
        ofs << "”кажите наименьшую стоимость пути из " << labels[0][(*p[0].vertices.begin())] << " в " << labels[0][(*(p[0].vertices.end()-1))] << "." << endl;
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
            for (size_t j=0; j<order.size(); j++) ofs << "<td>"<<(matrix[order[i]][order[j]]==0?"":to_string(matrix[order[i]][order[j]])) << "</td>";
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
            ofs << p[0].len;
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
