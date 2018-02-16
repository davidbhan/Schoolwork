package assignment1_3035344211;

import java.io.*;

/**
 * Implementation of Infix to Postfix Reader
 * @author davidbhan
 *
 */
public class InfixReader {

	/**
	 * Main driver function to test code
	 * @param args input when running code, not used in this case
	 */
	public static void main(String[] args) {
		InfixReader myAnswer = new InfixReader();
		myAnswer.doConversion();
	}
	
	/**
	 * Reads in infix input and prints out the postfix version of that input
	 */
	public void doConversion() {
		String[] infix = this.readInfix(); // Infix expression
		String postfix = "Postfix:"; // Postfix output
		Stack stack = new Stack(); // Stack for operators
		
		// Iterate though all values in infix, appending to output string as needed
		for(String value : infix) {
			// When encountering number, directly append to result
			if(getPrecedence(value) < 0) {
				postfix += " " + value;
			// When encountering operator (not parenthesis), clear all higher precedence operators in stack, then push to stack
			} else if(getPrecedence(value) > 0) {
				if(stack.isEmpty()) {
					stack.push(value);
				} else {
					while(!stack.isEmpty() && getPrecedence(stack.peek()) >= getPrecedence(value)) {
						postfix += " " + stack.pop();
					}
					stack.push(value);
				}
			// When encountering closing parenthesis, we pop all operators until matching opening parenthesis
			} else if(value.equals("(")) {
				stack.push(value);
			} else if(value.equals(")")) {
				while(!stack.peek().equals("(")) {
					postfix += " " + stack.pop();
				}
				// No need to output opening parenthesis
				stack.pop();
			} else {
				System.out.println("Error in getPrecedence");
			}
		}
		// Add remaining operators from stack to result
		while(!stack.isEmpty()) {
			postfix += " " + stack.pop();
		}
		System.out.println(postfix);
	}
	
	/**
	 * Checks the order of operation precedence of a String
	 * @param operator a String, can be operator, number, or parenthesis
	 * @return -1 for a number/letter
	 *  0 for parenthesis
	 *  1 for +,-
	 *  2 for *,/
	 *  3 for ^
	 */
	public int getPrecedence(String operator) {
		if(operator.equals("^")) {
			return 3;
		} else if(operator.equals("*") || operator.equals("/")) {
			return 2;
		} else if(operator.equals("+") || operator.equals("–") || operator.equals("-")) {
			return 1;
		} else if(operator.equals("(") || operator.equals(")")) {
			return 0;
		} else {
			return -1;
		}
	}
	
	/**
	 * Reads Infix expression from command line into a String[]
	 * @return Infix expression with each number/operator in a String[]
	 */
	private String [] readInfix() {
		BufferedReader input = new BufferedReader(new InputStreamReader(System.in)); 
		String inputLine;
		try {
			System.out.print("Please input infix: ");
			inputLine = input.readLine();
			return inputLine.split(" ");
		} catch (IOException e) {
			System.err.println("Input ERROR.");
		}
		
		// return empty array if error occurs
		return new String[] { };
	}
}
