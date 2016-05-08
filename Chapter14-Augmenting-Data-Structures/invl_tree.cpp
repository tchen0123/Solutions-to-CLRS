/*
 * Solutions-to-CLRS/Chapter14-Augmenting-Data-Structures/invl_tree.cpp
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#include "invl_tree.h"
#include "invltree_queue.h"
#include <stdlib.h>
#include <limits.h>
#include <iostream>


static struct invlTree_s *treeNil_g; // sentinel tree nil


/*
 * Search the max endpoint.
 */
static inline int MaxEndpoint(struct invlTree_s *treePtr)
{
        int retMax = treePtr->left->maxEndpoint > treePtr->left->maxEndpoint
                ? treePtr->left->maxEndpoint
                : treePtr->right->maxEndpoint;

        return (retMax > treePtr->maxEndpoint ? retMax : treePtr->maxEndpoint);

}
/*
 * Create a new tree node.
 */
static inline struct invlTree_s *CreateNode(struct invl_s interval)
{
        struct invlTree_s *newNode = (struct invlTree_s *)malloc(sizeof(struct invlTree_s));
        newNode->interval = interval;
        newNode->color = RB_RED;
        newNode->maxEndpoint = interval.high; // left and right are tree nil
        newNode->parent = treeNil_g;
        newNode->left = newNode->right = treeNil_g;

        return newNode;
}

/*
 * Search the minimum node.
 */
static inline struct invlTree_s *Minimum(struct invlTree_s *root)
{
        while (root != treeNil_g && root->left != treeNil_g) {
                root = root->left;
        }
        return root;
}

/*
 * Inquire whether overlap or not.
 */
bool IsOverlap(struct invl_s invl1, struct invl_s invl2)
{
        return (invl1.low <= invl2.high) && (invl2.low <= invl1.high);
}

static struct invlTree_s *LeftRotate(struct invlTree_s *root, struct invlTree_s *targetPtr);
static struct invlTree_s *RightRotate(struct invlTree_s *root, struct invlTree_s *targetPtr);
static struct invlTree_s *InvltreeDeleteFixup(struct invlTree_s *root, struct invlTree_s *targetPtr);
static struct invlTree_s *InvltreeInsertFixup(struct invlTree_s *root, struct invlTree_s *targetPtr);
static struct invlTree_s *Transplant(struct invlTree_s *root, struct invlTree_s *oldPtr, struct invlTree_s *newPtr);


/*
 * Initialize invlTree nil.
 */
struct invlTree_s *InitInvltreeNil(void)
{
        treeNil_g = (struct invlTree_s *)malloc(sizeof(struct invlTree_s));
        treeNil_g->color = RB_BLACK;
        treeNil_g->maxEndpoint = INT_MIN;

        return treeNil_g;
}

/*
 * InvlTree insertion.
 */
struct invlTree_s *InvltreeInsert(struct invlTree_s *root, struct invl_s interval)
{
        struct invlTree_s *prev = treeNil_g, *curr = root;
        while (curr != treeNil_g) {
                prev = curr;
                // Update max point
                if (curr->maxEndpoint < interval.high) {
                        curr->maxEndpoint = interval.high;
                }

                if (curr->interval.low > interval.low) {
                        curr = curr->left;
                } else {
                        curr = curr->right;
                }
        }

        // link
        struct invlTree_s *newNode = CreateNode(interval);
        newNode->parent = prev;
        if (prev == treeNil_g) {
                root = newNode;
        } else if (prev->interval.low > interval.low) {
                prev->left = newNode;
        } else{
                prev->right = newNode;
        }
        std::cout << "hello world" << std::endl;

        root = InvltreeInsertFixup(root, newNode);

        return root;
}

/*
 * Invltree deletion.
 */
struct invlTree_s *InvlTreeDelete(struct invlTree_s *root, struct invl_s invterval)
{
        struct invlTree_s *targetPtr = InvltreeSearch(root, invterval);
        if (targetPtr == treeNil_g) {
                return root;
        }

        struct invlTree_s *yPtr = targetPtr, *xPtr;
        struct invlTree_s *tempPtr = yPtr->parent; // in order to update max end point
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
                tempPtr = yPtr->parent;

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
                yPtr->color = targetPtr->color;
        }
        free(targetPtr);

        // Update max end point
        while (tempPtr != treeNil_g) {
                tempPtr->maxEndpoint = MaxEndpoint(tempPtr);
                tempPtr = tempPtr->parent;
        }

        if (yColor == RB_BLACK) {
                root = InvltreeDeleteFixup(root, xPtr);
        }

        return root;
}


/*
 * Left rotation.
 */
static struct invlTree_s *LeftRotate(struct invlTree_s *root, struct invlTree_s *targetPtr)
{
        struct invlTree_s *right = targetPtr->right;
        targetPtr->right = right->left;
        if (targetPtr->right != treeNil_g) {
                targetPtr->right->parent = targetPtr;
        }

        struct invlTree_s *parent = targetPtr->parent;
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

        right->maxEndpoint = targetPtr->maxEndpoint;
        targetPtr->maxEndpoint = MaxEndpoint(targetPtr);

        return root;
}

/*
 * Right rotation.
 */
static struct invlTree_s *RightRotate(struct invlTree_s *root, struct invlTree_s *targetPtr)
{
        struct invlTree_s *left = targetPtr->left;
        targetPtr->left = left->right;
        if (targetPtr->left != treeNil_g) {
                targetPtr->left->parent = targetPtr;
        }

        struct invlTree_s *parent = targetPtr->parent;
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

        left->maxEndpoint = targetPtr->maxEndpoint;
        targetPtr->maxEndpoint = MaxEndpoint(targetPtr);

        return root;
}

/*
 * Insertion fix up.
 */
static struct invlTree_s *InvltreeInsertFixup(struct invlTree_s *root, struct invlTree_s *targetPtr)
{
        while (targetPtr->parent->color == RB_RED) {
                if (targetPtr->parent == targetPtr->parent->parent->left) {
                        struct invlTree_s *uncle = targetPtr->parent->parent->right;

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
                        struct invlTree_s *uncle = targetPtr->parent->parent->left;

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
 * Transplant.
 */
static struct invlTree_s *Transplant(struct invlTree_s *root, struct invlTree_s *oldPtr, struct invlTree_s *newPtr)
{
        struct invlTree_s *parent = oldPtr->parent;
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
 * Deletion fix up.
 */
static struct invlTree_s *InvltreeDeleteFixup(struct invlTree_s *root, struct invlTree_s *targetPtr)
{
        while (targetPtr != root && targetPtr->color == RB_BLACK) {
                if (targetPtr == targetPtr->parent->left) {
                        struct invlTree_s *sibling = targetPtr->parent->right;

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
                        struct invlTree_s *sibling = targetPtr->parent->left;

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
 * Search a tree node.
 */
struct invlTree_s *InvltreeSearch(struct invlTree_s *root, struct invl_s interval)
{
        while (root != treeNil_g && !IsOverlap(root->interval, interval)) {
                if (root->left != treeNil_g && root->left->maxEndpoint >= interval.low) {
                        root = root->left;
                } else {
                        root = root->right;
                }
        }
        return root;
}

/*
 * invltree walk by level.
 */
void InvltreeWalkBylevel(struct invlTree_s *root)
{
        /*
        if (root == nullptr || root == treeNil_g) {
                return;
        }
        */

        struct invlqueue_s *queue = InitInvlqueue();

        EnInvlqueue(queue, root);
        EnInvlqueue(queue, nullptr); // newline flag
        do {
                struct invlTree_s *treePtr = DeInvlqueue(queue);

                if (treePtr) {
                        std::cout << '[' << treePtr->interval.low << ", " << treePtr->interval.high << "] ";

                        if (treePtr->left != treeNil_g) {
                                EnInvlqueue(queue, treePtr->left);
                        }
                        if (treePtr->right != treeNil_g) {
                                EnInvlqueue(queue, treePtr->right);
                        }
                } else if (!InvlqueueIsEmpty(queue)) { // newline
                        std::cout << std::endl;
                        EnInvlqueue(queue, nullptr);
                }
        } while (!InvlqueueIsEmpty(queue));

        DeleteInvlqueue(queue);
}

/*
 * Delete the whole tree.
 */
void DeleteInvltree(struct invlTree_s *root)
{
        if (root == nullptr) {
                return;
        } else if (root != treeNil_g) {
                struct invlqueue_s *queue = InitInvlqueue();

                EnInvlqueue(queue, root);
                do {
                        root = DeInvlqueue(queue);

                        if (root->left != treeNil_g) {
                                EnInvlqueue(queue, root->left);
                        }
                        if (root->right != treeNil_g) {
                                EnInvlqueue(queue, root->right);
                        }
                        free(root);
                } while (!InvlqueueIsEmpty(queue));

                DeleteInvlqueue(queue);
        }

        free(treeNil_g);
}
