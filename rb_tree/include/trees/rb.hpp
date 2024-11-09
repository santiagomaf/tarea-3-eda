#ifndef RB_HPP_
#define RB_HPP_


#include "trees/rbNode.hpp"


namespace trees {


enum RotationType {
    LEFT_ROTATION,
    RIGHT_ROTATION,
    LEFT_RIGHT_ROTATION,
    RIGHT_LEFT_ROTATION,
    NONE // No rotation needed
};


class RB {
private:
    RBNode* root;


    // Métodos privados
    void balance(RBNode* node);
    void leftRotation(RBNode* node);
    void rightRotation(RBNode* node);
    RotationType getRotationType(RBNode* node);


public:
    RB();
    void insert(int val);
    RBNode* find(int val);
    void traverse();
    virtual ~RB();


    // Métodos auxiliares
    void insert(int val, RBNode* node);
    RBNode* find(int val, RBNode* node);
    void traverse(RBNode* node, int level);
};


} /* namespace trees */


#endif /* RB_HPP_ */





