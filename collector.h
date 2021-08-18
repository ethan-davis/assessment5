#pragma once
#include "main.h"
#include "game.h"

/*  Struct:  Node data for LLL
    Members:
    *   variables:
    *      Game: Game class object: data for game entry
    *	   next: pointer to next node in list
    *   functions: None
    */
struct Node
{
	Game* data;
	Node* next;
};

/*  Class:  Information for list collector
    Members:
    *   variables:
    *      aGame: object array: collection of games
    *   functions:
    *      Collector(): default constructor
    *      AddEntry(): Add game to collection
    *      DisplayEntries(): Prints all games
    *      DeleteEntry(): Remove game from list
    *      WriteFile(): Writes all games to file
    *      ReadFile(): Adds games from file to collection
    */
class Collector
{
        public:
                // Constructors
                Collector();
		~Collector();
		
		void AddEntry();
		void DisplayEntries();
		void DisplayDetails();
		void DeleteEntry();
		void WriteFile();
		void ReadFile();

        private:
		Node* head;
		Node* tail;

		void CreateNode(Game* obj);
};
