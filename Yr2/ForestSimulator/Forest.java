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
	 * Central logic code of the program
	 * NOTE: The ArrayList of animals is nested in the Map Class for cleaner, more economic design
	 */
	public void run() {
		Map map = new Map(); // Create a new map for the forest
		
		String line; // Read in user input and iterate the map until user types 'exit'
		System.out.print("Press enter to iterate, type 'exit' to quit:");
		line = scanner.nextLine();
		while(!line.equals("exit")) {
			map.iterate();
			System.out.print("Press enter to iterate, type 'exit' to quit:");
			line = scanner.nextLine();
		}
	}
	
}
