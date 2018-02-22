package assignment2_3035344211;

/**
 * 
 * Abstract Canine class
 * @author davidbhan
 *
 */
public abstract class Canine extends Animal{

	/**
	 * Constructor for Canine, initializes type of animal
	 */
	Canine() {
		this.setType("Canine");
	}
	
	/**
	 * Move function for Canines (4 directions, 1-2 steps), overwrites move function of superclass Animal
	 */
	public void move() {
		
		// If animal is in corner, 50% chance to not move
		if(this.isInCorner()) {
			if(this.getRandom(2) == 0) {
				return;
			}
		}
		
		// Random movement in 4 directions, 1 or 2 steps at a time, with out of bounds checking
		int moveDistance = 1;
		moveDistance += this.getRandom(2); // 50% chance to move 2 units
		
		boolean moved = false;
		while(!moved) {
			int direction = this.getRandom(4);
			if(direction == 0) {
				if(this.getPositionX() + moveDistance <= 14) {
					this.setPositionX(this.getPositionX()+moveDistance);
					moved = true;
				}
			} else if(direction == 1) {
				if(this.getPositionX() - moveDistance >= 0) {
					this.setPositionX(this.getPositionX()-moveDistance);
					moved = true;
				}
			} else if(direction == 2) {
				if(this.getPositionY() + moveDistance <= 14) {
					this.setPositionY(this.getPositionY()+moveDistance);
					moved = true;
				}
			} else if(direction == 3) {
				if(this.getPositionY() - moveDistance >= 0) {
					this.setPositionY(this.getPositionY()-moveDistance);
					moved = true;
				}
			}
		}	
	}
		
	/**
	 * Attack function for Canine
	 * @param animal target animal that is being attacked by this
	 * @return true if the attack is a success and target dies
	 */
	public boolean attack(Animal animal) {
		// 50% chance to win against Feline
		if(animal.getType().equals("Feline")) {
			if(getRandom(2) == 0) {
				return true;
			}
			return false;
		} else {
			// Defer to superclass Animal attack 
			return super.attack(animal);
		}
	}
	
}
