
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;


void checkGuess(int secret, int guess, int player, int numPlayers, int attempts);


void takeTurn(int secret, int player, int numPlayers, int attempts)
{
    int guess;
    cout << "Player " << player << ", enter your guess (1-100): ";
    if (!(cin >> guess)) {
        cout << "\nInput ended. Game aborted.\n";
        return;
    }
    checkGuess(secret, guess, player, numPlayers, attempts);   
}


void checkGuess(int secret, int guess, int player, int numPlayers, int attempts)
{
    if (guess < 1 || guess > 100) {                
        cout << "Invalid guess! Enter a number from 1 to 100.\n";
        takeTurn(secret, player, numPlayers, attempts);
        return;
    }

    attempts++;

    if (guess == secret) {                         
        cout << "\n*** Player " << player << " guessed it! The number was "
             << secret << ". Total guesses: " << attempts << " ***\n";
        return;
    }

    cout << (guess > secret ? "Too high!" : "Too low!")
         << " Turn passes to the next player.\n\n";

    int nextPlayer = player % numPlayers + 1;
    takeTurn(secret, nextPlayer, numPlayers, attempts);     
}

int main()
{
    srand((unsigned)time(0));
    int secret = rand() % 100 + 1;

    int numPlayers = 0;
    cout << "Enter number of players: ";
    while (!(cin >> numPlayers) || numPlayers < 1) {
        if (cin.eof()) return 0;
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Please enter a valid number of players (>= 1): ";
    }

    cout << "\nI have picked a secret number between 1 and 100. Good luck!\n\n";
    takeTurn(secret, 1, numPlayers, 0);
    return 0;
}
