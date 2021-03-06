#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
struct node{
	int city;
	int x;
	int y;
	int visited;
	struct node *next;	
};
typedef struct node node;
node * head;
int totalcost=0;
int indexmin;

int insert(node** root,int city,int x,int y){	//// inserting linkedlist
	node* newNode;
	node*temp;
	newNode=(node*)malloc(sizeof(node));
	newNode->city=city;
	newNode->x=x;
	newNode->y=y;
	newNode->visited=0;
	newNode->next=NULL;		
	if(*root == NULL)
		*root=newNode;
	else{
		temp=*root;
		while (temp->next!=NULL){
			temp=temp->next;
		}
		temp->next=newNode;					
	}
	return 0;
}
void changenode(node**root,int c){
	node*iter=*root;
	node*temp=*root;
	int value;	
	int i=1;
	while(i<c){
		iter=iter->next;
		i++;
	}
	value=iter->city;
	iter->city=temp->city;
	temp->city=value;
	value=iter->x;
	iter->x=temp->x;
	temp->x=value;
	value=iter->y;
	iter->y=temp->y;
	temp->y=value;
	value=iter->visited;
	iter->visited=temp->visited;
	temp->visited=value;
}
void colorize(node**root,int c){
	node *temp =*root;
	int i=1;
	while(i<c){	
		temp=temp->next;
		i++;
	}
	temp->visited =1;	
}
void recolorize(node**root,int c){
	node *temp =*root;
	int i=1;
	while(i<=c){
		temp->visited =0;
		temp=temp->next;
		i++;
	}	
}
int read_file_to_count(char*name){	
	FILE *file;
	file = fopen(name,"r");
	if(file==NULL){
		perror("File could not found");
		return -1;
	}
	int city=0;
	int x=0;
	int y=0;
	int counter=0;
		while(1){	  		
	  	    fscanf(file,"%d %d %d",&city,&x,&y);			
			counter++;
	  	    if(feof(file))
	  	       break;    			   	  	                 
	 	}
	 	return counter;
}
int findmin(int arr[], int n){
    int i;
    int min = arr[0]; 
    for (i = 1; i < n; i++)
        if (arr[i] < min){
			min = arr[i];
			indexmin=i;
		}
    return min;
}
void read_file(char*name,node*root){
	FILE *file;
	file = fopen(name,"r");
	if(file==NULL){
		perror("File could not found");
		exit(0);
	}	
	int city=0;
	int x=0;
	int y=0;
		while(1){	  		
	  	    fscanf(file,"%d %d %d",&city,&x,&y);		
			insert(&root,city,x,y); 	  	
	  	    if(feof(file))
	  	       break;    				  				   	  	                 
	 	}
	head=root;
}
int distance(int x1,int x2,int y1,int y2){
	int d = round(sqrt( pow(x1-x2,2) + pow(y1-y2,2) ));	   
	return d;	
}  
 void printList (struct node *n){	   //method that prints lists
	node*node;
	node=n;
    while (node != NULL)
    {
        printf ("%d %d %d %d \n", node->city,node->x,node->y,node->visited);
        node = node->next;
    }
}

int main(){
	char file_name[30];
	int count=-1;
	int dist;
	int i,j,k,a,p,r;	
	int returncost;
	node *temp1,*temp2,*temp3;	
	while(count==-1){
	printf("\nEnter the input file name:");
	gets(file_name);
	count=read_file_to_count(file_name);
	}
	int costs[count];
	static int tour_order[2924][2924];	
	read_file(file_name,head);
	
	temp1=head;
	temp2=head;
	temp3=head;
	int nextcity=0;
	int min;

	for(p=1;p<=count;p++){		
		temp1=head;
		temp2=head;
		r=1;
		for( i=1;i<count;i++){			///ad�m say�s�
			min=300000;
			for(j=1;j<=count;j++){			//1. �ehirden en k�sa yeri bulduk		
				if(temp1->city!=temp2->city){			
					dist=distance(temp1->x,temp2->x,temp1->y,temp2->y);
					if(dist<min&&temp2->visited!=1){
						min=dist;					//1. �ehirden en k�sa yer
						nextcity=j	;
									//nextcity 2. �ehirimiz	
					}
				}
				temp2=temp2->next;	
			}
			tour_order[p-1][i-1]=temp1->city;
			colorize(&head,r);
			r=nextcity;
			totalcost+=min;
			returncost= distance(head->x,temp1->x,head->y,temp1->y);
			temp1=head;
			temp2=head;
			for(k=1;k<nextcity;k++){
				temp1=temp1->next;
			}
		}
		tour_order[p-1][count-1]=temp1->city;
		costs[p-1]=totalcost+returncost;
		totalcost=0;
		recolorize(&head,count); 
		changenode(&head,p);
	} 
	int result;
	result =findmin(costs,count-1);
	FILE *file = fopen("out.txt","w");	
	fprintf(file, "%d\n",result);
	printf(" %d\n",result);
	for(i=0;i<count;i++){
		fprintf(file, "%d\n",tour_order[indexmin][i]);
		printf("%d: %d\n",i,tour_order[indexmin][i]);
	}
}
