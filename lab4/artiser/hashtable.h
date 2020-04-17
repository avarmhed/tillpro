#ifndef tproHASHFUNC_H
#define tproHASHFUNC_H
#include <stdint.h>

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

void put(Artist ** hashtable, Artist * theNewNode)
{
    int hash_key = tilpro_hash(theNewNode->artistid);

    Artist * result = search(&hashtable[hash_key], theNewNode->artistid);

    if (result != NULL)
    {
        //printf("The song with this name is already stored.\n");
        //strcpy(result->artistname, value);
        //printf("Value updated.\n");
    }else{
        insertnod(&hashtable[hash_key], theNewNode);
        printf("Node inserted. Id: %s\n", theNewNode->artistid);
    }

}

Artist * get(Artist ** hashtable, char * artistid)
{
    int hash_key = tilpro_hash(artistid);
    printf("%d\n", hash_key);
    Artist * result = search(&hashtable[hash_key], artistid);
    if  (result != NULL)
    {
        return result;
    }else{
        return NULL;
    }
}

void init(Artist ** vek) // assigns all hash pointers to NULL
{
    for (int i = 0; i <= HASHVEKSIZE; i++) vek[i] = NULL;
}

#endif