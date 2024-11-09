#include "trees/rb.hpp"
#include <iostream>


namespace trees {


RB::RB() : root(nullptr) {}


void RB::insert(int val) {
    if (root == nullptr) {
        root = new RBNode(val);
        root->setColor(NodeColor::BLACK); // La raíz siempre es negra
    } else {
        insert(val, root);
    }
}


void RB::insert(int val, RBNode* node) {
    if (val < node->getData()) {
        if (node->getLeft() == nullptr) {
            node->setLeft(new RBNode(val, node));
            balance(node->getLeft()); // Balancear después de la inserción
        } else {
            insert(val, node->getLeft());
        }
    } else {
        if (node->getRight() == nullptr) {
            node->setRight(new RBNode(val, node));
            balance(node->getRight()); // Balancear después de la inserción
        } else {
            insert(val, node->getRight());
        }
    }
}


void RB::balance(RBNode* node) {
    while (node != root && node->getParent()->getColor() == NodeColor::RED) {
        RBNode* parent = node->getParent();
        RBNode* grandparent = parent->getParent();


        if (parent == grandparent->getLeft()) {
            RBNode* uncle = grandparent->getRight();
            if (uncle != nullptr && uncle->getColor() == NodeColor::RED) {
                // Caso 1: El tío es rojo
                parent->setColor(NodeColor::BLACK);
                uncle->setColor(NodeColor::BLACK);
                grandparent->setColor(NodeColor::RED);
                node = grandparent;
            } else {
                // Caso 2 y 3: El tío es negro
                if (node == parent->getRight()) {
                    node = parent;
                    leftRotation(node);
                }
                parent->setColor(NodeColor::BLACK);
                grandparent->setColor(NodeColor::RED);
                rightRotation(grandparent);
            }
        } else {
            RBNode* uncle = grandparent->getLeft();
            if (uncle != nullptr && uncle->getColor() == NodeColor::RED) {
                // Caso 1: El tío es rojo
                parent->setColor(NodeColor::BLACK);
                uncle->setColor(NodeColor::BLACK);
                grandparent->setColor(NodeColor::RED);
                node = grandparent;
            } else {
                // Caso 2 y 3: El tío es negro
                if (node == parent->getLeft()) {
                    node = parent;
                    rightRotation(node);
                }
                parent->setColor(NodeColor::BLACK);
                grandparent->setColor(NodeColor::RED);
                leftRotation(grandparent);
            }
        }
    }
    root->setColor(NodeColor::BLACK); // La raíz siempre debe ser negra
}


void RB::leftRotation(RBNode* node) {
    RBNode* rightChild = node->getRight();
    node->setRight(rightChild->getLeft());


    if (rightChild->getLeft() != nullptr) {
        rightChild->getLeft()->setParent(node);
    }
    rightChild->setParent(node->getParent());


    if (node->getParent() == nullptr) {
        root = rightChild;
    } else if (node == node->getParent()->getLeft()) {
        node->getParent()->setLeft(rightChild);
    } else {
        node->getParent()->setRight(rightChild);
    }
    rightChild->setLeft(node);
    node->setParent(rightChild);
}


void RB::rightRotation(RBNode* node) {
    RBNode* leftChild = node->getLeft();
    node->setLeft(leftChild->getRight());


    if (leftChild->getRight() != nullptr) {
        leftChild->getRight()->setParent(node);
    }
    leftChild->setParent(node->getParent());


    if (node->getParent() == nullptr) {
        root = leftChild;
    } else if (node == node->getParent()->getLeft()) {
        node->getParent()->setLeft(leftChild);
    } else {
        node->getParent()->setRight(leftChild);
    }
    leftChild->setRight(node);
    node->setParent(leftChild);
}


RBNode* RB::find(int val, RBNode* node) {
    if (node == nullptr || node->getData() == val) {
        return node;
    } else if (val < node->getData()) {
        return find(val, node->getLeft());
    } else {
        return find(val, node->getRight());
    }
}


RBNode* RB::find(int val) {
    return find(val, root);
}


void RB::traverse(RBNode* node, int level) {
    if (node != nullptr) {
        for (int i = 0; i < level; i++) {
            std::cout << "*";
        }
        std::cout << node->getData() << " (" << node->getColor() << ")\n";
        traverse(node->getLeft(), level + 1);
        traverse(node->getRight(), level + 1);
    }
}


void RB::traverse() {
    traverse(root, 1);
}


RB::~RB() {
    delete root;
}


} // namespace trees





