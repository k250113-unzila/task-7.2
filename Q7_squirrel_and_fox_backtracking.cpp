
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

const int R = 5, C = 5;

char forest[R][C] = {
    {'S','A','A','T','A'},
    {'A','T','A','A','G'},
    {'T','A','T','A','F'},
    {'A','A','A','T','G'},
    {'A','T','G','T','G'}
};

const int dr[4] = {1, 0, -1, 0};                  
const int dc[4] = {0, 1, 0, -1};

struct Animal {
    string name;
    char   goal;                 
    int    target;               
    int    collected = 0;
    int    step = 0;
    bool   visited[R][C] = {};
    bool   gotItem[R][C] = {};
    int    order[R][C]   = {};   
    vector<pair<int,int>> walk;  
};

bool explore(Animal& a, int r, int c)
{
    a.visited[r][c] = true;
    a.order[r][c] = ++a.step;
    a.walk.push_back({r, c});

    if (forest[r][c] == a.goal) {                   
        a.collected++;
        a.gotItem[r][c] = true;
    }
    if (a.collected >= a.target) return true;        

    for (int d = 0; d < 4; d++) {
        int nr = r + dr[d], nc = c + dc[d];
        if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;   
        if (forest[nr][nc] == 'T') continue;                    
        if (a.visited[nr][nc]) continue;                        

        if (explore(a, nr, nc)) return true;
        a.walk.push_back({r, c});                    
    }
    return false;
}

void report(const Animal& a, int sr, int sc)
{
    int total = 0;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            if (forest[i][j] == a.goal) total++;

    cout << "==================== " << a.name << " ====================\n";
    cout << "Start (" << sr << "," << sc << "), target = " << a.target
         << " item(s) '" << a.goal << "', items in forest = " << total << "\n";

    if (a.collected >= a.target)
        cout << "RESULT: target reached, collected " << a.collected << ".\n";
    else
        cout << "RESULT: target NOT reachable. Collected all it could reach: "
             << a.collected << " of " << a.target << ".\n"
             << "        (Only " << total << " '" << a.goal << "' exist in the forest, "
             << "and some may be sealed off by traps.)\n";

    cout << "\nPath (including backtracking moves):\n  ";
    for (size_t i = 0; i < a.walk.size(); i++) {
        cout << "(" << a.walk[i].first << "," << a.walk[i].second << ")";
        if (i + 1 < a.walk.size()) cout << "->";
    }

    cout << "\n\nOutput array (number = step of first visit, * = item collected,"
            " T = trap, . = never visited):\n";
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (forest[i][j] == 'T') cout << setw(5) << "T";
            else if (!a.visited[i][j]) cout << setw(5) << ".";
            else {
                string s = to_string(a.order[i][j]) + (a.gotItem[i][j] ? "*" : "");
                cout << setw(5) << s;
            }
        }
        cout << "\n";
    }
    cout << "\n";
}

int main()
{
    Animal squirrel; squirrel.name = "SQUIRREL"; squirrel.goal = 'A'; squirrel.target = 7;
    Animal fox;      fox.name      = "FOX";      fox.goal      = 'G'; fox.target      = 6;

    explore(squirrel, 0, 0);
    explore(fox, 2, 4);

    report(squirrel, 0, 0);
    report(fox, 2, 4);
    return 0;
}
