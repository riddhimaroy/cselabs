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
#include <stdlib.h>
#include <string.h>
#define MAX 30

typedef struct 
{
    char** arr;
    int size;
}stringArray;

void findLongestWord(stringArray* s, int i, char** longestWord)
{
    if(i>=s->size)
        return;

    if(i==0 || strlen(*longestWord)<strlen(s->arr[i]))
    {
        strcpy(*longestWord, s->arr[i]);
    }

    findLongestWord(s, i+1, longestWord);
}

void display(char* longestWord)
{
    puts(longestWord);
}

int main()
{
    stringArray *s = (stringArray*)calloc(1, sizeof(stringArray));
    int n, i;

    printf("Enter the number of strings\n");
    scanf("%d", &n);
    s->size = n;

    s->arr = (char**)calloc(n, sizeof(char*));
    for(i=0; i<n; i++)
    {
        s->arr[i] = (char*)calloc(MAX, sizeof(char));
    }

    printf("Enter the strings: \n");

    for(i=0; i<n; i++)
    {
        scanf("%s", s->arr[i]);
    }

    char* longestWord = (char*)calloc(MAX, sizeof(char));
    //strcpy(longestWord, "");

    findLongestWord(s, 0, &longestWord);
    display(longestWord);

}
