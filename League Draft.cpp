
#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <random>
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
        cout << m_clubname << '\n' << m_stadium << " Stadium\n" 
            << "Capicity: " << m_capacity << endl;
    }
    friend void gamesim(const Club& club1, const Club& club2);
    

};


void gamesim(const Club& club1, const Club& club2) {
    random_device rd;  // Obtain a random number from hardware
    mt19937 gen(rd());  // Seed the generator
    uniform_real_distribution<> distr(0, 100);  // Define the range
    static int city = 0;
    float difference = abs(club1.m_rating - club2.m_rating);
    float winner = distr(gen);
    cout << endl << "winner : " << winner << "\n difference: " << difference << "\n";
    if (club1.m_rating > club2.m_rating) {
        if (winner <= (50 + (difference * 1.5))) {
           cout << club1.m_clubname << " is the winner ";
        }
        else { cout << club2.m_clubname << " is the winner"; }
    }
    else {
        if (winner <= (50 + (difference * 1.5))) {
            cout << club2.m_clubname << " is the winner!\n";
        }
        else {
            cout << club1.m_clubname << " is the winner!\n";
        }
    }
    cout << endl << "city: "<< city << endl;
}

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
    int x = time(0);
    srand(x);
    League premier_league("Premier League");
    Club club1("Manchester United", "Old Trafford", 74000, 84.5);
    Club club2("Liverpool", "Anfield", 54000, 94.7);
    Club club3("Chelsea", "Stamford Bridge", 42000, 88.3);
    Club club4("Arsenal", "Emirates", 60260, 90.4);
    Club club5("Manchester City", "Etihad", 55000, 95.6);
    vector<Club> clubs = { club1,club2,club3,club4,club5 };
    for (auto club : clubs) {
        premier_league.addclub(club);
    }
    premier_league.displayLeague();
    gamesim(club5, club1);
    gamesim(club1,club5);
}