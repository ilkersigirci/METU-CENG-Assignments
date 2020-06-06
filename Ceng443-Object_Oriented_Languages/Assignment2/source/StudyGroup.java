package hw2;

public class StudyGroup {

	final String name;
	final Lab lab;

	public StudyGroup(String name, Lab lab) {
		this.name = name;
		this.lab = lab;
	}

	public String getName() {
		return name;
	}

	public Lab getLab() {
		return lab;
	}

	// all the operations handled within the lab class
	public void startStudyingWith() {
		lab.addToLab(name);
	}

	// all the operations handled within the lab class
	public void stopStudyingWith() {
		lab.removeFromLab(name);
	}
}
