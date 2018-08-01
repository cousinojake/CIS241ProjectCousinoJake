#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include "sha1-master/sha1.c"

// ListNode structure definition
struct ListNode {
    char data[50]; // node data
    struct ListNode *nextPtr; // pointer to next node
}; // end struct ListNode

typedef struct ListNode ListNode;
typedef ListNode *ListNodePtr;

void insertItem( ListNodePtr *sPtr, char value[20] );

int main()
{

  struct dirent *dirent;

  char * filePath = "sample_files1/";
  DIR *dr = opendir(filePath);
  int fileCount = 0;

  ListNodePtr MainList = NULL;
  //Initalize Sha-1
  SHA1_CTX sha;
  SHA1Init(&sha);

  printf("%s%s\n", "Files in ", filePath);
  while((dirent = readdir(dr)) != NULL)
  {
    if(strncmp(dirent->d_name, ".", 1) != 0)
    {
      // printf("%s\n", dirent->d_name);
      FILE *file;
      char fileName[200], dataPoint;
      sprintf(fileName, "%s%s", "/Users/jakecousino/Desktop/CIS241ProjectCousinoJake/sample_files1/", dirent->d_name);
      printf("fileName: %s\n", fileName);
      if((file = fopen(fileName, "r")) == NULL)
      {
        printf("%s\n", "File does not exits.");
      }
      else
      {
        int charCount = 0;
        char data[10000] = "", hashResult[50];
        dataPoint = fgetc(file);
        data[charCount] = dataPoint;
        while(dataPoint != EOF)
        {
          // printf("%c", dataPoint);
          data[charCount] = dataPoint;
          charCount++;
          dataPoint = fgetc(file);
        }
        // fscanf(file, "%s", data);
        // printf("File Content: %s\n", data);
        uint8_t results[20];
        int n = strlen(data);
        SHA1Update(&sha, (uint8_t *)data, n);
        SHA1Final(results, &sha);
        sprintf(hashResult, "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
          results[0], results[1], results[2], results[3], results[4], results[5], results[6], results[7], results[8], results[9],
          results[10], results[11], results[12], results[13], results[14], results[15], results[16], results[17], results[18], results[19]);

        insertItem(&MainList, hashResult);
        fileCount++;
      }
    }
  }

  //List used to manage the hashed values.
  ListNodePtr holdingList = NULL;
  holdingList = MainList;

  // //Initalize Sha-1
  // SHA1_CTX sha;
  // SHA1Init(&sha);

  while(fileCount > 1)
  {
    fileCount = ((fileCount / 2) + (fileCount % 2));

    ListNodePtr current = NULL;
    ListNodePtr next = NULL;
    ListNodePtr newList = NULL;

    for(int i = 0; i < fileCount; i++)
    {
      current = holdingList;
      next = holdingList->nextPtr;
      // printf("%s%s\n", "Current: ", current->data);
      // printf("%s%s\n", "Next: ", next->data);
      char addedHash[100];

      /* Perform hash by getting the lenght of the string to hash then sending
      *  the paramaters to the Sha-1 implementation and use Final to get the hash
      *  value in results
      */
      uint8_t results[20];
      int n = strlen(current->data);
      SHA1Update(&sha, (uint8_t *)current->data, n);
      SHA1Final(results, &sha);

      char firstResult[50], secondResult[50], finalResult[50];
      // Uses sprintf to format the uint8_t result array into a char array.
      sprintf(firstResult, "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
        results[0], results[1], results[2], results[3], results[4], results[5], results[6], results[7], results[8], results[9],
        results[10], results[11], results[12], results[13], results[14], results[15], results[16], results[17], results[18], results[19]);

      // printf("firstResult: %s\n", firstResult);

      //if NULL then do not compute the second hash of null
      if(next != NULL)
      {
        n = strlen(next->data);
        SHA1Update(&sha, (uint8_t *)next->data, n);
        SHA1Final(results, &sha);

        // Uses sprintf to format the uint8_t result array into a char array.
        sprintf(secondResult, "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
          results[0], results[1], results[2], results[3], results[4], results[5], results[6], results[7], results[8], results[9],
          results[10], results[11], results[12], results[13], results[14], results[15], results[16], results[17], results[18], results[19]);

        // printf("secondResult: %s\n", secondResult);

      }
      // Combine the two hashes.
      sprintf(addedHash, "%s%s", firstResult, secondResult);
      n = strlen(addedHash);
      SHA1Update(&sha, (uint8_t *)addedHash, n);
      SHA1Final(results, &sha);

      sprintf(finalResult, "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
        results[0], results[1], results[2], results[3], results[4], results[5], results[6], results[7], results[8], results[9],
        results[10], results[11], results[12], results[13], results[14], results[15], results[16], results[17], results[18], results[19]);

      // printf("finalResult: %s\n", finalResult);

      // Insert the added hash to the newList.
      insertItem(&newList, finalResult);

      if(next != NULL)
      {
        if(next->nextPtr != NULL) holdingList = next->nextPtr;
      }
    }

    if(fileCount == 1)
    {
      printf("%s%s\n", "Top Hash: ", newList->data);
    }
    holdingList = newList;
  }
  closedir(dr);
  return 0;
}


// Insert a new value into the list in sorted order
void insertItem( ListNodePtr *sPtr, char value[50] )
{
    ListNodePtr newPtr; // new node
    ListNodePtr previousPtr; // previous node
    ListNodePtr currentPtr; // current node

    newPtr = malloc( sizeof( ListNode ) );
    if ( newPtr ) {
        for(int i = 0; i < strlen(value); i++)
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
