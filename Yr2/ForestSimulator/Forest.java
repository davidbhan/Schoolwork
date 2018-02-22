package assignment2_3035344211;

import java.util.Scanner;

/**
 * 
 * Implementation of a Forest simulator
 * @author davidbhan
 *
 */
public class Forest {

	private Scanner scanner = new Scanner(System.in);
	
	/**
	 * Start of Program
	 * @param args not used
	 */
	public static void main(String[] args) {
		Forest forest = new Forest();
		forest.run();
	}
	
	/**
	 * Driver for the program
	 * NOTE: The ArrayList of animals is nested in the Map Class for cleaner, more economic design
	 * Full use of polymorphism and inheritance is still used in Animal moving and attacking, only class nesting is different from sinkDotCom
	 */
	public void run() {
		// Create a new map section in the forest and print it
		Map map = new Map(); 
		System.out.print("Press enter to iterate, type 'exit' to quit:");
		String line = scanner.nextLine();
		
		// Read in user input and iterate the map until user types 'exit'
		while(!line.equals("exit")) {
			map.iterate(); 
			System.out.print("Press enter to iterate, type 'exit' to quit:");
			line = scanner.nextLine();
		}
		
		map.exit(); // Prints living conditions and locations of all animals
	}
	
}
