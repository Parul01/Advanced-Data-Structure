#include<iostream>
#include<string>

using namespace std;

template<class T>
class AVL{

private:

	template<class T2>
	struct Node{
		T2 data;
		struct Node<T2>* left;
		struct Node<T2>*right;
		int height;
		int leftSubTCount;
		int rightSubTCount;
		int bal_fact;
		int occCount;

		Node(T2 d){
			data = d;
			left = NULL;
			right = NULL;
			height = 1;
			leftSubTCount = 0;
			rightSubTCount = 0;	
			bal_fact = 0;
			occCount = 1;	
		}
	};

	Node<T>* root;

	int findHeight(Node<T>* root){
		if(root == NULL) return 0;
		if(root->left == NULL){
			if(root->right == NULL){
				return 1;
			}else{
				return (root->right->height+1);
			}
		}

		if(root->right == NULL){
			if(root->left == NULL){
				return 1;
			}else{
				return (root->left->height+1);
			}
		}

		return (max(root->left->height,root->right->height)+1);
	}

	// balance out
	Node<T>* selfBalance(Node<T>* root){

	}

	Node<T>* inorderSuccessor(Node<T>* root){
		Node<T>* successor = root;

		while(successor->left != NULL){
			successor = successor->left;
		}
		return successor;
	}


	int findBalancingFactor(Node<T>* root){
		if(root == NULL) return 0;

		if(root->left == NULL && root->right == NULL) return 0;

		if(root->left == NULL && root->right != NULL){
			return (0 - root->right->height);
		}
		if(root->right == NULL && root->left != NULL){
			return (root->left->height - 0);
		}

		// return(findBalancingFactor(root->left) - findBalancingFactor(root->right));
		return (root->left->height - root->right->height);
	}

	Node<T>* rightRotate(Node<T>* c){
		Node<T>* b = c->left;
		Node<T>* a = b->right;

		//rotate
		b->right = c;
		c->left = a;

		// update height
		c->height = findHeight(c);
		b->height = findHeight(b);
		c->bal_fact = findBalancingFactor(c);
		b->bal_fact = findBalancingFactor(b);
		c->leftSubTCount = leftSubTreeWT(c);
		c->rightSubTCount = rightSubTreeWT(c);
		b->leftSubTCount = leftSubTreeWT(b);
		b->rightSubTCount = rightSubTreeWT(b);

		return b;
	}

	Node<T>* leftRotate(Node<T>* c){
		Node<T>* b = c->right;
		Node<T>*  a = b->left;

		//rotate
		b->left = c;
		c->right = a;

		// update height (sequence matters below)
		c->height = findHeight(c);
		b->height = findHeight(b);
		c->bal_fact = findBalancingFactor(c);
		b->bal_fact = findBalancingFactor(b);
		c->leftSubTCount = leftSubTreeWT(c);
		c->rightSubTCount = rightSubTreeWT(c);
		b->leftSubTCount = leftSubTreeWT(b);
		b->rightSubTCount = rightSubTreeWT(b);

		return b;
	}

	Node<T>* delete_dup(Node<T>* root, T value, bool flag){
		// cout<<"  IN "<<endl;
		// Node<T>* tmp;
		if(root == NULL){
			return NULL;
		}else if(value == root->data){
			//Found node to delete, 3 cases will follow up
			if(root->occCount > 1 && flag == false){
				// no balancing also required in this case
				root->occCount -= 1;
				return root;
			}
			//1. Node with 0 children
			else if(root->left == NULL && root->right == NULL){
				delete root;
				root = NULL;
			}

			//2. Node with 1 child
			else if(root->left != NULL && root->right == NULL){
				Node<T>* leftChild = root->left;
				delete root;
				root = leftChild;
			}
			else if(root->right != NULL && root->left == NULL){
				Node<T>* rightChild = root->right;
				delete root;
				root = rightChild;
			}

			//3. if both chidlren are not null
			else if(root->left != NULL && root->right != NULL){
				//find inorder successor
				Node<T>* successor = inorderSuccessor(root->right);
				root->data = successor->data;
				root->occCount = successor->occCount;

				root->right = delete_dup(root->right,successor->data,true);
				// root->height = findHeight
			}

			// root->height = findHeight(root);
			// root->bal_fact = findBalancingFactor(root);


		}else if(value <  root->data){
			root->left = delete_dup(root->left,value,flag);
		}else{
			root->right = delete_dup(root->right,value,flag);
		}

		if(root == NULL){
			return NULL;
		}

		root->height = findHeight(root);
		root->bal_fact = findBalancingFactor(root);

		// LL case
		if(root->bal_fact > 1 && root->left->bal_fact >= 0){
			return rightRotate(root);
		}

		// RR case
		if(root->bal_fact < -1 && root->right->bal_fact <= 0){
			return leftRotate(root);
		}

		// LR case
		if(root->bal_fact > 1 && root->left->bal_fact < 0){
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}

		// RL case
		if(root->bal_fact < -1 && root->right->bal_fact > 0 ){
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}

		root->leftSubTCount = leftSubTreeWT(root);
		root->rightSubTCount = rightSubTreeWT(root);

		return root;


	}

	int leftSubTreeWT(Node<T>* root){
		if(root->left == NULL) return 0;

		return (root->left->leftSubTCount + root->left->rightSubTCount + root->left->occCount);
	}

	int rightSubTreeWT(Node<T>* root){
		if(root->right == NULL) return 0;
		return (root->right->rightSubTCount + root->right->leftSubTCount + root->right->occCount);
	}

	Node<T>* insert_dup(Node<T>* root, T item){

		if(root == NULL){
			Node<T>* node = new Node<T>(item);
			return node;
		}

		//duplicates allowed // balancing factor not disturbed
		if(item == root->data){
			root->occCount += 1;
			return root;
		}

		if(item > root->data){
			root->right = insert_dup(root->right,item);
		}else if(item < root->data){
			root->left = insert_dup(root->left, item);
		}

		root->height = findHeight(root);
		root->bal_fact = findBalancingFactor(root);

		// LL case
		if(root->bal_fact > 1 && item < root->left->data){
			return rightRotate(root);
		}

		// RR case
		if(root->bal_fact < -1 && item > root->right->data){
			return leftRotate(root);
		}

		// LR case
		if(root->bal_fact > 1 && item > root->left->data){
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}

		// RL case
		if(root->bal_fact < -1 && item < root->right->data ){
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}
		// if(bal_fact < 1 || bal_fact > 1){
		// 	selfBalance(root);
		// }

		root->leftSubTCount = leftSubTreeWT(root);
		root->rightSubTCount = rightSubTreeWT(root);
		return root;
	}

	// void display_dup(Node<T>* root){
	// 	if(root ==  NULL) return;
	// 	string str = "";

	// 	if(root->left == NULL){
	// 		str += ".";
	// 	}else{
	// 		str += to_string(root->left->data);
	// 	}

	// 	str += " - " + to_string(root->data) + " - ";

	// 	if(root->right == NULL){
	// 		str += ".";
	// 	}else{
	// 		str += to_string(root->right->data);
	// 	}

	// 	cout<<str<<endl;

	// 	display_dup(root->left);
	// 	display_dup(root->right);
	// }


	void display_dup(Node<T>* root){
		if(root ==  NULL) return;
		string str = "";

		if(root->left == NULL){
			str += ".";
		}else{
			str += to_string(root->left->data);
		}

		str += " -> " + to_string(root->leftSubTCount)+" ** "+to_string(root->data)+ " ** "+to_string(root->rightSubTCount)+ " <- ";

		if(root->right == NULL){
			str += ".";
		}else{
			str += to_string(root->right->data);
		}

		cout<<str<<endl;

		display_dup(root->left);
		display_dup(root->right);
	}

	bool search_dup(Node<T>* root, T value){
		if(root == NULL) return false;
		if(root->data == value) return true;
		if(value < root->data) return search_dup(root->left,value);
		if(value > root->data) return search_dup(root->right,value);
	}

	int countOccurances_dup(Node<T>* root, T value){
		if(root == NULL) return 0;
		if(root->data == value) return root->occCount;
		if(value < root->data) return countOccurances_dup(root->left,value);
		if(value > root->data) return countOccurances_dup(root->right,value);
	}


// NOT WORKING
	// int lower_bound_dup(Node* root, int value){
	// 	// if(root == NULL) return INT8_MAX;
	// 	if(root->data == value) return value;
	// 	if(root->data > value && root->left == NULL) return root->data;
	// 	if(root->data > value && root->left != NULL){
	// 		cout<<" IN "<<endl;
	// 		return min(root->data,lower_bound_dup(root->left,value));
	// 	}
	// 	if(root->data < value && root->right == NULL) return
	// 	if(root->data < value && root->right != NULL){
	// 		if(root->right->data < value)
	// 		return lower_bound_dup(root->right,value);
	// 	}

	// 	// return 1;
	// }

	Node<T>* lower_bound_dup(Node<T>* root, T x){
		if(root == NULL) return NULL;
		if(x == root->data) return root;
		if(x < root->data && root->left == NULL) return root;
		if( x < root->data){
			Node<T>* tmp = lower_bound_dup(root->left,x);
			if(tmp == NULL) return root;
			if(root->data < tmp->data){
				return root;
			 // min(root->data, (lower_bound_dup(root->left,x))->data);
			}else{
				return tmp;
			}
		}
		// if(x > root->data && root->right == NULL)
		if(x > root->data){
			return lower_bound_dup(root->right,x);
		}
	}

	Node<T>* rootSuccessor(Node<T>* root){
		Node<T>* successor = root;

		while(successor->left != NULL){
			successor = successor->left;
		}
		return successor;
	}
	

	T KthLargest_dup(Node<T>* root, int k){
		if(root == NULL) return 0; // required?
		if(k == (root->rightSubTCount+1)) return root->data;

		if(k == root->rightSubTCount){
			return (rootSuccessor(root->right))->data;
		}

		if(k > root->rightSubTCount){
			if((root->occCount + root->rightSubTCount) >= k) return root->data;
			return KthLargest_dup(root->left, (k - (root->occCount + root->rightSubTCount)));
		}
		if(k < root->rightSubTCount){
			return KthLargest_dup(root->right, k);
		}
	}

	// retrieve greatest element which is not more than a given no.
	Node<T>* getGreatest(Node<T>* root,T x ){
		if(root == NULL) return NULL;
		if(x == root->data) return root;
		if(x > root->data && root->right == NULL) return root;
		if( x > root->data){
			Node<T>* tmp = getGreatest(root->right,x);
			if(tmp == NULL) return root;
			if(root->data > tmp->data){
				return root;
			 // min(root->data, (lower_bound_dup(root->left,x))->data);
			}else{
				return tmp;
			}
		}
		// if(x > root->data && root->right == NULL)
		if(x < root->data){
			return getGreatest(root->left,x);
		}
	}

	Node<T>* getClosestElement_dup(Node<T>* root, T value){

		Node<T>* lowerMax = lower_bound_dup(root,value);
		Node<T>* upperMin = getGreatest(root,value);
		if(lowerMax == NULL){
			if(upperMin == NULL){
				return NULL;
			}else{
				return upperMin;
			}
		}

		if(upperMin == NULL){
			return lowerMax;
		}




		// getDifference -- least diff will be closest

		T lowDiff = lowerMax->data - value;
		T upDiff = value - upperMin->data;

		if(lowDiff < upDiff){
			return lowerMax;
		}else{
			return upperMin;
		}

	}

	Node<T>* upper_bound_dup(Node<T>* root, T x){
		if(root == NULL) return NULL;
		// if(x == root->data) return root;
		if(x < root->data && root->left == NULL) return root;
		if( x < root->data){
			Node<T>* tmp = upper_bound_dup(root->left,x);
			if(tmp == NULL) return root;
			if(root->data < tmp->data){
				return root;
			 // min(root->data, (lower_bound_dup(root->left,x))->data);
			}else{
				return tmp;
			}
		}else{
			return upper_bound_dup(root->right,x);
		}
		// if(x > root->data && root->right == NULL)
		// if(x > root->data){
		// 	return upper_bound_dup(root->right,x);
		// }

	}


public:

	AVL(){
		root = NULL;
	}
	void insert(T value){
		root = insert_dup(root,value);
	}


	void display(){
		display_dup(root);
	}

	// 3 types of node deletion
	// 0 children
	// 1 children
	// 2 children
	void delete_node(T value){
		root = delete_dup(root,value,false);
	}

	bool search(T value){
		return search_dup(root,value);
	}

	int countOccurances(T value){
		return countOccurances_dup(root, value);
	}

	T lower_bound(T value){

		Node<T>* tmp = lower_bound_dup(root, value);
		if(tmp != NULL) return tmp->data;
	}


	T upper_bound(T value){

		Node<T>* tmp = upper_bound_dup(root, value);
		if(tmp != NULL) return tmp->data;
	}



	T KthLargest(int k){
		return KthLargest_dup(root, k);
	}

	int countRange(T l, T r){
		// logic
		// leftBound = get lowerbound node
		// rightBound = get upperbound node
		// total elements == root->leftsubtcount + root->rightsubtreecount + root->occCount
		// total - (leftBound->leftsubtcount + rightBound->rightsubtreecount)

		int totalElements = root->leftSubTCount + root->rightSubTCount + root->occCount;
		Node<T>* leftBound = lower_bound_dup(root, l); // greater or equal
		Node<T>* rightBound = getGreatest(root, r); // lesser or equal
		// cout<<"left "<<leftBound->leftSubTCount<<"right "<<rightBound->rightSubTCount<<endl;
		// cout<<"left "<<leftBound->data<<"right "<<rightBound->data<<endl;

		return (totalElements - (leftBound->leftSubTCount + rightBound->rightSubTCount));


	}

	T getClosestElement(T value){
		Node<T>* tmp = getClosestElement_dup(root,value);
		if(tmp != NULL){
			return tmp->data;
		}
		

	}	

	T getGreatestt(T k){
		return getGreatest(root, k)->data;
	}

	int getCountInRange(T l, T r){
		return getCountInRange_dup(root,l,r);
	}



};

int main(int argc, char const *argv[])
{
	AVL<int> t;
	t.insert(20);
	t.insert(25);
	t.insert(30);
	t.insert(10);
	t.insert(5);
	t.insert(15);
	t.insert(27);
	t.insert(19);
	t.insert(16);

	cout<<" ---  ";
	cout<<t.getClosestElement(32)<<endl;
	
// 	t.delete_node(10);
// 	t.delete_node(5);

// 	t.delete_node(20);


// 	t.insert(10);

// 	t.insert(4);

// 	t.insert(17);
// 	t.display();

	// cout<<t.KthLargest(3)<<endl;



	// cout<<" ---------------------- "<<endl;
	//10,8,7,5,3,2,1
	// t.insert(10);
	// t.insert(8);
	// t.insert(7);
	// t.insert(5);
	// t.insert(3);
	// t.insert(2);
	// t.insert(1);
	
	// t.display();
	// cout<<" ------------ "<<endl;
	// cout<<t.lower_bound(18)<<endl;
	// cout<<t.lower_bound(27)<<endl;

	// cout<<" ------------ "<<endl;
	// cout<<t.getGreatestt(19)<<endl;
	// cout<<t.getGreatestt(28)<<endl;
	// cout<<" ------------ "<<endl;
	// cout<<t.countRange(10,19)<<endl;

	// cout<<"closest Element "<<t.getClosestElement(18);

	// AVL<int> t;

	// int q;
	// cin>>q;

	// while(q--){
	// 	int no;
	// 	//int x;
	// 	cin>>no;
	// 	switch(no){
	// 		case 1:{  //insert
	// 				int x;
	// 				cin>>x;
	// 				t.insert(x);
	// 				// t.display();
	// 				break;
	// 				}
	// 		case 2:{ //delete
	// 				int x;
	// 				cin>>x;
	// 				t.delete_node(x);
	// 				// t.display();
	// 				break;
	// 				}
	// 		case 3:{ //search
	// 				int x;
	// 				cin>>x;
	// 				cout<<t.search(x)<<endl;
	// 				// t.display();
	// 				break;

	// 				}
	// 		case 4:{ //count occurances
	// 				int x;
	// 				cin>>x;
	// 				cout<<t.countOccurances(x)<<endl;
	// 				// t.display();
	// 				break;
	// 				}
	// 		case 5:{  //lower bound
	// 				int x;
	// 				cin>>x;
	// 				cout<<lower_bound(x)<<endl;
					
	// 				// t.display();
	// 				break;
	// 				}
	// 		case 6:{  //upper bound
	// 				int x;
	// 				cin>>x;

	// 				cout<<t.upper_bound(x)<<endl;
					
	// 				break;
	// 				}
	// 		case 7:{  //get closest element
	// 				int x;
	// 				cin>>x;
	// 				cout<<t.getClosestElement(x)<<endl;
					
	// 				break;
	// 				}
	// 		case 8:{ //get kth largest element
	// 				int k;
	// 				cin>>k;
	// 				cout<<t.KthLargest(k)<<endl;
	// 				break;
	// 				}	
	// 		case 9:{  //count elements in range
	// 				int l,r;
	// 				cin>>l>>r;
	// 				cout<<t.getCountInRange(l,r)<<endl;
	// 				break;
	// 				}

			
	// 		default:{

	// 				}

	// 	}
	// }
	

	return 0;
}