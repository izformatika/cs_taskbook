#ifndef TASKS_HPP_INCLUDED
#define TASKS_HPP_INCLUDED
#include "includes.hpp"
#include <iostream>
int youngest_mom(std::ostream& fs);
int oldest_mom(std::ostream& fs);
int youngest_dad(std::ostream& fs);
int oldest_dad(std::ostream& fs);
int youngest_gmom(std::ostream& fs);
int oldest_gmom(std::ostream& fs);
int youngest_gdad(std::ostream& fs);
int oldest_gdad(std::ostream& fs);
int youngest_aunt(std::ostream& fs);
int oldest_aunt(std::ostream& fs);
int youngest_uncle(std::ostream& fs);
int oldest_uncle(std::ostream& fs);
int most_gchildren_f(std::ostream &fs);
int most_gchildren_m(std::ostream &fs);
int age_between_f(std::ostream &fs);
int age_between_m(std::ostream &fs);
int exact_descendants_age(std::ostream &fs);

#endif // TASKS_HPP_INCLUDED
