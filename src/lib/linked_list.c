#ifndef LINKED_LIST_C
#define LINKED_LIST_C

#include <stdlib.h>

typedef long int node_value;

typedef struct LinkedListNode {
  struct LinkedListNode *next;
  node_value value;
} LLNode;

/*
    @brief Create a new node
*/
LLNode *linked_list_new(node_value first_value) {
  LLNode *head = malloc(sizeof(LLNode));
  head->next = NULL;
  head->value = first_value;
  return head;
}

/*
    @brief Append the value to the end of the linked list (creates a new node)
*/
LLNode *linked_list_append(LLNode *node, node_value value) {
  if (node->next != NULL) {
    return linked_list_append(node->next, value);
  }
  LLNode *new_node = malloc(sizeof(LLNode));
  new_node->next = NULL;
  new_node->value = value;
  return new_node;
}

/*
   @brief Free all nodes after this node, and the node itself.
*/
void linked_list_free(LLNode *node) {
  if (node->next != NULL) {
    linked_list_free(node->next);
  }
  free(node);
}

/*
    @brief Removes the last element of this list, and returns its value
*/
node_value linked_list_splice_end(LLNode *node) {
  if (node->next != NULL) {
    return linked_list_splice_end(node->next);
  }
  node_value value = node->value;
  free(node);
  return value;
}

node_value linked_list_get_index(LLNode *node, size_t index) {
  if (index == 0) {
    return node->value;
  }
  if (node->next == NULL) {
    return 0;
  }
  return linked_list_get_index(node->next, index - 1);
}

#endif // LINKED_LIST_C