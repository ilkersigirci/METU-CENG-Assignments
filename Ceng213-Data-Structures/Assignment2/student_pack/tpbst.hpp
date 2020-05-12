#ifndef TWOPHASEBST_H
#define TWOPHASEBST_H

#include <iostream>
#include <string>
#include <stack>
#include <list>
// do not add any other library.
// modify parts as directed by assignment text and comments here.

template <class T>
class TwoPhaseBST {
private: //do not change
    struct SecondaryNode {
        std::string key;
        T data;
        SecondaryNode *left;
        SecondaryNode *right;

        SecondaryNode(const std::string &k, const T &d, SecondaryNode *l, SecondaryNode *r);
    };

    struct PrimaryNode {
        std::string key;
        PrimaryNode *left;
        PrimaryNode *right;
        SecondaryNode *rootSecondaryNode;

        PrimaryNode(const std::string &k, PrimaryNode *l, PrimaryNode *r, SecondaryNode *rsn);
    };

public: // do not change.
    TwoPhaseBST();
    ~TwoPhaseBST();

    TwoPhaseBST &insert(const std::string &primaryKey, const std::string &secondaryKey, const T &data);
    TwoPhaseBST &remove(const std::string &primaryKey, const std::string &secondaryKey);
    TwoPhaseBST &print(const std::string &primaryKey = "", const std::string &secondaryKey = "");
    T *find(const std::string &primaryKey, const std::string &secondaryKey);

private: // you may add your own utility member functions here.
    void destructNode(PrimaryNode * &root);
    void destructNode(SecondaryNode * &root);

    void insert_helper(PrimaryNode * primary, PrimaryNode* & rootP); //for insert
    void insert_helper(SecondaryNode * secondary, SecondaryNode* & rootS);

    PrimaryNode * findPrimary(const std::string &primaryKey,PrimaryNode* rootP); //for find
    SecondaryNode * findSecondary(const std::string &secondaryKey,SecondaryNode* rootS);

    SecondaryNode * findMin(SecondaryNode * rootS); //for delete
    void deleteSecondary(const std::string & key, SecondaryNode* & rootS); 

    PrimaryNode * findMax(PrimaryNode * rootP); //for print
    SecondaryNode * findMax(SecondaryNode * rootS);
    void printPrimary(PrimaryNode * rootP, PrimaryNode * max);
    void printSecondary(SecondaryNode * rootS, SecondaryNode * max);


private: // do not change.
    PrimaryNode *root; //designated root.

    // do not provide an implementation. TwoPhaseBST's are not copiable.
    TwoPhaseBST(const TwoPhaseBST &);
    const TwoPhaseBST &operator=(const TwoPhaseBST &);
};

template <class T>
TwoPhaseBST<T>::SecondaryNode::SecondaryNode(const std::string &k, const T &d, SecondaryNode *l, SecondaryNode *r)
        : key(k), data(d), left(l), right(r) {}

template <class T>
TwoPhaseBST<T>::PrimaryNode::PrimaryNode(const std::string &k, PrimaryNode *l, PrimaryNode *r, SecondaryNode *rsn)
        : key(k), left(l), right(r), rootSecondaryNode(rsn) {}

template <class T>
TwoPhaseBST<T>::TwoPhaseBST() : root(NULL) {}

template <class T>
TwoPhaseBST<T>::~TwoPhaseBST() {
    destructNode(root);
}
/***************************************************************************************************/
/***************************************************************************************************/

template <class T>
typename TwoPhaseBST<T>::PrimaryNode * TwoPhaseBST<T>::findPrimary(const std::string &primaryKey,PrimaryNode * rootP)
{
    if(rootP == NULL) return NULL;
    else if(primaryKey < rootP->key) return findPrimary(primaryKey, rootP->left);
    else if(primaryKey > rootP->key) return findPrimary(primaryKey, rootP->right);
    else return rootP; //found
    
}
template <class T>
typename TwoPhaseBST<T>::SecondaryNode * TwoPhaseBST<T>::findSecondary(const std::string &secondaryKey,SecondaryNode * rootS)
{
    if(rootS == NULL) return NULL;
    else if(secondaryKey < rootS->key) return findSecondary(secondaryKey, rootS->left);
    else if(secondaryKey > rootS->key) return findSecondary(secondaryKey, rootS->right);
    else return rootS; //found
}
template <class T>
void TwoPhaseBST<T>::insert_helper(PrimaryNode * primary, PrimaryNode*  & rootP)
{
    if(rootP == NULL) rootP=primary;
    else if(primary->key < rootP->key) insert_helper(primary,rootP->left);
    else if(primary->key > rootP->key) insert_helper(primary,rootP->right);
    else;
}
template <class T>
void TwoPhaseBST<T>::insert_helper(SecondaryNode * secondary, SecondaryNode*  & rootS)
{
    if(rootS == NULL) rootS = secondary;
    else if(secondary->key < rootS->key) insert_helper(secondary,rootS->left);
    else if(secondary->key > rootS->key) insert_helper(secondary,rootS->right);
    else;
}
template <class T>
typename TwoPhaseBST<T>::SecondaryNode * TwoPhaseBST<T>::findMin(SecondaryNode * rootS)
{
    if(rootS == NULL) return NULL;
    if(rootS->left == NULL) return rootS;
    return findMin(rootS->left);
}

template <class T>
void TwoPhaseBST<T>::deleteSecondary(const std::string & key, SecondaryNode* & rootS)
{
    if(rootS == NULL) return;
    else if(key < rootS->key) deleteSecondary(key, rootS->left);
    else if(key > rootS->key) deleteSecondary(key, rootS->right);
    else if(rootS->left != NULL && rootS->right != NULL)
    {
        /* rootS->key = rightMin->key; 
        rootS->data = rightMin->data; //FIXME: data kopyala
        SecondaryNode newSecond(rightMin->key, rightMin->data, rootS->left, rootS->right);
        rootS = & newSecond; */
        // FIXED
        SecondaryNode * rightMin = findMin(rootS->right);        
        SecondaryNode * newSecond = new SecondaryNode(rightMin->key, rightMin->data, rootS->left, rootS->right);
        delete rootS;
        rootS = newSecond;
        deleteSecondary(rightMin->key, rootS->right);
    }
    else
    {
        SecondaryNode * old = rootS;
        rootS = (rootS->left != NULL) ? rootS->left : rootS->right;
        delete old;
    }  
}
template <class T>
typename TwoPhaseBST<T>::PrimaryNode * TwoPhaseBST<T>::findMax(PrimaryNode * rootP)
{
    if(rootP == NULL) return NULL;
    if(rootP->right == NULL) return rootP;
    return findMax(rootP->right);
}
template <class T>
typename TwoPhaseBST<T>::SecondaryNode * TwoPhaseBST<T>::findMax(SecondaryNode * rootS)
{
    if(rootS == NULL) return NULL;
    if(rootS->right == NULL) return rootS;
    return findMax(rootS->right);
}

template <class T>
void TwoPhaseBST<T>::printSecondary(SecondaryNode * rootS, SecondaryNode * max)
{
    char quot = '"';
    if(rootS == NULL){return;}
    printSecondary(rootS->left, max);
    std::cout << quot << rootS->key << quot << " : " << quot << rootS->data << quot;
    if(rootS->key != max->key) std::cout << ", ";
    printSecondary(rootS->right, max);
}

template <class T>
void TwoPhaseBST<T>::printPrimary(PrimaryNode * rootP, PrimaryNode * max)
{
    char quot = '"';
    if(rootP == NULL){return;}
    printPrimary(rootP->left, max);
    std::cout << quot << rootP->key << quot << " : ";
    std::cout << "{";
    printSecondary(rootP->rootSecondaryNode, findMax(rootP->rootSecondaryNode));    
    std::cout << "}";
    if(rootP->key != max->key) std::cout << ", ";
    printPrimary(rootP->right, max);
}
/***************************************************************************************************/
/***************************************************************************************************/

template <class T>
TwoPhaseBST<T> &
TwoPhaseBST<T>::insert(const std::string &primaryKey, const std::string &secondaryKey, const T &data) {
    
    SecondaryNode * newSecondary = new SecondaryNode(secondaryKey, data, NULL, NULL);    
    PrimaryNode * found = findPrimary(primaryKey, this->root);
    
    if(found == NULL){
        PrimaryNode * newPrimary = new PrimaryNode(primaryKey, NULL, NULL, newSecondary);
        insert_helper(newPrimary, this->root);
    }
    else
    {
        insert_helper(newSecondary,found->rootSecondaryNode);
    }
    return *this;
    
}

template <class T>
TwoPhaseBST<T> &
TwoPhaseBST<T>::remove(const std::string &primaryKey, const std::string &secondaryKey) {
    PrimaryNode * primary = findPrimary(primaryKey, this->root);
    if(primary == NULL) return *this;
    SecondaryNode * secondary = findSecondary(secondaryKey, primary->rootSecondaryNode);
    if(secondary == NULL) return *this;

    deleteSecondary(secondary->key, primary->rootSecondaryNode);
    return *this;
}

template <class T>
TwoPhaseBST<T> &TwoPhaseBST<T>::print(const std::string &primaryKey, const std::string &secondaryKey) {
    
    char quot = '"';
    if(primaryKey == "" && secondaryKey == "")
    {
        //printALL
        std::cout << "{";
        printPrimary(this->root, findMax(this->root));
        std::cout << "}" << std::endl;
    }
    else if(primaryKey == "" && secondaryKey != "") return *this;
    else if(primaryKey != "" && secondaryKey == "")
    {
        //print secondaryTree of primaryKey
        PrimaryNode * primary = findPrimary(primaryKey, this->root);
        if(!primary)
        {
            std::cout << "{}" << std::endl;
            return *this;
        }
        std::cout << "{";
        std::cout << quot << primary->key << quot << " : ";
        std::cout << "{";
        printSecondary(primary->rootSecondaryNode, findMax(primary->rootSecondaryNode));
        std::cout << "}";
        std::cout << "}" << std::endl;
    }
    else if(primaryKey != "" && secondaryKey != "")
    {
        //print specific data
        PrimaryNode * primary = findPrimary(primaryKey, this->root);
        if(!primary)
        {
            std::cout << "{}" << std::endl;
            return *this;
        }
        SecondaryNode * secondary = primary->rootSecondaryNode;
        SecondaryNode * foundSecondary = findSecondary(secondaryKey, secondary);
        if(!foundSecondary)
        {
            std::cout << "{}" << std::endl;
            return *this;
        }
        std::cout << "{";
        std::cout << quot << primary->key << quot << " : ";
        std::cout << "{" << quot << foundSecondary->key << quot << " : " << quot << foundSecondary->data << quot << "}";
        std::cout << "}" << std::endl;
    }
    else;

    return *this;
}

template <class T>
T *TwoPhaseBST<T>::find(const std::string &primaryKey, const std::string &secondaryKey) {

    PrimaryNode * primary = findPrimary(primaryKey, this->root);
    if(primary == NULL) return NULL;
    
    SecondaryNode * secondary = findSecondary(secondaryKey, primary->rootSecondaryNode);
    if(secondary == NULL) return NULL;

    return &(secondary->data);  

}

template <class T>
void TwoPhaseBST<T>::destructNode(TwoPhaseBST::PrimaryNode * &root)
{
    if (root == NULL)
        return;

    destructNode(root->left);
    destructNode(root->right);

    destructNode(root->rootSecondaryNode);

    delete root;

    root = NULL;
}

template <class T>
void TwoPhaseBST<T>::destructNode(TwoPhaseBST::SecondaryNode * &root)
{
    if (root == NULL)
        return;

    destructNode(root->left);
    destructNode(root->right);

    delete root;

    root = NULL;
}
#endif //TWOPHASEBST_H


