// TASK-2: Tic-Tac-Toe Game in C++
// This program implements a simple Tic-Tac-Toe game for two players.
// It keeps track of scores and allows players to play multiple rounds.

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// ================= GLOBALS =================
char board[3][3];   // 3x3 Tic-Tac-Toe board
string player1, player2;
int score1 = 0, score2 = 0, draws = 0;
const string SCORE_FILE = "scores.txt";

// ================= FUNCTION DECLARATIONS =================
void initializeBoard();
void displayBoard();
bool makeMove(char mark, int row, int col);
bool checkWin(char mark);
bool checkDraw();
void playRound();
void loadScores();
void saveScores();

// ================= MAIN =================
int main() {
    cout << "====================================\n";
    cout << "         TIC-TAC-TOE GAME   \n";
    cout << "====================================\n";

    cout << "Enter name for Player 1 (X): ";
    getline(cin, player1);
    cout << "Enter name for Player 2 (O): ";
    getline(cin, player2);

    // Load scores from file
    loadScores();

    int choice;
    do {
        playRound();
        cout << "\nCurrent Scores:\n";
        cout << " " << player1 << " (X) : " << score1 << endl;
        cout << " " << player2 << " (O) : " << score2 << endl;
        cout << " Draws          : " << draws << endl;

        saveScores();

        cout << "\nDo you want to play another round? (1=Yes, 0=No): ";
        cin >> choice;
    } while (choice == 1);

    cout << "\n======================\n";
    cout << " Final Scores:\n";
    cout << " " << player1 << " (X) : " << score1 << endl;
    cout << " " << player2 << " (O) : " << score2 << endl;
    cout << " Draws          : " << draws << endl;
    cout << "======================\n";
    cout << "Thanks for playing!\n";

    return 0;
}

// ================= FUNCTIONS =================

// Initialize the board with empty cells
void initializeBoard() {
    char c = '1';
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = c++;
}

// Display the board
void displayBoard() {
    cout << "\n";
    cout << "     |     |     \n";
    cout << "  " << board[0][0] << "  |  " << board[0][1] << "  |  " << board[0][2] << "\n";
    cout << "_____|_____|_____\n";
    cout << "     |     |     \n";
    cout << "  " << board[1][0] << "  |  " << board[1][1] << "  |  " << board[1][2] << "\n";
    cout << "_____|_____|_____\n";
    cout << "     |     |     \n";
    cout << "  " << board[2][0] << "  |  " << board[2][1] << "  |  " << board[2][2] << "\n";
    cout << "     |     |     \n\n";
}

// Make a move if the cell is free
bool makeMove(char mark, int row, int col) {
    if (board[row][col] != 'X' && board[row][col] != 'O') {
        board[row][col] = mark;
        return true;
    }
    return false;
}

// Check win condition
bool checkWin(char mark) {
    // Rows & Columns
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == mark && board[i][1] == mark && board[i][2] == mark) return true;
        if (board[0][i] == mark && board[1][i] == mark && board[2][i] == mark) return true;
    }
    // Diagonals
    if (board[0][0] == mark && board[1][1] == mark && board[2][2] == mark) return true;
    if (board[0][2] == mark && board[1][1] == mark && board[2][0] == mark) return true;

    return false;
}

// Check draw condition
bool checkDraw() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return false;
    return true;
}

// Play one round of Tic-Tac-Toe
void playRound() {
    initializeBoard();
    displayBoard();

    char mark;
    int move, row, col;
    bool turn = true; // true = Player1, false = Player2

    while (true) {
        if (turn) {
            cout << player1 << " (X), enter your move (1-9): ";
            mark = 'X';
        } else {
            cout << player2 << " (O), enter your move (1-9): ";
            mark = 'O';
        }
        cin >> move;
        row = (move - 1) / 3;
        col = (move - 1) % 3;

        if (move < 1 || move > 9 || !makeMove(mark, row, col)) {
            cout << "Invalid move! Try again.\n";
            continue;
        }

        displayBoard();

        if (checkWin(mark)) {
            if (mark == 'X') {
                cout << player1 << " WINS this round!\n";
                score1++;
            } else {
                cout << player2 << " WINS this round!\n";
                score2++;
            }
            break;
        }

        if (checkDraw()) {
            cout << "It's a DRAW!\n";
            draws++;
            break;
        }

        turn = !turn; // Switch turn
    }
}

// Load scores from file
void loadScores() {
    ifstream ifs(SCORE_FILE);
    if (ifs) {
        ifs >> score1 >> score2 >> draws;
    }
    ifs.close();
}

// Save scores to file
void saveScores() {
    ofstream ofs(SCORE_FILE);
    ofs << score1 << " " << score2 << " " << draws;
    ofs.close();
}
