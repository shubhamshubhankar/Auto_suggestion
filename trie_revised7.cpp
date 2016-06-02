// C++ implementation of Query Auto suggestion using Trie(Based on the Heuristics)
#include "bits/stdc++.h"
using namespace std;
#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])

// Alphabet size (# of symbols)
#define ALPHABET_SIZE (26)

// Converts key current character into index
// use only 'a' through 'z' and lower case
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

//Function to convert index of an array into corresponding character value.
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
    struct TrieNode *parent;
    struct TrieNode *children[ALPHABET_SIZE];
    // isLeaf is true if the node represents
    // end of a word
    int frequency;
    int best_child;
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
        pNode->best_child=0;
        pNode->parent=NULL;
        for (i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;
    }
    return pNode;
}

//It calculates if the all the children of the node are null or not.
bool has_child(struct TrieNode *root)
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

//This function finds out the value of the best children to traverse on.
int best_of_child_value(struct TrieNode *root)
{
    struct TrieNode *pCrawl = root;
    int flag=0,maximum=0,level=0,temp=0;
    for (level = 0; level < 26; level++)
    {
        if (pCrawl->children[level])
        {
            temp++;
            if(maximum <= pCrawl->children[level]->best_child)
            {
                maximum = pCrawl->children[level]->best_child;
                flag=level;
            }
        }
        if(temp==0)
        maximum=pCrawl->frequency;
    }
    return maximum;
}

//This function finds out the best children to traverse on.
int best_of_child_position(struct TrieNode *root)
{
    struct TrieNode *pCrawl = root;
    int flag=0,maximum=0,level=0,temp=0;
    for (level = 0; level < 26; level++)
    {

        if (pCrawl->children[level])
        {
            temp++;
            if(maximum <= pCrawl->children[level]->best_child)
            {
                maximum = pCrawl->children[level]->best_child;
                flag=level;
            }

        }
        if(temp==0)
        flag=30;

    }
    return flag;
}


//Assigning best frequency from the children to the parent.
void assigning_best(struct TrieNode *pCrawl)
{
    while(pCrawl->parent)
    {

        pCrawl->best_child = best_of_child_value(pCrawl);
        pCrawl=pCrawl->parent;
    }
    pCrawl->best_child = best_of_child_value(pCrawl);
}

//Function to insert the term and its frequency.
void insert(struct TrieNode *root, const char *key,int times)
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
        pCrawl->children[index]->parent=pCrawl;
        pCrawl = pCrawl->children[index];
    }
    pCrawl->frequency+=times;
    pCrawl->isLeaf = true;          // mark last node as leaf
    assigning_best(pCrawl);
}

//Function to find the popularity of a particular term
int popularity(struct TrieNode *root, const char *key)
{
    int level;
    int length = strlen(key);
    int index;
    struct TrieNode *pCrawl = root;
    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);
        if (!pCrawl->children[index])
        return 0;
        cout<<endl<<"Popularity for " ;
        for(int j=0;j<level;j++)
        cout<<key[j];
        cout<<" is "<<pCrawl->best_child<<endl;
        pCrawl = pCrawl->children[index];
    }
    return pCrawl->best_child;
}

// Function to assign popularity to all the nodes of a particular string.
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
        pCrawl->frequency=pCrawl->frequency;
        assigning_best(pCrawl);
    }
    return (pCrawl != NULL && pCrawl->isLeaf);
}

// Function to suggest the top n queries on the basis of the hueristics.
void query_suggester(struct TrieNode *root, const char *key, int top_n_suggestions)
{
    char query1[top_n_suggestions][30];
    int penalty[top_n_suggestions];
    int level;
    int length = strlen(key);
    int index;
    struct TrieNode *pCrawl = root;

    //for Traversing through trie to the end of query.
    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);
        pCrawl = pCrawl->children[index];
    }

    for(int suggestion=0;suggestion<top_n_suggestions;suggestion++)
    {
            struct TrieNode *root1 = pCrawl;
            int l;
            char query[30]={0};
            strcpy(query,key);
            //Program to copy query into a dummy string.
            cout<<endl<<"The candidate no."<<suggestion+1<<" is ";
            int size1 =strlen(query);
            while(has_child(root1))
            {
                int pos=best_of_child_position(root1);
                if((root1->children[pos]->best_child > root1->frequency) && pos!=30)
                {
                    query[size1++]=INDEX_TO_CHAR(pos);
                    root1=root1->children[pos];
                }
                else
                break;
            }
            penalty[suggestion]=root1->frequency;
            root1->frequency=0;
            assigning_best(root1);
            strcpy(query1[suggestion],query);
            cout<<query1[suggestion]<<" -"<<penalty[suggestion];
            cout<<endl;
    }
    
    //Revival of the queries. 
    for (int i = 0; i < top_n_suggestions; i++)
    {
        insert(root,query1[i],penalty[i]);
    }
}


// Driver
int main()
{
    char keys[][20] = {"abalones","abamp","abampere","abamperes","abamps","aband","abandon"};
    struct TrieNode *root = getNode();
    for (int i = 0; i < ARRAY_SIZE(keys); i++)
    insert(root, keys[i],1);
    insert(root,keys[6],2);
    insert(root,keys[0],4);
    insert(root,keys[5],1);
    
    int choice=0;
    
    while(choice!=6  )
    {
        cout<<"\n \n Enter your choice \n";
        cout<<"1. Insert \n";
        cout<<"2. Search \n";
        cout<<"3. Find Popularity \n";
        cout<<"4. Auto Suggestion \n";
        cout<<"5. Inserting a dictionary \n";
        cout<<"6. Quit \n";
        cin>> choice;
        char term[30];
        int flag=0;
        int top_n_suggestions=3;
        if(choice==1)
        {
            int frequency=1;
            cout<<"Enter the term you want to insert: ";
            cin>>term;
            
            // To convert the string into lowercase.
            for(int i=0;i<strlen(term);i++)
            tolower(term[i]);
            
            cout<<"Enter the frequency for "<<term<<":";
            cin>>frequency;
            insert(root,term,frequency);
        }
        else if(choice==2)
        {
            cout<<"Enter the term you want to search:";
            cin>>term;

            // To convert the string into lowercase.
            for(int i=0;i<strlen(term);i++)
            tolower(term[i]);
            
            flag=search(root,term);
            
            if(flag)
            cout<<"Present in the trie\n";
            else
            cout<<"Not present\n";
        }
        else if(choice==3)
        {
            cout<<"Enter the term you want to search:";
            cin>>term;
            
            // To convert the string into lowercase.
            for(int i=0;i<strlen(term);i++)
            tolower(term[i]);
            
            flag=popularity(root,term);
            cout<<"\nPopularity for "<<term<<" is "<<flag;
        }
        else if(choice==4)
        {
            cout<<"Enter the term for query suggestion:";
            cin>>term;
            
            // To convert the string into lowercase.
            for(int i=0;i<strlen(term);i++)
            tolower(term[i]);
            
            cout<<"\nEnter the no. of suggestions: ";
            cin>>top_n_suggestions;
            query_suggester(root,term,top_n_suggestions);
        }
        else if(choice==5)
        {
            char filename[50];
            cout<<"Enter the filename where dictionary exist: ";
            cin>>filename;
            cout<<endl;
            ifstream file;
            file.open(filename);
            string word;
            
            // To convert the string into lowercase.
            for(int i=0;i<word.size();i++)
            tolower(word[i]);

            while (file >> word)
            {
                char myArray[word.size()+1];  //as 1 char space for null is also required
                strcpy(myArray, word.c_str());
                insert(root,myArray,1);
            }
        }
        else if(choice==6)
        {
            cout<<"Program Terminated";
            return 0;
        }
        else
        cout<<"Wrong choice\n";
    }
    return 0;
}
