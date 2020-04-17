#ifndef tproHASHFUNC_H
#define tproHASHFUNC_H

#include <stdint.h>
#include "lista.h"    // en headerfil för en modifierad dubbellänkad lista p3

extern const int HASHVEKSIZE;

uint32_t tilpro_hash(const char * s) {

  uint32_t hash = 0;
  size_t i = 0;
  while (s[i] != '\0') {
    hash += s[i++];
    hash += hash << 10;
    hash ^= hash >> 6;
  }
  hash += hash << 3;
  hash ^= hash >> 11;
  hash += hash << 13;

  hash = hash & ( HASHVEKSIZE - 1 );
  return hash;
}

void put(Nod ** hashtable, char * key, char * value)
{
    int hash_key = tilpro_hash(key);

    Nod * result = search(&hashtable[hash_key], key);

    if (result != NULL)
    {
        if (strcmp(value, result->value) == 0)
        {
            printf("This node already exists.\n");
        }else{
            strcpy(result->value, value);
            printf("Value updated.\n");
        }
    }else{
        Nod * newnode = malloc(sizeof(Nod));
        strcpy(newnode->key, key);
        strcpy(newnode->value, value);
        insertnod(&hashtable[hash_key], newnode);

        printf("Node inserted.\n");
    }

}

char * get(Nod ** hashtable, char * key)
{
    int hash_key = tilpro_hash(key);
    Nod * result = search(&hashtable[hash_key], key);
    if  (result != NULL)
    {
        return result->value;
    }else{
        return NULL;
    }
}

void init(Nod ** vek) // assigns all hash pointers to NULL
{
    for (int i = 0; i <= HASHVEKSIZE; i++) vek[i] = NULL;
}

#endif