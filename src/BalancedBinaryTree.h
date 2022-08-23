
#ifndef BALANCED_BINARY_TREE_CLASS_HEADER
#define BALANCED_BINARY_TREE_CLASS_HEADER




/**
 * A balanced binary tree, AKA red/black tree
 */
typedef struct _BalancedBinaryTree _BalancedBinaryTree;




typedef struct
{
    /**
     * @param value - the value of the root
     * @param compareCallback - the callback to compare future elements with, should return :
     *  < 0 if current value is smaller,
     *  > 0 if other value is smaller,
     *  = 0 if both are equal
     */
    _BalancedBinaryTree * (* constructor)(
        void const * value,
        int (* compareValuesCallback)(void const * const currentValue, void const * const otherValue)
    );

    /**
     * Destroys all nodes and sets them all to NULL
     */
    void (* destructor)(_BalancedBinaryTree ** this);

    /**
     * @return - the value of the node, or NULL if node is NULL
     */
    void const * (* value)(_BalancedBinaryTree const * const this);

    /**
     * @param value - the value to find from the node and deeper in the tree
     *
     * @return - the first node having the given value, or NULL if not found
     */
    _BalancedBinaryTree * (* find)(_BalancedBinaryTree * const this, void const * const value);

    /**
     * @param value - the value to find from the node and deeper in the tree
     *
     * @return - 1 if the value was found from the node or deeper, 0 otherwise
     */
    int (* contains)(_BalancedBinaryTree * const this, void const * const value);

    /**
     * @param value - the value to add in the tree
     *
     * @return - the constructorly created node
     */
    _BalancedBinaryTree * (* add)(_BalancedBinaryTree * const this, void const * const value);

    /**
     * @return - the height of the tree from the given node
     */
    unsigned int (* height)(_BalancedBinaryTree const * const this);

    /**
     * Detaches the whole branch from its parent
     *
     * @return - the parent of the detached node, or NULL if node is NULL
     */
    _BalancedBinaryTree * (* detach)(_BalancedBinaryTree * const this);

    _BalancedBinaryTree * (* root)(_BalancedBinaryTree * const this);

    /**
     * @param this - the node from which to find the value, and deeper
     * @param value - the value to pop from the tree
     *
     * @return - the popped node, or NULL if it was not found
     */
    _BalancedBinaryTree * (* pop)(_BalancedBinaryTree * const this, void const * const value);

    /**
     * Applies the callback on every node in the tree
     *
     * @param callback - the callback to apply on each value
     */
    void (* map)(
        _BalancedBinaryTree const * const this,
        void (* callback)(void const * const value),
        BinaryTreeTraversal traversal
    );
} BalancedBinaryTreeMethods;




/**
 * BalancedBinaryTree methods table
 */
extern BalancedBinaryTreeMethods const * const BalancedBinaryTree;




#endif /* BALANCED_BINARY_TREE_CLASS_HEADER */
