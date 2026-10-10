
#include <iostream>
using namespace std;

const int N = 16;

int  colOfRow[N];            
bool colUsed[N];             
bool diagDown[2 * N - 1];    
bool diagUp[2 * N - 1];      
long long nodesVisited = 0;

bool placeFlags(int row)
{
    if (row == N) return true;                    

    for (int col = 0; col < N; col++) {
        nodesVisited++;
        if (colUsed[col] || diagDown[row - col + N - 1] || diagUp[row + col])
            continue;                            

        colUsed[col] = diagDown[row - col + N - 1] = diagUp[row + col] = true;   
        colOfRow[row] = col;

        if (placeFlags(row + 1)) return true;      

        colUsed[col] = diagDown[row - col + N - 1] = diagUp[row + col] = false;  
    }
    return false;
}

int main()
{
    if (placeFlags(0)) {
        cout << "Maximum number of flags on the " << N << "x" << N << " grid = " << N << "\n\n";
        for (int r = 0; r < N; r++) {
            for (int c = 0; c < N; c++)
                cout << (colOfRow[r] == c ? "F " : ". ");
            cout << "\n";
        }
        cout << "\n(Search nodes examined: " << nodesVisited << ")\n";
    } else {
        cout << "No full placement found.\n";
    }
    return 0;
}
