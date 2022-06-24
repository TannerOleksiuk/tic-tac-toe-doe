/*
Author: Tanner Oleksiuk
Date: November 28 2016
Description: Game like tic tac toe but more rows/columns
and the goal is to NOT get a row, diagonal, or column of markers
*/

#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

//Declaring constants
const int MAXLEN = 100;
const int MAX_DRAW_SIZE = 22;
const int TWO = 2;

//if running on linux \e[32m makes text green and \e[33m makes it yellow
//const char playerX = '\e[33mX\e[0m';
//const char playerO = '\e[32mO\e[0m';

// Uncomment if running on windows because it doesn't support colours with \e
const char playerX = 'X';
const char playerO = 'O';


//typedef for all input
typedef char Input[MAXLEN];

//struct for the game board
struct GameBoard{
    int size;
    char *elements;
};

//function prototypes
bool mainMenu();
void gameMain();
int setDrawSize(int size);
void displayRules();
bool initGameBoard(GameBoard &board);
void drawBoard(GameBoard board, int drawSize);
int getSize();
void fillGameBoard(int x, int y, GameBoard &board, char player);
int scanWinner(int size, GameBoard board);
char* allocateArray(int size);
int getInt(int size);
bool verifyCoord(int x, int y, GameBoard board);

//main function
int main(){

    bool cont = mainMenu();

    if(!cont){
        return 0;
    }
    return 0;
}

//main menu that displays at start
bool mainMenu(){
    Input menuOption;

    cout << "Hi welcome to Tic Tac Toe Doh!" << endl;
    cout << "Press Q to quit, S to start a new game, or R for rules: " << endl;

    cin.getline(menuOption, MAXLEN);

    if(strlen(menuOption) <= 0 || strlen(menuOption) > MAXLEN){
        cout << "Invalid Option" << endl << endl;
        return mainMenu();
    }
    else if(menuOption[0]=='Q' || menuOption[0]=='q'){
        cout << "Quitting...." << endl;
        return false;
    }
    else if(menuOption[0]=='S' || menuOption[0]=='s'){
        gameMain();
        return true;
    }
    else if(menuOption[0]=='R' || menuOption[0]=='r'){
        displayRules();
        return true;
    }
    else{
        cout << "Invalid Option" << endl;
        return mainMenu();
    }
}

//main part of game
void gameMain(){

    GameBoard board;
    Input endInput;
    bool gameOver = false;
    int playerIndex = 1;
    int winner = -1;

    int rowPos = 0;
    int colPos = 0;

    //Displays quick greeting and allows for user to read rules if they have not already
    cout << "\nWelcome to Tic Tac Toe Doh!" << endl;
    cout << "If you have not read the rules yet please take the time to do so now!" << endl;
    cout << "Type R to read rules or any other key to continue: " << endl;

    cin.getline(endInput, MAXLEN);
    if(endInput[0]=='R' || endInput[0] == 'r'){
        displayRules();
    }
    cout << endl;

    //sets board size to user input
    board.size = getSize();
    int size = board.size;

    //initializes gameboard and catches if fail
    if(!initGameBoard(board)){
        cout << "Initialization of game board failed..." << endl;
        cout << "Returning to main menu" << endl;
        mainMenu();
    }
    int drawSize = setDrawSize(size);

    //start of actual game
    do{
        //draws board out
        drawBoard(board, drawSize);

        bool validCoord = false;
        //chooses which players turn it is
        if(playerIndex%2==0){
            while(!validCoord){
                cout << "\nX it's your turn! " << endl;
                cout << "Enter a row: ";
                rowPos = getInt(size);
                cout << "Enter a column: ";
                colPos = getInt(size);
                cout << endl;
                validCoord = verifyCoord(colPos, rowPos, board);
            }
            fillGameBoard(colPos, rowPos, board, playerX);
        }
        else{
            while(!validCoord){
                cout << "\nO it's your turn! " << endl;
                cout << "Enter a row: ";
                rowPos = getInt(size);
                cout << "Enter a column: ";
                colPos = getInt(size);
                cout << endl;
                validCoord = verifyCoord(colPos, rowPos, board);
            }
            fillGameBoard(colPos, rowPos, board, playerO);
        }

        //changes turn
        playerIndex++;
        //scans for a winner at end of turn
        winner = scanWinner(size, board);
        //if there is a winner stop the game
        if(winner == 0 || winner == 1 || winner == TWO){
            gameOver = true;
        }

    }while(!gameOver);

    drawBoard(board, drawSize);

    //decides which winner to display
    if(winner == 2){
        cout << "Game Over! " << playerO << " Wins!\n" << endl;
    }
    else if(winner == 1){
        cout << "Game Over! " << playerX << " Wins!\n" << endl;
    }
    else{
        cout << "Game Over! It's a tie!\n" << endl;
    }

    //deletes dynamically allocated memory
    delete [] board.elements;

    //provides an end game menu
    bool validOption = false;
    while(!validOption){

        cout << "Press M to return to menu, Q to quit or R to replay: ";
        cin.getline(endInput, MAXLEN);


        if(strlen(endInput) > 1){
            cout << "Invalid Option" << endl;
        }
        else if(endInput[0] == 'M' || endInput[0] == 'm'){
            cout << endl << endl;
            validOption = true;
            main();
        }
        else if(endInput[0] == 'R' || endInput[0] == 'r'){
            validOption = true;
            gameMain();
        }
        else if(endInput[0] == 'q' || endInput[0] == 'Q'){
            validOption = true;
            //function to exit program (included in cstdlib)
            exit(0);
        }
        else{
            cout << "Invalid Option" << endl;
        }
    }
}

//verifies that on the selected coordinate there isn't already an X or O
bool verifyCoord(int x, int y, GameBoard board){
    x = x-1;
    y = y-1;
    int size = board.size;
    int arrElement = (size*y + x);
    if(board.elements[arrElement] == playerO || board.elements[arrElement] == playerX){
        cout << "That coordinate is already full! Please choose another" << endl;
        return false;
    }
    return true;
}

//gets an integer value used for the row and column
int getInt(int size){
    Input input;
    int returnVal = 0;
    cin.getline(input, MAXLEN);
    if(atoi(input)){
        returnVal = atoi(input);
        if(returnVal <= 0 || returnVal > size){
            cout << "Value out of range of grid" << endl;
            cout << "Please enter a valid number: ";
            return getInt(size);
        }
        else{
            return returnVal;
        }
    }
    else{
        cout << "Invalid Input" << endl;
        cout << "Please enter a valid number: ";
        return getInt(size);
    }
}

//displays rules to user
void displayRules(){
    Input pause;

    cout << "This game is similar to Tic Tac Toe however, ";
    cout << "the first person to get a row, column or diagonal loses!";
    cout << "\nThe board can also be between a 3x3 to 10x10 sized board.";
    cout << "\n\nPress enter to continue" << endl;

    cin.getline(pause, MAXLEN);

    mainMenu();
}

//initializes game board, if any part of the init fails return false
bool initGameBoard(GameBoard &board){
    int size = board.size * board.size;

    board.elements = allocateArray(size);
    //catches if dynamic allocation fails
    if(board.elements == NULL){
        cout << "Memory allocation failure" << endl;
        return false;
    }

    for(int i = 0; i < (size); i++){
        board.elements[i] = ' ';
    }
    //added a null terminator for safety reasons and debugging
    board.elements[size] = '\0';

    return true;
}

//dynamically allocates a char array for the board elements
char* allocateArray(int size){
    char* elements = NULL;
    elements = new char[size*size];
    if(elements == NULL){
        return NULL;
    }
    return elements;
}

//draws the board using a big long algorithm to draw it properly
void drawBoard(GameBoard board, int drawSize){
    //cell value to indicate if it should draw X or O
    int cellValue = 0;

    //This beautiful tree of if statements and for loops
    //all deals with drawing the square to the dynamic proportions
    //selected by the user and also compensates for the extra
    //character when the user selects a 10x10 grid to keep everything
    //aligned
    if(drawSize == MAX_DRAW_SIZE){
        cout << " ";
    }
    for(int row = 0; row < drawSize; row++){
        for(int col = 0; col < drawSize; col++){
            if(row == 0){
                if(((col%TWO)==0) && (col!=0)){
                    cout << (col-(col/TWO));
                }
                else{
                    cout << " ";
                }
            }
            else if(row > 0){
                if(col == 0){
                    if(((row%TWO)==0) && (row!=0)){
                        cout << (row-(row/TWO));
                    }
                    else{
                        cout << " ";
                    }
                }
                else if((row%TWO)!=0){
                    if(((col%TWO)==0) && (col!=0) && drawSize < MAX_DRAW_SIZE){
                        cout << "-";
                    }
                    else if(((col%TWO)==0) && col==TWO && drawSize == MAX_DRAW_SIZE){
                        cout << " -";
                    }
                    else if(((col%TWO)==0) && col > TWO && drawSize == MAX_DRAW_SIZE){
                        cout << "-";
                    }
                    else{
                        cout << " ";
                    }
                }
                else if((row%TWO)==0){
                    if((col%TWO)!=0 && drawSize < MAX_DRAW_SIZE){
                        cout << "|";
                    }
                    else if((col%TWO)!=0 && drawSize == MAX_DRAW_SIZE && col == 1){
                        if(row == (MAX_DRAW_SIZE-TWO)){
                            cout << "|";
                        }
                        else{
                            cout << " |";
                        }
                    }
                    else if((col%TWO)!=0 && drawSize == MAX_DRAW_SIZE && col > 1){
                        cout << "|";
                    }
                    else{
                        cout << board.elements[cellValue];
                        cellValue++;
                    }
                }
                else{
                    cout << " ";
                }
            }
        }
        cout << endl;
    }
}

//Gets the size of board through user input
int getSize(){
    int size = 0;
    Input brdSize;

    cout << "How big of a game board would you like? " << endl;
    cout << "Type in a single number between 3 and 10";
    cout <<" (i.e. board will be made as 3x3 etc): ";

    cin.getline(brdSize, MAXLEN);
    if(atoi(brdSize)){
        size = atoi(brdSize);
        if(10 < size || size < 3){
            cout << "Value not in range of 3-10" << endl;
            return getSize();
        }
        else{
            return size;
        }
    }
    else{
        cout << "Invalid Input" << endl;
        return getSize();
    }
}

//sets the size of how big the canvas of the board will be
//for graphical purposes
int setDrawSize(int size){
    int drawSize = ((size+TWO)+size);
    return drawSize;
}

//fills the board with player character depending on which player calls the function
void fillGameBoard(int x, int y, GameBoard &board, char player){
    //x-1 and y-1 because the rows and cols deal with other chars
    //for drawing purposes, this accounts for that
    x = x-1;
    y = y-1;
    int size = board.size;
    //size*row + col is an algorithm to retrieve the index from the 1-D array
    int arrElement = (size*y + x);
    board.elements[arrElement] = player;
}

//scans for a winner by splicing the board array into a smaller
//dynamic temporary array which allows for easier scanning
int scanWinner(int size, GameBoard board){

    bool isWinner = true;

    char *tempArr;
    tempArr = new char[size];
    if(tempArr == NULL){
        cout << "Memory Allocation Failure" << endl;
        cout << "Attempting to reallocate...." << endl;
        return scanWinner(size, board);
    }


    //Scans for horizontal line win
    for(int row = 0; row < size; row++){
        for(int col = 0; col < size; col++){
            int index = size*(row)+(col);
            tempArr[col] = board.elements[index];
        }

        for(int i = 1; i < size; i++){
            if(tempArr[i-1]!=tempArr[i]){
                isWinner = false;
            }
        }
        if(isWinner){
            if(tempArr[0]==playerO){
                delete[] tempArr;
                return 1;
            }
            else if(tempArr[0]==playerX){
                delete[] tempArr;
                return TWO;
            }
        }
        isWinner = true;
    }

    //scans for vertical line win
    for(int col = 0; col < size; col++){
        for(int row = 0; row < size; row++){
            int index = size*(row)+(col);
            tempArr[row] = board.elements[index];
        }

        for(int i = 1; i < size; i++){
            if(tempArr[i-1]!=tempArr[i]){
                isWinner = false;
            }
        }
        if(isWinner){
            if(tempArr[0]==playerO){
                delete[] tempArr;
                return 1;
            }
            else if(tempArr[0]==playerX){
                delete[] tempArr;
                return TWO;
            }
        }
        isWinner = true;
    }

    //scans for downwards diagonal line win
    for(int col = 0; col < size; col++){
        int diagonalIndex = 0;
        for(int row = 0; row < size; row++){
            int index = size*(row)+ (col+diagonalIndex);
            tempArr[row] = board.elements[index];
            diagonalIndex++;
        }

        for(int i = 1; i < size; i++){
            if(tempArr[i-1]!=tempArr[i]){
                isWinner = false;
            }
        }
        if(isWinner){
            if(tempArr[0]==playerO){
                delete[] tempArr;
                return 1;
            }
            else if(tempArr[0]==playerX){
                delete[] tempArr;
                return TWO;
            }
        }
        isWinner = true;
    }

    //scans for upwards diagonal line win
    int diagonalIndex = (size-1);
    for(int row = 0; row < size; row++){
        int index = size*(row)+ diagonalIndex;
        tempArr[row] = board.elements[index];
        diagonalIndex--;
    }

    for(int i = 1; i < size; i++){
        if(tempArr[i-1]!=tempArr[i]){
            isWinner = false;
        }
    }
    if(isWinner){
        if(tempArr[0]==playerO){
            delete[] tempArr;
            return 1;
        }
        else if(tempArr[0]==playerX){
            delete[] tempArr;
            return TWO;
        }
    }
    isWinner = true;

    //scans for tie (board full and no winner)
    for(int i = 0; i < (size*size); i++){
        if(board.elements[i] == ' '){
            isWinner = false;
        }
    }
    if(isWinner){
        delete[] tempArr;
        return 0;
    }

    //If no winner or tie is detected return -1 to indicate
    delete[] tempArr;
    return -1;
}

