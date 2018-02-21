package assignment2_3035344211;

public class Lion extends Feline{
	
	Lion() {
		this.setRepresentation('l');
		this.setSpecies("Lion");
	}
	
	public boolean attack(Animal animal) {
		if(animal.getSpecies().equals("Hippo")) {
			return true;
		} else {
			return super.attack(animal);
		}
	}
	
}
