package hw2;
import java.util.concurrent.locks.*;

public class Lab {

	// initial final variables
	final String name;
	final int capacity;

	// for getting which group is studying in the lab at the moment
	private String currentGroup;

	// for getting how many students are studying in the lab
	private int studentNumber;

	// to synchronize adding/removing student methods
	private final ReentrantLock mainLock;

	// to signal/wait for  add/remove student methods according to given conditions
	private final Condition addCond;
	private final Condition removeCond;

	// constructor for initializing class variables
	public Lab(String name, int capacity) {
		this.name = name;
		this.capacity = capacity;
		currentGroup = null;
		studentNumber = 0;
		mainLock = new ReentrantLock();
		addCond = mainLock.newCondition();
		removeCond = mainLock.newCondition();
	}

	// public getter for the name of the lab
	public String getName() {
		return name;
	}

	// public getter for capacity of the lab
	public int getCapacity() {
		return capacity;
	}

	// add a student to the lab
	public void addToLab(String groupName){

		// for synchronization with removeFromLab method
		mainLock.lock();

		try {
			// a student must wait if lab capacity is full or his/her study group is different than the current lab study group
			while ( studentNumber == capacity && currentGroup != null || (!groupName.equals(currentGroup) && studentNumber != 0)) {
				addCond.await();
			}
			// now set the current study group if the student is the first entering.
			if (studentNumber == 0) {
				currentGroup = groupName;
			}
			// add student to the lab
			studentNumber += 1;

			// signal removeFromLab method so that it knows that a student entered the lab
			removeCond.signal();

		} catch (InterruptedException e) {
			e.printStackTrace();
		} finally {

			// since critical condition part ends, the method must release the lock.
			mainLock.unlock();
		}
	}

	// remove a student from the lab
	public void removeFromLab(String groupName){

		// for synchronization with removeFromLab method
		mainLock.lock();
		try {
			// a student can't be removed if there is no one in the lab
			while (studentNumber == 0) {
				removeCond.await();
			}
			// otherwise, remove the student
			studentNumber -= 1;

			// signal addToLab method so that it knows that a student left the lab
			addCond.signal();

		} catch (InterruptedException e) {
			e.printStackTrace();
		} finally {

			// since critical condition part ends, the method must release the lock.
			mainLock.unlock();
		}
	}
}
