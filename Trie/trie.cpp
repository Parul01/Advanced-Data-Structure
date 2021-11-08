#include<iostream>
using namespace std;
#define nOB 39
#define ll long long int


class Trie{
	struct Node{
		Node* left;
		Node* right;
		Node(){
			left = NULL;
			right = NULL;
		}

	};

	Node* root;
	int count;

public:

	Trie(int n){
		count = n;
		root = new Node();
	}

	// logic to insert a node (int is stored as its binary equivalent)
	void insertNumber(ll n){

		int bitValue;
		Node* tmp = root;

		for(ll i = nOB;i>=0;i--){
			ll shiftBit = n>>i;
			bitValue = shiftBit & (ll)1;

			if(bitValue == 1){
				if(tmp->right == NULL){
					// insert node at right of tmp;
					tmp->right = new Node();

				}
				tmp = tmp->right;
			}else{
				if(tmp->left == NULL){
					tmp->left = new Node();

				}
				tmp = tmp->left;

			}
		}


		// if(root->left == NULL && root->right == NULL)

	}

	void insert(ll *nbr){

		for(int i =0;i<count;i++){
			insertNumber(nbr[i]);
		}

	}

	ll maxXOR(ll n){
		Node* tmp = root;
		int bitValue;
		ll maxCurr=0;
		int mul =1;


		for(ll i=nOB;i>=0;i--){
			// mul = 
			bitValue = n >> i;

			// if XOR is 1, find 0 to get XOR 1
			if ((bitValue&(ll)1)== 0){  // find 0
				if (tmp->right != NULL){
					tmp=tmp->right;
					maxCurr += (1<<i);

				}else{
					tmp=tmp->left;

				}

				
			}else{  //find 1
				if(tmp->left != NULL){
					tmp = tmp->left;
					maxCurr += (1<<i);
				}else{
					tmp = tmp->right;
				}
			}

		}
		return maxCurr;

	}


};

int main(int argc, char const *argv[])
{
	// cout<<sizeof(unsigned long long int)<<endl;
	Trie *t = new Trie(4);
	ll arr[5] = {3,10,7,21};
	t->insert(arr);
	cout<<t->maxXOR(3)<<endl;
	cout<<t->maxXOR(10)<<endl;
	cout<<t->maxXOR(21)<<endl;

	// t.insert(3);
	// cout<<t.maxXOR(3)<<endl;
	// t.insert(10);
	// cout<<t.maxXOR(10)<<endl;
	return 0;
}