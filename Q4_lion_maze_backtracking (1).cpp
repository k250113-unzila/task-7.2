
#include <iostream>
using namespace std;

const int N = 5;

int maze[N][N] = {
    {1, 0, 1, 0, 1},
    {1, 1, 1, 1, 1},
    {0, 1, 0, 1, 1},
    {1, 0, 0, 1, 1},
    {1, 1, 1, 0, 1}
};

int solution[N][N] = {0};                         


const int dr[4] = {1, 0, -1, 0};
const int dc[4] = {0, 1, 0, -1};

bool isSafe(int r, int c)
{
    return r >= 0 && r < N && c >= 0 && c < N      
        && maze[r][c] == 1                         
        && solution[r][c] == 0;                    
}

bool solveMaze(int r, int c)
{
    if (!isSafe(r, c)) return false;

    solution[r][c] = 1;                           

    if (r == N - 1 && c == N - 1) return true;    

    for (int d = 0; d < 4; d++)                    
        if (solveMaze(r + dr[d], c + dc[d]))
            return true;

    solution[r][c] = 0;                            
    return false;
}

int main()
{
    if (solveMaze(0, 0)) {
        cout << "The lion reached the meat! Solution array:\n\n";
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) cout << solution[i][j] << " ";
            cout << endl;
        }
    } else {
        cout << "No path exists for the lion.\n";
    }
    return 0;
}
