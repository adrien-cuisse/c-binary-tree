
#ifndef BINARY_TREE_CLASS_HEADER
#define BINARY_TREE_CLASS_HEADER




/**
 * Ways to travel a tree
 */
typedef enum
{
    PreOrder,
    InOrder,
    PostOrder
} BinaryTreeTraversal;




typedef struct _BinaryTree _BinaryTree;




typedef struct
{
    /**
     * @param value - the value of the root
     * @param compareCallback - the callback to compare future elements with, should return :
     *  < 0 if current value is smaller,
     *  > 0 if other value is smaller,
     *  = 0 if both are equal
     */
    _BinaryTree * (* constructor)(
        void const * value,
        int (* compareValuesCallback)(void const * const currentValue, void const * const otherValue)
    );

    /**
     * Destroys all nodes and sets them all to NULL
     */
    void (* destructor)(_BinaryTree ** this);

    /**
     * @return - the value of the node, or NULL if node is NULL
     */
    void const * (* value)(_BinaryTree const * const this);

    /**
     * @param value - the value to find from the node and deeper in the tree
     *
     * @return - the first node having the given value, or NULL if not found
     */
    _BinaryTree * (* find)(_BinaryTree * const this, void const * const value);

    /**
     * @param value - the value to find from the node and deeper in the tree
     *
     * @return - 1 if the value was found from the node or deeper, 0 otherwise
     */
    int (* contains)(_BinaryTree * const this, void const * const value);

    /**
     * @param value - the value to add in the tree
     *
     * @return - the constructorly created node
     */
    _BinaryTree * (* add)(_BinaryTree * const this, void const * const value);

    /**
     * @return - the height of the tree from the given node
     */
    unsigned int (* height)(_BinaryTree const * const this);

    /**
     * Detaches the whole branch from its parent
     *
     * @return - the parent of the detached node, or NULL if node is NULL
     */
    _BinaryTree * (* detach)(_BinaryTree * const this);

    _BinaryTree * (* root)(_BinaryTree * const this);

    /**
     * @param this - the node from which to find the value, and deeper
     * @param value - the value to pop from the tree
     *
     * @return - the popped node, or NULL if it was not found
     */
    _BinaryTree * (* pop)(_BinaryTree * const this, void const * const value);

    /**
     * Applies the callback on every node in the tree
     *
     * @param callback - the callback to apply on each value
     */
    void (* map)(
        _BinaryTree const * const this,
        void (* callback)(void const * const value),
        BinaryTreeTraversal traversal
    );
} BinaryTreeMethods;




/**
 * BinaryTree methods table
 */
extern BinaryTreeMethods const * const BinaryTree;




#endif /* BINARY_TREE_CLASS_HEADER */
