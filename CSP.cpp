#include<bits/stdc++.h>
using namespace std;

vector< vector<bool> > Graph = {
	{0,1,1,0,0,0,0},
	{1,0,1,1,0,0,0},
	{1,1,0,1,1,1,1},
	{0,1,1,0,1,0,0},
	{0,0,1,1,0,1,0},
	{0,0,1,0,1,0,1},
	{0,0,1,0,0,1,0}
};

int Color_Count = 3;
vector<int> Constrained = {2,3,5,3,3,3,1};
int Variables = 7;


void Print_Assigned_Color(int Assigned_Color[]){
	for(int i=0;i<Variables;++i){
		cout<<Assigned_Color[i]<<"  ";
	}
}


bool is_Complete_Assignment(int Assigned_Color[]){
	return (count(Assigned_Color,Assigned_Color+Variables,-1))==0;
}


bool Forward_Check(bool Domain[][3],int Assigned_Color[],int Current_Vertex,int Check_Color,vector<int> &Changed){
	for(int i=0;i<Variables;++i){
		if(Assigned_Color[i] == -1 && Graph[i][Current_Vertex]){
			int temp = Domain[i][Check_Color];
			Domain[i][Check_Color]=0;
			if(temp!=0) Changed.push_back(i);
			int cnt=0;
			for(int j=0;j<Color_Count;++j){
				if(Domain[i][j]==1) cnt++;
			}
			if(cnt==0){
				Domain[i][Check_Color] = temp;
				return false;
			}	
		}
	}
	return true;
}


void Reverse_Change(bool Domain[][3],int Current_Vertex,int Check_Color,vector<int> &Changed){
	for(auto i=Changed.begin();i!=Changed.end();++i){
		Domain[*i][Check_Color]=1;
	}	
}


vector<int> Least_Constraint_Value(bool Domain[][3],int Assigned_Color[],int Current_Vertex){
	vector< pair<int,int> > temp;
	for(int i=0;i<Color_Count;++i){
		if(Domain[Current_Vertex][i]){
			int sum=0;
			for(int j=0;j<Variables;++j){
				if(Graph[Current_Vertex][j] && Assigned_Color[j]==-1){
					if(Domain[j][i]){
						Domain[j][i]=0;
						int cnt = 0;
						for(int k=0;k<Color_Count;++k){
							if(Domain[j][k]) cnt++;
						}
						Domain[j][i]=1;				
						if(cnt==0){
							sum=0;
							break;
						}
						sum+=cnt;
					}	
				}
			}
			temp.push_back(make_pair(sum,i));
		}
	}
	sort(temp.begin(),temp.end());
	vector<int> temp1;
	for(auto i=temp.begin();i!=temp.end();++i){
		temp1.push_back((*i).second);
	}
	return temp1;	
}


int Minimum_Remaining_Value(bool Domain[][3],int Assigned_Color[]){
	int val=-1,Maxcnt=Color_Count+1;
	for(int i=0;i<Variables;++i){
		if(Assigned_Color[i]==-1){
			int cnt=0;
			for(int j=0;j<Color_Count;++j){
				if(Domain[i][j]){
					cnt++;
				}
			}
			if(cnt<Maxcnt){
				Maxcnt = cnt;
				val=i;
			}
			else if(cnt==Maxcnt){
				if(Constrained[val]<Constrained[i]){
					val = i;
					Maxcnt=cnt;
				}
			}	
		}
	}	
	return val;
}


bool is_Graph_Colored(bool Domain[][3],int Assigned_Color[]){
	if(is_Complete_Assignment(Assigned_Color)){
		return true;
	}	
	else{
		int Current_Vertex = Minimum_Remaining_Value(Domain,Assigned_Color);
		vector<int> Least_Constraint_Color = Least_Constraint_Value(Domain,Assigned_Color,Current_Vertex);
		for(auto i=Least_Constraint_Color.begin();i!=Least_Constraint_Color.end();++i){
			Assigned_Color[Current_Vertex] = *i;
			vector<int> Changed;
			Changed.clear();
			if(Forward_Check(Domain,Assigned_Color,Current_Vertex,*i,Changed)){
			 	if(is_Graph_Colored(Domain,Assigned_Color)){
					return true;
				}
				else{
					Assigned_Color[Current_Vertex]=-1;
					Reverse_Change(Domain,Current_Vertex,*i,Changed);
				}
			}
			else{
				Assigned_Color[Current_Vertex]=-1;	
			}
		}
		return false;
	}
	return false;
}



void solve(){
	int Assigned_Color[7];
	bool Domain[7][3]; 
	for(int i=0;i<7;++i){
		for(int j=0;j<3;j++){
			Domain[i][j]=1;
		}
		Assigned_Color[i]=-1;
	}
	if(is_Graph_Colored(Domain,Assigned_Color)){
		Print_Assigned_Color(Assigned_Color);
	}
	else{
		cout<<"Given graph can not be colored with "<<Color_Count<<" colors"<<endl;
	}
	return;
}


int main(){
	solve();
}

