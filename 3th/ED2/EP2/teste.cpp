//
// Created by shirin dora on 20/03/2020.
//

#include <iostream>
#include "TwoThreeTree.h"

TwoThreeTree::TwoThreeTree() {
    root = nullptr;
    node_count = 0;
}

TwoThreeTree::~TwoThreeTree() {

}

void TwoThreeTree::insert(int k) {
    insert(k, root);
}

void TwoThreeTree::insert(int k, TwoThreeNode *n) {
    TwoThreeNode* found_node = nullptr; // node in which the search key will be inserted

    // find the node where this key should be inserted
    if (n == nullptr) {
        // create a node if root does not exist
        root = new TwoThreeNode(k);
        return;
    } else {
        // find a node where this key should be inserted
        search(found_node, k);
    }

    // insert the key into the found node
    if (isTwoNode(found_node)) {
        // key is to be inserted in a node with one key
        addKey2TwoNode(found_node, k);
    } else {
        // key is to be inserted into a node with two keys
        TwoThreeNode* added_node = nullptr;
        bool continue_split = true;

        while (continue_split) {
            split(k, found_node, added_node);

            if (!found_node->parent) {
                // create new root as node splitting has propagated to the current root node
                root = new TwoThreeNode(k);
                root->set_child(TwoThreeNode::LEFT, added_node);
                root->set_child(TwoThreeNode::RIGHT, found_node);

                continue_split = false;
            } else {
                found_node = found_node->parent;

                if (isTwoNode(found_node)) {
                    // parent of the split node is a node with one key
                    if (k < found_node->left_key) {
                        addKey2TwoNode(found_node, k);

                        found_node->set_child(TwoThreeNode::MIDDLE, found_node->left);
                        found_node->set_child(TwoThreeNode::LEFT, added_node);
                    } else if (k > found_node->left_key) {
                        addKey2TwoNode(found_node, k);

                        found_node->set_child(TwoThreeNode::MIDDLE, added_node);
                        found_node->middle = added_node;
                    }

                    continue_split = false;
                }
            }
        }
    }
}

void TwoThreeTree::search(TwoThreeNode *&found_node, int k) {
    bool found_flag = false;

    found_node = root;
    while (!found_flag) {
        // search key is smaller than the left_key in current node
        if (k < found_node->left_key) {
            if (!found_node->left) {
                found_flag = true;
            } else {
                found_node = found_node->left;
            }
        } else if ((isTwoNode(found_node) && k > found_node->left_key) ||
                   (!isTwoNode(found_node) && k > found_node->right_key)) {
            // search key is greater than the highest key present in a node
            if (!found_node->right) {
                found_flag = true;
            } else {
                found_node = found_node->right;
            }
        } else {
            // search key is greater than the left_key but smaller than the right_key
            if (!found_node->middle) {
                found_flag = true;
            } else {
                found_node = found_node->middle;
            }
        }
    }
}

bool TwoThreeTree::isTwoNode(TwoThreeNode *n) {
    if (n->right_key == (-1)) {
        return true;
    }

    return false;
}

void TwoThreeTree::addKey2TwoNode(TwoThreeNode *n, int k) {
    if (k > n->left_key) {
        n->right_key = k;
    } else {
        n->right_key = n->left_key;
        n->left_key = k;
    }
}

void TwoThreeTree::split(int &k, TwoThreeNode *node2split, TwoThreeNode *&added_node) {
    TwoThreeNode* new_node;

    // A node can be split into three different ways depending on the key value being inserted
    if (k > node2split->right_key) {
        new_node = new TwoThreeNode(node2split->left_key);
        new_node->set_child(TwoThreeNode::LEFT, node2split->left);
        new_node->set_child(TwoThreeNode::RIGHT, node2split->middle);

        node2split->left_key = k;
        node2split->set_child(TwoThreeNode::LEFT, added_node);
        k = node2split->right_key;
    } else if (k < node2split->left_key) {
        new_node = new TwoThreeNode(k);
        new_node->set_child(TwoThreeNode::LEFT, added_node);
        new_node->set_child(TwoThreeNode::RIGHT, node2split->left);

        k = node2split->left_key;
        node2split->left_key = node2split->right_key;
        node2split->set_child(TwoThreeNode::LEFT, node2split->middle);
    } else {
        new_node = new TwoThreeNode(node2split->left_key);
        new_node->set_child(TwoThreeNode::LEFT, node2split->left);
        new_node->set_child(TwoThreeNode::RIGHT, added_node);

        node2split->left_key = node2split->right_key;
        node2split->set_child(TwoThreeNode::LEFT, node2split->middle);
    }

    node2split->reset_child(TwoThreeNode::MIDDLE);
    node2split->right_key = -1;
    added_node = new_node;
}

void TwoThreeTree::traverseInOrder() {
    traverseInOrder(root);
}

void TwoThreeTree::traverseInOrder(TwoThreeNode *n) {
    if (n) {
        traverseInOrder(n->left);
        std::cout << n->left_key << "\t";
        traverseInOrder(n->middle);
        if (n->right_key != -1) {
            std::cout << n->right_key << "\t";
        }
        traverseInOrder(n->right);
    }
}