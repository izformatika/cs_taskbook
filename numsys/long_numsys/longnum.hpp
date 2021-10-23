#ifndef LONGNUM_HPP_INCLUDED
#define LONGNUM_HPP_INCLUDED
#include <string>
#include <map>
#include <vector>
#include <iostream>
typedef unsigned long long int dig_sz_t ;

class longnum
{

public:
    bool has_letters();
    bool has_big_letters();
    bool all_letters();
    std::string str() const;
    unsigned long long mod_dec_value() const;
    longnum(int d = 0, unsigned char base = 1);
    longnum(std::string a_s, unsigned char base);
    longnum(std::string a_s, int str_base, int tgt_base);
    longnum& operator=(const longnum& src);
    longnum& operator++();
    longnum operator++(int);
    longnum operator/(const longnum& rhs);

    bool operator>(const longnum& r);
    bool operator>=(const longnum& r);
    bool operator<(const longnum& r);
    bool operator<=(const longnum& r);
    bool operator==(const longnum& r);
    bool operator!=(const longnum& r);
    longnum operator*(const longnum& rhs);
    longnum operator+(const longnum& rhs);
    longnum operator-(const longnum& r);
    bool is_neg() {return m_negative;}
    bool is_pos() {return !m_negative;}
    void setdigit(dig_sz_t where, unsigned char what);
    dig_sz_t count_digits(unsigned char what);
    std::map<unsigned char, dig_sz_t> digit_stat();
    void rand_digs(int qtty);
    void direct(longnum afrom);
    int base(){return int(m_base);}
    bool even();
private:
    void cut_leading_zeros();
    int compare(const longnum& r)
    {
        using namespace std;
        longnum rhs("", m_base);
        if (r.m_base!=m_base) {rhs=longnum(r.str(), r.m_base, m_base);cerr << "warning: comparison doesn't work for big numbers" << endl;}
        else rhs=r;
        if (m_digits.size()>rhs.m_digits.size()) return 1;
        if (m_digits.size()<rhs.m_digits.size()) return -1;
        for (dig_sz_t i=m_digits.size()-1;; i--)
        {
            if (m_digits[i]>rhs.m_digits[i]) return 1;
            if (m_digits[i]<rhs.m_digits[i]) return -1;
            if (i==0) break;
        }
        return 0;
    }
    std::vector<unsigned char> m_digits;
    unsigned char m_base;
    static const std::string alphabet;
    bool m_negative=false;
};



#endif // LONGNUM_HPP_INCLUDED
