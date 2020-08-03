// Authors: Quansen Wang & Tom Zu

#include <string>
#include <iostream>
#include <vector>
#include <ctime>
#include "movies.h"

using namespace std;

// constructor sets up empty tree
Movie::Movie() : root(0) {}

// destructor that clears all nodes
Movie::~Movie() {
	clear(root);
}

void Movie::clear(Movie::film *n) {
	if (n) {
		clear(n->left);
		clear(n->right);
		delete n;
	}
}

void Movie::insert(string n, double r) {
	// create a new root
	if (!root) {
		root = new Movie::film(n,r,0);
		return;
	}

	// if the tree is not empty, use recursive helper to create nodes in the tree
	insert(n,r,root);
	return;
}

void Movie::insert(string n, double r, Movie::film *node) {
	// check if the movie is already in the tree
	if (n == node->name && r == node->rating) {
		return;
	}

	// if the n is smaller than the current name
	// if the left child DNE, create a new left child with name n
	// else insert under the left child

	// if the n is bigger than the current name
	// if the right child DNE, create a new right child with name n
	// else insert under the right child
	if (n < node->name) {
		if (node->left) {
			insert(n,r,node->left);
			return;
		} else {
			node->left = new Movie::film(n,r,node->depth+1);
			node->left->parent = node;
			return;
		}
	} else {
		if (node->right) {
			insert(n,r,node->right);
			return;
		} else {
			node->right = new Movie::film(n,r,node->depth+1);
			node->right->parent = node;
			return;
		}
	}

	return;
}

int Movie::findDepth(string n) {
	// call recursive helper function
	return getDepth(n, root);
}

int Movie::getDepth(string n, Movie::film *node) {
	if (n == node->name) {
		return node->depth;
	} else {
		if (n < node->name) {
			return getDepth(n, node->left);
		}
		return getDepth(n, node->right);
	}

	// the movie DNE, return -1
	return -1;
}

// find all nodes that contains the prefix, push to a vector, check each rating, print out the highest one
void Movie::findHighestRating(string prefix) {
	vector<Movie::film*> b;
	findHighestRatingNodes(prefix, b);
	Movie::film *temp, *best = 0;
	if(b.empty()) {return;}
	best = b[0];
	for (int i=0;i<b.size();i++) {
		temp = b[i];
		if (temp->rating > best->rating) {best = temp;}
	}
	cout << "Best movie is " << best->name << " with rating " << best->rating << endl;
}

void Movie::findHighestRatingNodes(string prefix, vector<Movie::film*> &v) {
	findHighestRatingNodes(prefix, v, root);
}


void Movie::findHighestRatingNodes(string prefix, vector<Movie::film*> &v, Movie::film *n) {
	int len = prefix.size();

	// check if the current name has the prefix
	// if the first three characters is bigger than the prefix, check the left subtree of the current node
	// if the first three characters is smaller than the prefix, check the right subtree of the current node
	if (n) {
		if (prefix.compare(n->name.substr(0,len)) == 0) {
			v.push_back(n);
			findHighestRatingNodes(prefix, v, n->right);
			return findHighestRatingNodes(prefix, v, n->left);
		} else if (prefix.compare(n->name.substr(0,len)) < 0) {
			findHighestRatingNodes(prefix, v, n->left);
		} else {findHighestRatingNodes(prefix, v, n->right);}
	}

	// if the current node is 0, do nothing and return
	return;
}

void Movie::printPreOrder() const {
	printPreOrder(root);
}

void Movie::printPreOrder(Movie::film *node) const {
	if (node) {
		cout << node->name << ", " << node->rating << ", " << node->depth << endl;
		printPreOrder(node->left);
		printPreOrder(node->right);
	}
}

int Movie::count() const {
	return count(root);
}

int Movie::count(film *n) const {
	// base case: if the current node is empty, then return 0
	if (!n) {
	    return 0;
	}

	// recursive case: return the sum of left child count and right child count + 1
	return count(n->left) + count (n->right) + 1;
}

// This will print the average time for searching a movie with W times
void Movie::search(string n, int W) const {
	clock_t t;
    double time;
    int c = count();
    t = clock();
    for(int i=0;i<W;i++) {
    	searchTree(root);
		time = (clock()-t);
		cout << "Average Time to search in single node in the tree: " << (time/c)/CLOCKS_PER_SEC << endl;
		time = 0;
		t = clock();
    }
}

void Movie::searchTree(Movie::film *root) const{
	if (!root) {
		return;
	} else {
		searchNodes(root->name,root);
		searchTree(root->left);
		searchTree(root->right);
		return;
	}
}
void Movie::searchNodes(string n, Movie::film *node) const{
	if (node) {
		if (node->name == n) {return;}
		else if (node->name > n) {searchNodes(n,node->left);}
		else {searchNodes(n,node->right);}
	} 

	return;
}

/*
// recursive function that returns a node with the name n
Movie::film* Movie::getNodeFor(string n, Movie::film *node) const{
	if (node) {
		if (node->name == n) {
			return node;
		} else if (node->name > n) {
			return getNodeFor(n, node->left);
		} else {return getNodeFor(n, node->right);}
	}

	return NULL;
}
*/


int Movie::getNumberBeforeInserted(string n) const{
	return getNumberBeforeInserted(n, root);
}

int Movie::getNumberBeforeInserted(string n, Movie::film *node) const{
	if (node) {
		if (node->name == n) {return node->num;} 
		else if (node->name > n) {return getNumberBeforeInserted(n,node->left);}
		else {return getNumberBeforeInserted(n,node->right);}
	}

	return -1;
}
