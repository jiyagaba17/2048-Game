#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

int board[4][4];

int dirLine[] = {1, 0, -1, 0};
int dirColumn[] = {0, 1, 0, -1};

pair<int, int> generateUnoccupiedPosition() {
    vector<pair<int, int>> emptyPositions;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 0) {
                emptyPositions.push_back(make_pair(i, j));
            }
        }
    }

    int index = rand() % emptyPositions.size();
    return emptyPositions[index];
}

void addPiece() {
    pair<int, int> pos = generateUnoccupiedPosition();
    board[pos.first][pos.second] = (rand() % 2 + 1) * 2; // Add 2 or 4
}

void newGame() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            board[i][j] = 0;
        }
    }
    addPiece(); // Add first piece
    addPiece(); // Add second piece
}

void printUI() {
    // Use "clear" for Linux/Mac
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    cout << endl << "-----------2048 GAME-----------" << endl << endl;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 0) {
                cout << setw(4) << ".";
            } else {
                cout << setw(4) << board[i][j];
            }
        }
        cout << endl;
    }

    cout << "n :new game, u:up , d:down, r:right, l:left, q:quit" << endl << endl;
}

bool canDoMove(int line, int column, int nextLine, int nextColumn) {
    // Prevents out-of-bounds moves and multiple merges
    if (nextLine < 0 || nextColumn < 0 || nextLine >= 4 || nextColumn >= 4 ||
        (board[line][column] != board[nextLine][nextColumn] && board[nextLine][nextColumn] != 0)) {
        return false;
    }
    return true;
}

void applyMove(int direction) {
    int startLine = (direction == 0) ? 3 : 0;
    int startColumn = (direction == 1) ? 3 : 0;
    int lineStep = (direction == 0) ? -1 : 1;
    int columnStep = (direction == 1) ? -1 : 1;

    bool moved = false;
    bool merged[4][4] = {false};

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int line = startLine + i * lineStep;
            int column = startColumn + j * columnStep;

            while (true) {
                int nextLine = line + dirLine[direction];
                int nextColumn = column + dirColumn[direction];

                if (nextLine < 0 || nextColumn < 0 || nextLine >= 4 || nextColumn >= 4) {
                    break; // Out of bounds
                }

                if (board[nextLine][nextColumn] == 0) {
                    board[nextLine][nextColumn] = board[line][column];
                    board[line][column] = 0;
                    line = nextLine;
                    column = nextColumn;
                    moved = true;
                } else if (board[nextLine][nextColumn] == board[line][column] && !merged[nextLine][nextColumn]) {
                    board[nextLine][nextColumn] *= 2;
                    board[line][column] = 0;
                    merged[nextLine][nextColumn] = true;
                    moved = true;
                    break; // Stop moving this tile
                } else {
                    break; // Can't move further
                }

                if (board[nextLine][nextColumn] == 2048) {
                    printUI();
                    cout << "Congratulations! You've reached 2048!" << endl;
                    exit(0); // End the game when the player wins
                }
            }
        }
    }

    if (moved) {
        addPiece(); // Add new piece only if any move was successful
    }
}

bool canMove() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 0) {
                return true;
            }
            for (int d = 0; d < 4; d++) {
                int nextLine = i + dirLine[d];
                int nextColumn = j + dirColumn[d];
                if (nextLine >= 0 && nextColumn >= 0 && nextLine < 4 && nextColumn < 4 &&
                    (board[nextLine][nextColumn] == 0 || board[nextLine][nextColumn] == board[i][j])) {
                    return true;
                }
            }
        }
    }
    return false;
}

int main() {
    srand(time(0));

    char commandToDir[256] = {};
    commandToDir['d'] = 0;
    commandToDir['r'] = 1;
    commandToDir['u'] = 2;
    commandToDir['l'] = 3;

    cout << endl;

    newGame(); // Start a new game with two pieces

    while (true) {
        printUI();
        char command;
        cin >> command;

        if (command == 'n') {
            newGame(); // Start a new game
        } else if (command == 'q') {
            break; // Quit the game
        } else if (command == 'u' || command == 'd' || command == 'l' || command == 'r') {
            int currentDirection = commandToDir[command];
            applyMove(currentDirection); // Apply the move in the given direction

            if (!canMove()) {
                printUI();
                cout << "Game Over!" << endl; // Check if no moves are possible
                break;
            }
        }
    }
}

// #include <iostream>
// #include <iomanip>
// #include <ctime>
// #include <cstdlib>
// #include <vector>
// #include <algorithm>

// using namespace std;

// int board[4][4];

// int dirLine[] = {1, 0, -1, 0};
// int dirColumn[] = {0, 1, 0, -1};

// pair<int, int> generateUnoccupiedPosition()
// {
//     vector<pair<int, int>> emptyPositions;
//     for (int i = 0; i < 4; i++)
//     {
//         for (int j = 0; j < 4; j++)
//         {
//             if (board[i][j] == 0)
//             {
//                 emptyPositions.push_back(make_pair(i, j));
//             }
//         }
//     }

//     int index = rand() % emptyPositions.size();
//     return emptyPositions[index];
// }

// void addPiece()
// {
//     pair<int, int> pos = generateUnoccupiedPosition();
//     board[pos.first][pos.second] = (rand() % 2 + 1) * 2; // Add 2 or 4
// }

// void newGame()
// {
//     for (int i = 0; i < 4; i++)
//     {
//         for (int j = 0; j < 4; j++)
//         {
//             board[i][j] = 0;
//         }
//     }
//     addPiece(); // Add first piece
//     addPiece(); // Add second piece
// }

// void printUI()
// {
//     // Use "clear" for Linux/Mac
//     #ifdef _WIN32
//         system("cls");
//     #else
//         system("clear");
//     #endif

//     cout << endl << "-----------2048 GAME-----------" << endl << endl;

//     for (int i = 0; i < 4; i++)
//     {
//         for (int j = 0; j < 4; j++)
//         {
//             if (board[i][j] == 0)
//             {
//                 cout << setw(4) << ".";
//             }
//             else
//             {
//                 cout << setw(4) << board[i][j];
//             }
//         }
//         cout << endl;
//     }

//     cout << "n :new game, u:up , d:down, r:right, l:left, q:quit" << endl << endl;
// }

// bool canDoMove(int line, int column, int nextLine, int nextColumn)
// {
//     // Prevents out-of-bounds moves and multiple merges
//     if (nextLine < 0 || nextColumn < 0 || nextLine >= 4 || nextColumn >= 4 ||
//         (board[line][column] != board[nextLine][nextColumn] && board[nextLine][nextColumn] != 0))
//     {
//         return false;
//     }
//     return true;
// }

// void applyMove(int direction)
// {
//     int startLine = (direction == 0) ? 3 : 0;
//     int startColumn = (direction == 1) ? 3 : 0;
//     int lineStep = (direction == 0) ? -1 : 1;
//     int columnStep = (direction == 1) ? -1 : 1;

//     bool moved = false;
//     bool merged[4][4] = {false};

//     for (int i = 0; i < 4; i++)
//     {
//         for (int j = 0; j < 4; j++)
//         {
//             int line = startLine + i * lineStep;
//             int column = startColumn + j * columnStep;

//             while (true)
//             {
//                 int nextLine = line + dirLine[direction];
//                 int nextColumn = column + dirColumn[direction];

//                 if (!canDoMove(line, column, nextLine, nextColumn) || merged[nextLine][nextColumn])
//                 {
//                     break;
//                 }

//                 if (board[nextLine][nextColumn] == board[line][column])
//                 {
//                     merged[nextLine][nextColumn] = true; // Prevent multiple merges
//                 }

//                 board[nextLine][nextColumn] += board[line][column];
//                 board[line][column] = 0;
//                 line = nextLine;
//                 column = nextColumn;
//                 moved = true;

//                 if (board[nextLine][nextColumn] == 2048)
//                 {
//                     printUI();
//                     cout << "Congratulations! You've reached 2048!" << endl;
//                     exit(0); // End the game when the player wins
//                 }
//             }
//         }
//     }

//     if (moved)
//     {
//         addPiece(); // Add new piece only if any move was successful
//     }
// }

// bool canMove()
// {
//     for (int i = 0; i < 4; i++)
//     {
//         for (int j = 0; j < 4; j++)
//         {
//             if (board[i][j] == 0)
//             {
//                 return true;
//             }
//             for (int d = 0; d < 4; d++)
//             {
//                 int nextLine = i + dirLine[d];
//                 int nextColumn = j + dirColumn[d];
//                 if (nextLine >= 0 && nextColumn >= 0 && nextLine < 4 && nextColumn < 4 &&
//                     (board[nextLine][nextColumn] == 0 || board[nextLine][nextColumn] == board[i][j]))
//                 {
//                     return true;
//                 }
//             }
//         }
//     }
//     return false;
// }

// int main()
// {
//     srand(time(0));

//     char commandToDir[256] = {};
//     commandToDir['d'] = 0;
//     commandToDir['r'] = 1;
//     commandToDir['u'] = 2;
//     commandToDir['l'] = 3;

//     cout << endl;

//     newGame(); // Start a new game with two pieces

//     while (true)
//     {
//         printUI();
//         char command;
//         cin >> command;

//         if (command == 'n')
//         {
//             newGame(); // Start a new game
//         }
//         else if (command == 'q')
//         {
//             break; // Quit the game
//         }
//         else if (command == 'u' || command == 'd' || command == 'l' || command == 'r')
//         {
//             int currentDirection = commandToDir[command];
//             applyMove(currentDirection); // Apply the move in the given direction

//             if (!canMove())
//             {
//                 printUI();
//                 cout << "Game Over!" << endl; // Check if no moves are possible
//                 break;
//             }
//         }
//     }
// }

