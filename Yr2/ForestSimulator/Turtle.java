package assignment2_3035344211;

public class Turtle extends Animal{
	
	Turtle() {
		this.setRepresentation('u');
		this.setSpecies("Turtle");
	}
	
	/**
	 * General move method for animal to update x and y position
	 * Movement in 4 directions, 1 step at a time, with corner being 50% chance of not moving
	 */
	public void move() {		
		
		// Whether turtle is in corner or not, it has 50% chance to stay in place
		if(this.getRandom(2) > 0) {
			return;
		}
		
		// Random movement in 4 directions, with out of bounds checking
		boolean moved = false;
		while(!moved) {
			int direction = this.getRandom(4);
			if(direction == 0) {
				if(this.getPositionX() + 1 <= 14) {
					this.setPositionX(this.getPositionX()+1);
					moved = true;
				}
			} else if(direction == 1) {
				if(this.getPositionX() - 1 >= 0) {
					this.setPositionX(this.getPositionX()-1);
					moved = true;
				}
			} else if(direction == 2) {
				if(this.getPositionY() + 1 <= 14) {
					this.setPositionY(this.getPositionY()+1);
					moved = true;
				}
			} else if(direction == 3) {
				if(this.getPositionY() - 1 >= 0) {
					this.setPositionY(this.getPositionY()-1);
					moved = true;
				}
			}
		}				
	}
	
	public boolean attack(Animal animal) {
		if(getRandom(2) == 0) {
			return true;
		}		
		return false; 
	}
}
