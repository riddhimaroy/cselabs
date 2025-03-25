// Write a singte C program that uses recursion to find the longest word in a dynamically allocated array of strings. 
// The program should include the following 1. 
// a. Define a structure StringArray to represent an array of strings. 
// The structure should contain the following members: A pointer to a pointer of characters words to store the strings 
// (Use dynamic memory allocation). An integer value siza indicating the number of strings in the anay 
// (Assuming max length of each word is 50, create a StringArray variable in main 
// b. Implement a function void find Longest Word(StringArray" strArray, int index, char** longest Word) that takes a StringArray and its
//  current index, and recursively finds the longest word in the array. 
//  c. Write a function void displayLongestWord(char" longestWord) that displays the longest word found. 
//  d. Release the memory allocated for the array of strings.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 50

typedef struct
{
    char** arr;
    int size;
}stringarray;

void findLongestWord(stringarray* s, int i, char** longestWord)
{
    if(i>=s->size)
    {
        return;
    }

    if(i==0)
    {
        strcpy(*longestWord, s->arr[i]);
    }

    if(strlen(*longestWord)<strlen(s->arr[i]))
    {
        strcpy(*longestWord, s->arr[i]);
    }

    return findLongestWord(s, i+1, longestWord);

}

void displayLongestWord(char* longestWord) {
    printf("The longest word is: %s\n", longestWord);
}

int main()
{
    int n, i;
    char* longestWord;
    stringarray* strarr;

    longestWord =(char*)calloc(MAX, sizeof(char));
    strcpy(longestWord, "");
    strarr = (stringarray*)calloc(1, sizeof(stringarray));


    printf("Enter number of strings");
    scanf("%d", &n);
    (strarr->size)=n;

    strarr->arr = (char**)calloc(n, sizeof(char*));

    for(i=0; i<n; i++)
    {
        strarr->arr[i] = (char*)calloc(MAX, sizeof(char));
    }

    printf("Enter the strings");
    for(i=0; i<n; i++)
    {
        scanf("%s", strarr->arr[i]);
    }

    findLongestWord(strarr, 0, &longestWord);
    displayLongestWord(longestWord);

    for(i=0; i<n; i++)
    free(strarr->arr[i]);
    free(strarr->arr);
    free(strarr);
}