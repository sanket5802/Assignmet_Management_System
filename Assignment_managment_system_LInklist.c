#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LEN 50


typedef struct student_record
{
	int student_id;
	char name[MAX_LEN];
	char group_partner[MAX_LEN];
	int group_id;
	char assignment_name_id[MAX_LEN];
	char deadline[MAX_LEN];
	char status[MAX_LEN];
	float offline_marks;
	float viva_marks;
	
	struct student_record* next;
	
}Node1;


typedef struct assignment_record
{
	int assignment_id;
	char topic_name[MAX_LEN];
	char status[MAX_LEN];
	struct StudentAssignmentRecord* student_group;
	
	struct assignment_record* next;
}Node2;


typedef struct StudentAssignmentRecord 
{
    int student_group_id;
    char status[MAX_LEN];
    float marks_given;
    
    struct StudentAssignmentRecord* next;
}Node3;


int hashcode(int value)
{
	return (value%10);
}


Node1* student[10] ;
Node2* assignment[10] ;

void initialise()
{
	int i;
	for(i=0;i<10;i++)
	{
		student[i]=NULL;
		assignment[i]=NULL;
	}
}


Node1* create_student(int student_id,char* name,char* group_partner,int group_id,char* assignment_name_id,char* deadline,char* status,float offline_marks,float viva_marks)
{
	Node1* nptr = (Node1*)malloc(sizeof(Node1));
	
	nptr->student_id = student_id;
	strcpy(nptr->name , name);
	strcpy(nptr->group_partner , group_partner);
	nptr->group_id = group_id;
	strcpy(nptr->assignment_name_id , assignment_name_id);
	strcpy(nptr->deadline , deadline);
	strcpy(nptr->status , status);
	nptr->offline_marks = offline_marks;
	nptr->viva_marks = viva_marks;
	nptr->next = NULL;
	
	return nptr;
}


Node2* create_assignment(int assignment_id , char* topic_name)
{
	Node2* nptr = (Node2*)malloc(sizeof(Node2));
	
	nptr->assignment_id = assignment_id;
	strcpy(nptr->topic_name , topic_name);
	strcpy(nptr->status , "Declared");
	nptr->student_group = NULL;
	nptr->next = NULL;
	
	return nptr;
}

float max(float a , float b)
{
	if(a>=b)
	{
		return a;
	}
	return b;
}

Node3* create_student_group(int student_group_id , char* status , float offline_marks1 , float viva_marks1 , float offline_marks2 , float viva_marks2)
{
	Node3* nptr = (Node3*) malloc(sizeof(Node3));
	
	nptr->student_group_id = student_group_id;
	strcpy(nptr->status, status);
	nptr->marks_given = max(offline_marks1+viva_marks1 , offline_marks2+viva_marks2);
	nptr->next = NULL;
	
	return nptr;
}





//// Question 1----------------->>>>

void insert_student(Node1* student[],int student_id1,int student_id2,char* name,char* group_partner,int group_id,char* assignment_name_id,char* deadline,char* status,float offline_marks1,float viva_marks1,float offline_marks2,float viva_marks2,int assignment_id)
{
	Node1* nptr1 = create_student(student_id1,name,group_partner,group_id,assignment_name_id,deadline,status,offline_marks1,viva_marks1);
	Node1* nptr2 = create_student(student_id2,group_partner,name,group_id,assignment_name_id,deadline,status,offline_marks2,viva_marks2);
	
	int key = hashcode(group_id);
	
	Node1* ptr = student[key];
	Node1* prev = NULL;
	int found = 0;
	while(ptr!=NULL)  // Traversingn list
	{
		prev = ptr;
		if(ptr->group_id == group_id)
		{
			found = 1;
		}
		ptr = ptr->next;
	}
	if(found == 1)
	{
		printf("Group Id already exists \n\n");
	}
	else
	{
		if(prev == NULL)
		{
			nptr1->next = nptr2;
			student[key] = nptr1;
		}
		else
		{
			prev->next = nptr1;
			nptr1->next = nptr2;
		}
		
		////Checking in assignment record ---------------------->>>>>
		found = 0;
		int key = hashcode(assignment_id);
		Node2* ptr = assignment[key];
		Node2* prev = NULL;
		
		while(ptr!=NULL)
		{
			prev = ptr;
			if(strcmp(ptr->topic_name , assignment_name_id) == 0)
			{
				found =1;
				break;
			}
			ptr = ptr->next;
		}
		
		if(found == 0)
		{
			Node2* nptr = create_assignment(assignment_id , assignment_name_id );
			if(prev == NULL)
			{
				assignment[key] = nptr;
			}
			else
			{
				prev->next = nptr;
			}
		}
		
		
		//// Adding Students Groups
		
		Node3* nptr3 = create_student_group(group_id ,status ,offline_marks1 ,viva_marks1 ,offline_marks2 ,viva_marks2);
		
		ptr = assignment[key];
		while(ptr!=NULL)
		{
			if(ptr->assignment_id == assignment_id)
			{
				nptr3->next = ptr->student_group; //Inserting at Start
				ptr->student_group = nptr3;
				
				break;
			}
			ptr = ptr->next;
		}
	}
	
}







//// Question 2 --------------->>>>

void insert_assignment(Node1* student[] , Node2* assignment[] , char* topic_name , int assignment_id , int* student_id , char* name[] , int* group_id , char* deadline , char** status , float* offline_marks , float* viva_marks , int num_stud )
{
	Node2* nptr = create_assignment(assignment_id , topic_name );
	
	int key = hashcode(assignment_id);
	Node2* ptr = assignment[key];
	Node2* prev = NULL;
	int found = 0;
	while(ptr!=NULL)
	{
		prev = ptr;
		if(ptr->assignment_id == assignment_id)
		{
			found = 1;
		}
		ptr = ptr->next;
	}
	//printf("Found : %d\n",found);
	if(found == 1)
	{
		printf("An assignment with same id already exists \n\n");
	}
	else
	{
	
		nptr->next = assignment[key];
		assignment[key] =nptr;
		
		//printf("Found : %d\n",found);
		
		int i;
		for(i=0;i<num_stud;i+=2)
		{
			Node3* nptr3 = create_student_group(group_id[i] , status[i] ,offline_marks[i] ,viva_marks[i] ,offline_marks[i+1] ,viva_marks[i+1]);
			
			nptr3->next = nptr->student_group;
			nptr->student_group = nptr3;
		}
		//printf("Found : %d\n",found);
		
		for(i=0;i<num_stud;i+=2)
		{
			key = hashcode(group_id[i]);
			Node1* ptr = student[key];
			Node1* nptr1 = create_student(student_id[i],name[i],name[i+1],group_id[i],topic_name,deadline,status[i],offline_marks[i],viva_marks[i]);
			Node1* nptr2 = create_student(student_id[i+1],name[i+1],name[i],group_id[i+1],topic_name,deadline,status[i],offline_marks[i+1],viva_marks[i+1]);
			
			nptr1->next = nptr2 ;
			nptr2->next = ptr;
			student[key] = nptr1;
		}
	}
	//printf("heyyyy\n");
}






///// Question 3 --------------->>>>

void change_status(Node1* student[] , Node2* assignment[] , int group_id , char* status ,float offline_marks1 , float viva_marks1 , float offline_marks2 , float viva_marks2 , int asg_id)
{
	int key = hashcode(group_id) ;
	int flag=1;
	Node1* ptr = student[key];
	//printf("h\n");
	while(ptr!=NULL && flag==1)
	{
		//printf("%d\n",ptr->group_id);
		if(ptr->group_id == group_id)
		{
			//printf("Came here\n");
			strcpy(ptr->status , status);
			strcpy(ptr->next->status , status);
			ptr->offline_marks = offline_marks1;
			ptr->next->offline_marks = offline_marks2;
			ptr->viva_marks = viva_marks1;
			ptr->next->viva_marks = viva_marks2;
			
			flag=0;
		
		}
		ptr = ptr->next;
	}
	
	
	//// Changing in student group records 
	key = hashcode(asg_id) ;
	flag=1;
	Node2* ptr2 = assignment[key];
	while(ptr2!=NULL && flag==1)
	{
		if(strcmp(ptr2->topic_name , ptr->assignment_name_id) == 0)
		{
			Node3* ptr3 = ptr2->student_group;
			while(ptr3!=NULL && flag==1)
			{
				if(ptr3->student_group_id == group_id)
				{
					strcpy(ptr3->status , status);
					ptr3->marks_given = max(offline_marks1+viva_marks1 , offline_marks2+viva_marks2);
					flag=0;
				}
				ptr3 = ptr3->next ;
			}
			flag=0;
		}
		ptr2 = ptr2->next;
	}
	
	
	
	
	/// Changing status of Assignment
	
	ptr2 = assignment[key];
	//flag ;
	while(ptr2!=NULL)
	{
		flag=1;
		Node3* ptr3 = ptr2->student_group;
		while(ptr3!=NULL)
		{
			if(strcmp(ptr3->status , "Evaluated") != 0)
			{
				flag = 0;   // Not Evaluated
				break;
			}
			ptr3 = ptr3->next;
		}
		if(flag == 1)
		{
			strcpy(ptr2->status , "Evaluated");
			break;
		}
		ptr2 = ptr2->next;
	}
}









void change_status_asg_duedate(Node2* assignment[] , int asg_id)
{
	int key = hashcode(asg_id);
	Node2* ptr = assignment[key];
	
	while(ptr!=NULL)
	{
		if(ptr->assignment_id == asg_id)
		{
			strcpy(ptr->status , "DueDateOver");
			break;
		}
		ptr = ptr->next;
	}
	
	Node2* ptr2 = assignment[key];
	while(ptr2!=NULL)
	{
		int flag=1;
		Node3* ptr3 = ptr2->student_group;
		while(ptr3!=NULL)
		{
			if(strcmp(ptr3->status , "Evaluated") != 0)
			{
				flag = 0;   // Not Evaluated
				break;
			}
			ptr3 = ptr3->next;
		}
		if(flag == 1)
		{
			strcpy(ptr2->status , "Evaluated");
			break;
		}
		ptr2 = ptr2->next;
	}
}






/////Question 4 ------------------------>>>

void print_declared_not_eval(Node2* assignment[])
{
	int i;
	for(i=0;i<10;i++)
	{
		Node2* ptr = assignment[i];
		while(ptr!=NULL)
		{
			if(strcmp(ptr->status , "Evaluated") != 0 && strcmp(ptr->status , "DueDateOver") !=0)
			{
				printf("\nAssignment id : %d\n",ptr->assignment_id);
				printf("Topic Name : %s\n",ptr->topic_name);
				printf("Status : %s\n",ptr->status);
				printf("-----------\n");
			}
			ptr = ptr->next;
		}
	}
}






/////Question 5 ------------------------->>>

void print_stud_not_submitted(Node2* assignment[] , Node1* student[])
{
	int i;
	for(i=0;i<10;i++)
	{
		Node2* ptr = assignment[i];	
		while(ptr!=NULL)
		{
			int found = 0;
			if(strcmp(ptr->status , "DueDateOver") == 0)
			{
				printf("\nAssignment id : %d\n",ptr->assignment_id);
				printf("Topic Name : %s\n",ptr->topic_name);
				printf("Status : %s\n\n",ptr->status);
				
				Node3* ptr2 = ptr->student_group;
				while(ptr2!=NULL)
				{
					if(strcmp(ptr2->status , "NotSubmitted") == 0)
					{
						int key = hashcode(ptr2->student_group_id);
						Node1* ptr3 = student[key];
						while(ptr3!=NULL)
						{
							if(ptr3->group_id == ptr2->student_group_id)
							{
								printf("		Group id : %d\n",ptr2->student_group_id);
								printf("		Member 1 : %s\n",ptr3->name);
								printf("		Member 2 : %s\n\n",ptr3->group_partner);
								found = 1;
								break;
							}
							ptr3 = ptr3->next;
						}	
					}
					ptr2 = ptr2->next;
				}
				if(found == 0)
				{
					printf("		No One\n\n");
				}
				printf("------------\n\n");
			}
			ptr = ptr->next;
		}
	}
}






/////Question 6 ------------------------->>>

void print_stud_notEval_sub(Node1* student[])
{
	int i;
	for(i=0;i<10;i++)
	{
		Node1* ptr = student[i];
		while(ptr!=NULL)
		{
			if(strcmp(ptr->status , "Submitted") == 0)
			{
				printf("\nGroup id : %d\n",ptr->group_id);
				printf("Assignment Topic : %s\n",ptr->assignment_name_id);
				printf("Member 1 : %s\n",ptr->name);
				printf("Member 2 : %s\n",ptr->group_partner);
				printf("Submitted but not Evaluated\n\n\n");
			}
			if(strcmp(ptr->status , "Evaluated") == 0)
			{
				if(ptr->viva_marks == 0)
				{
					printf("Group id : %d\n",ptr->group_id);
					printf("Assignment Topic : %s\n",ptr->assignment_name_id);
					printf("Member 1 : %s\n",ptr->name);
					printf("Member 2 : %s\n",ptr->group_partner);
					printf("Evaluated but Viva is Not Yet Completed\n\n\n");
				}
			}
			ptr = ptr->next->next;
		}
	}
}








/////Question 7 ------------------------->>>

void BubbleSort(Node3* lptr)
{
	Node3* ptr = lptr;
	Node3* ptr1 = NULL;
	int sorted = 0;
	while(sorted == 0)
	{
		ptr = lptr;
		sorted = 1;
		while(ptr->next!=ptr1)
		{
			if(ptr->marks_given < ptr->next->marks_given)
			{
				int a = ptr->marks_given;
				ptr->marks_given = ptr->next->marks_given;
				ptr->next->marks_given = a;
				
				a = ptr->student_group_id;
				ptr->student_group_id = ptr->next->student_group_id;
				ptr->next->student_group_id = a;
				
				char str[MAX_LEN];
				strcpy(str , ptr->status);
				strcpy(ptr->status , ptr->next->status);
				strcpy(ptr->next->status , str);
				
				sorted = 0;
			}
			ptr = ptr->next;
		}
		ptr1 = ptr;
	}
}


void print_dec_order(Node2* assignment[] , int assignment_id)
{
	int key = hashcode(assignment_id);
	Node2* ptr = assignment[key];
	while(ptr!=NULL)
	{
		if(ptr->assignment_id == assignment_id)
		{
			printf("\nAssignment id : %d\n",ptr->assignment_id);
			printf("Topic Name    : %s\n",ptr->topic_name);
			Node3* ptr1 = ptr->student_group;
			BubbleSort(ptr1);
			
			while(ptr1!=NULL)
			{
				printf("		Group id : %d\n",ptr1->student_group_id);
				printf("		Marks Given : %f\n\n\n",ptr1->marks_given);
				ptr1 = ptr1->next;
			}
			break;
		}
		ptr = ptr->next;
	}
}







/////Question 8 -------------------------->>>

void print_top_stud(Node2* assignment[])
{
	int i;
	for(i=0;i<10;i++)
	{
		Node2* ptr = assignment[i];
		while(ptr!=NULL)
		{
			printf("\nAssignment id : %d\n",ptr->assignment_id);
			printf("Topic Name : %s\n",ptr->topic_name);
			Node3* ptr1 = ptr->student_group;
			BubbleSort(ptr1);
			printf("		Group id : %d\n",ptr1->student_group_id);
			printf("		Top Marks Given : %f\n\n\n",ptr1->marks_given);
			
			ptr = ptr->next;
		}
	}
}







////Display Marks of a student ----------------->>>

void Display_Marks(char* name , int group_id)
{
	int key = hashcode(group_id);
	Node1* ptr = student[key];
	while(ptr!=NULL)
	{
		if(strcmp(ptr->name , name) == 0)
		{
			printf("\nPrinting your Marks  : \n");
			printf("Group id         : %d\n",ptr->group_id);
			printf("Assignment Topic : %s\n",ptr->assignment_name_id);
			printf("Name             : %s\n",ptr->name);
			printf("Status            : %s\n",ptr->status);
			if(ptr->status == "NotSubmitted")
			{
				printf("Assignment Not Submitted yet\n\n");
			}
			else if(strcmp(ptr->status , "Submitted")==0)
			{
				printf("Assignment Submitted but not evaluated yet\n\n");
			}
			else
			{
				printf("Offline Marks    : %f\n",ptr->offline_marks);
				printf("Viva Marks       : %f\n\n",ptr->viva_marks);
			}
		}
		ptr = ptr->next;
	}
}






/////Display Group Details ----------------------->>>

void Display_grp_details(int group_id)
{
	int key = hashcode(group_id);
	Node1* ptr = student[key];
	//printf("1\n");
	while(ptr!=NULL)
	{
		//printf("%d\n",ptr->group_id);
		if(ptr->group_id == group_id)
		{
			//printf("3\n");
			printf("\nPrinting Group Details ------> \n");
			printf("Group id              : %d\n",ptr->group_id);
			printf("Assignment Topic      : %s\n",ptr->assignment_name_id);
			printf("Member 1 		      : %s\n",ptr->name);
			printf("Member2               : %s\n",ptr->group_partner);
			printf("Status                : %s\n\n",ptr->status);
			
			break;
		}
		ptr = ptr->next;
	}
}








////Print student records ------------------------>>>>

void print_stud_rec(Node1* student[])
{
	int i;
	for(i=0;i<10;i++)
	{
		Node1* ptr = student[i];
		while(ptr!=NULL)
		{
			printf("\nStudent id      : %d\n",ptr->student_id);
			printf("Name            : %s\n",ptr->name);
			printf("Partner Name    : %s\n",ptr->group_partner);
			printf("Group id        : %d\n",ptr->group_id);
			printf("Assignment Name : %s\n",ptr->assignment_name_id);
			printf("Deadline        : %s\n",ptr->deadline);
			printf("Status          : %s\n",ptr->status);
			printf("Offline marks   : %f\n",ptr->offline_marks);
			printf("Viva Marks      : %f\n",ptr->viva_marks);
			printf("---------------\n");
			
			ptr = ptr->next;
		}
	}
}







///// Print Assignment records --------------->>>>

void print_asg_rec(Node2* assignment[])
{
	int i;
	for(i=0;i<10;i++)
	{
		Node2* ptr = assignment[i];
		while(ptr!=NULL)
		{
			
			printf("\nAssignment id  : %d\n",ptr->assignment_id);
			printf("Topic Name     : %s\n",ptr->topic_name);
			printf("Status         : %s\n\n",ptr->status );
			
			Node3* nptr = ptr->student_group;
			while(nptr!=NULL)
			{
				printf("		Group id    : %d\n",nptr->student_group_id );
				printf("		Status      : %s\n",nptr->status);
				printf("		Marks Given : %f\n\n",nptr->marks_given);
				
				nptr = nptr->next;
			}
			printf("----------------------------------\n");
			ptr = ptr->next;
		}
	}
}







int main()
{
	initialise();
	FILE *fp;
    fp = fopen("input.txt", "r");

    if (fp == NULL)
    {
        printf("Can't open file for reading.\n");
        return 0;
    }
	do
	{
		int a;
		printf("Choose the correct choice :\n");
		printf("1. Student\n");
		printf("2. Teacher\n");
		printf("3. Exit Program\n");
		//printf("Enter your choice : ");
		//scanf("%d",&a);
		fscanf(fp, "%d", &a);
		if(a==3)
		{
			break;
		}
		switch(a)
		{
			char name[MAX_LEN] ;
			int password ,found;
			Node1* ptr;
			int key;
			case 1 :
			{
				printf("You choose 1 \n\n");
				printf("------------------Students Portal-------------------\n");
				found = 0;
//				printf("Enter your Name : ");
//				scanf("%s",name);
//				printf("Enter your Password (Password is same as of your grp_id) : ");
//				scanf("%d",&password);
				fscanf(fp,"%s",name);
				fscanf(fp,"%d",&password);
				//printf("%s %d",name,password);
				
				key = hashcode(password);
				ptr = student[key];
				while(ptr!=NULL)
				{
					if(ptr->group_id == password && strcmp(ptr->name,name)==0)
					{
						printf("Validated\n");
						found = 1;
						do
						{
							int b;
							printf("Choose the correct choice :\n");
							printf("1. Display your Marks\n");
							printf("2. Display your Group Details\n");
							printf("3. Exit this block\n\n");
							printf("Enter your choice : ");
							fscanf(fp,"%d",&b);
							if(b==3)
							{
								printf("Exiting this block\n\n");
								break;
							}
							switch(b)
							{
								int id;
								case 1 :
									printf("You choose 1 \n\n");
									//printf("Enter your Group id : ");
									//scanf("%d",&id);
									Display_Marks(name , password);
									//printf("Hi\n");
									break;
								case 2 :
									printf("You choose 2 \n\n");
									Display_grp_details(password);
									
									break;
								default : 
									printf("Invalid Choice\n");	
									break;
							}
						}while(1);
						break;
					}
					ptr = ptr->next;
					if(found == 0)
					{
						printf("Password is Wrong / User not Found\n\n");
					}
				}
				break;
			}
			char name2[MAX_LEN] ;
			char password1[MAX_LEN] ;
			case 2 :
			{
				printf("You choose 2 \n\n");
				printf("------------------Teachers Portal-------------------\n");
				//printf("Enter your Name : ");
				//scanf("%s",name2);
				fscanf(fp, "%s %s", name2, password1);
				//printf("%s\n",name2);
				//printf("Enter your Password (all small letters) : ");
				//scanf("%s",password1);
				//printf("%s\n",password1);
				//printf("Hi");
				if(strcmp(name2, "Keskar") == 0 && strcmp(password1, "keskar") == 0 )
				{
					printf("Validated\n");
					do
					{
						int b;
						printf("Choose the correct choice :\n");
						printf("1. Insert Student Record\n");
						printf("2. Insert Assignment\n");
						printf("3. Change Status\n");
						printf("4. Print List of Assignments declared but not Evaluated\n");
						printf("5. Print the list student groups who have not submitted the assignments even if the due-date is over. \n");
						printf("6. Print the list of student groups for whom the assignment is yet-to-be-evaluated even though they have been submitted.\n");
						printf("7. Print the details of student-groups, in the decreasing order of marks for a particular assignment\n");
						printf("8. Print student groups receiving top marks in each of the assignment given.\n");
						printf("9. Exit this Block\n\n");
 						printf("Enter your choice : ");
						//scanf("%d",&b);
						fscanf(fp, "%d", &b);
						if(b==9)
						{
							printf("Exiting this block\n\n");
							break;
						}
						switch(b)
						{
							int c,d,h,o;
							char e[MAX_LEN],f[MAX_LEN],g[MAX_LEN],i[MAX_LEN],j[MAX_LEN];
							float k,l,m,n;
							case 1 :
							{
								printf("Inserting student record-------->\n");
								printf("Enter the both student ids and names : ");
								fscanf(fp,"%d %d %s %s",&c,&d,e,f);
								printf("\nEnter group id : ");
								fscanf(fp,"%d",&o);
								printf("\nEnter asg name and id");
								fscanf(fp,"%s %d",g,&h);
								printf("\nEnter deadline and status : ");
								fscanf(fp,"%s %s",i,j);
	    						printf("\nEnter offline and viva marks of both students : ");
								fscanf(fp,"%f %f %f %f",&k,&l,&m,&n);
								
								insert_student(student,c,d,e,f,o,g,i,j,k,l,m,n,h);
								print_stud_rec(student);
								break;
							}
							int num,p,asg_id;
							char deadline[MAX_LEN] ; 
							char topic_name[MAX_LEN];
							int stud_id[100];
							int grp_id[100];
							char name[100][MAX_LEN];
							char status[100][MAX_LEN];
							float off_marks[100] ;
							float viva_marks[100];
							char *name_pointers[100];
							char *status_pointers[100];
							case 2 :
							{
								printf("Inserting Assignment record---------->\n");
								printf("Enter Assignment id , Topic name and deadline respectively : ");
								fscanf(fp,"%d %s %s",&asg_id,topic_name,deadline);
								
								printf("Enter number of students : ");
								fscanf(fp,"%d",&num);
								//char* topic_name , int assignment_id , int* student_id , char** name , int* group_id , char* deadline , char** status , float* offline_marks , float* viva_marks , int num_stud
								for(p=0;p<num;p++)
								{
									printf("Enter student id , Name , Group Id , Status , Offline and viva marks respectively : \n");
									fscanf(fp,"%d %s %d %s %f %f",&stud_id[p],name[p],&grp_id[p],status[p],&off_marks[p],&viva_marks[p]);
									name_pointers[p]=name[p];
									status_pointers[p]=status[p];
								}
								
								insert_assignment(student , assignment ,topic_name, asg_id,stud_id,name_pointers,grp_id,deadline,status_pointers,off_marks,viva_marks,num);
								printf("-----\n");
								print_stud_rec(student);
								printf("-----\n");
								print_asg_rec(assignment);
								break;
							}
							int group_id,assig_id;
							char stat[MAX_LEN];
							float m1,m2,m3,m4;
							case 3 :
							{
								printf("Changing status of a group ----------->\n");
								printf("Enter the group id , Assignment id and status : ");
								fscanf(fp,"%d %d %s",&group_id,&assig_id,stat);
								//printf("%d %s",group_id,stat);
								if(strcmp(stat , "Evaluated") != 0)
								{
									change_status(student,assignment,group_id,stat,0,0,0,0,assig_id);
								}
								else if(strcmp(stat , "Evaluated") == 0 )
								{
									printf("Enter offline and viva marks of both students respectively : ");
									fscanf(fp,"%f %f %f %f",&m1,&m2,&m3,&m4);
									//printf("%f %f %f %f",m1,m2,m3,m4);
									change_status(student,assignment,group_id,stat,m1,m2,m3,m4,assig_id);
								}
								printf("-----\n");
								print_stud_rec(student);
								printf("-----\n");
								print_asg_rec(assignment);
								
								change_status_asg_duedate(assignment ,  assig_id);
								printf("-----\n");
								print_asg_rec(assignment);
								
								break;
							}
							case 4 :
							{
								printf("Printing List of Assignments declared but not evaluated--------->\n");
								print_declared_not_eval(assignment);
								break;
							}
							case 5 :
							{
								printf("Printing the list student groups who have not submitted the assignments even if the due-date is over.\n");
								print_stud_not_submitted(assignment , student);
								break;
							}
							case 6 :
							{
								printf(" Printing the list of student groups for whom the assignment is yet-to-be-evaluated even though they have been submitted.\n");
								print_stud_notEval_sub(student);
								break;
							}
							int assignment_id;
							case 7 :
							{
								printf("Printing the details of student-groups, in the decreasing order of marks for a particular assignment\n");
								printf("Enter Assignment id : ");
								fscanf(fp,"%d",&assignment_id);
								print_dec_order(assignment , assignment_id);
								break;
							}
							case 8 :
							{
								printf("Printing student groups receiving top marks in each of the assignment given.\n");
								print_top_stud(assignment);
								break;
							}
							case 9 :
							{
								break;
							}
							default :
							{
								printf("Enter valid Number \n");
								break;
							}
						}
					}while(1);
				}
				else
				{
					printf("Incorrect Password\n");
					exit(0);
				}
				break;
			}
			case 3 :
				break;
			default :
				printf("Enter Valid Number\n\n");	
				break;		
		}
	}while(1);
	fclose(fp);
	return 0;
}



