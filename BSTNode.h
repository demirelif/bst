/**
 * Title: Binary Search Trees
 * Author: Elif Demir
 * ID: 21601571
 * Section: 1
 * Assignment: 2
 * Description: header file for the bst node */
#ifndef BSTNode_h
#define BSTNode_h
class BSTNode{
private:
    // constructors
    BSTNode();
    BSTNode(const int & nodeItem, BSTNode *left = NULL, BSTNode *right = NULL );
    ~BSTNode();
    // properties 
    int item;
    int marked; 
    BSTNode *leftChildPtr;
    BSTNode *rightChildPtr;
    
    friend class BST;
};
#endif /* BSTNode_h */
