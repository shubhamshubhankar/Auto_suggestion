//C++ implementation of Query Auto Suggestion using Trie (Brute Force (DFS))
#include "bits/stdc++.h"
using namespace std;

// Function to convert character into index.
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

// Alphabet size (# of symbols)
#define ALPHABET_SIZE (27) 		// One extra to capture the root node also.

// Function to find the size of an array.
#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])   

// Function to convert Index to corresponding Character value. 
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

// For storing the values of best suggestions in a linked list.
typedef struct down_linklist
{
	int cost;		// For storing the cost of a suggestion, when it reaches the leaf.
	vector<char> v;	// For storing the whole word in a vector for displaying purpose.
} down_linklist;


// trie node
typedef struct node
{
	int value;
	int real_count;
	int frequency; 
	bool isLeaf;  // isLeaf is true if the node represents end of a word
	node *children[ALPHABET_SIZE];
}node;

list <down_linklist> popular_searches;

// Returns new trie node (initialized to NULL)
node * getNode()
{
	node *pNode= (node *)calloc(1,sizeof(node));
	if(pNode)
	{
		pNode->value=0;
		pNode->frequency=0;
		pNode->real_count=0;
		pNode->isLeaf=false;
		for(int i=0;i<27;i++)
		pNode->children[i]=NULL;
	}
	return pNode;
}

//Function to insert the values in a trie.
void insert(node* root,char *key,int start_key)  			// start_key is for starting index of the key.
{
	int length=strlen(key);
	int index= CHAR_TO_INDEX(key[start_key]);

	if(!root->children[index])  							// checking if the node exist ?
	root->children[index]=getNode();						// make a new node
	root->frequency++;
	root->value=start_key;
	
	if(length-1!=start_key)									// checking for a base case
	insert(root->children[index],key,start_key+1);
	
	else
	{
		root->children[index]->frequency++;
		root->children[index]->value=start_key+1;			// do the same for the children
		root->children[index]->isLeaf=true;
		root->children[index]->real_count=1;
	}

}

// Function  to display the whole trie.
// In this function the pointer is traversing to every node in the trie using dfs. 
void display_trie(node * root)
{
		for(int i=0;i<ALPHABET_SIZE;i++)
		{
			if(root->children[i])
			{
				printf("%c-%d\n",i+97,root->children[i]->frequency);
				display_trie(root->children[i]);
			}
		}

}

//  Function to reach the aimed pointer for further searching.
node * traverse_trie(node * root,char *key,int start_key)
{
	int length=strlen(key);
	int index= CHAR_TO_INDEX(key[start_key]);

	if(length==start_key)
		return root; 
	if(root->children[index])  // checking if the node exist ?
	{
		return traverse_trie(root->children[index],key,start_key+1);
	}
}

// Function to fetch the most popular queries in an order.
void fetch_queries(node* root,down_linklist element)
{
	//If the root is a leaf.
	if(root->isLeaf)
	{
		element.cost=root->real_count;
		list<down_linklist>::iterator it;
		
		//If the linked list is empty, put the element in front of the linked list.
		if(popular_searches.empty())
		{
			popular_searches.push_front(element);
		}
		
		//Else search its correct position, where it should be placed.
		else
		{
			for(it=popular_searches.begin();it!=popular_searches.end();it++)
			{
				if((*it).cost <= element.cost)	 
				break;	
			}
			popular_searches.insert(it,element);
		}
	}
	
	//Depth first search(DFS) to find out the cost of every word. 
	for(int i=0;i<ALPHABET_SIZE;i++)
	{
		if(root->children[i])
		{
			element.v.push_back((INDEX_TO_CHAR(i)));
			fetch_queries(root->children[i],element);
			element.v.pop_back();
		}
	}

}

// Function to search whether a word is present in the trie or not.
bool search(node * root,char * key,int start_key,int freq)
{
	int length=strlen(key);
	int index= CHAR_TO_INDEX(key[start_key]);
	
	if(root->children[index])  					// Checking if the node exist ?
	{
		root->frequency+=freq;
		if(length-1 == start_key)
		{
			if(root->children[index]->isLeaf)
			{
					root->children[index]->frequency+=freq;
					root->children[index]->real_count+=freq;
					return true;
			}
			else
			return false;
		}
		else
		return search(root->children[index],key,start_key+1,freq);
	}
	else
	return false;
}

// Function to increase the frequency and real_count, when found.
void final_search(node * root ,char * key)
{
	if(search(root,key,0,0))   				// If word found
	{
		search(root,key,0,1);				// Then we increase its frequency and the real_count by one. 
	}
	else
		printf("NO......\n");
}
			
int main()
{
	node *root = getNode();
	// Input keys (use only 'a' through 'z' and lower case)
    char keys[][20] = {"abalones","abamp","abampere","abamperes","abamps","aband","abandon"};

    /*char a[100];
    for (int i = 0; i < 100; i++)
    {
    	scanf("%s",a);

    	// To convert the string into lowercase.
    	for(int i=0;i<strlen(a);i++)
        a[i]=tolower(a[i]);
    	
    	insert(root, a, 0);
    }

    for(int i=0;i<50;i++)
    {
    	scanf("%s",a);
    	final_search(root,a);
    }*/
    
    //printf("\n");
   	//display_trie(root);
    
    //For small input.
    for (int i = 0; i < 7; i++)
    {
    	insert(root,keys[i],0);
    }
    final_search(root,keys[6]);
    final_search(root,keys[6]);
    final_search(root,keys[0]);
    final_search(root,keys[0]);
    final_search(root,keys[0]);
    final_search(root,keys[0]);
    final_search(root,keys[5]);

    down_linklist element;
    element.cost=0;

    char test[]={"ab"};

    fetch_queries(traverse_trie(root,test,0),element);
    list<down_linklist>::iterator it;
    printf("\n %d\n",(int)popular_searches.size());
    
    //Code snippet to show all the popular searches in decreasing order.
    for(it=popular_searches.begin();it!=popular_searches.end();it++)
    {
    	printf("%d - ",(*it).cost);
    	printf("%s",test );
    	for (vector<char>::const_iterator i = it->v.begin(); i != it->v.end(); ++i)
      	printf("%c",(*i) );
      	printf("\n");
    }

	return 0;
}
	
