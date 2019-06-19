/**
 * Title: Binary Search Trees
 * Author: Elif Demir
 * ID: 21601571
 * Section: 1
 * Assignment: 2
 * Description: header file for the binary search tree */

#ifndef BST_h
#define BST_h
#include "BSTNode.h"

class BST{ // right larger, left smaller 
public:
    // constructions
    BST();
    BST( const int& rootItem );
    //BST( BSTNode* nodePtr );  // protected constr.
    BST( const int& rootItem, BST& leftTree, BST& rightTree );
    BST( const BST& tree );
    
    // destructor
    ~BST();
    
    // public functions
    void insertItem( int key );
    void deleteItem( int key );
    BSTNode* retrieveItem( int key );
    int* inorderTraversal( int& length );
    bool containsSequence(int* seq, int length);
    int countNodesDeeperThan(int level);
    int maxBalancedHeight();

protected:
    void destroyTree(BSTNode*& treePtr); 
    void copyTree(BSTNode *treePtr, BSTNode*& newTreePtr) const; 
    void attachLeftSubtree(BST& leftTree);
    void attachRightSubtree(BST& rightTree);
    void insertItemHelper( BSTNode *& treePtr, const int& newItem );
    void deleteItemHelper( BSTNode *& treePrt, int& searchKey );
    void deleteNodeItem( BSTNode *& nodePtr );
    void processLeftmost( BSTNode *& nodePtr, int& treeItem );
    void retrieveItemHelper(BSTNode *treePtr, int key, BSTNode*& treeItem );
    void inorderTraversalHelper( BSTNode *& treePtr, int *& array, int& size );
    void findTheSequenceRoot( BSTNode*& treePtr, int& first, int& last, int *& array, int& size);
    void countNodesDeeperThanHelper(BSTNode*& treePtr, int& level, int& curLevel, int& counter);
    bool isBalanced( BSTNode*& treePtr, int& extra);
    void maxBalancedHeightHelper( BSTNode*& treePtr, int& soFar  );
    int getHeight( BSTNode*& treePtr);
    int assumedDeletion( BSTNode*& treePtr, int& direction );
    int heightAfterDeletion(BSTNode*& treePtr );
    bool isEmpty();

private:
    // proporties
    BSTNode* root; 
};
#endif /* BST_h */
