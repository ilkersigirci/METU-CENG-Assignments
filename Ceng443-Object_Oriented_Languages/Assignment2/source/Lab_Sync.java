package hw2;
import java.util.concurrent.locks.*;

public class Lab {

	final String name;
	final int capacity;
	private String currentGroup;
	private int studentNumber;

	public Lab(String name, int capacity) {
		this.name = name;
		this.capacity = capacity;
		currentGroup = null;
		studentNumber = 0;
	}

	public String getName() {
		return name;
	}

	public int getCapacity() {
		return capacity;
	}

	public synchronized void  addToLab(String groupName) throws InterruptedException{

		while ( studentNumber == capacity || ( currentGroup != null && !groupName.equals(currentGroup)) ){ wait(); }
		if (studentNumber == 0) { currentGroup = groupName; }
		studentNumber += 1;
		notifyAll();
	}

	public synchronized void removeFromLab(String groupName) throws InterruptedException{

		if (studentNumber == 0) { wait(); }
		studentNumber -= 1;
		if (studentNumber == 0) { currentGroup = null; }
		notifyAll();
	}
}
