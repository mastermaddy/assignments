#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MAX_SIZE 100



typedef struct node_tag{
	char* S_address;
	int size;  
	char c;
	struct node_tag* next;
} node;




node *alloc_ptr,*free_ptr; 
char* heap_ptr;


// MERGE_SORT FOR SORTING THE CLUSTERS ON THE BASIS OF ADDRESS;
node* sortedmerge(node* a,node* b);

void frontbacksplit(node* source,node** frontRef,node** backRef);
 
void mergesort( node** headRef)
{
     node* head = *headRef;

     node* a;

     node* b;

    if ((head == NULL) || (head->next == NULL))
    {
        return;
    }

    frontbacksplit(head, &a, &b);

    mergesort(&a);

    mergesort(&b);

    *headRef = sortedmerge(a, b);

}

 
 
 

node* sortedmerge(node* a,node* b)
{
 	node* result = NULL;
    if (a == NULL)
        return(b);

    else if (b == NULL)
        return(a);
        
    if ( a->S_address <= b->S_address)
    {
        result = a;

        result->next = sortedmerge(a->next, b);
	}
	else
	{
        result = b;

        result->next = sortedmerge(a, b -> next);
    }

    return(result);
}

 
 
 

void frontbacksplit(node* source,node** frontRef,node** backRef)
{
    node* fast;

	node* slow;

    if ( source == NULL || source->next == NULL )
    {
       *frontRef = source;

        *backRef = NULL;
    }
    else
    {
        slow = source;

        fast = source -> next;

        while ( fast != NULL )
  		{
            fast = fast -> next;

            if ( fast != NULL )
            {
                slow = slow -> next;

                fast = fast -> next;
            }
    	}

    *frontRef = source;

    *backRef = slow->next;

    slow->next = NULL;

    }
}





void print(char heap_ptr[],node* alloc_ptr)
{
	int size = 0;
	
	node* t_alloc_ptr=alloc_ptr;
	
	mergesort(&free_ptr);
	
	node* temp_free = free_ptr;
	
	while( temp_free != NULL )
	{
		printf("address of %c is %c with free space %d\n",temp_free->c,temp_free->S_address,temp_free->size);
		size = size + (temp_free->size);
		temp_free = temp_free->next;
	}
	
	
	printf("\nFREE HEAP MEMORY = %d \n",size);
	
	while( t_alloc_ptr !=NULL)
	{
		printf("\nCLUSTER %c (%d)\n",t_alloc_ptr->c,t_alloc_ptr->size);
	
		t_alloc_ptr=t_alloc_ptr->next;
	}		
}





node* Compact(node* free_ptr)
{
	mergesort(&free_ptr);
	char* c = free_ptr->S_address;
	int size;
	node* free_temp = free_ptr;
	node* temp;
	
	while( free_temp->next != NULL )
	{
		size = free_temp->size;
		
		while(size != 0)
		{
			c++;
			size--;	
		}
	
		if( c == (free_temp->next)->S_address )
		{
			temp = free_temp->next;	
			free_temp->next = temp->next;
			free_temp->size = free_temp->size + temp->size;
			free(temp);
		}
		
		free_temp = free_temp->next;		
	}

	return free_ptr;
}





void Initialize()
{	
	heap_ptr = (char*)malloc(MAX_SIZE*sizeof(char));
	
	free_ptr = (node*)malloc(sizeof(node));
	
	free_ptr->S_address = heap_ptr;
	
	free_ptr->size = MAX_SIZE;
	
	free_ptr->next = NULL;	
}





node* Allocation( int n)
{
	static char c = 'A';
		
	node* temp_free = free_ptr;
	
	node* temp = (node*)malloc(sizeof(node));
	
	int free_size = 0;
	
	while( temp_free != NULL )
	{
		free_size = free_size + (temp_free->size);
		
		temp_free = temp_free->next;
	}
	
	temp_free = free_ptr;
	
	if( n <= MAX_SIZE && n <= free_size )
	{
		if( alloc_ptr == NULL )				// first allocation from free_memory
		{
			temp->size = n;
		
			temp->S_address = free_ptr->S_address;
		
			temp->next = alloc_ptr;
		
			temp->c = c++;
		
			alloc_ptr = temp;
		
			free_ptr->S_address = (free_ptr->S_address) + n;
		
			free_ptr->size = (free_ptr->size) - n;
		
			return alloc_ptr;		
		}
		
				
		if( free_size >= n )
		{	
		
			if( temp_free->size >=n )					// FIRST FIT....
			{
				temp->size = n;
		
				temp->S_address = temp_free->S_address;
				
				temp_free->S_address = temp_free->S_address + n;
		
				temp->next = alloc_ptr;
		
				temp->c = c++;
		
				alloc_ptr = temp;	
					
				temp_free->size = temp_free->size - n;
					
				if( temp_free->size == 0 )
				{
					temp = temp_free;
					
					temp_free = temp_free->next;
					
					free(temp);
				}
				return alloc_ptr;	
			}	
		
		
			node* prev;
					
			while( temp_free->next != NULL && (temp_free->next->next) != NULL )			// FINDING FIRST FIT
			{
				prev = temp_free;
				
				temp_free =  temp_free->next;
				
				if( temp_free->size >= n )
				{
					temp->size = n;
		
					temp->S_address = temp_free->S_address;
					
					temp->S_address = temp_free->S_address + n;
		
					temp->next = alloc_ptr;
		
					temp->c = c++;
		
					alloc_ptr = temp;	
					
					temp_free->size = temp_free->size - n;
					
					if( temp_free->size == 0 )
					{
						prev->next = temp_free->next;
					
						free(temp_free);
					}
					
					return alloc_ptr;			
				}			
			}
			
			
			if( temp_free->next == NULL )									// ONLY FREE_MEMORY IS AVAILABLE
			{	
				temp->S_address = temp_free->S_address;
				
				temp_free->S_address = (temp_free->S_address) + n;
			
				temp_free->size = (temp_free->size) - n;
			
				temp->c = c++;
			
				temp->size = n;
		
				temp->next = alloc_ptr;
	
				alloc_ptr = temp;
		
				return alloc_ptr;
			}
		
		
			if( temp_free->next->next == NULL )										//IF ONLY TWO FREE_BLOCKS ARE AVAILABLE 
			{	
				temp->S_address = temp_free->next->S_address;
		
				temp_free->next->S_address = (temp_free->next->S_address) + n;
			
				temp_free->next->size = (temp_free->next->size) - n;
			
				temp->c = c++;
			
				temp->size = n;
		
				temp->next = alloc_ptr;
	
				alloc_ptr = temp;
		
				return alloc_ptr;
			}
		}
	}
		
	else
	{
		printf("\nSIZE NOT AVAILABLE\n");
		return alloc_ptr;
	}
	
}





// DEALLOCATION OF HEAP MEMORY
node* Deallocation( char zero )
{
	node* temp_alloc = alloc_ptr;
	
	if( alloc_ptr == NULL )
	{
		printf("UNABLE TO DE-ALLOCATE MEMORY :(\n");
	
		return alloc_ptr;
	}
	
	if( alloc_ptr->next != NULL )
	{	
		if(alloc_ptr->c == zero )				// if head of alloc_ptr needs to deallocate
		{
			node* temp = alloc_ptr;
			
			node* temp2 = (node*)malloc(sizeof(node));
		
			temp2->S_address = alloc_ptr->S_address;
		
			temp2->size = alloc_ptr->size;
		
			temp2->next = free_ptr;
			
			free_ptr = temp2;
		
			alloc_ptr = alloc_ptr->next;
		
			free(temp);
		
			return alloc_ptr;
		}
	
	
		else													// FINDING WHICH BLOCK HAS TO BE DELETED
		{	
			node* alloc_temp = alloc_ptr;			
														
			node* prev = alloc_temp;
			
			alloc_temp = alloc_temp->next;
			
			while( alloc_temp != NULL )
			{	
				if( alloc_temp->c == zero )
				{		
					node* temp2 = (node*)malloc(sizeof(node));
		
					temp2->S_address = alloc_temp->S_address;
		
					temp2->size = alloc_temp->size;
		
					temp2->next = free_ptr;
			
					free_ptr = temp2;
					
					prev->next = alloc_temp->next;
		
					free(alloc_temp);
		
					return alloc_ptr;
				}
				
				prev = alloc_temp;
				alloc_temp = alloc_temp->next;	
		
			}
	
			if(alloc_temp == NULL )
			{
				printf("\nNOT FOUND\n");
				return alloc_ptr;
			}
	
		}
	}
	
	
	else if(alloc_ptr->c == zero)				// if the block with next == NULL has to deallocate
	{
		node* temp = alloc_ptr;
		
		node* temp2 = (node*)malloc(sizeof(node));
		
		temp2->S_address = alloc_ptr->S_address;
		
		temp2->size = alloc_ptr->size;
		
		temp2->next = free_ptr;
		
		free_ptr = temp2;
		
		alloc_ptr = alloc_ptr->next;
		
		free(temp);
		
		return alloc_ptr;	
	}
	else
	{
		printf("OPERATION UNSUCCESSFUL :(");
	}
}





int main()
{
	alloc_ptr = NULL;
	
	int n;
	
	char x;
	
    Initialize();

	int choice;
	
	while(1)
	{
		printf("1. ALLOCATION\n2. DE-ALLOCATION\n3. PRINT\n=> ");
		
		scanf("%d",&choice);
	
		switch(choice)
		{
		
			case 1 : printf("HOW MANY NODES? => ");
					 scanf("%d",&n);
					 if(n>0)
					 alloc_ptr = Allocation(n);
					 else
					 printf("UNABLE TO ALLOCATE\n");
					 break;
		
			case 3 : print( heap_ptr ,alloc_ptr);
					 break;
					 
			case 2:  printf("ENTER CLUSTER NAME =>  ");
					 getchar();
					 scanf("%c",&x);
					 alloc_ptr = Deallocation(x);
					 break;
		}
		printf("0. CONTINUE\n1. QUIT\n=> ");
		scanf("%d",&choice);
		if(choice)
		{
			break;
		}
		
		free_ptr = Compact(free_ptr);
	
	}
}





