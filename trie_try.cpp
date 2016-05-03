// C++ implementation of Query Auto suggester using Trie
#include<bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <algorithm>
#include<iostream>
using namespace std;
#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])

// Alphabet size (# of symbols)
#define ALPHABET_SIZE (26)

// Converts key current character into index
// use only 'a' through 'z' and lower case
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')


char INDEX_TO_CHAR(int i)
{
    char value;
    if(i==0)value='a';
    if(i==1)value='b';
    if(i==2)value='c';
    if(i==3)value='d';
    if(i==4)
    value='e';if(i==5)
    value='f';if(i==6)
    value='g';if(i==7)
    value='h';if(i==8)
    value='i';if(i==9)
    value='j';if(i==10)
    value='k';if(i==11)
    value='l';if(i==12)
    value='m';if(i==13)
    value='n';if(i==14)
    value='o';if(i==15)
    value='p';if(i==16)
    value='q';if(i==17)
    value='r';if(i==18)
    value='s';if(i==19)
    value='t';if(i==20)
    value='u';if(i==21)
    value='v';if(i==22)
    value='w';if(i==23)
    value='x';if(i==24)
    value='y';if(i==25)
    value='z';
    return value;
}
// trie node
struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
    // isLeaf is true if the node represents
    // end of a word
    int s;
    int frequency;
    int temp_frequency;
    bool isLeaf;
};

// Returns new trie node (initialized to NULLs)
struct TrieNode *getNode(void)
{
    struct TrieNode *pNode = NULL;
    pNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    if (pNode)
    {
        int i;
        pNode->isLeaf = false;
        pNode->frequency=0;
        pNode->temp_frequency=0;
        for (i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;
    }
    return pNode;
}

bool onlyonechild(struct TrieNode *root)
{
    struct TrieNode *pCrawl = root;
    while(pCrawl)
    {
        int flag=0,pos=0;
        for (int level = 0; level < 26; level++)
        {
            if(pCrawl->children[level])
            {
                flag++;
                pos=level;
            }
        }
        if(flag==1)
        {
            pCrawl=pCrawl->children[pos];
        }
        else if(flag==0)
        {
            return 1;
        }
        else
        return 0;
    }
    return 1;
}
// If not present, inserts key into trie
// If the key is prefix of trie node, just marks leaf node
void insert(struct TrieNode *root, const char *key)
{
    int level;
    int length = strlen(key);
    int index;

    struct TrieNode *pCrawl = root;

    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);
        if (!pCrawl->children[index])
        pCrawl->children[index] = getNode();
        (pCrawl->frequency)++;
        pCrawl->temp_frequency=pCrawl->frequency;
        pCrawl = pCrawl->children[index];

    }
    (pCrawl->frequency)++;
    pCrawl->temp_frequency=pCrawl->frequency;
    // mark last node as leaf
    pCrawl->isLeaf = true;
}
//Function to assign popularity to all the nodes of a particular string.

void assign_popularity(struct TrieNode *root, const char *key, int p)
{
    int level;
    int length = strlen(key);
    int index;
    struct TrieNode *pCrawl = root;
    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);
        if(pCrawl)
        {
            (pCrawl->frequency)++;
            pCrawl->temp_frequency=pCrawl->frequency;

        }
        pCrawl = pCrawl->children[index];
    }
}

//It calculates if the all the children of the node are null or not.
bool allnull(struct TrieNode *root)
{
    struct TrieNode *pCrawl = root;
    int flag=0;
    int level;
    for (level = 0; level < 26; level++)
    {
        if (pCrawl->children[level])
        flag++;
    }
    if(flag)
    return 1;
    else
    return 0;
}

//This function finds out the best children to traverse on.
int findbest(struct TrieNode *root)
{
    struct TrieNode *pCrawl = root;
    int flag=0,maximum=0,level=0;
    for (level = 0; level < 26; level++)
    {
        if (pCrawl->children[level])
        {
            if(maximum < pCrawl->children[level]->temp_frequency)
            {
                maximum = pCrawl->children[level]->temp_frequency;
                flag=level;
            }
        }

    }
    if(onlyonechild(pCrawl))
    {
            pCrawl->temp_frequency=0;
            //cout<<" hey :"<<INDEX_TO_CHAR(level)<<endl;
    }

    return flag;
}

// Returns true if key presents in trie, else false
bool search(struct TrieNode *root, const char *key)
{
    int level;
    int length = strlen(key);
    int index;
    struct TrieNode *pCrawl = root;
    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);
        if (!pCrawl->children[index])
        return false;
        pCrawl = pCrawl->children[index];
    }
    if(pCrawl->isLeaf)
    {
        (pCrawl->frequency)++;
        pCrawl->temp_frequency=pCrawl->frequency;
        assign_popularity(root,key,pCrawl->frequency);
    }
    return (pCrawl != NULL && pCrawl->isLeaf);
}


//Function to find the popularity all the nodes that lies on path of a string.
int popularity(struct TrieNode *root, const char *key)
{
    int level;
    int length = strlen(key);
    int index;
    struct TrieNode *pCrawl = root;

    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);
        //char arr[index];

        if (!pCrawl->children[index])
        return 0;
        cout<<endl<<"Popularity for " ;

        for(int j=0;j<level;j++)
        cout<<key[j];

        cout<<" is "<<pCrawl->temp_frequency<<endl;
        pCrawl = pCrawl->children[index];
    }
    return pCrawl->temp_frequency;
}
//changing the values of temp_frequency
void penalty_insert(struct TrieNode *root, const char *key)
{
    int level;
    int length = strlen(key);
    int index;
    struct TrieNode *pCrawl = root;

    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);
        if (pCrawl->children[index])
        {
            pCrawl->temp_frequency=pCrawl->frequency;
            pCrawl = pCrawl->children[index];
            pCrawl->temp_frequency=pCrawl->frequency;
        }
    }
}

//Query_Suggester
void query_suggester(struct TrieNode *root, const char *key)
{
    char query1[20][5];
    int level;
    int length = strlen(key);
    int index;
    struct TrieNode *pCrawl = root;
    //for traversing through trie to the end of query.
    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);
        pCrawl = pCrawl->children[index];
    }

    //Snippet to find the best candidate for a query.
    for(int candidate=0;candidate<5;candidate++)
    {
            struct TrieNode *root1 = pCrawl;
            int l;
            char query[20]={0};
            strcpy(query,key);
            //Program to copy query into a dummy string.
            cout<<endl<<"The candidate no."<<candidate+1<<" is ";
            int size1 =strlen(query);
            while(allnull(root1))
            {
                int pos=findbest(root1);
                query[size1++]=INDEX_TO_CHAR(pos);
                root1=root1->children[pos];
            }
            strcpy(query1[candidate],query);
            cout<<query1[candidate];
            cout<<endl;
            int abc = popularity(root,query);
            cout<<"Popularity of "<<query<<" is "<<abc;

    }
    for (int i = 0; i < 5; i++)
    {
        penalty_insert(root, query1[i]);
    }
}


// Driver
int main()
{
    // Input keys (use only 'a' through 'z' and lower case)
    char keys[][6] = {"this","there","then","than","the"};

    struct TrieNode *root = getNode();

    // Constructing trie by intserting the query
    int i,choice=0;
    for (i = 0; i < ARRAY_SIZE(keys); i++)
    insert(root, keys[i]);
/*
    ifstream file;
    file.open ("problem.txt");
    string word;
    while (file >> word)
    {
        char myArray[word.size()+1];//as 1 char space for null is also required
        strcpy(myArray, word.c_str());
        insert(root,myArray);
    }
*/
    while( choice!=4)
    {
        cout<<"\n \nEnter your choice \n";
        cout<<"1. Search \n";
        cout<<"2. Find Popularity \n";
        cout<<"3. Query Suggester \n";
        cout<<"4. Quit \n";
        cin>> choice;
        char term[10];
        int flag=0;
        if(choice==1)
        {
            cout<<"Enter the term you want to search: ";
            cin>>term;
            flag=search(root,term);
            if(flag)
            cout<<"Present in trie";
            else
            cout<<"Not Present in trie";

        }
        else if(choice==2)
        {
            cout<<"Enter the term you want to search:";
            cin>>term;
            flag=popularity(root,term);
            cout<<"Popularity for "<<term<<" is "<<flag;
        }
        else if(choice==3)
        {
            cout<<"Enter the term for query suggestion:";
            cin>>term;
            query_suggester(root,term);
        }
        else if(choice==4)
        {
            cout<<"Program Terminated";
            return 0;
        }
        else
        cout<<"Wrong choice\n";
    }
    return 0;
}
