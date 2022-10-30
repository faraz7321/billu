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
class Game
{
public:
    // attributes
    Card **gameState, *freeCells, *homeSlots, *deck;
    int gameStateRow, gameStateColumn, freeCellsSize, homeSlotsSize, numberOfCards;
    // util functions
    int MovesByUser();
    int GameOptions();
    void columnToColumn();
    void shuffle();
    void initialiseDeck();
    void columnToFreeCell();
    void freeCellToColumn();
    void columnToHomeSlot();
    void freeCellToHomeSlot();
    void displayBoard();
    bool LoadCard(Card *cards, int n, string filename);
    bool LoadGameState();
    bool SaveDeck(Card *cards, int n, string filename);
    bool SaveGameState();
    void initializeBoard();
    // constructor
    Game();
    Game(int n);
    // destructor
    ~Game();
};
Game::Game()
{
    homeSlotsSize = 4;
    freeCellsSize = 4;
    numberOfCards = 52;
    gameStateColumn = 8;
    gameStateRow = 7;
    deck = new Card[52];      // this array will store the deck
    freeCells[freeCellsSize]; // this array will be used to store the cards in the free cells
    homeSlots[homeSlotsSize]; // this array will be used to store the cards in the home slots.
    gameState = new Card *[gameStateColumn];

    // FIX
    for (int i = 0; i < 4; i++)
    {
        gameState[i] = new Card[gameStateColumn];
    }
    for (int i = 4; i < gameStateColumn; i++)
    {
        gameState[i] = new Card[gameStateRow];
    }
}
Game::Game(int n)
{
    homeSlotsSize = 4;
    freeCellsSize = 4;
    numberOfCards = 52;
    gameStateColumn = 8;
    gameStateRow = 7;
    deck = new Card[n];       // this array will store the deck
    freeCells[freeCellsSize]; // this array will be used to store the cards in the free cells
    homeSlots[homeSlotsSize]; // this array will be used to store the cards in the home slots.
    gameState = new Card *[gameStateColumn];
    // FIX
    for (int i = 0; i < 4; i++)
    {
        gameState[i] = new Card[gameStateColumn];
    }
    for (int i = 4; i < 8; i++)
    {
        gameState[i] = new Card[gameStateRow];
    }
}
Game::~Game()
{
    delete[] deck;
    for (int i = 0; i < 8; i++)
    {
        delete[] gameState[i];
    }
    delete[] gameState;
}
int main()
{
    int numberOfCards = 52;
    Game *gameObj = new Game{numberOfCards};
    int choice = 0;

    int newGameOrLoadedGame = gameObj->GameOptions();

    if (newGameOrLoadedGame == 1)
    {
        gameObj->initialiseDeck();
        gameObj->shuffle();
        gameObj->initializeBoard();
        gameObj->displayBoard();
    }
    else if (newGameOrLoadedGame == 2)
    {
        // TODO
        // gameObj->LoadCard("deck.txt");
        // gameObj->LoadCard("freeCells.txt");
        // gameObj->LoadCard("HomeSlots.txt");
        // gameObj->LoadGameState();
        // gameObj->displayBoard();
    }

    do
    {
        choice = gameObj->MovesByUser();
        switch (choice)
        {
        case 1:
            // TO DO:---- Implement functionality to doing a column to column move
            // meed to fix this yet...
            gameObj->columnToColumn();
            gameObj->displayBoard();
            break;
        case 2: // dynamic
            gameObj->columnToFreeCell();
            gameObj->displayBoard();
            break;
        case 3:
            // a free cell to column move
            gameObj->freeCellToColumn();
            gameObj->displayBoard();
            break;
        case 4:
            // TO DO:---- Implement functionality to doing a column to home slot move
            gameObj->columnToHomeSlot();
            gameObj->displayBoard();
            break;
        case 5:
            // TO DO:---- Implement functionality to doing a free cell to home slot movebreak;
            gameObj->freeCellToHomeSlot();
            gameObj->displayBoard();
            break;
        case 6:
            // TO DO:---- Save the game state in a file
            // gameObj->SaveDeck("deck.txt");
            // gameObj->SaveDeck("freeCells.txt");
            // gameObj->SaveDeck("HomeSlots.txt");
            // gameObj->SaveGameState();
            break;
        default:
            cout << "INVALID INPUT" << endl;
        }
    } while (choice >= 1 && choice <= 6);

    return 0;
}
void Game::shuffle()
{
    srand(time(0));
    for (int i = 0; i < numberOfCards; i++)
    {
        // Random for remaining positions.
        int r = i + (rand() % (52 - i));
        swap(deck[i], deck[r]);
    }
}
void Game::initialiseDeck()
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

bool Game::LoadCard(Card *cards, int n, string filename)
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
            if (line[0] == ' ' || line == "")
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
bool Game::LoadGameState()
{
    cout << "load game state\n";
    int i = 0;
    int j = 0;
    ifstream getItems("gameState.txt");
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
            if (line == "" || line[0] == ' ')
            {
                continue;
            }
            // need to change condition. writes garbage value, segmentation faults
            j = 0;
            while (gameState[i][j].rank != '\0')
            {
                stringstream ss(line);
                std::getline(ss, card, ';');
                gameState[i][j].color = card[0];
                gameState[i][j].suit = card[1];
                gameState[i][j].rank = card[2];
                j++;
            }
            i++;
        }
        getItems.close();
        return true;
    }
}

bool Game::SaveDeck(Card *cards, int n, string filename)
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
bool Game::SaveGameState()
{
    int j = 0;
    // This variable for read data from file
    ofstream myfile;
    myfile.open("gameState.txt");
    // This function will check if the file open then write data from file
    if (myfile.is_open())
    {
        // These lines will write all array data to the file and make a comma separated file

        for (int i = 0; i < 8; i++)
        {
            // need to change condition. writes garbage value, segmentation faults
            j = 0;
            while (gameState[i][j].rank != ' ')
            {
                myfile << gameState[i][j].color << gameState[i][j].suit << gameState[i][j].rank << ";";
                j++;
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

int Game::MovesByUser()
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

int Game::GameOptions()
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

void Game::initializeBoard()
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
        homeSlots[j].color = ' ';
        homeSlots[j].suit = ' ';
        homeSlots[j].rank = ' ';
    }
}

void Game::displayBoard()
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
        cout << homeSlots[i].rank << homeSlots[i].suit << " |";
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
void Game::columnToColumn()
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

void Game::columnToFreeCell()
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

void Game::freeCellToColumn()
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

void Game::columnToHomeSlot() // need to implement dynamic arrays
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

    if (homeSlots[homeSlot].rank == ' ')
    {
        if (gameState[col][i].rank == 'A')
        {
            homeSlots[homeSlot].rank = gameState[col][i].rank;
            homeSlots[homeSlot].suit = gameState[col][i].suit;
            homeSlots[homeSlot].color = gameState[col][i].color;

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

    if (gameState[col][i].suit == homeSlots[homeSlot].suit)
    {
        cout << "The suits are the same" << endl;
        if (gameState[col][i].rank == '2' && homeSlots[homeSlot].rank == 'A')
        {
            cout << "The ranks are succesive" << endl;
            homeSlots[homeSlot].rank = gameState[col][i].rank;
            homeSlots[homeSlot].suit = gameState[col][i].suit;
            homeSlots[homeSlot].color = gameState[col][i].color;

            gameState[col][i].rank = ' ';
            gameState[col][i].suit = ' ';
            gameState[col][i].color = ' ';
        }
        else if (gameState[col][i].rank == homeSlots[homeSlot].rank + char(1))
        {
            homeSlots[homeSlot].rank = gameState[col][i].rank;
            homeSlots[homeSlot].suit = gameState[col][i].suit;
            homeSlots[homeSlot].color = gameState[col][i].color;

            gameState[col][i].rank = ' ';
            gameState[col][i].suit = ' ';
            gameState[col][i].color = ' ';
        }
    }
    else if (gameState[col][i].rank == 'K' && homeSlots[homeSlot].rank == 'Q')
    {
        homeSlots[homeSlot].rank = gameState[col][i].rank;
        homeSlots[homeSlot].suit = gameState[col][i].suit;
        homeSlots[homeSlot].color = gameState[col][i].color;

        gameState[col][i].rank = ' ';
        gameState[col][i].suit = ' ';
        gameState[col][i].color = ' ';
    }
    else if (gameState[col][i].rank == 'Q' && homeSlots[homeSlot].rank == 'J')
    {
        homeSlots[homeSlot].rank = gameState[col][i].rank;
        homeSlots[homeSlot].suit = gameState[col][i].suit;
        homeSlots[homeSlot].color = gameState[col][i].color;

        gameState[col][i].rank = ' ';
        gameState[col][i].suit = ' ';
        gameState[col][i].color = ' ';
    }
    else if (gameState[col][i].rank == 'J' && homeSlots[homeSlot].rank == 'T')
    {
        homeSlots[homeSlot].rank = gameState[col][i].rank;
        homeSlots[homeSlot].suit = gameState[col][i].suit;
        homeSlots[homeSlot].color = gameState[col][i].color;

        gameState[col][i].rank = ' ';
        gameState[col][i].suit = ' ';
        gameState[col][i].color = ' ';
    }
    else if (gameState[col][i].rank == 'T' && homeSlots[homeSlot].rank == '9')
    {
        homeSlots[homeSlot].rank = gameState[col][i].rank;
        homeSlots[homeSlot].suit = gameState[col][i].suit;
        homeSlots[homeSlot].color = gameState[col][i].color;

        gameState[col][i].rank = ' ';
        gameState[col][i].suit = ' ';
        gameState[col][i].color = ' ';
    }
    else
    {
        cout << "\nInvalid move. Please try again." << endl;
    }
}
void freeCellToHomeSlot(Card *freeCells, Card *homeSlots) // need to implement dynamic arrays
{
    cout << "Enter the free cell number from which you want to move the card: ";
    int freeCell;
    cin >> freeCell;
    freeCell--;

    cout << "Enter the homeslot column number to which you want to move the card: ";
    int homeSlot;
    cin >> homeSlot;
    homeSlot--;

    if (homeSlots[homeSlot].rank == ' ')
    {
        if (freeCells[freeCell].rank == 'A')
        {
            homeSlots[homeSlot].rank = freeCells[freeCell].rank;
            homeSlots[homeSlot].suit = freeCells[freeCell].suit;
            homeSlots[homeSlot].color = freeCells[freeCell].color;

            freeCells[freeCell].rank = ' ';
            freeCells[freeCell].suit = ' ';
            freeCells[freeCell].color = ' ';
        }
        else
        {
            cout << "\nInvalid move. Please try again." << endl;
        }
    }
    else if (freeCells[freeCell].suit == homeSlots[homeSlot].suit)
    {
        if (freeCells[freeCell].rank == '2' && homeSlots[homeSlot].rank == 'A')
        {
            homeSlots[homeSlot].rank = freeCells[freeCell].rank;
            homeSlots[homeSlot].suit = freeCells[freeCell].suit;
            homeSlots[homeSlot].color = freeCells[freeCell].color;

            freeCells[freeCell].rank = ' ';
            freeCells[freeCell].suit = ' ';
            freeCells[freeCell].color = ' ';
        }
        else if (freeCells[freeCell].rank == homeSlots[homeSlot].rank + char(1))
        {
            homeSlots[homeSlot].rank = freeCells[freeCell].rank;
            homeSlots[homeSlot].suit = freeCells[freeCell].suit;
            homeSlots[homeSlot].color = freeCells[freeCell].color;

            freeCells[freeCell].rank = ' ';
            freeCells[freeCell].suit = ' ';
            freeCells[freeCell].color = ' ';
        }
    }
    else if (freeCells[freeCell].rank == 'K' && homeSlots[homeSlot].rank == 'Q')
    {
        homeSlots[homeSlot].rank = freeCells[freeCell].rank;
        homeSlots[homeSlot].suit = freeCells[freeCell].suit;
        homeSlots[homeSlot].color = freeCells[freeCell].color;

        freeCells[freeCell].rank = ' ';
        freeCells[freeCell].suit = ' ';
        freeCells[freeCell].color = ' ';
    }
    else if (freeCells[freeCell].rank == 'Q' && homeSlots[homeSlot].rank == 'J')
    {
        homeSlots[homeSlot].rank = freeCells[freeCell].rank;
        homeSlots[homeSlot].suit = freeCells[freeCell].suit;
        homeSlots[homeSlot].color = freeCells[freeCell].color;

        freeCells[freeCell].rank = ' ';
        freeCells[freeCell].suit = ' ';
        freeCells[freeCell].color = ' ';
    }
    else if (freeCells[freeCell].rank == 'J' && homeSlots[homeSlot].rank == 'T')
    {
        homeSlots[homeSlot].rank = freeCells[freeCell].rank;
        homeSlots[homeSlot].suit = freeCells[freeCell].suit;
        homeSlots[homeSlot].color = freeCells[freeCell].color;

        freeCells[freeCell].rank = ' ';
        freeCells[freeCell].suit = ' ';
        freeCells[freeCell].color = ' ';
    }
    else if (freeCells[freeCell].rank == 'T' && homeSlots[homeSlot].rank == '9')
    {
        homeSlots[homeSlot].rank = freeCells[freeCell].rank;
        homeSlots[homeSlot].suit = freeCells[freeCell].suit;
        homeSlots[homeSlot].color = freeCells[freeCell].color;

        freeCells[freeCell].rank = ' ';
        freeCells[freeCell].suit = ' ';
        freeCells[freeCell].color = ' ';
    }
    else
    {
        cout << "\nInvalid move. Please try again." << endl;
    }
}
