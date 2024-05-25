//
// Created by shirin dora on 20/03/2020.
//

#ifndef INC_23TREE_TWOTHREETREE_H
#define INC_23TREE_TWOTHREETREE_H

#include "TwoThreeNode.h"


class TwoThreeTree {
public:
    TwoThreeTree();
    ~TwoThreeTree();

    void insert(int k);
    void traverseInOrder();
private:
    TwoThreeNode* root;
    int node_count;

    bool isTwoNode(TwoThreeNode* n); // return true if a node contains one key and two children
    void addKey2TwoNode(TwoThreeNode *n, int k); // add key to a node with single key
    void insert(int k, TwoThreeNode* n);
    void search(TwoThreeNode *&found_node, int k);
    void split(int &k, TwoThreeNode *node2split, TwoThreeNode *&added_node);
    void traverseInOrder(TwoThreeNode* n);
};


#endif //INC_23TREE_TWOTHREETREE_H
