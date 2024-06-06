
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <utility>
#include <iomanip>

using namespace std;

class Club {
private:
    string m_clubname;
    string m_stadium;
    int m_capacity;
    double m_rating;
    int m_matches;
    int m_points;
    int m_win;
    int m_draw;
    int m_lose;
    //vector<char> form;
    //int m_goals;
public:
    Club(const string & clubname, const string stadium, int capacity, double rating)
    :m_clubname(clubname),m_stadium(stadium),m_capacity(capacity),m_rating(rating)
    {
        m_matches = 0;
        m_points = 0; 
        m_win = 0;
        m_draw = 0;
        m_lose = 0;
    }

    void  display() const {
        cout << m_clubname << '\n' << m_stadium << " Stadium\n" 
            << "Capicity: " << m_capacity << endl << "\n\n";
    }

    void displayStats() const {
        cout << left << setw(25) << m_clubname
            << setw(5) << m_matches
            << setw(5) << m_points
            << setw(5) << m_win
            << setw(5) << m_draw
            << setw(5) << m_lose << endl;
    }
    void addGame() { m_matches++; }
    void addWin() { m_win++; m_points += 3; }
    void addDraw() { m_draw++; m_points += 1; }
    void addLoss() { m_lose++; }
    string getclubname() const { return m_clubname; }
    string getStadium() const { return m_stadium; }
    int getCapacity() const { return m_capacity; }
    double getRating() const { return m_rating; }
    int getMatches() const { return m_matches; }
    int getPoints() const { return m_points; }
    int getWin() const { return m_win; }
    int getDraw() const { return m_draw; }
    int getLoss() const { return m_lose; }



    friend void gamesim(const Club& club1, const Club& club2);
    

};


void gamesim( Club& club1,  Club& club2) {
    // Assuming the chance of winning is 33.4%, drawing and losing 33.3%
    // assumed home advantage increase winning chance by 5% with no effect on drawing
    // assumed squad rating diffrence increase winning chance by the diffrence * 1.5   
    random_device rd;  // Obtain a random number
    mt19937 gen(rd());  // Seed the generator
    uniform_real_distribution<> distr(0, 100);  // Define the range
    float difference = abs(club1.getRating() - club2.getRating());
    float score = distr(gen);
    //cout << endl << "winner : " << score << "\n difference: " << difference << "\n";
    
    cout << club1.getclubname() << " vs " << club2.getclubname() << endl;
    club1.addGame();
    club2.addGame();

    if (club1.getRating() >= club2.getRating()) {
       // cout << "\n\nless than " << (38.4 + (difference * 1.5)) << "to win\n";
        //cout << "draw between " << (38.4 + (difference * 1.5)) << " and " << (38.4 + ((difference * 1.5)) + ((30.8 - ((difference * 1.5) / 2)))) << endl;
        if (score < (38.4 + (difference * 1.5))) {
            club1.addWin();
            club2.addLoss();
            cout << club1.getclubname() << " won against "
                << club2.getclubname() << " at " << club1.getStadium() << endl;
        }
        else if (score >= (38.4 + (difference * 1.5)) && score <= (38.4 + ((difference * 1.5)) + ((30.8 - ((difference * 1.5) / 2)))))
        {
            club1.addDraw();
            club2.addDraw();
            cout << club1.getclubname() << " drawed with "
                << club2.getclubname() << " at " << club1.getStadium() << endl;
        }
        else {
            club2.addWin();
            club1.addLoss();
            cout << club2.getclubname() << " won against "
                << club1.getclubname() << " at " << club1.getStadium() << endl;
        }
    }
        else if(club2.getRating() > club1.getRating()) {
        //cout << club1.getclubname() << " win less than " << (38.4 - ((difference * 1.5) / 2)) << endl;
      //  cout << "draw at " << (38.4 - ((difference * 1.5) / 2)) << " and " << ((38.4 - ((difference * 1.5) / 2)) + (30.8 - ((difference * 1.5) / 2))) << endl;
            if (score < (38.4 - ((difference*1.5)/2))) {
                club1.addWin();
                club2.addLoss();
                cout << club1.getclubname() << " won against "
                    << club2.getclubname() << " at " << club1.getStadium() << endl;
            }
            else if (score >= (38.4 - ((difference * 1.5) / 2)) && score <= ((38.4 - ((difference * 1.5) / 2)) + (30.8 - ((difference * 1.5) / 2)))) {
                club1.addDraw();
                club2.addDraw();
                cout << club1.getclubname() << " drawed with "
                    << club2.getclubname() << " at " << club1.getStadium() << endl;
            }
            else {
                club2.addWin();
                club1.addLoss();
                cout << club2.getclubname() << " won against "
                    << club1.getclubname() << " at " << club1.getStadium() << endl;
            }
            }
    }

class League {
private:
    string League_name;
    int club_no;
    vector<Club> clubs;
    vector<vector<pair<int, int>>> matchday;;

public: 
    League(string const name) : League_name(name), club_no(0) {}
    void addclub(Club const & club) {
        clubs.push_back(club);
        club_no = clubs.size(); //need something more efficient O(n)
    }
    void addmatchday(){

        matchday.resize(((club_no - 1)*2), vector<pair<int, int>>(club_no / 2));
        vector<int> team_indices(club_no);
        for (int i = 0; i < club_no; i++) {
            team_indices[i] = i;
        }
        random_device rd;
        mt19937 g(rd());
        for (int i = 0; i < club_no - 1; ++i) {
            shuffle(team_indices.begin(), team_indices.end(), g);
            for (int j = 0; j < club_no / 2; ++j) {
                matchday[i][j] = make_pair(team_indices[2 * j], team_indices[2 * j + 1]);
                matchday[i+club_no-1][j] = make_pair(team_indices[2 * j + 1], team_indices[2 * j]);
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
    void displayLeagueTable()const {
        vector<Club> sorted_clubs = clubs;
        
        sort(sorted_clubs.begin(), sorted_clubs.end(), [](const Club& a, const Club& b) {
            return a.getPoints() > b.getPoints();
            });

        cout << left << setw(25) << "Club"
            << setw(5) << "MP"
            << setw(5) << "Pts"
            << setw(5) << "W"
            << setw(5) << "D"
            << setw(5) << "L" << endl;
        for (const auto& Club : sorted_clubs) {
            Club.displayStats();
        }
    }
    void displayMatchday() {
        // Display matches
        for (int match = 0; match < ((club_no - 1)*2); ++match) {
            cout << "\nMatchday: " << match + 1 << endl;
            for (const auto& game : matchday[match]) {
                cout << "\n" << clubs[game.first].getclubname() << " vs " << clubs[game.second].getclubname();
               
            }
            cout << endl;
        }
    }
    friend void gamesim(const Club& club1, const Club& club2);

    void simulateMatchdays() {
        for (int match = 0; match < ((club_no - 1) * 2); ++match) {
            cout << "\nMatchday: " << match + 1 << endl;
            for (const auto& game : matchday[match]) {
                gamesim(clubs[game.first], clubs[game.second]);
            }
            cout << endl;
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
    Club club4("Arsenal", "Emirates", 60260, 88.4);
    Club club5("Manchester City", "Etihad", 55000, 97.5);
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
    premier_league.displayLeague();
    premier_league.addmatchday();
    premier_league.displayMatchday();
    premier_league.simulateMatchdays();
    premier_league.displayLeagueTable();
  
    
}