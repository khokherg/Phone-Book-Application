//header files
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

//DECELARATIONS
typedef struct
{
 char fname[100];
 char lname[100];
 char phone [15];
}Contact;

typedef struct node {
	Contact c;
	struct node *next;
} Node, *NodePtr;

struct node *head = NULL;

//METHOD DECELARATIONS
void load(char filename[10]);
void print_list(void);
void addContact(void);
void save(void);
void search_item(char fnm[20]);
void delete(char cName [30]);
int addUniqueContact(char cname [50]);

//MAIN BEGINS
int main()
{
    load("contacts.txt");          //Function to load all the contacts from file in linked list
	int userChoice;                //Determines which option the user has selected
	char contactToDelete [50];    //determines which contact to delete
	char contactToSearch [50];    //Determines which contact to search 

	do
	{
		printf("\nSelect the option below:\n");
		printf("1. Add the Contact\n");
		printf("2. Save the Contact\n");
		printf("3. View the Contact\n");
		printf("4. Search the Contact\n");
		printf("5. Delete the Contact\n");
		printf("6. Exit\n");

        scanf("%d", &userChoice);

		switch(userChoice)
		{
			case 1:
				addContact();    //Function to add the contact
				break;

			case 2:
				save();          //function to save the contacts in file from linked ist
				break;
			case 3:
				print_list();   //function to view all the contacts from file
				break;
			case 4:
				printf("\nPlesae enter the contact first name to search it from contact list:\n");
				scanf("%s", contactToSearch);
				search_item(contactToSearch);    //function to search the contact by first name
				break;
			case 5:
				
				printf("\nPlesae enter the contact first name to delete it from contact list:\n");
				scanf("%s", contactToDelete);
				delete(contactToDelete);      //function to delte the contact from the list by first name
				break;
			case 6:
				exit(0);     //closes the application
				break;
			default:
				printf("Plesae select the valid choice\n");
				break;

		}

	}while(userChoice!=6);
		
}  //MAIN ENDS


void print_list(void)  //function to print the link list
	{
 		FILE *fp1;        //pointer to the file
	    char c;
	    fp1 = fopen("contacts.txt", "r");   
        if(fp1 == NULL)
	      {  
	        printf("Error in opening the file");
	      }
	    else
	      {
			printf("\n");
            do
	         {
		       c = getc(fp1); 
			   putchar(c);  
		     }while (c!=EOF);
	   
	        fclose(fp1); //closing the file
	      }
	}

void addContact(void)   //function to add the contact in linked list
{
	int c;

	char firstname [50];
	char lastname [50];
	char phnumber [20];
	do
	{		
		printf("\nPlease enter the first name of the contact: \n");
		scanf("%s",firstname);
		c = addUniqueContact(firstname);   //function that checks if the first name is unique or not
	}while(c==1);
		printf("Please enter the last name of the contact: \n");
		scanf("%s",lastname);
      	int phlength=0;    
	do{
		printf("Please enter the phone number of the contact (digits): \n");
		scanf("%s", phnumber);
		phlength++;
	}	while(!isdigit(phnumber[phlength]));

	NodePtr newNode;   //pointer to insert a new contact
	newNode = (NodePtr)malloc(sizeof(Node));  //allocating the memory

	strcpy(newNode->c.fname,firstname);
	strcpy(newNode->c.lname, lastname);
	strcpy(newNode->c.phone , phnumber);
	if(head == NULL)
	{
	  //Making the pointer of the node to NULL
		newNode->next=NULL;
		head = newNode;     //header node is pointing to newly created node
	}

	else  // if the list already has contacts
	{
		newNode->next=head;
		head=newNode;
		printf("\nContact Added!!\n");

    }
}

 //WRITE TO THE FILE FUNCTION
void save()
{
	NodePtr wptr = head;
      char fname[30];
      char lname[30];
      char phone[15];
      FILE*fp; 
      
	  //opening the file
      fp = fopen("contacts.txt", "w+");

      while(wptr!=NULL)
	   {
	        fprintf(fp, "%s ",wptr->c.fname);
		    fprintf(fp, "%s ",wptr->c.lname);
		    fprintf(fp, "%s\n", wptr->c.phone);
            wptr = wptr->next;
	   }
	fclose(fp);   //closing the file
}

void load(char filename[10]){
	// create temp variables that hold the data while reading the file 
	char tmpFname[30]; 
    char tmpLname[30]; 
	char tmpPhone[15]; 
	NodePtr cptr ;
	FILE *input=fopen(filename,"r+");
	// check if the file opened successfuly  
	if(input==NULL) 
		printf("Error: Cannot open the file"); 
	else
		{

		// continue in reading the file till the EOF
		while(!feof(input))
			{
			 cptr = (NodePtr)malloc(sizeof(Node));
			 
			strcpy(tmpFname,""); 
			strcpy(tmpLname,""); 
			strcpy(tmpPhone,"");
			fscanf(input,"%s %s %s", tmpFname,tmpLname, tmpPhone); 
			if(strcmp(tmpFname,"")!=0){
				strcpy(cptr->c.fname,tmpFname);   //copies the name and phoone numbers from the file in temp variables
                strcpy(cptr->c.lname,tmpLname);
				strcpy(cptr->c.phone,tmpPhone); 

				if(head==NULL)
				{
					
					cptr->next=NULL;
					head= cptr;

				}
				else
				{
					struct node *temp=head;
		        	while(temp->next!=NULL){
			      	  temp=temp->next;
		             }
		               temp->next=cptr;
				}
				 
			}
		}

		fclose(input);
	} 

}

//FUNCTION TO SEARCH A SPECIFIC CONTACT
void search_item(char fnm[20])
{
    int counter =0;

    NodePtr searchNode= (NodePtr)malloc(sizeof(Node));
	searchNode=head;
    while(searchNode!=NULL)
    {
        if(strcmp(searchNode->c.fname,fnm)==0)   //compares first name of the contact with the first name that is enetered by user
        {
            printf("%s %s %s", searchNode->c.fname,searchNode->c.lname,searchNode->c.phone);
			counter = 1;
            break;
        }
        else
            searchNode = searchNode->next;
    }

    if(counter==0)
        printf("Item not found\n");

}

//FUNCTION TO DELETE A SPECIFIC CONTACT FROM THE FILE
void delete(char cName [30])
{

	struct node *temp1 = head, *temp2;	//need two pointer to keep tract of the two nodes
	//if the list contains only one node
	if(strcmp(temp1->c.fname,cName)==0){
		head = head->next;
		save();
		}
	else
		{
			while (strcmp(temp1->c.fname, cName)!=0)    //Search the specific contact to delete it
			{
		
				if (temp1->next == NULL)
				{
					printf("\nGiven not found in the list!!!");
					goto functionEnd;
				}
				temp2 = temp1;
				temp1 = temp1->next;
		
			}
     		temp2->next = temp1->next;

	 		free(temp1);
	 		printf("\nOne contact deleted!!!\n");
			save();     //Save the contact list into file after making changes in the list
	 		functionEnd:;
		}

}

//FUNCTION TO VERIFY IF THE FIRST NAME IS UNIQUE OR NOT
int addUniqueContact(char cname [50])
{
    int returnVal =0;
    NodePtr searchNode= (NodePtr)malloc(sizeof(Node));
	searchNode=head;
    while(searchNode!=NULL)
    {
        if(strcmp(searchNode->c.fname,cname)==0)
        {
			printf("\nThis name already exist enter any other name\n");
			printf("%s %s %s", searchNode->c.fname,searchNode->c.lname,searchNode->c.phone);
            
            returnVal=1;  //Changes value to 1 if the contact with the same first name already exist
			break;
        }
        else
            searchNode = searchNode->next;
		    
    }

  return returnVal;

}
