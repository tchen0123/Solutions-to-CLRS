/*
 * Solutions-to-CLRS/Chapter14-Augmenting-Data-Structures/ostree.cpp
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#include "ostree.h"
#include "queue.h"
#include <stdlib.h>
#include <iostream>

static struct ostree_s *treeNil_g; // Sentinel tree nil


/*
 * Create a new tree node.
 */
static inline struct ostree_s *CreateNode(int num)
{
        struct ostree_s *newNode = (struct ostree_s *)malloc(sizeof(struct ostree_s));
        newNode->value = num;
        newNode->color = RB_RED;
        newNode->parent = treeNil_g;
        newNode->left = newNode->right = treeNil_g;
        newNode->size = 1; // left.size + right.size + 1

        return newNode;
}

static inline unsigned int Rank(struct ostree_s *treePtr)
{
        if (treePtr != treeNil_g) {
                return treePtr->left->size + 1;
        } else {
                return 0;
        }
}

/*
 * Search the minimum node.
 */
static inline struct ostree_s *Minimum(struct ostree_s *treeRoot)
{
        while (treeRoot != treeNil_g && treeRoot->left != treeNil_g) {
                treeRoot = treeRoot->left;
        }
        return treeRoot;
}

static struct ostree_s *LeftRotate(struct ostree_s *treeRoot, struct ostree_s *targetPtr);
static struct ostree_s *RightRotate(struct ostree_s *treeRoot, struct ostree_s *targetPtr);
static struct ostree_s *Transplant(struct ostree_s *treeRoot, struct ostree_s *oldPtr, struct ostree_s *newPtr);
static struct ostree_s *OstreeInsertFixup(struct ostree_s *treeRoot, struct ostree_s *targetPtr);
static struct ostree_s *OstreeDeleteFixup(struct ostree_s *treeRoot, struct ostree_s *targetPtr);


/*
 * Initialize tree nil.
 */
struct ostree_s *InitOstreeNil(void)
{
        treeNil_g = (struct ostree_s *)malloc(sizeof(struct ostree_s));
        treeNil_g->color = RB_BLACK;
        treeNil_g->size = 0;

        return treeNil_g;
}

/*
 * Ostree insertion.
 */
struct ostree_s *OstreeInsert(struct ostree_s *treeRoot, int num)
{
        struct ostree_s *prev = treeNil_g;
        struct ostree_s *curr = treeRoot;

        while (curr != treeNil_g) {
                prev = curr;
                curr->size++;

                if (curr->value > num) {
                        curr = curr->left;
                } else {
                        curr = curr->right;
                }
        }

        // link
        struct ostree_s *newNode = CreateNode(num);
        newNode->parent = prev;
        if (prev == treeNil_g) {
                treeRoot = newNode;
        } else if (prev->value > num) {
                prev->left = newNode;
        } else {
                prev->right = newNode;
        }

        treeRoot = OstreeInsertFixup(treeRoot, newNode);

        return treeRoot;
}

/*
 * Ostree deletion.
 */
struct ostree_s *OstreeDelete(struct ostree_s *treeRoot, int num)
{
        // Search
        struct ostree_s *targetPtr = OstreeSearch(treeRoot, num);
        if (targetPtr == treeNil_g) {
                return treeRoot;
        }

        // Reduce size
        struct ostree_s *temp = targetPtr;
        while (temp != treeNil_g) {
                temp->size--;
                temp = temp->parent;
        }

        struct ostree_s *yPtr = targetPtr, *xPtr = nullptr;
        bool yColor = yPtr->color;

        if (targetPtr->left == treeNil_g) {
                xPtr = targetPtr->right;
                treeRoot = Transplant(treeRoot, targetPtr, targetPtr->right);
        } else if (targetPtr->right == treeNil_g) {
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
                treeRoot = OstreeDeleteFixup(treeRoot, xPtr);
        }

        return treeRoot;
}

/*
 * Ostree lefet rotation.
 */
static struct ostree_s *LeftRotate(struct ostree_s *treeRoot, struct ostree_s *targetPtr)
{
        struct ostree_s *right = targetPtr->right;
        targetPtr->right = right->left;
        if (targetPtr->right != treeNil_g) {
                targetPtr->right->parent = targetPtr;
        }

        struct ostree_s *parent = targetPtr->parent;
        right->parent = parent;
        if (parent == treeNil_g) {
                treeRoot = right;
        } else if (parent->left == targetPtr) {
                parent->left = right;
        } else {
                parent->right = right;
        }

        right->left = targetPtr;
        targetPtr->parent = right;

        right->size = targetPtr->size;
        targetPtr->size = targetPtr->left->size + targetPtr->right->size + 1;

        return treeRoot;
}

/*
 * Ostree right rotation.
 */
static struct ostree_s *RightRotate(struct ostree_s *treeRoot, struct ostree_s *targetPtr)
{
        struct ostree_s *left = targetPtr->left;
        targetPtr->left = left->right;
        if (targetPtr->left != treeNil_g) {
                targetPtr->left->parent = targetPtr;
        }

        struct ostree_s *parent = targetPtr->parent;
        left->parent = parent;
        if (parent == treeNil_g) {
                treeRoot = left;
        } else if (parent->left == targetPtr) {
                parent->left = left;
        } else {
                parent->right = left;
        }

        left->right = targetPtr;
        targetPtr->parent = left;

        left->size = targetPtr->size;
        targetPtr->size = targetPtr->left->size + targetPtr->right->size + 1;

        return treeRoot;
}

/*
 * Ostree transplant.
 */
static struct ostree_s *Transplant(struct ostree_s *treeRoot, struct ostree_s *oldPtr, struct ostree_s *newPtr)
{
        struct ostree_s *parent = oldPtr->parent;
        newPtr->parent = parent;
        if (parent == treeNil_g) {
                treeRoot = newPtr;
        } else if (parent->left == oldPtr) {
                parent->left = newPtr;
        } else {
                parent->right = newPtr;
        }

        return treeRoot;
}

/*
 * Ostree insertion fix up.
 */
static struct ostree_s *OstreeInsertFixup(struct ostree_s *treeRoot, struct ostree_s *targetPtr)
{
        while (targetPtr->parent->color == RB_RED) {
                if (targetPtr->parent == targetPtr->parent->parent->left) {
                        struct ostree_s *uncle = targetPtr->parent->parent->right;

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

                                treeRoot = RightRotate(treeRoot, targetPtr->parent->parent);
                        }
                } else {
                        struct ostree_s *uncle = targetPtr->parent->parent->left;

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

                                treeRoot = LeftRotate(treeRoot, targetPtr->parent->parent);
                        }
                }
        }
        treeRoot->color = RB_BLACK;

        return treeRoot;
}

/*
 * Ostree deletion fix up.
 */
static struct ostree_s *OstreeDeleteFixup(struct ostree_s *treeRoot, struct ostree_s *targetPtr)
{
        while (targetPtr != treeRoot && targetPtr->color == RB_BLACK) {
                if (targetPtr == targetPtr->parent->left) {
                        struct ostree_s *sibling = targetPtr->parent->right;

                        if (sibling->color == RB_RED) {
                                sibling->color = RB_BLACK;
                                targetPtr->parent->color = RB_RED;

                                treeRoot = LeftRotate(treeRoot, targetPtr->parent);
                                sibling = targetPtr->parent->right;
                        }
                        if (sibling->left->color == RB_BLACK && sibling->right->color == RB_BLACK) {
                                sibling->color = RB_RED;
                                targetPtr = targetPtr->parent;
                        } else {
                                if (sibling->right->color == RB_BLACK) {
                                        sibling->color = RB_RED;
                                        sibling->left->color = RB_BLACK;

                                        treeRoot = RightRotate(treeRoot, sibling);
                                        sibling = targetPtr->parent->right;
                                }
                                sibling->color = targetPtr->parent->color;
                                targetPtr->parent->color = RB_BLACK;
                                sibling->right->color = RB_BLACK;

                                treeRoot = LeftRotate(treeRoot, targetPtr->parent);
                                targetPtr = treeRoot;
                        }
                } else {
                        struct ostree_s *sibling = targetPtr->parent->left;

                        if (sibling->color == RB_RED) {
                                sibling->color = RB_BLACK;
                                targetPtr->parent->color = RB_RED;

                                treeRoot = RightRotate(treeRoot, targetPtr->parent);
                                sibling = targetPtr->parent->left;
                        }
                        if (sibling->left->color == RB_BLACK && sibling->right->color == RB_BLACK) {
                                sibling->color = RB_RED;
                                targetPtr = targetPtr->parent;
                        } else {
                                if (sibling->left->color == RB_BLACK) {
                                        sibling->color = RB_RED;
                                        sibling->right->color = RB_BLACK;

                                        treeRoot = LeftRotate(treeRoot, sibling);
                                        sibling = targetPtr->parent->left;
                                }
                                sibling->color = targetPtr->parent->color;
                                targetPtr->parent->color = RB_BLACK;
                                sibling->left->color = RB_BLACK;

                                treeRoot = RightRotate(treeRoot, targetPtr->parent);
                                targetPtr = treeRoot;
                        }
                }
        }
        targetPtr->color = RB_BLACK;

        return treeRoot;
}

/*
 * Ostree walk by level.
 */
void OstreeWalkBylevel(struct ostree_s *treeRoot)
{
        if (treeRoot == nullptr || treeRoot == treeNil_g) {
                return;
        }

        struct queue_s *queue = InitQueue();

        // Breadth first search
        EnQueue(queue, treeRoot);
        EnQueue(queue, nullptr);
        do {
                struct ostree_s *treePtr = DeQueue(queue);

                if (treePtr) {
                        std::cout << treePtr->value << ' ';

                        if (treePtr->left != treeNil_g) {
                                EnQueue(queue, treePtr->left);
                        }
                        if (treePtr->right != treeNil_g) {
                                EnQueue(queue, treePtr->right);
                        }
                } else if (!QueueIsEmpty(queue)) {
                        std::cout << std::endl;
                        EnQueue(queue, nullptr);
                }
        } while (!QueueIsEmpty(queue));
}

/*
 * Select the tree node ranked rank.
 */
struct ostree_s *OstreeSelect(struct ostree_s *treeRoot, unsigned int rank)
{
        unsigned int tempRank = Rank(treeRoot);
        while (treeRoot != treeNil_g && tempRank != rank) {
                if (tempRank > rank) {
                        treeRoot = treeRoot->left;
                } else {
                        treeRoot = treeRoot->right;
                        rank -= tempRank;
                }
                tempRank = Rank(treeRoot);
        }

        if (treeRoot != treeNil_g) {
                return treeRoot;
        } else {
                return nullptr;
        }
}

/*
 * Calculate the rank of the tree node.
 */
unsigned int OstreeRank(struct ostree_s *treeRoot, struct ostree_s *targetPtr)
{
        unsigned int rank = targetPtr->left->size + 1;
        while (targetPtr != treeRoot) {
                if (targetPtr == targetPtr->parent->right) {
                        rank += targetPtr->parent->left->size + 1;
                }
                targetPtr = targetPtr->parent;
        }

        return rank;
}

/*
 * Search a tree node.
 */
struct ostree_s *OstreeSearch(struct ostree_s *treeRoot, int num)
{
        while (treeRoot != treeNil_g && treeRoot->value != num) {
                if (treeRoot->value > num) {
                        treeRoot = treeRoot->left;
                } else {
                        treeRoot = treeRoot->right;
                }
        }
        return treeRoot;
}
