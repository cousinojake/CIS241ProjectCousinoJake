#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include "sha1-master/sha1.c"

// int GetArraySize(int array[]);
// ListNode structure definition
struct ListNode {
    char data[20]; // node data
    struct ListNode *nextPtr; // pointer to next node
}; // end struct ListNode

typedef struct ListNode ListNode;
typedef ListNode *ListNodePtr;

void insertItem( ListNodePtr *sPtr, char value[20] );

int main()
{

  // SHA1_CTX sha;
  // uint8_t results[20];
  // // char *result1;
  // char *buf;
  // int n;
  // buf = "abc";
  // n = strlen(buf);
  // SHA1Init(&sha);
  // SHA1Update(&sha, (uint8_t *)buf, n);
  // SHA1Final(results, &sha);
  // // SHA1Final(result1, &sha);
  //
  // /* Print the digest as one long hex value */
  // printf("0x");
  // for (n = 0; n < 20; n++)
  // {
  //   printf("%02x", results[n]);
  // }
  // printf("\n%s\n", "0xa9993e364706816aba3e25717850c26c9cd0d89d");


/**
  start a second linked list to hold all of the hashes. then when finished, start from tail and work to the head.
/**/

  struct dirent *dirent;

  DIR *dr = opendir(".");
  int fileCount = 0;

  ListNodePtr MainList = NULL;

  while((dirent = readdir(dr)) != NULL)
  {
    if(strncmp(dirent->d_name, ".", 1) != 0)
    {
      printf("%s\n", dirent->d_name);
      insertItem(&MainList, dirent->d_name);
      fileCount++;
    }
  }

  while(fileCount > 1)
  {
    fileCount = ((fileCount / 2) + (fileCount % 2));
    ListNodePtr newList = NULL;
    for(int i = 0; i < fileCount; i++)
    {

    }

    if(fileCount == 1)
    {
      printf("Top Hash: Hello!\n");
    }

  }
  // int myarray[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  // while(1)
  // {
  //   int size = (sizeof(myarray) / sizeof(myarray[0]));
  //   printf("%s%d\n", "Array size is: ", size);
  //   break;
  // }

  closedir(dr);
  return 0;
}

// Insert a new value into the list in sorted order
void insertItem( ListNodePtr *sPtr, char value[20] )
{
    ListNodePtr newPtr; // new node
    ListNodePtr previousPtr; // previous node
    ListNodePtr currentPtr; // current node

    newPtr = malloc( sizeof( ListNode ) );
    if ( newPtr ) {
        for(int i = 0; i < 20; i++)
        {
          newPtr->data[i] = value[i];
        }
        newPtr->nextPtr = NULL;

        previousPtr = NULL;
        currentPtr = *sPtr; // set currentPtr to start of list

        while ( currentPtr != NULL && value > currentPtr->data ) {
            previousPtr = currentPtr;
            currentPtr = currentPtr->nextPtr;
        } // end while

        if ( previousPtr == NULL ) {
            newPtr->nextPtr = *sPtr;
            *sPtr = newPtr;
        } // end if
        else { // insert node between previousPtr and currentPtr
            previousPtr->nextPtr = newPtr;
            newPtr->nextPtr = currentPtr;
        } // end else
    } // end if
    else {
        printf( "%s not inserted. No memory available.\n", value );
    } // end else
} // end function insertItem




// int GetArraySize(int array[])
// {
//   return (int)(sizeof(array) / sizeof(int));
// }
