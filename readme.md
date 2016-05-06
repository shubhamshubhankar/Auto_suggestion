This is a C++ implementation of Query Auto Suggestion using Trie(Brute Force (DFS))

Structure of Trie
It contains following variables:
(a)value: 		Keeps the count of the depth of the node from the root.
(b)real_count: 	Keeps the track of how many times a particular word has been encountered, real_count will be zero except for 
				leaf nodes.
(c)frequency: 	Shows how many times a particular node is traversed.
(d)isLeaf:		Shows whether a node is a leaf or not.
(e)children:	Shows the links to the children nodes, if any.

Structure of down_linkedlist
(a)cost: 		For storing the cost of a suggestion, when it reaches the leaf.
(b)v:    		For storing the whole word in a vector for displaying purpose.

Function getnode: 		Returns a initialized node.

Function insert: 		Inserts a word into a trie.

Function display_trie: 	Displays all the nodes of the trie with their frequency.

Function traverse_trie: Traverses the trie until the end of a subquery(i.e. "ab").

Function search: 		Returns a bool value to show whether a word is in trie or not.

Function final_search: 	Increaments the no. of occurences of a particular word by factor of 1,if a word is present in trie.

Function fetch_queries: Function which fetches all the queries with their cost and stores it in a global variable popular search. 

Algorithm: 

A pointer traverses till the end of the subquery.

Then a pointer traverses all the nodes of the trie with root at the end of the subquery.

Whenever it encounters a leaf node. It checks whether the linked list is empty or not. 

If its empty, it puts the word and its real_count in the front of the trie.

Otherwise, it keeps the element in the decreasing order of its real_count.

Input: A text file containing 100 distinct words and then 50 reoccuring words separated by a newline.
Output: Displays all the queries with their frequency in decreasing order.