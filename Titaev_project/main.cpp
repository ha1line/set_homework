#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <set>
#include <algorithm>

using namespace std;

template <typename T1, typename T2>
ostream& operator<<(ostream& stream, const pair<T1, T2> p);

template <typename T>
ostream& operator<<(ostream& stream, const vector<T>& vec);

template <typename T>
ostream& operator<<(ostream& stream, const vector<T>& vec)
{
    for(const auto& v : vec)
    {
        stream << v << " ";
    }
    return stream;
}

template <typename T1, typename T2>
ostream& operator<<(ostream& stream, const pair<T1, T2> p)
{
    stream << p.first << " " << p.second;
    return stream;
}


string loadFromFile(const string& s, vector<pair<char,double>>& lit)
{
    for(size_t i = 0; i < s.size(); i++)
    {
        if((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z'))
        {
            //      cout << static_cast<int>(s[i]) << " " << endl;
            int num = static_cast<int>(s[i]);
            if(isupper(s[i]))
            {
                // 65 - 90
                lit[num - 65].second++;
            }
            else
            {
                // 97 - 122
                lit[num - 97].second++;
            }
        }
    }

    return s;
};


void literalsCount(const vector<pair<char,double>>& vec, int& count, int& symbols_size)
{
    for(const auto& v : vec)
    {
        symbols_size += v.second;
        if(v.second != 0)
        {
            count++;
        }
    }
}

void symblos(const vector<pair<char, double>>& lit, vector<pair<char, double>>& prob, const double& symbols_size)
{
    for(size_t i = 0; i < prob.size(); i++)
    {
        prob[i].second = (lit[i].second / symbols_size);
        //        cout << prob[i] << endl;
    }
}

double shenon(const vector<pair<char, double>>& prob)
{
    double shenon = 0;

    for(const auto& p : prob)
    {
        if(p.second!=0)
        {
            shenon += p.second * log2(p.second);
            //cout << "p " << p <<"log 2 p" << log2(p) << "shenon " << shenon << endl;
        }
    }
    shenon *= -1;
    return shenon;
}


int main()
{
    vector <pair<char, double>> litteral_to_count =
    {{'a',0}, {'b',0}, {'c',0}, {'d',0}, {'e',0}, {'f',0}, {'g',0}, {'h',0},
    {'i',0}, {'j',0}, {'k',0}, {'l',0}, {'m',0}, {'n',0}, {'o',0}, {'p',0},
    {'q',0}, {'r',0}, {'s',0}, {'t',0}, {'u',0}, {'v',0}, {'w',0}, {'x',0}, {'y',0}, {'z',0}};

    vector <pair<char, double>> prob =
    {{'a',0}, {'b',0}, {'c',0}, {'d',0}, {'e',0}, {'f',0}, {'g',0}, {'h',0},
    {'i',0}, {'j',0}, {'k',0}, {'l',0}, {'m',0}, {'n',0}, {'o',0}, {'p',0},
    {'q',0}, {'r',0}, {'s',0}, {'t',0}, {'u',0}, {'v',0}, {'w',0}, {'x',0}, {'y',0}, {'z',0}};
                ;

    ifstream file("/home/putin/Titaev_project/file.txt");

    string s;

    int N, sum;

    while (getline(file,s)) {
        //cout << s << endl;
        loadFromFile(s, litteral_to_count);
    }

    file.close();

    literalsCount(litteral_to_count, N, sum);

    cout << N << " " << sum << endl;

    symblos(litteral_to_count, prob, sum);

    cout << "Hartli " << log2(N) << endl;
    cout << "Shenon " << shenon(prob) << endl;

    sort(litteral_to_count.begin(), litteral_to_count.end(), [] (const pair<char, double>& lhs,const  pair<char, double>& rhs){
        return lhs.second > rhs.second;
    });
    sort(prob.begin(), prob.end(), [] (const pair<char, double>& lhs,const  pair<char, double>& rhs){
        return lhs.second > rhs.second;
    });

    cout << litteral_to_count << endl;

    cout << prob << endl;

    return 0;
}
