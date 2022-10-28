#include <iostream>
#include <fstream>

using namespace std;

void fraz_nub()
{
    cout << " hehe";
}

struct Card
{
    char color; // color should either be set to R(red) or B(black)
    char suit;  // suit should be S(spades), D(diamonds), C(clubs), H(Hearts)
    char rank;  // rank signifies numbers 2-10 and (A)Ace, (K)King, (Q)Queen and (J)Jack.

    /*Feel free to add any member function IF you want to*/
};

void initialiseDeck(Card *deck, int numberOfCards)
{
    /*  TO DO:------

        Initialise your deck here with by assigning Color, Suit, and Rank to each of the 52 cards.
        You also need to shuffle your deck. Use the random function.
    */

    // for spades
    deck[0].rank = 'A';
    deck[9].rank = 'T';
    deck[10].rank = 'J';
    deck[11].rank = 'Q';
    deck[12].rank = 'K';
    for (int i = 0; i < 13; i++)
    {
        deck[i].color = 'B';
        deck[i].suit = 'S';
        if (i > 0 && i < 9)
        {
            int temp = i + 1;
            char temp2 = char(temp) + '0';
            deck[i].rank = temp2;
        }
    }
    // for diamonds
    deck[13].rank = 'A';
    deck[22].rank = 'T';
    deck[23].rank = 'J';
    deck[24].rank = 'Q';
    deck[25].rank = 'K';
    for (int i = 13; i < 26; i++)
    {
        deck[i].color = 'R';
        deck[i].suit = 'D';
        if (i > 13 && i < 22)
        {
            int temp = i - 13 + 1;
            char temp2 = char(temp) + '0';
            deck[i].rank = temp2;
        }
    }
    // for clubs
    deck[26].rank = 'A';
    deck[35].rank = 'T';
    deck[36].rank = 'J';
    deck[37].rank = 'Q';
    deck[38].rank = 'K';
    for (int i = 26; i < 39; i++)
    {
        deck[i].color = 'B';
        deck[i].suit = 'C';
        if (i > 26 && i < 35)
        {
            int temp = i - 26 + 1;
            char temp2 = char(temp) + '0';
            deck[i].rank = temp2;
        }
    }
    // for hearts
    deck[39].rank = 'A';
    deck[48].rank = 'T';
    deck[49].rank = 'J';
    deck[50].rank = 'Q';
    deck[51].rank = 'K';
    for (int i = 39; i < 52; i++)
    {
        deck[i].color = 'R';
        deck[i].suit = 'H';
        if (i > 39 && i < 48)
        {
            int temp = i - 39 + 1;
            char temp2 = char(temp) + '0';
            deck[i].rank = temp2;
        }
    }
    // for (int i = 0; i < 52; i++)
    // {
    //     cout << deck[i].suit << deck[i].rank << endl;
    // }
    // randomize elements
    for (int i = 0; i < 52; i++)
    {
        int random = rand() % 52;
        Card temp = deck[i];
        deck[i] = deck[random];
        deck[random] = temp;
    }
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
        cout << "Press 1 for column to column move" << endl;
        cout << "Press 2 for column to free cell move" << endl;
        cout << "Press 3 for free cell to column move" << endl;
        cout << "Press 4 to move from column to home cell" << endl;
        cout << "Press 5 to move from free cell to home cell" << endl;
        cout << "Press 6 to save your unfinished game" << endl;
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
    }
    // initializing the last four columns with six cards each
    for (int j = 4; j < 8; j++)
    {
        for (int k = 0; k < 6; k++)
        {
            gameState[j][k] = deck[i];
            i++;
        }
    }
    // the freecells and homeslots are empty upon beginning.
    for (int j = 0; j < 4; j++)
    {
        (freeCells + j)->color = ' ';
        (freeCells + j)->suit = ' ';
        (freeCells + j)->rank = ' ';
    }
    for (int j = 0; j < 4; j++)
    {
        (HomeSlots + j)->color = ' ';
        (HomeSlots + j)->suit = ' ';
        (HomeSlots + j)->rank = ' ';
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
        cout << i+1 << ": ";
        int j = 0;
        while (gameState[i][j].rank != ' ')
        {
            cout << gameState[i][j].rank << gameState[i][j].suit << " ";
            j++;
        }
        cout << endl;
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
    while (gameState[col][i].rank != ' ')
    {
        i++;
    }
    i--;
    int j = 0;
    while (freeCells[j].rank != ' ')
    {
        j++;
    }
    if (j < 5 && freeCells[j].rank == ' ')
    {
        freeCells[j] = gameState[col][i];
        gameState[col][i].rank = ' ';
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
        if (freeCells[freeCell].rank == ' ')
        {
            cout << "\nInvalid move. The given freecell slot is empty!" << endl;
        }
        else
        {
            int i = 0;
            while (gameState[col][i].rank != ' ')
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
                else if (freeCells[freeCell].rank == 'Q' && gameState[col][i].rank == 'K')
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
                else if (freeCells[freeCell].rank == 'J' && gameState[col][i].rank == 'Q')
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
                else if (freeCells[freeCell].rank == 'T' && gameState[col][i].rank == 'J')
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
                cout << "\nInvalid move. Please try again.\n" << endl;
            }
        }
    }
}

int main()
{
    int numberOfCards = 52;
    Card *deck = new Card[numberOfCards]; // this array will store the deck
    Card freeCells[4];                    // this array will be used to store the cards in the free cells
    Card HomeSlots[4];                    // this array will be used to store the cards in the home slots.
    Card **gameState = new Card *[8];     // this is a 2-D array which will store your game's condition at any given point. There will a total of 8 columns. Use this to print display your game.

    for (int i = 0; i < 4; i++)
    {
        gameState[i] = new Card[7];
    }
    for (int i = 4; i < 8; i++)
    {
        gameState[i] = new Card[6];
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
        initializeBoard(deck, numberOfCards, gameState, freeCells, HomeSlots);
        displayBoard(gameState, freeCells, HomeSlots);
    }
    /* else if (newGameOrLoadedGame == 2)
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

     */

    int choice;
    do
    {
        choice = MovesByUser();
        if (choice == 1)
        {
            // TO DO:---- Implement functionality to doing a column to column move
            int col1, col2;
            cout << "Enter the column number from which you want to move the card: ";
            cin >> col1;
            cout << "Enter the column number to which you want to move the card: ";
            cin >> col2;
            if (gameState[col1 - 1][0].rank == '0')
            {
                cout << "The column you entered is empty. Please enter a valid column number." << endl;
            }
            else if (gameState[col2 - 1][0].rank == '0')
            {
                gameState[col2 - 1][0] = gameState[col1 - 1][0];
                gameState[col1 - 1][0].rank = '0';
            }
            else
            {
                int i = 0;
                while (gameState[col2 - 1][i].rank != '0')
                {
                    i++;
                }
                gameState[col2 - 1][i] = gameState[col1 - 1][0];
                gameState[col1 - 1][0].rank = '0';
            }
        }
        else if (choice == 2)
        {
            // TO DO:---- Implement functionality to doing a column to free cell move
            columnToFreeCell(gameState, freeCells);
            displayBoard(gameState, freeCells, HomeSlots);
        }
        else if (choice == 3)
        {
            // TO DO:---- Implement functionality to doing a free cell to column move
            freeCellToColumn(gameState, freeCells);
            displayBoard(gameState, freeCells, HomeSlots);
        }
        else if (choice == 4)
        {
            // TO DO:---- Implement functionality to doing a column to home slot move
        }
        else if (choice == 5)
        {
            // TO DO:---- Implement functionality to doing a free cell to home slot move
        }
        else if (choice == 6)
        {
            // TO DO:---- Save the game state in a file
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
        else
        {
            cout << "INVALID INPUT" << endl;
        }
    } while (choice == 1 || choice == 2 || choice == 3 || choice == 4 || choice == 5 || choice == 6);

    delete[] deck;
    for (int i = 0; i < 8; i++)
    {
        delete[] gameState[i];
    }
    delete[] gameState;
    return 0;
}