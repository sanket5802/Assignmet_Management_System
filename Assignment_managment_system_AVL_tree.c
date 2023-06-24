#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LEN 50

struct student
{
	int student_id;
	char name[MAX_LEN];
	char group_partner[MAX_LEN];
	int group_id;
	char assignment_name_id[MAX_LEN];
	char deadline[MAX_LEN];
	int assignment_id;
	char status[MAX_LEN];
	float offline_marks;
	float viva_marks;
	int height;
	struct student *left;
	struct student *right;
} *stu_node = NULL;

struct StudentAssignmentRecord
{
	int student_group_id;
	char status[MAX_LEN];
	float marks_given;
	int height;
	struct StudentAssignmentRecord *left;
	struct StudentAssignmentRecord *right;

} *stu_asg_node = NULL;

struct assignment_record//2nds struct
{
	int assignment_id;
	char topic_name[MAX_LEN];
	char status[MAX_LEN];
	int height;
	struct assignment_record *left;
	struct assignment_record *right;
	struct StudentAssignmentRecord *student_group;
} *asg_rec = NULL;

struct StudentAssignmentRecord *assignmetrecordarray[100];



int max(int a, int b)
{
	return (a > b) ? a : b;
}

struct student *insert_student(int student_id, char *name, char *group_partner, int group_id,
							   char *assignment_name_id, char *deadline,
							   char *status, float offline_marks, float viva_marks, int assignment_id)
{

	struct student *nptr = (struct student *)malloc(sizeof(struct student));
	nptr->student_id = student_id;
	strcpy(nptr->name, name);
	strcpy(nptr->group_partner, group_partner);
	nptr->group_id = group_id;
	strcpy(nptr->assignment_name_id, assignment_name_id);
	strcpy(nptr->deadline, deadline);
	strcpy(nptr->status, status);
	nptr->offline_marks = offline_marks;
	nptr->viva_marks = viva_marks;
	nptr->left = NULL;
	nptr->right = NULL;
	nptr->height = 1;
	nptr->assignment_id = assignment_id;
	return nptr;
}
struct assignment_record *insert_assignment(int assignment_id, char *topic_name, char *status)
{
	struct assignment_record *a = (struct assignment_record *)malloc(sizeof(struct assignment_record));
	a->assignment_id = assignment_id;
	strcpy(a->status, status);
	strcpy(a->topic_name, topic_name);

	a->student_group = NULL;
	a->left = NULL;
	a->right = NULL;
	a->height = 1;

	return a;
}

struct StudentAssignmentRecord *insert_StudentAssignmentRecord(int student_group_id, char *status, float marks_given)
{
	struct StudentAssignmentRecord *a = (struct StudentAssignmentRecord *)malloc(sizeof(struct StudentAssignmentRecord));
	a->student_group_id = student_group_id;
	strcpy(a->status, status);
	a->marks_given = marks_given;
	a->height = 1;
	a->left = NULL;
	a->right = NULL;
	return a;
}

// 1

int height_node1(struct student *N)
{
	if (N == NULL)
		return 0;
	return N->height;
}

// Get Balance factor of node N
int getbalance_node1(struct student *N)
{
	if (N == NULL)
		return 0;
	return height_node1(N->left) - height_node1(N->right);
}

// A utility function to right rotate subtree rooted with y
// See the diagram given above.
struct student *rightroate_node1(struct student *y)
{
	struct student *x = y->left;
	struct student *T2 = x->right;

	// Perform rotation
	x->right = y;
	y->left = T2;

	// Update heights
	y->height = max(height_node1(y->left),
					height_node1(y->right)) +
				1;
	x->height = max(height_node1(x->left),
					height_node1(x->right)) +
				1;

	// Return new root
	return x;
}

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
struct student *leftrotate_node1(struct student *x)
{
	struct student *y = x->right;
	struct student *T2 = y->left;

	// Perform rotation
	y->left = x;
	x->right = T2;

	//  Update heights
	x->height = max(height_node1(x->left),
					height_node1(x->right)) +
				1;
	y->height = max(height_node1(y->left),
					height_node1(y->right)) +
				1;

	// Return new root
	return y;
}

// 2

int height_node2(struct assignment_record *N)
{
	if (N == NULL)
		return 0;
	return N->height;
}

// Get Balance factor of node N
int getbalance_node2(struct assignment_record *N)
{
	if (N == NULL)
		return 0;
	return height_node2(N->left) - height_node2(N->right);
}

// A utility function to right rotate subtree rooted with y
// See the diagram given above.
struct assignment_record *rightroate_node2(struct assignment_record *y)
{
	struct assignment_record *x = y->left;
	struct assignment_record *T2 = x->right;

	// Perform rotation
	x->right = y;
	y->left = T2;

	// Update heights
	y->height = max(height_node2(y->left),
					height_node2(y->right)) +
				1;
	x->height = max(height_node2(x->left),
					height_node2(x->right)) +
				1;

	// Return new root
	return x;
}

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
struct assignment_record *leftrotate_node2(struct assignment_record *x)
{
	struct assignment_record *y = x->right;
	struct assignment_record *T2 = y->left;

	// Perform rotation
	y->left = x;
	x->right = T2;

	//  Update heights
	x->height = max(height_node2(x->left),
					height_node2(x->right)) +
				1;
	y->height = max(height_node2(y->left),
					height_node2(y->right)) +
				1;

	// Return new root
	return y;
}

// 3

int height_node3(struct StudentAssignmentRecord *N)
{
	if (N == NULL)
		return 0;
	return N->height;
}

// Get Balance factor of node N
int getBalance(struct StudentAssignmentRecord *N)
{
	if (N == NULL)
		return 0;
	return height_node3(N->left) - height_node3(N->right);
}

// A utility function to right rotate subtree rooted with y
// See the diagram given above.
struct StudentAssignmentRecord *rightroate_node3(struct StudentAssignmentRecord *y)
{
	struct StudentAssignmentRecord *x = y->left;
	struct StudentAssignmentRecord *T2 = x->right;

	// Perform rotation
	x->right = y;
	y->left = T2;

	// Update heights
	y->height = max(height_node3(y->left),
					height_node3(y->right)) +
				1;
	x->height = max(height_node3(x->left),
					height_node3(x->right)) +
				1;

	// Return new root
	return x;
}

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
struct StudentAssignmentRecord *leftrotate_node3(struct StudentAssignmentRecord *x)
{
	struct StudentAssignmentRecord *y = x->right;
	struct StudentAssignmentRecord *T2 = y->left;

	// Perform rotation
	y->left = x;
	x->right = T2;

	//  Update heights
	x->height = max(height_node3(x->left),
					height_node3(x->right)) +
				1;
	y->height = max(height_node3(y->left),
					height_node3(y->right)) +
				1;

	// Return new root
	return y;
}
int getbalance_node3(struct StudentAssignmentRecord *N)
{
	if (N == NULL)
		return 0;
	return height_node3(N->left) - height_node3(N->right);
}

// 3
struct student *reversstudent(struct student *p, int student_id, char *name, char *group_partner, int group_id, char *assignment_name_id,
							  char *deadline, char *status, float offline_marks, float viva_marks, int assignment_id)
{

	struct student *t = NULL;

	if (p == NULL)
	{
		t = insert_student(student_id, name, group_partner, group_id, assignment_name_id,
						   deadline, status, offline_marks, viva_marks, assignment_id);
		return t;
	}

	if (assignment_id < p->assignment_id)
	{
		p->left = reversstudent(p->left, student_id, name, group_partner, group_id, assignment_name_id,
								deadline, status, offline_marks, viva_marks, assignment_id);
	}
	else if (assignment_id > p->assignment_id)
	{
		p->right = reversstudent(p->right, student_id, name, group_partner, group_id, assignment_name_id,
								 deadline, status, offline_marks, viva_marks, assignment_id);
	}
	p->height = 1 + max(height_node1(p->left), height_node1(p->right));

	int balance = getbalance_node1(p);

	if (balance > 1 && assignment_id < p->left->assignment_id)
	{
		return rightroate_node1(p);
	}
	if (balance < -1 && assignment_id > p->right->assignment_id)
	{
		return leftrotate_node1(p);
	}

	if (balance > 1 && assignment_id > p->left->assignment_id)
	{
		p->left = leftrotate_node1(p->left);
		return rightroate_node1(p);
	}


	if (balance < -1 && assignment_id < p->right->assignment_id)
	{
		p->right = rightroate_node1(p->right);
		return leftrotate_node1(p);
	}
	return p;
}

struct assignment_record *reverse_assignment_record(struct assignment_record *p, char *topic_name, int assignment_id, char *status)
{

	struct assignment_record *t = NULL;

	if (p == NULL)
	{
		t = insert_assignment(assignment_id, topic_name, status);
		return t;
	}

	if (assignment_id < p->assignment_id)
	{
		p->left = reverse_assignment_record(p->left, topic_name, assignment_id, status);
	}
	else if (assignment_id > p->assignment_id)
	{
		p->right = reverse_assignment_record(p->right, topic_name, assignment_id, status);
	}
	p->height = 1 + max(height_node2(p->left), height_node2(p->right));

	int balance = getbalance_node2(p);

	if (balance > 1 && assignment_id < p->left->assignment_id)
	{
		return rightroate_node2(p);
	}
	if (balance < -1 && assignment_id > p->right->assignment_id)
	{
		return leftrotate_node2(p);
	}
    
    if (balance > 1 && assignment_id > p->left->assignment_id)
	{
		p->left = leftrotate_node2(p->left);
		return rightroate_node2(p);
	}


	if (balance < -1 && assignment_id < p->right->assignment_id)
	{
		p->right = rightroate_node2(p->right);
		return leftrotate_node2(p);
	}
	return p;
}
//

struct StudentAssignmentRecord *reveseStudentAssignmentRecord(struct StudentAssignmentRecord *p, int student_group_id, char *status, float marks_given)
{

	struct StudentAssignmentRecord *t = NULL;

	if (p == NULL)
	{
		t = insert_StudentAssignmentRecord(student_group_id, status, marks_given);
		return t;
	}

	if (marks_given < p->marks_given)
	{
		p->left = reveseStudentAssignmentRecord(p->left, student_group_id, status, marks_given);
	}
	else if (marks_given > p->marks_given)
	{
		p->right = reveseStudentAssignmentRecord(p->right, student_group_id, status, marks_given);
	}
	p->height = 1 + max(height_node3(p->left), height_node3(p->right));

	int balance = getbalance_node3(p);

	if (balance > 1 && marks_given < p->left->marks_given)
	{
		return rightroate_node3(p);
	}
	if (balance < -1 && marks_given > p->right->marks_given)
	{
		return leftrotate_node3(p);
	}
     if (balance > 1 && marks_given > p->left->marks_given)
	{
		p->left = leftrotate_node3(p->left);
		return rightroate_node3(p);
	}

	if (balance < -1 && marks_given < p->right->marks_given)
	{
		p->right = rightroate_node3(p->right);
		return leftrotate_node3(p);
	}
	return p;
}
//

void preorderstudent(struct student *p)
{

	if (p)
	{

		printf("Student id      : %d\n", p->student_id);
		printf("Name            : %s\n", p->name);
		printf("Partner Name    : %s\n", p->group_partner);
		printf("Group id        : %d\n", p->group_id);
		printf("Assignment Name : %s\n", p->assignment_name_id);
		printf("Assignemt id =  : %d\n", p->assignment_id);
		printf("Deadline        : %s\n", p->deadline);
		printf("Offline marks   : %f\n", p->offline_marks);
		printf("Viva Marks      : %f\n", p->viva_marks);
		printf("---------------\n");
		preorderstudent(p->left);
		preorderstudent(p->right);
	}
}
void prorderassignemt(struct assignment_record *p)
{
	if (p)
	{
		printf("assignemt id : %d\n", p->assignment_id);
		printf("topic name  :%s\n", p->topic_name);
		printf("status : %s\n", p->status);
		prorderassignemt(p->left);
		prorderassignemt(p->right);
	}
}

void preoderstudentassignemt(struct StudentAssignmentRecord *p)
{
	if (p)
	{

		preoderstudentassignemt(p->left);
		printf("   group id =           %d  \n", p->student_group_id);
		printf("   total marks carry =  %f  \n", p->marks_given);
		printf("   status of assigment = %s \n", p->status);
		preoderstudentassignemt(p->right);
	}
}
void inoderstudentassignemt(struct StudentAssignmentRecord *p)
{
	if (p)
	{

		inoderstudentassignemt(p->right);
		printf("   group id           =  %d  \n", p->student_group_id);
		printf("   total marks carry =  %f  \n", p->marks_given);
		printf("   status of assigment = %s \n", p->status);
		inoderstudentassignemt(p->left);
	}
}

struct assignment_record *search_assignment(struct assignment_record *p, int key)
{
	if (p == NULL || p->assignment_id == key)
	{
		return p;
	}
	if (p->assignment_id < key)
	{
		return search_assignment(p->right, key);
	}

	return search_assignment(p->left, key);
}

struct StudentAssignmentRecord *search_assignment_record(struct StudentAssignmentRecord *p, int key)
{
	if (p == NULL || p->student_group_id == key)
	{
		return p;
	}
	if (p->student_group_id < key)
	{
		return search_assignment_record(p->right, key);
	}

	return search_assignment_record(p->left, key);
}

struct student *search_student(struct student *p, int key)
{
	if (p == NULL || p->group_id == key)
	{
		return p;
	}
	if (p->group_id < key)
	{
		return search_student(p->right, key);
	}

	return search_student(p->left, key);
}

void status_manager(struct StudentAssignmentRecord *p)
{
	if (p)
	{ 
	    float viva_mks , offline_mks;	
		int key = p->student_group_id;

		//struct student *changer = search_student(stu_node ,key);
		printf("enter the viva and offline marks of the student associted with group id %d \n", p->student_group_id);
		scanf("%f%f", &viva_mks, &offline_mks);
		strcpy(p->status, "evaluated");
		//strcpy(changer->status, "evaluated");
		p->marks_given = offline_mks + viva_mks;
		//changer->offline_marks = offline_mks;
		//changer->viva_marks = viva_mks;
		status_manager(p->left);
		status_manager(p->right);
	}
} // q3

void change_status(struct student *stu, struct assignment_record *asg)
{
	int num;
	printf("Q3(1) = change the status of group \n");
	printf("Q3(2) =  change the status of entire assignemt node \n");
	scanf("%d", &num);
	int gp_id;
	int t;
	int x;
	float offline, viva;
	float viva_mak, offline_mak;
	switch (num)
	{

	case 1:
		printf("enter the assignement id for changing status\n");
		printf("enter group id \n");

		scanf("%d", &t);
		scanf("%d", &gp_id);
		struct assignment_record *a = search_assignment(asg_rec, t); // t=asg id
		struct StudentAssignmentRecord *ptr = a->student_group;

		ptr = search_assignment_record(ptr, gp_id);
        struct student *chan = search_student(stu_node, gp_id);
		char str[20];
		printf("enter the status of the assignemt \n");
		scanf("%s", str);
		if (strcmp(str, "evaluated") == 0) // its for submitted , declared once
		{								   // provide the marks of student

			printf("enter the viva and offline marks of the group\n");

			scanf("%f", &viva);
			scanf("%f", &offline);
			strcpy(ptr->status, "evaluated");
			ptr->marks_given = viva + offline;
		    
			//strcpy(chan->status, "evaluated");
			chan->offline_marks = offline;
			chan->viva_marks = viva;
			ptr->marks_given = offline + viva;
		}
		else if (strcmp(str, "duedateover") == 0)
		{
			strcpy(ptr->status, "duedateover");
			printf("These students will recieve penaty of 2 marks for late submission\n");

			scanf("%f", &viva_mak);
			scanf("%f", &offline_mak);
			ptr->marks_given = viva_mak + offline_mak - 2;
			struct student *chi = search_student(stu_node, gp_id);
			//strcpy(chi->status, "evaluated");
			chi->offline_marks = offline_mak;
			chi->viva_marks = viva_mak;
		}
		else if (strcmp(str, "submitted") == 0) // its for declared once
		{
			strcpy(ptr->status, "submitted");
			ptr->marks_given = 0;
			struct student *submit = search_student(stu_node, gp_id);
			//strcpy(submit->status, "submitted");
			submit->offline_marks = 0;
			submit->viva_marks = 0;
		}
		break;

		case 2:
		
			//  case 2:
			printf("enter the assignement id for changing status\n");
			scanf("%d", &x);
			struct assignment_record *q = search_assignment(asg_rec, x); // t=asg id
		
			struct StudentAssignmentRecord *pt = q->student_group;
			status_manager(pt);
			strcpy(q->status , "submitted");
			break;
		
	}
}
// q4 Print the details of assignments that are declared but not evaluated.
void printf_declared_not_evaluated(struct assignment_record *p)
{
	if (p)
	{
		if (strcmp(p->status, "declared") == 0) // students submitted == declared
		{
			printf("assignemt id = %d", p->assignment_id);
			printf("topic name = %s", p->topic_name);
			printf("status = %s", p->status);
			printf("\n");
		}
		printf_declared_not_evaluated(p->left);
		printf_declared_not_evaluated(p->right);
	}
}
// q5 Print the details of student groups who have not submitted the assignments even if the
// due-date is over.
void printf_group_not_submitted(struct StudentAssignmentRecord *p)
{
	if (p)
	{

		printf_group_not_submitted(p->left);
		if (strcmp(p->status, "duedateover") == 0)
		{
			printf("   group id =           %d  \n", p->student_group_id);
			printf("   total marks carry =  %f  \n", p->marks_given);
			printf("   status of assigment = %s \n", p->status);
			printf("\n");
		}
		printf_group_not_submitted(p->right);
	}
} // q5

void student_grp_not_evaluated(struct assignment_record *p)
{

	printf("enter the assigment id \n");
	int num;
	scanf("%d", &num);
	struct assignment_record *ptr = search_assignment(asg_rec, num);
	struct StudentAssignmentRecord *q = ptr->student_group;

	printf_group_not_submitted(q);

	printf("\n");
	//  }
}

// q6
void printf_group_submitted(struct StudentAssignmentRecord *p)
{
	if (p)
	{

		printf_group_submitted(p->left);
		if (strcmp(p->status, "submitted") == 0)
		{
			printf("   group id =           %d  \n", p->student_group_id);
			printf("   total marks carry =  %f  \n", p->marks_given);
			printf("   status of assigment = %s \n", p->status);
			printf("\n");
		}
		printf_group_submitted(p->right);
	}
}
void printf_grp_not_eval(struct assignment_record *p)
{
	printf("enter the assigment id \n");
	int num;
	scanf("%d", &num);
	struct assignment_record *ptr = search_assignment(asg_rec, num);
	struct StudentAssignmentRecord *q = ptr->student_group;
	printf_group_submitted(q);
}
// Q7
void print_decreasing(struct assignment_record *p)
{
	printf("Enter the assignment id which you need to sort");
	int num;
	scanf("%d", &num);
	struct assignment_record *ptr = search_assignment(asg_rec, num);
	struct StudentAssignmentRecord *q = ptr->student_group;
	inoderstudentassignemt(q);
}

void printtop(struct StudentAssignmentRecord *q)
{
	while (q->right != NULL)
	{
		q = q->right;
	}
	printf(" Max marks is %f\n", q->marks_given);
}

// q8
void top_marks(struct assignment_record *p)
{
	if (p == NULL)
	{
		return;
	}
	printf("the asg id is %d\n", p->assignment_id);
	printtop(p->student_group);
	top_marks(p->left);
	top_marks(p->right);
} // q9
void range_preorder_search(struct assignment_record *p, int asg_id1, int asg_id2)
{
	if (p)
	{
		if (p->assignment_id <= asg_id2 && p->assignment_id >= asg_id1)
		{
			printf("  topic name = %s\n", p->topic_name);
			printf("  assignemt id = %d\n", p->assignment_id);
			printf("  status = %s\n", p->status);
		}
		range_preorder_search(p->left, asg_id1, asg_id2);
		range_preorder_search(p->right, asg_id1, asg_id2);
	}
}

void range_search(struct assignment_record *p)
{
	int asg_id1;
	int asg_id2;
	printf("enter the assignment ids \n");
	scanf("%d%d", &asg_id1, &asg_id2);
	range_preorder_search(asg_rec, asg_id1, asg_id2);
	printf("\n");
}
int main()
{

	int password;
	char prof[20];
	// printf("enter the password and name \n");
	// scanf("%d", &password);
	// scanf("%s", prof);
	// if (password == 27734 && strcmp(prof, "keskar") == 0)
	// {
		int number;
		int num;
		int g;
		int hash[1000];

		for (int i = 0; i < 1000; i++)
		{
			hash[i] = 11;
		}
		do
		{
			printf("Q1 = Enter Student Details\n");
			printf("Q2 = Enter Assignemt details\n");
			printf("Q3 = change status\n");
			printf("Q4 = print assignemt declared but not evaluated\n");
			printf("Q5 = print studnet group who have not submitted the assignemt \n");
			printf("Q6 = print details of student whoes evaluation is not done even though assignemt is submitted\n");
			printf("Q7 = Print decreasing order of student details\n");
			printf("Q8= Print Top Marks in the Assignments\n");
			printf("Q9 = printf reverse serach\n");
			printf("Q10 = print assignemt student details\n");
			printf("Q11 = printf assignemt details\n");
			printf("Q12 = print studnet details\n");
			printf("Q13 = print student details\n");
			printf("Q12 = exit the code\n");
			scanf("%d", &num);
			int viva, offline;
			char statusofassignment[10];
			char deadline[10];
			char name[10];
			char partnername[10];
			int student_id;
			char assignmentname[10];
			int assignmentidofstudnet;
			int group_id;
			if (num == 12)
			{
				printf("program is exited\n");
				break;
			}
			int t;
			switch (num)
			{

			case 1:
				printf("\nENter student id \n");

				scanf("%d", &student_id);
				printf("\n Enter name of student and Partner\n");
				scanf("%s", name);
				scanf("%s", partnername);
				printf("\nEnter the Assignment Name\n");

				scanf("%s", assignmentname);
				printf("\nenter the deadline\n");

				scanf("%s", deadline);
				printf("Enter the status\n");

				scanf("%s", statusofassignment);
				printf("\nenter the viva and offline marks\n");

				scanf("%f%f", &viva, &offline);
				printf("\nEnter assignment id\n");

				scanf("%d", &assignmentidofstudnet);
				printf("\nenter group id\n");
				scanf("%d", &group_id);
				stu_node = reversstudent(stu_node, student_id, name, partnername, group_id, assignmentname, deadline, statusofassignment, viva, offline, assignmentidofstudnet);

				if (hash[assignmentidofstudnet] == 11) // call the assigment function
				{

					asg_rec = reverse_assignment_record(asg_rec, assignmentname, assignmentidofstudnet, statusofassignment);
					printf("given assignmet is not allocated to anyone\n");
					printf("Enter all groups which has %d Assignment id\n", assignmentidofstudnet);
					struct assignment_record *p = search_assignment(asg_rec, assignmentidofstudnet);

					do
					{
						printf("1 = enter the details of group\n");
						printf("2 = exit the code\n");
						int select;
						scanf("%d", &num);
						if (num == 2)
						{

							break;
						}
						switch (num)
						{
						case 1:

							printf("enter the group details\n");
							scanf("%d", &group_id);
							printf("enter status\n");
							scanf("%s", statusofassignment);
							printf("enter marks of assignmet\n");

							scanf("%d", &t);
							p->student_group = reveseStudentAssignmentRecord(p->student_group, group_id, statusofassignment, t);
							break;
						}

					} while (1);

					hash[assignmentidofstudnet] = -11;
				}
				break;

			case 2:

				printf("enter topic name\n");
				scanf("%s", assignmentname);
				printf("enter the assignment id of student\n");
				scanf("%d", &assignmentidofstudnet);
				printf("enter status of assignment\n");
				scanf("%s", statusofassignment);

				asg_rec = reverse_assignment_record(asg_rec, assignmentname, assignmentidofstudnet, statusofassignment);
				struct assignment_record *a = search_assignment(asg_rec, assignmentidofstudnet);
				printf("enter the group details for current assignemt node\n");
				do
				{
					printf("1 = enter the details of group\n");
					printf("2 = exit the code\n");
					int select;
					scanf("%d", &num);
					if (num == 2)
					{

						break;
					}
					switch (num)
					{
					case 1:

						printf("enter the group details\n");
						scanf("%d", &group_id);
						printf("enter status\n");
						scanf("%s", statusofassignment);
						printf("enter marks of assignmet\n");
						scanf("%d", &t);
						a->student_group = reveseStudentAssignmentRecord(a->student_group, group_id, statusofassignment, t);
						break;
					}

				} while (1);

				if (hash[assignmentidofstudnet] == 11)
				{
					printf("given assignemt is not allocated to anyone so enter the studnets details and assignemt record details\n");

					printf("\nENter student id \n");

					scanf("%d", &student_id);
					printf("\n Enter name of student and Partner\n");
					scanf("%s", name);
					scanf("%s", partnername);
					printf("\nEnter the Assignment Name\n");

					scanf("%s", assignmentname);
					printf("enter the deadline\n");

					scanf("%s", deadline);

					printf("enter the viva and offline marks\n");

					scanf("%d%d", &viva, &offline);

					stu_node = reversstudent(stu_node, 1, "snaket", "smit", 900, "dspd", "23-04-90", "Submitted", viva, offline, assignmentidofstudnet);
				}
				break;

			case 3:
				change_status(stu_node, asg_rec);
				break;

			case 4:
				printf_declared_not_evaluated(asg_rec);
				break;
			case 5:
				student_grp_not_evaluated(asg_rec);
				break;

			case 6:
				printf_grp_not_eval(asg_rec);
				break;

			case 7:
				print_decreasing(asg_rec);
				break;
			case 8:
				top_marks(asg_rec);
				break;

			case 9:
				range_search(asg_rec);
				break;

			case 11:
				prorderassignemt(asg_rec);
				break;
			case 13:
			     preorderstudent(stu_node);
				 break;

			case 10:
				printf("enter the assignment id you want to know\n");
				int asgid;
				scanf("%d", &asgid);
				struct assignment_record *wo = search_assignment(asg_rec, asgid);
				struct StudentAssignmentRecord *ptr = wo->student_group;
				inoderstudentassignemt(ptr);
				break;
			}

		} while (1);
	//}
}