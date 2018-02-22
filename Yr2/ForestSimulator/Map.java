package assignment2_3035344211;

import java.util.ArrayList;

/**
 * 
 * Map class for handling the forest map display. Contains a nested animal list
 * @author davidbhan
 *
 */
public class Map {

	private ArrayList<Animal> animals; 	// List of animals on map
	private char[][] map; 				// Map representation
	
	/**
	 * Constructor for the Map, creates and populates the map, then prints it out
	 */
	Map() {		
		animals = new ArrayList<Animal>();
		map = new char[15][15]; 
		initializeMap(); 		// Fill map with '.'
		initializeAnimals(); 	// Add desired animals to the the ArrayList of animals in movement order
		initializePositions(); 	// Initialize Random positions of animals on map
		updateMap(); 			// Updates map with the current position of each animal
		printMap(); 				// Print map
	}
	
	/**
	 * Sets all values of the map to '.'
	 */
	public void initializeMap() {
		for(int i = 0; i < 15; i++) {
			for(int j = 0; j < 15; j++) {
				map[i][j] = '.';
			}
		}
	}
	
	/**
	 * Adds animals to animals ArrayList in movement order
	 */
	public void initializeAnimals() {
		animals.add(new Cat());
		animals.add(new Dog());
		animals.add(new Fox());
		animals.add(new Hippo());
		animals.add(new Lion());
		animals.add(new Tiger());
		animals.add(new Turtle());
		animals.add(new Wolf());
	}
	
	/**
	 * Randomly initialize animal positions
	 */
	public void initializePositions() {
		for(Animal animal : animals) {
			// Set random row position
			int randomX = animal.getRandom(15);
			animal.setPositionX(randomX);
		
			// Keep finding random column position until we find an empty space
			int randomY = animal.getRandom(15);
			while(map[randomX][randomY] != '.') {
				randomY = animal.getRandom(15);
			}
			animal.setPositionY(randomY);
			
			// Update map after adding each animal
			updateMap();
		}		
	}
	
	/**
	 * Reset the map to empty, then populates map with current animal positions
	 */
	public void updateMap() {
		initializeMap();
		for(Animal animal : animals) {
			if(animal.getIsDead()) {
				continue;
			}
			map[animal.getPositionX()][animal.getPositionY()] = animal.getRepresentation();
		}
	}
	
	/**
	 * Print the map to the command line
	 */
	public void printMap() {
		for(int i = 0; i < 15; i++) {
			for(int j = 0; j < 15; j++) {
				System.out.print(map[i][j]);
			}
			System.out.println();
		}
	}
	
	/**
	 * Iterate map by moving each animal and performing attacks if any
	 */
	public void iterate() {
		
		// Perform an action for each animal that is alive
		for(Animal animal : animals) {
			if(animal.getIsDead()) {
				continue;
			}
			
			// Tentatively move the animal and get original and target coordinates without updating map
			int originalX = animal.getPositionX();
			int originalY = animal.getPositionY();
			animal.move();			
			int newX = animal.getPositionX();
			int newY = animal.getPositionY();
			
			// Check if target map coordinates isn't empty and has a different animal
			if(map[newX][newY] != animal.getRepresentation() && map[newX][newY] != '.') {
				
				// Find which animal in animals is the target of the attack by matching x,y positions
				for(Animal target : animals) {
					
					// Skip dead animals
					if(target.getIsDead()) {
						continue;
					}
					
					// Skip self
					if(target.getSpecies().equals(animal.getSpecies())) {
						continue;
					}
					
					// Find animal with matching coordinates
					if(target.getPositionX() == newX && target.getPositionY() == newY) {
						boolean attackSuccess = animal.attack(target);
						if(attackSuccess) {
							System.out.println(animal.getSpecies() + " from " + originalX + "," + originalY + " attacks " + target.getSpecies() + " at " + newX + "," + newY + " and wins");
							kill(target);
							System.out.println(animal.getSpecies() + " moved from " + originalX + "," + originalY + " to " + newX + "," + newY);
						} else {
							System.out.println(animal.getSpecies() + " from " + originalX + "," + originalY + " attacks " + target.getSpecies() + " at " + newX + "," + newY + " and loses");							
							kill(animal);
						}
						
					}
				}
			} else {
				// Directly move animal when target coordinate is empty or is the original position
				System.out.println(animal.getSpecies() + " moved from " + originalX + "," + originalY + " to " + newX + "," + newY);
			}
			updateMap();
		}
	}
	
	/**
	 * Reassigns dead animal to a random nearby position, prints out its death, then marks it as dead
	 * @param animal Animal from ArrayList to be killed
	 */
	public void kill(Animal animal) {
		// Count number of open spaces around the target
		int numOpenSpaces = 0;
		for(int i = -1; i <= 1; i++) {
			for(int j = -1; j <= 1; j++) {
				int x = animal.getPositionX() + i;
				int y = animal.getPositionY() + j;
				if(x > 14 || x < 0 || y > 14 || y < 0) {
					continue;
				} else if(map[x][y] == '.') {
					numOpenSpaces++;
				}
			}
		}
		
		// Generate a random number less than num open spaces
		int random = animal.getRandom(numOpenSpaces);
		
		// Move dead body according to random number
		int counter = 0;
		for(int i = -1; i <= 1; i++) {
			for(int j = -1; j <= 1; j++) {
				int x = animal.getPositionX() + i;
				int y = animal.getPositionY() + j;
				if(x > 14 || x < 0 || y > 14 || y < 0) {
					continue;
				} else if(map[x][y] == '.') {
					if(counter == random) {
						animal.setPositionX(x);
						animal.setPositionY(y);
					}
					counter++;
				}
			}
		}
		
		// Print death message
		System.out.println(animal.getSpecies() + " dies at " + animal.getPositionX() + "," + animal.getPositionY());
		
		// Set animal as dead
		animal.setIsDead(true);
	}
	
	/**
	 * Prints out locations of living animals, followed by locations of dead animals
	 */
	public void exit() {
		// Print living animals
		for(Animal animal : animals) {
			if(!animal.getIsDead()) {
				System.out.println(animal.getSpecies() + " is alive at " + animal.getPositionX() + "," + animal.getPositionY());
			}
		}
		
		// Print dead animals
		for(Animal animal : animals) {
			if(animal.getIsDead()) {
				System.out.println(animal.getSpecies() + " is dead at " + animal.getPositionX() + "," + animal.getPositionY());
			}
		}
	}
	
}
