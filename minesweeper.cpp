#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Minesweeper {
private:
    int rows, cols, mines;
    vector<vector<int>> board;
    vector<vector<bool>> revealed;

public:
    Minesweeper(int r, int c, int m) : rows(r), cols(c), mines(m) {
        board.resize(rows, vector<int>(cols, 0));
        revealed.resize(rows, vector<bool>(cols, false));

        createMines();
        calculateNumbers();
    }

    void createMines() {
        srand(time(nullptr));

        for (int i = 0; i < mines; ++i) {
            int row, col;
            do {
                row = rand() % rows;
                col = rand() % cols;
            } while (board[row][col] == -1);

            board[row][col] = -1; // -1 represents a mine
        }
    }

    void calculateNumbers() {
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                if (board[row][col] == -1)
                    continue;

                for (int r = max(0, row - 1); r < min(rows, row + 2); ++r) {
                    for (int c = max(0, col - 1); c < min(cols, col + 2); ++c) {
                        if (board[r][c] == -1)
                            board[row][col]++;
                    }
                }
            }
        }
    }

    void printBoard(bool showMines = false) {
        cout << "  ";
        for (int i = 0; i < cols; ++i)
            cout << i << " ";
        cout << "\n";

        for (int row = 0; row < rows; ++row) {
            cout << row << " ";
            for (int col = 0; col < cols; ++col) {
                if (revealed[row][col] || showMines) {
                    if (board[row][col] == -1)
                        cout << "* ";
                    else
                        cout << board[row][col] << " ";
                } else {
                    cout << ". ";
                }
            }
            cout << "\n";
        }
    }

    bool isValidMove(int row, int col) {
        return row >= 0 && row < rows && col >= 0 && col < cols && !revealed[row][col];
    }

    void clearZeros(int row, int col) {
        if (!isValidMove(row, col) || revealed[row][col])
            return;

        revealed[row][col] = true;

        if (board[row][col] == 0) {
            for (int r = max(0, row - 1); r < min(rows, row + 2); ++r) {
                for (int c = max(0, col - 1); c < min(cols, col + 2); ++c) {
                    clearZeros(r, c);
                }
            }
        }
    }

    void playGame() {
        int row, col;

        while (true) {
            printBoard();
            cout << "Enter row and column (separated by space): ";
            cin >> row >> col;

            if (!isValidMove(row, col)) {
                cout << "Invalid move. Try again.\n";
                continue;
            }

            if (board[row][col] == -1) {
                cout << "Game over! You hit a mine.\n";
                printBoard(true);
                break;
            } else if (board[row][col] == 0) {
                clearZeros(row, col);
            } else {
                revealed[row][col] = true;
            }

            bool allMinesRevealed = true;
            for (int r = 0; r < rows; ++r) {
                for (int c = 0; c < cols; ++c) {
                    if (board[r][c] != -1 && !revealed[r][c]) {
                        allMinesRevealed = false;
                        break;
                    }
                }
                if (!allMinesRevealed) break;
            }

            if (allMinesRevealed) {
                cout << "Congratulations! You've cleared all mines.\n";
                printBoard(true);
                break;
            }
        }
    }
};

int main() {
    int rows, cols, mines;

    cout << "Enter number of rows, columns, and mines (separated by space): ";
    cin >> rows >> cols >> mines;

    Minesweeper game(rows, cols, mines);
    game.playGame();

    return 0;
}
