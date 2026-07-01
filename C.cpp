#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void showMenu();
void addStudent(struct student s[], int *count);
void showAllStudents(struct student s[], int count);
void searchStudent(struct student s[], int count);
void updateStudent(struct student s[], int *count);
void deleteStudent(struct student s[], int *count);
void saveToFile(struct student s[], int count);
void loadFromFile(struct student s[], int *count);

struct student
{
	char name[50];
	int roll;
	int age;
	float marks;
};


int main()
{
	int choice;
	int count = 0;
	struct student s[100];
	loadFromFile(s, &count);
	
	while(1)
	{
		showMenu();
		
		scanf("%d",&choice);
		
		switch(choice)
		{
			case 1:
				addStudent(s,&count);
				break;
				
			case 2:
				showAllStudents(s,count);
				break;
				
			case 3:
				searchStudent(s,count);
				break;
			
			case 4:
				updateStudent(s,&count);
				break;
				
			case 5:
				deleteStudent(s,&count);
				break;
				
			case 6:
				printf("Thank You!\n");
				exit(0);
				
			default:
				printf("Invalid Choice");
		}
		
	}
	
	
}

void showMenu()
{
	printf("==================================================\n");
	printf("             STUDENT MANAGEMENT SYSTEM             \n");
	printf("===================================================\n");
	printf("\n");
	printf("1. Add Student\n");
	printf("2. Show All Students\n");
	printf("3. Search Student\n");
	printf("4. Update Student\n");
	printf("5. Delete Student\n");
	printf("6. Exit\n");
	printf("\n");
	printf("Enter Your Choice : ");
}

void addStudent(struct student s[], int *count)
{
	int i;
	int newRoll;
	
	printf("Enter Roll Number: ");
	scanf("%d",&newRoll);
	
	if(*count >= 100)
	{
    	printf("Maximum Students Reached!\n");
    	return;
	}
	
	for(i=0;i<*count;i++)
	{
    	if(s[i].roll==newRoll)
		{
			printf("Roll Number Already Exists!\n");
        	return;
    	}
	}
	
	s[*count].roll = newRoll;
	
	printf("Enter Name: ");
	scanf(" %49[^\n]",s[*count].name); 
	
	printf("Enter Age: ");
	scanf("%d",&s[*count].age);
	
	printf("Enter Marks: ");
	scanf("%f",&s[*count].marks);
		
	(*count)++;
	
	printf("Student Added Successfully\n");
	
	saveToFile(s, *count);
}

void showAllStudents(struct student s[], int count)
{
	int i;
	
	if(count == 0)
	{
    	printf("No Students Found!\n");
    	return;
	}
		for(i=0; i < count; i++)
		{
			printf("------------------------------\n");
    		printf("Student %d\n\n", i + 1);
			
    		printf("Roll Number : %d\n", s[i].roll);
    		printf("Name        : %s\n", s[i].name);
    		printf("Age         : %d\n", s[i].age);
    		printf("Marks       : %.2f\n", s[i].marks);
			
    		printf("------------------------------\n\n");
		}
}

void searchStudent(struct student s[], int count)
{
	int searchRoll;
	int i;
	
	printf("Enter The Roll Number To Search: ");
	scanf("%d",&searchRoll);
		
	if(count == 0)
	{
    	printf("No Students Found!\n");
    	return;
	}
	
	for(i=0; i < count ; i++)
	{
		if(searchRoll == s[i].roll)
		{
			
			printf("------------------------------\n");
			printf("Student Found\n\n");
			
			printf("Roll Number : %d\n", s[i].roll);
    		printf("Name        : %s\n", s[i].name);
    		printf("Age         : %d\n", s[i].age);
    		printf("Marks       : %.2f\n", s[i].marks);
			
    		printf("------------------------------\n\n");
			return;
		}
	}
	
	printf("Student Not Found!\n");
}

void updateStudent(struct student s[], int *count)
{
	int searchRoll;
	int i;
	
	printf("Enter The Roll Number To Update: ");
	scanf("%d",&searchRoll);
	
	if(*count == 0)
	{
    	printf("No Students Found!\n");
    	return;
	}
	
	for(i = 0; i < *count; i++)
	{
		if(searchRoll == s[i].roll)
		{
			printf("------------------------------\n");
			printf("Student Found\n\n");
			
			printf("Roll Number : %d\n", s[i].roll);
    		printf("Name        : %s\n", s[i].name);
    		printf("Age         : %d\n", s[i].age);
    		printf("Marks       : %.2f\n", s[i].marks);
    		
    		printf("Enter New Name: ");
			scanf(" %49[^\n]", s[i].name);
			
			printf("Enter New Age: ");
			scanf("%d", &s[i].age);
			
			printf("Enter New Marks: ");
			scanf("%f",&s[i].marks);
			
			
			printf("Student Update Succesfull\n");
			
			saveToFile(s, *count);
			return;
		}
	}
	
	printf("Student Not Found!\n");
	
}

void deleteStudent(struct student s[], int *count)
{
	int searchRoll;
	int i;
	int j;
	
	printf("Enter Roll Number To Delete: ");
	scanf("%d",&searchRoll);
	
	if(*count == 0)
	{
    	printf("No Students Found!\n");
    	return;
	}
	
	for(i = 0; i < *count; i++)
	{
		if(searchRoll == s[i].roll)
		{
			for(j = i; j < *count - 1; j++)
			{
				s[j]=s[j+1];
			}
			
			(*count)--;
			
			printf("Student Deleted Successfully!\n");
			
			saveToFile(s, *count);
			return;
		}
	}
	
	
	printf("Student Not Found!\n");
	
}

void saveToFile(struct student s[], int count)
{
	FILE *fp;
	fp = fopen("students.txt","w");
	int i;

	if(fp==NULL)
	{
    	printf("File Is Not Opened\n");
    	return;
	}
	
	for(i = 0; i < count; i++)
	{
		fprintf(fp,"Roll Number: %d\n",s[i].roll);
		fprintf(fp,"Name: %s\n",s[i].name);
		fprintf(fp,"Age: %d\n",s[i].age);
		fprintf(fp,"Marks: %.2f\n",s[i].marks);
		fprintf(fp,"----------------------------------------\n");
	}
	
	fclose(fp);
}

void loadFromFile(struct student s[], int *count)
{
	FILE *fp;
	fp = fopen("students.txt","r");
	int i;

	if(fp==NULL)
	{
    	return;
	}
	
	while(*count < 100 && fscanf(fp,
                "Roll Number: %d\n"
                "Name: %49[^\n]\n"
                "Age: %d\n"
                "Marks: %f\n"
                "----------------------------------------\n",
                &s[*count].roll,
                s[*count].name,
                &s[*count].age,
                &s[*count].marks) == 4)
    {
        (*count)++;
    }
	
	fclose(fp);
}
