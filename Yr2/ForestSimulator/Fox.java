package assignment2_3035344211;

/**
 * 
 * Fox Class
 * @author davidbhan
 *
 */
public class Fox extends Canine{
	
	/**
	 * Constructor for Fox
	 */
	Fox() {
		this.setRepresentation('f');
		this.setSpecies("Fox");
	}
	
	/**
	 * Attack function for Fox
	 * @param animal target animal that is being attacked by this
	 * @return true if the attack is a success and target dies
	 */
	public boolean attack(Animal animal) {
		// Guaranteed win against cat
		if(animal.getSpecies().equals("Cat")) {
			return true;
		} else {
			// Defer to Canine superclass attack method
			return super.attack(animal);
		}
	}
	
}
