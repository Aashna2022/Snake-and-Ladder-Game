#include <iostream>
#include <cstdlib>
#include <ctime>
#include <map>
using namespace std;

const int START_POS = 1;
const int WIN_POS = 100;

// Roll a dice (1–6)
int rollDice() {
    return (rand() % 6) + 1;
}

// Move a player based on dice + snakes + ladders
void movePlayer(int &position, int dice, const map<int,int> &snakes, const map<int,int> &ladders) {
    if (position + dice <= WIN_POS) {
        position += dice;
        cout << "  Moved to " << position << endl;

        // Ladder check
        if (ladders.count(position)) {
            cout << "  Found ladder! Climb up to " << ladders.at(position) << endl;
            position = ladders.at(position);
        }
        // Snake check
        else if (snakes.count(position)) {
            cout << "  Oh no! Snake! Slide down to " << snakes.at(position) << endl;
            position = snakes.at(position);
        }
    } else {
        cout << "  Roll too high to reach 100, stay at " << position << endl;
    }
}

int main() {
    srand(time(0));

    // Define ladders
    map<int,int> ladders = {
        {1, 38}, {4, 14}, {8, 10}, {21, 42}, {28, 76},
        {50, 67}, {71, 92}, {80, 99}
    };

    // Define snakes
    map<int,int> snakes = {
        {36, 6}, {32, 10}, {48, 26}, {62, 18}, {88, 24},
        {95, 56}, {97, 78}
    };

    int player1 = START_POS, player2 = START_POS;
    bool player1Turn = true;

    cout << "=== Snakes and Ladders Game (Start at 1) ===" << endl;

    while (true) {
        if (player1Turn) {
            cout << "\n Player 1's turn (Position: " << player1 << ")" << endl;
            int dice = rollDice();
            cout << "  Rolled: " << dice << endl;
            movePlayer(player1, dice, snakes, ladders);

            if (player1 == WIN_POS) {
                cout << "\n Player 1 WINS!" << endl;
                break;
            }

            // Extra turn if dice = 6
            if (dice != 6) {
                player1Turn = false;  // switch to Player 2
            } else {
                cout << "  Rolled a 6! Extra turn for Player 1!" << endl;
            }
        } 
        else {
            cout << "\n Player 2's turn (Position: " << player2 << ")" << endl;
            int dice = rollDice();
            cout << "  Rolled: " << dice << endl;
            movePlayer(player2, dice, snakes, ladders);

            if (player2 == WIN_POS) {
                cout << "\n Player 2 WINS!" << endl;
                break;
            }

            // Extra turn if dice = 6
            if (dice != 6) {
                player1Turn = true;  // switch to Player 1
            } else {
                cout << "  Rolled a 6! Extra turn for Player 2!" << endl;
            }
        }
        // ✅ Pause before the next turn
        cout << "\nPress ENTER to continue to the next turn...";
        cin.ignore();   // Wait for Enter
    }

    return 0;
}
