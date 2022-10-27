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
    for (int i = 0; i < 13; i++)
    {
        (deck + i)->color = 'B';
        (deck + i)->suit = 'S';
        if (i == 0)
        {
            (deck + i)->rank = 'A';
        }
        else if (i == 10)
        {
            (deck + i)->rank = 'J';
        }
        else if (i == 11)
        {
            (deck + i)->rank = 'Q';
        }
        else if (i == 12)
        {
            (deck + i)->rank = 'K';
        }
        else if (i == 9)
        {
            (deck + i)->rank = 'T';
        }
        else
        {
            (deck + i)->rank = i + 1;
        }
    }
    // for diamonds
    for (int i = 0; i < 13; i++)
    {
        (deck + i + 13)->color = 'R';
        (deck + i + 13)->suit = 'D';
        if (i == 0)
        {
            (deck + i + 13)->rank = 'A';
        }
        else if (i == 10)
        {
            (deck + i + 13)->rank = 'J';
        }
        else if (i == 11)
        {
            (deck + i + 13)->rank = 'Q';
        }
        else if (i == 12)
        {
            (deck + i + 13)->rank = 'K';
        }
        else if (i == 9)
        {
            (deck + i + 13)->rank = 'T';
        }
        else
        {
            (deck + i + 13)->rank = i + 1;
        }
    }
    // for clubs
    for (int i = 0; i < 13; i++)
    {
        (deck + i + 26)->color = 'B';
        (deck + i + 26)->suit = 'C';
        if (i == 0)
        {
            (deck + i + 26)->rank = 'A';
        }
        else if (i == 10)
        {
            (deck + i + 26)->rank = 'J';
        }
        else if (i == 11)
        {
            (deck + i + 26)->rank = 'Q';
        }
        else if (i == 12)
        {
            (deck + i + 26)->rank = 'K';
        }
        else if (i == 9)
        {
            (deck + i + 26)->rank = 'T';
        }
        else
        {
            (deck + i + 26)->rank = i + 1;
        }
    }
    // for hearts
    for (int i = 0; i < 13; i++)
    {
        (deck + i + 39)->color = 'R';
        (deck + i + 39)->suit = 'H';
        if (i == 0)
        {
            (deck + i + 39)->rank = 'A';
        }
        else if (i == 10)
        {
            (deck + i + 39)->rank = 'J';
        }
        else if (i == 11)
        {
            (deck + i + 39)->rank = 'Q';
        }
        else if (i == 12)
        {
            (deck + i + 39)->rank = 'K';
        }
        else if (i == 9)
        {
            (deck + i + 39)->rank = 'T';
        }
        else
        {
            (deck + i + 39)->rank = i + 1;
        }
    }
    //randomize elements
    for (int i = 0; i < 52; i++)
    {
        int random = rand() % 52;
        Card temp = *(deck + i);
        *(deck + i) = *(deck + random);
        *(deck + random) = temp;
    }
    for (int i = 0; i < 52; i++)
    {
        cout << (deck + i)->suit << (deck + i)->rank << endl;
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

    cout << "Free Cells: ";
    for (int i = 0; i < 4; i++)
    {
        cout << (freeCells + i)->rank << (freeCells + i)->suit << " |";
    }
    cout << "\tHome Slots: ";
    for (int i = 0; i < 4; i++)
    {
        cout << (HomeSlots + i)->rank << (HomeSlots + i)->suit << " |";
    }
    cout << endl;
    cout << "Columns: " << endl;
    for (int i = 0; i < 8; i++)
    {
        cout << i + 1 << ": ";
        for (int j = 0; j < 7; j++)
        {
            cout << (gameState[i][j]).rank << (gameState[i][j]).suit << " ";
        }
        cout << endl;
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

    /*
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
            }
            else if (choice == 3)
            {
                // TO DO:---- Implement functionality to doing a free cell to column move
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

        */

    delete[] deck;
    for (int i = 0; i < 8; i++)
    {
        delete[] gameState[i];
    }
    delete[] gameState;
    return 0;
}