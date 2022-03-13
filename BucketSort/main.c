/*
 * program that uses the bucket sort to alphabetically sort lowercase letters
 */

/* 
 * File:   main.c
 * Author: Luis Oliveros 
 *
 * Created on July 21, 2020, 8:32 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef NODE_H
#define NODE_H
//new type node created for linked list in each bucket 
struct node
{ 
    char* string;//words stored in each specific bucket linked list 
    struct node* next;//access to next node in list
    
};

#endif /* NODE_H */
#ifndef BUCKET_H
#define BUCKET_H
//new type bucket created for sort of strings 
struct bucket
{
    int minInitial;//minimum first letter of word allowed in specific bucket
    int maxInitial;//maximum first letter of word allowed in specific bucket
    int numWords;//count of words in specific bucket
    struct node* chainHead;//head/start of linked list for a certain bucket
    
}; 
#endif /* BUCKET_H */
#define NUMBUCKS 8
int main()
{

    char inputWord[100];//user inputted string
    struct bucket list[NUMBUCKS] = {//initial setup of struct bucket array
       'a', 'b', 0, NULL,
       'c', 'c', 0, NULL,
       'd', 'f', 0, NULL,
       'g', 'k', 0, NULL,
       'l', 'o', 0, NULL,
       'p', 'r', 0, NULL,
       's', 's', 0, NULL,
       't', 'z', 0, NULL 
     };
    
    printf("Enter a word or type [0] to stop: ");//asking for user input
    while(strcmp(inputWord, "0") != 0)//end condition to stop bucket sort
    {    
        scanf("%s", inputWord);//receiving string from user
        if (strcmp(inputWord, "0") == 0)
        {
           break;//end of run
        }
        for (int i = 0; i < NUMBUCKS; i++)
        {
            //if the inputted words first character matches a buckets parameters  
            if (inputWord[0] >= list[i].minInitial && inputWord[0] 
                <= list[i].maxInitial)
            {
                //allocating memory for struct node pointer of size struct node
                struct node* current = malloc(sizeof(struct node));
                /*allocating memory for struct node pointer member, string, 
                of size char*/
                current->string = malloc(sizeof(char));
                current->next = NULL; //struct nodes next pointer set to NULL 
                //copying needed memory to char array of inputWords
                strcpy(current->string, inputWord); 
                
                //if a head node doesn't exist for current bucket
                if (list[i].chainHead == NULL) 
                {
                   list[i].chainHead = current;
                   //creates linked list in bucket from current
                }
                else 
                { 
                    //set new struct pointer to first word in list 
                    //of respective bucket
                    struct node* new = list[i].chainHead;
                    //if inputed word comes before alphabetically from first   
                    //word in list or is the same word
                    if (strcmp(inputWord, new->string) <= 0)
                    {
                         //first word in list moved to next node 
                        current->next = new;
                        list[i].chainHead = current;
                        //first word in the list is now the current user 
                        //inputted word
                    }
                    else
                    {  
                     //while next node after head node points to another  
                     //node and inputted word alphabetically comes after next 
                     //word in list     
                       while (new->next != NULL && strcmp(inputWord,
                              new->next->string) > 0)
                       {
                             new = new->next;//shift next node in list 
                       }
                        //switch/swap order of inputed word and next node
                        current->next = new->next ;
                        //next node in list is the first word that did not   
                        //not come alphabetically after.
                        new->next = current;//inputed word takes its spot.
                       
                    }    
                }
            }
        }
    }
    for (int i = 0; i < NUMBUCKS; i++)//for each struct bucket in the list
    {
        printf("[%c,%c] : ",list[i].minInitial, list[i].maxInitial);
        struct node *p = list[i].chainHead;
        //struct pointer set to beginning of each linked list for each bucket  
        while(p != NULL)//while there is a next node with an inputedWord
        {
           printf("%s\n", p->string);//print current string 
           p = p->next;//points to next in list
        }
        printf("\n");
    }
   
    return 0;
}  