
#include <stdio.h>
#include <stdlib.h>

#include "Class.h"
#include "BinaryTree.h"
#include "BalancedBinaryTree.h"




/**
 * Colors that nodes can have
 * Magic number as values are to avoid false positives when casting
 * from a simple binary tree
 */
typedef enum
{
    RED  = ~('R' << 16 | 'E' << 8 | 'D') + 1,
    BLACK = ~('B' << 16 | 'L' << 8 | 'K') + 1
} BalancedBinaryTreeNodeColor;


struct _BalancedBinaryTree
{
    void const * value;
    int (* compare)(void const * const currentValue, void const * const otherValue);
    _BalancedBinaryTree * parent;
    _BalancedBinaryTree * leftNode;
    _BalancedBinaryTree * rightNode;
    BalancedBinaryTreeNodeColor color;
};




/**
 * @param value - the value to compare with
 *
 * @return - 1 if the value of the node is greater than the other one, 0 otherwise
 */
static int nodeHasGreaterValue(_BalancedBinaryTree const * const this, void const * const value);


static _BalancedBinaryTree * addValueToTheLeft(_BalancedBinaryTree * const this, void const * const value);


static _BalancedBinaryTree * addValueToTheRight(_BalancedBinaryTree * const this, void const * const value);




static _BalancedBinaryTree * constructor(void const * value, int (* compareValuesCallback)(void const * const currentValue, void const * const otherValue))
{
    _BalancedBinaryTree * this = Class->constructor("BinaryTree", sizeof(* this));

    if (this == NULL)
        return NULL;

    this->value = value;
    this->compare = compareValuesCallback;
    this->parent = NULL;
    this->leftNode = NULL;
    this->rightNode = NULL;
    this->color = BLACK;

    return this;
}


static void destructor(_BalancedBinaryTree ** this)
{
    BinaryTree->destructor((_BinaryTree **) this);
}


static void const * value(_BalancedBinaryTree const * const this)
{
    return BinaryTree->value((_BinaryTree *) this);
}


static _BalancedBinaryTree * findValue(_BalancedBinaryTree * const this, void const * const value)
{
    return (_BalancedBinaryTree *) BinaryTree->find((_BinaryTree *) this, value);
}


static int containsValue(_BalancedBinaryTree * const this, void const * const value)
{
    return BinaryTree->contains((_BinaryTree *) this, value);
}


static _BalancedBinaryTree * addValue(_BalancedBinaryTree * const this, void const * const value)
{
    if (nodeHasGreaterValue(this, value))
        return addValueToTheLeft(this, value);
    return addValueToTheRight(this, value);
}


static unsigned int height(_BalancedBinaryTree const * const this)
{
    return BinaryTree->height((_BinaryTree *) this);
}


static _BalancedBinaryTree * detachNode(_BalancedBinaryTree * const this)
{
    return (_BalancedBinaryTree *) BinaryTree->detach((_BinaryTree *) this);
}


static _BalancedBinaryTree * root(_BalancedBinaryTree * const this)
{
    return (_BalancedBinaryTree *) BinaryTree->root((_BinaryTree *) this);
}


static _BalancedBinaryTree * pop(_BalancedBinaryTree * const this, void const * const value)
{
    return (_BalancedBinaryTree *) BinaryTree->pop((_BinaryTree *) this, value);
}


static void map(_BalancedBinaryTree const * const this, void (* callback)(void const * const value), BinaryTreeTraversal traversal)
{
    BinaryTree->map((_BinaryTree *) this, callback, traversal);
}




static int nodeHasGreaterValue(_BalancedBinaryTree const * const this, void const * const value)
{
    return this->compare(this->value, value) > 0;
}


static _BalancedBinaryTree * addValueToTheLeft(_BalancedBinaryTree * const this, void const * const value)
{
    if (this->leftNode != NULL)
        return addValue(this->leftNode, value);

    this->leftNode = constructor(value, this->compare);
    this->leftNode->parent = this;

    return this->leftNode;
}


static _BalancedBinaryTree * addValueToTheRight(_BalancedBinaryTree * const this, void const * const value)
{
    if (this->rightNode != NULL)
        return addValue(this->rightNode, value);

    this->rightNode = constructor(value, this->compare);
    this->rightNode->parent = this;

    return this->rightNode;
}




/**
 * Init BinaryTree methods table
 */
static BalancedBinaryTreeMethods methods = {
    constructor,
    destructor,
    value,
    findValue,
    containsValue,
    addValue,
    height,
    detachNode,
    root,
    pop,
    map
};
BalancedBinaryTreeMethods const * const BalancedBinaryTree = & methods;
