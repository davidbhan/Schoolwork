package assignment2_3035344211;

/**
 * 
 * Lion Class
 * @author davidbhan
 *
 */
public class Lion extends Feline{
	
	/**
	 * Constructor for Lion
	 */
	Lion() {
		this.setRepresentation('l');
		this.setSpecies("Lion");
	}
	
	/**
	 * Attack function for Lion
	 * @param animal target animal that is being attacked by this
	 * @return true if the attack is a success and target dies
	 */
	public boolean attack(Animal animal) {
		// Guaranteed win against Hippo
		if(animal.getSpecies().equals("Hippo")) {
			return true;
		} else {
			// Defer to Feline superclass attack
			return super.attack(animal);
		}
	}
	
}
