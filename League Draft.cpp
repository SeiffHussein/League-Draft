
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <utility>
#include <iomanip>
#include <queue>
#include <fstream>
#include <sstream>

using namespace std;

class Player {
private: 
    string m_name;
    int m_kit;
    int m_age;
    string m_position;
    double m_rating;
    double m_salary;
    int m_goals;
    int m_assists;
    int m_cleansheets;
    
public:
    Player(string name,int kit, int age, string position, double rating, double salary)
        : m_name(name),m_kit(kit),m_age(age),m_position(position),m_rating(rating), m_salary(salary),
        m_goals(0), m_assists(0), m_cleansheets(0) {}

    // Getter for name
    string getName() const { return m_name; }

    // Getter for age
    int getAge() const { return m_age; }

    // Getter for position
    string getPosition() const { return m_position; }

    // Getter for rating
    double getRating() const { return m_rating; }

    // Getter for salary
    double getSalary() const { return m_salary; }

    // Getter for goals
    int getGoals() const { return m_goals; }

    // Getter for assists
    int getAssists() const { return m_assists; }

    // Getter for clean sheets
    int getCleanSheets() const { return m_cleansheets; }

};

class Club {
private:
    string m_clubname;
    string m_stadium;
    string m_manager;
    int m_capacity;
    double m_rating;
    int m_matches;
    int m_points;
    int m_win;
    int m_draw;
    int m_lose;
    queue<char> m_form;
    vector<Player> squad;
    int m_goals;
    int m_goalsConceded;
    int m_goalDiff;
public:
    Club(const string & clubname, const string &stadium, const string& manager, int capacity, double rating)
    :m_clubname(clubname),m_stadium(stadium),m_manager(manager),m_capacity(capacity),m_rating(rating),
        m_matches(0), m_points(0),m_win(0), m_draw(0),m_lose(0), m_goals(0),m_goalsConceded(0),m_goalDiff(0)
    {}

    void  display() const {
        std::cout << m_clubname << '\n' << m_stadium << " Stadium\n"
            << "Capicity: " << m_capacity << "\nManager: " << m_manager << "\n\n";
    }

    void displayStats() const {
        std::cout << left << setw(25) << m_clubname
            << setw(5) << m_matches
            << setw(5) << m_points
            << setw(5) << m_win
            << setw(5) << m_draw
            << setw(5) << m_lose
            << setw(5) << m_goals
            << setw(5) << m_goalsConceded 
            << setw(5) << m_goalDiff<< endl;
    }
    void addGame() { m_matches++; }
    void addWin() {
        m_win++;
        m_points += 3;
        if (m_form.size() == 5) {
            m_form.pop();
            m_form.push('W');
        }
        else {
            m_form.push('W');
        }
    }
    void addDraw() {
        m_draw++;
        m_points += 1;
        if (m_form.size() == 5) {
            m_form.pop();
            m_form.push('D');
        }
        else {
            m_form.push('D');
        }
    }
    void addLoss() {
        m_lose++;
        if (m_form.size() == 5) {
            m_form.pop();
            m_form.push('L');
        }
        else {
                m_form.push('L');
        }
    }
    void addGoals(int goal) { m_goals += goal; m_goalDiff += goal; } //NOT EFFICIENT 
    void addGoalAgainst(int goal) { m_goalsConceded += goal; m_goalDiff -= goal; }
    int calculateForm() const {
        int form{0};
        queue<char> tempform = m_form;
        while (!tempform.empty()) {
            switch (tempform.front()) {
            case 'W':
                form++;
                tempform.pop();
                break;
            case 'D':
                tempform.pop();
                break;
            case 'L':
                form--;
                tempform.pop();
                break;
            default:
                std::cout << "Invalid variable is present" << endl;
                break;
            }
        }
        return form;
    }
    void displayForm() const {
        std::cout << m_clubname <<  " Form: ";
        queue<char> tempform = m_form;
        while (!tempform.empty()) {
            std::cout << tempform.front();
            tempform.pop();
        }
        std::cout << endl;
    }

    void addPlayer(const Player& player) {
       squad.push_back(player);
        
    }

    string getclubname() const { return m_clubname; }
    string getStadium() const { return m_stadium; }
    int getCapacity() const { return m_capacity; }
    double getRating() const { return m_rating; }
    int getMatches() const { return m_matches; }
    int getPoints() const { return m_points; }
    int getWin() const { return m_win; }
    int getDraw() const { return m_draw; }
    int getLoss() const { return m_lose; }
    int getGoals() const { return m_goals;}
    int getGoalDiff() const { return m_goalDiff; }



    friend void gamesim(const Club& club1, const Club& club2);
    

};

int WeightedGoals(double score, double advantage){
    double advantagecoefficient = advantage / 10;
    if (score <= (20 - advantagecoefficient)) {
        return 0;
    }
    if (score > (20 - advantagecoefficient) and score <= (40 - (2*advantagecoefficient))) {
        return 1;
    }
    if (score > (40 - (2 * advantagecoefficient)) and score <= (60- (3*advantagecoefficient))) {
        return 2;
    }
    if (score > (60 - (3 * advantagecoefficient)) and score <= (77- (4*advantagecoefficient))) {
        return 3;
    }
    if (score > (77 - (4 * advantagecoefficient)) and score <= (85 - (5 * advantagecoefficient))) {
        return 4;
    }
    if (score > (85-(5*advantagecoefficient)) and score <= (92 - (4 * advantagecoefficient))) {
        return 5;
    }
    if (score > (92 - (4*advantagecoefficient))  and score <= (97 - (3 * advantagecoefficient))) {
        return 6;
    }
    if (score > (96.5 - (3*advantagecoefficient)) and score <= (99 - (2 * advantagecoefficient))) {
        return 7;
    }
    if (score > (99-(2*advantagecoefficient)) and score <= (99.75-advantagecoefficient)) {
        return 8;
    }
    if (score > (99.75 -advantagecoefficient) and score <= 100) {
        return 9;
    }
}

void gamesim( Club& club1,  Club& club2) {
    // Assuming the chance of winning is 33.4%, drawing and losing 33.3%
    // assumed home advantage increase winning chance by 5% with no effect on drawing
    // assumed squad rating diffrence increase winning chance by the diffrence * 1.5  
    // Last 5 matches a team play give them dis/advantage in the range of -+5 


 
     random_device rd;  // Obtain a random number
     mt19937 gen(rd());  // Seed the generator
    uniform_real_distribution<> distr(0, 100);  // Define the range
    float difference = abs(club1.getRating() - club2.getRating());
    double signedDifference = club1.getRating() - club2.getRating();
    //if (difference > 41){}
    float score = distr(gen); // random number to determine the winner
    float goal_score = distr(gen); // random number to determine number of goals
   // cout << "goal: " << goal_score<< endl;
 

    // *form difference code here*
    int formdiff = club1.calculateForm() - club2.calculateForm(); 
    double advantage = formdiff + signedDifference;
    
    
   // std::cout << endl << "winner : " << score << "\n difference: " << difference << "\n";
    
    //cout << club1.getclubname() << " vs " << club2.getclubname() << endl;
    club1.addGame();
    club2.addGame();

    double winThreshold = (38.4 + formdiff + (difference * 1.5));
    double drawThreshold = winThreshold + ((30.8 - ((difference * 1.5) / 2)));
    int winnergoals;
    int losergoals;
    int goals;

    if (club1.getRating() >= club2.getRating()) {
     //   std::cout << "\n\nless than " << winThreshold << "to win\n";
       // std::cout << "draw between " << winThreshold << " and " << drawThreshold << endl;
        if (score < winThreshold) {
            club1.addWin();
            club2.addLoss();
             winnergoals = WeightedGoals(goal_score,(5+advantage));
            if (winnergoals > 1) {
                losergoals = rand() % (winnergoals-1);
            }
            else {
                winnergoals = 1;
                losergoals = 0;
            }
            club1.addGoals(winnergoals);
            club1.addGoalAgainst(losergoals);
            club2.addGoals(losergoals);
            club2.addGoalAgainst(winnergoals);
           std:: cout << club1.getclubname() << " " << winnergoals << " - " << losergoals << " "
                << club2.getclubname() << " at " << club1.getStadium() << endl;
           
        }
        else if (score >= winThreshold && score <= drawThreshold)
        {
            club1.addDraw();
            club2.addDraw();
             goals = WeightedGoals(goal_score,advantage);
            club1.addGoals(goals);
            club1.addGoalAgainst(goals);
            club2.addGoals(goals);
            club2.addGoalAgainst(goals);

            std::cout << club1.getclubname() << " " << goals << " - " << goals << " "
                << club2.getclubname() << " at " << club1.getStadium() << endl;
        }
        else {
            club2.addWin();
            club1.addLoss();
             winnergoals = WeightedGoals(goal_score, advantage);
            if (winnergoals > 1) {
                 losergoals = rand() % (winnergoals-1);
            }
            else {
                winnergoals = 1;
                losergoals = 0;
            }
            club2.addGoals(winnergoals);
            club2.addGoalAgainst(losergoals);
            club1.addGoals(losergoals);
            club1.addGoalAgainst(winnergoals);
            std::cout << club1.getclubname() << " " << losergoals << " - " << winnergoals << " "
                << club2.getclubname() << " at " << club1.getStadium() << endl;
        }
    }

    //// calculating chances of winning if club2 (away) rating > club1 (home) rating
        else if(club2.getRating() > club1.getRating()) {
        winThreshold = (38.4 + (formdiff / 2) - ((difference * 1.5) / 2));
        drawThreshold = winThreshold + (30.8 + (formdiff / 2) - ((difference * 1.5) / 2));
        //std::cout << club1.getclubname() << " win less than " << winThreshold << endl;
      //std::cout << "draw at " << winThreshold << " and " << drawThreshold << endl;
            if (score < winThreshold) {
                club1.addWin();
                club2.addLoss();

                winnergoals = WeightedGoals(goal_score, (5 + advantage));
                if (winnergoals > 1) {
                    losergoals = rand() % (winnergoals-1);
                }
                else {
                    winnergoals = 1;
                    losergoals = 0;
                }
                club1.addGoals(winnergoals);
                club1.addGoalAgainst(losergoals);
                club2.addGoals(losergoals);
                club2.addGoalAgainst(winnergoals);

                std::cout << club1.getclubname() << '\t' << winnergoals << " - " << losergoals<< '\t'
                    << club2.getclubname() << " at " << club1.getStadium() << endl;
            }
            else if (score >= winThreshold && score <= drawThreshold) {
                club1.addDraw();
                club2.addDraw();
                goals = WeightedGoals(goal_score, advantage);
                club1.addGoals(goals);
                club1.addGoalAgainst(goals);
                club2.addGoals(goals);
                club2.addGoalAgainst(goals);

                std::cout << club1.getclubname() << " " << goals << " - " << goals << " "
                    << club2.getclubname() << " at " << club1.getStadium() << endl;
            }
            else {
                club2.addWin();
                club1.addLoss();
                winnergoals = WeightedGoals(goal_score, advantage);
                if (winnergoals > 1) {
                    losergoals = rand() % (winnergoals - 1);
                }
                else {
                    winnergoals = 1;
                    losergoals = 0;
                }
                club2.addGoals(winnergoals);
                club2.addGoalAgainst(losergoals);
                club1.addGoals(losergoals);
                club1.addGoalAgainst(winnergoals);
                //std::cout << club1.getclubname() << " " << losergoals << " - " << winnergoals << " "
                  //  << club2.getclubname() << " at " << club1.getStadium() << endl;
            }
            }
    // displaying the last 5 matches results for each team
    //club1.displayForm();
    //std::cout << club1.calculateForm() << endl;
    //club2.displayForm();
    //std::cout << club2.calculateForm() << endl;
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
        std::cout << "League name: " << League_name << endl;
        std::cout << "Number of clubs: " << club_no << endl;
        std::cout << "clubs:\n";
        for (const auto & Club : clubs) {
            Club.display();

    }
                        }
    void displayLeagueTable()const {
        vector<Club> sorted_clubs = clubs;
        
        sort(sorted_clubs.begin(), sorted_clubs.end(), [](const Club& a, const Club& b) {
            if (a.getPoints() == b.getPoints()) {
                return a.getGoalDiff() > b.getGoalDiff();
            }
            return a.getPoints() > b.getPoints();
            });

        std::cout << left << setw(25) << "Club"
            << setw(5) << "MP"
            << setw(5) << "Pts"
            << setw(5) << "W"
            << setw(5) << "D"
            << setw(5) << "L" 
            << setw(5) << "G"
            << setw(5) << "GA" 
            << setw(5) << "GD" << endl;
        for (const auto& Club : sorted_clubs) {
            Club.displayStats();
        }
    std:cout << sorted_clubs[0].getclubname() << " is " << League_name << " winner " << endl;
        //std::cout << "total goals: " << calculateTotalGoals();
    }
    void displayMatchday() {
        // Display matches
        for (int match = 0; match < ((club_no - 1)*2); ++match) {
            std::cout << "\nMatchday: " << match + 1 << endl;
            for (const auto& game : matchday[match]) {
                std::cout << "\n" << clubs[game.first].getclubname() << " vs " << clubs[game.second].getclubname();
               
            }
            std::cout << endl;
        }
    }
    friend void gamesim(const Club& club1, const Club& club2);

    void simulateMatchdays() {
        for (int match = 0; match < ((club_no - 1) * 2); ++match) {
            std::cout << "\nMatchday: " << match + 1 << endl;
            for (const auto& game : matchday[match]) {
                gamesim(clubs[game.first], clubs[game.second]);
            }
            std::cout << endl;
        }
    }
    int calculateTotalGoals() const {
        int totalGoals = 0;
        for (const auto& club : clubs) {
            totalGoals += club.getGoals();
        }
        return totalGoals;
    }
};



int main() {
    int x = time(0);
    srand(x);
    std::cout << "Input League Name: ";
    string LeagueName;
    getline(cin,LeagueName);
    League league(LeagueName);
    vector<Club> clubs;
    cout << "Please input the League's file name: ";
    string filename;
    cin >> filename;
    ifstream file(filename);
    if (!file) { cerr << "file could not be opened"; return 1; }
    string line;
    string clubname, stadium, manager;
    int capacity;
    double rating;

    while (getline(file, line)) {
        stringstream stream(line);
        if (getline(stream, clubname, ',') &&
            getline(stream, stadium, ',') &&
            getline(stream, manager, ',') &&
            (stream >> capacity) && stream.ignore() &&
            (stream >> rating)) {
            league.addclub(Club(clubname, stadium, manager, capacity, rating));
        }
        else {
            cerr << "wrong formatting in line " << line << endl;
        }
    }
        league.displayLeague();
       league.addmatchday();
        league.displayMatchday();
        league.simulateMatchdays();
        league.displayLeagueTable();
    }