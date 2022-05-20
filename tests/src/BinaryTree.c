
#include <stdio.h>
#include <string.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "../../src/BinaryTree.h"

#define TREE_NODE_COMPARISON_CALLBACK_TYPE int (*)(void const * const, void const * const)
#define TO_NODE_COMPARISON_CALLBACK(function) ((TREE_NODE_COMPARISON_CALLBACK_TYPE) function)
#define STRING_NODE_COMPARISON_CALLBACK TO_NODE_COMPARISON_CALLBACK(strcmp)




Test(binary_tree, constructor_allocates_memory)
{
    // when creating an instance
    _BinaryTree * instance = BinaryTree->constructor(NULL, NULL);

    // then it shouldn't be null
    cr_assert_not_null(
        instance,
        "Constructor should allocate memory"
    );
}


Test(binary_tree, stores_given_value)
{
    // when storing a value in an element
    char * value = "root";
    _BinaryTree * instance = BinaryTree->constructor(value, NULL);

    // then the stored value should be the given one
    cr_assert_eq(
        BinaryTree->value(instance),
        value,
        "Constructor should store the given value"
    );
}


Test(binary_tree, destructor_doesnt_crash_when_instance_is_null)
{
    // given a null tree
    _BinaryTree * tree = NULL;

    // when deleting it
    BinaryTree->destructor(& tree);

    // then it shouldn't crash
}


Test(binary_tree, destructor_frees_memory)
{
    // given an instance
    _BinaryTree * instance = BinaryTree->constructor(NULL, NULL);

    // when deleting it
    BinaryTree->destructor(& instance);

    // then it should be null
    cr_assert_null(
        instance,
        "Destructor should free the instance memory"
    );
}


Test(binary_tree, destructor_doesnt_affect_value)
{
    // given a value
    char * value = "some important data";

    // when putting it in a tree and deleting it
    _BinaryTree * instance = BinaryTree->constructor(value, NULL);
    BinaryTree->destructor(& instance);

    // then value should remain intact
    cr_assert_not_null(
        value,
        "Destructor should let stored value as is"
    );
}


Test(binary_tree, null_trees_dont_contain_values)
{
    // given a null tree
    _BinaryTree * tree = NULL;

    // when checking if it contains any value
    int isStored = BinaryTree->contains(tree, "any value");

    // then it shouldn't
    cr_assert_eq(
        0,
        isStored,
        "Null trees shouldn't contain values"
    );
}


Test(binary_tree, finds_root_value)
{
    // given a tree with a value
    _BinaryTree * tree = BinaryTree->constructor("root", STRING_NODE_COMPARISON_CALLBACK);

    // when checking if the value is stored
    int isStored = BinaryTree->contains(tree, "root");

    // then it should be
    cr_assert_neq(
        0,
        isStored,
        "Stored values should be found"
    );
}


Test(binary_tree, finds_added_lesser_values)
{
    // given a tree with a value added in a later node
    _BinaryTree * tree = BinaryTree->constructor("42", STRING_NODE_COMPARISON_CALLBACK);
    BinaryTree->add(tree, "41");

    // when looking for the latest value
    int isStored = BinaryTree->contains(tree, "41");

    // then it should be found
    cr_assert_neq(
        0,
        isStored,
        "Added lesser values should be found"
    );
}


Test(binary_tree, finds_added_greater_values)
{
    // given a tree with a value added in a later node
    _BinaryTree * tree = BinaryTree->constructor("42", STRING_NODE_COMPARISON_CALLBACK);
    BinaryTree->add(tree, "43");

    // when looking for the latest value
    int isStored = BinaryTree->contains(tree, "43");

    // then it should be found
    cr_assert_neq(
        0,
        isStored,
        "Added greater values should be found"
    );
}


Test(binary_tree, doesnt_find_non_stored_value)
{
    // given a tree with differents values
    _BinaryTree * tree = BinaryTree->constructor("root", STRING_NODE_COMPARISON_CALLBACK);
    BinaryTree->add(tree, "added");

    // when checking if another value is stored
    int isStored = BinaryTree->contains(tree, "non-stored value");

    // then it shouldn't be
    cr_assert_eq(
        0,
        isStored,
        "Non-stored values shouldn't be found"
    );
}


Test(binary_tree, null_trees_have_no_height)
{
    // given a null tree
    _BinaryTree * tree = NULL;

    // when checking the height of the tree
    int height = BinaryTree->height(tree);

    // then it should be 0
    cr_assert_eq(
        0,
        height,
        "Null trees should have no height"
    );
}


Test(binary_tree, initial_height_is_1)
{
    // given a tree made of only its root
    _BinaryTree * root = BinaryTree->constructor("root", STRING_NODE_COMPARISON_CALLBACK);

    // when checking the height of the tree
    int height = BinaryTree->height(root);

    // then it should be 1
    cr_assert_eq(
        1,
        height,
        "Height should be 1 when the tree is only made of 1 node"
    );
}


Test(binary_tree, computes_height_from_lesser_value_nodes)
{
    // given a tree with an added lesser value
    _BinaryTree * root = BinaryTree->constructor("42", STRING_NODE_COMPARISON_CALLBACK);
    BinaryTree->add(root, "41");

    // when checking its height
    int height = BinaryTree->height(root);

    // then it should be 2
    cr_assert_eq(
        2,
        height,
        "Height should be computed from lesser-value nodes"
    );
}


Test(binary_tree, computes_height_from_equal_value_nodes)
{
    // given a tree with an added equal value
    _BinaryTree * root = BinaryTree->constructor("42", STRING_NODE_COMPARISON_CALLBACK);
    BinaryTree->add(root, "42");

    // when checking its height
    int height = BinaryTree->height(root);

    // then it should be 2
    cr_assert_eq(
        2,
        height,
        "Height should be computed from equal-value nodes"
    );
}


Test(binary_tree, computes_height_from_greater_value_nodes)
{
    // given a tree with an added greater value
    _BinaryTree * root = BinaryTree->constructor("42", STRING_NODE_COMPARISON_CALLBACK);
    BinaryTree->add(root, "43");

    // when checking its height
    int height = BinaryTree->height(root);

    // then it should be 2
    cr_assert_eq(
        2,
        height,
        "Height should be computed from greater-value nodes"
    );
}


Test(binary_tree, height_is_lesser_values_chain)
{
    // given a tree with a root, a chain of "lesser-values" of length 2, a chain of "greater-values" of length 1
    _BinaryTree * root = BinaryTree->constructor("3", STRING_NODE_COMPARISON_CALLBACK);
    BinaryTree->add(root, "2");
    BinaryTree->add(root, "1");
    BinaryTree->add(root, "4 is greater than the root value");

    // when checking its height
    int height = BinaryTree->height(root);

    // then it should be 3
    cr_assert_eq(
        3,
        height,
        "Height should be the 'lesser-values height' when its greater than the 'greater-values height'"
    );
}


Test(binary_tree, height_is_greater_values_chain)
{
    // given a tree with a root, a chain of "greater-values" of length 2, a chain of "lesser-values" of length 1
    _BinaryTree * root = BinaryTree->constructor("1", STRING_NODE_COMPARISON_CALLBACK);
    BinaryTree->add(root, "2");
    BinaryTree->add(root, "3");
    BinaryTree->add(root, "0 is lesser than the root value");

    // when checking its height
    int height = BinaryTree->height(root);

    // then it should be 3
    cr_assert_eq(
        3,
        height,
        "Height should be the 'greater-values height' when its greater than the 'lesser-values height'"
    );
}


Test(binary_tree, finds_nothing_in_null_tree)
{
    // given a null tree
    _BinaryTree * tree = NULL;

    // when trying to find any node in it
    _BinaryTree * node = BinaryTree->find(tree, "any value");

    // then it should be NULL
    cr_assert_null(
        node,
        "No node should be found in a null tree"
    );
}


Test(binary_tree, finds_root_node)
{
    // given a tree made of only its root
    _BinaryTree * tree = BinaryTree->constructor("root node", STRING_NODE_COMPARISON_CALLBACK);

    // when trying to find the root node from its value
    _BinaryTree * node = BinaryTree->find(tree, "root node");

    // then the found node should be the root one
    cr_assert_eq(
        tree,
        node,
        "Root node should be found when it's the only one in the tree"
    );
}


Test(binary_tree, finds_lesser_value)
{
    // given a tree with an added lesser value
    _BinaryTree * root = BinaryTree->constructor("root node", STRING_NODE_COMPARISON_CALLBACK);
    _BinaryTree * lesser = BinaryTree->add(root, "lesser value");

    // when trying to find the added lesser value
    _BinaryTree * found = BinaryTree->find(root, "lesser value");

    // then it should be the added node
    cr_assert_eq(
        lesser,
        found,
        "Node should be found when its value is lesser than the root"
    );
}


Test(binary_tree, finds_greater_value)
{
    // given a tree with an added greater value
    _BinaryTree * root = BinaryTree->constructor("root", STRING_NODE_COMPARISON_CALLBACK);
    _BinaryTree * greater = BinaryTree->add(root, "superior value");

    // when trying to find the added greater value
    _BinaryTree * found = BinaryTree->find(root, "superior value");

    // then it should be the added node
    cr_assert_eq(
        greater,
        found,
        "Node should be found when its value is greater than the root"
    );
}


Test(binary_tree, detaches_nothing_in_null_tree)
{
    // given a null tree
    _BinaryTree * tree = NULL;

    // when trying to detach it
    BinaryTree->detach(tree);

    // then it shouldn't crash
}


Test(binary_tree, has_no_effect_on_root)
{
    // given a tree made of only its root
    _BinaryTree * root = BinaryTree->constructor("root", STRING_NODE_COMPARISON_CALLBACK);

    // when trying to detach it
    BinaryTree->detach(root);

    // then it shouldn't crash
}


Test(binary_tree, null_tree_has_no_root)
{
    // given a null tree
    _BinaryTree * tree = NULL;

    // when trying to find its root
    _BinaryTree * root = BinaryTree->root(tree);

    // then there should be none
    cr_assert_null(
        root,
        "Null tree should have no root"
    );
}


Test(binary_tree, finds_root_of_tree)
{
    // given a tree with more than 1 value
    _BinaryTree * tree = BinaryTree->constructor("root", STRING_NODE_COMPARISON_CALLBACK);
    _BinaryTree * leaf = BinaryTree->add(tree, "leaf");

    // when trying to find its root from any leaf
    _BinaryTree * root = BinaryTree->root(leaf);

    // then it should be the right one
    cr_assert_eq(
        tree,
        root,
        "Expected to get the top-most node"
    );
}


Test(binary_tree, detached_node_is_not_in_tree_anymore)
{
    // given a tree with 2 values
    _BinaryTree * tree = BinaryTree->constructor("root", STRING_NODE_COMPARISON_CALLBACK);
    _BinaryTree * son = BinaryTree->add(tree, "son");

    // when detaching a non-root node from the tree
    BinaryTree->detach(son);

    // then the detached node is not in the tree anymore
    cr_assert_null(
        BinaryTree->find(tree, "son"),
        "Detached node shouldn't be accessible from the tree anymore"
    );
}


Test(binary_tree, detached_node_has_no_parent_anymore)
{
    // given a tree with 2 values
    _BinaryTree * tree = BinaryTree->constructor("root", STRING_NODE_COMPARISON_CALLBACK);
    _BinaryTree * son = BinaryTree->add(tree, "son");

    // when detaching a non-root node from the tree
    BinaryTree->detach(son);

    // then the detached node should be the root of a new tree
    cr_assert_eq(
        son,
        BinaryTree->root(son),
        "Detached node shouldn't have parent anymore"
    );
}

Test(binary_tree, null_tree_cant_be_popped)
{
    // given a null tree
    _BinaryTree * tree = NULL;

    // when trying to pop it
    BinaryTree->pop(tree, NULL);

    // then it shouldn't crash
}


Test(binary_tree, popping_node_with_only_left_son_removes_it_from_the_tree)
{
    // given a tree containing a node with no right son
    _BinaryTree * tree = BinaryTree->constructor("root", STRING_NODE_COMPARISON_CALLBACK);
    _BinaryTree * node = BinaryTree->add(tree, "node with only left son");
    _BinaryTree * leaf = BinaryTree->add(tree, "leaf");

    // when popping that node
    BinaryTree->pop(tree, "node with only left son");

    // then it shouldn't be in the tree anymore
    cr_assert_eq(
        0,
        BinaryTree->contains(tree, "node with only left son"),
        "Popped node should be removed from the tree"
    );
}


Test(binary_tree, popping_node_with_only_left_son_becomes_a_root)
{
    // given a tree containing a node with no right son
    _BinaryTree * tree = BinaryTree->constructor("root", STRING_NODE_COMPARISON_CALLBACK);
    _BinaryTree * node = BinaryTree->add(tree, "node with only left son");
    _BinaryTree * leaf = BinaryTree->add(tree, "leaf");

    // when popping that node
    BinaryTree->pop(tree, "node with only left son");

    // then it should be its own root afterwards
    cr_assert_eq(
        node,
        BinaryTree->root(node),
        "Popped node should be its own root"
    );
}


Test(binary_tree, popping_node_with_only_left_son_makes_a_single_node_tree)
{
    // given a tree containing a node with no right son
    _BinaryTree * tree = BinaryTree->constructor("root", STRING_NODE_COMPARISON_CALLBACK);
    _BinaryTree * node = BinaryTree->add(tree, "node with only left son");
    _BinaryTree * leaf = BinaryTree->add(tree, "leaf");

    // when popping that node
    BinaryTree->pop(tree, "node with only left son");

    // the the node should become a tree of height 1
    cr_assert_eq(
        1,
        BinaryTree->height(node),
        "Popped node should become a tree of height 1"
    );
}


Test(binary_tree, popping_node_with_only_left_son_lets_sons_in_tree)
{
    // given a tree containing a node with no right son
    _BinaryTree * tree = BinaryTree->constructor("root", STRING_NODE_COMPARISON_CALLBACK);
    _BinaryTree * node = BinaryTree->add(tree, "node with only left son");
    _BinaryTree * leaf = BinaryTree->add(tree, "leaf");

    // when popping that node
    BinaryTree->pop(tree, "node with only left son");

    // then the sons the popped node had before should still be accessible from the tree
    cr_assert_neq(
        0,
        BinaryTree->contains(tree, "leaf"),
        "Popped node's sons should remain in the tree"
    );
}


Test(binary_tree, popping_node_with_only_right_son_removes_it_from_the_tree)
{
    // given a tree containing a node with no left son
    _BinaryTree * tree = BinaryTree->constructor("n1=root", STRING_NODE_COMPARISON_CALLBACK);
    _BinaryTree * node = BinaryTree->add(tree, "n2=node with only right son");
    _BinaryTree * leaf = BinaryTree->add(tree, "n3=leaf");

    // when popping that node
    BinaryTree->pop(tree, "n2=node with only right son");

    // then it shouldn't be in the tree anymore
    cr_assert_eq(
        0,
        BinaryTree->contains(tree, "n2=node with only left son"),
        "Popped node should be removed from the tree"
    );
}


Test(binary_tree, popping_node_with_only_right_son_becomes_a_root)
{
    // given a tree containing a node with no left son
    _BinaryTree * tree = BinaryTree->constructor("n1=root", STRING_NODE_COMPARISON_CALLBACK);
    _BinaryTree * node = BinaryTree->add(tree, "n2=node with only right son");
    _BinaryTree * leaf = BinaryTree->add(tree, "n3=leaf");

    // when popping that node
    BinaryTree->pop(tree, "n2=node with only right son");

    // then it should be its own root afterwards
    cr_assert_eq(
        node,
        BinaryTree->root(node),
        "Popped node should be its own root"
    );
}


Test(binary_tree, popping_node_with_only_right_son_makes_a_single_node_tree)
{
    // given a tree containing a node with no left son
    _BinaryTree * tree = BinaryTree->constructor("n1=root", STRING_NODE_COMPARISON_CALLBACK);
    _BinaryTree * node = BinaryTree->add(tree, "n2=node with only right son");
    _BinaryTree * leaf = BinaryTree->add(tree, "n3=leaf");

    // when popping that node
    BinaryTree->pop(tree, "n2=node with only right son");

    // the the node should become a tree of height 1
    cr_assert_eq(
        1,
        BinaryTree->height(node),
        "Popped node should become a tree of height 1"
    );
}


Test(binary_tree, popping_node_with_only_right_son_lets_sons_in_tree)
{
    // given a tree containing a node with no left son
    _BinaryTree * tree = BinaryTree->constructor("n1=root", STRING_NODE_COMPARISON_CALLBACK);
    _BinaryTree * node = BinaryTree->add(tree, "n2=node with only right son");
    _BinaryTree * leaf = BinaryTree->add(tree, "n3=leaf");

    // when popping that node
    BinaryTree->pop(tree, "n2=node with only right son");

    // then the sons the popped node had before should still be accessible from the tree
    cr_assert_neq(
        0,
        BinaryTree->contains(tree, "n3=leaf"),
        "Popped node's sons should remain in the tree"
    );
}


Test(binary_tree, popping_node_with_2_sons_removes_it_from_the_tree)
{
    // given a tree containing a node with 2 sons
    _BinaryTree * tree = BinaryTree->constructor("root", STRING_NODE_COMPARISON_CALLBACK);
    _BinaryTree * node = BinaryTree->add(tree, "node with 2 sons");
    _BinaryTree * leftLeaf = BinaryTree->add(tree, "left leaf");
    _BinaryTree * rightLeaf  = BinaryTree->add(tree, "right leaf");

    // when popping that node
    BinaryTree->pop(tree, "node with 2 sons");

    // then it shouldn't be in the tree anymore
    cr_assert_eq(
        0,
        BinaryTree->contains(tree, "node with 2 sons"),
        "Popped node should be removed from the tree"
    );
}


Test(binary_tree, popping_node_with_2_sons_becomes_a_root)
{
    // given a tree containing a node with 2 sons
    _BinaryTree * tree = BinaryTree->constructor("root", STRING_NODE_COMPARISON_CALLBACK);
    _BinaryTree * node = BinaryTree->add(tree, "node with 2 sons");
    _BinaryTree * leftLeaf = BinaryTree->add(tree, "left leaf");
    _BinaryTree * rightLeaf  = BinaryTree->add(tree, "right leaf");

    // when popping that node
    BinaryTree->pop(tree, "node with 2 sons");

    // then it should be its own root afterwards
    cr_assert_eq(
        node,
        BinaryTree->root(node),
        "Popped node should be its own root"
    );
}


Test(binary_tree, popping_node_with_2_sons_makes_a_single_node_tree)
{
    // given a tree containing a node with 2 sons
    _BinaryTree * tree = BinaryTree->constructor("root", STRING_NODE_COMPARISON_CALLBACK);
    _BinaryTree * node = BinaryTree->add(tree, "node with 2 sons");
    _BinaryTree * leftLeaf = BinaryTree->add(tree, "left leaf");
    _BinaryTree * rightLeaf  = BinaryTree->add(tree, "right leaf");

    // when popping that node
    BinaryTree->pop(tree, "node with 2 sons");

    // the the node should become a tree of height 1
    cr_assert_eq(
        1,
        BinaryTree->height(node),
        "Popped node should become a tree of height 1"
    );
}


Test(binary_tree, popping_node_with_2_sons_lets_sons_in_tree)
{
    // given a tree containing a node with 2 sons
    _BinaryTree * tree = BinaryTree->constructor("root", STRING_NODE_COMPARISON_CALLBACK);
    _BinaryTree * node = BinaryTree->add(tree, "node with 2 sons");
    _BinaryTree * leftLeaf = BinaryTree->add(tree, "left leaf");
    _BinaryTree * rightLeaf  = BinaryTree->add(tree, "right leaf");

    // when popping that node
    BinaryTree->pop(tree, "node with 2 sons");

    // then the sons the popped node had before should still be accessible from the tree
    cr_assert_neq(
        0,
        BinaryTree->contains(tree, "left leaf"),
        "Popped node's left son should remain in the tree"
    );
    cr_assert_neq(
        0,
        BinaryTree->contains(tree, "right leaf"),
        "Popped node's right son should remain in the tree"
    );
}


// Visited nodes order will be written here
static int visitedNodesBufferIndex;
static char visitedNodesBuffer[9];


static void addVisitedNodeCallbackSetup(void)
{
    extern int visitedNodesBufferIndex;
    visitedNodesBufferIndex = 0;
}


static void addVisitedNodeCallback(void const * const value)
{
    extern int visitedNodesBufferIndex;
    extern char visitedNodesBuffer[];
    visitedNodesBuffer[visitedNodesBufferIndex++] = ((char *) value)[0];
}


Test(binary_tree, mapping_pre_order_visits_node_with_pre_order, .init=addVisitedNodeCallbackSetup)
{
    // given a tree with several nodes
    _BinaryTree * tree = BinaryTree->constructor("F", STRING_NODE_COMPARISON_CALLBACK);
    BinaryTree->add(tree, "B");
    BinaryTree->add(tree, "G");
    BinaryTree->add(tree, "A");
    BinaryTree->add(tree, "D");
    BinaryTree->add(tree, "I");
    BinaryTree->add(tree, "C");
    BinaryTree->add(tree, "E");
    BinaryTree->add(tree, "H");

    // when applying the callback to each node with pre-order
    BinaryTree->map(tree, addVisitedNodeCallback, PreOrder);

    // then nodes should be visited in pre-order
    cr_assert_str_eq(
        "FBADCEGIH",
        visitedNodesBuffer,
        "Wrong nodes order, got %s", visitedNodesBuffer
    );
}


Test(binary_tree, mapping_in_order_visits_node_with_in_order, .init=addVisitedNodeCallbackSetup)
{
    // given a tree with several nodes
    _BinaryTree * tree = BinaryTree->constructor("F", STRING_NODE_COMPARISON_CALLBACK);
    BinaryTree->add(tree, "B");
    BinaryTree->add(tree, "G");
    BinaryTree->add(tree, "A");
    BinaryTree->add(tree, "D");
    BinaryTree->add(tree, "I");
    BinaryTree->add(tree, "C");
    BinaryTree->add(tree, "E");
    BinaryTree->add(tree, "H");

    // when applying the callback to each node with in-order
    BinaryTree->map(tree, addVisitedNodeCallback, InOrder);

    // then nodes should be visited with in-order
    cr_assert_str_eq(
        "ABCDEFGHI",
        visitedNodesBuffer,
        "Wrong nodes order, got %s", visitedNodesBuffer
    );
}


Test(binary_tree, mapping_post_order_visits_node_with_post_order, .init=addVisitedNodeCallbackSetup)
{
    // given a tree with several nodes
    _BinaryTree * tree = BinaryTree->constructor("F", STRING_NODE_COMPARISON_CALLBACK);
    BinaryTree->add(tree, "B");
    BinaryTree->add(tree, "G");
    BinaryTree->add(tree, "A");
    BinaryTree->add(tree, "D");
    BinaryTree->add(tree, "I");
    BinaryTree->add(tree, "C");
    BinaryTree->add(tree, "E");
    BinaryTree->add(tree, "H");

    // when applying the callback to each node with post-order
    BinaryTree->map(tree, addVisitedNodeCallback, PostOrder);

    // then nodes should be visited with post-order
    cr_assert_str_eq(
        "ACEDBHIGF",
        visitedNodesBuffer,
        "Wrong nodes order, got %s", visitedNodesBuffer
    );
}
