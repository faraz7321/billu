#include <iostream>
#include <bits/stdc++.h>
#include <stdlib.h>

using namespace std;

struct Card
{
    char color; // color should either be set to R(red) or B(black)
    char suit;  // suit should be S(spades), D(diamonds), C(clubs), H(Hearts)
    char rank;  // rank signifies numbers 2-10 and (A)Ace, (K)King, (Q)Queen and (J)Jack.

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
void freeCellToHomeSlot(Card *freeCells, Card *HomeSlots);
void displayBoard(Card **gameState, Card *freeCells, Card *HomeSlots);
bool LoadDeck(Card *deck, int numberOfCards, string filename);
bool LoadGameState(Card **gameState, string filename);
bool SaveDeck(Card *deck, int numberOfCards, string filename);
bool SaveGameState(Card **gameState, string filename);
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

    if (newGameOrLoadedGame == 1)
    {
        initialiseDeck(deck, numberOfCards);
        shuffle(deck, numberOfCards);
        initializeBoard(deck, numberOfCards, gameState, freeCells, HomeSlots);
        displayBoard(gameState, freeCells, HomeSlots);
    }
    else if (newGameOrLoadedGame == 2)
    {
        // TODO
        LoadDeck(deck, numberOfCards, "deck.txt");
        LoadDeck(freeCells, 4, "freeCells.txt");
        LoadDeck(HomeSlots, 4, "HomeSlots.txt");
        LoadGameState(gameState, "gameState.txt");
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
        case 2: // dynamic
            columnToFreeCell(gameState, freeCells);
            displayBoard(gameState, freeCells, HomeSlots);
            break;
        case 3:
            // a free cell to column move
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
            freeCellToHomeSlot(freeCells, HomeSlots);
            displayBoard(gameState, freeCells, HomeSlots);
            break;
        case 6:
            // TO DO:---- Save the game state in a file
            SaveDeck(deck, numberOfCards, "deck.txt");
            SaveDeck(freeCells, 4, "freeCells.txt");
            SaveDeck(HomeSlots, 4, "HomeSlots.txt");
            SaveGameState(gameState, "gameState.txt");
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
    char rankArray[13] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
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
        cout << deck[i].rank << deck[i].suit << deck[i].color << ' ';
        if (i == 12 || i == 25 || i == 38 || i == 51)
        {
            cout << endl;
        }
    }
}
bool LoadDeck(Card *deck, int numberOfCards, string filename)
{
    int i = 0;
    ifstream getItems(filename);
    string rank, suit, color;
    string line;
    if (!getItems.is_open())
    {
        cout << "Item file failed to open" << endl;
        return false;
    }
    else
    {
        while (!getItems.eof())
        {
            std::getline(getItems, line);
            if (line == "")
            {
                continue;
            }
            stringstream ss(line);
            std::getline(ss, color, ',');
            deck[i].color = color[0];

            std::getline(ss, suit, ',');
            deck[i].suit = suit[0];

            std::getline(ss, rank, ',');
            deck[i].rank = rank[0];
            i++;
        }
        getItems.close();
        return true;
    }
}
bool LoadGameState(Card **gameState, string filename)
{
    int i = 0;
    ifstream getItems(filename);
    string card;
    string line;
    if (!getItems.is_open())
    {
        cout << "Item file failed to open" << endl;
        return false;
    }
    else
    {
        while (!getItems.eof())
        {
            std::getline(getItems, line);
            if (line == "")
            {
                continue;
            }
            // need to change condition. writes garbage value, segmentation faults

            for (int j = 0; j < 13; j++)
            {
                stringstream ss(line);
                std::getline(ss, card, ';');
                gameState[i][j].color = card[0];
                gameState[i][j].suit = card[1];
                gameState[i][j].rank = card[2];
            }
            i++;
        }
        getItems.close();
        return true;
    }
}

bool SaveDeck(Card *deck, int numberOfCards, string filename)
{
    // This variable for read data from file
    ofstream myfile;
    myfile.open(filename);
    // This function will check if the file open then write data from file
    if (myfile.is_open())
    {
        // These lines will write all array data to the file and make a comma separated file

        for (int i = 0; i < numberOfCards; i++)
        {
            myfile << deck[i].color << deck[i].suit << deck[i].rank << endl;
        }
        myfile << endl;
        myfile.close();
        return true;
    }
    else
    {
        // If there is error while opening file this function will return false
        return false;
    }
}
bool SaveGameState(Card **gameState, string filename)
{
    // This variable for read data from file
    ofstream myfile;
    myfile.open(filename);
    // This function will check if the file open then write data from file
    if (myfile.is_open())
    {
        // These lines will write all array data to the file and make a comma separated file

        for (int i = 0; i < 8; i++)
        {
            // need to change condition. writes garbage value, segmentation faults
            for (int j = 0; j < 13; j++)
            {
                myfile << gameState[i][j].color << gameState[i][j].suit << gameState[i][j].rank << ";";
            }
            myfile << endl;
        }
        return true;
    }
    else
    {
        // If there is error while opening file this function will return false
        return false;
    }
}

int MovesByUser()
{
    bool valid = true;
    int choice = 0;
    while (valid)
    {
        cout << "Press 1 for column to column move" << endl
             << "Press 2 for column to free cell move" << endl
             << "Press 3 for free cell to column move" << endl
             << "Press 4 to move from column to home cell" << endl
             << "Press 5 to move from free cell to home cell" << endl
             << "Press 6 to save your unfinished game" << endl;
        cin >> choice;

        if (choice >= 1 && choice <= 6)
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
    return choice;
}

int GameOptions()
{
    /*This function takes in the user's wish to play a new game or a previously saved game.

    TO DO:---- Implement error handling so user gives chooses a move only from the given options

    */
    bool valid = true;
    int choice = 0;
    while (valid)
    {

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
    return choice;
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
        while (gameState[i][j].rank != ' ')
        {
            cout << gameState[i][j].rank << gameState[i][j].suit << ' ';
            j++;
        }
        cout << endl;
    }
}

// still need to work on column to column move
void columnToColumn(Card **gameState)
{
    // masla
    //  This function implements in the user's move from column to column

    /*
    i want to do something like this:
    cout << "Enter the column number from which you want to move the card: ";
    int columnFrom;
    cin >> columnFrom;
    columnfrom--;
    int i = 0;
    while(gameState[columnFrom][i].rank != ' ')
    {
        i++;
    }
    i--;
    cout << "Enter the number of cards you want to move: "
    int << numberOfCards;
    cin >> numberOfCards;
    cout << "Enter the column number to which you want to move the card: ";
    int columnTo;
    cin >> columnTo;
    columnTo--;
    int j = 0;
    while(gameState[columnTo][j].rank != ' ')
    {
        j++;
    }
    now i want to check if the move is valid or not.
    so you run a loop from columnFrom to columnFrom - numberOfCards and check if the card is red and the next card is black or vice versa.
    You also check if the cards are successive - i.e the next card is one less than the previous card, or if the next card is a king and the previous card is an ace,
    or if the next card is a queen and the previous card is a king, or if the next card is a jack and the previous card is a queen, or if the next card is a ten and the previous card is a 9.
    etc.
    then if the card is valid, you check if card[columnFrom][i - numberOfCards] is greater than card[columnTo][i].rank. (need to check all the corner cases such as queen king etc)
    if it is, then you move the card.
    else you print an error message.
    */

    int col1, col2;
    cout << "Enter the column number from which you want to move the card: ";
    cin >> col1;
    cout << "Enter the column number to which you want to move the card: ";
    cin >> col2;
    col1--;
    col2--;
    int i = 0;
    while (gameState[col1][i].rank != ' ')
    {
        i++;
    }
    i--;
    int j = 0;
    while (gameState[col2][j].rank != ' ')
    {
        j++;
    }
    if (gameState[col2][j - 1].rank == ' ')
    {
        gameState[col2][j - 1] = gameState[col1][i];
        gameState[col1][i].rank = ' ';
        gameState[col1][i].suit = ' ';
        gameState[col1][i].color = ' ';
    }
    else if (gameState[col2][j - 1].rank != ' ')
    {
        if (gameState[col2][j - 1].color != gameState[col1][i].color)
        {
            if (gameState[col2][j - 1].rank == gameState[col1][i].rank + 1)
            {
                gameState[col2][j] = gameState[col1][i];
                gameState[col1][i].rank = ' ';
                gameState[col1][i].suit = ' ';
                gameState[col1][i].color = ' ';
            }
            else if (gameState[col2][j - 1].rank == 'K' && gameState[col1][i].rank == 'Q')
            {
                gameState[col2][j] = gameState[col1][i];
                gameState[col1][i].rank = ' ';
                gameState[col1][i].suit = ' ';
                gameState[col1][i].color = ' ';
            }
            else if (gameState[col2][j - 1].rank == 'Q' && gameState[col1][i].rank == 'J')
            {
                gameState[col2][j] = gameState[col1][i];
                gameState[col1][i].rank = ' ';
                gameState[col1][i].suit = ' ';
                gameState[col1][i].color = ' ';
            }
            else if (gameState[col2][j - 1].rank == 'J' && gameState[col1][i].rank == 'T')
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

        Card *temp = new Card[i + 1];
        // cout << "The size before transfer is: " << i+1 << endl;
        for (int k = 0; k < i; k++)
        {
            temp[k] = gameState[col][k];
        }
        delete[] gameState[col];
        gameState[col] = temp;

        gameState[col][i].rank = ' ';
        gameState[col][i].suit = ' ';
        gameState[col][i].color = ' ';

        // int x = 0;
        // while (gameState[col][x].rank != ' ')
        // {
        //     cout << "Running loop\n";
        //     x++;
        // }
        // cout << "The size after transfer is: " << x << endl;
        // ya Allah shukar it works.
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
                cout << "\nInvalid move. Please try again.\n"
                     << endl;
            }
        }
    }
}

void columnToHomeSlot(Card **gameState, Card *HomeSlots) // need to implement dynamic arrays
{
    cout << "Enter the column number from which you want to move the card: ";
    int col;
    cin >> col;
    col--;

    int i = 0;
    while (gameState[col][i].rank != ' ')
    {
        i++;
    }
    i--;

    cout << "Enter the homeslot column number to which you want to move the card: ";
    int homeSlot;
    cin >> homeSlot;
    homeSlot--;

    if (HomeSlots[homeSlot].rank == ' ')
    {
        if (gameState[col][i].rank == 'A')
        {
            HomeSlots[homeSlot].rank = gameState[col][i].rank;
            HomeSlots[homeSlot].suit = gameState[col][i].suit;
            HomeSlots[homeSlot].color = gameState[col][i].color;

            gameState[col][i].rank = ' ';
            gameState[col][i].suit = ' ';
            gameState[col][i].color = ' ';
        }
        else
        {
            cout << "\nInvalid move. Please try again." << endl;
        }
    }
    else if (i == 0)
    {
        cout << "\nInvalid move. Please try again." << endl;
    }

    if (gameState[col][i].suit == HomeSlots[homeSlot].suit)
    {
        cout << "The suits are the same" << endl;
        if (gameState[col][i].rank == '2' && HomeSlots[homeSlot].rank == 'A')
        {
            cout << "The ranks are succesive" << endl;
            HomeSlots[homeSlot].rank = gameState[col][i].rank;
            HomeSlots[homeSlot].suit = gameState[col][i].suit;
            HomeSlots[homeSlot].color = gameState[col][i].color;

            gameState[col][i].rank = ' ';
            gameState[col][i].suit = ' ';
            gameState[col][i].color = ' ';
        }
        else if (gameState[col][i].rank == HomeSlots[homeSlot].rank + char(1))
        {
            HomeSlots[homeSlot].rank = gameState[col][i].rank;
            HomeSlots[homeSlot].suit = gameState[col][i].suit;
            HomeSlots[homeSlot].color = gameState[col][i].color;

            gameState[col][i].rank = ' ';
            gameState[col][i].suit = ' ';
            gameState[col][i].color = ' ';
        }
    }
    else if (gameState[col][i].rank == 'K' && HomeSlots[homeSlot].rank == 'Q')
    {
        HomeSlots[homeSlot].rank = gameState[col][i].rank;
        HomeSlots[homeSlot].suit = gameState[col][i].suit;
        HomeSlots[homeSlot].color = gameState[col][i].color;

        gameState[col][i].rank = ' ';
        gameState[col][i].suit = ' ';
        gameState[col][i].color = ' ';
    }
    else if (gameState[col][i].rank == 'Q' && HomeSlots[homeSlot].rank == 'J')
    {
        HomeSlots[homeSlot].rank = gameState[col][i].rank;
        HomeSlots[homeSlot].suit = gameState[col][i].suit;
        HomeSlots[homeSlot].color = gameState[col][i].color;

        gameState[col][i].rank = ' ';
        gameState[col][i].suit = ' ';
        gameState[col][i].color = ' ';
    }
    else if (gameState[col][i].rank == 'J' && HomeSlots[homeSlot].rank == 'T')
    {
        HomeSlots[homeSlot].rank = gameState[col][i].rank;
        HomeSlots[homeSlot].suit = gameState[col][i].suit;
        HomeSlots[homeSlot].color = gameState[col][i].color;

        gameState[col][i].rank = ' ';
        gameState[col][i].suit = ' ';
        gameState[col][i].color = ' ';
    }
    else if (gameState[col][i].rank == 'T' && HomeSlots[homeSlot].rank == '9')
    {
        HomeSlots[homeSlot].rank = gameState[col][i].rank;
        HomeSlots[homeSlot].suit = gameState[col][i].suit;
        HomeSlots[homeSlot].color = gameState[col][i].color;

        gameState[col][i].rank = ' ';
        gameState[col][i].suit = ' ';
        gameState[col][i].color = ' ';
    }
    else
    {
        cout << "\nInvalid move. Please try again." << endl;
    }
}
void freeCellToHomeSlot(Card *freeCells, Card *HomeSlots) // need to implement dynamic arrays
{
    cout << "Enter the free cell number from which you want to move the card: ";
    int freeCell;
    cin >> freeCell;
    freeCell--;

    cout << "Enter the homeslot column number to which you want to move the card: ";
    int homeSlot;
    cin >> homeSlot;
    homeSlot--;

    if (HomeSlots[homeSlot].rank == ' ')
    {
        if (freeCells[freeCell].rank == 'A')
        {
            HomeSlots[homeSlot].rank = freeCells[freeCell].rank;
            HomeSlots[homeSlot].suit = freeCells[freeCell].suit;
            HomeSlots[homeSlot].color = freeCells[freeCell].color;

            freeCells[freeCell].rank = ' ';
            freeCells[freeCell].suit = ' ';
            freeCells[freeCell].color = ' ';
        }
        else
        {
            cout << "\nInvalid move. Please try again." << endl;
        }
    }
    else if (freeCells[freeCell].suit == HomeSlots[homeSlot].suit)
    {
        if (freeCells[freeCell].rank == '2' && HomeSlots[homeSlot].rank == 'A')
        {
            HomeSlots[homeSlot].rank = freeCells[freeCell].rank;
            HomeSlots[homeSlot].suit = freeCells[freeCell].suit;
            HomeSlots[homeSlot].color = freeCells[freeCell].color;

            freeCells[freeCell].rank = ' ';
            freeCells[freeCell].suit = ' ';
            freeCells[freeCell].color = ' ';
        }
        else if (freeCells[freeCell].rank == HomeSlots[homeSlot].rank + char(1))
        {
            HomeSlots[homeSlot].rank = freeCells[freeCell].rank;
            HomeSlots[homeSlot].suit = freeCells[freeCell].suit;
            HomeSlots[homeSlot].color = freeCells[freeCell].color;

            freeCells[freeCell].rank = ' ';
            freeCells[freeCell].suit = ' ';
            freeCells[freeCell].color = ' ';
        }
    }
    else if (freeCells[freeCell].rank == 'K' && HomeSlots[homeSlot].rank == 'Q')
    {
        HomeSlots[homeSlot].rank = freeCells[freeCell].rank;
        HomeSlots[homeSlot].suit = freeCells[freeCell].suit;
        HomeSlots[homeSlot].color = freeCells[freeCell].color;

        freeCells[freeCell].rank = ' ';
        freeCells[freeCell].suit = ' ';
        freeCells[freeCell].color = ' ';
    }
    else if (freeCells[freeCell].rank == 'Q' && HomeSlots[homeSlot].rank == 'J')
    {
        HomeSlots[homeSlot].rank = freeCells[freeCell].rank;
        HomeSlots[homeSlot].suit = freeCells[freeCell].suit;
        HomeSlots[homeSlot].color = freeCells[freeCell].color;

        freeCells[freeCell].rank = ' ';
        freeCells[freeCell].suit = ' ';
        freeCells[freeCell].color = ' ';
    }
    else if (freeCells[freeCell].rank == 'J' && HomeSlots[homeSlot].rank == 'T')
    {
        HomeSlots[homeSlot].rank = freeCells[freeCell].rank;
        HomeSlots[homeSlot].suit = freeCells[freeCell].suit;
        HomeSlots[homeSlot].color = freeCells[freeCell].color;

        freeCells[freeCell].rank = ' ';
        freeCells[freeCell].suit = ' ';
        freeCells[freeCell].color = ' ';
    }
    else if (freeCells[freeCell].rank == 'T' && HomeSlots[homeSlot].rank == '9')
    {
        HomeSlots[homeSlot].rank = freeCells[freeCell].rank;
        HomeSlots[homeSlot].suit = freeCells[freeCell].suit;
        HomeSlots[homeSlot].color = freeCells[freeCell].color;

        freeCells[freeCell].rank = ' ';
        freeCells[freeCell].suit = ' ';
        freeCells[freeCell].color = ' ';
    }
    else
    {
        cout << "\nInvalid move. Please try again." << endl;
    }
}
