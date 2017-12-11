#include <bits/stdc++.h>
using namespace std;
void setup_env(){
    ios_base::sync_with_stdio(false);
    srand( time(NULL) );
}

struct node{
	int state[3][3];
	node* parent;
	int f;
	int g;
	int h;
	string stringvalue;
};

int goalState[3][3] = {{1,2,3},{4,5,6},{7,8,0}};
int opened,explored;
vector<string> alreadyVisited,alreadyExplored;
map<string,int> getValVisited,getValExplored;
node* initialState;

void printState(node* current){
	cout<<endl;
	cout<<current->f<<endl;
	for(int i=0;i<3;++i){
		for(int j=0;j<3;++j){
			cout<<current->state[i][j]<<" ";
		}
		cout<<endl;
	}
}


void printSolution(node* currentState){
	node* tempState= currentState;
	while(tempState){
		for(int i=0;i<3;++i){
			for(int j=0;j<3;++j){
				cout<<tempState->state[i][j]<<" ";
			}
			cout<<endl;
		}
		cout<<endl;
		tempState = tempState->parent;
	}
}


void epilogue(){
	cout<<"Sorry Given Configuration can not reach the Goal :(";
}


int heauristic(int currentState[3][3]){
	int manhattenDistance=0,hammingDistance=0;
	for(int i=0;i<3;++i){
		for(int j=0;j<3;++j){
			if(currentState[i][j] && currentState[i][j]!=goalState[i][j]){
				hammingDistance++;
				manhattenDistance+=abs(i-((currentState[i][j]-1)%3)) + abs(j-((currentState[i][j]-1)/3));
			}
		}
	}
	return max(manhattenDistance,hammingDistance);
}


void convertToString(node* currentState){
	string s="";
	for(int i=0;i<3;++i){
		for(int j=0;j<3;++j){
			s+=to_string(currentState->state[i][j]);
		}
	}
	currentState->stringvalue = s;
}


node* make_node(node* currentState,int m1,int n1,int m2,int n2){
	node* n = new node;
	for(int i=0;i<3;++i){
		for(int j=0;j<3;++j){
			n->state[i][j] = currentState->state[i][j];
		}
	}
	int temp = n->state[m1][n1];
	n->state[m1][n1] = n->state[m2][n2];
	n->state[m2][n2] = temp;
	n->parent = currentState;
	n->g = currentState->g + 1;
	n->h = heauristic(n->state);
	n->f = n->g + n->h;
	return n;
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


struct compare{
	bool operator()(node* x,node* y){
		return x->f>y->f;
	}	
};


bool isInExploredList(node* currentState){
	auto it = find(alreadyExplored.begin(),alreadyExplored.end(),currentState->stringvalue);
	if(it==alreadyExplored.end() || currentState->f<getValExplored[(*it)]) return false;
	return true;
}


bool isInVisitedList(node* currentState){
	auto it = find(alreadyVisited.begin(),alreadyVisited.end(),currentState->stringvalue);
	if(it==alreadyVisited.end() || currentState->f<getValVisited[(*it)]) return false;
	return true;
}


bool a_Star(){
	priority_queue<node*,vector<node*>,compare> openList;
	openList.push(initialState);
	while(!openList.empty()){
		node* currentState = openList.top();
		printState(currentState);
		openList.pop();
		if(isGoalState(currentState->state)){
			cout<<endl<<endl;
			printSolution(currentState);
			return true;
		}
		explored++;
		pair<int,int> blank = findBlank(currentState->state);
		int m = blank.first, n = blank.second;
		if(m+1<3){
			opened++;
			node* temp = make_node(currentState,m,n,m+1,n);
			convertToString(temp);
			if(!isInVisitedList(temp) && !isInExploredList(temp))
			openList.push(temp),alreadyVisited.push_back(temp->stringvalue),getValVisited[temp->stringvalue] = temp->f;
		}
		if(m-1>=0){
			opened++;
			node* temp = make_node(currentState,m,n,m-1,n);
			convertToString(temp);
			if(!isInVisitedList(temp) && !isInExploredList(temp))
			openList.push(temp),alreadyVisited.push_back(temp->stringvalue),getValVisited[temp->stringvalue] = temp->f;
		}
		if(n+1<3){
			opened++;
			node* temp = make_node(currentState,m,n,m,n+1);
			convertToString(temp);
			if(!isInVisitedList(temp) && !isInExploredList(temp))
			openList.push(temp),alreadyVisited.push_back(temp->stringvalue),getValVisited[temp->stringvalue] = temp->f;
		}
		if(n-1>=0){
			opened++;
			node* temp = make_node(currentState,m,n,m,n-1);
			convertToString(temp);
			if(!isInVisitedList(temp) && !isInExploredList(temp))
			openList.push(temp),alreadyVisited.push_back(temp->stringvalue),getValVisited[temp->stringvalue] = temp->f;
		}
		alreadyExplored.push_back(currentState->stringvalue);
		getValExplored[currentState->stringvalue] = currentState->f;
	}
	return false;
}


void solve(){
	if(a_Star()){
		cout<<"Number of states explored to reach goal state : "<<explored<<endl;
		cout<<"Number of states visited to reach goal state  : "<<alreadyVisited.size()<<endl;
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


node* userDefinedInitial(){
	cout<<"Enter Initial State: \n";
	node* n = new node;
	opened = explored = 0;
	for(int i=0;i<3;++i){
		for(int j=0;j<3;++j){
			cin>>n->state[i][j];
		}
	}
	n->g=0;
	n->h=heauristic(n->state);
	n->f = n->g + n->h;
	n->parent = NULL;
	convertToString(n);
	getValVisited[n->stringvalue]=n->f;
	alreadyVisited.push_back(n->stringvalue);
	return n;
}


bool prologue(){
	initialState = userDefinedInitial();
	if(!isSolvable((int *)(initialState->state))){
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

