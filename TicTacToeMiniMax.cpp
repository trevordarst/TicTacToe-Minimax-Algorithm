#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void nextMove(char[][3], int&, int&);
bool checkWin(char[][3], char);
bool checkTie(char[][3]);
void printBoard(char[][3]);
void calcBestMove(char[][3], int&, int&);
int findMax(char[][3]);
int findMin(char[][3]);
bool moveOne = true;



int main()
{
    char keepPlaying;

    do              //The do-while loop continues until the player does not want to play anymore.
    {
        char board[3][3] = { {'-','-','-'},{'-','-','-'},{'-','-','-'} };

        while (true)      //This while loop continues until the player or computer wins.
        {
            int rowX = 0, colX = 0, rowO, colO, repeat; //Computer play
            calcBestMove(board, rowX, colX); //this calls the nextMove function using call by reference.
            board[rowX][colX] = 'X';   //this puts the X in the correct spot.
            printBoard(board);  //This calls the printBoard function using call by value.

            if (checkWin(board, 'X')) //The if statement checks if the computer won and breaks out
            {
                cout << "computer wins \n ";
                break;
            };
            if (checkTie(board))
            {
                cout << "There is a tie \n";
                break;
            };
            
            

            //This section prompts the user to input a row and column to place and O.
            {
                repeat = 1;
                while (repeat == 1) //check legal inputs
                {
                    cout << "What row (0, 1, or 2) would you like to place your O in?" << endl;
                    cin >> rowO;
                    cout << "What column (0, 1, or 2) would you like to place your O in?" << endl;
                    cin >> colO;
                    if (board[rowO][colO] == 'X')
                    {
                        repeat = 1;
                        cout << "That spot is already taken. Please choose another row and column."
                            << endl;
                    }
                    else if (board[rowO][colO] == 'O')
                    {
                        repeat = 1;
                        cout << "That spot is already taken. Please choose another row and column."
                            << endl;
                    }
                    else if (rowO > 2 || colO > 2 || rowO < 0 || colO < 0)
                    {
                        repeat = 1;
                        cout << "You must choose either 0, 1, or 2. Please enter another row and column." << endl;

                    }
                    else
                        repeat = 0;
                } //end of lgal input check

                board[rowO][colO] = 'O';    //This places an O in the correct stop.
                printBoard(board);        //This prints the board again.
                if (checkWin(board, 'O')) {
                    cout << "You win " << endl;          //This checks if the player has won.
                    break;
                };
                if (checkTie(board)) {
                    cout << "There is a tie " << endl;
                    break;
                }
            } //end of user play

        } //end of while(true)

        cout << "Do you want to play again? (Y/N)?" << endl;;
        cin >> keepPlaying;

    } while (keepPlaying == 'Y');

    return 0;
}



int findMax(char board[][3])
{

    if(checkWin(board, 'O'))
    {
        return 10;
    }
    
    else if(checkWin(board, 'X'))
    {
        return -10;
    }

    else if (checkTie(board))
    {
        return 0;
    }

    int advantage = -9999;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == '-')
            {

                board[i][j] = 'X';

                advantage = max(advantage, findMin(board));

                board[i][j] = '-';

            }
        }
    }

    return advantage;
}

int findMin(char board[][3])
{

    if (checkWin(board, 'O'))
    {
        return 10;
    }

    else if (checkWin(board, 'X'))
    {
        return -10;
    }

    else if (checkTie(board))
    {
        return 0;
    }

    int advantage = 9999;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == '-')
            {

                board[i][j] = 'O';

                advantage = min(advantage, findMax(board));

                board[i][j] = '-';

            }
        }
    }

    return advantage;
}

void calcBestMove(char board[][3], int& row, int& col)
{
    int advantage = 9999;


    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == '-')
            {
                board[i][j] = 'X';

                int tval = findMax(board);

                if (tval < advantage)
                {
                    advantage = tval;
                    row = i;
                    col = j;
                }

                board[i][j] = '-';
            }
        }
    }

    
}

//modified this so I could code the minimax algorithm more comfortably

bool checkWin(char board[][3], char symbol)
{
    bool win = false;
    for (int i = 0; i <= 2; i++)
    {

        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol)
        {
            win = true;
        }

        else if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol)
        {
            win = true;
        }

    }

    if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol)
    {
        win = true;
    }


    if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol)
    {
        win = true;
    }

    //cout << " win in check function " << win << endl;
    return win;
}


void printBoard(char board[][3])       //This function prints the board.
{
    cout << endl;
    for (int row = 0; row <= 2; row++)
    {
        for (int col = 0; col <= 2; col++)
        {
            cout << board[row][col];
        }
        cout << endl;
    }
    cout << endl;
}




bool checkTie(char board[][3])       //This function checks tie.
{

    int count = 0;
    for (int row = 0; row <= 2; row++)
    {
        for (int col = 0; col <= 2; col++)
        {
            if ((board[row][col] == 'O') || (board[row][col] == 'X'))  count++;
        }
    }
    if (count == 9) return true; else
        return false;
}
