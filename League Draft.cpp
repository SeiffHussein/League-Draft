
#include <iostream>
#include <cmath>
#include <string>
#include <algorithm>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <random>
#include <utility>
using namespace std;

class Club {
private:
    string m_clubname;
    string m_stadium;
    int m_capacity;
    double m_rating;
public:
    Club(const string & clubname, const string stadium, int capacity, double rating)
    :m_clubname(clubname),m_stadium(stadium),m_capacity(capacity),m_rating(rating){}

    void  display() const {
        cout << m_clubname << '\n' << m_stadium << " Stadium\n" 
            << "Capicity: " << m_capacity << endl << "\n\n";
    }

    string getclubname() { return m_clubname; }



};


class League {
private:
    string League_name;
    int club_no;
    vector<Club> clubs;
    vector<vector <pair<Club&, Club&>>> matchday;

public: 
    League(string const name) : League_name(name), club_no(0) {}
    void addclub(Club const & club) {
        clubs.push_back(club);
        club_no = clubs.size(); //need something more efficient O(n)
    }
    void addmatchday(){
        matchday.resize(club_no);
        for (int team = 0; team < club_no; team++) {
            vector<int> opponents;
            for (int i = 0; i < club_no; ++i) {
                if (team != i) {
                    opponents.push_back(i);
                }
            }

            
            random_shuffle(opponents.begin(), opponents.end());

            for (int match = 0; match < club_no - 1; match++) {
                matchday[team].push_back({ clubs[team], clubs[opponents[match]] });
            }
        }
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
    void displayMatchday() {
        for (const auto& team_matches : matchday) {
            for (const auto& match : team_matches) {
                cout << match.first.getclubname() << " vs " << match.second.getclubname() << endl;
            }
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
    Club club6("Tottenham Spurs", "White Heartlane", 30000, 86.1);
    Club club7("Leicester City", "King Power Stadium", 32312, 82.1);
    Club club8("West Ham United", "London Stadium", 60000, 78.9);
    Club club9("Everton", "Goodison Park", 39209, 81.4);
    Club club10("Aston Villa", "Villa Park", 42785, 79.8);
    Club club11("Wolverhampton Wanderers", "Molineux Stadium", 32050, 77.6);
    Club club12("Leeds United", "Elland Road", 37966, 75.2);
    Club club13("Crystal Palace", "Selhurst Park", 25486, 72.9);
    Club club14("Southampton", "St Mary's Stadium", 32389, 74.3);
    Club club15("Brighton & Hove Albion", "Amex Stadium", 30750, 71.5);
    Club club16("Newcastle United", "St James' Park", 52389, 73.8);
    Club club17("Burnley", "Turf Moor", 21401, 69.2);
    Club club18("Fulham", "Craven Cottage", 19359, 67.4);
    Club club19("Sheffield United", "Bramall Lane", 32702, 68.7);
    Club club20("West Bromwich Albion", "The Hawthorns", 26688, 66.9);
    vector<Club> clubs = { club1, club2, club3, club4, club5, club6, club7, club8, club9, club10,
                           club11, club12, club13, club14, club15, club16, club17, club18, club19, club20 };
    for (auto club : clubs) {
        premier_league.addclub(club);
    }
    //premier_league.displayLeague();
    premier_league.addmatchday();
    premier_league.displayMatchday();
}