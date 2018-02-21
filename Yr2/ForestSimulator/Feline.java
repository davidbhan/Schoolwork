package assignment2_3035344211;

public class Feline extends Animal{

	Feline() {
		this.setType("Feline");
	}

	public void move() {
		
		// If animal is in corner, 50% chance to not move
		if(this.isInCorner()) {
			if(this.getRandom(2) > 0) {
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
	
	public boolean attack(Animal animal) {
		if(animal.getType().equals("Canine")) {
			return true;
		} else {
			return super.attack(animal);
		}
		
	}
	
}
