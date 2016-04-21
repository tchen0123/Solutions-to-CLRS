/*
 * Solutions-to-CLRS/Chapter13-Red-Black-Trees/rbtree.h
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#include "rbtree.h"
#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

static struct rbtree_s *rbtreeNil_g; // the sentinel tree nil

/*
 * Create a new tree node.
 */
static inline struct rbtree_s *CreateNode(int num)
{
        struct rbtree_s *newNode = (struct rbtree_s *)malloc(sizeof(struct rbtree_s));
        newNode->value = num;
        newNode->color = RB_RED;
        newNode->parent = rbtreeNil_g;
        newNode->left = newNode->right = rbtreeNil_g;

        return newNode;
}

static struct rbtree_s *Minimum(struct rbtree_s *treeRoot);
static struct rbtree_s *Search(struct rbtree_s *treeRoot, int num);
static struct rbtree_s *LeftRotate(struct rbtree_s *treeRoot, struct rbtree_s *targetPtr);
static struct rbtree_s *RightRotate(struct rbtree_s *treeRoot, struct rbtree_s *targetPtr);
static struct rbtree_s *RbtreeInsertFixup(struct rbtree_s *treeRoot, struct rbtree_s *targetPtr);
static struct rbtree_s *RbtreeDeleteFixup(struct rbtree_s *treeRoot, struct rbtree_s *targetPtr);
static struct rbtree_s *Transplant(struct rbtree_s *treeRoot, struct rbtree_s *oldPtr, struct rbtree_s *newPtr);
static void DeleteTreeFixup(struct rbtree_s *treeRoot);

/*
 * Tree walk inorder.
 */
void TreeWalkInorder(struct rbtree_s *treeRoot)
{
        if (treeRoot != rbtreeNil_g) {
                TreeWalkInorder(treeRoot->left);
                printf("%d ", treeRoot->value);
                TreeWalkInorder(treeRoot->right);
        }
}

/*
 * Tree insertion.
 */
struct rbtree_s *RbtreeInsert(struct rbtree_s *treeRoot, int num)
{
        struct rbtree_s *parent, *curr;
        parent = rbtreeNil_g;
        curr = treeRoot;
        while (curr != rbtreeNil_g) {
                parent = curr;

                if (curr->value > num) {
                        curr = curr->left;
                } else if (curr->value < num) {
                        curr = curr->right;
                } else {
                        return treeRoot;
                }
        }

        struct rbtree_s *newNode = CreateNode(num);
        newNode->parent = parent;
        if (parent == rbtreeNil_g) {
                treeRoot = newNode;
        } else if (parent->value > num) {
                parent->left = newNode;
        } else {
                parent->right = newNode;
        }

        treeRoot = RbtreeInsertFixup(treeRoot, newNode);

        return treeRoot;
}

/*
 * Fix up tree insertion.
 */
static struct rbtree_s *RbtreeInsertFixup(struct rbtree_s *treeRoot, struct rbtree_s *targetPtr)
{
        while (targetPtr->parent->color == RB_RED) {
                if (targetPtr->parent == targetPtr->parent->parent->left) {
                        struct rbtree_s *uncle = targetPtr->parent->parent->right;

                        if (uncle->color == RB_RED) {
                                targetPtr->parent->parent->color = RB_RED;
                                targetPtr->parent->color = RB_BLACK;
                                uncle->color = RB_BLACK;

                                targetPtr = targetPtr->parent->parent;
                        } else {
                                if (targetPtr == targetPtr->parent->right) {
                                        targetPtr = targetPtr->parent;

                                        treeRoot = LeftRotate(treeRoot, targetPtr);
                                }
                                targetPtr->parent->parent->color = RB_RED;
                                targetPtr->parent->color = RB_BLACK;
                                targetPtr = targetPtr->parent->parent;

                                treeRoot = RightRotate(treeRoot, targetPtr);
                        }
                } else {
                        struct rbtree_s *uncle = targetPtr->parent->parent->left;

                        if (uncle->color == RB_RED) {
                                targetPtr->parent->parent->color = RB_RED;
                                targetPtr->parent->color = RB_BLACK;
                                uncle->color = RB_BLACK;

                                targetPtr = targetPtr->parent->parent;
                        } else {
                                if (targetPtr == targetPtr->parent->left) {
                                        targetPtr = targetPtr->parent;

                                        treeRoot = RightRotate(treeRoot, targetPtr);
                                }
                                targetPtr->parent->parent->color = RB_RED;
                                targetPtr->parent->color = RB_BLACK;
                                targetPtr = targetPtr->parent->parent;

                                treeRoot = LeftRotate(treeRoot, targetPtr);
                        }
                }
        }
        treeRoot->color = RB_BLACK;

        return treeRoot;
}

/*
 * Tree right rotate.
 */
static struct rbtree_s *RightRotate(struct rbtree_s *treeRoot, struct rbtree_s *targetPtr)
{
        struct rbtree_s *left = targetPtr->left;
        targetPtr->left = left->right;
        if (targetPtr->left != rbtreeNil_g) {
                targetPtr->left->parent = targetPtr;
        }

        struct rbtree_s *parent = targetPtr->parent;
        left->parent = parent;
        if (parent == rbtreeNil_g) {
                treeRoot = left;
        } else if (parent->left == targetPtr) {
                parent->left = left;
        } else {
                parent->right = left;
        }

        left->right = targetPtr;
        targetPtr->parent = left;

        return treeRoot;
}

/*
 * Tree left rotate.
 */
static struct rbtree_s *LeftRotate(struct rbtree_s *treeRoot, struct rbtree_s *targetPtr)
{
        struct rbtree_s *right = targetPtr->right;
        targetPtr->right = right->left;
        if (targetPtr->right != rbtreeNil_g) {
                targetPtr->right->parent = targetPtr;
        }

        struct rbtree_s *parent = targetPtr->parent;
        right->parent = parent;
        if (parent == rbtreeNil_g) {
                treeRoot = right;
        } else if (parent->left == targetPtr) {
                parent->left = right;
        } else {
                parent->right = right;
        }

        right->left = targetPtr;
        targetPtr->parent = right;

        return treeRoot;
}

/*
 * Initialize the sentinel tree nil
 */
struct rbtree_s *InitRbtreeNil(void)
{
        rbtreeNil_g = (struct rbtree_s *)malloc(sizeof(struct rbtree_s));
        rbtreeNil_g->color = RB_BLACK;

        return rbtreeNil_g;
}

void TreeWalkInlevel(struct rbtree_s *treeRoot)
{
        if (treeRoot == rbtreeNil_g) {
                return;
        }

        struct queue_s *queue = InitQueue();

        /* breadth first search */
        EnQueue(queue, treeRoot);
        EnQueue(queue, NULL); // newline
        do {
                struct rbtree_s *treeNode = DeQueue(queue);

                if (treeNode) {
                        printf("%d ", treeNode->value);

                        if (treeNode->left != rbtreeNil_g) {
                                EnQueue(queue, treeNode->left);
                        }
                        if (treeNode->right != rbtreeNil_g) {
                                EnQueue(queue, treeNode->right);
                        }
                } else if (!QueueIsEmpty(queue)) {
                        printf("\n");
                        EnQueue(queue, NULL); // newline
                }
        } while (!QueueIsEmpty(queue));

        /* free the queue */
        free(queue);
}

/*
 * Tree transplant.
 */
static struct rbtree_s *Transplant(struct rbtree_s *treeRoot, struct rbtree_s *oldPtr, struct rbtree_s *newPtr)
{
        struct rbtree_s *parent = oldPtr->parent;
        newPtr->parent = parent;
        if (parent == rbtreeNil_g) {
                treeRoot = newPtr;
        } else if (parent->left == oldPtr) {
                parent->left = newPtr;
        } else {
                parent->right = newPtr;
        }

        return treeRoot;
}

static struct rbtree_s *RbtreeDeleteFixup(struct rbtree_s *treeRoot, struct rbtree_s *targetPtr)
{
        while (targetPtr != treeRoot && targetPtr->color == RB_BLACK) {
                if (targetPtr == targetPtr->parent->left) {
                        struct rbtree_s *brother = targetPtr->parent->right;

                        if (brother->color == RB_RED) {
                                brother->color = RB_BLACK;
                                targetPtr->parent->color = RB_RED;

                                treeRoot = LeftRotate(treeRoot, targetPtr->parent);
                                brother = targetPtr->parent->right;
                        }
                        if (brother->left->color == RB_BLACK && brother->right->color == RB_BLACK) {
                                brother->color = RB_RED;
                                targetPtr = targetPtr->parent;
                        } else {
                                if (brother->right->color == RB_BLACK) {
                                        brother->color = RB_RED;
                                        brother->left->color = RB_BLACK;
                                        treeRoot = RightRotate(treeRoot, brother);

                                        brother = targetPtr->parent->right;
                                }
                                brother->color = targetPtr->parent->color;
                                targetPtr->parent->color = RB_BLACK;
                                brother->right->color = RB_BLACK;
                                treeRoot = LeftRotate(treeRoot, targetPtr->parent);
                                targetPtr = treeRoot;
                        }
                } else {
                        struct rbtree_s *brother = targetPtr->parent->left;

                        if (brother->color == RB_RED) {
                                brother->color = RB_BLACK;
                                targetPtr->parent->color = RB_RED;

                                treeRoot = RightRotate(treeRoot, targetPtr->parent);
                                brother = targetPtr->parent->left;
                        }
                        if (brother->left->color == RB_BLACK && brother->right->color == RB_BLACK) {
                                brother->color = RB_RED;
                                targetPtr = targetPtr->parent;
                        } else {
                                if (brother->left->color == RB_BLACK) {
                                        brother->color = RB_RED;
                                        brother->right->color = RB_BLACK;
                                        treeRoot = LeftRotate(treeRoot, brother);
                                        brother = targetPtr->parent->left;
                                }
                                brother->color = targetPtr->parent->color;
                                targetPtr->parent->color = RB_BLACK;
                                brother->left->color = RB_BLACK;
                                treeRoot = RightRotate(treeRoot, targetPtr->parent);
                                targetPtr = treeRoot;
                        }
                }
        }
        targetPtr->color = RB_BLACK;

        return treeRoot;
}

struct rbtree_s *RbtreeDelete(struct rbtree_s *treeRoot, int num)
{
        struct rbtree_s *targetPtr = Search(treeRoot, num);

        if (targetPtr == rbtreeNil_g) {
                return treeRoot;
        }

        struct rbtree_s *yPtr, *xPtr;
        int yColor;

        yPtr = targetPtr;
        yColor = targetPtr->color;
        if (targetPtr->left == rbtreeNil_g) {
                xPtr = targetPtr->right;
                treeRoot = Transplant(treeRoot, targetPtr, targetPtr->right);
        } else if (treeRoot->right == rbtreeNil_g) {
                xPtr = targetPtr->left;
                treeRoot = Transplant(treeRoot, targetPtr, targetPtr->left);
        } else {
                yPtr = Minimum(targetPtr->right);
                yColor = yPtr->color;

                xPtr = yPtr->right;
                if (yPtr == targetPtr->right) {
                        xPtr->parent = yPtr;
                } else {
                        treeRoot = Transplant(treeRoot, yPtr, yPtr->right);
                        yPtr->right = targetPtr->right;
                        yPtr->right->parent = yPtr;
                }

                treeRoot = Transplant(treeRoot, targetPtr, yPtr);
                yPtr->left = targetPtr->left;
                yPtr->left->parent = yPtr;
                yPtr->color = targetPtr->color;
        }
        free(targetPtr);

        if (yColor == RB_BLACK) {
                treeRoot = RbtreeDeleteFixup(treeRoot, xPtr);
        }

        return treeRoot;
}

static struct rbtree_s *Search(struct rbtree_s *treeRoot, int num)
{
        while (treeRoot != rbtreeNil_g && treeRoot->value != num) {
                if (treeRoot->value > num) {
                        treeRoot = treeRoot->left;
                } else {
                        treeRoot = treeRoot->right;
                }
        }
        return treeRoot;
}

static struct rbtree_s *Minimum(struct rbtree_s *treeRoot)
{
        if (treeRoot == rbtreeNil_g) {
                return treeRoot;
        }

        while (treeRoot->left != rbtreeNil_g) {
                treeRoot = treeRoot->left;
        }
        return treeRoot;
}

/*
 * Delete the whole tree.
 */
void DeleteTree(struct rbtree_s *treeRoot)
{
        DeleteTreeFixup(treeRoot);

        free(rbtreeNil_g);
}

static void DeleteTreeFixup(struct rbtree_s *treeRoot)
{
        if (treeRoot != NULL && treeRoot != rbtreeNil_g) {
                DeleteTreeFixup(treeRoot->left);
                DeleteTreeFixup(treeRoot->right);
                free(treeRoot);
        }
}
