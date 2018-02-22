package assignment2_3035344211;

import java.util.Random;

/**
 * 
 * Abstract animal superclass
 * @author davidbhan
 *
 */
public abstract class Animal {

	private char representation;
	private String species;
	private String type;
	private int positionX;
	private int positionY;
	private boolean isDead;
	private Random rand = new Random();
	
	/**
	 * Constructor for Animal
	 */
	Animal() {
		type = "no_type";
		species = "no_species";
		representation = 'n';
		isDead = false;
	}
	
	/**
	 * General move method for animal to update x and y position
	 * Movement in 4 directions, 1 step at a time, with corner being 50% chance of not moving
	 */
	public void move() {		
		
		// If animal is in corner, 50% chance to not move
		if(isInCorner()) {
			if(getRandom(2) == 0) {
				return;
			}
		}
		
		// Random movement in 4 directions, with out of bounds checking
		boolean moved = false;
		while(!moved) {
			int direction = getRandom(4);
			if(direction == 0) {
				if(getPositionX() + 1 <= 14) {
					setPositionX(getPositionX()+1);
					moved = true;
				}
			} else if(direction == 1) {
				if(getPositionX() - 1 >= 0) {
					setPositionX(getPositionX()-1);
					moved = true;
				}
			} else if(direction == 2) {
				if(getPositionY() + 1 <= 14) {
					setPositionY(getPositionY()+1);
					moved = true;
				}
			} else if(direction == 3) {
				if(getPositionY() - 1 >= 0) {
					setPositionY(getPositionY()-1);
					moved = true;
				}
			}
		}		
		
	}
	
	/**
	 * Baseline attack function for animal
	 * @param animal target animal that is being attacked by this
	 * @return true if the attack is a success and target dies
	 */
	public boolean attack(Animal animal) {
		// 20% chance to win against turtle
		if(animal.getClass().getSimpleName().equals("Turtle")) {
			if(getRandom(10) < 2) {
				return true;
			}
		}
		// Default behavior is to lose
		return false;
	}
	
	/**
	 * Checks if animal is located in a corner of the board
	 * @return true if in corner
	 */
	public boolean isInCorner() {
		if(positionX == 0 && positionY == 0) {
			return true;
		} else if(positionX == 0 && positionY == 14) {
			return true;
		} else if(positionX == 14 && positionY == 0) {
			return true;
		} else if(positionX == 14 && positionY == 14) {
			return true;
		}
		return false;
	}
	
	/**
	 * Random number generator method for ease of use in subclasses
	 * @param bound the bound on the random number generated
	 * @return an integer from [0,bound)
	 */
	public int getRandom(int bound) {
		return rand.nextInt(bound);
	}
	
	/**
	 * @return the representation
	 */
	public char getRepresentation() {
		return representation;
	}

	/**
	 * @param representation the representation to set
	 */
	public void setRepresentation(char representation) {
		this.representation = representation;
	}

	/**
	 * @return the species
	 */
	public String getSpecies() {
		return species;
	}

	/**
	 * @param species the species to set
	 */
	public void setSpecies(String species) {
		this.species = species;
	}

	/**
	 * @return the type
	 */
	public String getType() {
		return type;
	}

	/**
	 * @param type the type to set
	 */
	public void setType(String type) {
		this.type = type;
	}

	/**
	 * @return the isDead
	 */
	public boolean getIsDead() {
		return isDead;
	}

	/**
	 * @param isDead the isDead to set
	 */
	public void setIsDead(boolean isDead) {
		this.isDead = isDead;
	}
	
	/**
	 * @return the positionX
	 */
	public int getPositionX() {
		return positionX;
	}

	/**
	 * @param positionX the positionX to set
	 */
	public void setPositionX(int positionX) {
		this.positionX = positionX;
	}

	/**
	 * @return the positionY
	 */
	public int getPositionY() {
		return positionY;
	}

	/**
	 * @param positionY the positionY to set
	 */
	public void setPositionY(int positionY) {
		this.positionY = positionY;
	}


}
