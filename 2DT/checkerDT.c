/*--------------------------------------------------------------------*/
/* checkerDT.c                                                        */
/* Author:                                                            */
/*--------------------------------------------------------------------*/

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "checkerDT.h"
#include "dynarray.h"
#include "path.h"



/* see checkerDT.h for specification */
boolean CheckerDT_Node_isValid(Node_T oNNode) {
  Node_T oNParent;
  Path_T oPNPath;
  Path_T oPPPath;

  Path_T nodePathPrefix = Node_getPath(oNNode);

  /* Sample check: a NULL pointer is not a valid node */
  if(oNNode == NULL) {
    fprintf(stderr, "A node is a NULL pointer\n");
    return FALSE;
  }

  /*
  TODO:
    - If parent is null, path should be itself
    - Check if node's prefix aligns with parent's path
  */
  /* Sample check: parent's path must be the longest possible
    proper prefix of the node's path */
  oNParent = Node_getParent(oNNode);
  oPNPath = Node_getPath(oNNode);
  if(oNParent != NULL) {
    oPPPath = Node_getPath(oNParent);

    if (Path_getSharedPrefixDepth(oPNPath, oPPPath) !=
      Path_getDepth(oPNPath) - 1) {
      fprintf(stderr, "P-C nodes don't have P-C paths: (%s) (%s)\n",
              Path_getPathname(oPPPath), Path_getPathname(oPNPath));
      return FALSE;
    }

    /* if parent != null, then this path's prefix should be exactly
    parent's path*/
    Path_prefix(oPNPath, Path_getDepth(oPNPath) - 1, &nodePathPrefix);
    if (nodePathPrefix != NULL &&
        Path_comparePath(oPPPath, nodePathPrefix) != 0) {
      fprintf(stderr, "Node's path prefix doesn't match parent's path\n"
        );
      return FALSE;
    }
  }

  /* if parent is null, then this path should be itself */
  if (oNParent == NULL) {
    oPNPath = Node_getPath(oNNode);
    if (Path_getDepth(oPNPath) != 1) {
      fprintf(stderr, "Root node does not point to itself: (%s) (%s)\n",
              Node_toString(oNNode), Path_getPathname(oPNPath));
      return FALSE;
    }
  }

   return TRUE;
}

/*
   Performs a pre-order traversal of the tree rooted at oNNode.
   Returns FALSE if a broken invariant is found and
   returns TRUE otherwise.

   treeCount refers to the current number of nodes within the tree.
   Each node increments treeCount.

   You may want to change this function's return type or
   parameter list to facilitate constructing your checks.
   If you do, you should update this function comment.
*/
static boolean CheckerDT_treeCheck(Node_T oNNode, size_t* treeCount) {
  size_t ulIndex;
  size_t puIndex = 0;
  DynArray_T children;
  Node_T prevChild;

  if(oNNode!= NULL) {


    /* Sample check on each node: node must be valid */
    /* If not, pass that failure back up immediately */
    if(!CheckerDT_Node_isValid(oNNode))
      return FALSE;

    children = DynArray_new(0);

    *treeCount = *treeCount + 1;

    /* Recur on every child of oNNode */
    for(ulIndex = 0; ulIndex < Node_getNumChildren(oNNode); ulIndex++)
    {
        Node_T oNChild = NULL;
        int iStatus = Node_getChild(oNNode, ulIndex, &oNChild);

        if(iStatus != SUCCESS) {
            fprintf(stderr, "getNumChildren claims more children than getChild returns\n");
            return FALSE;
        }

        /* checks for duplicates */
        if (DynArray_getLength(children) != 0 &&
                DynArray_search(children, oNChild, &puIndex,
                (int(*)(const void*, const void*))Node_compare)) {
            fprintf(stderr, "Duplicate child\n");
            DynArray_free(children);
            return FALSE;
        } else {
            DynArray_add(children, oNChild);
        }

        /* check this path with previous path lexicographically*/
        if (ulIndex > 1) {
            prevChild = DynArray_get(children, ulIndex - 1);
            if (Path_comparePath(Node_getPath(prevChild),
                    Node_getPath(oNChild)) > 0) {
                fprintf(stderr, "Children are not stored in order\n");
                DynArray_free(children);
                return FALSE;
            }
        }

        /* if recurring down one subtree results in a failed check
            farther down, passes the failure back up immediately */
        if(!CheckerDT_treeCheck(oNChild, treeCount))
            return FALSE;
    }
    DynArray_free(children);

  }
  return TRUE;
}

/* see checkerDT.h for specification */
boolean CheckerDT_isValid(boolean bIsInitialized, Node_T oNRoot,
                          size_t ulCount) {

    size_t trueCount = 0;
    boolean isValid;

    /* Sample check on a top-level data structure invariant:
    if the DT is not initialized, its count should be 0. */
    if(!bIsInitialized)
        if(ulCount != 0) {
        fprintf(stderr, "Not initialized, but count is not 0\n");
        return FALSE;
        }

    /* Now checks invariants recursively at each node from the root. */
    isValid = CheckerDT_treeCheck(oNRoot, &trueCount);
    if (trueCount != ulCount) {
        fprintf(stderr, "Given ulCount does not match actual number of nodes\n");
        return FALSE;
    }

   return isValid;
}
