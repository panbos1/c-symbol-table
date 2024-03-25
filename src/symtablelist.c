/**
 * @Author Panagiotis Berberids
 * @Lesson HY-255
 * @Assignment 3
 * @AM 4376 
 * @File_name symtablelist.c
 */

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "symtable.h"

struct Binding {
  char *key;
  void *value;
  struct Binding *next;
};

struct SymTable_S {
  unsigned int size;
  struct Binding *bindingsRoot;
};

struct Binding* new_binding(const char *pcKey, const void *pvValue) {
  struct Binding *new = (struct Binding*)malloc(sizeof(struct Binding));
  assert(pcKey != NULL);
  assert(new != NULL);
  new->key = strdup(pcKey);
  assert(new->key != NULL);
  new->value = (void*)pvValue;
  return new;
}

SymTable_T SymTable_new(void) {
  SymTable_T new = (SymTable_T)malloc(sizeof(struct SymTable_S));
  assert(new != NULL);
  new->size = 0;
  new->bindingsRoot = NULL;
  return new;
}

void SymTable_free(SymTable_T oSymTable) {
  struct Binding *temp, *next;
  if (oSymTable == NULL)
    return;
  temp = oSymTable->bindingsRoot;
  while (temp != NULL) {
    next = temp->next;
    free(temp->key);
    free(temp);
    temp = next;
  }
  free(oSymTable);
  return;
}

unsigned int SymTable_getLength(SymTable_T oSymTable) {
  assert(oSymTable != NULL);
  return oSymTable->size;
}

int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue) {
  struct Binding *new = new_binding(pcKey, pvValue);
  assert(pcKey != NULL);
  assert(oSymTable != NULL);
  if (SymTable_contains(oSymTable, pcKey))
    return 0;
  new->next = oSymTable->bindingsRoot;
  oSymTable->bindingsRoot = new;
  oSymTable->size++;
  return 1;
}

int SymTable_remove(SymTable_T oSymTable, const char *pcKey) {
  struct Binding *temp, *prev;
  assert(oSymTable != NULL);
  assert(pcKey != NULL);

  temp = oSymTable->bindingsRoot;
  prev = temp;
  while (temp != NULL) {
    if (!strcmp(temp->key, pcKey)) {
      if (temp == oSymTable->bindingsRoot)
        oSymTable->bindingsRoot = temp->next;
      else
        prev->next = temp->next;
      free(temp->key);
      free(temp);
      oSymTable->size--;
      return 1;
    }
    prev = temp;
    temp = temp->next;
  }
  return 0;
}

int SymTable_contains(SymTable_T oSymTable, const char *pcKey) {
  struct Binding *temp;
  assert(oSymTable != NULL);
  assert(pcKey != NULL);
  temp = oSymTable->bindingsRoot;
  while (temp != NULL) {
    if (!strcmp(temp->key, pcKey))
      return 1;
    temp = temp->next;
  }
  return 0;
}

void* SymTable_get(SymTable_T oSymTable, const char *pcKey) {
  struct Binding *temp;
  assert(oSymTable != NULL);
  assert(pcKey != NULL);
  temp = oSymTable->bindingsRoot;
  while (temp != NULL) {
    if (!strcmp(temp->key, pcKey))
      return temp->value;
    temp = temp->next;
  }
  return NULL;
}

void SymTable_map(SymTable_T oSymTable, void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra), const void *pvExtra) {
  void *extra;
  struct Binding *temp;
  assert(oSymTable != NULL);
  assert(pfApply != NULL);
  extra = (void*)pvExtra;
  temp = oSymTable->bindingsRoot;
  while (temp != NULL) {
    pfApply(temp->key, temp->value, extra);
    temp = temp->next;
  }
  return;
}
