
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
    int m_capacity;
    float m_rating;
public:
    Club(const string & clubname, const string stadium, int capacity, float rating)
    :m_clubname(clubname),m_stadium(stadium),m_capacity(capacity),m_rating(rating){}



};


class League {
private:
    string League_name;
    int club_no;
    vector<Club> clubs;
public: 
    void addclub(Club const & club) {
        clubs.push_back(club);
    }
    void setClubNo(int n) { club_no = n; }
};



int main() {}