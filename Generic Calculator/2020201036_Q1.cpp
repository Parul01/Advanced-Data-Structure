#include<iostream>
#include<string>
#include<iomanip>
//#include "LinkedList.h"
using namespace std;
template<class T>
class LinkedList{

	template<class T2>
	struct Node{
		T2 data;
		struct Node<T2>* next;
		Node(T2 d){
			data = d;
			next = NULL;
		}

	};

	Node<T>* head;
	Node<T>* tail;
	int size;


public:
		LinkedList(){
		head = NULL;
		tail = NULL;
		size = 0;
	}


	void traverse(){
		if(head == NULL){
			return;
		}

		Node<T>* tmp = head;
		while(tmp){
			//cout<<tmp->data;
			tmp = tmp->next;
		}

	}

	bool isEmpty(){
		return(size == 0);
	}

	void insert_at_start(T data){
		if(head == NULL){
			head = new Node<T>(data);
			size++;
			
			return;
		}

		Node<T> *tmp = new Node<T>(data);
		tmp->next = head;
		head = tmp;
		tmp = NULL;
		size++;

	}

	void delete_from_start(){
		if(head == NULL){
			return;
		}
		Node<T>* tmp = head;
		head = head->next;
		tmp->next = NULL;
		size--;
	}

	T get_first(){
		return (head->data);
	}


};


template<class S>
class stack{
	LinkedList<S> ll;
public:
	bool empty(){
		return ll.isEmpty();
	}
	void push(S data){
		ll.insert_at_start(data);
	}
	void pop(){
		ll.delete_from_start();
	}

	S top(){
		return ll.get_first();
	}
};

bool precedence(char c1, char c2){

	// c1 is top of stack
	// c2 is current operator in string
	int setprec1 = 0;
	int setprec2 = 0;

	if(c1 == '%' || c1 == '*' || c1 == '/'){
		setprec1 = 2;
	}else{
		setprec1 = 1;
	}


	if(c2 == '%' || c2 == '*' || c2 == '/'){
		setprec2 = 2;
	}else{
		setprec2 = 1;
	}

	if((setprec1 == setprec2) || (setprec1 > setprec2)){
		return true;
	}else{
		return false;
	}

}

int convertToPostfix(string str,string *s){
	stack<char> operator_st;
	//stack<char> operand_st;

	// string str;
	// cin>>str;
	// cout<<str<<endl;
	//string *s = new string[str.length()];
	string res = "";
	int k = 0;
	//int len = sizeof(str)/sizeof(string);
	for(int i=0;i<str.length();i++){
		if(res == "" && str[i] != '(' && str[i] != ')' && str[i] != '+' && str[i] != '-' && str[i] != '/' && str[i] != '*' && str[i] != '%'){
			res += str[i];
			
		}else if(str[i] != '(' && str[i] != ')' && str[i] != '+' && str[i] != '-' && str[i] != '/' && str[i] != '*' && str[i] != '%'){
			res += str[i];
			
		}else{
			if(res != ""){
				s[k]=res;
				k++;
				res = "";
			}
			if(operator_st.empty() || str[i] == '(' || operator_st.top() == '('){
				operator_st.push(str[i]);
			}else if(str[i] == operator_st.top()){
				s[k]= operator_st.top();
				k++;
				operator_st.pop();        //actually not required
				operator_st.push(str[i]);  //actually not required
			}else if(str[i] == ')'){
				while(operator_st.top() != '('){
					s[k] = operator_st.top();
					operator_st.pop();
					k++;
				}
				operator_st.pop();

			}else if(precedence(operator_st.top(), str[i])){
				while((!operator_st.empty()) && operator_st.top() != '(' && precedence(operator_st.top(), str[i])){
					s[k] = operator_st.top();
					k++;
					operator_st.pop();
					
				}
				operator_st.push(str[i]);
			
			}else{
				operator_st.push(str[i]);
			}


		}
	}

	if(res != ""){
		s[k] = res;
		k++;
	}

	while(!operator_st.empty()){
		s[k] = operator_st.top();
		operator_st.pop();
		k++;
	}

	return k;
}

double evaluate(string s){
	int n = s.length();

	string *str = new string[s.length()];

	int k = convertToPostfix(s,str);
	stack<double> st;

	for(int i =0;i<k;i++){
		if(str[i] == "+"){
			double d1 = st.top();
			st.pop();
			double d2 = st.top();
			st.pop();

			st.push(d2 + d1);
		}
		else if(str[i] == "-"){
			double d1 = st.top();
			st.pop();
			double d2 = st.top();
			st.pop();

			st.push(d2 - d1);
		}

		else if(str[i] == "/"){
			double d1 = st.top();
			st.pop();
			double d2 = st.top();
			st.pop();

			st.push(d2 / d1);
		}

		else if(str[i] == "*"){
			double d1 = st.top();
			st.pop();
			double d2 = st.top();
			st.pop();

			st.push(d2 * d1);
		}

		else if(str[i] == "%"){
			int d1 = (int)st.top();
			st.pop();
			int d2 = (int)st.top();
			st.pop();

			st.push(double(d2 % d1));
		}
		else{
			st.push(stod(str[i]));
		}
	}
	double res = st.top();
	return res;
}


int main(int argc, char const *argv[])
{
	string str;
	cin>>str;

	double ev = evaluate(str);
	cout<<ev<<endl;
	return 0;
}
