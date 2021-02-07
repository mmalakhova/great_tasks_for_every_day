#pragma once
#include <stdlib.h>
#include "fatal.h"

template<typename t>
class Treap_node {
private:
	t _element{0};
	int _priority{ULLONG_MAX};
public:
	Treap_node* left{nullptr};
	Treap_node* right{nullptr};
	Treap_node() {}
	Treap_node(int el, int pr)
	{
		_element = el;
		_priority = pr;
	}

	int get_element() {
		return _element;
	}
	int get_priority() {
		return _priority;
	}
	void set_element(int el) {
		_element = el;
	}

	void set_priority() {
		_priority = rand() - 1;
	}

};

template<typename t>
class treap
{
private:
	Treap_node* root;
public:
	treap();
	void MakeEmpty(Treap_node*);
	void PrintTree(Treap_node*);

	Treap_node* Find(t X, Treap_node*);
	Treap_node* FindMin(Treap_node*);
	Treap_node* FindMax(Treap_node*);

	Treap_node* SingleRotateWithLeft(Treap_node*);
	Treap_node* SingleRotateWithRight(Treap_node*);

	//Treap_node* Initialize();

	Treap_node* Insert(t , Treap_node*);
	Treap_node* Remove(t, Treap_node*);
	t Retrieve(Treap_node* P);

};




