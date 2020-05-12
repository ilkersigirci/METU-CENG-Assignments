import java.util.ArrayList;

public class LibraryNodePrimaryIndex extends LibraryNode
{
	private ArrayList<Integer> keys;
	private ArrayList<LibraryNode> children;	
	
	public LibraryNodePrimaryIndex(LibraryNode parent) 
	{
		super(parent);
		keys = new ArrayList<Integer>();
		children = new ArrayList<LibraryNode>();
		this.type = LibraryNodeType.Internal;
	}
	
	public LibraryNodePrimaryIndex(LibraryNode parent, ArrayList<Integer> keys, ArrayList<LibraryNode> children) 
	{
		super(parent);
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

	public boolean isOverflow() {
		return this.keyCount() > 2 * LibraryNode.order;
	}
	public LibraryNode splitInternal(int choose){
		int i;
		int key;

		if(choose == 1){
			LibraryNode lInternal = new LibraryNodePrimaryIndex(null);
			for (i = 0; i < LibraryNode.order; i++) {
				key = this.keyAtIndex(i);
				((LibraryNodePrimaryIndex) lInternal).addKeyToIndex(i, key);
			}
			return lInternal;
		}
		else{
			LibraryNode rInternal = new LibraryNodePrimaryIndex(null);
			for (i = LibraryNode.order+1; i < this.keyCount(); i++) {
				key = this.keyAtIndex(i);
				((LibraryNodePrimaryIndex) rInternal).addKeyToIndex(i - (LibraryNode.order+1), key);
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
				((LibraryNodePrimaryIndex) internalNode).addChildToIndex(i, child);
			}
		}
		else{
			for (i = LibraryNode.order+1; i < this.keyCount()+1; i++) {
				child = this.getChildrenAt(i);
				child.setParent(internalNode);
				((LibraryNodePrimaryIndex) internalNode).addChildToIndex(i - (LibraryNode.order+1), child);
			}
		}
	}

}
