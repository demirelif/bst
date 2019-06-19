/**
 * Title: Binary Search Trees
 * Author: Elif Demir
 * ID: 21601571
 * Section: 1
 * Assignment: 2
 * Description: this cpp file contains the constructors of the bst node and its properties */
#include <stdio.h>
#include "BSTNode.h"
BSTNode::BSTNode(){
    leftChildPtr = NULL;
    rightChildPtr = NULL;
    marked = 0;
}

BSTNode::BSTNode(const int & nodeItem, BSTNode *left, BSTNode *right)
:item(nodeItem),leftChildPtr(left),rightChildPtr(right){
    item = nodeItem;
    leftChildPtr = left;
    rightChildPtr = right;
    marked = 0;
}
/*
BSTNode::~BSTNode(){
    delete leftChildPtr;
    delete rightChildPtr;
    leftChildPtr = NULL;
    rightChildPtr = NULL;
}
*/
int item;
BSTNode *leftChildPtr;
BSTNode *rightChildPtr;
