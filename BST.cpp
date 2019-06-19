/**
 * Title: Binary Search Trees
 * Author: Elif Demir
 * ID: 21601571
 * Section: 1
 * Assignment: 2
 * Description: this cpp file contains the properties and methods of the binary search tree */

#include <stdio.h>
#include "BST.h"
#include "BSTNode.h"
#include <iostream>
#include <algorithm>
using namespace std;

// default constructor - empty tree
BST::BST(){
    root = NULL;
}

// constructor - tree with only the root
BST::BST(const int& rootItem){
    root = new BSTNode(rootItem,NULL,NULL);
}

// constructor
BST::BST( const int& rootItem, BST& leftTree, BST& rightTree ){
    root = new BSTNode(rootItem, NULL, NULL);
    attachLeftSubtree(leftTree);
    attachRightSubtree(rightTree);
}

// copy constructor
BST::BST( const BST& tree ){
    copyTree(tree.root, root);
}

// destructor
BST :: ~BST(){
    destroyTree(root);
}

// functions
void BST::destroyTree(BSTNode*& treePtr){
    if ( treePtr != NULL ){
        destroyTree(treePtr->leftChildPtr);
        destroyTree(treePtr->rightChildPtr);
        delete treePtr;
        treePtr = NULL;
    }
}

void BST::copyTree(BSTNode *treePtr, BSTNode*& newTreePtr) const{
    if ( treePtr != NULL ){
        newTreePtr = new BSTNode(treePtr -> item, NULL, NULL);
        copyTree(treePtr->leftChildPtr, newTreePtr->leftChildPtr);
        copyTree(treePtr->rightChildPtr, newTreePtr->rightChildPtr);
    }
    else
        newTreePtr = NULL;
}

void BST::attachLeftSubtree(BST& leftTree){
    if ( !isEmpty() && ( root->leftChildPtr == NULL) )
    {
        root->leftChildPtr = leftTree.root;
        leftTree.root = NULL;
    }
}

void BST::attachRightSubtree(BST& rightTree){
    if (!isEmpty() && (root->rightChildPtr==NULL))
    {
        root->rightChildPtr = rightTree.root;
        rightTree.root = NULL;
    }
}

bool BST::isEmpty(){
    return root == NULL;
}

// insertion
void BST::insertItem( int key ){
    insertItemHelper( root, key );
}

void BST::insertItemHelper(BSTNode *& treePtr, const int& newItem){
    if ( treePtr == NULL ){
        treePtr = new BSTNode( newItem, NULL, NULL ); // create a node in an empty tree
        if ( treePtr == NULL ){
            // exception 
        }
    }
    // search for insertion position
    else if ( newItem < treePtr -> item ){
        insertItemHelper( treePtr -> leftChildPtr, newItem );
    }
    else {
        insertItemHelper( treePtr -> rightChildPtr, newItem );
    }
}

// deletion
void BST::deleteItem(int key){
    deleteItemHelper(root, key);
}

void BST::deleteItemHelper(BSTNode *& treePtr, int& key ){
    if ( treePtr == NULL ){
    // empty tree - exception
    }
    else if ( key == treePtr -> item )
        deleteNodeItem( treePtr ); // ??
    else if ( key < treePtr -> item )
        deleteItemHelper( treePtr -> leftChildPtr, key );
    else
        deleteItemHelper( treePtr -> rightChildPtr, key );
}

void BST::deleteNodeItem(BSTNode *& nodePtr){
    BSTNode *delPtr;
    int replacementItem = 0;
    
    // test for leaf
    if ( ( nodePtr -> leftChildPtr == NULL ) && ( nodePtr -> rightChildPtr == NULL ) )
    {
        delete nodePtr;
        nodePtr = NULL;
    }
    // test for no left child
    else if ( nodePtr -> leftChildPtr == NULL ){
        delPtr = nodePtr;
        nodePtr = nodePtr -> rightChildPtr;
        delPtr -> rightChildPtr = NULL;
        delete delPtr;
    }
    
    // test for no right child
    else if ( nodePtr -> rightChildPtr == NULL ){
        delPtr = nodePtr;
        nodePtr = nodePtr -> leftChildPtr;
        delPtr -> leftChildPtr = NULL;
        delete delPtr; 
    }
    // two children
    else {
        processLeftmost( nodePtr -> rightChildPtr, replacementItem);
        nodePtr -> item = replacementItem;
    }
}

void BST::processLeftmost( BSTNode *& nodePtr, int& treeItem ){
    if ( nodePtr -> leftChildPtr == NULL ){
        treeItem = nodePtr -> item;
        BSTNode *delPtr = nodePtr;
        nodePtr = nodePtr -> rightChildPtr;
        delPtr -> rightChildPtr = NULL;
        delete delPtr;
    }
    else
        processLeftmost( nodePtr -> leftChildPtr, treeItem );
}

// retrive
BSTNode* BST::retrieveItem(int key){
    BSTNode* treeItem;
    retrieveItemHelper( root, key, treeItem );
    return treeItem;
}

void BST::retrieveItemHelper(BSTNode *treePtr, int key, BSTNode*& treeItem){
    if ( treePtr == NULL ){
        treeItem = NULL;
    }
    else if ( key == treePtr -> item ){
        treeItem = treePtr; 
    }

    else if ( key < treePtr -> item ){
        retrieveItemHelper(treePtr-> leftChildPtr, key, treeItem);
    }
    else{
        retrieveItemHelper(treePtr-> rightChildPtr, key, treeItem);
    }
}

// traversal
int* BST::inorderTraversal(int& length){
    int *traversal = new int[100];
    length = 0; 
    inorderTraversalHelper(root, traversal, length);
    return traversal;
}

void BST::inorderTraversalHelper( BSTNode *& treePtr, int *& array, int& size){
    if ( treePtr != NULL ){
        inorderTraversalHelper(treePtr->leftChildPtr, array, size);
        array[size] = treePtr -> item;
        size++;
        inorderTraversalHelper(treePtr->rightChildPtr, array, size);
    }
}

// contains sequence
bool BST::containsSequence( int* seq, int length ){
    int *treeArray = new int[100];
    int size = 0;
    int smallest = seq[0];
    int biggest = seq[length-1];
    findTheSequenceRoot( root, smallest, biggest, treeArray, size );
    
    if ( length != size ){
        delete[] treeArray;
        return false;
    }
    
    else {
        for ( int i = 0; i < size; i++ ){
            if ( seq[i] != treeArray[i] ){
                delete[] treeArray;
                return false;
            }
        }
        delete[] treeArray;
        return true;
    }
}

void BST::findTheSequenceRoot( BSTNode*& treePtr, int& smallest, int& biggest, int *& array, int& size ){
    if ( treePtr != NULL){
        cout << "visited: " << treePtr -> item << endl;
        if ( (treePtr -> item <= biggest) && (treePtr -> item >= smallest) ){ // then the root is inside
            findTheSequenceRoot(treePtr->leftChildPtr, smallest, biggest, array, size);
            array[size] = treePtr -> item;
            size++;
            findTheSequenceRoot(treePtr->rightChildPtr, smallest, biggest, array, size);
        }
        else if ( treePtr -> item > biggest ){
            findTheSequenceRoot( treePtr->leftChildPtr, smallest, biggest, array, size );
        }
        else {
            findTheSequenceRoot( treePtr->rightChildPtr, smallest, biggest, array, size );
        }
    }
}

// counts deeper than
int BST::countNodesDeeperThan( int level ){
    int counter = 0;
    int curLevel = 0;
    countNodesDeeperThanHelper(root, level, curLevel, counter);
    return counter;
}

void BST::countNodesDeeperThanHelper( BSTNode*& treePtr, int& level, int& curLevel, int& counter ){
    if ( treePtr != NULL ){
        curLevel++;
        if ( curLevel >= level ){
            counter++;
        }
        int temp = curLevel;
        countNodesDeeperThanHelper( treePtr->leftChildPtr, level, curLevel, counter);
        curLevel = temp; 
        countNodesDeeperThanHelper( treePtr->rightChildPtr, level, curLevel, counter);
    }
}

// max balanced height
int BST::maxBalancedHeight(){
    int counter = 0; // temp
    maxBalancedHeightHelper( root, counter );
    return heightAfterDeletion( root );
}


void BST::maxBalancedHeightHelper( BSTNode*& treePtr, int& soFar ){
    if ( treePtr != NULL ){
        int extra = 0;
        maxBalancedHeightHelper( treePtr->leftChildPtr, soFar );
        maxBalancedHeightHelper( treePtr->rightChildPtr, soFar );
        if ( !isBalanced(treePtr, extra) ) {
            extra = (extra > 0);
            soFar = soFar + assumedDeletion( treePtr, extra );
        }
    }
}

int BST:: heightAfterDeletion(BSTNode*& treePtr ){
    return getHeight(treePtr);
}

bool BST::isBalanced( BSTNode*& treePtr, int& extra){
    extra = getHeight( treePtr->leftChildPtr ) - getHeight( treePtr->rightChildPtr );
    if ( abs(extra) <= 1 ){
        return true;
    }
    return false;
}

int BST:: assumedDeletion( BSTNode*& treePtr, int& direction ){ // left 1, right 0
    int deletedNodes = 0;
    if ( direction == 1 ){
        treePtr = treePtr -> leftChildPtr;
        if ( treePtr -> leftChildPtr != NULL ){
            ( treePtr -> leftChildPtr ) -> marked = 1;
            deletedNodes++;
        }
        if ( treePtr -> rightChildPtr != NULL ){
            ( treePtr -> rightChildPtr ) -> marked = 1;
            deletedNodes++;
        }
    }
    else if ( direction == 0 ){
        if ( treePtr -> leftChildPtr != NULL ){
            ( treePtr -> leftChildPtr ) -> marked = 1;
            deletedNodes++;
        }
        if ( treePtr -> rightChildPtr != NULL ){
            ( treePtr -> rightChildPtr ) -> marked = 1;
            deletedNodes++;
        }
    }
    return deletedNodes;
}


int BST::getHeight( BSTNode*& treePtr){
    int height = 0;
    if ( treePtr != NULL && (treePtr -> marked == 0) ){
        height = 1 + max( getHeight(treePtr->leftChildPtr), getHeight(treePtr -> rightChildPtr) );
    }
    return height;
}

