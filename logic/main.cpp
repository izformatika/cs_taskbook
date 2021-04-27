#include "logic_expressions.h"
#include <boost/algorithm/string.hpp>
#define PIMPL shared_ptr<impl>
#define POR shared_ptr<disjunction>
#define PAND shared_ptr<conjunction>
#define PNOT shared_ptr<neg>
#define PEQ shared_ptr<eq>

bool allbraces;


bool check_table(vector<vector<bool>> sol)
{
    for (size_t c1(0); c1<sol[0].size()-1; c1++)
    for (size_t c2(c1+1); c2<sol[0].size()-1; c2++)
    {
        //vector<bool> same(sol.size(), true);
        int diff(0);
        for (size_t r(0); r<sol.size(); r++)
        if (sol[r][c1]!=sol[r][c2]) {diff++;}
        if (diff == 0) return false;
        /*
        //a table is bad if it has two cols where either all cells are the same or contain different values only in rows that are otherwise the same (hence we cant tell between these two variables)
            //actually no, that should be checked only after removing some lines...
        if (diff%2 == 0)
        {
            vector<pair<int,int>> dangerous_row_couples;
            for (size_t r1(0); r1<sol.size(); r1++)
            {
                for (size_t r2(0); r2<sol.size(); r2++)
                {
                    bool enough(false);
                    for (size_t c(0); c<sol[0].size(); c++)
                        if (sol[r1][c]!=sol[r2][c] and (c!=c1 or c!=c2)) {enough = true; break;}
                    if (enough) break;
                    cout << r1 << " " << r2 << endl;
                    dangerous_row_couples.push_back(pair<int,int>(r1,r2));
                }
            }
        }*/

    }
    return true;
}

void gen_func_with_sparse_table()
{
    ofstream ofs("data.txt");
    shared_ptr<conjunction> root = make_shared<conjunction> (make_shared<var> (NULL, ""), make_shared<var> (NULL, ""));
    while (true)
    {
        vars.clear();
        root->populate(3,0.1);
        int solutions(0);
        vector<vector<bool>> sol(pow(2, vars.size()), vector<bool>(vars.size() + 1, false));
        for (int mask(0); mask<pow(2, vars.size());mask++)
        {
            int curmask = mask;
            for (size_t j(0); j<vars.size(); j++)
            {
                *vars[j] = curmask%2;
                sol[mask][j] = curmask%2;
                curmask /= 2;
            }
            //cout << root->wrap(false,false) << " = " << root->value() << endl;
            if (root->value()==1) {solutions++;sol[mask][vars.size()] = true;}
        }
        int nos = pow(2, vars.size()) - solutions;
        bool needed = (solutions < nos);
        for (int i(0); i<sol.size(); i++)
        {
            if (sol[i][sol[0].size()-1] != needed)
            {sol.erase(sol.begin()+i); i--;}
        }

        if (vars.size() == 5 and (solutions == 4 or solutions == 5 or solutions == 6 or nos == 4 or nos == 5 or nos == 6) and check_table(sol))
        {
            ofs << root->wrap(true) << endl;
            ofs << root->fulltext() << endl;
            ofs << root->count_rotations() << endl;
            ofs << solutions << " " << nos << endl;
            for (auto i: vars)
            {
                ofs << i->str(true) << " ";
            }
            ofs << endl;
            for (auto i: sol)
            {
                for (int j(0); j<i.size()-1; j++)
                    ofs << i[j] << " ";
                ofs << endl;
            }
            break;
        }
    }
    /*TODO: generate smaller table as well. drop rows and digits one-by-one.
    check if the remaining table is recognizeable, i.e. if it has a unique row\col:
    only number of 1 or 0 that fits the original qtty. then check the rest of the table
    for recognizeability considering rows\cols left

    */
}

std::string ReplaceString(std::string subject, const std::string& search,
                          const std::string& replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
    return subject;
}

bool shuffled_ok(vector<int> ord)
{
    for (int i(1); i<ord.size(); i++)
        if (ord[i]==ord[i-1]+1) return false;
    return true;
}

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

struct task_src
{
    shared_ptr<expr> exp;
    vector<string> part_truth_table;
    task_src(shared_ptr<expr> e, vector<string> ptt):exp(e), part_truth_table(ptt) {}
    task_src(){}
};
/*
void make_task_from_file()
{

}

void make_task_on_the_fly()
{

}*/

void shuffle_table()
{
    int tasks_from_each(20);
    mt19937 mt(time(0));

    ifstream ifs("data.txt");
    ofstream ofs("task.xml");
    /*TODO: insert manually from file (no eval yet)*/
    make_vars(5);
    auto logexpr_l = make_shared<conjunction>(make_shared<conjunction>(make_shared<disjunction>(make_shared<disjunction>(vars[0], vars[1]), make_shared<impl>(vars[1], vars[2])), make_shared<disjunction>(make_shared<conjunction>(vars[2], vars[2]), make_shared<impl>(vars[0], vars[3]))), make_shared<disjunction>(make_shared<neg>(make_shared<eq>(vars[0], vars[4])), make_shared<impl>(make_shared<neg>(vars[3]), make_shared<eq>(vars[2], vars[4]))));

    int rot_qtty=logexpr_l->count_rotations();
    uniform_int_distribution<> uid(0, pow(2, rot_qtty)-1);

    moodle_header(ofs);
    string buf;
    string logexpr;
    getline(ifs, logexpr);
    getline(ifs, buf);
    int yes(0), no(0);
    ifs >> rot_qtty >> yes >> no;
    //cout << rot_qtty << " " << yes << " " << no << endl;
    getline(ifs, buf);

    getline(ifs, buf);
    vector<string> labels;
    buf = ReplaceString(ReplaceString(buf, " \r\n", "\r\n"), "  ", " ");
    boost::split(labels, buf, boost::is_any_of(" "));
    if (labels[labels.size()-1] == "") labels.erase(labels.end()-1);

    bool first_gone(false);
    int tasks(0);

    while (!ifs.eof())
    {
        vector<vector<int>> values;
        while (true)
        {
            getline(ifs, buf);
            if (buf == "") break;
            values.push_back(vector<int>(labels.size(), 0));
            for (int i(0); i<buf.size(); i+=2) values[values.size()-1][i/2]=(buf[i]=='-'?(-1):(buf[i]-'0'));
        }
        if (!first_gone) {first_gone=true; continue;}
        /*for (auto i: values){
            for (auto j: i) cout << j << " "; cout << endl;
            }*/
        for (int t(0); t<tasks_from_each; t++)
        {
        auto cur_logexpr = logexpr_l->clone();

        dynamic_bitset<> rot_mask(rot_qtty,uid(mt));
        cur_logexpr->make_rot(rot_mask, 0, rot_qtty-1);
        logexpr = cur_logexpr->wrap();

        vector<int> ord(labels.size());
        for (int i(0); i<labels.size(); i++) ord[i]=i;

        do
        random_shuffle(ord.begin(), ord.end());
        while (!shuffled_ok(ord));

        string ans;
        for (auto i: ord) ans+=labels[i];
        //cout << ans << endl;

        vector<vector<char>> sh_values(values.size(), vector<char>(labels.size(), 0));
        for (int row(0); row<values.size(); row++)
        for (int col(0); col<labels.size(); col++)
            sh_values[row][col] = (values[row][ord[col]]==-1?' ':values[row][ord[col]]+'0');
        /*for (auto i: sh_values){
            for (auto j: i) cout << j << " "; cout << endl;
            }*/
        random_shuffle(sh_values.begin(), sh_values.end());
        stringstream ss;
        ss << "Логическая функция F задаётся выражением:<br> " << endl << logexpr << endl;
        ss << "<br>Дан частично заполненный фрагмент, содержащий неповторяющиеся строки таблицы истинности функции F.<br>" << endl <<
            "Определите, какому столбцу таблицы истинности соответствует каждая из переменных ";
        for (int i(0); i<labels.size()-1; i++) ss << labels[i] << ", "; ss << labels[labels.size()-1] << "." << endl;
        ss << "<table border=1><tr>";
        for (int i(0); i<labels.size(); i++) ss << "<th>переменная " << i+1 << "</th>";
        ss << "<th>значение функции</th></tr>"<<endl<<"<tr>";
        for (int i(0); i<labels.size(); i++) ss << "<td>?</td>";
        ss << "<td>F</td></tr>"<<endl;
        for (auto row: sh_values)
        {
            ss << "<tr>";
            for (auto v: row)
                ss << "<td>" << v << "</td>";
            ss << "<td>" << (yes<no) << "</td>";

            ss << "</tr>" << endl;
        }
        ss << "</table>В ответе напишите буквы переменных в том порядке, в котором идут соответствующие им столбцы (сначала буква, соответствующая первому столбцу; затем буква, соответствующая второму столбцу, и т. д.)." <<
        " Буквы в ответе пишите подряд, никаких разделителей между буквами ставить не нужно.<br>" << endl;
        ss << "<i>Пример. Пусть задано выражение x → y, зависящее от двух переменных x и y, и фрагмент таблицы истинности:" << endl;
        ss << "<table border=1><tr><th>переменная 1</th><th>переменная 2</th><th>значение функции</th></tr>"<<endl<<"<tr>";
        ss << "<tr><td>?</td><td>?</td><td>F</td></tr>" << endl;
        ss << "<tr><td>0</td><td>1</td><td>0</td></tr>" << endl;
        ss << "</table>Тогда первому столбцу соответствует переменная y, а второму столбцу – переменная x. В ответе нужно написать: yx. </i>" << endl;


        moodle_write_question(ofs, tasks, ss.str(), ans);
        tasks++;
        }
    }
    ofs << "</quiz>" << endl;
//line 1, 2 - ignore
//line 3 - get rotation number
//line 4 - get yes-no (n = min)
//line 5 - get labels
//n lines - ignore
//until the end:
    //1 line - empty, ignore
    //several (<=n) nonempty lines - shuffle lines and cols

}

void test_rotations()
{
    make_vars(5);
    auto a = make_shared<conjunction>(make_shared<disjunction>(make_shared<impl>(make_shared<eq>(vars[0], vars[1]), make_shared<disjunction>(vars[1], vars[0])), make_shared<impl>(make_shared<disjunction>(vars[0], vars[2]), make_shared<eq>(vars[2], vars[0]))), make_shared<disjunction>(make_shared<disjunction>(make_shared<disjunction>(vars[0], vars[3]), make_shared<impl>(vars[1], vars[3])), make_shared<impl>(vars[1], make_shared<impl>(vars[1], vars[4]))));
    cout << a->wrap() << endl;
    int rot_qtty=a->count_rotations();
    cout << rot_qtty << endl;
    dynamic_bitset<> rot_mask(rot_qtty,0);
    for (int i(0); i<pow(2, rot_qtty); i++)
    {
        rot_mask = dynamic_bitset<>(rot_qtty, i);
        auto cur_rot = a->clone();
        cur_rot->make_rot(rot_mask, 0, rot_qtty-1);
        cout << cur_rot->wrap() << endl;
    }
}


void polyakov_3(int id)
{
    make_vars(3);
    map<int, task_src> cat;
    cat[175]=task_src (dynamic_pointer_cast<expr> (PIMPL(new impl(POR(new disjunction(vars[2], vars[1])),PEQ(new eq(vars[0], vars[2]))))),{"0 -1 0", "0 -1 -1"});

    if (id == 175) cout << cat[175].exp->wrap() << endl;
    /*auto p178=PIMPL(POR(PNOT(vars[2]), PNOT(vars[1])), PEQ(vars[0], vars[2]));
    vector<string> t178={"1 1 -1","1 -1 -1"};

    auto p180=POR(PIMPL(POR(vars[1], vars[2]), vars[0]), PEQ(vars[0], vars[2]));
    vector<string> t180={"0 0 -1", "0 -1 -1"};*/

}

int main()
{
    allbraces = false;
    style = ampersand;
    fill_op_symb();
    srand(time(0));

    catalogue.push_back(make_shared<conjunction>(make_shared<var>(NULL, ""), make_shared<var>(NULL, "")));
    catalogue.push_back(make_shared<disjunction>(make_shared<var>(NULL, ""), make_shared<var>(NULL, "")));
    catalogue.push_back(make_shared<impl>(make_shared<var>(NULL, ""), make_shared<var>(NULL, "")));
    catalogue.push_back(make_shared<eq>(make_shared<var>(NULL, ""), make_shared<var>(NULL, "")));
    catalogue.push_back(make_shared<neg>(make_shared<var>(NULL, "")));

    //gen_func_with_sparse_table();


    //shuffle_table
    polyakov_3(175);
    return 0;
}
