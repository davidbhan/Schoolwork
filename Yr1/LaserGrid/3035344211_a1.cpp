#include <iostream>
using namespace std;
//Structure for Items in the array and laser structure to be made from a source item
struct Item {
	string type;
	string direction;
	int x;
	int y;
};

struct Laser {
	string direction;
	int x;
	int y;
	bool destinationReached;
};

//global variables
int mazeSize = 0, itemCount = 0; 

//global array of items
Item itemArray[20];	

//function declarations
Item inputItems();
void trackDest(Item source);
Laser initializeLaser(Item source);
bool checkCollision(Laser laser);
string calculateNewDirection(Laser laser, Item item);
Item getCollisionItem(Laser laser);
void printDestNum(Laser laser);


int main() {
	//Set variables and fills item array
	cin >> mazeSize >> itemCount;
	for(int i = 0; i < itemCount; i++) {
		itemArray[i] = inputItems(); 
	}

	//Loops through the item array, prints each source and destination
	int sourceNum = 0;
	for(int i = 0; i < itemCount; i++) { 
		if(itemArray[i].type == "source") {
			sourceNum++;
			cout << sourceNum << "-";
			trackDest(itemArray[i]); //Tracks the destination for each source
		}
	}
	return 0;
}

//Takes in a line in the assignment format to input as an Item in itemArray
Item inputItems() {
	char dummy;
	Item singleItem;
	cin >> singleItem.type;
	if(singleItem.type != "dest" && singleItem.type != "block") { //Handles different formatting
		cin >> singleItem.direction;
	}
	cin >> singleItem.x;
	cin >> dummy; //Handles the comma
	cin >> singleItem.y;

	return singleItem;
}

//inputs a source item, creates a laser struct, then tracks it until it goes out of bounds or terminates.
void trackDest(Item source) {
	Laser laser = initializeLaser(source);
	Item item;

	while(laser.destinationReached == false) {
		//Used to keep track of laser coordinates for testing
		//cout << "(" << laser.x << "," << laser.y << ")" << endl;
		if(laser.direction == "east") {
			laser.x++; //moves laser right
			if(laser.x >= mazeSize) { //Handles out of bounds to the right
				cout << "X" << endl;
				return;
			}
			if(checkCollision(laser)){ //If there is a collision, calculate new direction or see if laser ends
				laser.direction = calculateNewDirection(laser, getCollisionItem(laser));
				if(laser.direction == "X") {
					cout << "X" << endl;
					return;
				} else if (laser.direction == "Destination") {
					laser.destinationReached = true;
					printDestNum(laser);					
				}
			}
		} else if(laser.direction == "west") {
			laser.x--; //moves laser left
			if(laser.x < 0) { //Handles out of bounds to the left
				cout << "X" << endl;
				return;
			}
			if(checkCollision(laser)){
				laser.direction = calculateNewDirection(laser, getCollisionItem(laser));
				if(laser.direction == "X") {
					cout << "X" << endl;
					return;
				} else if (laser.direction == "Destination") {
					laser.destinationReached = true;
					printDestNum(laser);
				}
			}
		} else if(laser.direction == "north") {
			laser.y++; //moves laser up
			if(laser.y >= mazeSize) { //Handles out of bounds to the top
				cout << "X" << endl;
				return;
			}
			if(checkCollision(laser)) {
				laser.direction = calculateNewDirection(laser, getCollisionItem(laser));
				if(laser.direction == "X") {
					cout << "X" << endl;
					return;
				} else if (laser.direction == "Destination") {
					laser.destinationReached = true;
					printDestNum(laser);
				}				
			}
		} else if(laser.direction == "south") {
			laser.y--; //moves laser down
			if(laser.y < 0) { //Handles out of bounds to the bottom
				cout << "X" << endl;
				return;
			}
			if(checkCollision(laser)) {
				laser.direction = calculateNewDirection(laser, getCollisionItem(laser));
				if(laser.direction == "X") {
					cout << "X" << endl;
					return;
				} else if (laser.direction == "Destination") {
					laser.destinationReached = true;
					printDestNum(laser);
				}				
			}
		}
	}
	return;
}

//Takes a source item and makes a laser struct from it
Laser initializeLaser(Item source) {
	Laser laser;
	laser.direction = source.direction;
	laser.x = source.x;
	laser.y = source.y;
	laser.destinationReached = false;
	return laser;
}

//Uses a lasers coordinates to see if a collision occurs by seeing if there are any items with the same coordinates
bool checkCollision(Laser laser) {
	bool collisionExists = false;
	for(int i = 0; i < itemCount; i++) {
		if(itemArray[i].x == laser.x && itemArray[i].y == laser.y){
			collisionExists = true;
			return collisionExists;
		}
	}
	return collisionExists;
}

//returns the new direction of the laser beam("east", "west", "south", "north")
//If laser hits obstacle, returns "X", if hits destination, returns "Destination"
string calculateNewDirection(Laser laser, Item item) {
	string outputDirection = "not outputDirection assigned yet"; 
	if(item.type == "single") { //Handles reflection off 1 sided mirror
		if(laser.direction == "east") {
			if(item.direction == "nw") {
				outputDirection = "north";
			} else if(item.direction == "sw") {
				outputDirection = "south";
			} else {
				outputDirection = "X";
			}
		} else if(laser.direction == "west") {
			if(item.direction == "ne") {
				outputDirection = "north";
			} else if(item.direction == "se") {
				outputDirection = "south";
			} else {
				outputDirection = "X";
			}
		} else if(laser.direction == "north") {
			if(item.direction == "se") {
				outputDirection = "east";
			} else if(item.direction == "sw") {
				outputDirection = "west";
			} else {
				outputDirection = "X";
			}
		} else if(laser.direction == "south") {
			if(item.direction == "ne") {
				outputDirection = "east";
			} else if(item.direction == "nw") {
				outputDirection = "west";
			} else {
				outputDirection = "X";
			}
		} else {
			return "mistakes were made";
		}
	} else if(item.type == "double") { //Handles reflections off of doubles
		if(laser.direction == "east") {
			if(item.direction == "nw" || item.direction == "se") {
				outputDirection = "north";
			} else if(item.direction == "ne" || item.direction == "sw") {
				outputDirection = "south";
			} else {
				outputDirection = "X";
			}
		} else if(laser.direction == "west") {
			if(item.direction == "nw" || item.direction == "se") {
				outputDirection = "south";
			} else if(item.direction == "ne" || item.direction == "sw") {
				outputDirection = "north";
			} else {
				outputDirection = "X";
			}
		} else if(laser.direction == "north") {
			if(item.direction == "nw" || item.direction == "se") {
				outputDirection = "east";
			} else if(item.direction == "ne" || item.direction == "sw") {
				outputDirection = "west";
			} else {
				outputDirection = "X";
			}
		} else if(laser.direction == "south") {
			if(item.direction == "nw" || item.direction == "se") {
				outputDirection = "west";
			} else if(item.direction == "ne" || item.direction == "sw") {
				outputDirection = "east";
			} else {
				outputDirection = "X";
			}
		} else { //Should never trigger as long as input is in correct format
			return "mistakes were made";
		}
	} else if(item.type == "block" || item.type == "source") { //Handles terminating collision
		outputDirection = "X";
	} else if(item.type == "dest") { //Reached destination!
		outputDirection = "Destination";
	}
	return outputDirection;
}

//Returns an item from the itemArray that the laser is colliding with using the x and y coordinates
Item getCollisionItem(Laser laser) {
	Item item;
	for(int i = 0; i < itemCount; i++) {
		if(itemArray[i].x == laser.x && itemArray[i].y == laser.y){
			item = itemArray[i];
			return item;
		}
	}
	return item;
}

//takes in a laser and uses its final x and y coordinates to determine the destination number rank
void printDestNum(Laser laser) {
	int destNum = 0;
	for(int i = 0; i < itemCount; i++) {
		if(itemArray[i].type == "dest") {
			destNum++;
			if(itemArray[i].x == laser.x && itemArray[i].y == laser.y) {
				cout << destNum << endl;
				return;
			}			
		}
	}
	return;
}
