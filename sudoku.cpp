#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

const int N = 9;
int sudoku[N][N];
// Function to input the Sudoku puzzle from the user
void inputSudoku(int sudoku[N][N]) {
    cout << "Enter the Sudoku puzzle (use 0 for empty cells):\n";
    int temp;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            while(true){
                cin>>temp;
                if(temp>=0 && temp<10){
                    sudoku[i][j]=temp;
                    break;
                }
                else{
                    cout<<"Number should be between 1-9. Please enter again"<<endl;
                }
            }
        }
    }
}
bool isValid(int board[N][N], int row, int col, int num) {
    if (num < 0 || num > 9 || row > 8 || row < 0 || col > 8 || col < 0)
        return false;

    // Check if 'num' is already in the same row
    for (int i = 0; i < N; i++)
        if (board[row][i] == num)
            return false;

    // Check if 'num' is already in the same column
    for (int i = 0; i < N; i++)
        if (board[i][col] == num)
            return false;

    // Check if 'num' is already in the same 3x3 grid
    int gridRowStart = row - row % 3;
    int gridColStart = col - col % 3;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i + gridRowStart][j + gridColStart] == num)
                return false;

    return true;
}

void printBoard(int grid[N][N]) {
    for (int row = 0; row < N; row++){
      for (int col = 0; col < N; col++){
         if(col == 3 || col == 6)
            cout << " | ";
         cout << grid[row][col] <<" ";
      }
      if(row == 2 || row == 5){
         cout << endl;
         for(int i = 0; i<N; i++)
            cout << "---";
      }
      cout << endl;
   }
}

bool solveSudoku(int board[N][N], int row, int col) {
    // If all cells are filled, the puzzle is solved
    if (row == N - 1 && col == N)
        return true;

    // Move to the next row if the current column is N
    if (col == N) {
        row++;
        col = 0;
    }

    // Skip the cells that already have a value
    if (board[row][col] != 0)
        return solveSudoku(board, row, col + 1);

    // Try filling the current cell with a number from 1 to 9
    for (int num = 1; num <= 9; num++) {
        if (isValid(board, row, col, num)) {
            board[row][col] = num;
            if (solveSudoku(board, row, col + 1))
                return true;
            board[row][col] = 0;
        }
    }
    return false;
}

bool isSolvedCompletely(int grid[N][N]){
    for (int row = 0; row < N; row++)
        for (int col = 0; col < N; col++)
            if (grid[row][col] == 0)
                return false;

    return true;
}

void playGame(int board[N][N]){
    int ch;
    int row, col, num;
    while(true){
        printBoard(board);
        cout << endl << endl;
        cout << "Unable to solve? Enter -1 as row, col and num to view the solved sudoku."<<endl;
        cout << "Enter row: ";
        cin >> row;
        cout << "Enter column: ";
        cin >> col;
        cout << "Enter number: ";
        cin >> num;
    
        if(row == -1 && col == -1 && num == -1){
            solveSudoku(board, 0, 0);
            printBoard(board);
            cout << endl;
            cout << "Better luck next time!!!" << endl;
            return;
        }
        if (isSolvedCompletely(board))
            break;
        row--;
        col--;
        if (!isValid(board, row, col, num)) {
            cout << "Invalid move. Try again." << endl;
            continue;
        }
        board[row][col] = num;
    }

    // Check if the user has solved it correctly or not
    bool solved = true;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == 0) {
                solved = false;
                break;
            }
        }
    }

    if (solved) {
        cout << "Congratulations! You have solved the puzzle." << endl;
        printBoard(board);
    }
    else {
        cout << "Puzzle not solved. Better luck next time." << endl;
    }

}

int main() {

    int board[N][N] = {
        {3, 0, 6, 5, 0, 8, 4, 0, 0},
        {5, 2, 0, 0, 0, 0, 0, 0, 0},
        {0, 8, 7, 0, 0, 0, 0, 3, 1},
        {0, 0, 3, 0, 1, 0, 0, 8, 0},
        {9, 0, 0, 8, 6, 3, 0, 0, 5},
        {0, 5, 0, 0, 9, 0, 6, 0, 0},
        {1, 3, 0, 0, 0, 0, 2, 5, 0},
        {0, 0, 0, 0, 0, 0, 0, 7, 4},
        {0, 0, 5, 2, 0, 6, 3, 0, 0}
    };

    cout << "\t\t\t<********************************************************************************>" << endl;
    cout << "\t\t\t|                        WELCOME TO SUDOKU Game!                                 |" << endl;
    cout << "\t\t\t|       Fill in the missing numbers(represented by 0) to solve the puzzle.       |" << endl;
    cout << "\t\t\t<********************************************************************************>" << endl;

    while (true) {

        int choice;
        cout << endl << endl;
        cout << "\t\t[1] Solve the Sudoku" << endl;
        cout << "\t\t[2] Input a sudoku puzzle"<<endl;
        cout << "\t\t[3] View the solved Sudoku for default sudoku" << endl;
        cout << "\t\t[4] Exit" << endl;
        cout << "\t\tEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                playGame(board);
                break;
            case 2:
                inputSudoku(sudoku);
                cout<<"---------------------------------------------------------------------------"<<endl;
                playGame(sudoku);
                break;
            case 3:
                if (solveSudoku(board, 0, 0))
                {
                    cout << "Completely Solved Sudoku is: "<< endl;
                    cout << endl << endl;
                    for (int row = 0; row < N; row++){
                        for (int col = 0; col < N; col++){
                            if(col == 3 || col == 6)
                                cout << " | ";
                            cout << board[row][col] <<" ";
                        }
                        if(row == 2 || row == 5){
                            cout << endl;
                            for(int i = 0; i<N; i++)
                                cout << "---";
                        }
                        cout << endl;
                    }
                    cout << endl;
                    cout << "Better luck next time!!!" << endl;
                }
                else
                    cout << "No solution found" << endl;
                break;
            case 4:
                exit(0);
            default:
                cout << "Invalid choice" << endl;
        }
    return 0;
}
}
