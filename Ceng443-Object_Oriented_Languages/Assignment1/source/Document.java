package hw1;
import java.util.*;

public class Document implements DocElement{

	private String title;
	private ArrayList<DocElement> elements = new ArrayList<>();

	public Document(String title) {
		this.title = title;
	}

	@Override
	public <T> T accept(TextVisitor<T> visitor) {
		return visitor.visit(this);
	}

	public String getTitle() {
		return title;
	}

	public void setTitle(String title) {
		this.title = title;
	}

	public ArrayList<DocElement> getElements() {
		return elements;
	}

	public void setElements(ArrayList<DocElement> arr) {
		elements.clear();
		elements.addAll(arr);
	}

	public void add(DocElement de) {
		elements.add(de);
	}
}
