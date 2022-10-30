#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>

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
void displayBoard(Card **gameState, Card *freeCells, Card *HomeSlots);

void initializeBoard(Card *deck, int numberOfCards, Card **gameState, Card *freeCells, Card *HomeSlots);
void initialiseDeck(Card *deck, int numberOfCards);
void shuffle(Card *deck, int numberOfCards);

void columnToColumn(Card **gameState, Card *freeCells);
void columnToFreeCell(Card **gameState, Card *freeCells);
void freeCellToColumn(Card **gameState, Card *freeCells);
void columnToHomeSlot(Card **gameState, Card *HomeSlots);
void freeCellToHomeSlot(Card *freeCells, Card *HomeSlots);

bool LoadCard(Card *deck, string filename);
bool LoadGameState(Card **gameState, string filename);
bool SaveCard(Card *deck, string filename);
bool SaveGameState(Card **gameState, string filename);

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

        LoadCard(freeCells, "freeCells.txt");
        LoadCard(HomeSlots, "HomeSlots.txt");
        LoadGameState(gameState, "gameState.txt");
        displayBoard(gameState, freeCells, HomeSlots);
    }

    do
    {
        choice = MovesByUser();
        switch (choice)
        {
        case 1:
            // TO DO:---- Implement functionality to doing a column to column move
            // meed to fix this yet...
            columnToColumn(gameState, freeCells);
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
            SaveCard(freeCells, "freeCells.txt");
            SaveCard(HomeSlots, "HomeSlots.txt");
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
bool LoadCard(Card *cards, string filename)
{
    int i = 0;
    //cards = new Card[4];
    ifstream getItems(filename);
    string line;
    if (!getItems.is_open())
    {
        cout << "Item file failed to open" << endl;
        return false;
    }
    else
    {
        while (!getItems.eof() && i<4)
        {
            std::getline(getItems, line);

            cards[i].color = line[0];
            cards[i].suit = line[1];
            cards[i].rank = line[2];
            i++;
        }
        getItems.close();
        //cout << "returning\n";
        return true;
    }
}
bool LoadGameState(Card **gameState, string filename)
{
     for (int i = 0; i < 8; i++)
    {
        delete[] gameState[i];
    }
    int sizearr[8];
    // cout << "into gs\n";
    int i = 0, j = 0;
    ifstream getItems(filename);
    // string card;
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
            j = 0;
            while (1)
            {
                std::getline(getItems, line);
                if (line == ";")
                {
                    break;
                }
                j++;
            }
            sizearr[i] = j;
            i++;
            if (i == 8)
            {
                break;
            }
        }
        getItems.close();

        ifstream myfile(filename);

        for (int i = 0; i < 8; i++)
        {
            gameState[i] = new Card[sizearr[i] + 1];
        }
        i = 0;
        while (!myfile.eof())
        {
            for (int j = 0; j < sizearr[i]; j++)
            {
                std::getline(myfile, line);
                if (line == ";\n")
                {
                    break;
                }

                gameState[i][j].color = line[0];
                gameState[i][j].suit = line[1];
                gameState[i][j].rank = line[2];
            }
            i++;
            if (i >= 8)
            {
                break;
            }
        }
        for (int i = 0; i < 8; i++)
        {
            gameState[i][sizearr[i]].color = ' ';
            gameState[i][sizearr[i]].suit = ' ';
            gameState[i][sizearr[i]].rank = ' ';
        }
        myfile.close();

        return true;
    }
}

bool SaveCard(Card *deck, string filename)
{
    // This variable for read data from file
    ofstream myfile;
    myfile.open(filename);
    // This function will check if the file open then write data from file
    if (myfile.is_open())
    {
        // These lines will write all array data to the file and make a comma separated file

        for (int i = 0; i < 4; i++)
        {
            myfile << deck[i].color << deck[i].suit << deck[i].rank << endl;
        }
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
    int j = 0;
    // This variable for read data from file
    ofstream myfile;
    myfile.open(filename);
    // This function will check if the file open then write data from file
    if (myfile.is_open())
    {
        // These lines will write all array data to the file and make a comma separated file
        for (int i = 0; i < 8; i++)
        {
            j = 0;
            while (gameState[i][j].color != ' ' || gameState[i][j].rank != ' ' || gameState[i][j].suit != ' ')
            {
                myfile << gameState[i][j].color << gameState[i][j].suit << gameState[i][j].rank << "\n";
                j++;
            }
            myfile << ";\n";
        }
        myfile.close();
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
             << "Press 6 to save your unfinished game" << endl
             << "Choice: ";
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
        cout << "Choice: ";
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
void columnToColumn(Card **gameState, Card *freeCells)
{
    int count = 0;
    for (int i = 0; i < 4; i++)
    {
        if (freeCells[i].rank == ' ')
        {
            count++;
        }
    }
    count++;
    // cout << "Valid number of cards you can move from column to column is: " << count <<endl;

    int col1, col2, no_cards;
    cout << "Enter the column number from which you want to move the card: ";
    cin >> col1;
    cout << "Enter the number of Cards you wish to move: ";
    cin >> no_cards;
    cout << "Enter the column number to which you want to move the card: ";
    cin >> col2;
    col1--;
    col2--;

    if (no_cards < 1 || no_cards > count)
    {
        cout << "Invalid Move. Please try again.\n"
             << endl;
    }
    else
    {
        int i = 0;
        int j = 0;
        while (gameState[col1][i].rank != ' ')
        {
            i++;
        }
        while (gameState[col2][j].rank != ' ')
        {
            j++;
        }
        i--;
        j--;

        bool valid = false;
        bool check = false;
        if (no_cards == 1)
        {
            if (gameState[col1][i].color != gameState[col2][j].color)
            {
                if (gameState[col1][i].rank + char(1) == gameState[col2][j].rank)
                {
                    valid = true;
                }
                else if (gameState[col1][i].rank == 'Q' && gameState[col2][j].rank == 'K')
                {
                    valid = true;
                }
                else if (gameState[col1][i].rank == 'J' && gameState[col2][j].rank == 'Q')
                {
                    valid = true;
                }
                else if (gameState[col1][i].rank == 'T' && gameState[col2][j].rank == 'J')
                {
                    valid = true;
                }
                else if (gameState[col1][i].rank == '9' && gameState[col2][j].rank == 'T')
                {
                    valid = true;
                }
                else
                {
                    valid = false;
                    cout << "\nInvalid move. Please try again." << endl;
                }
            }
            if (valid)
            {
                gameState[col2][j + 1].rank = gameState[col1][i].rank;
                gameState[col2][j + 1].suit = gameState[col1][i].suit;
                gameState[col2][j + 1].color = gameState[col1][i].color;

                // first lets reduce the size of col1.

                Card *temp1 = new Card[i + 1];
                // cout << "The size before transfer is: " << i+1 << endl;
                for (int k = 0; k < i; k++)
                {
                    temp1[k] = gameState[col1][k];
                }
                delete[] gameState[col1];
                gameState[col1] = temp1;

                gameState[col1][i].rank = ' ';
                gameState[col1][i].suit = ' ';
                gameState[col1][i].color = ' ';

                // now lets increase the size of col2

                Card *temp2 = new Card[j + 3];
                for (int k = 0; k < j + 2; k++)
                {
                    temp2[k] = gameState[col2][k];
                }
                delete[] gameState[col2];
                temp2[j + 2].rank = ' ';
                temp2[j + 2].color = ' ';
                temp2[j + 2].suit = ' ';
                gameState[col2] = temp2;
            }
        }
        else if (no_cards == 2)
        {
            if (gameState[col1][i].color != gameState[col1][i - 1].color)
            {
                if (gameState[col1][i].rank + char(1) == gameState[col1][i - 1].rank)
                {
                    check = true;
                }
                else if (gameState[col1][i].rank == 'Q' && gameState[col1][i - 1].rank == 'K')
                {
                    check = true;
                }
                else if (gameState[col1][i].rank == 'J' && gameState[col1][i - 1].rank == 'Q')
                {
                    check = true;
                }
                else if (gameState[col1][i].rank == 'T' && gameState[col1][i - 1].rank == 'J')
                {
                    check = true;
                }
                else if (gameState[col1][i].rank == '9' && gameState[col1][i - 1].rank == 'T')
                {
                    check = true;
                }
                else
                {
                    check = false;
                    cout << "The two cards are not successive/alternating colors. Invalid move. Try again.\n"
                         << endl;
                }
                // see if the two cards are successive and alternating, then check if the upper of the
                // two cards go with the last card of col2
                if (check)
                {
                    if (gameState[col1][i - 1].color != gameState[col2][j].color)
                    {
                        if (gameState[col1][i - 1].rank + char(1) == gameState[col2][j].rank)
                        {
                            valid = true;
                        }
                        else if (gameState[col1][i - 1].rank == 'Q' && gameState[col2][j].rank == 'K')
                        {
                            valid = true;
                        }
                        else if (gameState[col1][i - 1].rank == 'J' && gameState[col2][j].rank == 'Q')
                        {
                            valid = true;
                        }
                        else if (gameState[col1][i - 1].rank == 'T' && gameState[col2][j].rank == 'J')
                        {
                            valid = true;
                        }
                        else if (gameState[col1][i - 1].rank == '9' && gameState[col2][j].rank == 'T')
                        {
                            valid = true;
                        }
                        else
                        {
                            valid = false;
                            cout << "\nInvalid move. Please try again." << endl;
                        }
                    }
                    else
                    {
                        cout << "Invalid Move! Try again.\n"
                             << endl;
                    }
                    if (valid)
                    {
                        // increase size of the receiving array and copying the last two elements in it(col2)
                        Card *tempp = new Card[j + 4];
                        for (int k = 0; k < j + 1; k++)
                        {
                            tempp[k] = gameState[col2][k];
                        }
                        delete[] gameState[col2];
                        tempp[j + 1].color = gameState[col1][i - 1].color;
                        tempp[j + 1].suit = gameState[col1][i - 1].suit;
                        tempp[j + 1].rank = gameState[col1][i - 1].rank;

                        tempp[j + 2].color = gameState[col1][i].color;
                        tempp[j + 2].suit = gameState[col1][i].suit;
                        tempp[j + 2].rank = gameState[col1][i].rank;

                        tempp[j + 3].rank = ' ';
                        tempp[j + 3].suit = ' ';
                        tempp[j + 3].color = ' ';

                        gameState[col2] = tempp;

                        // decrease the size of the sending array and deleting elements.
                        Card *temppp = new Card[i];
                        for (int k = 0; k < i - 1; k++)
                        {
                            temppp[k] = gameState[col1][k];
                        }
                        delete[] gameState[col1];
                        temppp[i - 1].rank = ' ';
                        temppp[i - 1].suit = ' ';
                        temppp[i - 1].color = ' ';

                        gameState[col1] = temppp;
                    }
                }
            }
        }
        else if (no_cards == 3)
        {
        }
    }
}

// the following are all good
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
        freeCells[j].rank = gameState[col][i].rank;
        freeCells[j].color = gameState[col][i].color;
        freeCells[j].suit = gameState[col][i].suit;

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
    bool valid = false;
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
                    valid = true;
                }
                else if (freeCells[freeCell].rank == 'Q' && gameState[col][i].rank == 'K')
                {
                    valid = true;
                }
                else if (freeCells[freeCell].rank == 'J' && gameState[col][i].rank == 'Q')
                {
                    valid = true;
                }
                else if (freeCells[freeCell].rank == 'T' && gameState[col][i].rank == 'J')
                {
                    valid = true;
                }
                else
                {
                    valid = false;
                    cout << "\nInvalid move. Please try again." << endl;
                }
                if (valid)
                {
                    gameState[col][i + 1].rank = freeCells[freeCell].rank;
                    gameState[col][i + 1].suit = freeCells[freeCell].suit;
                    gameState[col][i + 1].color = freeCells[freeCell].color;

                    freeCells[freeCell].rank = ' ';
                    freeCells[freeCell].suit = ' ';
                    freeCells[freeCell].color = ' ';

                    Card *temparr = new Card[i + 3];
                    for (int k = 0; k < i + 2; k++)
                    {
                        temparr[k] = gameState[col][k];
                    }
                    delete[] gameState[col];
                    temparr[i + 2].rank = ' ';
                    temparr[i + 2].color = ' ';
                    temparr[i + 2].suit = ' ';
                    gameState[col] = temparr;

                    // int w = 0;
                    // while (gameState[col][w].rank != ' ')
                    // {
                    //     w++;
                    // }
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
    cout << "Enter the column number from which you want to move the card: ";
    int col;
    cin >> col;
    col--;
    bool valid = false;

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
            valid = true;
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
        // cout << "The suits are the same" << endl;
        if (gameState[col][i].rank == '2' && HomeSlots[homeSlot].rank == 'A')
        {
            // cout << "The ranks are succesive" << endl;
            valid = true;
        }
        else if (gameState[col][i].rank == HomeSlots[homeSlot].rank + char(1))
        {
            valid = true;
        }

        else if (gameState[col][i].rank == 'K' && HomeSlots[homeSlot].rank == 'Q')
        {
            valid = true;
        }
        else if (gameState[col][i].rank == 'Q' && HomeSlots[homeSlot].rank == 'J')
        {
            valid = true;
        }
        else if (gameState[col][i].rank == 'J' && HomeSlots[homeSlot].rank == 'T')
        {
            valid = true;
        }
        else if (gameState[col][i].rank == 'T' && HomeSlots[homeSlot].rank == '9')
        {
            valid = true;
        }
        else
        {
            valid = false;
            cout << "\nInvalid move. Please try again." << endl;
        }
    }
    if (valid)
    {
        HomeSlots[homeSlot].rank = gameState[col][i].rank;
        HomeSlots[homeSlot].suit = gameState[col][i].suit;
        HomeSlots[homeSlot].color = gameState[col][i].color;

        Card *tempfree = new Card[i + 1];
        cout << "The size before the transfer is: " << i + 1 << endl;
        for (int k = 0; k < i; k++)
        {
            tempfree[k] = gameState[col][k];
        }
        delete[] gameState[col];
        gameState[col] = tempfree;

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
    }
}
void freeCellToHomeSlot(Card *freeCells, Card *HomeSlots)
{
    cout << "Enter the free cell number from which you want to move the card: ";
    int freeCell;
    cin >> freeCell;
    freeCell--;

    cout << "Enter the homeslot column number to which you want to move the card: ";
    int homeSlot;
    cin >> homeSlot;
    homeSlot--;
    bool valid = false;

    if (HomeSlots[homeSlot].rank == ' ')
    {
        if (freeCells[freeCell].rank == 'A')
        {
            valid = true;
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
            valid = true;
        }
        else if (freeCells[freeCell].rank == HomeSlots[homeSlot].rank + char(1))
        {
            valid = true;
        }
    }
    else if (freeCells[freeCell].rank == 'K' && HomeSlots[homeSlot].rank == 'Q')
    {
        valid = true;
    }
    else if (freeCells[freeCell].rank == 'Q' && HomeSlots[homeSlot].rank == 'J')
    {
        valid = true;
    }
    else if (freeCells[freeCell].rank == 'J' && HomeSlots[homeSlot].rank == 'T')
    {
        valid = true;
    }
    else if (freeCells[freeCell].rank == 'T' && HomeSlots[homeSlot].rank == '9')
    {
        valid = true;
    }
    else
    {
        valid = false;
        cout << "\nInvalid move. Please try again." << endl;
    }
    if (valid)
    {
        HomeSlots[homeSlot].rank = freeCells[freeCell].rank;
        HomeSlots[homeSlot].suit = freeCells[freeCell].suit;
        HomeSlots[homeSlot].color = freeCells[freeCell].color;

        freeCells[freeCell].rank = ' ';
        freeCells[freeCell].suit = ' ';
        freeCells[freeCell].color = ' ';
    }
}
