import java.util.ArrayList;

public class LibraryNodeSecondaryIndex extends LibraryNode
{
	private ArrayList<Integer> keys;
	private ArrayList<Integer> years;
	private ArrayList<LibraryNode> children;	
	
	public LibraryNodeSecondaryIndex(LibraryNode parent) 
	{
		super(parent);
		keys = new ArrayList<Integer>();
		years = new ArrayList<Integer>();
		children = new ArrayList<LibraryNode>();
		this.type = LibraryNodeType.Internal;
	}
	
	public LibraryNodeSecondaryIndex(LibraryNode parent, ArrayList<Integer> years, ArrayList<Integer> keys, ArrayList<LibraryNode> children) 
	{
		super(parent);
		this.years = years;
		this.keys = keys;
		this.children = children;
		this.type = LibraryNodeType.Internal;
	}
	
	// GUI Methods - Do not modify
	public ArrayList<LibraryNode> getAllChildren()
	{
		return this.children;
	}
	
	public LibraryNode getChildrenAt(Integer index) {
		
		return this.children.get(index);
	}
	
	public Integer keyCount()
	{
		return this.keys.size();
	}
	public Integer keyAtIndex(Integer index)
	{
		if(index >= this.keyCount() || index < 0)
		{
			return -1;
		}
		else
		{
			return this.keys.get(index);			
		}
	}
	
	public Integer yearAtIndex(Integer index)
	{
		if(index >= this.keyCount() || index < 0)
		{
			return -1;
		}
		else
		{
			return this.years.get(index);			
		}
	}
	
	
	// Extra functions if needed

	public void setChildAtIndex(int i, LibraryNode child){
		this.children.set(i, child);
	}
	public void addChildToIndex(int i, LibraryNode child){
		this.children.add(i, child);
	}
	public void addKeyToIndex(int i, int key){
		this.keys.add(i, key);
	}
	public void addYearToIndex(int i, int year){
		this.years.add(i, year);
	}

	public boolean isOverflow() {
		return this.keyCount() > 2 * LibraryNode.order;
	}
	public LibraryNode splitInternal(int choose){
		int i;
		int key;
		int year;

		if(choose == 1){
			LibraryNode lInternal = new LibraryNodeSecondaryIndex(null);
			for (i = 0; i < LibraryNode.order; i++) {
				key = this.keyAtIndex(i);
				year = this.yearAtIndex(i);
				((LibraryNodeSecondaryIndex) lInternal).addKeyToIndex(i, key);
				((LibraryNodeSecondaryIndex) lInternal).addYearToIndex(i, year);
			}
			return lInternal;
		}
		else{
			LibraryNode rInternal = new LibraryNodeSecondaryIndex(null);
			for (i = LibraryNode.order+1; i < this.keyCount(); i++) {
				key = this.keyAtIndex(i);
				year = this.yearAtIndex(i);
				((LibraryNodeSecondaryIndex) rInternal).addKeyToIndex(i - (LibraryNode.order+1), key);
				((LibraryNodeSecondaryIndex) rInternal).addYearToIndex(i - (LibraryNode.order+1), year);
			}
			return rInternal;
		}

	}
	public void arrangeChildren(int choose, LibraryNode internalNode){
		LibraryNode child;
		int i;
		if(choose == 1){
			for (i = 0; i < LibraryNode.order+1; i++) {
				child = this.getChildrenAt(i);
				child.setParent(internalNode);
				((LibraryNodeSecondaryIndex) internalNode).addChildToIndex(i, child);
			}
		}
		else{
			for (i = LibraryNode.order+1; i < this.keyCount()+1; i++) {
				child = this.getChildrenAt(i);
				child.setParent(internalNode);
				((LibraryNodeSecondaryIndex) internalNode).addChildToIndex(i - (LibraryNode.order+1), child);
			}
		}
	}


}
