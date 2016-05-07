/*
 * Solutions-to-CLRS/Chapter14-Augmenting-Data-Structures/ostree.cpp
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#include "ostree.h"
#include "queue.h"
#include <stdlib.h>
#include <iostream>


static struct ostree_s *treeNil_g; // sentinel tree nil


/*
 * Calculate the rank.
 */
static inline unsigned int Rank(struct ostree_s *ostree)
{
        if (ostree != treeNil_g) {
                return ostree->left->size + 1;
        } else {
                return 0;
        }
}


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

/*
 * Search the minimum node.
 */
static inline struct ostree_s *Minimum(struct ostree_s *root)
{
        while (root != treeNil_g && root->left != treeNil_g) {
                root = root->left;
        }

        return root;
}


static struct ostree_s *LeftRotate(struct ostree_s *root, struct ostree_s *targetPtr);
static struct ostree_s *RightRotate(struct ostree_s *root, struct ostree_s *targetPtr);
static struct ostree_s *OstreeInsertFixup(struct ostree_s *root, struct ostree_s *targetPtr);
static struct ostree_s *OstreeDeleteFixup(struct ostree_s *root, struct ostree_s *targetPtr);
static struct ostree_s *Transplant(struct ostree_s *root, struct ostree_s *oldPtr, struct ostree_s *newPtr);


/*
 * Initialize ostree nil.
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
struct ostree_s *OstreeInsert(struct ostree_s *root, int num)
{
        struct ostree_s *prev = treeNil_g, *curr = root;
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
                root = newNode;
        } else if (prev->value > num) {
                prev->left = newNode;
        } else {
                prev->right = newNode;
        }

        root = OstreeInsertFixup(root, newNode);

        return root;
}

/*
 * Ostree deletion.
 */
struct ostree_s *OstreeDelete(struct ostree_s *root, int num)
{
        struct ostree_s *targetPtr = OstreeSearch(root, num);
        if (targetPtr == treeNil_g) {
                return root;
        }

        // reduce size
        struct ostree_s *tempPtr = targetPtr;
        while (tempPtr != treeNil_g) {
                tempPtr->size--;
                tempPtr = tempPtr->parent;
        }

        struct ostree_s *yPtr = targetPtr, *xPtr;
        bool yColor = yPtr->color;

        if (targetPtr->left == treeNil_g) {
                xPtr = targetPtr->right;
                root = Transplant(root, targetPtr, targetPtr->right);
        } else if (targetPtr->right == treeNil_g) {
                xPtr = targetPtr->left;
                root = Transplant(root, targetPtr, targetPtr->left);
        } else {
                yPtr = Minimum(targetPtr->right);
                yColor = yPtr->color;
                xPtr = yPtr->right;

                if (yPtr == targetPtr->right) {
                        xPtr->parent = yPtr;
                } else {
                        root = Transplant(root, yPtr, yPtr->right);
                        yPtr->right = targetPtr->right;
                        yPtr->right->parent = yPtr;
                }
                root = Transplant(root, targetPtr, yPtr);
                yPtr->left = targetPtr->left;
                yPtr->left->parent = yPtr;
                yPtr->color = targetPtr;
        }

        if (yColor == RB_BLACK) {
                root = OstreeDeleteFixup(root, xPtr);
        }

        return root;
}

/*
 * Search a node.
 */
struct ostree_s *OstreeSearch(struct ostree_s *root, int num)
{
        while (root != treeNil_g && root->value != num) {
                if (root->value > num) {
                        root = root->left;
                } else {
                        root = root->right;
                }
        }
        return root;
}

/*
 * Ostree left rotation.
 */
static struct ostree_s *LeftRotate(struct ostree_s *root, struct ostree_s *targetPtr)
{
        struct ostree_s *right = targetPtr->right;
        targetPtr->right = right->left;
        if (targetPtr->right != treeNil_g) {
                targetPtr->right->parent = targetPtr;
        }

        struct ostree_s *parent = targetPtr->parent;
        right->parent = parent;
        if (parent == treeNil_g) {
                root = right;
        } else if (parent->left == targetPtr) {
                parent->left = right;
        } else {
                parent->right = right;
        }

        right->left = targetPtr;
        targetPtr->parent = right;

        right->size = targetPtr->size;
        targetPtr->size = targetPtr->left->size + targetPtr->right->size + 1;

        return root;
}

/*
 * Ostree right rotation.
 */
static struct ostree_s *RightRotate(struct ostree_s *root, struct ostree_s *targetPtr)
{
        struct ostree_s *left = targetPtr->left;
        targetPtr->left = left->right;
        if (targetPtr->left != treeNil_g) {
                targetPtr->left->parent = targetPtr;
        }

        struct ostree_s *parent = targetPtr->parent;
        left->parent = parent;
        if (parent == treeNil_g) {
                root = left;
        } else if (parent->left == targetPtr) {
                parent->left = left;
        } else {
                parent->right = left;
        }

        left->right = targetPtr;
        targetPtr->parent = left;

        left->size = targetPtr->size;
        targetPtr->size = targetPtr->left->size + targetPtr->right->size + 1;

        return root;
}

/*
 * Ostree insertion fix up.
 */
static struct ostree_s *OstreeInsertFixup(struct ostree_s *root, struct ostree_s *targetPtr)
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

                                        root = LeftRotate(root, targetPtr);
                                }
                                targetPtr->parent->parent->color = RB_RED;
                                targetPtr->parent->color = RB_BLACK;

                                root = RightRotate(root, targetPtr->parent->parent);
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

                                        root = RightRotate(root, targetPtr);
                                }
                                targetPtr->parent->parent->color = RB_RED;
                                targetPtr->parent->color = RB_BLACK;

                                root = LeftRotate(root, targetPtr->parent->parent);
                        }
                }
        }
        root->color = RB_BLACK;

        return root;
}

/*
 * Ostree transplant.
 */
static struct ostree_s *Transplant(struct ostree_s *root, struct ostree_s *oldPtr, struct ostree_s *newPtr)
{
        struct ostree_s *parent = oldPtr->parent;
        newPtr->parent = parent;
        if (parent == treeNil_g) {
                root = newPtr;
        } else if (parent->left == oldPtr) {
                parent->left = newPtr;
        } else {
                parent->right = newPtr;
        }

        return root;
}

/*
 * Ostree deletion fix up.
 */
static struct ostree_s *OstreeDeleteFixup(struct ostree_s *root, struct ostree_s *targetPtr)
{
        while (targetPtr != root && targetPtr->color == RB_BLACK) {
                if (targetPtr == targetPtr->parent->left) {
                        struct ostree_s *sibling = targetPtr->parent->right;

                        if (sibling->color == RB_RED) {
                                sibling->color = RB_BLACK;
                                targetPtr->parent->color = RB_RED;

                                root = LeftRotate(root, targetPtr->parent);
                                sibling = targetPtr->parent->right;
                        }
                        if (sibling->left->color == RB_BLACK && sibling->right->color == RB_BLACK) {
                                sibling->color = RB_RED;
                                targetPtr = targetPtr->parent;
                        } else {
                                if (sibling->right->color == RB_BLACK) {
                                        sibling->color = RB_RED;
                                        sibling->left->color = RB_BLACK;

                                        root = RightRotate(root, sibling);
                                        sibling = targetPtr->parent->right;
                                }
                                sibling->color = targetPtr->parent->color;
                                targetPtr->parent->color = RB_BLACK;
                                sibling->right->color = RB_BLACK;

                                root = LeftRotate(root, targetPtr->parent);
                                targetPtr = root;
                        }
                } else {
                        struct ostree_s *sibling = targetPtr->parent->left;

                        if (sibling->color == RB_RED) {
                                sibling->color = RB_BLACK;
                                targetPtr->parent->color = RB_RED;

                                root = RightRotate(root, targetPtr->parent);
                                sibling = targetPtr->parent->left;
                        }
                        if (sibling->left->color == RB_BLACK && sibling->right->color == RB_BLACK) {
                                sibling->color = RB_RED;
                                targetPtr = targetPtr->parent;
                        } else {
                                if (sibling->left->color == RB_BLACK) {
                                        sibling->right->color = RB_BLACK;
                                        sibling->color = RB_RED;

                                        root = LeftRotate(root, sibling);
                                        sibling = targetPtr->parent->left;
                                }
                                sibling->color = targetPtr->parent->color;
                                targetPtr->parent->color = RB_BLACK;
                                sibling->left->color = RB_BLACK;

                                root = RightRotate(root, targetPtr->parent);
                                targetPtr = root;
                        }
                }
        }
        targetPtr->color = RB_BLACK;

        return root;
}

/*
 * Ostree walk by level.
 */
void OstreeWalkBylevel(struct ostree_s *root)
{
        struct queue_s *queue = InitQueue();

        // Breadth first search
        EnQueue(queue, root);
        EnQueue(queue, nullptr); // newline flag
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
                } else if (!QueueIsEmpty(queue)) { // newline
                        std::cout << '\n';
                        EnQueue(queue, nullptr);
                }
        } while (!QueueIsEmpty(queue));

        DeleteQueue(queue);
}

/*
 * Delete the whole ostree.
 */
void DeleteOstree(struct ostree_s *root)
{
        struct queue_s *queue = InitQueue();

        EnQueue(queue, root);
        do {
                struct ostree_s *treePtr = DeQueue(queue);

                if (treePtr->left != treeNil_g) {
                        EnQueue(queue, treePtr->left);
                }
                if (treePtr->right != treeNil_g) {
                        EnQueue(queue, treePtr->right);
                }

                free(treePtr);
        } while (!QueueIsEmpty(queue));
        DeleteQueue(queue);

        free(treeNil_g);

}

/*
 * Select the tree node ranked rank.
 */
struct ostree_s *OstreeSelect(struct ostree_s *root, unsigned int rank)
{
        unsigned int tempRank = Rank(root);

        while (root != treeNil_g && tempRank != rank) {
                if (tempRank > rank) {
                        root = root->left;
                } else {
                        root = root->right;
                        rank -= tempRank;
                }
                tempRank = Rank(root);
        }

        return root;
}

/*
 * Calculate the rank.
 */
unsigned int OstreeRank(struct ostree_s *root, struct ostree_s *targetPtr)
{
        unsigned int rank = Rank(targetPtr);

        while (targetPtr != root) {
                if (targetPtr == targetPtr->parent->right) {
                        rank += targetPtr->parent->left->size + 1;
                }
                targetPtr = targetPtr->parent;
        }

        return rank;
}
