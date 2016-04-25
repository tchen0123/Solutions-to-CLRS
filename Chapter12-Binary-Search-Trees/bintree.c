/*
 * Solutions-to-CLRS/Chapter12-Binary-Search-Trees/bintree.c
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#include "bintree.h"
#include "queue.h"
#include "pre_tree_walk.h"
#include <stdlib.h>
#include <stdio.h>

/*
 * Create a new node.
 */
static inline struct bintree_s *CreateNode(int num)
{
        struct bintree_s *newNode = (struct bintree_s *)malloc(sizeof(struct bintree_s));
        newNode->value = num;
        newNode->parent = NULL;
        newNode->left = newNode->right = NULL;

        return newNode;
}

static struct bintree_s *Transplant(struct bintree_s *treeRoot, struct bintree_s *oldPtr, struct bintree_s *newPtr);
static struct bintree_s *Minimum(struct bintree_s *treeRoot);
static struct bintree_s *Maximum(struct bintree_s *treeRoot);

/*
 * Search a node in the binary search tree.
 */
struct bintree_s *BintreeSearch(struct bintree_s *treeRoot, int num)
{
        while (treeRoot != NULL && treeRoot->value != num) {
                if (treeRoot->value > num) {
                        treeRoot = treeRoot->left;
                } else {
                        treeRoot = treeRoot->right;
                }
        }

        return treeRoot;
}

/*
 * Insert a new element to the binary search tree.
 */
struct bintree_s *BintreeInsert(struct bintree_s *treeRoot, int num)
{
        struct bintree_s *parent, *curr;
        parent = NULL;
        curr = treeRoot;
        while (curr != NULL) {
                parent = curr;

                if (curr->value > num) {
                        curr = curr->left;
                } else if (curr->value < num) {
                        curr = curr->right;
                } else {
                        return treeRoot;
                }
        }

        struct bintree_s *newNode = CreateNode(num);
        newNode->parent = parent;
        if (parent == NULL) {
                treeRoot = newNode;
        } else if (parent->value > num) {
                parent->left = newNode;
        } else {
                parent->right = newNode;
        }

        return treeRoot;
}

/*
 * Delete a node int the binary search tree.
 */
struct bintree_s *BintreeDelete(struct bintree_s *treeRoot, int num)
{
        struct bintree_s *targetPtr = BintreeSearch(treeRoot, num);
        if (targetPtr == NULL) {
                return treeRoot;
        }

        if (targetPtr->left == NULL) {
                treeRoot = Transplant(treeRoot, targetPtr, targetPtr->right);
        } else if (targetPtr->right == NULL) {
                treeRoot = Transplant(treeRoot, targetPtr, targetPtr->left);
        } else {
                struct bintree_s *minPtr = Minimum(targetPtr->right);

                if (minPtr != targetPtr->right) {
                        treeRoot = Transplant(treeRoot, minPtr, minPtr->right);
                        minPtr->right = targetPtr->right;
                        minPtr->right->parent = minPtr;
                }
                treeRoot = Transplant(treeRoot, targetPtr, minPtr);
                minPtr->left = targetPtr->left;
                minPtr->left->parent = minPtr;
        }
        free(targetPtr);

        return treeRoot;
}

/*
 * Tree transplant.
 */
static struct bintree_s *Transplant(struct bintree_s *treeRoot, struct bintree_s *oldPtr, struct bintree_s *newPtr)
{
        struct bintree_s *parent = oldPtr->parent;
        if (newPtr != NULL) {
                newPtr->parent = parent;
        }

        if (parent == NULL) {
                treeRoot = newPtr;
        } else if (parent->left == oldPtr) {
                parent->left = newPtr;
        } else {
                parent->right = newPtr;
        }

        return treeRoot;
}

/*
 * Search the minimum node of treeRoot.
 */
static struct bintree_s *Minimum(struct bintree_s *treeRoot)
{
        if (treeRoot == NULL) {
                return treeRoot;
        }

        while (treeRoot->left != NULL) {
                treeRoot = treeRoot->left;
        }
        return treeRoot;
}

static struct bintree_s *Maximum(struct bintree_s *treeRoot)
{
        if (treeRoot == NULL) {
                return treeRoot;
        }

        while (treeRoot->right != NULL) {
                treeRoot = treeRoot->right;
        }
        return treeRoot;
}

/*
 * Tree walk inorder.
 */
void TreeWalkInorder(struct bintree_s *treeRoot)
{
        struct bintree_s *treeNode = treeRoot;
        struct preWalk_s *stack = InitPreWalk();

        /* Depth first search */
        while (treeNode || !PreWalkIsEmpty(stack)) {
                if (treeNode) {
                        PreWalkPush(stack, treeNode);

                        treeNode = treeNode->left;
                } else {
                        treeNode = PreWalkPop(stack);

                        printf("%d ", treeNode->value);

                        treeNode = treeNode->right;
                }
        }
        DeletePreWalk(stack);
}

/*
 * Tree walk preorder.
 */
void TreeWalkPreorder(struct bintree_s *treeRoot)
{
        struct bintree_s *treeNode = treeRoot;
        struct preWalk_s *stack = InitPreWalk();

        /* Depth first search */
        while (treeNode || !PreWalkIsEmpty(stack)) {
                if (treeNode) {
                        printf("%d ", treeNode->value);

                        PreWalkPush(stack, treeNode);

                        treeNode = treeNode->left;
                } else {
                        treeNode = PreWalkPop(stack);

                        treeNode = treeNode->right;
                }
        }
        DeletePreWalk(stack);

}

void TreeWalkPostorder(struct bintree_s *treeRoot)
{
}

/*
 * Tree walk inlevel.
 */
void TreeWalkInlevel(struct bintree_s *treeRoot)
{
        if (treeRoot == NULL) {
                return;
        }

        struct queue_s *queue = InitQueue();

        EnQueue(queue, treeRoot);
        EnQueue(queue, NULL);
        do {
                struct bintree_s *treePtr = DeQueue(queue);

                if (treePtr) {
                        printf("%d ", treePtr->value);

                        if (treePtr->left) {
                                EnQueue(queue, treePtr->left);
                        }
                        if (treePtr->right) {
                                EnQueue(queue, treePtr->right);
                        }
                } else if (!QueueIsEmpty(queue)) {
                        printf("\n");

                        EnQueue(queue, NULL);
                }
        } while (!QueueIsEmpty(queue));

        DeleteQueue(queue);
}

/*
 * Delete the whole tree.
 */
void DeleteBinTree(struct bintree_s *treeRoot)
{
        if (treeRoot != NULL) {
                DeleteBinTree(treeRoot->left);
                DeleteBinTree(treeRoot->right);
                free(treeRoot);
        }
}

/*
 * Search successor node.
 */
struct bintree_s *Successor(struct bintree_s *treeRoot)
{
        struct bintree_s *minPtr = Minimum(treeRoot->right);
        if (minPtr) {
                return minPtr;
        }

        struct bintree_s *parent, *curr;
        parent = treeRoot->parent;
        curr = treeRoot;
        while (parent != NULL && curr == parent->right) {
                curr = parent;
                parent = curr->parent;
        }
        return parent;
}

/*
 * Search the predecessor node.
 */
struct bintree_s *Predecessor(struct bintree_s *treeRoot)
{
        struct bintree_s *maxPtr = Maximum(treeRoot->left);
        if (maxPtr) {
                return maxPtr;
        }

        struct bintree_s *parent, *curr;
        parent = treeRoot->parent;
        curr = treeRoot;
        while (parent != NULL && curr == parent->left) {
                curr = parent;
                parent = curr->parent;
        }
        return parent;
}

/*
 * Invert the binary search tree, and output its mirror.
 * Using queue!
 */
void BintreeInvert(struct bintree_s *treeRoot)
{
        struct queue_s *queue = InitQueue();
        EnQueue(queue, treeRoot);

        do {
                struct bintree_s *treePtr = DeQueue(queue);

                /* Invert */
                struct bintree_s *tempPtr = treePtr->left;
                treePtr->left = treePtr->right;
                if (treePtr->left) {
                        treePtr->left->parent = treePtr;
                }
                treePtr->right = tempPtr;
                if (treePtr->right) {
                        treePtr->right->parent = treePtr;
                }

                if (treePtr->left) {
                        EnQueue(queue, treePtr->left);
                }
                if (treePtr->right) {
                        EnQueue(queue, treePtr->right);
                }
        } while (!QueueIsEmpty(queue));

        DeleteQueue(queue);

        TreeWalkInlevel(treeRoot);
}
