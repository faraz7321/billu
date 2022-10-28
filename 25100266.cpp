#include <iostream>
#include <bits/stdc++.h>
#include <stdlib.h>

using namespace std;

struct Card
{
    char color;       // color should either be set to R(red) or B(black)
    char suit;        // suit should be S(spades), D(diamonds), C(clubs), H(Hearts)
    std::string rank; // rank signifies numbers 2-10 and (A)Ace, (K)King, (Q)Queen and (J)Jack.

    /*Feel free to add any member function IF you want to*/
};

int MovesByUser();
int GameOptions();

void columnToColumn(Card **gameState);
void shuffle(Card *deck, int numberOfCards);
void PrintDeck(Card *deck, int numberOfCards);
void initialiseDeck(Card *deck, int numberOfCards);
void columnToFreeCell(Card **gameState, Card *freeCells);
void freeCellToColumn(Card **gameState, Card *freeCells);
void columnToHomeSlot(Card **gameState, Card *HomeSlots);
void displayBoard(Card **gameState, Card *freeCells, Card *HomeSlots);
void LoadGame(Card *deck, int numberOfCards, Card **gameState, Card *freeCells, Card *HomeSlots);
void SaveGame(Card *deck, int numberOfCards, Card **gameState, Card *freeCells, Card *HomeSlots);
void initializeBoard(Card *deck, int numberOfCards, Card **gameState, Card *freeCells, Card *HomeSlots);

int main()
{
    int choice = 0;
    int numberOfCards = 52;
    Card *deck = new Card[numberOfCards]; // this array will store the deck
    Card freeCells[4];                    // this array will be used to store the cards in the free cells
    Card HomeSlots[4];                    // this array will be used to store the cards in the home slots.
    Card **gameState = new Card *[8];     // this is a 2-D array which will store your game's condition at any given point. There will a total of 8 columns. Use this to print display your game.

    for (int i = 0; i < 4; i++)
    {
        gameState[i] = new Card[8];
    }
    for (int i = 4; i < 8; i++)
    {
        gameState[i] = new Card[7];
    }
    int newGameOrLoadedGame = GameOptions();
    /*
         TO DO:----

         1. If the user wishes to play a new game, intialise the deck using the function given to you and display the a new game to the user.
         2. Else If the user wishes to resume a previously saved game, load it from a file and display it to the user.
    */
    if (newGameOrLoadedGame == 1)
    {
        initialiseDeck(deck, numberOfCards);
        shuffle(deck, numberOfCards);
        initializeBoard(deck, numberOfCards, gameState, freeCells, HomeSlots);
        displayBoard(gameState, freeCells, HomeSlots);
    }
    else if (newGameOrLoadedGame == 2)
    {
        LoadGame(deck, numberOfCards, gameState, freeCells, HomeSlots);
    }

    do
    {
        choice = MovesByUser();
        switch (choice)
        {
        case 1:
            // TO DO:---- Implement functionality to doing a column to column move
            // meed to fix this yet...
            columnToColumn(gameState);
            displayBoard(gameState, freeCells, HomeSlots);
            break;
        case 2:
            // TO DO:---- Implement functionality to doing a column to free cell move
            columnToFreeCell(gameState, freeCells);
            displayBoard(gameState, freeCells, HomeSlots);
            break;
        case 3:
            // TO DO:---- Implement functionality to doing a free cell to column move
            freeCellToColumn(gameState, freeCells);
            displayBoard(gameState, freeCells, HomeSlots);
            break;
        case 4:
            // TO DO:---- Implement functionality to doing a column to home slot move
            columnToHomeSlot(gameState, HomeSlots);
            displayBoard(gameState, freeCells, HomeSlots);
            break;
        case 5:
            // TO DO:---- Implement functionality to doing a free cell to home slot movebreak;
        case 6:
            // TO DO:---- Save the game state in a file
            SaveGame(deck, numberOfCards, gameState, freeCells, HomeSlots);
            break;
        default:
            cout << "INVALID INPUT" << endl;
        }
    } while (choice >= 1 && choice <= 6);

    delete[] deck;
    for (int i = 0; i < 8; i++)
    {
        delete[] gameState[i];
    }
    delete[] gameState;
    return 0;
}
void shuffle(Card *deck, int numberOfCards)
{
    srand(time(0));
    for (int i = 0; i < numberOfCards; i++)
    {
        // Random for remaining positions.
        int r = i + (rand() % (52 - i));
        swap(deck[i], deck[r]);
    }
}
void initialiseDeck(Card *deck, int numberOfCards)
{
    string rankArray[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    char suitArr[4] = {'S', 'C', 'D', 'H'};
    char colorArr[2] = {'B', 'R'};

    int j = 0;
    int k = 0;
    int l = 0;
    for (int i = 0; i < numberOfCards; i++)
    {
        deck[i].rank = rankArray[j];
        deck[i].suit = suitArr[k];
        deck[i].color = colorArr[l];
        j++;
        if (j == 13)
        {
            j = 0;
            k++;
        }
        if (i == 26)
        {
            l++;
        }
    }
}
void PrintDeck(Card *deck, int numberOfCards)
{
    for (int i = 0; i < numberOfCards; i++)
    {
        cout << deck[i].rank << deck[i].suit << deck[i].color << " ";
        if (i == 12 || i == 25 || i == 38 || i == 51)
        {
            cout << endl;
        }
    }
}
void LoadGame(Card *deck, int numberOfCards, Card **gameState, Card *freeCells, Card *HomeSlots)
{
    ifstream fin;
    fin.open("savedGame.txt");
    if (fin.fail())
    {
        cout << "Error opening file" << endl;
        exit(1);
    }
    for (int i = 0; i < 52; i++)
    {
        fin >> deck[i].color;
        fin >> deck[i].suit;
        fin >> deck[i].rank;
    }
    for (int i = 0; i < 4; i++)
    {
        fin >> freeCells[i].color;
        fin >> freeCells[i].suit;
        fin >> freeCells[i].rank;
    }
    for (int i = 0; i < 4; i++)
    {
        fin >> HomeSlots[i].color;
        fin >> HomeSlots[i].suit;
        fin >> HomeSlots[i].rank;
    }
    for (int i = 0; i < 8; i++)
    {
        gameState[i] = new Card[13];
        for (int j = 0; j < 13; j++)
        {
            fin >> gameState[i][j].color;
            fin >> gameState[i][j].suit;
            fin >> gameState[i][j].rank;
        }
    }
    fin.close();
}

void SaveGame(Card *deck, int numberOfCards, Card **gameState, Card *freeCells, Card *HomeSlots)
{
    ofstream fout;
    fout.open("savedGame.txt");
    if (fout.fail())
    {
        cout << "Error opening file" << endl;
        exit(1);
    }
    for (int i = 0; i < 52; i++)
    {
        fout << deck[i].color << " ";
        fout << deck[i].suit << " ";
        fout << deck[i].rank << " ";
    }
    for (int i = 0; i < 4; i++)
    {
        fout << freeCells[i].color << " ";
        fout << freeCells[i].suit << " ";
        fout << freeCells[i].rank << " ";
    }
    for (int i = 0; i < 4; i++)
    {
        fout << HomeSlots[i].color << " ";
        fout << HomeSlots[i].suit << " ";
        fout << HomeSlots[i].rank << " ";
    }
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 13; j++)
        {
            fout << gameState[i][j].color << " ";
            fout << gameState[i][j].suit << " ";
            fout << gameState[i][j].rank << " ";
        }
    }
    fout.close();
}

int MovesByUser()
{
    /*This function takes in the user's move

        TO DO:---- Implement error handling so user gives chooses a move only from the given options

    */
    bool valid = true;
    while (valid)
    {
        int choice;
        cout << "Press 1 for column to column move" << endl
             << "Press 2 for column to free cell move" << endl
             << "Press 3 for free cell to column move" << endl
             << "Press 4 to move from column to home cell" << endl
             << "Press 5 to move from free cell to home cell" << endl
             << "Press 6 to save your unfinished game" << endl;
        cin >> choice;

        if (choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5 || choice == 6)
        {
            return choice;
            valid = false;
        }
        else
        {
            cout << "Please enter a valid input.\n"
                 << endl;
        }
    }
}

int GameOptions()
{
    /*This function takes in the user's wish to play a new game or a previously saved game.

    TO DO:---- Implement error handling so user gives chooses a move only from the given options

    */
    bool valid = true;
    while (valid)
    {

        int choice;
        cout << "Press 1 to start new game" << endl;
        cout << "Press 2 to resume saved game" << endl;
        cin >> choice;
        if (choice == 1 || choice == 2)
        {
            return choice;
            valid = false;
        }
        else
        {
            cout << "Please enter a valid input.\n"
                 << endl;
        }
    }
}

void initializeBoard(Card *deck, int numberOfCards, Card **gameState, Card *freeCells, Card *HomeSlots)
{
    // This function initializes the board for the first time when you start a new game.

    int i = 0;

    // initializing the first four columns with seven cards each
    for (int j = 0; j < 4; j++)
    {
        for (int k = 0; k < 7; k++)
        {
            gameState[j][k] = deck[i];
            i++;
        }
        // putting the last character as null to indicate the end of the column
        gameState[j][7].rank = ' ';
        gameState[j][7].suit = ' ';
        gameState[j][7].color = ' ';
    }
    // initializing the last four columns with six cards each
    for (int j = 4; j < 8; j++)
    {
        for (int k = 0; k < 6; k++)
        {
            gameState[j][k] = deck[i];
            i++;
        }
        // putting the last character as null to indicate the end of the column
        gameState[j][6].rank = ' ';
        gameState[j][6].suit = ' ';
        gameState[j][6].color = ' ';
    }
    // the freecells and homeslots are empty upon beginning.
    for (int j = 0; j < 4; j++)
    {
        freeCells[j].color = ' ';
        freeCells[j].suit = ' ';
        freeCells[j].rank = ' ';
    }
    for (int j = 0; j < 4; j++)
    {
        HomeSlots[j].color = ' ';
        HomeSlots[j].suit = ' ';
        HomeSlots[j].rank = ' ';
    }
}

void displayBoard(Card **gameState, Card *freeCells, Card *HomeSlots)
{
    // This function displays the board for the user to see.

    cout << "Free Cells:  | ";
    for (int i = 0; i < 4; i++)
    {
        cout << freeCells[i].rank << freeCells[i].suit << " |";
    }
    cout << "\tHome Slots:  | ";
    for (int i = 0; i < 4; i++)
    {
        cout << HomeSlots[i].rank << HomeSlots[i].suit << " |";
    }
    cout << endl;
    cout << "Columns: " << endl;
    for (int i = 0; i < 8; i++)
    {
        cout << i + 1 << ": ";
        int j = 0;
        while (gameState[i][j].rank != " ")
        {
            cout << gameState[i][j].rank << gameState[i][j].suit << " ";
            j++;
        }
        cout << endl;
    }
}

// still need to work on column to column move
void columnToColumn(Card **gameState)
{
    // This function implements in the user's move from column to column
    int col1, col2;
    cout << "Enter the column number from which you want to move the card: ";
    cin >> col1;
    cout << "Enter the column number to which you want to move the card: ";
    cin >> col2;
    col1--;
    col2--;
    int i = 0;
    while (gameState[col1][i].rank != " ")
    {
        i++;
    }
    i--;
    int j = 0;
    while (gameState[col2][j].rank != " ")
    {
        j++;
    }
    if (gameState[col2][j - 1].rank == " ")
    {
        gameState[col2][j - 1] = gameState[col1][i];
        gameState[col1][i].rank = ' ';
        gameState[col1][i].suit = ' ';
        gameState[col1][i].color = ' ';
    }
    else if (gameState[col2][j - 1].rank != " ")
    {
        if (gameState[col2][j - 1].color != gameState[col1][i].color)
        {
            if (stoi(gameState[col2][j - 1].rank) == stoi(gameState[col1][i].rank) + 1)
            {
                gameState[col2][j] = gameState[col1][i];
                gameState[col1][i].rank = ' ';
                gameState[col1][i].suit = ' ';
                gameState[col1][i].color = ' ';
            }
            else if (gameState[col2][j - 1].rank == "K" && gameState[col1][i].rank == "Q")
            {
                gameState[col2][j] = gameState[col1][i];
                gameState[col1][i].rank = ' ';
                gameState[col1][i].suit = ' ';
                gameState[col1][i].color = ' ';
            }
            else if (gameState[col2][j - 1].rank == "Q" && gameState[col1][i].rank == "J")
            {
                gameState[col2][j] = gameState[col1][i];
                gameState[col1][i].rank = ' ';
                gameState[col1][i].suit = ' ';
                gameState[col1][i].color = ' ';
            }
            else if (gameState[col2][j - 1].rank == "J" && gameState[col1][i].rank == "T")
            {
                gameState[col2][j] = gameState[col1][i];
                gameState[col1][i].rank = ' ';
                gameState[col1][i].suit = ' ';
                gameState[col1][i].color = ' ';
            }
            else
            {
                cout << "Invalid move. Please try again." << endl;
            }
        }
    }
}

void columnToFreeCell(Card **gameState, Card *freeCells)
{
    // This function implements in the user's move from column to freecell
    int col;
    cout << "Enter the column number from which you want to move the card: ";
    cin >> col;
    col--;
    int i = 0;
    while (gameState[col][i].rank != " ")
    {
        i++;
    }
    i--;
    int j = 0;
    while (freeCells[j].rank != " ")
    {
        j++;
    }
    if (j < 5 && freeCells[j].rank == " ")
    {
        freeCells[j] = gameState[col][i];
        // i need to dynamically change the size of columns.... uskay ilawa this works fine but i need to fix that..

        // Card **old_array = gameState;
        // gameState[col] = new Card[i];
        //  for (int k = 0; k < i; k++)
        //  {
        //      cout << "print oldarr[col][k]: " << old_array[col][k].rank << old_array[col][k].suit << endl;
        //      gameState[col][k] = old_array[col][k];
        //      cout << "now print game state: " << gameState[col][k].rank << gameState[col][k].suit << endl;
        //  }

        // for (int x = 0; x < 8; x++)
        // {
        //     delete[] old_array[x];
        // }
        // delete[] old_array;

        gameState[col][i].rank = " ";
        gameState[col][i].suit = ' ';
        gameState[col][i].color = ' ';
    }
    else
    {
        cout << "\nInvalid move. Your freecells are full!" << endl;
    }
}

void freeCellToColumn(Card **gameState, Card *freeCells)
{
    // This function implements the users move from any freecell to column
    int col;
    int freeCell;
    cout << "Enter the column number to which you want to move the card: ";
    cin >> col;
    cout << "Enter the freecell number from which you want to move the card: ";
    cin >> freeCell;
    col--;
    freeCell--;
    if (freeCell > 4)
    {
        cout << "\nInvalid move. There are only 4 freecells :(" << endl;
    }
    else
    {
        if (freeCells[freeCell].rank == " ")
        {
            cout << "\nInvalid move. The given freecell slot is empty!" << endl;
        }
        else
        {
            int i = 0;
            while (gameState[col][i].rank != " ")
            {
                i++;
            }
            i--;
            if (freeCells[freeCell].color != gameState[col][i].color)
            {
                if (freeCells[freeCell].rank + char(1) == gameState[col][i].rank)
                {
                    gameState[col][i + 1].rank = freeCells[freeCell].rank;
                    gameState[col][i + 1].suit = freeCells[freeCell].suit;
                    gameState[col][i + 1].color = freeCells[freeCell].color;

                    freeCells[freeCell].rank = ' ';
                    freeCells[freeCell].suit = ' ';
                    freeCells[freeCell].color = ' ';

                    gameState[col][i + 2].rank = ' ';
                    gameState[col][i + 2].suit = ' ';
                    gameState[col][i + 2].color = ' ';
                }
                else if (freeCells[freeCell].rank == "Q" && gameState[col][i].rank == "K")
                {
                    gameState[col][i + 1].rank = freeCells[freeCell].rank;
                    gameState[col][i + 1].suit = freeCells[freeCell].suit;
                    gameState[col][i + 1].color = freeCells[freeCell].color;

                    freeCells[freeCell].rank = ' ';
                    freeCells[freeCell].suit = ' ';
                    freeCells[freeCell].color = ' ';

                    gameState[col][i + 2].rank = ' ';
                    gameState[col][i + 2].suit = ' ';
                    gameState[col][i + 2].color = ' ';
                }
                else if (freeCells[freeCell].rank == "J" && gameState[col][i].rank == "Q")
                {
                    gameState[col][i + 1].rank = freeCells[freeCell].rank;
                    gameState[col][i + 1].suit = freeCells[freeCell].suit;
                    gameState[col][i + 1].color = freeCells[freeCell].color;

                    freeCells[freeCell].rank = ' ';
                    freeCells[freeCell].suit = ' ';
                    freeCells[freeCell].color = ' ';

                    gameState[col][i + 2].rank = ' ';
                    gameState[col][i + 2].suit = ' ';
                    gameState[col][i + 2].color = ' ';
                }
                else if (freeCells[freeCell].rank == "T" && gameState[col][i].rank == "J")
                {
                    gameState[col][i + 1].rank = freeCells[freeCell].rank;
                    gameState[col][i + 1].suit = freeCells[freeCell].suit;
                    gameState[col][i + 1].color = freeCells[freeCell].color;

                    freeCells[freeCell].rank = ' ';
                    freeCells[freeCell].suit = ' ';
                    freeCells[freeCell].color = ' ';

                    gameState[col][i + 2].rank = ' ';
                    gameState[col][i + 2].suit = ' ';
                    gameState[col][i + 2].color = ' ';
                }
                else
                {
                    cout << "\nInvalid move. Please try again." << endl;
                }
            }
            else
            {
                cout << "\nInvalid move. Please try again.\n"
                     << endl;
            }
        }
    }
}

void columnToHomeSlot(Card **gameState, Card *HomeSlots)
{
}
