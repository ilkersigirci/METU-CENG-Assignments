#ifndef _BIN_SEARCH_TREE_H_
#define _BIN_SEARCH_TREE_H_

#include <cstddef>
#include <ostream>
#include <string>
#include <sstream>

class ItemNotFound { };

template <typename Key, typename Object>
class Tree 
{
  private:
    struct BinaryNode //node definition: a nested type
    {
      Key key;
      Object data;
      BinaryNode * left;
      BinaryNode * right;

      BinaryNode(const Key &, const Object &,
                 BinaryNode *, BinaryNode *);
    };

  public:
    Tree( ); //empty tree
    ~Tree( ); //reclaim all dyn allocated mem

    //implement these two functions
    void insert(const Key &, const Object &); //to insert new key,item
    void modify(const Key &, const Object &); //update data@key

  public:
    const Object & find(const Key &) const /*throw(ItemNotFound)*/;
    void getSizeAndHeight(int &, int &) const; //implement at home

  private:
    BinaryNode * root; //designated root
 
    /* private utility functions */
    void makeEmpty(BinaryNode * &);
    BinaryNode * find(const Key &, BinaryNode *) const;
    //add more functions if you need to

  private: //not copiable: do not provide an implementation (to issue comp. error)
    Tree(const Tree &);
    const Tree & operator=(const Tree &);

  private:
    void toString(BinaryNode *, std::stringstream &) const;
    void insert_helper(BinaryNode*, BinaryNode* &);

  template <typename K, typename O>
  friend std::ostream& operator<<(std::ostream &, const Tree<K,O> &);
};

//node constructor
template <typename K, typename O>
Tree<K,O>::BinaryNode::
BinaryNode(const K & _k, const O & _d,
           BinaryNode * _l, BinaryNode * _r)
  : key(_k), data(_d), left(_l), right(_r)
{
}

//default constructor
template <typename K, typename O>
Tree<K,O>::Tree( )
  : root(NULL)
{
}

//destructor
template <typename K, typename O>
Tree<K,O>::~Tree( )
{
  makeEmpty(root);
}

//private utility function for destructor
template <typename K, typename O>
void //inlab
Tree<K,O>::makeEmpty(BinaryNode * & t)
{
  if (t != NULL)
  {
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
  }

  t = NULL;
}

template <typename K, typename O>
void Tree<K,O>::insert_helper(BinaryNode* x, BinaryNode* & root){  // & root kismi onemli
  if(root == NULL){
    root = x;
  }
  else if(x -> key < root -> key){
    insert_helper(x, root -> left);
  }
  else if(x -> key > root -> key){
    insert_helper(x, root -> right);
  }
  else ;


}

//public function to insert into BST, implement
template <typename K, typename O>
void
Tree<K,O>::insert(const K & k, const O & x)
{
  BinaryNode* found = find(k, root);
  if(found){
    found -> data = x;
    return ;
  }
  BinaryNode* new_node = new BinaryNode(k, x, NULL, NULL);
  insert_helper(new_node, root);
}

//public function to modify an Object if its Key exists, implement
template <typename K, typename O>
void
Tree<K,O>::modify(const K & key, const O & newdata)
{
  insert(key,newdata);
}

//public function to search elements
template <typename K, typename O>
const O &
Tree<K,O>::find(const K & key) const /*throw(ItemNotFound)*/
{
  BinaryNode * node = find(key, root);

  if (node == NULL)
  {
    throw ItemNotFound();
  }
  else
  {              
    return node->data;
  }
}

/*
 * private utility function to search elements
 *
 */
template <typename K, typename O>
typename Tree<K,O>::BinaryNode *
Tree<K,O>::find(const K & key, BinaryNode * t) const
{
  if (t == NULL)
  {
    return NULL;
  }
  else if (key < t->key)
  {
    return find(key, t->left);
  }
  else if (t->key < key)
  {
    return find(key, t->right);
  }
  else //found
  {
    return t;
  }
}

//private toString function
template <typename K, typename O>
void
Tree<K,O>::toString(BinaryNode * t, std::stringstream & ss) const
{
  if (t == NULL)
  {
	  ;
  }

  else
  {
    toString(t->left, ss);
    ss << t->key << " : " << t->data << ", ";
    toString(t->right, ss);
  }
}

//friend function defined here this time
template <typename K, typename O>
std::ostream &
operator<<(std::ostream & out, const Tree<K,O> & tree)
{
  /*
   * empty tree is printed as "{ }"
   * non-empty trees of size n are printed as
   * "{key1 : object1, key2 : object2, ..., keyn : objectn}" 
   */
  std::stringstream ss;
  ss << "{";
  tree.toString(tree.root, ss); 
  out << (tree.root == NULL ? ss.str()+" " : 
          ss.str().substr(0, ss.str().size()-2)) 
      << "}";
  return out;
}

#endif
