package assignment2_3035344211;

/**
 * 
 * Abstract Feline Class
 * @author davidbhan
 *
 */
public abstract class Feline extends Animal{

	/**
	 * Constructor for Feline, initializes type of animal
	 */
	Feline() {
		this.setType("Feline");
	}

	/**
	 * Move function for Feline (8 directions, 1 step), overwrites move function of superclass Animal
	 */
	public void move() {
		
		// If animal is in corner, 50% chance to not move
		if(this.isInCorner()) {
			if(this.getRandom(2) == 0) {
				return;
			}
		}
		
		// Random movement in 8 directions, with out of bounds checking
		boolean moved = false;
		while(!moved) {
			int direction = this.getRandom(8);
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
			} else if(direction == 4) {
				if(this.getPositionX() + 1 <= 14 && this.getPositionY() + 1 <= 14) {
					this.setPositionX(this.getPositionX()+1);
					this.setPositionY(this.getPositionY()+1);
					moved = true;
				}
			} else if(direction == 5) {
				if(this.getPositionX() + 1 <= 14 && this.getPositionY() - 1 >= 0) {
					this.setPositionX(this.getPositionX()+1);
					this.setPositionY(this.getPositionY()-1);
					moved = true;
				}
			} else if(direction == 6) {
				if(this.getPositionX() - 1 >= 0 && this.getPositionY() + 1 <= 14) {
					this.setPositionX(this.getPositionX()-1);
					this.setPositionY(this.getPositionY()+1);
					moved = true;
				}
			} else if(direction == 7) {
				if(this.getPositionX() - 1 >= 0 && this.getPositionY() - 1 >= 0) {
					this.setPositionX(this.getPositionX()-1);
					this.setPositionY(this.getPositionY()-1);
					moved = true;
				}
			}
		}	
	}
	
	/**
	 * Attack function for Feline
	 * @param animal target animal that is being attacked by this
	 * @return true if the attack is a success and target dies
	 */
	public boolean attack(Animal animal) {
		if(animal.getType().equals("Canine")) {
			return true;
		} else {
			return super.attack(animal);
		}
		
	}
	
}
