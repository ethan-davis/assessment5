/* collector.cpp - Assessment 4 - Ethan Davis
 * This file is the implementation file for
 *  the Collector class.
 */

#include "collector.h"

// Default constructor 
Collector::Collector()
{
	head = NULL;
	tail = NULL;
}

// Destructor
Collector::~Collector()
{
	Node* current = head;
	while(head != NULL)
	{
		current = head;
		head = head->next;
		delete current->data;
		delete current;
	}
}

/* Purpose: Allows user to add new entries to
 *   game collection. Validate each input with
 *   variable type specific functions.
 * Parameters: game collection, number of games
 *  in collection.
 */
void Collector::AddEntry()
{
        // Temporary variables
        char tTitle[MAX_CHAR], tPlatform[MAX_CHAR], tGenre[MAX_CHAR];
        int tYear;
        double tRating;
        char addAnother = 'y';
        // loop until they select n at the prompt
        do
        {
                // Use setter functions to assign temp
                // variables to class members
                cout << "Enter Game Title: ";
                GetStringInput(tTitle);
                cout << "Enter Platform: ";
                GetStringInput(tPlatform);
                cout << "Enter Genre: ";
                GetStringInput(tGenre);
                cout << "Enter Release Year (1970-2021): ";
                // get int input with range of 1970 to 2021
                tYear = GetIntInput(1970, 2021);
                cout << "Enter Rating (5.0 Scale): ";
                // get int input with range of 1.0 to 5.0
                tRating = GetDoubleInput(1.0, 5.0);
                cout << "\n==Entry Saved!==\n";
                // Check if user wants to continue adding to collection
                cout << "Would you like to add another (y/n)? ";
                Confirm(addAnother);
                cout << endl;
        } while(addAnother == 'y');

	Game* obj = new Game(tTitle, tPlatform, tGenre, tYear, tRating);
	AppendToLL(obj);

}

void Collector::AppendToLL(Game* obj)
{
	Node* newNode = new Node;
	newNode->data = obj;
	newNode->next = NULL;

	if(!head)
	{
		head = tail = newNode;
		return;
	}

	tail->next = newNode;
	tail = newNode;
}

/* Purpose: Displays a list of all games.
 * Parameters: Game collection, number of games
 *   in collection.
 */
void Collector::DisplayEntries()
{
        // Show message and return if collection is empty
        if(!head)
        {
                cout << "== No Games in Collection! ==\n" << endl;
                return;
        }

	Node* current = head;

        cout << "---------------------------\n";
        cout << "|    Showing All Games    |\n";
        cout << "---------------------------\n";
        while(current)
        {
		current->data->DisplayDetails();
		current = current->next;
        }
        cout << endl;
}

/* Purpose: Allows user to delete from collection.
 * Parameters: Game collection, number of games
 *   in collection.
 */
void Collector::DeleteEntry()
{
        char confirmDelete = 'n';
        // Alert user if there are no games to remove
        if(!head)
        {
                cout << "There are no games to delete!" << endl;
                return;
        }
        // Prompt user with valid range of indexes
        //cout << "Enter index to delete (0-" << count - 1 << "): ";  // FIX ME
        // Confirm game title with user before deletion
        cout << "Are you sure you want to delete ";
        cout << " (y/n)? ";
        Confirm(confirmDelete);
        if(confirmDelete == 'y')
        {
        }
}

/* Purpose: Allows user to specify a file to write game
 *  collection to.
 * Parameters: Game collection, number of games
 *   in collection.
 */
void Collector::WriteFile()
{
        char fileName[MAX_CHAR];
        ofstream outFile;
        // Prompt user for file name
        cout << "Enter a file name to create: ";
        GetStringInput(fileName);
        // Attempt to open file
        outFile.open(fileName);
        // Display error if file did not open
        if(!outFile.is_open())
        {
                cout << "Unable to open file for writing!" << endl;
                return;
        }

	Node* current = head;

        // Loop through LL and write
        // member variables to file.
        while(current)
        {
                outFile << current->data->getTitle() << endl;
                outFile << current->data->getGenre() << endl;
                outFile << current->data->getPlatform() << endl;
                outFile << current->data->getYear() << endl;
                outFile << current->data->getRating() << endl;

		current = current->next;
        }
        cout << "== Game collection saved to: " << fileName << " ==\n";
        cout << endl;
        outFile.close();
}

/* Purpose: Allows user to specify a file to load contents
 *  into game collection.
 * Parameters: Game collection, number of games
 *   in collection.
 */
void Collector::ReadFile()
{
        char fileName[MAX_CHAR];
        ifstream inFile;
        //Temporary Variables
        char sTitle[MAX_CHAR], sGenre[MAX_CHAR], sPlatform[MAX_CHAR];
        int sYear;
        double sRating;

        cout << "Enter the file name to read in: ";
        GetStringInput(fileName);
        inFile.open(fileName);
        while(!inFile.is_open())
        {
                cout << "Unable to open file! Check the file name and try again.";
                cout << endl;
                return;
        }
        // Loop while first C String Title is found
        while(inFile.getline(sTitle, MAX_CHAR-1))
        {
                // Assign contents of file to temp variables
                inFile.getline(sGenre, MAX_CHAR-1);
                inFile.getline(sPlatform, MAX_CHAR-1);
                inFile >> sYear;
                inFile.ignore(100, '\n');
                inFile >> sRating;
                inFile.ignore(100, '\n');
                // Create new object with parameterized constructor
		Game* obj = new Game(sTitle, sGenre, sPlatform, sYear, sRating);
		AppendToLL(obj);
        }
        inFile.close();
        cout << "== Games loaded from " << fileName << " into collection! == \n" << endl;
}

