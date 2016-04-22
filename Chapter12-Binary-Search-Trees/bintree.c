/*
 * Solutions-to-CLRS/Chapter12-Binary-Search-Trees/bintree.c
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#include "bintree.h"
#include "queue.h"
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
                parent->right = newPtr;
        } else {
                parent->left = newPtr;
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

/*
 * Tree walk inorder.
 */
void TreeWalkInorder(struct bintree_s *treeRoot)
{
        if (treeRoot != NULL) {
                TreeWalkInorder(treeRoot->left);
                printf("%d ", treeRoot->value);
                TreeWalkInorder(treeRoot->right);
        }
}

/*
 * Tree walk inlevel.
 */
void TreeWalkInlevel(struct bintree_s *treeRoot)
{
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
}
