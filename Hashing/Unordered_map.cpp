#include<iostream>
#include<sstream>
#include<string>

using namespace std;
#define ut unsigned int
ut tableSize = 23;

template<class T1,class T2>
class UnorderedMap{
	// template<class T2>

	template<class U,class T>
	struct Node{
		U key;
		T value;


		struct Node<U,T>* next;
		
		Node(U k, T v){
			key = k;
			value = v;
			next = NULL;

		}

	};


	float threshold = 0.85; // if load factor goes beyond this -- rehash
	ut currCount;
 	ut p = 17; // close to 2^4
	Node<T1,T2>** addressTable = new Node<T1,T2>*[tableSize];


	// string convertToString(T1 key){

	// 	// if string return as it is // use typeid

	// }

	void rehash(){
		// double table size and reshash
		ut initSize = tableSize;
		tableSize = tableSize * 2;
		currCount = 0;

		Node<T1,T2>** table = addressTable;
		addressTable = new Node<T1,T2>*[tableSize];

		for(int i = 0;i < tableSize;i++){
			addressTable[i] = NULL;
		}

		for(int i = 0;i < initSize;i++){
			Node<T1,T2>* tmp = table[i];
			while(tmp != NULL){
				insert(tmp->key,tmp->value);
				tmp = tmp->next;
			}

		}
	}

	ut hashCode(T1 key){


	std::ostringstream strkey;
    strkey << key;
    string res = strkey.str();

		//write your own hash function
		
		int index = 0;
		// int index = 0;
		int prod = 1;

		for(int i =0;i<res.length();i++){
			index = ((index + res[i]*prod) % tableSize) % tableSize;
			prod = (prod*p) % tableSize;


		}
		return index;
	}

public:
	UnorderedMap(){
		currCount = 0;
		for(ut i =0;i<tableSize;i++){
			addressTable[i] = NULL;
		}
	}

	string find(T1 strkey){
		int index = hashCode(strkey);

		Node<T1,T2>* tmp = addressTable[index];
		if(tmp == NULL) return "False";

		while(tmp != NULL){
			if(tmp->key == strkey) return "True";
			tmp = tmp->next;
		}

		return "False";

	}

	Node<T1,T2>* find_dup(T1 strkey){
		int index = hashCode(strkey);

		Node<T1,T2>* tmp = addressTable[index];
		if(tmp == NULL) return NULL;

		while(tmp != NULL){
			if(tmp->key == strkey) return tmp;
			tmp = tmp->next;
		}

		return NULL;

	}

	void erase(T1 strKey){
		Node<T1,T2>* tmp = find_dup(strKey);
		int index;
		// no key found
		if(tmp == NULL) return;
		else index = hashCode(strKey);
		Node<T1,T2>* prev = NULL;
		Node<T1,T2>* fwd = addressTable[index];
		while(fwd != NULL){
			if(fwd->key == strKey){
				if(prev == NULL){
					addressTable[index] = fwd->next;
					delete fwd;
					fwd = NULL;
					currCount--;
					return;
				}else{
					prev->next = fwd->next;
					delete fwd;
					fwd = NULL;
					currCount--;
					return;
				}
				
			}
			prev = fwd;
			fwd = fwd->next;
		}
	}

	// overload subscript operator
	T2 operator[](T1 strkey){
		Node<T1,T2>* tmp = find_dup(strkey);
		// assert(tmp == NULL && "Key now presnt");
		// if(tmp == NULL){
		// 	cout<<"not present"<<endl;
		// }else{
		// 	return tmp->value;
		// }

		if(tmp == NULL){
			cout<<"Invalid location !";
			exit(1);
		}

		return tmp->value;

	}



	void insert(T1 strKey, T2 value){
		// convert key to string
		// string strKey = convertToString(T1 key);
		if(find(strKey) == "False"){
			// insert into table
			// get hashCode
			ut index = hashCode(strKey);

			if(addressTable[index] == NULL){
				// create node
				addressTable[index] = new Node<T1,T2>(strKey,value);

			}else{
				// conflict --- resolution - chaining
				Node<T1,T2>* newNode = new Node<T1,T2>(strKey,value);
				Node<T1,T2>* tmp = addressTable[index];

				while(tmp->next != NULL){
					tmp = tmp->next;
				}

				tmp->next = newNode; 
			}
			currCount ++;
			 if((currCount/(tableSize*1.0)) > threshold){
			 //	cout<<"load factor inc "<<currCount/(tableSize*1.0)<<"  "<<currCount<<"  "<<(tableSize*1.0)<<endl;
			 	rehash();
			 }

		}
	}

	void display(){
		for(int i =0;i<tableSize;i++){
			Node<T1,T2>* index = addressTable[i];
			cout<<i<<" -->  ";
			while(index != NULL){
				cout<<" --> ";
				cout<<"( "<<index->key<<" , "<<index->value<<" )";
				index = index->next;
			}
			cout<<endl;
		}
	}


};

int main(int argc, char const *argv[])
{

	UnorderedMap<int,float> umap;
	for(int i =0;i<12;i++){
		// string str = "key first "+to_string(i);
		umap.insert(i,i);
	}

	for(int i =0;i<30;i++){
		// string str = "key second "+to_string(i);
		umap.insert(i,i);
	}
	// umap.insert("hello",5);
	// umap.insert("hello world",7);
	// umap.insert("yellow",100);
	// umap.insert("this is one line of key",13);
	// umap.insert("Jason",89);

	// for(int i =0;i<10;i++){
	// 	string str;
	// 	cin>>str;

	// 	float f;
	// 	cin>>f;

	// 	umap.insert(str,f);
	// }

	// umap.display();
	// cout<<umap.find("13.7")<<endl;
	// umap.erase("13.7");
	// umap.erase("key first 1");
	// umap.erase("key first 5");
	// umap.erase("key first 69");
	umap.display();
	cout<<" ---------- "<<endl;
	umap.erase(2);
	umap.erase(11);
	cout<<umap.find(6)<<endl;
	umap.display();

	// cout<<umap["Jason"]<<endl;
	
	return 0;
}