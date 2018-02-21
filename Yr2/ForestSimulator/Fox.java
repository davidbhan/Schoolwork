package assignment2_3035344211;

public class Fox extends Canine{
	
	Fox() {
		this.setRepresentation('f');
		this.setSpecies("Fox");
	}
	
	public boolean attack(Animal animal) {

		if(animal.getSpecies().equals("Cat")) {
			return true;
		} else {
			return super.attack(animal);
		}
	}
	
}
