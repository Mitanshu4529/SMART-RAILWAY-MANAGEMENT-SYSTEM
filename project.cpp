// FINDING SHORTEST PATH BETWEEN TWO STATIONS

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <unordered_map>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <climits>
#include <conio.h>
#include <windows.h>
using namespace std;

string randomDirection()
{
    string direction;
    int min = 0;
    int max = 90;
    srand(time(0));
    // Generate random coordinates
    int x = min + rand() % (max - min + 1);  // Latitude
    int y = min + rand() % (max - min + 1);  // Longitude

    direction = to_string(x) + "\370 N latitude, " + to_string(y) + "\370 E longitude";
    return direction;
}

class Station
{
public:
    string Sname;
    int wheelchairfacility;
    int atm;
    int wifi;
    int parking;
    int foodcourt;
    int waitingrooms;
    string direction;

    Station() {}
    Station(string name, int a, int b, int c, int d, int e, int f)
    {
        Sname = name;
        wheelchairfacility = a;
        atm = b;
        wifi = c;
        parking = d;
        foodcourt = e;
        waitingrooms = f;
        direction = randomDirection();
    }
};

class Graph
{
public:
    unordered_map<string, vector<pair<string, int>>> adjlist;
    unordered_map<string, Station> stationLookup;

    void addStation(Station src, Station dest, int dist)
    {
        stationLookup[src.Sname] = src;
        stationLookup[dest.Sname] = dest;
        adjlist[src.Sname].push_back({dest.Sname, dist});
        adjlist[dest.Sname].push_back({src.Sname, dist});
        cout << "Adding edge from " << src.Sname << " to " << dest.Sname << " with distance " << dist << endl;
    }

    pair<vector<string>, int> shortest_path(string source, string destination)
    {
        unordered_map<string, int> dist;
        unordered_map<string, string> previous;
        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;

        for (auto &pair : adjlist)
        {
            dist[pair.first] = INT_MAX;
        }
        dist[source] = 0;
        pq.push({0, source});

        while (!pq.empty())
        {
            string top = pq.top().second;
            pq.pop();

            for (auto &neighbor : adjlist[top])
            {
                if (dist[top] + neighbor.second < dist[neighbor.first])
                {
                    dist[neighbor.first] = dist[top] + neighbor.second;
                    previous[neighbor.first] = top;
                    pq.push({dist[neighbor.first], neighbor.first});
                }
            }
        }

        vector<string> path;
        string crawl = destination;
        while (crawl != source)
        {
            path.push_back(crawl);
            crawl = previous[crawl];
        }
        path.push_back(source);
        reverse(path.begin(), path.end());
        return {path, dist[destination]};
    }

    void showFareOptions(int distance)
    {
        int baseFare = 0;
        if (distance < 50) baseFare = distance*3.5;
        else if (distance < 200) baseFare = distance*3;
        else baseFare = distance*3.2;

        int daily = baseFare*6-(baseFare*6*0.2);
        int monthly = baseFare*26-(baseFare*26*0.4);

        cout << "\nFare Options:" << endl;
        cout << "* Single Journey: Rs. " << baseFare << endl;
        cout << "* Daily/Weekly Pass: Rs. " << daily << " (approx 6 rides/week)" << endl;
        cout << "* Monthly Pass: Rs. " << monthly << " (approx 26 rides/month)" << endl;
    }

    void showTime(int distance)
    {
        double avgSpeed = 60.0;
        double time = (double)distance / avgSpeed;
        cout << "* Estimated Travel Time: " << time << " hours\n";
    }
};

// class representing admin ..
class admin
{
public:
vector<Station>&v;
Graph &graph;
admin(vector<Station> &s, Graph &g) : v(s), graph(g){}
    void call()
    {
    // LOGIN WINDOW FOR AUTHENTICATION OF USER
    mainmenu:
        cout << endl
             << endl
             << endl
             << " LOGIN WINDOW : " << endl;
        cout << " .............. " << endl
             << endl;
        cout << "ENTER USERNAME : ";
        string username;
        cin >> username;
        cout << "ENTER PASSWORD : ";
        string password;
        char c;
        for (int i = 0; i <= 5 - 1; i++)
        {
            c = getch();
            password += c;
            cout << "*";
        }
        // CODE FOR 4 DIGIT CAPTCHA GENERATION
        // SECOND FACTOR AUTHENTICATION
        srand(time(0));
        int ans = 0;
        const int CAPTCHA_LENGTH = 4;
        int captcha = rand() % (9000) + 1000;
        cout << endl
             << endl
             << "ENTER CAPTCHA " << captcha << " : ";
        cin >> ans;
        while (username != "admin" || password != "admin" || ans != captcha)
        {
            cout << endl << "INCORRECT USERNAME OR PASSWORD OR CAPTCHA " << endl;
            cout << "TRY AGAIN !!! " << endl;

            cout << "ENTER USERNAME : ";
            cin >> username;

            password.clear();
            cout << "ENTER PASSWORD : ";
            char c;
            for (int i = 0; i <= 4; i++)  // 5 characters
            {
                c = getch();
                password += c;
                cout << "*";
            }

            captcha = rand() % (9000) + 1000;
            cout << endl << endl << "ENTER CAPTCHA " << captcha << " : ";
            cin >> ans;
        }

        cout << endl;
        cout << endl
             << "LOGIN SUCCESSFUL !!" << endl;
        cout << "ACCESS GRANTED !!!" << endl
             << endl;

             while(true)
             {
        cout << "\t\t\t\t\t\t\t   ----------------------------------------" << endl;
        cout << "\t\t\t\t\t\t\t       SMART RAILWAY MANAGEMENT SYSTEM          " << endl;
        cout << "\t\t\t\t\t\t\t   ----------------------------------------" << endl
             << endl
             << endl
             << endl;
        cout << "\t\t\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * " << endl;
        cout << "\t\t\t\t\t\t                   ENTER 1 TO ADD THE ROUTE " << endl;
        cout << "\t\t\t\t\t\t                   ENTER 2 TO GO BACK TO MAIN MENU  " << endl;
        cout << "\t\t\t\t\t\t                   ENTER 3 TO EXIT " << endl;
        cout << "\t\t\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *  " << endl;
        int ans;
        cout << endl
             << "ENTER YOUR CHOICE : ";
        cin >> ans;
        switch(ans)
        {
            case 1 :
            {
                string dept,arrival;
                while(true)
                {
                int distance;
                cout<<"ENTER DEPARTURE PLACE :";
                cin>>dept;
                if(dept=="Null")
                {
                    break;
                }
                cout<<"ENTER ARRIVAL PLACE :";
                cin>>arrival;
                cout<<"ENTER DISTANCE : ";
                cin>>distance;
                vector<Station>::iterator i;
                bool a1 = false;
                bool a2 = false;
                Station s;
                for (i = v.begin(); i != v.end(); i++)
                {
                    if (i->Sname == dept)
                    {
                        a1 = true;
                    }
                    if (i->Sname == arrival)
                    {
                        a2 = true;
                    }
                    if (a1 == true && a2 == true)
                    {
                        break;
                    }
                }
                Station d(dept,0,0,0,0,0,0);
                Station a(arrival,0,0,0,0,0,0);
                if(!a1&& !a2)
                {
                    v.push_back(d);
                    v.push_back(a);     
                }
                else if(!a1)
                {
                    v.push_back(d);
                }
                else if(!a2)
                {
                    v.push_back(a); 
                }
                graph.addStation(d, a, distance);
                }
                cout<<"ROUTE ADDED SUCCESSFULLY ";
                break;
            }
            case 2:
            {
                return;
            }
            case 3:
            {
                exit(0);
                break;
            }
        }
             }
    }
};

//class representing user..
class user
{
public:
vector<Station>&v;
Graph &graph;
user(vector<Station> &s, Graph &g) : v(s), graph(g){}
    void call()
    {
    // LOGIN WINDOW FOR AUTHENTICATION OF USER
    mainmenu:
        cout << endl
             << endl
             << endl
             << " LOGIN WINDOW : " << endl;
        cout << " .............. " << endl
             << endl;
        cout << "ENTER USERNAME : ";
        string username;
        cin >> username;
        cout << "ENTER PASSWORD : ";
        string password;
        char c;
        for (int i = 0; i <= 3; i++)
        {
            c = getch();
            password += c;
            cout << "*";
        }

        // CODE FOR 5 DIGIT CAPTCHA GENERATION
        // SECOND FACTOR AUTHENTICATION
        srand(time(0));
        int ans = 0;
        const int CAPTCHA_LENGTH = 5;
        int captcha = rand() % (90000) + 10000;
        cout << endl
             << endl
             << "ENTER CAPTCHA " << captcha << " : ";
        cin >> ans;
        while (username != "user" || password != "user" || ans != captcha)
        {
            cout << endl << "INCORRECT USERNAME OR PASSWORD OR CAPTCHA " << endl;
            cout << "TRY AGAIN !!! " << endl;

            cout << "ENTER USERNAME : ";
            cin >> username;

            password.clear();
            cout << "ENTER PASSWORD : ";
            char c;
            for (int i = 0; i <= 3; i++)  // 4 characters
            {
                c = getch();
                password += c;
                cout << "*";
            }

            captcha = rand() % (90000) + 10000;
            cout << endl << endl << "ENTER CAPTCHA " << captcha << " : ";
            cin >> ans;
        }

        cout << endl;
        cout << endl
             << "LOGIN SUCCESSFUL !!" << endl;
        cout << "ACCESS GRANTED !!!" << endl
             << endl;
              cout << endl
         << endl
         << endl;
    // system("Color 7D");
    while (true)
    {
        cout << "\t\t\t\t\t\t\t   ----------------------------------------" << endl;
        cout << "\t\t\t\t\t\t\t       SMART RAILWAY MANAGEMENT SYSTEM          " << endl;
        cout << "\t\t\t\t\t\t\t   ----------------------------------------" << endl
             << endl
             << endl
             << endl;
        cout << "\t\t\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * " << endl;
        cout << "\t\t\t\t\t\t        ENTER 1 TO FIND THE ROUTE " << endl;
        cout << "\t\t\t\t\t\t        ENTER 2 TO FIND THE FARE  " << endl;
        cout << "\t\t\t\t\t\t        ENTER 3 TO FIND THE AVAILABLE FACILITIES AT A STATION  " << endl;
        cout << "\t\t\t\t\t\t        ENTER 4 TO GO BACK TO MAIN MENU  " << endl;
        cout << "\t\t\t\t\t\t        ENTER 5 TO EXIT " << endl;
        cout << "\t\t\t\t\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * " << endl;
        int ans;
        cout << endl
             << "ENTER YOUR CHOICE : ";
        cin >> ans;
        switch (ans)
        {
            case 1:
            {
                string dept, arrival;
            
                cout << "----------------------------------------------------------------------------" << endl;
                cout << "Enter the departure place (first letter capitalized, rest in lowercase): " << endl;
                cin >> dept;
            
                cout << "--------------------------------------------------------------------------" << endl;
                cout << "Enter the arrival place (first letter capitalized, rest in lowercase): " << endl;
                cin >> arrival;
                cout << "--------------------------------------------------------------------------" << endl;
            
                if (dept == arrival)
                {
                    cout << "ERROR!  DEPARTURE AND ARRIVAL DESTINATION CANNOT BE SAME " << endl;
                }
                else
                {
                    vector<Station>::iterator i;
                    bool a1 = false;
                    bool a2 = false;
                    Station s;
                    for (i = v.begin(); i != v.end(); i++)
                    {
                        if (i->Sname == dept)
                        {
                            a1 = true;
                        }
                        if (i->Sname == arrival)
                        {
                            a2 = true;
                        }
                        if (a1 == true && a2 == true)
                        {
                            break;
                        }
                    }
                    if (a1 && a2)
                    {
                        pair<vector<string>, int> result = graph.shortest_path(dept, arrival);
            
                        cout << "Shortest path from " << dept << " to " << arrival << " is: ";
                        cout << endl;
                        cout << "* ";
                        for (int i = 0; i < result.first.size(); ++i)
                        {
                            cout << result.first[i];
                            cout << " (" << graph.stationLookup[result.first[i]].direction << ")";
                            if (i < result.first.size() - 1)
                            {
                                cout << " -> ";
                            }
                        }
            
                        cout << endl
                             << "* Distance : " << result.second << " Kms" << endl;
            
                        // Call showTime function to display estimated time for travel
                        graph.showTime(result.second);
                    }
                    else
                    {
                        cout << "EITHER DEPARTURE OR ARRIVAL STATION DOES NOT EXISTS " << endl;
                    }
                }
                break;
            }
        case 2:
        {
            string dept, arrival;
            cout << "--------------------------------------------------------------------------" << endl;
            cout << "Enter the departure place (first letter capitalized, rest in lowercase): ";
            cin >> dept;
            cout << "--------------------------------------------------------------------------" << endl;
            cout << "Enter the arrival place (first letter capitalized, rest in lowercase): ";
            cin >> arrival;
            cout << "--------------------------------------------------------------------------" << endl;
            if (dept == arrival)
            {
                cout << "ERROR!       DEPARTURE AND ARRIVAL DESTINATION CANNOT BE SAME " << endl;
            }
            else
            {
                vector<Station>::iterator i;
                bool a1 = false;
                bool a2 = false;
                Station s;
                for (i = v.begin(); i != v.end(); i++)
                {
                    if (i->Sname == dept)
                    {
                        a1 = true;
                    }
                    if (i->Sname == arrival)
                    {
                        a2 = true;
                    }
                    if (a1 == true && a2 == true)
                    {
                        break;
                    }
                }
                if (a1 && a2)
                {
                    Station d(dept, 0, 0, 0, 0, 0, 0);
                    Station a(arrival, 0, 0, 0, 0, 0, 0);
                    pair<vector<string>, int> result = graph.shortest_path(dept, arrival);

                    graph.showFareOptions(result.second);
                    graph.showTime(result.second);  // Call showTime to display estimated time
                }
                else
                {
                    cout << "EITHER DEPARTURE OR ARRIVAL STATION DOES NOT EXISTS " << endl;
                }
            }
            break;
        }

        case 3:
        {
            string city;
            cout << "--------------------------------------------------------------------------" << endl;
            cout << "ENTER A STATION NAME(first letter capitalized, rest in lowercase): ";
            cin >> city;
            cout << "--------------------------------------------------------------------------" << endl;
            vector<Station>::iterator i;
            bool ans = false;
            Station s;
            for (i = v.begin(); i != v.end(); i++)
            {
                if (i->Sname == city)
                {
                    s = *i;
                    ans = true;
                    break;
                }
            }
            if (ans)
            {
                cout << "----------------------------" << endl;
                cout << "* WHEELCHAIR FACILITY : " << s.wheelchairfacility << endl;
                cout << "* ATM : " << s.atm << endl;
                cout << "* WIFI : " << s.wifi << endl;
                cout << "* PARKING : " << s.parking << endl;
                cout << "* FOOD COURT : " << s.foodcourt << endl;
                cout << "* WAITING ROOMS : " << s.waitingrooms << endl;
                cout << "* LOCATION : " << s.direction << endl;                
                cout << "-----------------------------" << endl;
            }
            else
            {
                cout << "ERROR! STATION NOT FOUND " << endl;
            }
            break;
        }
        case 4:
        {
            return;

        }
        case 5:
        {
            exit(0);
            break;
        }
        default:
        {
            cout << "PLEASE ENTER THE CORRECT CHOICE ";
            break;
        }
        }
    }
    }
};

int main()
{
    Graph graph;

    //adding some stations..

    Station delhi("Delhi", 1, 1, 1, 1, 1, 1);
    Station ambala("Ambala", 1, 1, 0, 1, 1, 0);
    Station ludhiana("Ludhiana", 1, 1, 1, 1, 1, 1);
    Station jammu("Jammu", 1, 0, 0, 1, 0, 1);
    Station katra("Katra", 1, 1, 1, 1, 1, 1);
    Station meerut("Meerut", 1, 0, 1, 0, 0, 1);
    Station kerala("Kerala", 1, 1, 1, 1, 1, 1);
    Station bangalore("Bangalore", 1, 1, 1, 1, 1, 1);
    Station mysore("Mysore", 1, 0, 0, 1, 0, 1);
    Station gandhinagar("Gandhinagar", 1, 0, 1, 0, 1, 1);
    Station kurushetra("Kurushetra", 1, 1, 1, 1, 1, 1);
    
    vector<Station> v;
    
    v.push_back(delhi);
    v.push_back(ambala);
    v.push_back(ludhiana);
    v.push_back(jammu);
    v.push_back(katra);
    v.push_back(meerut);
    v.push_back(kerala);
    v.push_back(bangalore);
    v.push_back(mysore);
    v.push_back(gandhinagar);
    v.push_back(kurushetra);

    graph.addStation(delhi, ambala, 200);
    graph.addStation(ambala, ludhiana, 108);
    graph.addStation(ludhiana, jammu, 286);
    graph.addStation(jammu, katra, 43);
    graph.addStation(delhi, meerut, 78);
    graph.addStation(meerut, ludhiana, 302);
    graph.addStation(kerala, bangalore, 529);
    graph.addStation(bangalore, mysore, 600);
    graph.addStation(mysore, gandhinagar, 820);
    graph.addStation(gandhinagar, kurushetra, 1030);
    
    admin a1(v,graph);
    
    user u1(v,graph);
    
    //menu driven program..
    while (true)
    {
    
    time_t now = time(0);     // GET CURRENT DATE AND TIME WITH RESPECT TO SYSTEM
    char *date = ctime(&now); // CONVERT IT INTO STRING
    cout << endl<< endl<< endl;
    cout << "\t\t\t\t\t\t\t\t " << date;
    cout << endl;
        cout << "\t\t\t\t\t\t\t==============================================" << endl;
        cout << "\t\t\t\t\t\t\t     SMART RAILWAY TRAIN MANAGEMENT SYSTEM  " << endl;
        cout << "\t\t\t\t\t\t\t==============================================" << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t\tPROJECT PREPARED BY : " << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t\tDevanshi Srivastava    9923103117 " << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t\tMitanshu Finaviya      9923103120 " << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t\tDeepanshu Bhalia       9923103122 " << endl;
    cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t\tRaunak Kheshwani       9923103124 " << endl;
    int key;
    cout << endl;

    cout << "ENTER ANY KEY TO CONTINUE : ";
    cin >> key;
      cout << endl
         << endl;
    cout << " PRESS 1 FOR ADMIN " << endl;
    cout << " PRESS 2 FOR USER " << endl;
    cout << " PRESS 3 TO EXIT " << endl;
    cout << " ENTER YOUR CHOICE : ";
    int k;
    cin >> k;
    switch (k)
    {
    case 1:
    {
        a1.call();
        break;
    }
    case 2:
    {
        u1.call();
        break;
    }
    case 3:
    {
        exit(0);
        break;
    }
    default:
    {
        cout << "Invalid choice! pls" << endl;
        break;
    }
    }
    }
    return 0;
}