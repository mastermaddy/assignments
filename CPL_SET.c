#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 5


typedef struct nodet{
	int value;
	struct nodet* next;
}link;


typedef struct nodet1{
	int number_node;
	link* link; 
}set;


void Insert(set node1[],int value,int index)
{
	link* temp=(link*)malloc(sizeof(link));
	temp->next=NULL;
	link* l;
	
	if(node1[index].number_node==0)								// for 1st node of linked_list
	{
		node1[index].link = temp;
		node1[index].link->next = NULL;
		node1[index].link->value = value;
		node1[index].number_node++;
	}
	else 
	{
		l=node1[index].link;								
		while(l->next && l->value != value)						// inserting at end
		{
			l = l->next;	
		}
		if(l->value == value)									// for duplicate entry
		{
			printf("\n\t\t D U P L I C A T E  E N T R Y \n");
		}
		else
		{
			temp->value = value;								
			temp->next = NULL;	
			l->next = temp;
			node1[index].number_node++;	
		}
	}
}


void Delete(set node1[],int value,int index)
{
	link* prev,*temp;
	temp = node1[index].link;
	int flag=1;
	
	if(node1[index].number_node>0)									// if start of linked_list has to delete
	{
		if(temp->value==value)
		{	
			printf("\n\t\t O P E R A T I O N  S U C C E S S F U L ");
			node1[index].link = node1[index].link->next;
			free(temp);
			node1[index].number_node--;
		}
		else
		{
			while(temp->next!=NULL && flag)						// searching for the node to be delete
			{
				prev=temp;
				temp=temp->next;
				if(value == temp->value)
				{
					prev->next=temp->next;
					free(temp);
					flag=0;
					node1[index].number_node--;
				}	
			}
			if(flag)
			{
				printf("\n\t\t O P E R A T I O N  U N S U C C E S S F U L");
			}
			else
			{
				printf("\n\t\t O P E R A T I O N  S U C C E S S F U L ");
			}		
		}	
	}
	else
	printf("\n\t\t E N T R Y  N O T  F O U N D  :(");
}


void UnionSet(set union_set[],set node1[],int value,int index)
{	
	link* l = node1[index].link;
	if(node1[index].number_node>0)							
	{
		while(l && l->value != value)
		{
			l = l->next;	
		}
		if(l==NULL)
		{
			Insert(union_set,value,value%MAX_SIZE);		// if value not found then inserting value 
		}	
	}
	else
	{
		Insert(union_set,value,value%MAX_SIZE);		
	}		
}


link* Union(set union_set[],set node1[],set node2[])
{
	int i=0;
	link* l;
	
	for(i=0;i<MAX_SIZE;i++)
	{
		l=node1[i].link;
		while(l)
		{
			Insert(union_set,l->value,(l->value)%MAX_SIZE); // inserting whole set2 in union set
			l=l->next;
		}
	}
	for(i=0;i<MAX_SIZE;i++)
	{
		l=node2[i].link;
		while(l)
		{
			UnionSet(union_set,node1,l->value,(l->value)%MAX_SIZE); // checking each value of set1 in set2
			l=l->next;
		}
	}		
}


void Intersection(set intersection_set[],set node1[],int value,int index)
{
	link* l = node1[index].link;
	if(node1[index].number_node>0)
	{
		while(l && l->value != value)
		{
			l = l->next;	
		}
		if(l!=NULL && l->value==value)					// if value found then inserting in intersection set
		{
			Insert(intersection_set,value,value%MAX_SIZE);	
		}	
	}
}


void IntersectionSet(set intersection_set[],set node1[],set node2[])
{
	int i=0;
	link* l;
	
	for(i=0;i<MAX_SIZE;i++)
	{
		l=node2[i].link;
		while(l)
		{
			Intersection(intersection_set,node1,l->value,(l->value)%MAX_SIZE);			// searching a value from one set in 
			l=l->next;																	// another set
		}
	}	
}


void Difference(set difference_set[],set node2[],int value,int index )
{
	link* l = node2[index].link;
	if(node2[index].number_node>0)
	{
		while(l && l->value != value)
		{
			l = l->next;	
		}
		if(l==NULL)
		{
			Insert(difference_set,value,value%MAX_SIZE);		// if search not found then inserting value in difference set
		}	
	}
	else
	{
		Insert(difference_set,value,value%MAX_SIZE);	
	}
	
}


void DifferenceSet(set difference_set[],set node1[],set node2[])
{
	int i=0;
	link* l;
	
	for(i=0;i<MAX_SIZE;i++)										// taking one entry from 1st set and searching in 2nd set
	{
		l=node1[i].link;
		while(l)
		{
			Difference(difference_set,node2,l->value,(l->value)%MAX_SIZE);
			l=l->next;
		}
	}
}


void print(set node2[])
{
	int i=0;
	link* l;
	for(i=0;i<MAX_SIZE;i++)
	{
		l=node2[i].link;
		printf("\n\t\t %d.  ",i+1);
		while(l)
		{
			printf(" %d ",l->value);
			l=l->next;
		}
	}	
}


void Search(set node1[],int value,int index)
{
	link* l = node1[index].link;
	if(node1[index].number_node>0)
	{
		while(l && l->value != value)								// searching on the basis of value
		{
			l = l->next;	
		}
		if(l!=NULL && l->value==value)
		{
			printf("\n\t\t E N T R Y  F O U N D  :) ");	
		}
		if(l==NULL)
		{
			printf("\n\t\t E N T R Y  N O T  F O U N D  :(");
		}	
	}
	else
	{
		printf("\n\t\t E N T R Y  N O T  F O U N D  :(");
	}
	
	
}


void Initialize(set node1[])
{
	int i;													// making each value in array equals to zero
	for(i=0;i<MAX_SIZE;i++)									// and link = NULL
	{
		node1[i].number_node=0;
		node1[i].link=NULL;
	}
}


int main()
{
	set node1[MAX_SIZE],node2[MAX_SIZE];				 // node1 and node2 are set1 and set2 respectively
	set union_node[MAX_SIZE],intersection_node[MAX_SIZE]; 
	set difference1[MAX_SIZE],difference2[MAX_SIZE],symmetric[MAX_SIZE];
	int i=0,value,choice,set_no=1;
	char c,opt;
	
	Initialize(node1);
	Initialize(node2);
	Initialize(union_node);
	Initialize(intersection_node);
	Initialize(difference1);
	Initialize(difference2);
	Initialize(symmetric);
	
	
	while( 1 )
    {         			
		if( set_no == 1 )
		{
           	printf("\n\n\t\tY O U  H A V E  C U R R E N T L Y  S E L E C T E D  S E T  1\n\n");        	
		}
        else if( set_no == 2 )
        {     	
			printf("\n\n\t\tY O U  H A V E  C U R R E N T L Y  S E L E C T E D  S E T  2\n\n");	
		}
		while( 1 )
		{
			printf("\n\t\t浜様様様様様様様様様様様様様様様様様様様様様様様様様様様様融");
			printf("\n\t\t紺                                                        虻");   
			printf("\n\t\t紺                   SET IMPLEMENTATION                   虻");
        	printf("\n\t\t紺                                                        虻");
        	printf("\n\t\t藩様様様様様様様様様様様様様様様様様様様様様様様様様様様様夕");
			printf("\n\n********************************** M E N U *****************************************");
			printf("\n\t\t01. SELECTION OF SET");
			printf("\n\t\t02. TO INSERT");
			printf("\n\t\t03. TO DELETE");
			printf("\n\t\t04. UNION OF TWO SETS");
			printf("\n\t\t05. INTERSECTION OF TWO SETS");
			printf("\n\t\t06. DIFFRENCE OF TWO SETS (SET 1 - SET 2)"); 
			printf("\n\t\t07. SYMMETRIC DIFFERENCE OF TWO SETS");
			printf("\n\t\t08. TO DISPLAY CURRENT SET");
			printf("\n\t\t09. TO SEARCH FOR A VALUE");
			printf("\n**************************************************************************************");
		
			printf("\n\t\t P L E A S E  E N T E R  A  V A L I D  C H O I C E \n\n\t\t=> ");
		
			scanf("%d",&choice);
		
			getchar();
		
			switch( choice )
			{					
				case 1: printf("\n\n\t\tS E L E C T  T H E  S E T \n\n\t\t1) SET 1\n\n\t\t2) SET 2\n\n\t\t=> ");
						scanf("%d",&set_no);	
						getchar();
						break;
								
				case 2:	if(set_no == 1)
						{
							printf("\n\t\t H O W  M A N Y  V A L U E S ? \n\n\t\t=> ");
							scanf("%d",&choice);
							while(choice)
							{
								printf("\n\t\t E N T E R  D A T A : ");
								scanf("%d",&value);
								Insert(node1,value,value%MAX_SIZE);	
								choice--;
							}
							Initialize(union_node);
							Initialize(intersection_node);
							Initialize(difference1);
							Initialize(difference2);
							Initialize(symmetric);
						}
						else
						{
							printf("\n\t\t H O W  M A N Y  V A L U E S ? \n\n\t\t=> ");
							scanf("%d",&choice);
							while(choice!=0)
							{
								printf("\n\t\t E N T E R  D A T A : ");
								scanf("%d",&value);
								Insert(node2,value,value%MAX_SIZE);
								choice--;	
							}
							Initialize(union_node);
							Initialize(intersection_node);
							Initialize(difference1);
							Initialize(difference2);
							Initialize(symmetric);			
						}
						break;
			
				case 3: if(set_no == 1)
						{
							printf("\n\t\t E N T E R  D A T A : ");
							scanf("%d",&value);
							Delete(node1,value,value%MAX_SIZE);	
							Initialize(union_node);
							Initialize(intersection_node);
							Initialize(difference1);
							Initialize(difference2);
							Initialize(symmetric);	
						}
						else
						{
							printf("\n\t\t E N T E R  D A T A : ");
							scanf("%d",&value);
							Delete(node2,value,value%MAX_SIZE);
							Initialize(union_node);
							Initialize(intersection_node);
							Initialize(difference1);
							Initialize(difference2);
							Initialize(symmetric);
						}
						break;
					
				case 4: Union(union_node,node1,node2);
						print(union_node);
						break;	
					
				case 5: IntersectionSet(intersection_node,node1,node2);
						 print(intersection_node);
						 break;
				
				case 6: if( set_no == 1 )
						{
							DifferenceSet(difference1,node1,node2);
							print(difference1);
						}
						else
						{
							DifferenceSet(difference2,node2,node1);
							print(difference2);
						}
						break;
				
				case 7:  Initialize(difference1);
	                     Initialize(difference2);
	                     Initialize(symmetric);
						 DifferenceSet(difference1,node1,node2);
						 DifferenceSet(difference2,node2,node1);
						 Union(symmetric,difference1,difference2);
						 print(symmetric);
						 break;

				case 8: if(set_no == 1)
						{
							print(node1);
						}
						else
						{
							print(node2);
						}
						break;
				case 9: if(set_no == 1)
						{
							printf("\n\t\t ENTER DATA TO BE SEARCH => ");
							scanf("%d",&choice);
							Search(node1,choice,choice%MAX_SIZE);
						}
						else
						{
							printf("\n\t\t ENTER DATA TO BE SEARCH => ");
							scanf("%d",&choice);
							Search(node2,choice,choice%MAX_SIZE);
						}
						break;
				default: printf("\n\t\t P L E A S E  E N T E R  V A L I D  C H O I C E . . .\n\n");
			}
			
			printf("\n\n\t\t C O N T I N U E  O P E R A T I O N  O N  S E T  N O.  %d ? ",set_no);
			printf("\n\n\t\t E N T E R  'Y'  T O  C O N T I N U E : ");
 			fflush(stdin);
 			scanf("%c",&opt);
 			getchar();
			
			if(opt != 'y' && opt != 'Y')
			{
				break;	
			}
			
		}	
		
		printf("\n\n\t\t E N T E R  'Y'  T O  Q U I T : ");
 		fflush(stdin);
 		scanf("%c",&opt);
 		getchar();		
 		
		if( opt=='y' || opt=='Y' )
		{	
			break;	
		}
		else
		{
			printf("\n\n\t\t S E L E C T  T H E  S E T \n\t\t1) SET 1\n\n\t\t2) SET 2\n\n\t\t=> ");
			scanf("%d",&set_no);
			getchar();	
		}				
	}
}

