import java.util.ArrayList;
import java.util.Collections;
public class LibraryTree {
	
	public LibraryNode primaryRoot;		//root of the primary B+ tree
	public LibraryNode secondaryRoot;	//root of the secondary B+ tree
	public LibraryTree(Integer order)
	{
		LibraryNode.order = order;
		primaryRoot = new LibraryNodeLeaf(null);
		primaryRoot.level = 0;
		secondaryRoot = new LibraryNodeLeaf(null);
		secondaryRoot.level = 0;
	}

	public void addBook(CengBook book) {
		
		// add methods to fill both primary and secondary tree
		myAddBook(book, primaryRoot, 0);
		myAddBook2(book, secondaryRoot, 0);
	}
	
	
	
	public CengBook searchBook(Integer key) {
		
		// add methods to find the book with the searched key in primary B+ tree
		// return value will not be tested, just print as the specicifications say
		mySearchBook(primaryRoot, key);
		return null;
		}
	
	
	public void printPrimaryLibrary() {
		
		// add methods to print the primary B+ tree in Depth-first order
		dfs(primaryRoot);
		
	}
	
	public void printSecondaryLibrary() {
		
		// add methods to print the secondary B+ tree in Depth-first order
		dfs2(secondaryRoot);
	}
	
	// Extra functions if needed

	public void myAddBook(CengBook book, LibraryNode node, int index) {
		int key = book.key();
		int i, flag = 0;
		LibraryNode newRoot;
		LibraryNode parent = node.getParent();
		//LibraryNode child = new LibraryNode(null);
		LibraryNode child = null;
		if (node.getType() == LibraryNodeType.Internal) {
			for (i = 0; i < ((LibraryNodePrimaryIndex) node).keyCount(); i++) {
				int myKey = ((LibraryNodePrimaryIndex) node).keyAtIndex(i);
				if (key > myKey) continue;
				child = ((LibraryNodePrimaryIndex) node).getChildrenAt(i);
				flag = 1;
				break;
			}
			if(flag == 0) child = ((LibraryNodePrimaryIndex) node).getChildrenAt(i);

			myAddBook(book, child, i);
			//TODO: internal islemleri(add ve overflow handle)

			if(((LibraryNodePrimaryIndex) node).isOverflow() == false) return;

			//Handle split
			LibraryNode lInternal = ((LibraryNodePrimaryIndex)node).splitInternal(1);
			LibraryNode rInternal = ((LibraryNodePrimaryIndex) node).splitInternal(2);
			int pushUpKey = ((LibraryNodePrimaryIndex) node).keyAtIndex(LibraryNode.order);
			((LibraryNodePrimaryIndex) node).arrangeChildren(1, lInternal);
			((LibraryNodePrimaryIndex) node).arrangeChildren(2, rInternal);

			if (parent == null) {
				ArrayList<Integer> myKeys = new ArrayList<Integer>();
				ArrayList<LibraryNode> myChildren = new ArrayList<LibraryNode>();
				myKeys.add(0, pushUpKey);
				myChildren.add(0, lInternal);
				myChildren.add(1, rInternal);
				newRoot = new LibraryNodePrimaryIndex(null, myKeys, myChildren);
				lInternal.setParent(newRoot);
				rInternal.setParent(newRoot);
				primaryRoot = newRoot;
			}
			else{
				((LibraryNodePrimaryIndex) parent).addKeyToIndex(index, pushUpKey);
				((LibraryNodePrimaryIndex) parent).setChildAtIndex(index, lInternal);
				((LibraryNodePrimaryIndex) parent).addChildToIndex(index+1, rInternal);
				lInternal.setParent(parent);
				rInternal.setParent(parent);
			}

		}
		else { // leaf
			addSorted(book, node);
			if(isOverflow(node)== false) return; // no split

			//Handle split
			LibraryNode lLeaf = splitLeaf(1, node);
			LibraryNode rLeaf = splitLeaf(2, node);
			int copyUpKey = ((LibraryNodeLeaf) rLeaf).bookKeyAtIndex(0);

			if (parent == null) {
				ArrayList<Integer> myKeys = new ArrayList<Integer>();
				ArrayList<LibraryNode> myChildren = new ArrayList<LibraryNode>();
				myKeys.add(0, copyUpKey);
				myChildren.add(0, lLeaf);
				myChildren.add(1, rLeaf);
				newRoot = new LibraryNodePrimaryIndex(null, myKeys, myChildren);
				lLeaf.setParent(newRoot);
				rLeaf.setParent(newRoot);
				primaryRoot = newRoot;
			}
			else {
				((LibraryNodePrimaryIndex) parent).addKeyToIndex(index, copyUpKey);
				((LibraryNodePrimaryIndex) parent).setChildAtIndex(index, lLeaf);
				((LibraryNodePrimaryIndex) parent).addChildToIndex(index+1, rLeaf);
				lLeaf.setParent(parent);
				rLeaf.setParent(parent);
			}


		}
	}

	public void myAddBook2(CengBook book, LibraryNode node, int index) {
		int key = book.key();
		int year = book.year();
		int i, flag = 0;
		LibraryNode newRoot;
		LibraryNode parent = node.getParent();
		//LibraryNode child = new LibraryNode(null);
		LibraryNode child = null;
		if (node.getType() == LibraryNodeType.Internal) {
			for (i = 0; i < ((LibraryNodeSecondaryIndex) node).keyCount(); i++) {
				int myKey = ((LibraryNodeSecondaryIndex) node).keyAtIndex(i);
				int myYear = ((LibraryNodeSecondaryIndex) node).yearAtIndex(i);
				if ( (year > myYear) || ((year == myYear) && (key > myKey)) ) continue;
				child = ((LibraryNodeSecondaryIndex) node).getChildrenAt(i);
				flag = 1;
				break;
			}
			if(flag == 0) child = ((LibraryNodeSecondaryIndex) node).getChildrenAt(i);

			myAddBook2(book, child, i);
			//TODO: internal islemleri(add ve overflow handle)

			if(((LibraryNodeSecondaryIndex) node).isOverflow() == false) return;

			//Handle split
			LibraryNode lInternal = ((LibraryNodeSecondaryIndex)node).splitInternal(1);
			LibraryNode rInternal = ((LibraryNodeSecondaryIndex) node).splitInternal(2);
			int pushUpKey = ((LibraryNodeSecondaryIndex) node).keyAtIndex(LibraryNode.order);
			int pushUpYear = ((LibraryNodeSecondaryIndex) node).yearAtIndex(LibraryNode.order);
			((LibraryNodeSecondaryIndex) node).arrangeChildren(1, lInternal);
			((LibraryNodeSecondaryIndex) node).arrangeChildren(2, rInternal);

			if (parent == null) {
				ArrayList<Integer> myKeys = new ArrayList<Integer>();
				ArrayList<Integer> myYears = new ArrayList<Integer>();
				ArrayList<LibraryNode> myChildren = new ArrayList<LibraryNode>();
				myKeys.add(0, pushUpKey);
				myYears.add(0, pushUpYear);
				myChildren.add(0, lInternal);
				myChildren.add(1, rInternal);
				newRoot = new LibraryNodeSecondaryIndex(null, myYears, myKeys, myChildren);
				lInternal.setParent(newRoot);
				rInternal.setParent(newRoot);
				secondaryRoot = newRoot;
			}
			else{
				((LibraryNodeSecondaryIndex) parent).addKeyToIndex(index, pushUpKey);
				((LibraryNodeSecondaryIndex) parent).addYearToIndex(index, pushUpYear);
				((LibraryNodeSecondaryIndex) parent).setChildAtIndex(index, lInternal);
				((LibraryNodeSecondaryIndex) parent).addChildToIndex(index+1, rInternal);
				lInternal.setParent(parent);
				rInternal.setParent(parent);
			}

		}
		else { // leaf
			addSorted2(book, node);
			if(isOverflow(node) == false) return; // no split

			//Handle split
			LibraryNode lLeaf = splitLeaf(1, node);
			LibraryNode rLeaf = splitLeaf(2, node);
			int copyUpKey = ((LibraryNodeLeaf) rLeaf).bookKeyAtIndex(0);
			int copyUpYear = ((LibraryNodeLeaf) rLeaf).bookYearAtIndex(0);

			if (parent == null) {
				ArrayList<Integer> myKeys = new ArrayList<Integer>();
				ArrayList<Integer> myYears = new ArrayList<Integer>();
				ArrayList<LibraryNode> myChildren = new ArrayList<LibraryNode>();
				myKeys.add(0, copyUpKey);
				myYears.add(0, copyUpYear);
				myChildren.add(0, lLeaf);
				myChildren.add(1, rLeaf);
				newRoot = new LibraryNodeSecondaryIndex(null, myYears, myKeys, myChildren);
				lLeaf.setParent(newRoot);
				rLeaf.setParent(newRoot);
				secondaryRoot = newRoot;
			}
			else {
				((LibraryNodeSecondaryIndex) parent).addKeyToIndex(index, copyUpKey);
				((LibraryNodeSecondaryIndex) parent).addYearToIndex(index, copyUpYear);
				((LibraryNodeSecondaryIndex) parent).setChildAtIndex(index, lLeaf);
				((LibraryNodeSecondaryIndex) parent).addChildToIndex(index+1, rLeaf);
				lLeaf.setParent(parent);
				rLeaf.setParent(parent);
			}


		}
	}

	public void mySearchBook(LibraryNode node, int key){
		LibraryNode child = null;
		int flag = 0;
		int i;
		int myKey;
		CengBook myBook;
		if (node.getType() == LibraryNodeType.Internal) {

			System.out.println("<index>");
			for (i = 0; i < ((LibraryNodePrimaryIndex) node).keyCount(); i++) {
				myKey = ((LibraryNodePrimaryIndex) node).keyAtIndex(i);
				System.out.println(myKey);
			}
			System.out.println("</index>");

			for (i = 0; i < ((LibraryNodePrimaryIndex) node).keyCount(); i++) {
				myKey = ((LibraryNodePrimaryIndex) node).keyAtIndex(i);
				if (key >= myKey) continue;
				child = ((LibraryNodePrimaryIndex) node).getChildrenAt(i);
				flag = 1;
				break;
			}
			if (flag == 0) child = ((LibraryNodePrimaryIndex) node).getChildrenAt(i);
			mySearchBook(child, key);
		}

		else{ //node is leaf now
			flag = 0;

			for (i = 0; i < ((LibraryNodeLeaf) node).bookCount(); i++) {
				myKey = ((LibraryNodeLeaf) node).bookKeyAtIndex(i);
				if (myKey == key) {
					flag = 1;
					break;
				}
			}
			if (flag == 1) {
				myBook = ((LibraryNodeLeaf) node).bookAtIndex(i);
				System.out.println("<data>");
				System.out.println("<record>" + myBook.fullName() + "</record>");
				System.out.println("</data>");
			}
			else System.out.println("No match for " + key);
		}
	}


	public void printAllLeaf(LibraryNode node){
		LibraryNode child = null;
		CengBook book;
		int myKey;

		System.out.println("<index>");
		for (int i = 0; i < ((LibraryNodePrimaryIndex) node).keyCount(); i++) {
			myKey = ((LibraryNodePrimaryIndex) node).keyAtIndex(i);
			System.out.println(myKey);
		}
		System.out.println("</index>");

		///////////////////////////////////////////////

		ArrayList<LibraryNode> children = ((LibraryNodePrimaryIndex) node).getAllChildren();

		for (int i = 0; i < children.size(); i++) {
			child = children.get(i);
			System.out.println("<data>");
			for (int j = 0; j < ((LibraryNodeLeaf) child).bookCount() ; j++) {
				book = ((LibraryNodeLeaf) child).bookAtIndex(j);
				System.out.println("<record>" + book.fullName() + "</record>");
			}
			System.out.println("</data>");
		}

	}

	public void printAllLeaf2(LibraryNode node){
		LibraryNode child = null;
		CengBook book;
		int myKey, myYear;

		System.out.println("<index>");
		for (int i = 0; i < ((LibraryNodeSecondaryIndex) node).keyCount(); i++) {
			myKey = ((LibraryNodeSecondaryIndex) node).keyAtIndex(i);
			myYear = ((LibraryNodeSecondaryIndex) node).yearAtIndex(i);
			System.out.println(myYear + "|" + myKey);
		}
		System.out.println("</index>");

		///////////////////////////////////////////////

		ArrayList<LibraryNode> children = ((LibraryNodeSecondaryIndex) node).getAllChildren();

		for (int i = 0; i < children.size(); i++) {
			child = children.get(i);
			System.out.println("<data>");
			for (int j = 0; j < ((LibraryNodeLeaf) child).bookCount() ; j++) {
				book = ((LibraryNodeLeaf) child).bookAtIndex(j);
				System.out.println("<record>" + book.fullName() + "</record>");
			}
			System.out.println("</data>");
		}

	}

	public void dfs(LibraryNode node){

		ArrayList<LibraryNode> children = ((LibraryNodePrimaryIndex) node).getAllChildren();
		LibraryNode child = children.get(0);
		int myKey;

		if(child.getType() == LibraryNodeType.Leaf) {
			printAllLeaf(node);
			return;
		}

		System.out.println("<index>");
		for (int i = 0; i < ((LibraryNodePrimaryIndex) node).keyCount(); i++) {
			myKey = ((LibraryNodePrimaryIndex) node).keyAtIndex(i);
			System.out.println(myKey);
		}
		System.out.println("</index>");


		for (int i = 0; i < children.size(); i++) {
			child = children.get(i);
			dfs(child);
		}


	}

	public void dfs2(LibraryNode node){

		ArrayList<LibraryNode> children = ((LibraryNodeSecondaryIndex) node).getAllChildren();
		LibraryNode child = children.get(0);
		int myKey, myYear;

		if(child.getType() == LibraryNodeType.Leaf) {
			printAllLeaf2(node);
			return;
		}

		System.out.println("<index>");
		for (int i = 0; i < ((LibraryNodeSecondaryIndex) node).keyCount(); i++) {
			myKey = ((LibraryNodeSecondaryIndex) node).keyAtIndex(i);
			myYear = ((LibraryNodeSecondaryIndex) node).yearAtIndex(i);
			System.out.println(myYear + "|" + myKey);
		}
		System.out.println("</index>");


		for (int i = 0; i < children.size(); i++) {
			child = children.get(i);
			dfs2(child);
		}


	}

	///////////////////////////////////////////

	public boolean isOverflow(LibraryNode node) {
		return ((LibraryNodeLeaf) node).bookCount() > 2 * LibraryNode.order;
	}

	public void addSorted(CengBook book, LibraryNode node){
		int i = 0;
		for (; i < ((LibraryNodeLeaf) node).bookCount(); i++) {
			if (book.key() >  ((LibraryNodeLeaf) node).bookKeyAtIndex(i)) continue;
			((LibraryNodeLeaf) node).addBook(i, book);
			return;
		}
		((LibraryNodeLeaf) node).addBook(i, book);
	}
	public void addSorted2(CengBook book, LibraryNode node){
		int i = 0;
		int key = book.key();
		int year = book.year();
		int myKey, myYear;
		for (; i < ((LibraryNodeLeaf) node).bookCount(); i++) {
			myKey = ((LibraryNodeLeaf) node).bookKeyAtIndex(i);
			myYear = ((LibraryNodeLeaf) node).bookYearAtIndex(i);
			if ( (year > myYear) || ((year == myYear) && (key > myKey)) ) continue;
			((LibraryNodeLeaf) node).addBook(i, book);
			return;
		}
		((LibraryNodeLeaf) node).addBook(i, book);
	}

	public LibraryNode splitLeaf(int choose, LibraryNode node){
		int i;
		CengBook book;

		if(choose == 1){
			LibraryNode lLeaf = new LibraryNodeLeaf(null);
			for (i = 0; i < LibraryNode.order; i++) {
				book = ((LibraryNodeLeaf) node).bookAtIndex(i);
				((LibraryNodeLeaf) lLeaf).addBook(i, book);
			}
			return lLeaf;
		}
		else{
			LibraryNode rLeaf = new LibraryNodeLeaf(null);
			for (i = LibraryNode.order; i < ((LibraryNodeLeaf) node).bookCount(); i++) {
				book = ((LibraryNodeLeaf) node).bookAtIndex(i);
				((LibraryNodeLeaf) rLeaf).addBook(i - LibraryNode.order, book);
			}
			return rLeaf;
		}

	}



}
