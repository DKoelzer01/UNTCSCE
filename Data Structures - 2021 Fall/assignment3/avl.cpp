#include <stdio.h>
#include <iostream>
#include "avl.hpp"
#include <string>
using namespace std;

#define IS_ROOT 0
#define IS_LEFT 1
#define IS_RIGHT 2

void balance(AvlNode * & root ); //Function to check / restore AVL balance property
AvlNode * rotate(AvlNode * & root, AvlNode * child, int rotateType); //Function to rotate / double rotate tree. Used in deletion and balance
void print(AvlNode *root); //Print function
void print(AvlNode *root, int level, int type); //Print function
void findMin (AvlNode * & root, AvlNode * & target);  //Find minimum value. Used in deletion.

/**
 * Internal method to insert into a subtree.
 * x is the item to insert.
 * t is the node that roots the subtree.
 * Set the new root of the subtree.
 */
void insert( const int & info, AvlNode * & root, AvlNode * parent, int State) //Insertion function. Balances tree prior to insertion only if the starting node is the root of the entire tree.
{
	if(root != NULL){
		if(abs(root->balanceFactor) > 1 )
			balance(root);
	}
	if (root == NULL){
		root = new AvlNode (info, NULL, NULL, parent);
		if(root->parent != NULL) {
			root->height = parent->height + 1;
		}else{
			root->height = 0;
		}
		root->state = State;
	}
    else if (info < root->element){
		root->balanceFactor--;
		insert( info, root->left, root, IS_LEFT);
	} else {
		root->balanceFactor++;
		insert( info, root->right, root, IS_RIGHT);
	}
	
}

/**
 * Internal method to remove from a subtree.
 * info is the item to remove.
 * root is the node that roots the subtree.
 * Set the new root of the subtree.
 */
void remove( const int & info, AvlNode * & root ) { //Semi-functional. Issues trying to move new node to deleted node's position.
	while(false){ //Set to true to re-enable
		if(root->element == info) {
			if(root->left == NULL && root->right == NULL) { //Target is found and does not have children.
				root = NULL;
			}
			else if(root->left == NULL) { //Target is found and has 1 child (right)
				root->right->height = root->height;
				root->right->balanceFactor = root->balanceFactor;
				root->right->parent = root->parent;
				root = root->right;
				root->left = NULL;
				root->right = NULL;
			}
			else if(root->right == NULL) { //Target is found and has 1 child (left)
				root->left->height = root->height;
				root->left->balanceFactor = root->balanceFactor;
				root->left->parent = root->parent;
				root = root->left;
				root->left = NULL;
				root->right = NULL;
			} else { //Target is found, has two children.
				AvlNode * newRoot = new AvlNode(0,NULL,NULL,NULL);
				AvlNode * & match = root;
				if(root->right != NULL){
					findMin(root->right, newRoot);
				}
				else
					newRoot = root->left;
				while(true){ //Find new root in existing tree, Remove it.
					if(match->element > newRoot->element) {
						match = match->left;
						continue;
					} else if(match->element < newRoot->element) {
						match = match->right;
						continue;
					} else {
						AvlNode * temp = match->parent;
						if(match->state == IS_LEFT) {
							temp->left == NULL;
						} else if (match->state == IS_RIGHT){
							temp->right == NULL;
						}
						match = NULL;
						match = temp;
						while(match->parent) {
							match = match->parent;
						}
					}
					break;
				}
				if(newRoot->state == IS_LEFT) {
					newRoot->parent->left == NULL;
				} else if (newRoot->state == IS_RIGHT){
					newRoot->parent->right == NULL;
				}
				newRoot->height = root->height; 
				newRoot->balanceFactor = root->balanceFactor;
				newRoot->parent = root->parent;
				if(newRoot != match->right) {
					newRoot->right = match->right;
					newRoot->right->parent = newRoot;
					newRoot->right->state = IS_RIGHT;
					match->right = NULL;
				}

				if(newRoot != match->left) {
					newRoot->left = match->left;
					newRoot->left->parent = newRoot;
					newRoot->left->state = IS_LEFT;
					match->left = NULL;
				}
				root = NULL;
				root = newRoot;
				return;
			}
		} else {
			if(root->element > info) {
				try {
					root = root->left;
				} catch (exception e) {}
			} else if (root->element < info) {
				try {
					root = root->right;
				} catch (exception e) {}
			} else {
				return;
			}
		}
	}
}


void balance(AvlNode * & root ) { //Balance function.
	switch(root->balanceFactor){
		case(2): //Right heavy
			root = rotate(root,root->right,1);
			break;
		case(-2): //Left heavy
			root = rotate(root,root->left,2);
			break;
		case(1):
		case(-1):
		case(0):
		default:
			break;
	}
}

AvlNode * rotate(AvlNode * & root, AvlNode * child, int rotateType) { //Rotate function.
	//1 Represents left, 2 represents right. Ex. 21 is Right-left rotate
	switch(rotateType){
		case(1): //LEFT
			if (root->parent != NULL) {
				child->parent = root->parent;
				switch(root->state){
					case(IS_LEFT):
						child->parent->left = child;
						child->state = IS_LEFT;
						break;
					case(IS_RIGHT):
						child->parent->right = child;
						child->state = IS_RIGHT;
						break;
					case(IS_ROOT):
						child->state = IS_ROOT;
					default:
						break;
				}
			} else {
				child->parent = NULL;
				child->state = IS_ROOT;
			}
			root->parent = child;
			root->right = (child->left != NULL) ? child->left : NULL;
			child->left = root;
			root->state = IS_LEFT;
			
			if(root->balanceFactor == 2) {
				root->balanceFactor-=2;
				child->balanceFactor--;
				root->height++;
				child->height--;
			} else {
				root->balanceFactor = 0;
				child->balanceFactor = 0;
			}
			return child;
		case(2): //RIGHT
			if (root->parent != NULL) {
				child->parent = root->parent;
				switch(root->state){
					case(IS_LEFT):
						child->parent->left = child;
						child->state = IS_LEFT;
						break;
					case(IS_RIGHT):
						child->parent->right = child;
						child->state = IS_RIGHT;
						break;
					case(IS_ROOT):
						child->state = IS_ROOT;
					default:
						break;
				}
			} else {
				child->parent = NULL;
				child->state = IS_ROOT;
			}
			root->parent = child;
			root->left = (child->right != NULL) ? child->right : NULL;
			child->right = root;
			root->state = IS_RIGHT;
			
			if(root->balanceFactor == -2) {
				root->balanceFactor+=2;
				child->balanceFactor++;
				root->height++;
				child->height--;
			} else {
				root->balanceFactor = 0;
				child->balanceFactor = 0;
			}
			return child;
		case(12):
			rotate(root, child, 1);
			rotate(root, child, 2);
			break;
		case(21):
			rotate(root, child, 2);
			rotate(root, child, 1);
			break;
		case(11):
			rotate(root, child, 1);
			rotate(root, child, 1);
			break;
		case(22):
			rotate(root, child, 2);
			rotate(root, child, 2);
			break;
		default:
			break;
	}
	
}

void findMin (AvlNode * & root, AvlNode * & target) { //Find min function. Traverse tree to the left until no more nodes found.
	AvlNode * wN = root;
	while(wN->left)
		wN = wN->left;
	target = wN;
}


/*
 * Print methods, do not change
 */
void print(AvlNode *root, int level, int type) {
  if (root == NULL) {
    return;
  }
  if (type == IS_ROOT) {
    std::cout << root -> element << "\n";
  } else {
    for (int i = 1; i < level; i++) {
      std::cout << "| ";
    }
    if (type == IS_LEFT) {
      std::cout << "|l_" << root -> element << "\n";
    } else {
      std::cout << "|r_" << root -> element << "\n";
    }
  }
  if (root -> left != NULL) {
    print(root -> left, level + 1, IS_LEFT);
  }
  if (root -> right != NULL) {
    print(root -> right, level + 1, IS_RIGHT);
  }
}
void print(AvlNode *root) {
  print(root, 0, IS_ROOT);
}
/*
 * END Print methods, do not change
 */


/* 
 * Main method, do not change
 */
int main(int argc, const char * argv[]) {
  AvlNode *root = NULL;
  std::string filename = argv[1];
  freopen(filename.c_str(), "r", stdin);
  std::string input;
  int data;
  while(std::cin >> input){
    if (input == "insert"){
      std::cin>>data;
      insert(data, root, NULL,IS_ROOT);
    } else if(input == "delete"){
      std::cin>>data;
      remove(data, root);
    } else if(input == "print"){
      print(root);
      std::cout << "\n";
    } else{
      std::cout<<"Data not consistent in file";
      break;
    }
  }
  return 0;
}
/*
 * END main method
 */
