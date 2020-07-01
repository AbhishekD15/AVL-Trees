## AVL-Trees

**Implementing :**
- 1.Binary Tree Traversal
- 2.AVL Tree Insertion and Deletion
  
  This program starts by initializing an empty AVL tree. The program takes one line as input. The input line contains n “modification moves” separated by spaces (1 ≤ n ≤ 100). 
  
The available modification moves are:
  
-**Aint** (Character A followed by an int value between 1 and 100): A3 means insert value 3 into the AVL tree. If 3 is already in the tree, do nothing.

-**Dint** (Character D followed by an int value between 1 and 100): D3 means delete value 3 into the AVL tree. If 3 is not in the tree, do nothing.

Our input is then followed by exactly one finishing move (PRE or POST or IN): If the finishing move is PRE, then it should print out the tree (in its current situation) in pre-order. If the tree is empty, print out EMPTY. Otherwise, print out the values separated by spaces. POST and IN are handled similarly.

>Sample input 1: A1 A2 A3 IN
>Sample output 1: 1 2 3
>Sample input 2: A1 A2 A3 PRE
>Sample output 2: 2 1 3 Sample input 3: A1 D1 POST Sample output 3: EMPTY

	~~NOTE: NOT TAKEN CARE OF INVALID INPUTS	~~
