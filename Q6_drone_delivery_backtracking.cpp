
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

const int N = 6;

char grid[N][N] = {
    {'D','S','S','F','D','F'},
    {'S','S','S','F','S','D'},
    {'S','D','S','S','S','F'},
    {'F','S','F','S','S','F'},
    {'S','S','S','D','S','F'},
    {'S','F','S','S','S','H'}
};

bool visited[N][N] = {false};
vector<pair<int,int>> currentPath, bestPath;
int bestWind = INT_MAX;

const int dr[4] = {1, 0, -1, 0};                   
const int dc[4] = {0, 1, 0, -1};

void findPath(int r, int c, int windCount)
{
    if (r < 0 || r >= N || c < 0 || c >= N) return;   
    if (grid[r][c] == 'F' || visited[r][c]) return; 

    if (grid[r][c] == 'D') windCount++;               
    if (windCount >= bestWind) return;                

    visited[r][c] = true;
    currentPath.push_back({r, c});

    if (grid[r][c] == 'H') {                          
        bestWind = windCount;
        bestPath = currentPath;
    } else {
        for (int d = 0; d < 4; d++)
            findPath(r + dr[d], c + dc[d], windCount);
    }

    currentPath.pop_back();                           
    visited[r][c] = false;
}

int main()
{
    findPath(0, 0, 0);

    if (bestWind == INT_MAX) {
        cout << "No valid path from D to H exists.\n";
        return 0;
    }

    cout << "Complete path followed by the drone:\n  ";
    for (size_t i = 0; i < bestPath.size(); i++) {
        cout << "(" << bestPath[i].first << "," << bestPath[i].second << ")";
        if (i + 1 < bestPath.size()) cout << " -> ";
    }

    cout << "\n\nNumber of high-wind (D) cells encountered: " << bestWind
         << "  (including the starting D cell)\n";

    cout << "\nNo-fly zone (F) cells:\n  ";
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (grid[i][j] == 'F') cout << "(" << i << "," << j << ") ";

  
    bool onPath[N][N] = {false};
    for (size_t i = 0; i < bestPath.size(); i++)
        onPath[bestPath[i].first][bestPath[i].second] = true;

    cout << "\n\nFinal path on the grid (* = path, X = no-fly zone):\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            char ch = onPath[i][j] ? '*' : (grid[i][j] == 'F' ? 'X' : grid[i][j]);
            cout << ch << " ";
        }
        cout << "\n";
    }
    return 0;
}
