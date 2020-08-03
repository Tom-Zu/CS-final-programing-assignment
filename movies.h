// author: Quansen Wang

#ifndef MOVIES_H
#define MOVIES_H

#include <string>
// Authors: Quansen Wang & Tom Zu

#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

class Movie
{
public:
	Movie();
	~Movie();

	void insert(string n, double r); // create a node with name n and rating r, call insert helper function
	int findDepth(string n); // return the depth of the movie with name n
	void findHighestRating(string prefix);
	void printPreOrder() const;
	int count() const; // return the total number of nodes in the tree
	void search(string n, int W) const;
	int getNumberBeforeInserted(string n) const;
private:
	struct film
	{
		string name; // the name of the movie
		double rating; // the rating of the movie
		int depth; // the depth of the movie (aka, the number of nodes visited before insert this key)
		int num; // the total number of nodes before insert the key
		film(string n="", double r=0.0, int d=0) : name(n), rating(r),depth(d),parent(0),left(0),right(0) {}

		film *parent, *left, *right;
	};

	film *root;

	// utility function
	int getDepth(string n, film *node); // return the depth of the node by calculating the depth of its parent
	void clear(film *n); // destructor helper
	void insert(string n, double r, film *node); // insert a node with name n, rating r, 
											  // depth is determined by the function getDepth()
	// film* findHighestRating(string prefix, film *node);
	void findHighestRatingNodes(string prefix, vector<film *> &v);
	void findHighestRatingNodes(string prefix, vector<film *> &v, film *n);
	void printPreOrder(film *node) const;
	int count(film *n) const;
	film* getNodeFor(string n, film *node) const;
	int getNumberBeforeInserted(string n, film *node) const;

	void searchTree(film *root) const;
	void searchNodes(string name,film *root) const;
};

#endif