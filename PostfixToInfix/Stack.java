package assignment1_3035344211;

/**
 * Implementation of a stack
 * @author davidbhan
 *
 */
public class Stack {
	private int capacity;
	private String[] stackArray;
	private int currentSize;
	
	/**
	 * Constructor for stack
	 */
	public Stack() {
		capacity = 0;
		stackArray = new String[capacity];
		currentSize = 0;
	}		
	
	/**
	 * Adds element to top of stack
	 * @param s String element to be added to stack
	 */
	public void push(String s) {
		// Implement dynamically expanding stack capacity
		if(this.isFull()) {
			if(capacity == 0) {
				capacity++;
			}
			capacity *= 2;
			String[] newArray = new String[capacity];
			for(int i = 0; i < stackArray.length; i++) {
				newArray[i] = stackArray[i];
			}
			stackArray = newArray;
		}
		currentSize++;
		stackArray[currentSize-1] = s;
		return;
	}
	
	/**
	 * Pops an element from the top of stack
	 * @return top element of stack
	 */
	public String pop() {
		// Empty stack returns a space
		if(this.isEmpty()) {
			return " ";
		}
		currentSize--;
		return stackArray[currentSize];
	}
	
	/**
	 * Views the top element of stack
	 * @return top element of stack
	 */
	public String peek() {
		return stackArray[currentSize-1];
	}
	
	/**
	 * Checks if stack is empty
	 * @return true if stack is empty
	 */
	public boolean isEmpty() {
		return currentSize == 0;
	}
	
	/**
	 * Checks if stack is full
	 * @return true if stack is full
	 */
	public boolean isFull() {
		return currentSize == capacity;
	}
	
}
