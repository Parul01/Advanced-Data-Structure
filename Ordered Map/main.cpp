#include<iostream>
#include<bits/stdc++.h>
using namespace std;

template<class T, class U>
class mapNode
{   

    public:
    T key;
    U value;
    int  height;
    mapNode<T,U>* left;
    mapNode<T,U>* right;

    mapNode(T k, U v)
    {
        key=k;
        value=v;
        left=right=NULL;
        height=1;
    }    


};


template<class T,class U>
class OrderedMap
{
public:

mapNode<T,U>*root;
int mapNodeCount;

OrderedMap()
{
    mapNodeCount=0;
    root=NULL;
}
 
	

U& operator[] (T k) 
{
 
 mapNode<T,U>* temp=findHelper(root,k);
 if(temp==NULL)
 {
	 U v;
	 map_insert(k,v);
	 mapNode<T,U>* q=findHelper(root,k);
	 return q->value;
 }
 	return temp->value;
}





int findBalancingFactor(mapNode<T,U>* root){
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


int findHeight(mapNode<T,U>* top){
		if(top == NULL) return 0;
		if(top->left == NULL){
			if(top->right == NULL){
				return 1;
			}else{
				return (top->right->height+1);
			}
		}

		if(top->right == NULL){
			if(top->left == NULL){
				return 1;
			}else{
				return (top->left->height+1);
			}
		}

		return (max(top->left->height,top->right->height)+1);
	}




void print(){
    if(root==NULL)
        cout<<"Map Empty-Nothing to print!"<<endl;
    display(root);
}

	void display(mapNode<T,U> *top){
		if(top ==  NULL) return;
		string str = "";

		if(top->left == NULL){
			str += ".";
		}else{
			str += to_string(top->left->key);
		}

		str += " - " + to_string(top->key) + " - ";

		if(top->right == NULL){
			str += ".";
		}else{
			str += to_string(top->right->key);
		}

		cout<<str<<endl;

		display(top->left);
		display(top->right);
	}



mapNode<T,U>* leftRotate(mapNode<T,U>* c){
		mapNode<T,U>* b = c->right;
		mapNode<T,U>*  T2 = b->left;

		//rotate
		b->left = c;
		c->right = T2;

		// update height (sequence matters below)
		c->height = findHeight(c);
		b->height = findHeight(b);
		

		return b;
	}


mapNode<T,U>* rightRotate(mapNode<T,U>* c){
		mapNode<T,U>* b = c->left;
		mapNode<T,U>* T3 = b->right;

		//rotate
		b->right = c;
		c->left = T3;

		// update height
		c->height = findHeight(c);
		b->height = findHeight(b);
		

		return b;
	}


void map_insert(T k,U value)
{
    root=insert_dup(root, k, value);
    root->height=max(findHeight(root->left),findHeight(root->left))+1;
}


mapNode<T,U>* findHelper(mapNode<T,U> *top ,T k)
{
    if(top==NULL)
        return NULL;
    else if(top->key==k)
        return top;
    else
    {
        mapNode<T,U>* ret;
      if(ret=findHelper(top->left,k))
        return ret;
      else if( ret=findHelper(top->right,k))
        return ret;
      else
        return NULL;
      
       

    } 

} 


bool find(T k)
{
    if(root==NULL)
        return false;
    else
    {
        if(findHelper(root,k))
            return true;
        else
            return false;
        
    }
    
}


mapNode<T,U>* inorderSuccessor(mapNode<T,U>* root){
		mapNode<T,U>* successor = root;

		while(successor->left != NULL){
			successor = successor->left;
		}
		return successor;
	}


mapNode<T,U>* delete_dup(mapNode<T,U>* root, T value,bool flag){
		// cout<<"  IN "<<endl;
		// Node<T>* tmp;
		if(root == NULL){
			return NULL;
		}else if(value == root->key){
			
			//1.
			 if(root->left == NULL && root->right == NULL){
				delete root;
				mapNodeCount--;
				root = NULL;
			}

			//2.
			else if(root->left != NULL && root->right == NULL){
				mapNode<T,U>* leftChild = root->left;
				delete root;
				mapNodeCount--;
				root = leftChild;
			}
			else if(root->right != NULL && root->left == NULL){
				mapNode<T,U>* rightChild = root->right;
				delete root;
                mapNodeCount--;
				root = rightChild;
			}

			//3. 
			else if(root->left != NULL && root->right != NULL){
				
				mapNode<T,U>* succ= inorderSuccessor(root->right);
				root->key = succ->key;
			

				root->right = delete_dup(root->right,succ->key,true);
				// root->height = findHeight
			}

			// root->height = findHeight(root);
			// root->bal_fact = findBalancingFactor(root);


		}else if(value <  root->key){
			root->left = delete_dup(root->left,value,flag);
		}else{
			root->right = delete_dup(root->right,value,flag);
		}

		if(root == NULL){
			return NULL;
		}

		root->height = findHeight(root);
		int f=findHeight(root->left)-findHeight(root->right);

		// LL case
		if(f > 1 && findBalancingFactor(root->left) >= 0){
			return rightRotate(root);
		}

		// RR case
		if(f < -1 && findBalancingFactor(root->right) <= 0){
			return leftRotate(root);
		}

		// LR case
		if(f > 1 && findBalancingFactor(root->left) < 0){
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}

		// RL case
		if(f < -1 && findBalancingFactor(root->right) > 0 ){
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}

	

		return root;


	}


mapNode<T,U>* insert_dup(mapNode<T,U> *root, T item,U second){

		if(root == NULL){
			mapNode<T,U> *node = new mapNode<T,U>(item,second);
            mapNodeCount++;
			return node;
            
		}

		//duplicates allowed // balancing factor not disturbed
		if(item== root->key)
			(*this)[item]=second;
		else if(item > root->key){
			root->right = insert_dup(root->right,item,second);
		}else if(item < root->key){
			root->left = insert_dup(root->left, item,second);
		}

		root->height = findHeight(root);
		
        int f=findHeight(root->left)-findHeight(root->right);
		// LL case
		if(f > 1 && item < root->left->key){
			return rightRotate(root);
		}

		// RR case
		if(f < -1 && item > root->right->key){
			return leftRotate(root);
		}

		// LR case
		if(f > 1 && item > root->left->key){
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}

		// RL case
		if(f < -1 && item < root->right->key )
        {
			root->right = rightRotate(root->right);
			return leftRotate(root);
		}
		// if(bal_fact < 1 || bal_fact > 1){
		// 	selfBalance(root);
		// }

		return root;
	}


void erase(T k)
{
    if(root==NULL) return;
    root=delete_dup(root,k,false);
    if(root != NULL){
    	root->height=max(findHeight(root->left),findHeight(root->left))+1;
    }
    

}


int size(){
    return mapNodeCount;
}
 

void clear()
{
	mapNodeCount = 0;
    if(root=NULL)
        cout<<"Map Empty!"<<endl;
    else
    {
        root=clear_helper(root);
    }
    
    
}


mapNode<T,U>* clear_helper(mapNode<T,U>* r)
{
    if(r==NULL)
        return NULL;
    else if(r->left==NULL and r->right==NULL)
    {
        delete r;
        return NULL;
    }
    else 
    {
        if(r->left)
            clear_helper(r->left);
        if(r->right)
            clear_helper(r->right);
        delete(r);
        return NULL;
    }


}

};

int main()
{

	OrderedMap<int,int>* mymap = new OrderedMap<int,int>();
	mymap->map_insert(1, 10);
	mymap->map_insert(2, 20);
	mymap->map_insert(3, 30);
	(*mymap)[4] = 25;

	//mymap->print();

	cout<<mymap->size()<<endl;
	mymap->erase(2);
	cout<<mymap->find(2)<<endl;
	mymap->size();
	cout<<mymap->find(3)<<endl;
	(*mymap)[1] = 100;
	(*mymap)[4] = 50;

	//mymap->print();

	mymap->clear();
	cout<<mymap->size()<<endl;
	

 //    OrderedMap<string,int>* o= new OrderedMap<string,int>();
	//    o->map_insert("Zac",49);
 //    o->map_insert("Tiya",29);
 //    o->map_insert("Zac",13);
	// cout<<o->size()<<endl;
 //    cout<<(*o)["Tiya"]<<endl;
	//  o->erase("Tiya");
	//  cout<<o->size()<<endl;
   
 //       cout<<(*o)["Zac"]<<endl;

    return 0;
}