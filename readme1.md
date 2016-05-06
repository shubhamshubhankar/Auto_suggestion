This is a C++ implementation of Query Auto Suggestion using Trie(Heuristic Based)

Structure of Trie
It contains following variables:
(a)parent: 		Keeps the track of address of the parent node.
(b)frequency: 	Keeps the track of how many times a particular word has been encountered, real_count will be zero except for 
				leaf nodes.
(c)best_child: 	Shows the frequency of the best child.
(d)isLeaf:		Shows whether a node is a leaf or not.
(e)children:	Keeps the track of the address of child nodes, if any.

 
Function getnode: 					Returns a initialized node.

Function insert: 					Inserts a word into a trie with a given frequency(default value is 1).

Function has_child:					Returns a bool value to show whether a node has child or not.

Function best_of_child_value:		Returns the value of the best child to traverse on.

Function best_of_child_position: 	This function finds out the position of the best child to traverse on.

Function search: 					Returns a bool value to show whether a word is in trie or not.

Function assigning_best:			Assigning best frequency from the children to the parent.

Function popularity:				Shows the popularity of a particular term.

Function query_suggester:			Shows the top n suggestions for a particular subquery.			


Algorithm: 

A pointer traverses till the end of the subquery.

Then a pointer traverses to the best node of the trie with root at the end of the subquery.

Whenever it encounters a leaf node. It check whether its children has best_child greater than its frequency or not. 

If the current node has frequency more than that of its children's best_child. It puts the whole word into an array with its frequency in another array. It assigns 0 to the frequency of the current node. And reassigns the values of all the parent nodes of this node.

Otherwise, it keeps on traversing to the end of the leaf.

Input: A text file containing 150  words separated by a newline.
Output: Top n suggestions with their frequency.
