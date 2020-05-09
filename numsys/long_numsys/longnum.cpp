#include "longnum.hpp"
#include <algorithm>
#include <conio.h>
#include <cmath>
unsigned long long int ull_max=18446744073709551615;
const std::string longnum::alphabet="0123456789abcdefghijklmnopqrstuvwxyz";
bool longnum::has_letters()
    {
        if (m_base<11) return false;
        for (auto i:m_digits) if ((int)i>9) return true;
        return false;
    }
    bool longnum::has_big_letters()
    {
        if (m_base<21) return false;
        for (auto i:m_digits) if ((int)i>20) return true;
        return false;
    }
    bool longnum::all_letters()
    {
        if (m_base<11) return false;
        for (auto i:m_digits) if ((int)i<10) return false;
        return true;
    }
    std::string longnum::str() const
    {
        using namespace std;
        if (m_base>36){cerr << "cannot display this number: not enough digits" <<endl; return "";}
        string res("");
        if (m_negative) res+="-";
        for (dig_sz_t i=m_digits.size()-1;; i--)
        {
            if (m_digits[i]>=m_base)
            {
                //clog << "\t";
                //for (auto i: m_digits) clog << (int)i <<":";
                //clog << endl;
                cerr << "incorrect number: digit " << (int)m_digits[i]<<" with base " << (int)m_base <<"!" << endl; return "";}
            res+=alphabet[m_digits[i]];
            if (i==0) {/*res+="_"; res+=m_base; */return res;}
        }
        cerr << "error: number changed while trying to read it" << endl;
        return "";
    }
    unsigned long long longnum::mod_dec_value() const
    {
        using namespace std;
        if (pow(m_base,m_digits.size())>ull_max)
        {
            cerr << "error! cannot store this number in an ull" << endl;
            return 0;
        }
        unsigned long long res=0;
        for (dig_sz_t i=m_digits.size()-1;; i--)
        {
            res=res*m_base+m_digits[i];
            if (i==0) break;
        }
        return res;

    }
    longnum::longnum(int d, unsigned char base):m_base(base),m_negative(false)
    {
        using namespace std;
        if (d<0) {cerr<<"Cannot work with negative numbers yet, making it positive" <<endl; d=-d;}
        m_digits.clear();
        //m_base=base;
        while (d>0)
        {
            m_digits.push_back(d%base);
            d/=base;
        }
    }
    longnum::longnum(std::string a_s, unsigned char base):m_base(base),m_negative(false)
    {
        using namespace std;
        int from=0;
        if (base>36) cerr << "warning: this number will be stored, but won't be displayed due to lack of available digits" << endl;
            if (a_s=="") m_digits.push_back(0);
            else
            {
            if (a_s[0]=='-')
                {m_negative=true;from++;}
            for (dig_sz_t i=from; i<a_s.length(); i++)
            {
                if (a_s[i]>=48 and a_s[i]<=57) m_digits.push_back(a_s[i]-48);
                else if (a_s[i]>=65 and a_s[i]<=90) m_digits.push_back(a_s[i]-55);
                else if (a_s[i]>=97 and a_s[i]<=122) m_digits.push_back(a_s[i]-87);
                else {cerr << "error: cannot recognize digit " << a_s[i] << endl; m_digits.push_back(0);}
            }
            reverse(m_digits.begin(), m_digits.end());
            }
    }
    longnum::longnum(std::string a_s, int str_base, int tgt_base):m_base(tgt_base),m_negative(false)
    {
        using namespace std;
        if (pow(str_base,a_s.length())>ull_max)
        {
            cerr << "error! cannot convert such big numbers yet" << endl;
            m_digits.clear();
            m_digits.push_back(0);
            m_base=tgt_base;
        }
        else
        {
            longnum tmp(a_s,str_base);
            unsigned long long val=tmp.mod_dec_value();
            m_digits.clear();
            while (val>0)
            {
                m_digits.push_back(val%tgt_base);
                val/=tgt_base;
            }
            m_negative=tmp.m_negative;
        }
    }
    longnum& longnum::operator=(const longnum& src)
    {
        m_digits.clear();
        for (auto i: src.m_digits)
            m_digits.push_back(i);
        m_negative=src.m_negative;
        m_base=src.m_base;
        return *this;
    }
    longnum& longnum::operator++()
    {
        using namespace std;
        if (m_negative) {cerr << "cannot work with negative numbers yet" <<endl; return *this;}
        dig_sz_t from=0;
        while (m_digits[from]==m_base-1 and from<m_digits.size()) {m_digits[from]=0;from++;}
        if (from==m_digits.size()) {m_digits.push_back((unsigned char)1);}
        else m_digits[from]++;
        return *this;
    }
    longnum longnum::operator++(int)
    {
        using namespace std;
        if (m_negative) {cerr << "cannot work with negative numbers yet" <<endl; return *this;}
        longnum tmp(*this);
        ++(*this);
        return tmp;
    }
    longnum longnum::operator/(const longnum& rhs)
    {
        using namespace std;
        longnum res("0",m_base);
        if (m_base!=rhs.m_base)
        {
            cerr << "warning: cannot divide two numbers in different numbering systems" << endl;
            res.m_digits.push_back(0);
            return res;
        }
        if (rhs.mod_dec_value()>this->mod_dec_value())
        {
            cerr << "warning: dividing a smaller number by a bigger one failed, cannot work with fractions yet" << endl;
            res.m_digits.push_back(0);
            return res;
        }
        longnum tmp(this->str(), m_base);
  //      cout << (tmp>rhs) << endl;

        while (tmp>rhs)
        {
            tmp=tmp-rhs;
//            cout << tmp.str() <<endl;
            res++;
            //cout << res.str() << endl;
        }
        if (m_negative!=rhs.m_negative) res.m_negative=true;
        return res;

    }

    bool longnum::operator>(const longnum& r)
    {
        if (compare(r)==1) return true;
        return false;

    }
    bool longnum::operator>=(const longnum& r)
    {
        if (compare(r)>-1) return true;
        return false;

    }
    bool longnum::operator<(const longnum& r)
    {
        if (compare(r)==-1) return true;
        return false;

    }
    bool longnum::operator<=(const longnum& r)
    {
        if (compare(r)<1) return true;
        return false;

    }
    bool longnum::operator==(const longnum& r)
    {
        if (compare(r)==0) return true;
        return false;

    }
    bool longnum::operator!=(const longnum& r)
    {
        if (compare(r)!=0) return true;
        return false;

    }
    longnum longnum::operator*(const longnum& rhs)
    {
        using namespace std;
        //definitely NOT optimal
        longnum res("",m_base);
        if (m_base!=rhs.m_base)
        {
            cerr << "warning: cannot multiply two numbers in different numbering systems" << endl;
            res.m_digits.push_back(0);
            return res;
        }
        res.m_digits.clear();
        //TODO: this will fail
        for (unsigned long long int i=0; i<rhs.mod_dec_value(); i++) res=res+*this;
        if (rhs.m_negative!=m_negative) res.m_negative=true;
        return res;
    }
    longnum longnum::operator+(const longnum& rhs)
    {
        using namespace std;
        longnum res("", m_base);
        res.m_digits.clear();
        if (m_negative)
        {
            cerr << "summing failed: first argument negative, cannot work with negative values yet" << endl;
            return res;
        }
        if (rhs.m_negative)
        {
            cerr << "summing failed: second argument negative, cannot work with negative values yet" << endl;
            return res;
        }
        if (m_base!=rhs.m_base)
        {
            cerr << "warning: cannot sum two numbers in different numbering systems" << endl;
            return res;
        }

        unsigned char up=0;
        for (dig_sz_t i=0;;i++)
        {
            unsigned char cur_val=up;
            if (rhs.m_digits.size()>i) cur_val+=rhs.m_digits[i];
            if (m_digits.size()>i) cur_val+=m_digits[i];
            //clog << i<<": "<<int(cur_val) <<endl;
            if ((int)cur_val==0 and rhs.m_digits.size()<=i and m_digits.size()<=i) break;
            res.m_digits.push_back(cur_val%m_base);
            up=cur_val/m_base;
        }
        return res;
    }
    longnum longnum::operator-(const longnum& r)
    {
        using namespace std;
//        clog << endl << "[" << str() << " - " << r.str() << "]"<< endl;
        longnum res("", m_base);
        res.m_digits.clear();
        if (m_negative or r.m_negative) {cerr << "cannot work with negative numbers yet" <<endl; return res;}
        if (m_base!=r.m_base)
        {
            cerr << "warning: cannot subtract two numbers in different numbering systems" << endl;
            return res;
        }
        res=*this;
        longnum rhs("", m_base);
        rhs=r;
        if (rhs>res)
        {
            swap(rhs,res);
            clog << "negative" << endl;
            res.m_negative=true;
        }
        //clog << rhs.m_digits.size() <<endl;
        for (dig_sz_t i=0;i<rhs.m_digits.size();i++)
        {
//            clog <<i <<endl;
            if ((int)res.m_digits[i]<(int)rhs.m_digits[i])
            {
                //clog << "need a loan: " << (int)res.m_digits[i]<< " - " << (int)rhs.m_digits[i] << endl;
                int j=i+1;
                while ((int)res.m_digits[j]==0) j++;
                res.m_digits[j]--;
                for (dig_sz_t k=j-1; k>=i; k--) {res.m_digits[k]+=m_base-1;}
                res.m_digits[i]+=1;
//                for (int k=res.m_digits.size()-1; k>=0; k--) cout <<"["<<(int)res.m_digits[k]<<"]";
    //            clog << res.str() << endl;
            }

            res.m_digits[i]=(int)res.m_digits[i]-(int)rhs.m_digits[i];
      //      clog <<"wat" <<endl;
        }
        //clog << "yes" <<endl;
        while ((int)res.m_digits[res.m_digits.size()-1]==0) res.m_digits.erase(res.m_digits.end()-1);
        return res;
    }
    void longnum::setdigit(dig_sz_t where, unsigned char what)
    {
        using namespace std;
        if (what>=m_base) {cerr << "impossible digit for this numbering system" << endl;return;}
        while (m_digits.size()-1<where) m_digits.push_back(0);
        m_digits[where]=m_digits[where]+what;
    }
    dig_sz_t longnum::count_digits(unsigned char what)
    {
        dig_sz_t res=0;
        for (auto i: m_digits)
        {
            if (i==what) res++;
        }
        return res;
    }
    std::map<unsigned char, dig_sz_t> longnum::digit_stat()
    {
        std::map<unsigned char, dig_sz_t> res;
        for (auto i: m_digits)
        {
            res[i]++;
        }
        return res;
    }

    void longnum::rand_digs(int qtty)
    {
        using namespace std;
        if (qtty<=0) return;
        if (m_base==2)//different digit distribution. we want 0.3>zeros>0.7 in binary and ~0.1 zeros in all other numsys
        {
            do
            {
                m_digits.clear();
                for (int i=1; i<qtty; i++)
                {
                    m_digits.push_back(rand()%2);
                }
                m_digits.push_back(1);
            }
            while (count_digits(0)<0.3*m_digits.size() or count_digits(0)>0.75*m_digits.size());
        }
        else
        {
        m_digits.clear();

        for (int i=1; i<qtty; i++)
        {
            unsigned char curdig=0;
            if (rand()%10==0) curdig=0;
            else curdig=rand()%(int(m_base)-1)+1;
            m_digits.push_back(curdig);
        }
        m_digits.push_back(rand()%(int(m_base)-1)+1);
        }


        while (!(m_base<=10 or (m_base<=16 and has_letters()) or has_big_letters()))
        {
            m_digits[rand()%m_digits.size()]=rand()%int(m_base);
        }
        cut_leading_zeros();
    }

    void longnum::direct(longnum from)
    {
        using namespace std;
        m_digits.clear();
        if (from.m_base<m_base)
        {
            float unite_f=log(m_base)/log(from.m_base);
            if (ceil(unite_f)!=unite_f)
            {
                cerr << "direct conversion not available, inconvenient bases" <<endl;
                m_digits.push_back(0);
                return;
            }
            int unite=unite_f;
            //clog << "uniting" <<endl;
            //clog << from.m_digits.size()<<" "<<unite <<endl;
            //getch();
            int curdig=0;
            for (int i=0; i<from.m_digits.size(); i+=unite)
            {
                //clog << i <<endl;
                //getch();
                for (int j=min(i+unite-1,int(from.m_digits.size()-1)); j>=i; j--){
                curdig*=int(from.m_base);
                //clog << "digit " << int(from.m_digits[j]) <<endl; getch();
                curdig+=int(from.m_digits[j]);
                }
                //clog << curdig <<endl;
                /*if (i!=0 and i%int(unite)==0)*/ {m_digits.push_back(curdig);curdig=0;}
            }
            //m_digits.insert(m_digits.begin(),curdig);
        }
        else//split
        {
            float split=log(from.m_base)/log(m_base);
            if (ceil(split)!=split)
            {
                cerr << "direct conversion not available, inconvenient bases" <<endl;
                m_digits.push_back(0);
                return;
            }
            for (int i=0; i<from.m_digits.size(); i++)
            {
                int curdig=from.m_digits[i];
                for (int j=0; j<split; j++)
                {
                    m_digits.push_back(curdig%m_base);
                    curdig/=m_base;
                }
            }
            cut_leading_zeros();
        }
    }

    void longnum::cut_leading_zeros()
    {
        while (*(m_digits.end()-1)==0) m_digits.erase(m_digits.end()-1);
    }
