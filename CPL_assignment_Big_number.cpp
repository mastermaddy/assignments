#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>

typedef struct digit{
	 int num;													//structure is defined;
     struct digit* next;
    struct digit* prev;
}digit;



digit* make_digit(char str[],digit* head,digit** last_ptr)
{
 	int i=0;
  	digit* num;
 	while(str[i]!='\0')
 	{
 		
  		num=(digit*)malloc(sizeof(digit));				// making a node, converting input string to integer linked_list
   		num->next=head;									// InsertatStart
  		num->prev=NULL;									//Making doubly linked_list 
  		num->num=str[i]-'0';
 
  		if(head!=NULL)
  		{
  			head->prev=num; 
  		}
 
  		head=num;
 
  		
  		if(!i)
  		{
   			*last_ptr=num;
  		}
  		
  		i++;
 
 	}
 	
 	return head;

}




void print(digit* last)
{

 	while(last!=NULL)
 	{
 		
 		printf("%d",last->num);				//Printing only numbers which we are going to use
 
  		last=last->prev; 		
 	
	}
 	
 	printf("\n");

}

void print2(digit* nptr)
{

 	while(nptr!=NULL)
 	{

  		printf("%d",nptr->num);					//Printing the results of operations

  		nptr=nptr->next; 

 	}
printf("\n");
}




digit* addition(digit* head1,digit* head2,digit* new_digit)
{
 	digit* nptr;
 
 	int carry=0,add;
 
 	while(head1!=NULL&&head2!=NULL)
 	{
 
 		nptr=(digit*)malloc(sizeof(digit));
  												
  		add=((head1->num+head2->num))+carry;					//adding last digit along with carry
  
  		carry=add/10;
 
  		add=add%10;
  		
  		nptr->num=add;
   
  		nptr->next=new_digit;							
 
  		new_digit=nptr;
  
  
  		head1=head1->next;
 
  		head2=head2->next;  
 	}
 
 	if(head1!=NULL)
 	{
  
  		while(head1!=NULL)
  		{
  
   			nptr=(digit*)malloc(sizeof(digit));
  																	//if 2nd number exhousted then we have to add directly
   			add=((head1->num))+carry;
  
   			carry=add/10;
  
   			add=add%10;
   
   			nptr->num=add;
  
   			nptr->next=new_digit;
  
   			new_digit=nptr;
  
   			head1=head1->next; 
  
  		}
 	}
 
 	else
 	{
 
 		while(head2!=NULL)
  		{
 
   			nptr=(digit*)malloc(sizeof(digit));					//if first number exhousted
 
   			add=((head2->num))+carry;
 
   			carry=add/10;
 
   			add=add%10;
   
   			nptr->num=add;
 
   			nptr->next=new_digit;
 
  	 		new_digit=nptr;
 
   			head2=head2->next; 
 
  		}
 	}
 
 	if(carry!=0)
 	{
 
   		nptr=(digit*)malloc(sizeof(digit));			//if carry does not become zero then we have to add to new node(start of answer);
 
   		add=carry;
 
   		nptr->num=add;
 
   		nptr->next=new_digit;
 
   		new_digit=nptr;
 
 	}
 
 	return new_digit;
 	
}




digit* substraction(digit* head1,digit* head2,digit* new_digit)
{
 
	digit* nptr;

 	digit *real_head1,*real_head2;
 	
 	real_head1=head1;

 	real_head2=head2;
 	
 	int borrow=0,sub;

 	new_digit=NULL;
 
 	while(head1!=NULL&&head2!=NULL)
 	{

 		nptr=(digit*)malloc(sizeof(digit));
 		
  		if(head1->num>=head2->num+borrow)									//substracting num1-num2 and then borrow (initially zero)
  		{

   			sub=(head1->num)-(head2->num)-borrow;

  		}
  		
  		else
  		{

   			sub=10+head1->num-head2->num-borrow;							//if significant digit of num2 > corresponding significant digit of num1

  		}
  
  		if(head1->num>=head2->num+borrow)
  		{

   			borrow=0;

  		}
  		
  		else
  		{

   			borrow=1;

  		}
  
  		nptr->num=sub;

  		nptr->next=new_digit;

  		new_digit=nptr;
  
  
  		head1=head1->next;

  		head2=head2->next;
		    
 	}
 
  	while(head1!=NULL)
  	{
   
   		nptr=(digit*)malloc(sizeof(digit));

   		if(head1->num>=borrow)
  		{

   			sub=(head1->num)-borrow;

  		}
  		
  		else
  		{

   			sub=10+head1->num-borrow;

  		}

   		(head1->num>=borrow)?borrow=0:borrow=1;							//if 2nd number == NULL
    
   		nptr->num=sub;

   		nptr->next=new_digit;

   		new_digit=nptr;

   		head1=head1->next; 

  	}
 
 
 	if(head2!=NULL)
 	{

  		new_digit=substraction(real_head2,real_head1,new_digit);		//if 1st number == NULL; means num2>num1 so we are changing position and calling function again
//printf("-");
  		return new_digit;

 	}
 
 	else if(borrow!=0)
 	{
		new_digit=substraction(real_head2,real_head1,new_digit);		//if borrow != 0 , same condition as above;
//		printf("-");	
  		return new_digit;

 	}
 	

 	
 	return new_digit;

}


digit* reverse(digit* head)					//reverse function created as we are Inserting at start of linked_list
{

	digit *trail,*mid;
	mid=NULL;
	
	while(head!=NULL)
	{

		trail=mid;

		mid=head;

		head=head->next;

		mid->next=trail;

	}
	
	return mid;

}



/**digit* multi2(digit* head1,digit* head2)
{
	digit *ptr1,*ptr2,*temp,*result,*new_head;
	new_head=NULL;
	int carry=0,count1=0,count2;
	result=NULL;
	
	for(ptr2=head2;ptr2!=NULL;ptr2=ptr2->next)
	{																	
		new_head=NULL;
		count2=count1;															
		while(count2>0)																		
		{
			temp=(digit*)malloc(sizeof(digit));
			temp->num=0;
			temp->next=new_head;
			new_head=temp;
			count2--;
		}
		
		for(ptr1=head1,carry=0;ptr1!=NULL;ptr1=ptr1->next)
		{
			temp=(digit*)malloc(sizeof(digit));							//normal multiplication of digits of 1st number and 2nd number
			temp->num=((ptr1->num)*(ptr2->num)+carry)%10;
			carry=((ptr1->num)*(ptr2->num)+carry)/10;
			temp->next=new_head;
			new_head=temp;
		}
		
		if(carry!=0)
		{
			temp=(digit*)malloc(sizeof(digit));			
			temp->num=carry;
			temp->next=new_head;
			new_head=temp;
		}
		
		count1++;
		new_head=reverse(new_head);										// reversing as we are inserting at start				
		result=addition(result,new_head,NULL);
		result=reverse(result);
	
	}
	
	result=reverse(result);
	return result;
}



int compare(digit* head1,digit* head2)
{
	
	while(head1->next!=NULL&&head2->next!=NULL)
	{					
		head1=head1->next;															//checking which number is big
		head2=head2->next;	
	}
	
	if(head2->next==NULL)
	{

		if(head1->next!=NULL)
		{																			//if num1>num2

			return 1;

		}

		else if(head1->num>head2->num)												//if both has same number of digits but Most signifi. digit of num1 is big
		{

			return 1;

		}

		else if(head1->num<head2->num)
		{
																					//if most signi. digit of num2 is big
			return 0;

		}
		else																		//if both numbers are same
		{
			return -1;
		}

	}
	
	else if(head1->next==NULL)														//if num2>num1
		{

			if(head2->next!=NULL)
			{
	
				return 0;
	
			}
	
			else if(head1->num>head2->num)
			{
	
				return 1;
	
			}
	
			else if(head1->num<head2->num)
			{
	
				return -1;
	
			}
			else
			{
				return -1;
			}
	
		}
			
}



digit* divide(digit* head1,digit* head2)
{
	
	digit *node0,*temp;
	
	int flag;
	
	node0=(digit*)malloc(sizeof(digit));
	
	node0->num=0;	node0->next=NULL;						//node0 is quotient node
	

		
	flag=compare(head1,head2);								// comparing both numbers
	
	if(flag<0)
	{
		(node0->num)++;										//if both numbers are same(quotient==1)
		return node0;
	}
	
	
	while(flag!=0)
	{
		
		temp=NULL;
		
		head1=substraction(head1,head2,temp);			//repeated substraction of divident
		
		while(head1->num==0)
		{
			temp=head1;									//we dont want zero at start of linked_list so we are removing
			head1=head1->next;
			free(temp);
		}
		
		if(head1!=NULL)
		{
			head1=reverse(head1);
			(node0->num)++;
		
			flag=compare(head1,head2);				//quotient will increase till num1>=num2
			
		}
		
		if(flag<0)
		{
			(node0->num)++;
			temp=substraction(head1,head2,NULL);		//substraction for remainder
			printf("Remainder is ");
			print2(temp);
			return node0;
		}
	
	}
	
	if(flag==0)
	{
		(node0->num);
		printf("Remainder is ");
		print2(head1);
		return node0;
	}
	
	(node0->num);
		temp=substraction(head1,head2,NULL);
		printf("\nRemainder is 3) ");
		print2(temp);
	return node0;

}


int main()
{

 	char str1[300],str2[300];

 	digit *head1,*head2,*head3;

 	digit *last1,*last2;
 	
 	int choice,sign;
 	
 	head2=head1=NULL;

 	last1=last2=NULL;

 	head3=NULL;

 	
 	printf("Enter first number= ");

 	gets(str1);

 	head1=make_digit(str1,head1,&last1);
 	
 	printf("Enter second number= ");

 	gets(str2);

 	head2=make_digit(str2,head2,&last2);
 		
 	printf("Enter:\n1 for addition\n2 for subtraction\n3 for multiplication\n4 for division\n=>");
 	scanf("%d",&choice);
 	switch(choice)
 	{
 			
		case 1:		head3=NULL;
					printf("addition is ");
 					head3=addition(head1,head2,head3);
					print2(head3);
					printf("\n");	
					break;
						
		case 2:		head3=NULL;
					printf("Substraction is ");
					sign=compare(head1,head2);
					if(sign==0)
					{
						printf("-");
					}
					head3=substraction(head1,head2,head3);
				 	print2(head3);
 					printf("\n");
 					break;
 			
		case 3:		printf("multipication is ");
 					head3=multi2(head1,head2);
					print2(head3);
					printf("\n");
					break;
		 		
		case 4:		head3=divide(head1,head2);
 					printf("Division is ");
 					print2(head3);
 					printf("\n");
 					break;
		}
 }
