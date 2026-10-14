#include <iostream>
#include <cstring>
#include <vector>
#include <cstdlib>
using namespace std;


class Object
{
private:
	int Status;
	int Value;
	int Rarity;
public:
	int row;
	int col;
	string Name;

	Object()
	{
		Status = -1;
		Value = 0;
		Rarity = -1;
		Name = "Null Object";
		row = -1;
		col = -1;
	}

	Object(int s, int v, int r, string n)
	{
		if (s < -1)
			Status = -1;
		else if (s > 1)
			Status = 1;
		else
			Status = s;
		
		if (v < 0)
			Value = 0;
		else if (r < 0)
			Value = v;
		else
			Value = v * (r + 1);
		
		if (r < -1)
			Rarity = -1;
		else if (Status == -1)
			Rarity = 0;
		else if (Rarity > 5)
			Rarity = 5;
		else
			Rarity = r;

		Name = n;

		row = -1;
		col = -1;
	}

	Object(int s, int v, int r, string n, int c, int w)
	{
		if (s < -1)
			Status = -1;
		else if (s > 1)
			Status = 1;
		else
			Status = s;

		if (v < 0)
			Value = 0;
		else if (r < 0)
			Value = v;
		else
			Value = v * (r + 1);

		if (r < -1)
			Rarity = -1;
		else if (Status == -1)
			Rarity = 0;
		else if (Rarity > 5)
			Rarity = 5;
		else
			Rarity = r;

		Name = n;

		col = c;
		row = w;
	}

	int getStat()
	{
		return Status;
	}

	int getVal()
	{
		return Value;
	}

	string getRar()
	{
		if (Rarity == -1)
			return "(Object Reference)";
		else if (Rarity == 0)
			return "Mundane";
		else if (Rarity == 1)
			return "Common";
		else if (Rarity == 2)
			return "Uncommon";
		else if (Rarity == 3)
			return "Rare";
		else if (Rarity == 4)
			return "Very Rare";
		else if (Rarity == 5)
			return "Ultra Rare";
	}

	string getName()
	{
		return Name;
	}

	/* IMPORTANT.
	* By Default, these values are not to be changed once made, aside from
	* row/col/Rarity, as those are to be used only when an object is found, set
	* only then. If upgrades are to be implemented later for the Submarine,
	* then this class would need to interact with the other class's functions
	* at that point.
	*/

	//Write here if more methods are to be created.

};

class Location
{
public:
	int y;
	int x;

	Location()
	{
		y = 0;
		x = 0;
	}

	Location(int row, int col)
	{
		y = row;
		x = col;
	}

	int getRow()
	{
		return y;
	}

	int getCol()
	{
		return x;
	}
};

class Gameboard
{
private:
	bool endGame = false;
	string endConf;
public:
	int Dives;
	int Funds;
	int Air;
	Object Items[4]; //modified only when used
	vector<vector<char>> Board;
	Object objects[10];
	Location Locations[10];
	Object Temp[5]; //modified only when used
	char prevTile;
	int prevX;
	int prevY;
	int subY;
	int subX;
	string mov;
	string null;

	Gameboard(size_t rows = 30, size_t cols = 15, char placeholder = '.')
		: Board(rows, std::vector<char>(cols, placeholder))
	{
		Funds = 0;
		Air = 200;
		prevTile = '~';
		subY = 2;
		subX = 7;

		//Setting the Board's Initial Tiles
		Board[0] = {'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X'};
		Board[1] = {'X', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'X'};
		Board[2] = {'X', '~', '~', '~', '~', '~', '~', '@', '~', '~', '~', '~', '~', '~', 'X'};
		Board[3] = {'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X'};
		Board[4] = {'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X'};
		Board[5] = {'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X'};
		Board[6] = {'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', 'X'};
		Board[7] = {'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', 'X'};
		Board[8] = {'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', 'X'};
		Board[9] = {'X', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', 'X'};
		Board[10] ={'X', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', 'X'};
		Board[11] ={'X', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', 'X'};
		Board[12] ={'X', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', 'X'};
		Board[13] ={'X', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', 'X'};
		Board[14] ={'X', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', 'X'};
		Board[15] ={'X', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', 'X'};
		Board[16] ={'X', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X'};
		Board[17] ={'X', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '*', ' ', 'X'};
		Board[18] ={'X', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', 'X'};
		Board[19] ={'X', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', 'X'};
		Board[20] ={'X', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', 'X'};
		Board[21] ={'X', '#', '0', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', 'X'};
		Board[22] ={'X', 'O', 'O', '#', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X'};
		Board[23] ={'X', ' ', ' ', '#', '#', '#', ' ', ' ', '#', '#', '#', ' ', ' ', ' ', 'X'};
		Board[24] ={'X', ' ', ' ', '#', '#', ' ', ' ', '#', '#', '#', '#', ' ', ' ', ' ', 'X'};
		Board[25] ={'X', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', ' ', '*', 'X'};
		Board[26] ={'X', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', 'X'};
		Board[27] ={'X', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', 'X'};
		Board[28] ={'X', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', '#', '#', 'X'};
		Board[29] ={'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'};

		//Set the Object List to pull from when generating Objects
		objects[0] = Object(0, 10, -1, "Gold Coin");
		objects[1] = Object(-1, 5, -1, "Knitted Doll");
		objects[2] = Object(0, 35, -1, "Cobalt Bar");
		objects[3] = Object(0, 24, -1, "Steel Sword");
		objects[4] = Object(-1, 4, -1, "Game Console");
		objects[5] = Object(0, 76, -1, "Shining Gemstone");
		objects[6] = Object(0, 46, -1, "Glowing Scales");
		objects[7] = Object(0, 18, -1, "Metal Pipe");
		objects[8] = Object(-1, 0, -1, "Skeleton");
		objects[9] = Object(0, 97, -1, "Pirate's Treasure Chest");

		/*Randomly determine Object locations after the first dive, and also
		* randomize the number of Objects with a minimum of 1, maximum of 5.
		* This will be handled by the check that triggers when reaching the Surface.
		* This check in and of itself compares if the last tile you were on was a
		* Surface Tile or not, which is updated only with the Move action.
		*/

		Locations[0] = Location(8, 12);
		Locations[1] = Location(12, 2);
		Locations[2] = Location(17, 12);
		Locations[3] = Location(19, 3);
		Locations[4] = Location(19, 9);
		Locations[5] = Location(22, 4);
		Locations[6] = Location(22, 9);
		Locations[7] = Location(25, 6);
		Locations[8] = Location(25, 13);
		Locations[9] = Location(28, 2);
	}

	int getX()
	{
		return subX;
	}

	int getY()
	{
		return subY;
	}

	char getTile(int x, int y)
	{
		return Board[y][x];
	}

	void Inspect()
	{
		string choice;
		bool found = false;
		
		for (int y = getY() - 1; y <= (getY() + 1); y++)
		{
			for (int x = getX() - 1; x <= (getX() + 1); x++)
			{
				
				if ((Board[y][x] == '*') || ((Board[y][x] == Board[subY][subX]) && (prevTile == '*')))
				{
					cout << "Item Located!" << endl;
					int rando = (rand() % 10);
					int rar = (rand() % 51);
					int Trar;
					if (rar <= 4)
						Trar = 0;
					else if (rar <= 19)
						Trar = 1;
					else if (rar <= 34)
						Trar = 2;
					else if (rar <= 44)
						Trar = 3;
					else if (rar <= 49)
						Trar = 4;
					else if (rar == 50)
						Trar = 5;
					
					cout << "Discerning Item..." << endl;

					for (int i = 0; i < 5; i++)
					{
						if (Temp[i].row == y)
						{
							if (Temp[i].col == x)
							{
								cout << "Documented Item Located!" << endl;
								found = true;
							}
						}
						else if (Temp[i].getName() == "Null Object")
						{
							cout << "New Item Located!" << endl;
							Temp[i] = Object(objects[rando].getStat(), objects[rando].getVal(), Trar, objects[rando].getName(), x, y);
							found = true;
						}
						else
							cout << "Check Fail." << endl;

						if (found == true)
						{
							cout << "Item Found: " << Temp[i].getName() << endl;
							cout << "Item Rarity: " << Temp[i].getRar() << endl;
							cout << "Item Value: $" << Temp[i].getVal() << endl;
							//Later when "Status" has a use, add a line for the Useability type.

							cout << "Would you like to Collect this item? [Y/N]" << endl;
							cout << "(Type only the letter for your choice)" << endl;
							bool condition;
							cin >> choice;
							if ((choice != "N") && (choice != "Y"))
								condition = false;
							else
								condition = true;
							while (condition == false)
							{
								cout << "|ERROR - Improper Prompt Response Format. Please use the requested Format for Response.|" << endl;
								cin >> choice;
								if ((choice != "N") && (choice != "Y"))
									condition = false;
								else
									condition = true;
							}
							if (choice == "Y")
							{
								if (Items[3].getName() != "Null Object")
									cout << "Unable to Collect, Held Items at Capacity." << endl;
								else
									for (int s = 0; s < 4; s++)
										if (Items[s].getName() == "Null Object")
										{
											Items[s] = Temp[i];
											Temp[i] = Object();
											if (prevTile == '*')
												prevTile = ' ';
											else
												Board[y][x] = ' ';
											cout << "Item Collected!" << endl;
											s = 4;
										}
								cout << "Enter any input to continue" << endl;
								cin >> null;
								return;
							}
							else if (choice == "N")
							{
								cout << "Item Documented." << endl;
								cout << "Enter any input to continue" << endl;
								cin >> null;
								return;
								//Can possibly incorporate a way to view the Temp List to recall where discovered Items are.
								//This can also allow for an implementation where items 'may' be lost when resurfacing, instead of always.
							}
						}
					}
				}
			}
		}

		if (found == false)
			cout << "No Items Found." << endl;
	}

	void Move()
	{
		//Test to ensure Format, Move the Sub Tile, and Correct Previous Tile.
		bool surf = false;

		bool condition;
		bool block = true;
		cout << "Which direction would you like to move? (Enter W/A/S/D for the directional input)" << endl;
		cin >> mov;
		
		if (prevTile == '~')
		{
			if ((Board[subY][subX + 1] == '~') || (Board[subY][subX - 1] == '~'))
			{
				Air = 201;
				surf = true;
			}
		}

		while (block == true)
		{
			if ((mov == "W") || (mov == "A") || (mov == "S") || (mov == "D"))
				condition = true;
			else
				condition = false;
			while (condition == false)
			{
				cout << "|ERROR - Improper Prompt Response Format. Please use the requested Format for Response.|" << endl;
				cin >> mov;
				if ((mov == "W") || (mov == "A") || (mov == "S") || (mov == "D"))
					condition = true;
			}

			if (mov == "W")
			{
				if ((Board[getY() - 1][getX()] == 'X') || (Board[getY() - 1][getX()] == '#') || (Board[getY() - 1][getX()] == '0'))
				{
					cout << "Cannot move in that direction, please select a different direction." << endl;
					cin >> mov;
				}
				else
				{
					Board[getY()][getX()] = prevTile;
					prevTile = getTile(getX(), getY() - 1);
					Board[getY() - 1][getX()] = '@';
					subY = getY() - 1;
					prevX = getX();
					prevY = getY();
					block = false;
				}
			}
			else if (mov == "A")
			{
				if ((Board[getY()][getX() - 1] == 'X') || (Board[getY()][getX() - 1] == '#') || (Board[getY()][getX() - 1] == '0'))
				{
					cout << "Cannot move in that direction, please select a different direction." << endl;
					cin >> mov;
				}
				else
				{
					Board[getY()][getX()] = prevTile;
					prevTile = getTile(getX() - 1, getY());
					Board[getY()][getX() - 1] = '@';
					subX = getX() - 1;
					prevX = getX();
					prevY = getY();
					block = false;
				}
			}
			else if (mov == "S")
			{
				if ((Board[getY() + 1][getX()] == 'X') || (Board[getY() + 1][getX()] == '#') || (Board[getY() + 1][getX()] == '0'))
				{
					cout << "Cannot move in that direction, please select a different direction." << endl;
					cin >> mov;
				}
				else
				{
					Board[getY()][getX()] = prevTile;
					prevTile = getTile(getX(), getY() + 1);
					Board[getY() + 1][getX()] = '@';
					subY = getY() + 1;
					prevX = getX();
					prevY = getY();
					block = false;
				}
			}
			else if (mov == "D")
			{
				if ((Board[getY()][getX() + 1] == 'X') || (Board[getY()][getX() + 1] == '#') || (Board[getY()][getX() + 1] == '0'))
				{
					cout << "Cannot move in that direction, please select a different direction." << endl;
					cin >> mov;
				}
				else
				{
					Board[getY()][getX()] = prevTile;
					prevTile = getTile(getX() + 1, getY());
					Board[getY()][getX() + 1] = '@';
					subX = getX() + 1;
					prevX = getX();
					prevY = getY();
					block = false;
				}
			}
		}

		//Clear the output window, and Print out the updated frame of the map
		cout << "\033[2J\033[1;1H";
		cout << "Printing Game Window..." << endl;
		int x = 0;
		int y = 0;
		if (getX() < 2)
			x = 2;
		else if (getX() > 12)
			x = 13;
		else
			x = getX();

		if (getY() < 2)
			y = 2;
		else if (getY() > 27)
			y = 27;
		else
			y = getY();

		int modx = -2;
		int mody = -2;
		while (mody < 3)
		{
			while (modx < 3)
			{
				cout << Board[y + mody][x + modx];
				modx++;
			}
			modx = -2;
			mody++;
			cout << "\n";
		}
		cout << "\n";

		//Reduce appropriate Air value
		int reduce = 1;
		reduce *= static_cast<int>((subY - 2) / 10 + 1);
		for (int I = 0; I < 4; I++)
			if (Items[I].getName() != "Null Object")
				reduce++;
		Air -= reduce;
		cout << "Air Remaining: " << Air << "/200." << endl;

		//Apply Tile Actions
		if (prevTile == 'O')
		{
			cout << "Reached Air Pocket." << endl;
			Air = 201;
			cout << "Air Refilled." << endl;
			cout << "Enter any input to continue" << endl;
			cin >> null;
		}
		
		if (prevTile == '~')
		{
			if (surf == false)
			{
				int fund = 0;
				cout << "Reached Surface Tile." << endl;
				cout << "Air Refilled." << endl;
				Air = 201;
				cout << "Cashing Treasure Found..." << endl;
				cout << "Previous Funds Total - $" << Funds << endl;
				for (int I = 0; I < 4; I++)
				{
					if (Items[I].getName() != "Null Object")
					{
						fund += Items[I].getVal();
						cout << "Item: " << Items[I].getName() << " (" << Items[I].getRar() << ")" << endl;
						cout << "Value: " << Items[I].getVal() << endl;
						Items[I] = Object();
					}
				}
				for (int I = 0; I < 5; I++)
					Temp[I] = Object();
				cout << "New Funds Scavenged on Dive - $" << fund << endl;
				Funds += fund;
				cout << "Current Funds Total - $" << Funds << endl;
				Dives++;
				cout << "Total Dives Completed: " << Dives << endl;

				cout << "Would you like to conclude your Dives? (Y/N)" << endl;
				cin >> endConf;

				if (endConf == "N")
				{
					//clear old treasure locations
					for (int e = 0; e < 10; e++)
						Board[Locations[e].y][Locations[e].x] = ' ';

					//set new treasure locations
					int treasures = rand() % 5 + 1;
					while (treasures > 0)
					{
						int place = rand() % 10;
						Board[Locations[place].y][Locations[place].x] = '*';
						treasures--;
					}

					cout << "(New Treasure Wave Created)" << endl;
				}
				cout << "Enter any input to continue" << endl;
				cin >> null;
			}
		}
	}

	void End()
	{
		cout << "\033[2J\033[1;1H";
		cout << "G A M E   E N D" << endl;
		if (Air <= 0)
		{
			cout << "Reason - Air Depleted (GAME OVER)\n" << endl;
			cout << "Total Dives Completed: " << Dives << endl;
			cout << "Total Funds Recovered: $" << (Funds / 2) << endl;
			cout << "(Score Reduced to Lose outcome)" << endl;
		}
		else if (endConf == "Y")
		{
			cout << "Reason - Expedition Ended (GAME WIN)\n" << endl;
			cout << "Total Dives Completed: " << Dives << endl;
			cout << "Total Funds Recovered: $" << Funds << endl;
			cout << "\n";
		}
		else
		{
			cout << "Reason - Manual Trigger (GAME CLOSE)\n" << endl;
			cout << "Total Dives Completed: " << Dives << endl;
			cout << "Total Funds Recovered: $" << Funds << endl;
			cout << "\n";
		}

		cout << "Thank you for Playing." << endl;
		cout << "Made By: Jason R. Oker (Joker)" << endl;
		return; //ends the entire program.
	}

	void Play()
	{
		//Conditions to End Game, called at end instead of Play() if met.
		if ((Air <= 0) || (endConf == "Y"))
			endGame = true;
		
		//Recursive chain to manage Play
		if (endGame == false)
		{
			string Action;
			bool check = false;
			cout << "What would you like to do?" << endl;
			cout << "Enter one of the Following Actions:\nMove\nInspect" << endl;
			cin >> Action;

			while (check == false)
			{
				if (Action == "End")
				{
					check = true;
					endGame = true;
				}
				else if ((Action != "Move") && (Action != "Inspect"))
				{
					cout << "|ERROR - Improper Prompt Response Format. Please use the requested Format for Response.|" << endl;
					cin >> Action;
				}
				else
					check = true;
			}

			if (Action == "Move")
				Move();
			else if (Action == "Inspect")
				Inspect();

			Play();
		}
		else if (endGame == true)
			End();
	}
};

/* OUTLINE:
* Make a Class for the Objects, which holds variables indicating Value, Rarity,
* and Status. Value is an Int that represents the value, Rarity is an Int that
* represents the cosmetic chance of finding the item and determines higher Value,
* and Status is an Int that states the use case for the Object with each number
* representing a different status (-1 = Useless, 0 = Treasure, 1 = Useable)
*   Note for Rarity: Each Int represents a Rarity, ranging from Common to Ultra
*   Rare, and in numeric form as 0 to 4 (this amount may change later to include
*   extra and/or unique rarities)
* 
* [Status is largely going to play a bigger role later on in a future update when]
* [the game is to be expanded upon. This can range from Status 1 items having]
* [proper effects, such as Stat increases to the Submarine, or Utility features]
* [such as destroying walls to open up the map.]
* 
* DONE FOR PORTFOLIO ENTRY 1.
* ----------------------------------------------------------------------------------
* 
* Make another class called Gameboard. This class will contain the main variables
* to keep track of while playing the game. This includes Funds, Air, Item Spaces,
* a vector to track the items currently held (Vector so it can change size later),
* and a 2d Array of Char's to Store the Game Board and it's tiles. It is important
* to track a lot of things as the amounts will impact other variable changes, such
* as having more loot (or Upgrades in futire possibly?) requiring more oxygen to move.
* When the game is over, an End method is called, which displays the results. The
* Results displays the total Funds earned, total Dives, and followed by the Main Menu.
* 
* DONE SO FAR IN PORTFOLIO ENTRY 1: Board Start, objects, and all other variable initializations.
* ----------------------------------------------------------------------------------
* 
* Gameboard will have many functions, though "Play" will be the recursive function
* to dictate Actions. Based on inputs and a series of checks, it will call one of
* many Actions (Move, Inspect, Use, etc.), and will need to be entered exactly, or 
* else it replies with an error message. Not all of the planned Actions will be
* Created now, just Move and inspect - Add new ones to the list when planned out.
* 
* Different Tile Icons represent different things as follows:
* @ - Player
* * - Object
* # - Terrain
* X - Map Edge
* ~ - Surface
* O - Air Pocket
* TBD...
* 
* Here is how each Action Function will work:
* 
*     -Inspect-
* Inspect will check all neighboring tiles to see if there is an Object (*) there.
* If there is, you will learn the details of the Object (Type/Name, Val, Rar, Stat),
* followed by if you would like to pick it up or not. If you have a full Item Storage,
* you will get a message saying that your Storage is full and you cannot pick the item
* up.
* Collecting will end the Inspect Function, requiring it to be called again in the
* event of multiple items being nearby. If you skip an item and don't collect it, inspect
* will continue it's search until all nearby tiles have been scanned for items.
* Once Inspect (or Collect subsequently) is done, it will say as such, end the Action 
* and call Play() again.
* 
* "Inspect" ACTION COMPLETE WITH VARIABLE MODIFICATIONS, ASIDE FROM RECURSIVE CALL TO "Play()".
* INCORPORATE THIS RECURSIVE CALL WITHIN THE "Play()" METHOD ITSELF.
* ----------------------------------------------------------------------------------
* 
*     -Move-
* Move will prompt the user for a directional input (W/A/S/D), and move the submarine
* one space that direction at the cost of some oxygen. Oxygen loss is increased based
* off of depth every 5 tiles, and for each Item held in your Item Storage. After the
* move, the function will check where the Sub is, and if it correlates to a needed
* change, such as reaching the surface, or if oxygen is less than 1 (in that order).
* 
* Air Tile - When reaching an Air tile, the Submarine's air is refilled.
* 
* Surface tile - The Surface Tile is an Air Tile with the added benefit of allowing
* the player to sell their Items for Funds, and refreshing the Treasure Locations.
* 
* Randomly determine Objects by name in a preset list of Objects, and randomly
* determining their rarity - These objects will have preset Statuses and Values
* already, so use a 1-50 random number generator to determine Rarity. The Preset
* List of Objects will be an Array of Objects to hold the defaults, and when making
* the Object into the map, pull a random name and it's default, then generate the
* rarity, then make the Object and save it as a Temp Object to a Vector - when the
* Object is picked up, add it to the Items list and remove it from the Temp List.
* 
* When you reach a Surface tile, reset the Object tiles, wipe the Temp List, and
* re-generate Treasure tiles. Objects are generated when reaching the Treasure Tile
* and stored in the Temp List either until picked up, or you reach a Surface Tile.
* 
* If the game is not over, Once all changes are done, the function will print out the
* current view of the nearby map on the Gameboard, and call Play(). If the game is
* determined to be over, it will instead end the game, calling the "End()" Function
* 
* CODE COMPILES AND RUNS SUCCESSFULLY. ALL THAT REMAINS IS TO TEST IF IT WORKS CORRECTLY
* ----------------------------------------------------------------------------------
* Known Issues:
* When Inspecting for Items, defaults to "Documented Item" then reads void constructor values.
* Line 300 Reference Point.
* 
*/

int main()
{
	srand(time(0));

	string start;

	/* OUTLINE:
	* The "Main" function dictates the game interface. It handles starting it, a
	* While loop to handle the Main Menu display, as well as the condition to end
	* the game, simply returning when the game is ended.
	*/

	cout << "Loading Game Options..." << endl;
	Gameboard b = Gameboard();
	cout << "Loading Complete." << endl;

	cout << "Welcome to Submarine Adventure." << endl;
	cout << "Dive to find treasure, and return to the surface to cash it in. Aim for" << endl;
	cout << "the highest score you can, but be careful to not deplete your air tank.\n" << endl;
	cout << "Type 'Play' to begin, or anything else to close the game." << endl;
	cout << "While running, type 'End' as your Action to close the game (for testing purposes)." << endl;
	cin >> start;

	if (start == "Play")
	{
		cout << "\033[2J\033[1;1H";
		cout << "Rendering Game..." << endl;
		cout << "Printing Game Window..." << endl;
		int x = 0;
		int y = 0;
		if (b.getX() < 2)
			x = 2;
		else if (b.getX() > 12)
			x = 13;
		else
			x = b.getX();

		if (b.getY() < 2)
			y = 2;
		else if (b.getY() > 27)
			y = 27;
		else
			y = b.getY();

		int modx = -2;
		int mody = -2;
		while (mody < 3)
		{
			while (modx < 3)
			{
				cout << b.Board[y + mody][x + modx];
				modx++;
			}
			modx = -2;
			mody++;
			cout << "\n";
		}
		cout << "\n";
		cout << "Air Remaining: " << b.Air << "/200." << endl;
		
		b.Play();
	}
}