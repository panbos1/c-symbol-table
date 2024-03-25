/**
 * @Author Panagiotis Berberidis
 * @Lesson HY-255
 * @Assignment 3
 * @AM 4376
 * @File_name symtablehash.c
 */

#include "symtable.h"

#define HASH_MULTIPLIER 65599
#define BUCKETS 509

/*the binding*/
struct binding
{
    char *key;
    void *value;
    struct binding * next;
};

/*
    Hashtable with single linked list
*/
struct SymTable_S
{
    struct binding** table;
    unsigned int buckets;
    unsigned int length;
};




/*Return a hash code for pcKey.*/
static unsigned int SymTable_hash(const char *pcKey,unsigned int buckets)
{
  size_t i;
  unsigned int uiHash = 0U;

  for (i = 0U; pcKey[i] != '\0'; i++)
    {
      uiHash = uiHash * HASH_MULTIPLIER + pcKey[i];
    }

  return uiHash % buckets;
}




/*makes a new object of the hash list*/
SymTable_T SymTable_new(void)
{
    SymTable_T new =malloc(sizeof(SymTable_T*));

    assert(new);
    new->table =malloc(BUCKETS * sizeof(struct binding*));
    new->length = 0;
    new->buckets = BUCKETS;
    return new;
}


/*returns the size of the table*/
unsigned int SymTable_getLength(SymTable_T oSymTable)
{
    assert(oSymTable);
    return oSymTable->length;
}

/*puts an element in the table*/
int SymTable_put(SymTable_T oSymTable, const char *pcKey,const void *pvValue){
    char *newkey;
    struct binding *newnode;
    int pos;
    int found;
    assert(oSymTable && pcKey);

    found=SymTable_contains(oSymTable,pcKey);

    if(found==1)
      {
        return 0;
      }
    newkey = (char *)malloc(strlen(pcKey)+1);
    assert(newkey);
    strcpy(newkey,pcKey);

    newnode = (struct binding *)malloc(sizeof(struct binding));
    assert(newnode);
    newnode->key = newkey;
    newnode->value = (void *)pvValue;

    pos = SymTable_hash(pcKey,oSymTable->buckets);
    newnode->next = oSymTable->table[pos];
    oSymTable->table[pos] = newnode;
    oSymTable->length++;


    return 1;
}

/*reallocates the memory*/
void SymTable_free(SymTable_T oSymTable)
{
    struct binding *tmp;
    struct binding  *next;
    int i;

    if(oSymTable!=NULL)
      {
       return;
      }

    for(i=0;i<BUCKETS;i++)
    {
        tmp = oSymTable->table[i];

        while(tmp!=NULL)
        {
            next = tmp->next;
            free(tmp->key);
            free(tmp);
            tmp = next;
        }
    }
    free(oSymTable->table);
}

/*removes an element*/
int SymTable_remove(SymTable_T oSymTable, const char *pcKey)
{
     struct binding  *prev;
     struct binding *curr;
     int pos;
     int compare;
     assert(oSymTable);
     assert(pcKey);

     pos=SymTable_hash(pcKey, BUCKETS);
     for (curr = oSymTable->table[pos], prev= NULL;curr!= NULL;prev=curr, curr = curr->next)
     {
        compare=strcmp(pcKey, curr->key);

         if (compare== 0)
          {
             if (prev== NULL)
              {
                 oSymTable->table[pos] = curr->next;
              }
             else
              {
                 prev->next = curr->next;
              }

             free(curr->key);
             free(curr);
             oSymTable->length--;

             return 1;
         }
     }
   return 0;
}

/*checks if the hastable has an element*/
int SymTable_contains(SymTable_T oSymTable, const char *pcKey){
    struct binding *curr;
    int compare;
    assert(oSymTable && pcKey);

    curr = oSymTable->table[SymTable_hash(pcKey,BUCKETS)];
    while(curr!=NULL)
      {
        compare=strcmp(curr->key,pcKey);

          if(compare == 0)
          {
            return 1;
          }

          curr = curr->next;
      }

    return 0;
}

/*returns an element of the hash*/
void *SymTable_get(SymTable_T oSymTable, const char *pcKey){
    struct binding *curr;
    assert(oSymTable && pcKey);

    curr = oSymTable->table[SymTable_hash(pcKey,BUCKETS)];
    while(curr!=NULL)
    {
        if(strcmp(curr->key,pcKey) == 0) return curr->value;
        curr = curr->next;
    }

    return NULL;
}

/*mapping the bindings*/
void SymTable_map(SymTable_T oSymTable,
                    void (*pfApply)(const char *pcKey, void *pvValue,void *pvExtra),
                    const void *pvExtra)
{
    int i;
    struct binding* cur;
    assert(oSymTable);

    for(i=0;i<BUCKETS;i++)
    {
        cur = oSymTable->table[i];
        while(cur!=NULL)
        {
           pfApply((const char *)(cur->key),cur->value,(void*)pvExtra);
            cur = cur ->next;
        }
    }
}