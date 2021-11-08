#include <iostream>
#include <vector>
#include<algorithm>
#include<cmath>
using namespace std;

vector<int> buildSuffixArray(string str){

	str += "$";
	int len = str.length();

	vector<int> indices(len,0);
	vector<int> equiClass(len);

	vector<pair<char,int>> res(len);
	

	for(int i=0;i<len;i++){
		res[i]=make_pair(str[i],i);
	}

	sort(res.begin(),res.end());

	// initial indices
	int i = 0;
	while(i<len){
		indices[i] = res[i].second;


		i++;
	}

	int cls = 0;
	
	equiClass[indices[0]] == cls;

	for(int i =1;i<len;i++){
		if(res[i].first ==res[i-1].first ){
			// equivalence class remains same
			// equiClass[indices[i]] = equiClass[indices[i-1]];
			equiClass[indices[i]] = cls;

		}else{
			cls++;
			equiClass[indices[i]] = cls;
		}
	}

	//equivalence classes for left and right part
	// cout<<" -- equival cls -- "<<endl;
	// for(auto it=equiClass.begin();it != equiClass.end();it++){
	// 	cout<<(*it)<<" ";
	// }
	// cout<<endl;

	// int mul = 0;

	int m =0;
	while((1<<m)<len){

		vector<pair<pair<int,int>,int>> resultant(len);

		for(int j =0;j<len;j++){
			pair<int,int> p = make_pair(equiClass[j],equiClass[j+(1<<m)%len]);
			resultant[j] = {p,j};


		}

		sort(resultant.begin(),resultant.end());

		for(int j =0;j<len;j++){
			indices[j] = resultant[j].second;

		}

		equiClass[indices[0]] = 0;

		for(int j=0;j<len;j++){
			if(resultant[j].first == resultant[j-1].first){
				equiClass[indices[j]] = equiClass[indices[j-1]];
  			}else{
  				equiClass[indices[j]] = equiClass[indices[j-1]] +1;
  			}
		}

		m++;
		// m = 1<<m;


	}

	// for(int k=0;k<len;k++){
	// 	cout<<indices[k]<<" "<<str.substr(indices[k],len-indices[k])<<endl;
	// }

	return indices;


}

string minLexicographicRotation(string str){
    string res = str + str;
    int n = res.size();

    int pos;
    vector<int> suffixArray = buildSuffixArray(res);

  for(int i=1;i<n/2;i++){
        // if(p[i] < min){
        //  min = p[i];
        // }
        if(suffixArray[i] >=0 && suffixArray[i] <= (n/2)){
            pos = suffixArray[i];
            break;
        }
    }


    

    string tmp = str.substr(pos,str.length()) + str.substr(0,pos);
    return tmp;
}

void kasaiAlgo(string str,vector<int> suffixArray,vector<int>&lcp){

	// cout<<" --suffix array--  "<<endl;
 //    for(auto x:suffixArray){
 //        cout<<x<<" ";
 //    }

 //    cout<<" ----  "<<endl;

	int len = suffixArray.end() - suffixArray.begin();
	vector<int> invsuffix(len,0);

	for(int i =0;i<len;i++){
		invsuffix[suffixArray[i]] = i;

	}
	 // cout<<" --inverse array--  "<<endl;
  //   for(auto x:invsuffix){
  //       cout<<x<<" ";
  //   }

  //   cout<<" ----  "<<endl;

    int k =0;
    for(int i=0;i<len;i++){
    	if(invsuffix[i] == len -1){
    		k =0;
    		continue;

    	}

    	int j = suffixArray[invsuffix[i]+1];
    	while((i+k <len) && (j+k<len) && str[i+k]==str[j+k]){
    		k++;
    	}

    	lcp[invsuffix[i]] = k;

    	if(k > 0){
    		k--;
    	}



    }



}

void buildlcp(string str,vector<int>&lcpArray){
    vector<int> suffixArray = buildSuffixArray(str);
    // suffixArray.erase(suffixArray.begin());
    // vector<int> lcpArray(str.length(),0);
    kasaiAlgo(str,suffixArray,lcpArray);
    // cout<<" --------- "<<endl;
    // for(auto x:lcpArray){
    //     cout<<x<<" ";
    // }
    // cout<<" --------- "<<endl;

}

int longestCommonSuffix(string str,int k){

	int len = str.length();
	if(k == 1){
		return len;
	}

	vector<int> lcp(str.length(),0);
	buildlcp(str,lcp); // create lcp array


	// cout<<" -- check "<<endl;
	int left=1;
	int right = str.length();

	int res = 0;
	while(left <= right){
		int mid = (left + right)/2;
		bool flag = false;
		int idx = -1;
		int c=0;
		idx++;

		while(idx<len){
			if(lcp[idx] >= mid){
				c++;
			}else{
				c=0;
			}

			if(c>= k-1){
				flag = true;
			}


			idx++;
		}

		if(flag){
			res = mid;
			left = mid + 1;
		}else{
			right = mid -1;
		}

		// while(idx<str.length()){
		// 	if(lcp[idx]>=mid){
		// 		c++;
		// 	}else{
		// 		c = 0;
		// 	}
		// 	if( c >= k-1){
		// 		res = mid;
		// 		left = mid + 1;
		// 		break;
		// 	}else{
		// 		right = mid -1;

		// 	}
		// }

	}
	return res;

}

int main(int argc, char const *argv[])
{
	string str;
	cin>>str;
	int k;
	cin>>k;

	// cout<<"--- lcp is "<<endl;
	cout<<longestCommonSuffix(str,k)<<endl;
	
	return 0;
}

