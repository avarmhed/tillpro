#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct artist {
  char artistid[20];
  char artistname[400];
  char songtitle[300];
  double length;
  int year;
  struct artist * next;
  struct artist * prev;
}; typedef struct artist Artist;

void insertnod(Artist ** padr, Artist * tobeadded)
{
    if(*padr == NULL)
    {   // list is empty!
        tobeadded->next = NULL;
        tobeadded->prev = NULL;
    }else{  // add new node to existing list
        (*padr)->prev = tobeadded;
        tobeadded->next = *padr;
    }

    (*padr) = tobeadded;
}

void removenod(Artist ** padr, Artist * toberemoved)
{
    // 3 cases: 1. removing first member of list, 2. removing last member, 3. any in between

    if(toberemoved->prev == NULL)
    {
        // removing first member of list. relink apdr to next, then remove
        (*padr) = toberemoved->next;
    }else if(toberemoved->next == NULL)
    {
        // removing last member of list. NULL next-pointer of prev member
        (toberemoved->prev)->next = NULL;
    }else
    {
        //find next and prev node:
        Artist * prevnode = toberemoved->prev;
        Artist * nextnode = toberemoved->next;

        // link prev node to next node and vice versa, uncoupling toberemoved
        prevnode->next = nextnode;
        nextnode->prev = prevnode;
    }

    // we can now remove the node.
    free(toberemoved);
}

void printnod(Artist * p)
{
    printf("%s: %s - %s (%d)\n", p->artistid, p->artistname, p->songtitle, p->year);
}

Artist * search(Artist ** p, char * searchTerm)
{
    //printf("Searching for: %s\n", searchTerm);
    for (Artist * curNode = *p; curNode != NULL; curNode = curNode->next)
    {
        if(strcmp(searchTerm, curNode->artistid) == 0)
        {
            return curNode;
            break;
        }
    }

    return NULL; // no result
}

void destroyList(Artist ** padr)
{
    Artist * curNode = *padr;
    while(curNode->next != NULL)
    {
        curNode = curNode->next;
    }   // the end

    while(curNode->prev != NULL)
    {
        curNode = curNode->prev;
        free(curNode->next);
    }
}