#include<bits/stdc++.h>
using namespace std;

// Generalized n_Queen problem, Populated column wise randomely.
// population is constant in each generation
// parents are chosen accourding to there probablity of fitness in fitness array
// mutation happens for each children because the probability of occurance of same position and same value is also same
// there is two inputs : Number of queens(Board size) and Initial_Population(new this much amount of childrens are created)



int solution=0;
int queens,population_size;
vector< vector<int> > initial_population(4,vector<int>(8)),crossover(4,vector<int>(8));
vector<int> probability(112);//28*4
vector<int> fitness_values(4);
int count1=0;
int max_fit;




int fitness(vector<int> arr){
	int i,j,count=0;
	for(i=0;i<queens;i++){
		for(j=i+1;j<queens;j++){
			if(arr[i]==arr[j] || ((j-i) == abs(arr[j]-arr[i]))){
				count++;
			}
		}
	}
	return max_fit-count;
}

void Initial_Population(){
	for(int i=0;i<population_size;i++){
		for(int j=0;j<queens;j++){
			initial_population[i][j]= 1 + (rand() % queens);
		}
	}
}

void Populatate_New_Generation(){
	for(int i=0;i<population_size;i++){
		for(int j=0;j<queens;j++){
			initial_population[i][j]=crossover[i][j];
		}
	}
}

void Mutation(){
	for(int i=0;i<population_size;i++){
		int mutation_point =  rand()%queens;
		int new_val= 1 + (rand() % queens);
		crossover[i][mutation_point]=new_val;
	}
}

void Crossover(int k){
	for(int i=0;i<(population_size/2);i++){
		int member1[queens],member2[queens];
		int random=probability[rand()%k];
		for(int j=0;j<queens;j++){
			member1[j]=initial_population[random][j];	
		}
		random=probability[rand()%k];
		for(int j=0;j<queens;j++){
			member2[j]=initial_population[random][j];	
		}
		int partition = 1 + (rand() % queens);
		for(int j=0;j<partition;j++){
			crossover[2*i][j]=member1[j];
			crossover[2*i+1][j]=member2[j];
		}
		for(int j=partition;j<queens;j++){
			crossover[2*i][j]=member2[j];
			crossover[2*i+1][j]=member1[j];
		}
	}
}

void print(int i){
	cout<<endl;
	solution++;
	for(int k=0;k<queens;++k){
		cout<<"--";
	}
	cout<<endl;
	cout<<"Number of Generations: "<<count1<<endl;
	for(int j=0;j<queens;j++){
		printf("%d ",initial_population[i][j]);
	}
	cout<<endl<<endl;
	for(int k=1;k<=queens;k++){
		for(int l=0;l<queens;l++){
			if(initial_population[i][l]==k){
				cout<<"Q ";
			}
			else{
				cout<<"_ ";
			}
		}
		cout<<endl;
	}
	cout<<endl;
	for(int k=0;k<queens;++k){
		cout<<"--";
	}
	cout<<endl<<endl;
}


int main(){
	srand(time(NULL));
	cout<<"Enter Number of Queens: ";cin>>queens;
	cout<<"Enter Initial Population Size: ";cin>>population_size;
	if(queens<=2 || population_size==1){
		cout<<"Impossible to populate ";
		return 0;
	}
	max_fit = (queens*(queens-1))/2;
	
	initial_population.resize(population_size,vector<int>(queens));
	crossover.resize(population_size,vector<int>(queens));
	fitness_values.resize(population_size+1);
	probability.resize(max_fit*population_size+1);

	
	Initial_Population();
	bool done=false;
//	int maximum_iterations=1000000;
	
	while(!done){
		count1++;
		int k=0;
		for(int i=0;i<population_size;i++){
			fitness_values[i]=fitness(initial_population[i]);
			for(int j=0;j<fitness_values[i];j++){
				probability[k]=i;
				k++;
			}
		}
		for(int i=0;i<population_size;i++){
			if(fitness_values[i]==max_fit){
				done=true;
				print(i);							
				return 0;									// if you want only one output remove comment
			}
		}
		Crossover(k);
		Mutation();
		Populatate_New_Generation();
   }
//   cout<<"\nNumber of solutions in "<<maximum_iterations<<" Generations are: "<<solution<<endl<<endl;
   return 0;
}
