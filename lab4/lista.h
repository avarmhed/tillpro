#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct nod {
    char key[512];
    char value[512];
    struct nod * next;
    struct nod * prev;
};
typedef struct nod Nod;

void insertnod(Nod ** padr, Nod * tobeadded)
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

void removenod(Nod ** padr, Nod * toberemoved)
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
        Nod * prevnode = toberemoved->prev;
        Nod * nextnode = toberemoved->next;

        // link prev node to next node and vice versa, uncoupling toberemoved
        prevnode->next = nextnode;
        nextnode->prev = prevnode;
    }

    // we can now remove the node.
    free(toberemoved);
}

void printnod(Nod * p)
{
    printf("Key: %s - Value: %s\n", p->key, p->value);
}

void printlist(Nod * p)
{
    // TO DO: Check if we are at the beginning of the list
    // Some prints to make it pretty:
    printf("Displaying the linked list:\n");
    printf("---------------------------\n");

    for(Nod * curNode = p; curNode != NULL; curNode = curNode->next)    // loop until break;
    {
        printnod(curNode);
    }
}

Nod * search(Nod ** p, char * searchTerm)
{
    // search from beginning (assume we get the first node)
    for (Nod * curNode = *p; curNode != NULL; curNode = curNode->next)
    {
        if(strcmp(searchTerm, curNode->key) == 0 || strcmp(searchTerm, curNode->value) == 0)
        {
            return curNode;
            break;
        }
    }

    return NULL; // no result
}