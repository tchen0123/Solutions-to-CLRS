/*
 * Solutions-to-CLRS/Chapter12-Binary-Search-Trees/bintree.c
 *
 * Copyright (c) 2016  Jiawei Feng
 */

#ifndef __BINTREE_H_
#define __BINTREE_H_

struct bintree_s {
        int value;
        struct bintree_s *parent;
        struct bintree_s *left;
        struct bintree_s *right;
};

struct bintree_s *BintreeSearch(struct bintree_s *treeRoot, int num);
struct bintree_s *BintreeInsert(struct bintree_s *treeRoot, int num);
struct bintree_s *BintreeDelete(struct bintree_s *treeRoot, int num);
struct bintree_s *Successor(struct bintree_s *treeRoot);
struct bintree_s *Predecessor(struct bintree_s *treeRoot);
void TreeWalkInorder(struct bintree_s *treeRoot);
void TreeWalkPreorder(struct bintree_s *treeRoot);
void TreeWalkInlevel(struct bintree_s *treeRoot);
void DeleteBinTree(struct bintree_s *treeRoot);
void BintreeInvert(struct bintree_s *treeRoot);

#endif
