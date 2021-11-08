#include<iostream>
using namespace std;
//#define ut int

template<class T>
class deque{
private:
	
	int sizee;
	T* arr;
	int capacity;
	int frontt;
	int rear;
	
public:
	
	
	deque(){
		sizee = 0;
		capacity = 1;
		arr = new T[capacity];
		frontt = -1;
		rear = -1;
	}

	deque(int n, T x){
		sizee = n;
		capacity = n;
		arr = new T[capacity];
		for(int i =0;i<n;i++){
			arr[i]=x;
		}
		frontt = 0;
		rear = sizee-1;
	}

	~deque(){

	}

	string empty(){
		if(isEmpty()){
			return "true";
		}else{
			return "false";
		}
	}

	bool isEmpty(){
		return (sizee == 0);
	}

	void resize(int n){
		T* tmp = new T[n];
		int f = frontt;

		if(n < sizee){
			
			for(int i=0;i<n;i++){
				tmp[i]=arr[f];
				f=(f+1)%capacity;
			}
			arr=tmp;
			frontt = 0;
			rear = n-1;
			return;
		}
		
		//int r = rear;
		for(int i = 0;i<sizee;i++){
			tmp[i] = arr[f];
			f=(f+1)%capacity; 
		}
		capacity = n;
		//delete[] arr;
		arr = tmp;
		frontt = 0;
		rear = sizee-1;
	}

	void resize(int x,T d){
	
		if(x < sizee){
		
			resize(x);
			sizee = x;
			capacity=x;

			return;	
		}
		
		resize(x);
		for(int i =sizee;i<x;i++){
			arr[i]=d;
		}

		sizee = x;
		rear = sizee-1;
	}
	void push_front(T x){
		if(isEmpty()){
			rear = 0;
			frontt = 0;
			arr[frontt]=x;
			
		}else if((rear+1)%capacity == frontt){
			resize(capacity*2);
			frontt = (frontt + capacity - 1)%capacity;
			arr[frontt] = x;
		}else{
			frontt = (frontt + capacity  - 1)%capacity;
			arr[frontt] = x;
		}
		sizee++;
	}

	void push_back(T x){
		if(isEmpty()){
			rear = 0;
			frontt = 0;
			arr[rear]=x;
			//size++;
		}else if((rear + 1)%capacity == frontt){  // array full
			resize(capacity*2);
			rear = (rear + 1)%capacity;
			arr[rear] = x;
		}else{
			rear = (rear + 1)%capacity;
			arr[rear] = x;
		}
		sizee++;
	}

	int size(){
		return sizee;
	}

	void pop_front(){
		if(isEmpty()){
			return;
		}else if(sizee == 1){
			//front = (front+1)%capacity;
			sizee--;
			frontt = rear = -1;
		}else{
			frontt = (frontt+1) % capacity;
			sizee--;
		}
	}


	void pop_back(){
		if(isEmpty()){
			return;
		}else if(sizee == 1){
			sizee--;
			frontt = rear = -1;
		}else{
			rear = (rear + capacity  - 1)%capacity;
			sizee--;
		}

	}

	T front(){
		return arr[frontt];
	}
	T back(){
		return arr[rear];
	}

	void clear(){
		sizee = 0;
		capacity = 1;
		arr = new T[capacity];
		frontt = -1;
		rear = -1;
		
	}

	T operator[](T idx){
		if(idx >= sizee){
			//error condition here
			//return -1;
			cout<<"Invalid location";
		}
		idx = (idx % capacity);
		//int *p = &front;
		return arr[(frontt + idx)%capacity];
	}

	void traverse(){
		int f=front;
		
		for(int i =0;i<capacity;i++){
			cout<<arr[i]<<" -> ";
		}
		cout<<endl;
	}


	void display(){
		if(isEmpty()){
			return;
		}

		int f = frontt;
		int count = 0;
		cout<<arr[f];
		count++;
		f = (f+1)%capacity;

		while(count < sizee){
			cout<<" "<<arr[f];
			f = (f+1)%capacity;
			count++;
		}
		cout<<endl;

	}



};

int main(int argc, char const *argv[])
{
	deque<int> d;
	int q;
	cin>>q;

	while(q--){
		int t;
		//int x;
		cin>>t;
		switch(t){
			case 1:{
					int x;
					cin>>x;
					d.push_front(x);
					d.display();
					break;
					}
			case 2:{
					d.pop_front();
					d.display();
					break;
					}
			case 3:{
					int x;
					cin>>x;
					d.push_back(x);
					d.display();
					break;

					}
			case 4:{
					d.pop_back();
					d.display();
					break;
					}
			case 6:{
					int s;
					int x;
					cin>>s>>x;
					deque<int> d(s,x);
					d.display();
					break;
					}
			case 7:{
					cout<<d.front()<<endl;
					
					break;
					}
			case 8:{
					cout<<d.back()<<endl;
					
					break;
					}
			case 9:{
					cout<<d.empty();
					break;
					}	
			case 10:{
					cout<<d.size();
					break;
					}

			case 11:{
					int n,x;
					cin>>n>>x;
					d.resize(n,x);
					d.display();
					break;
					}
			case 12:{
					d.clear();
					d.display();
					break;
					}
			case 13:{
					int n;
					cin>>n;
					cout<<d[n]<<endl;
					break;
					}
			case 14:{
					d.display();
					break;
					}
			default:{

					}

		}
	}
	
	
	return 0;
}