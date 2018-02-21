package assignment2_3035344211;

public class Canine extends Animal{

	Canine() {
		this.setType("Canine");
	}
	
	public void move() {
		
		// If animal is in corner, 50% chance to not move
		if(this.isInCorner()) {
			if(this.getRandom(2) > 0) {
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
	
	public boolean attack(Animal animal) {
		if(animal.getType().equals("Feline")) {
			if(getRandom(2) == 0) {
				return true;
			}
			return false;
		} else {
			return super.attack(animal);
		}
	}
	
}
