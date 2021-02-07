#include "treap.h"
#include "treap.h"
#include <stdlib.h>
#include "fatal.h"
#include <iostream>

using namespace std;

//treap NullNode = NULL;  /* Needs initialization */

//treap treap :: Initialize()
//{
//    //if (NullNode == NULL)
//    //{
//    //    NullNode = new TreapNode;
//    //        
//    //    if (NullNode == NULL)
//    //        FatalError("Out of space!!!");
//    //    NullNode->Left = NULL;
//    //    NullNode->Right = NULL;
//    //    NullNode->Priority = Infinity;
//    //}
//    //return NullNode;
//}

template<typename t>
treap<t>::treap()
{
  
}

template<typename t>
void treap<t> :: MakeEmpty(Treap_node<t>* node)
{
    if (node != nullptr)
    {
        MakeEmpty(node->left);
        MakeEmpty(node->right);
        delete(root);
    }
    return ;
}

template<typename t>
void treap<t>:: PrintTree(Treap_node<t>* node)
{
    if (node != nullptr)
    {
        
        PrintTree(root->left);
        cout <<" "<< node->get_element();
        PrintTree(root->right);
    }
    return;
}

template<typename t>
Treap_node<t>* treap<t> :: Find(t X, Treap_node<t>* node)
{
    if (node == nullptr)
        return ;
    if (X < node->get_element())
        return Find(X, node->left);
    else
        if (X > node->get_element())
            return Find(X,node->right);
        else
            return node;
}


template<typename t>
Treap_node<t>* treap<t>:: FindMin(Treap_node<t>* T)
{
    if (T == nullptr)
        return;
    else
        if (T->left == nullptr)
            return T;
        else
            return FindMin(T->left);
}

template<typename t>
Treap_node<t>* treap<t>:: FindMax(Treap_node<t>* T)
{
    if (T != nullptr)
        while (T->right != nullptr)
            T = T->right;

    return T;
}


template<typename t>
Treap_node<t>* treap<t>:: SingleRotateWithLeft(Treap_node<t>* K2)
{
    Treap_node* K1;
    K1 = K2->left;
    K2->left = K1->right;
    K1->right = K2;

    return K1; 
}

template<typename t>
 Treap_node<t>* treap<t>:: SingleRotateWithRight(Treap_node<t>* K1)
{
    Treap_node* K2;
    K2 = K1->right;
    K1->right = K2->left;
    K2->left = K1;

    return K2;  
}

 template<typename t>
Treap_node<t>* treap<t> :: Insert(t Item, Treap_node<t>* T)
{
    if (T == nullptr)
    {
        /* Create and return a one-node tree */
        T = new Treap_node;
          
        if (T == nullptr)
            FatalError("Out of space!!!");
        else
        {
            T->set_element(Item);
            T->set_priority();
            T->left = T->right = nullptr;
        }
    }
    else
        if (Item < T->get_element())
        {
            T->left = Insert(Item, T->left);
            if (T->left->get_priority() < T->get_priority())
                T = SingleRotateWithLeft(T);
        }
        else
            if (Item > T->get_element())
            {
                T->right = Insert(Item, T->right);
                if (T->right->get_priority() < T->get_priority())
                    T = SingleRotateWithRight(T);
            }

    return T;
}

template<typename t>
Treap_node<t>* treap<t>:: Remove(t Item, Treap_node<t>* T)
{
    if (T != nullptr)
    {
        if (Item < T->get_element())
            T->left = Remove(Item, T->left);
        else
            if (Item > T->get_element())
                T->right = Remove(Item, T->right);
            else
            {
                if (T->left->get_priority() < T->right->get_priority())
                    T = SingleRotateWithLeft(T);
                else
                    T = SingleRotateWithRight(T);

                if (T != nullptr)  
                    T = Remove(Item, T);
                else
                {
                    delete(T->left);
                    T->left = nullptr;
                }
            }
    }
    return T;
}

template<typename t>
t Retrieve(Treap_node<t>* P)
{
    return P->get_element();
}


