#include <bits/stdc++.h>
using namespace std;
void setup_env() {
    ios_base::sync_with_stdio(false);
    srand( time(NULL) );
}
int initialState[3][3],goalState[3][3] = {{1,2,3},{4,5,6},{7,8,0}};
pair<int,int> initialBlank;
int iterations1;



void GenerateInitial(){
	vector<int> excluded;
	bool done=0;
	int temp;
	for(int i=0;i<3;++i){
		for(int j=0;j<3;++j){
			done=0;
			do{
				temp = rand()%9;
				if(find(excluded.begin(),excluded.end(),temp)==excluded.end()){
					if(temp==0){
						initialBlank = make_pair(i,j);
					}
					done = 1;
					excluded.push_back(temp);
					initialState[i][j]=temp;
				}	
			}while(!done);
		}
	}	
} 


void printState(int tempState[3][3]){
	for(int j=0;j<3;++j){
		for(int k=0;k<3;++k){
			cout<<tempState[j][k]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}


void epilogue(){
	cout<<"Sorry Given Configuration can not reach the Goal :(";
}


bool isGoalState(int currentState[3][3]){
	for(int i=0;i<3;++i){
		for(int j=0;j<3;++j){
			if(currentState[i][j]!=goalState[i][j]){
				return false;
			}
		}
	}
	return true;
}


pair<int,int> findBlank(int currentState[3][3]){
	for(int i=0;i<3;++i){
		for(int j=0;j<3;++j){
			if(currentState[i][j]==0){
				return make_pair(i,j);
			}
		}
	}
}


void swap(int currentState[3][3],int i,int j,int m,int n){
	int temp = currentState[i][j];
	currentState[i][j] = currentState[m][n];
	currentState[m][n] = temp;
}


bool DLS(int depth,int currentState[3][3],int *iterations){
	if(isGoalState(currentState)){
		printState(currentState);
		return true;
	}
	if(depth>0){
		pair<int,int> blankPos = findBlank(currentState);
		int m = blankPos.first,n = blankPos.second;
		if(m+1<3){
			(*iterations)++;
			swap(currentState,m,n,m+1,n);
			if(DLS(depth-1,currentState,iterations)){
				swap(currentState,m,n,m+1,n);
				printState(currentState);
				return true;
			} 
			else{
				swap(currentState,m,n,m+1,n);
			}
		}
		if(m-1>=0){
			(*iterations)++;
			swap(currentState,m,n,m-1,n);
			if(DLS(depth-1,currentState,iterations)){
				swap(currentState,m,n,m-1,n);
				printState(currentState);
				return true;
			} 
			else{
				swap(currentState,m,n,m-1,n);
			}
		}
		if(n+1<3){
			(*iterations)++;
			swap(currentState,m,n,m,n+1);
			if(DLS(depth-1,currentState,iterations)){
				swap(currentState,m,n,m,n+1);
				printState(currentState);
				return true;
			} 
			else{
				swap(currentState,m,n,m,n+1);
			}
		}
		if(n-1>=0){
			(*iterations)++;
			swap(currentState,m,n,m,n-1);
			if(DLS(depth-1,currentState,iterations)){
				swap(currentState,m,n,m,n-1);
				printState(currentState);
				return true;
			} 
			else{
				swap(currentState,m,n,m,n-1);
			}
		}
	}
	return false;	
}


bool IDDFS(){
	int tempInitialState[3][3];
	//int initialState1[3][3]={{1,2,3},{7,4,5},{0,8,6}},initialState2[3][3]={{1,2,3},{0,7,6},{5,4,8}},initialstate3[3][3]={{1,2,3},{7,8,4},{0,5,6}};
	for(int depth=1;depth<50;++depth){
		int iterations=0;
		for(int i=0;i<3;++i){
			for(int j=0;j<3;++j){
				tempInitialState[i][j] = initialState[i][j];
			}
		}
		if(DLS(depth,tempInitialState,&iterations)){
			iterations1 = iterations;
			return true;
		}
	}
	return false;
}


void solve(){
	if(IDDFS()){
		cout<<"Number of states required to reach goal state : "<<iterations1<<endl;
	}
	else{
		cout<<"Solution not Found :("<<endl;
	}
}


bool isSolvable(int temp[]){
	int inversionCount=0;
	for(int i=0;i<8;++i){
		for(int j=i+1;j<9;++j){
			if(temp[i] && temp[j] && temp[i]>temp[j]){
				inversionCount++;
			}
		}
	}
	return (inversionCount%2==0);
}


void userDefinedInitial(){
	cout<<"Enter Initial State: \n";
	for(int i=0;i<3;++i){
		for(int j=0;j<3;++j){
			cin>>initialState[i][j];
		}
	}
	cout<<endl;
}


bool prologue(){
	//GenerateInitial();
	userDefinedInitial();
	if(!isSolvable((int *)initialState)){
		epilogue();
		return false;
	}	
	return true;
}


int main(){
	setup_env();
	if(prologue())
	solve();
}

