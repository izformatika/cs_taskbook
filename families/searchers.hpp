#ifndef SEARCHERS_HPP_INCLUDED
#define SEARCHERS_HPP_INCLUDED
#include <vector>
#include <set>
int check();
std::vector<std::pair<int,int>> parents(int g);
std::vector<std::pair<int,int>> fathers();
std::vector<std::pair<int,int>> mothers();
std::vector<std::pair<int,int>> gparents(int g);
std::vector<std::pair<int,int>> gfathers();
std::vector<std::pair<int,int>> gmothers();

std::vector<std::pair<int,int>> sibling(int g);

std::vector<std::pair<int,int>> uncleaunt(int g);
std::vector<std::pair<int,int>> aunts();
std::vector<std::pair<int,int>> uncles();
std::set<int> best_age(std::vector<std::pair<int,int>> p, bool youngest=true, bool scnd=true);
std::set<int> most_often(std::vector<std::pair<int,int>> p, bool scnd=true);
std::vector<std::pair<int,int>> age_by_birth(std::vector<std::pair<int,int>> p, int from, int to);
std::set<int> descendants(int of, int age = -1);
#endif // SEARCHERS_HPP_INCLUDED
