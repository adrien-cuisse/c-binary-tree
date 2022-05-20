
#include <stdio.h>
#include <stdlib.h>

#include "Class.h"
#include "BinaryTree.h"




struct _BinaryTree
{
    void const * value;
    int (* compare)(void const * const currentValue, void const * const otherValue);
    _BinaryTree * parent;
    _BinaryTree * leftNode;
    _BinaryTree * rightNode;
};




/**
 * @param value - the value to compare with
 *
 * @return - 1 if the value of the node is greater than the other one, 0 otherwise
 */
static int nodeHasGreaterValue(_BinaryTree const * const this, void const * const value);


/**
 * @return - the node whose value is right after this one in the tree
 */
static _BinaryTree * successor(_BinaryTree * const this);


static _BinaryTree * addValueToTheLeft(_BinaryTree * const this, void const * const value);


static _BinaryTree * addValueToTheRight(_BinaryTree * const this, void const * const value);


static void attachLeftSonToParent(_BinaryTree * const this);


static void attachRightSonToParent(_BinaryTree * const this);


static void replaceNodeWithSuccessor(_BinaryTree * const this);




static _BinaryTree * constructor(void const * value, int (* compareValuesCallback)(void const * const currentValue, void const * const otherValue))
{
    _BinaryTree * this = Class->constructor("BinaryTree", sizeof(* this));

    if (this == NULL)
        return NULL;

    this->value = value;
    this->compare = compareValuesCallback;
    this->parent = NULL;
    this->leftNode = NULL;
    this->rightNode = NULL;

    return this;
}


static void destructor(_BinaryTree ** this)
{
    if ((this == NULL) || (* this == NULL))
        return;

    destructor(& (* this)->parent);
    destructor(& (* this)->leftNode);
    destructor(& (* this)->rightNode);
    Class->destructor((void **) this);
}


static void const * value(_BinaryTree const * const this)
{
    if (this == NULL)
        return NULL;
    return this->value;
}


_BinaryTree * findValue(_BinaryTree * const this, void const * const value)
{
    int comparison;

    if (this == NULL)
        return NULL;

    comparison = this->compare(this->value, value);

    if (comparison == 0)
        return this;
    if (comparison > 0)
        return findValue(this->leftNode, value);
    return findValue(this->rightNode, value);
}


static int containsValue(_BinaryTree * const this, void const * const value)
{
    return findValue(this, value) != NULL;
}


static _BinaryTree * addValue(_BinaryTree * const this, void const * const value)
{
    if (nodeHasGreaterValue(this, value))
        return addValueToTheLeft(this, value);
    return addValueToTheRight(this, value);
}


static unsigned int height(_BinaryTree const * const this)
{
    int leftHeight, rightHeight;

    if (this == NULL)
        return 0;

    leftHeight = 1 + height(this->leftNode);
    rightHeight = 1 + height(this->rightNode);

    if (leftHeight > rightHeight)
        return leftHeight;

    return rightHeight;
}


static _BinaryTree * detachNode(_BinaryTree * const this)
{
    _BinaryTree * parent;
    if (this == NULL)
        return NULL;

    parent = this->parent;
    if (parent == NULL)
        return NULL;

    if (nodeHasGreaterValue(parent, this->value))
        parent->leftNode = NULL;
    else
        parent->rightNode = NULL;
    this->parent = NULL;

    return parent;
}


static _BinaryTree * root(_BinaryTree * const this)
{
    _BinaryTree * root = this;

    if (this == NULL)
        return NULL;

    while (root->parent != NULL)
        root = root->parent;

    return root;
}


static _BinaryTree * pop(_BinaryTree * const this, void const * const value)
{
    _BinaryTree * node;

    if (this == NULL)
        return NULL;

    node = findValue(this, value);
    if (node == NULL)
        return NULL;

    if (node->leftNode == NULL)
        attachRightSonToParent(node);
    else if (node->rightNode == NULL)
        attachLeftSonToParent(node);
    else
        replaceNodeWithSuccessor(node);

    node->parent = NULL;

    return node;
}


void map(_BinaryTree const * const this, void (* callback)(void const * const value), BinaryTreeTraversal traversal)
{
    if (this == NULL)
        return;

    if (traversal == PreOrder)
        callback(this->value);
    else
        map(this->leftNode, callback, traversal);

    if (traversal == PreOrder)
        map(this->leftNode, callback, traversal);
    else if (traversal == InOrder)
        callback(this->value);
    else
        map(this->rightNode, callback, traversal);

    if (traversal == PostOrder)
        callback(this->value);
    else
        map(this->rightNode, callback, traversal);

    /*switch (traversal)
    {
        case PreOrder:
            callback(this->value);
            map(this->leftNode, callback, traversal);
            map(this->rightNode, callback, traversal);
            break;
        case InOrder:
            map(this->leftNode, callback, traversal);
            callback(this->value);
            map(this->rightNode, callback, traversal);
            break;
        case PostOrder:
            map(this->leftNode, callback, traversal);
            map(this->rightNode, callback, traversal);
            callback(this->value);
            break;
        default:
            break;
    }*/
}




static int nodeHasGreaterValue(_BinaryTree const * const this, void const * const value)
{
    return this->compare(this->value, value) > 0;
}


static _BinaryTree * successor(_BinaryTree * const this)
{
    _BinaryTree * successor;

    successor = this->leftNode;
    while (successor->rightNode != NULL)
        successor = successor->rightNode;

    return successor;
}


static _BinaryTree * addValueToTheLeft(_BinaryTree * const this, void const * const value)
{
    if (this->leftNode != NULL)
        return addValue(this->leftNode, value);

    this->leftNode = constructor(value, this->compare);
    this->leftNode->parent = this;

    return this->leftNode;
}


static _BinaryTree * addValueToTheRight(_BinaryTree * const this, void const * const value)
{
    if (this->rightNode != NULL)
        return addValue(this->rightNode, value);

    this->rightNode = constructor(value, this->compare);
    this->rightNode->parent = this;

    return this->rightNode;
}


static void attachLeftSonToParent(_BinaryTree * const this)
{
    if (nodeHasGreaterValue(this->parent, this->value))
        this->parent->leftNode = this->leftNode;
    else
        this->parent->rightNode = this->leftNode;

    this->leftNode = NULL;
}


static void attachRightSonToParent(_BinaryTree * const this)
{
    if (nodeHasGreaterValue(this->parent, this->value))
        this->parent->leftNode = this->rightNode;
    else
        this->parent->rightNode = this->rightNode;

    this->rightNode = NULL;
}


static void replaceNodeWithSuccessor(_BinaryTree * const this)
{
    _BinaryTree * succeeding = successor(this);

    if (nodeHasGreaterValue(this->parent, this->value))
        this->parent->leftNode = succeeding;
    else
        this->parent->rightNode = succeeding;

    succeeding->rightNode = this->rightNode;

    this->leftNode = NULL;
    this->rightNode = NULL;
}




/**
 * Init BinaryTree methods table
 */
static BinaryTreeMethods methods = {
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
BinaryTreeMethods const * const BinaryTree = & methods;
