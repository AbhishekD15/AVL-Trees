
#include <iostream>
#include <cstring>
#include <string>
using namespace std;


struct Node{

	
	int value;
	Node* left;
	Node* right;
	int height;

	//function declarations
	int getHeight(Node*);
	Node* newNode(Node*, int);
	Node* insertNode(Node*, int);
	
	Node* deleteNode(Node*, int);
	Node* rightRotation(Node*);
	Node* leftRotation(Node*);
	int getBalanceFactor(Node*);
	int getMax(int a, int b);
	Node* getLargestLeftNode(Node*);
	
	void printPreOrder(Node*);
	void printInOrder(Node*);
	void printPostOrder(Node*);
};

//fucntion to find the maximum of two integers
int Node::getMax(int a, int b){
    if(a>b)
        return a;
    return b;
}

//function to find the height of the BST
int Node::getHeight(Node* node){
	if(node!=NULL)
		return node->height;
	else
		return 0;
}

//function to find the balance factor of the BST
int Node::getBalanceFactor(Node* node){
	if(node != NULL) //check if the node is not NULL
		return (getHeight(node->left)- getHeight(node->right));
	
	return 0;
}
//function to create and initialise a new node
Node* Node::newNode(Node* node, int value){
	node = new Node();
	node->value = value;
	node->left = NULL;
	node->right = NULL;
	node->height = 1;
	return node;
}

// fucntion to insert a node into the BST
Node* Node::insertNode(Node* node,int value){
	if(node == NULL){ //check if the node is NULL
		return(newNode(node,value));
	}

	//check if the value of the new node is less than the value of the current node
	// and insert the node as a left node recursively
	if(value < node->value){
		node->left = insertNode(node->left, value);
	}

	//check if the value of the new node is greater than the value of the current node
	// and insert the node as a left node recursively
	else if(value > node->value){
		node->right = insertNode(node->right, value);
	}
	else{
		return node;
	}

	//increase the height
	if(node!=NULL){
	    node->height = 1 + getMax(getHeight(node->left),getHeight(node->right));
	}

	//find the balance factor
	int balance = getBalanceFactor(node);
	//left-left imbalance
	if(balance >1 && value < node->left->value){
		return rightRotation(node);
	}
	//left-right imbalance
	if(balance >1 && value > node->left->value){
		node->left = node->leftRotation(node->left);
		return rightRotation(node);
	}
	//right-right imbalance
	if(balance < -1 && value > node->right->value){
		return leftRotation(node);
	}
	//right-left imbalance
	if(balance < -1 && value < node->right->value){
		node->right = rightRotation(node->right);
		return leftRotation(node);
	}
	return node;
}

// fucntion to delete a node from the BST
Node* Node::deleteNode(Node* node, int value){
	if(node == NULL){ //check if the node is NULL
		return node;
	}
	//check if the value to be deleted is less than the value of the current node
	// and delete the node as a left node recursively
	if(value < node->value){
		node->left = deleteNode(node->left,value);
	}
	//check if the value to be deleted is greater than the value of the current node
	// and delete the node as a right node recursively
	else if(value > node->value){
		node->right = deleteNode(node->right,value);
	}
	// check if the node has only one child or no child
	else if(value == node->value){
		if(node->left == NULL && node->right == NULL){
			node = NULL;
		}
		else if(node->left == NULL && node->right != NULL){
			node = node->right;
		}
		else if(node->left != NULL && node->right == NULL){
			node = node->left;
		}
		else{//delete a node with two children, swap the value with the largest value on the left
			Node* temp = getLargestLeftNode(node->left); 
			node->value = temp->value;
			node->left = deleteNode(node->left,temp->value);
		}	
	}
	//increase the height
	if(node !=NULL){
		node->height = 1 + getMax(getHeight(node->left),getHeight(node->right));
	}
	//find the balance factor
	int balance = getBalanceFactor(node);
	
	//left-left imbalance
	if(balance >1 && getBalanceFactor(node->left)>=0){
		return rightRotation(node);
	}
	//left-right imbalance
	if(balance >1 &&  getBalanceFactor(node->left)<0){
		node->left = leftRotation(node->left);
		return rightRotation(node);
	}
	//right-right imbalance
	if(balance < -1 && getBalanceFactor(node->right)<=0){
		return leftRotation(node);
	}
	//right-left imbalance
	if(balance < -1 && getBalanceFactor(node->right)>0){
		node->right = rightRotation(node->right);
		return leftRotation(node);
	}
	return node;
		
	}

//function to find the largest value on the left
Node* Node::getLargestLeftNode(Node* node){
	Node* temp = node;
	while(temp->right != NULL){
		temp = temp->right;
	}
	return temp;
}	
	
//right rotation of node
Node* Node::rightRotation(Node* node){
	//create temporary node 
	Node* node_left = node->left;
	Node* left_right = node_left->right;

	//performa the right rotation
	node_left->right = node;
	node->left = left_right;

	//increasing the height of the  node
	if(node!=NULL || node->left!=NULL || node->right!=NULL)
	    node->height = 1 + getMax(getHeight(node->left),getHeight(node->right));
		

	if(node_left!=NULL || node_left->left!=NULL || node_left->right!=NULL)
	    node_left->height = 1 + getMax(getHeight(node_left->left),getHeight(node_left->right));
		
	//returning the new node
	return node_left;
}

//left rotation of node
Node* Node::leftRotation(Node* node){
	//create temporary node 
	Node* node_right = node->right;
	Node* right_left = node_right->left;

	//performa the left rotation
	node_right->left = node;
	node->right = right_left;

	//increasing height of node
	if(node!=NULL || node->left!=NULL || node->right!=NULL)
	    node->height = 1 + getMax(getHeight(node->left),getHeight(node->right));
		

	if(node_right!=NULL || node_right->left!=NULL || node_right->right!=NULL)
	    node_right->height = 1 + getMax(getHeight(node_right->left),getHeight(node_right->right));
		

	//returning the new node
	return node_right;
}
//function to print in PRE order
void Node::printPreOrder(Node* node){
	if(node!=NULL){
		cout << node->value << " ";
		
		printPreOrder(node->left);
		printPreOrder(node->right);
	}
	else{
	    return;
	}    
	
}
//function to print in IN order
void Node::printInOrder(Node* node){
	if(node != NULL){
		printInOrder(node->left);
		cout << node->value << " ";
		printInOrder(node->right);
	}
	else{
	    return;
	}    
	
}
//function to print in POST order
void Node::printPostOrder(Node* node){
	if(node!= NULL){
		printPostOrder(node->left);
		printPostOrder(node->right);
		cout << node->value << " ";
	}
	else{
	    return;
	}    
	
}
//MAIN Method
int main1(){

	Node* root = NULL;
	string input;
	int number;
	bool flag=true;

	int order=0;
	while (flag) {
		cin >> input;
		if (input[0] == 'P' || input[0] == 'I') {
			if (input == "PRE") {
				order = 1;
			}
			else if(input == "POST"){
				order = 2;
			}
			else if(input == "IN"){
				order = 3;
			}
			flag=false;
		}

		if (input[0] == 'A') {
			number=stoi(input.substr(1));
			root = root->insertNode(root, number);
		}
		else if (input[0] == 'D') {
			number=stoi(input.substr(1));    
			root = root->deleteNode(root, number);
		}

	}
	switch(order){
		case 1:
		if(root==NULL){
    		cout<<"EMPTY";
		}
		else{
    		root->printPreOrder(root);
    
		}  
		break;

		case 2:
		if(root==NULL){
    		cout<<"EMPTY";
		}
		else{
    		root->printPostOrder(root);
    
		}   
		break;

		case 3:
			if(root==NULL){
    			cout<<"EMPTY";
			}
			else{
    			root->printInOrder(root);
    
			}   
			break;


}

}


		 



