
#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include <vector>
#include <ctime>
using namespace std;

class Club {
private:
    string m_clubname;
    string m_stadium;
    int m_capicity;
    float m_rating;
public:
    Club(const string & clubname, const string stadium) {}


};


class League {
private:
    string League_name;
    int club_no;

public: 
    void setClubNo(int n) { club_no = n; }
};
League l1;