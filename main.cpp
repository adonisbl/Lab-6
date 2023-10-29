#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include "ArgumentManager.h"
using namespace std;

int max(int a, int b) {
	if (a > b)
		return a;
	else
		return b;
}

struct node {
	int data;
	node* left;
	node* right;
	int height;
	node(int d) {
		data = d;
		left = nullptr;
		right = nullptr;
		height = 0;
	}
};

class avlTree {
private:
  node* root;

public:
  avlTree() { root = nullptr; }

  void add(int data) { root = insert(root, data); }

  node* getRoot() { return root; }

	node* insert(node* t, int x) {
		if (t == nullptr)
			t = new node(x);
		else if (x < t->data) {
			t->left = insert(t->left, x);
			if (bFactor(t) == 2) {
				if (x < t->left->data)
					t = singleRight(t);
				else
					t = leftRight(t);
			}
		}
		else if (x > t->data) {
			t->right = insert(t->right, x);
			if (bFactor(t) == -2) {
				if (x > t->right->data)
					t = singleLeft(t);
				else
					t = rightLeft(t);
			}
		}
		t->height = max(height(t->left), height(t->right)) + 1;
		return t;
	}

	node* singleRight(node* t) {
		node* u = t->left;
		t->left = u->right;
		u->right = t;
		t->height = max(height(t->left), height(t->right)) + 1;
		u->height = max(height(u->left), height(u->right)) + 1;
		return u;
	}

	node* singleLeft(node* t) {
		node* u = t->right;
		t->right = u->left;
		u->left = t;
		t->height = max(height(t->right), height(t->left)) + 1;
		u->height = max(height(u->right), height(u->left)) + 1;
		return u;
	}

	node* leftRight(node* t) {
		t->left = singleLeft(t->left);
		return singleRight(t);
	}

	node* rightLeft(node* t) {
		t->right = singleRight(t->right);
		return singleLeft(t);
	}

	int height(node* cu) {
		if (cu == nullptr)
			return -1;
		else
			return cu->height;
	}

	int bFactor(node* cu) {
		return (height(cu->left) - height(cu->right));
	}

	int xheight(node* node)
	{
	    if (node == NULL)
	        return 0;
	    else {
	        /* compute the height of each subtree */
	        int lheight = xheight(node->left);
	        int rheight = xheight(node->right);
	 
	        /* use the larger one */
	        if (lheight > rheight) {
	            return (lheight + 1);
	        }
	        else {
	            return (rheight + 1);
	        }
	    }
	}

	void printLevelOrder(node* root,ofstream &output)
	{
	    int h = xheight(root);
	    int i;
	    for (i = 1; i <= h; i++)
	        printCurrentLevel(root, i, output);
	}

 
/* Print nodes at a current level */
	void printCurrentLevel(node* root, int level, ofstream &out)
	{
	    if (root == NULL)
	        return;
	    if (level == 1)
	        out << root->data << " ";
	    else if (level > 1) {
	        printCurrentLevel(root->left, level - 1, out);
	        printCurrentLevel(root->right, level - 1,out);
	    }
	}
};

int main(int argc, char *argv[]) {
  avlTree t;
	string in, firstLn;
	
	ArgumentManager am(argc,argv);
  ifstream input(am.get("input"));
  ofstream output(am.get("output"));
	

	/*
	ifstream input("input1.txt");
  ofstream output("output1.txt");
	*/
	getline(input, firstLn);
	int numNodes = stoi(firstLn);
	cout << numNodes<<endl;

	while (getline(input, in))
	{
		in.erase(remove(in.begin(), in.end(), '\n'), in.end());
		in.erase(remove(in.begin(), in.end(), '\r'), in.end());
		in.erase(remove(in.begin(), in.end(), ' '), in.end());
		t.add(stoi(in));
	}
	t.printLevelOrder(t.getRoot(),output);
}