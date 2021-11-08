#include<iostream>
#include<string>
using namespace std;

int multiply_fact(int* arr, int n, int pos ){

	int carry = 0;
	int cum;

	for(int i=0;i<pos;i++){
		cum = arr[i]*n + carry;
		arr[i] = cum%10;
		carry = cum/10;
	}

	while(carry){
		arr[pos] = carry%10;
		carry = carry/10;
		pos++;
	}
	return pos;
}

void fact(int no){
	if(no == 1 || no == 0) {
		cout<<1<<endl;
		return;
	} 
	
	int *arr{ new int[3005]{0} }; 

	// for(int i =0;i<3005;i++ ){
	// 	cout<<arr[i]<<" "<<endl;
	// }
	int pos=0;
	arr[pos]=1;
	pos++;

	for(int i =2;i<=no;i++){
		pos = multiply_fact(arr,i,pos);
	}

	for(int i =pos-1;i>=0;i--){
		cout<<arr[i];
	}
	cout<<endl;
}

string multiply(string s1, string s2){
	//cout<<"1 -> ";
	//string res="";
	int carry = 0;
	int count = 0;
	int s1_len = s1.length();
	int s2_len = s2.length();
	//string res = "";
	string res(s1_len+s2_len+1,'0');
	for(int i = s1_len-1;i>=0;i--){
		//cout<<"2 -> ";
		carry = 0;
		int curr_i = s1[i]-'0';                            ;
		//count = 0;
		//int mul = 1;
		//string curr_res="";
		int pos = count;

		for(int j=s2_len-1;j>=0;j--){
			//cout<<"3 -> ";
			int curr_j = s2[j]-'0';
			curr_j = curr_j*curr_i+carry;

			curr_j = (res[pos]-'0')+curr_j;

			carry = curr_j/10;
			//cout<<"carry "<<carry<<endl;
			curr_j = curr_j%10;
			res[pos] = curr_j + '0';
			pos++;
		
			
		}
		//cout<<"4 -> "<<res<<endl;
		if(carry > 0){
			res[pos] = (carry+'0') ;
		}

		//cout<<"4 -> iteration "<<res<<endl;
		// int c = count;


		// while(c--){
		// 	res = "0" + res;
		// }
	

	
		//cout<<"6 -> ";

		count++;
	}
		int res_len = res.length();

		int k = res_len-1;  //2,1
		while(res[k]=='0' && k>0){
			k--;   
		}
	//	cout<<" *** "<<res<<endl;

		if(k != res_len-1){
			//cout<<"5 -> ";
			res.erase(k+1,res_len);
		}

	int left = 0;
	int right = res.length()-1;
	while(left < right){
		char tmp = res[left];
		res[left]=res[right];
		res[right]=tmp;
		left++;
		right--;
	}
	//reverse(res.begin(),res.end());
	return res;
}

string fast_exponentiation(string str, int n){

	string res = "1";
	while(n > 0){
		if(n%2 != 0){
			if(res == "1"){
				res = str;
			}else{
				res = multiply(res,str);
			}
			
			n = n-1;
		}
		str = multiply(str,str);
		n =n/2;

	}
	return res;
}

 string sub(string s1, string s2){  //13,4
 	int ns1 = s1.length();
 	int ns2 = s2.length();

 	int borrow = 0;

 	int i = ns1 - 1;
 	int j = ns2 - 1;
 	string res(ns1,'0');

 	int curr_i,curr_j;
 	int k = 0;
 	while(j >= 0){
 		curr_i = s1[i] - '0';
 		curr_j = s2[j] - '0';

 		if(borrow){
 			curr_i -=1;
 			borrow = 0;
 		}
 		if(curr_i < curr_j){
 			borrow = 1;
 			curr_i = curr_i + 10;
 			curr_j = curr_i - curr_j;
 		}else{
 			curr_j = curr_i - curr_j;
 		}

 		res[k] = curr_j + '0';


 		k++;
 		i--;
 		j--;
 	}

 	while( i >= 0){
 		curr_i = s1[i] - '0';
 		if(borrow){
 			if(i == 0){
 				curr_i -= 1;
 				if(curr_i == 0){
 					break;
 				}
 			}else{
 				curr_i -= 1;
 				borrow = 0;
 			}
 			
 		}
 		if(curr_i == 0){
 			borrow = 1;
 			res[k] = '9';
 		}else{
 			res[k] = curr_i + '0';
 		}
 		
 		k++;
 		i--;
 	}

 	int res_len = res.length();

	int p = res_len-1;

	while(res[p]=='0' && p>0){
			p--;   
	}

	if(p != res_len-1){
			//cout<<"5 -> ";
			res.erase(p+1,res_len);
	}
	int left = 0;
	int right = res.length()-1;
	while(left < right){
		char tmp = res[left];
		res[left]=res[right];
		res[right]=tmp;
		left++;
		right--;
	}

 	return res;
 }

 bool smaller(string a, string b){
 	if(a.length() > b.length()){
 		return false;
 	}
 	if(b.length() > a.length()){
 		return true;
 	}

 	// both a and b are of equal length // compare each and every digit 
 	//int curr_a,curr_b;
 	for(int i=0;i<a.length();i++){
 		if(a[i] < b[i]){
 			return true;
 		}

 		if(a[i] > b[i]){
 			return false; 
 		}
 	
 	}
 	return false;
 }


string gcd(string a,string b){
	//int count = 0;
	// assume a is always greater than b
	while((a != b) && ( b != "1") ){
	
		if(smaller(a,b)){ // if a < b
			string t = a;
			a = b;
			b = t;
		
		}
		string tmp = sub(a,b);
		a = b;
		b = tmp;
		if(a == b) return b;
		//count++;
	}

	return b;
}

int main(int argc, char const *argv[])
{
	int Q;
	cin>>Q;

	while(Q--){
		int t;
		cin>>t;
		switch(t){
			case 1:{
					string str;
					int n;
					cin>>str;
					cin>>n;
					//cout<<str<<" ** "<<n<<endl;
					cout<<fast_exponentiation(str,n)<<endl;
					break;
					
					}
			case 2:{string s1;
					string s2;
					cin>>s1>>s2;
					
					cout<<gcd(s1,s2)<<endl;
					
					break;
					}
			case 3:{					
					int n;
					cin>>n;
					fact(n);
					break;
					}
			default:{

			}
		}
	}
	return 0;
}