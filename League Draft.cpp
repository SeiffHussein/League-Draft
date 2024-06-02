
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

    void  display() const {
        cout << m_clubname << endl;
    }



};


class League {
private:
    string League_name;
    int club_no;
    vector<Club> clubs;
public: 
    League(string const name) : League_name(name), club_no(0) {}
    void addclub(Club const & club) {
        clubs.push_back(club);
        club_no = clubs.size(); //need something more efficient O(n)
    }
    int getClubno() { return club_no; }
    void displayLeague()const {
        cout << "League name: " << League_name << endl;
        cout << "Number of clubs: " << club_no << endl; 
        cout << "clubs:\n";
        for (const auto & Club : clubs) {
            Club.display();

    }
                        }

};



int main() {
    League premier_league("Premier League");
    Club club1("Manchester United", "Old Trafford", 74000, 84.5);
    Club club2("Liverpool", "Anfield", 54000, 94.7);
    Club club3("Chelsea", "Stamford Bridge", 42000, 88.3);
    Club club4("Arsenal", "Emirates Stadium", 60260, 90.4);
    Club club5("Manchester City", "Etihad Stadium", 55000, 95.6);
    vector<Club> clubs = { club1,club2,club3,club4,club5 };
    for (auto club : clubs) {
        premier_league.addclub(club);
    }
    premier_league.displayLeague();
}