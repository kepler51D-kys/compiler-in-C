#ifndef ARRAYLIST_C
#define ARRAYLIST_C

#include <stdlib.h>
#include <string.h>

#define ARRAYLIST_INITIAL_CAPACITY 4

#define DEFINE_ARRAYLIST(TYPE, NAME)                                           \
                                                                               \
  typedef struct {                                                             \
    TYPE *list;                                                                \
    size_t max_capacity;                                                       \
    size_t len;                                                                \
  } NAME;                                                                      \
                                                                               \
  NAME *NAME##_init() {                                                        \
    NAME *list = malloc(sizeof(NAME));                                         \
    list->list = malloc(sizeof(TYPE) * ARRAYLIST_INITIAL_CAPACITY);            \
    list->max_capacity = ARRAYLIST_INITIAL_CAPACITY;                           \
    list->len = 0;                                                             \
    return list;                                                               \
  }                                                                            \
                                                                               \
  void NAME##_allocate_at_least(NAME *list, size_t len) {                      \
    if (list->max_capacity >= len)                                             \
      return;                                                                  \
    size_t new_capacity = list->max_capacity;                                  \
    while (new_capacity < len) {                                               \
      new_capacity *= 2;                                                       \
    }                                                                          \
    TYPE *new_list_ptr = malloc(sizeof(TYPE) * new_capacity);                  \
    memcpy(new_list_ptr, list->list, list->len * sizeof(TYPE));                \
    free(list->list);                                                          \
    list->max_capacity = new_capacity;                                         \
    list->list = new_list_ptr;                                                 \
  }                                                                            \
                                                                               \
  void NAME##_append(NAME *list, TYPE value) {                                 \
    NAME##_allocate_at_least(list, list->len + 1);                             \
    list->list[list->len] = value;                                             \
    list->len++;                                                               \
  }                                                                            \
                                                                               \
  void NAME##_remove(NAME *list, size_t index) {                               \
    if (list->len < index)                                                     \
      return;                                                                  \
    memcpy((((char *)list) + (index * sizeof(TYPE))),                          \
           (((char *)list) + ((index + 1) * sizeof(TYPE))),                    \
           list->len - (index + 1));                                           \
    list->len--;                                                               \
  }                                                                            \
                                                                               \
  void NAME##_remove_last_elem(NAME *list) {                                   \
    if (list->len == 0)                                                        \
      return;                                                                  \
    list->len--;                                                               \
  }                                                                            \
                                                                               \
  void NAME##_shrink_to_fit(NAME *list) {                                      \
    size_t new_capacity = list->max_capacity;                                  \
    while (new_capacity >= list->len && new_capacity >= 4) {                   \
      new_capacity /= 2;                                                       \
    }                                                                          \
    if (new_capacity == list->max_capacity)                                    \
      return;                                                                  \
    TYPE *new_list = malloc(sizeof(TYPE) * new_capacity);                      \
    memcpy(new_list, list->list, list->len);                                   \
    free(list->list);                                                          \
    list->list = new_list;                                                     \
  }                                                                            \
                                                                               \
  void NAME##_free(NAME *list) {                                               \
    free(list->list);                                                          \
    list->list = NULL;                                                         \
    free(list);                                                                \
  }

#endif // ARRAYLIST_C
