#include <iostream>


using namespace std;

struct Card
{
	char color; //color should either be set to R(red) or B(black)
	char suit; //suit should be S(spades), D(diamonds), C(clubs), H(Hearts)
	char rank; //rank signifies numbers 2-10 and (A)Ace, (K)King, (Q)Queen and (J)Jack.

    /*Feel free to add any member function IF you want to*/
};

void initialiseDeck(Card* deck, int numberOfCards){
    
    /*  TO DO:------

        Initialise your deck here with by assigning Color, Suit, and Rank to each of the 52 cards.
        You also need to shuffle your deck. Use the random function.
    */

}

int MovesByUser()
{
    /*This function takes in the user's move
    
        TO DO:---- Implement error handling so user gives chooses a move only from the given options

    */
	int choice;
	cout<< "Press 1 for column to column move"<< endl;
	cout<< "Press 2 for column to free cell move"<< endl;
	cout<< "Press 3 for free cell to column move"<<endl;
	cout<< "Press 4 to move from column to home cell"<< endl;
	cout<< "Press 5 to move from free cell to home cell"<< endl;
	cout<< "Press 6 to save your unfinished game" << endl;
    cin>> choice;
    return choice;
}

int GameOptions()
{
        /*This function takes in the user's wish to play a new game or a previously saved game.
    
        TO DO:---- Implement error handling so user gives chooses a move only from the given options

        */
		int choice;
		cout<< "Press 1 to start new game"<< endl;
		cout<< "Press 2 to resume saved game"<< endl;	
		cin>> choice;
        return choice;
}

int main(){

    int numberOfCards= 52;
    Card* deck= new Card[numberOfCards]; //this array will store the deck
    Card freeCells[4]; //this array will be used to store the cards in the free cells
    Card HomeSlots[4]; //this array will be used to store the cards in the home slots.
    Card** gameState= new Card*[8]; //this is a 2-D array which will store your game's condition at any given point. There will a total of 8 columns. Use this to print display your game.

    int newGameOrLoadedGame= GameOptions();
    /*
         TO DO:----

         1. If the user wishes to play a new game, intialise the deck using the function given to you and display the a new game to the user.
         2. Else If the user wishes to resume a previously saved game, load it from a file and display it to the user.
    */


    int choice;
    do{
	    choice=MovesByUser();		
        if(choice==1)
        {
            // TO DO:---- Implement functionality to doing a column to column move
        }
        else if(choice==2)
        {
            // TO DO:---- Implement functionality to doing a column to free cell move
        }
        else if(choice==3)
        {
            // TO DO:---- Implement functionality to doing a free cell to column move
        }
        else if(choice==4)
        {
            // TO DO:---- Implement functionality to doing a column to home slot move
        }
        else if(choice==5)
        {
            // TO DO:---- Implement functionality to doing a free cell to home slot move
        }
        else if(choice==6)
        {
            // TO DO:---- Save the game state in a file
        }
        else{
            cout<< "INVALID INPUT"<< endl;
        }        
    }while(choice!=1 || choice!=2 || choice!=3 || choice!=4 || choice!=5 || choice!=6);		

   
}