#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <ctype.h>

#define SIZE 20
//Structure of node
typedef struct node *family_node;

struct node {
    int id;			// Unique id
    char name[SIZE];		// Name
    char lifeStatus;		// 'A' (Alive) or 'D' (Dead)
    int age;                    // Age
    family_node parents[2]; 	// pointers to parents
    family_node partner; 	// pointer to partner
    family_node children[5]; 	// pointers to children
    family_node prev;           //pointer to previous node
    family_node next;           //pointer to next node
};

family_node head;

family_node get_node(int id, char *name, int age, char lifeStatus);

void insert(int id, char *name, int age, char lifeStatus);

void deleteNode(char *name);

void printList();

void setParent(char *parentName, char *childName);

void setPartner(char *personName, char *partnerName);

void changeProfile(char *name, int age, char lifeStatus);

int printPerson(char *name);

void printParents(char *name);

void printChildren(char *name);

void printSiblings(char *name);

void printPartner(char *name);

void saveTree(char *fileName);

void loadTree(char *fileName);

void instructions();

family_node findNode(int id);

int personId;

int main(){

    head = NULL;
	personId = 0;
    int choice;

    do {
            instructions();
		while (1){

			printf("Enter your selection: ");         // Loop to get
			scanf("%i", &choice);                     // valid choice.
			if ((choice < 0) || (choice > 9)){
				printf("Invalid selection!\n");
				continue;
			}
			else
				break;
		}

		char name[21];
		int  age;
		char lifeStatus;
		char parentName[21];
		char childName[21];
		char personName[21];
		char partnerName[21];
		switch (choice) {

		case 1:             // Case 1 to add new person
			printf("Enter the name of the person: " );
			scanf("%20s", name);
			printf( "Enter the age of the person: " );
			scanf("%d", &age);
			fflush(stdin);
			printf("Enter character for life status of person (A = Alive/ D = Dead): " );
			scanf("\n%c", &lifeStatus);
			personId++;
		    insert(personId, name, age, lifeStatus);
			break;
		case 2:             //Case 2 to set parent and set child
			printf("Enter the name of the parent:" );
			scanf("%20s", parentName);
			printf("Enter the name of the child: " );
			scanf("%20s", childName);
			setParent(parentName, childName);
			break;
		case 3:             //Case 3 to set partners of each other
			printf("Enter the name of the person: " );
			scanf("%20s", personName);
			printf("Enter the name of the partner: " );
			scanf("%20s", partnerName);
			setPartner(personName, partnerName);
			break;

		case 4:         //Case 5 to edit profile
			printf("Enter the name of the person: " );
			scanf("%20s", name);
			printf("Enter the age of the person: " );
			scanf("%d", &age);
			fflush(stdin);
			printf("Enter the life status of the person (Alive/Dead): " );
			scanf("%c", &lifeStatus);
		    changeProfile(name, age, lifeStatus);
			break;
		case 5:         //Case 6 to delete node
			printf("Enter the name of the person: " );
			scanf("%20s", name);
			deleteNode(name);
			break;
		case 6:
			printList();
			break;
        case 7:             //Case 5 to print relatives
			printf("Enter the name of the person: " );
			scanf("%20s", personName);
			if (printPerson(personName)){
                printPartner(personName);
				printChildren(personName);
				printSiblings(personName);
				printParents(personName);
			}
			break;
		case 8:       // Case 8 to Save info to the file
			printf("Enter the file name: " );
			scanf("%20s", name);
		    saveTree(name);
			break;
		case 9:       // Case 9 to Load the File.
			printf("Enter the file name: " );
			scanf("%20s", name);
		    loadTree(name);
			break;
		}

    } while (choice != 0);

	return 0;
}
// Function to set new node of the person.
family_node get_node(int id, char *name, int age, char lifeStatus){

	family_node new_node = (family_node) malloc(sizeof(struct node));
	new_node->id = id;
	new_node->age = age;
	new_node->lifeStatus = toupper(lifeStatus);
	strcpy(new_node->name, name);
	new_node->prev = NULL;
	new_node->next = NULL;
	return new_node;
}

//Function to insert new node in the right place
void insert(int id, char *name, int age, char lifeStatus){

	family_node new_node = get_node(id, name, age, lifeStatus);
	if(head == NULL){
		head = new_node;
		return;
	}

	family_node current = head;
	family_node current_prev = NULL;
	while(current != NULL && strcmp(name, current->name) > 0){
		current_prev = current;
		current = current->next;
	}

	if (current == NULL) {
		new_node->next = NULL;
		new_node->prev = current_prev;
		current_prev->next = new_node;
	}
	else {
		if(strcmp(name, current->name) <= 0){
			new_node->next = current;
			if(strcmp(name, head->name) <= 0){
				head = new_node;
			} else {
				new_node->prev = current->prev;
				current->prev->next = new_node;
			}
			current->prev = new_node;
		} else {
			new_node->prev = current;
			current->next = new_node;
		}
	}
}
void changeProfile(char *name, int age, char lifeStatus){

	family_node p_name = head;
	while(p_name != NULL){
		if(strcmp(name, p_name->name) == 0){
			p_name->age = age;
			p_name->lifeStatus = toupper(lifeStatus);
			return;
		}
		else
			p_name = p_name->next;
	}
	puts("Person not found!");
}

//Function to delete the person from the family
void deleteNode(char *name){

	family_node temp = head;
	while(temp != NULL){
		if(strcmp(name, temp->name) == 0){
			if (temp == head) {
				if (temp->parents[0] != NULL) {
					for (int i=0; i<5; i++) {
						if (strcmp(temp->parents[0]->children[i]->name, temp->name) == 0) {
							temp->parents[0]->children[i] = NULL;
							break;
						}
					}
				}
				if (temp->parents[1] != NULL) {
					for (int i=0; i<5; i++) {
						if (strcmp(temp->parents[1]->children[i]->name, temp->name) == 0) {
							temp->parents[1]->children[i] = NULL;
							break;
						}
					}
				}
				if (temp->partner != NULL) {
					temp->partner->partner = NULL;
				}
				for (int i=0; i<5; i++) {
					if (temp->children[i] != NULL) {
						for (int j=0; j<2; j++) {
							if (strcmp(temp->children[i]->parents[j]->name, temp->name) == 0) {
								temp->children[i]->parents[j] = NULL;
								break;
							}
						}
					}
				}
				head = head->next;
				free(temp);
				return;
			}
			else {
				family_node del = temp;
				temp->prev->next = temp->next;
				if (temp->next != NULL)
					temp->next->prev = temp->prev;
				free(del);
				return;
			}
		}
		else
			temp = temp->next;
	}
	puts("Person not found!");
}

//Function to set Parent .
void setParent(char *parentName, char *childName) {

	family_node child = head;
	while(child != NULL){
		if(strcmp(childName, child->name) == 0){
			break;
		}
		else
			child = child->next;
	}

	if (child != NULL) {
		family_node parent = head;
		while(parent != NULL) {

			if(strcmp(parentName, parent->name) == 0){
				if (child->parents[0] != NULL) {
					child->parents[0] = parent;
					puts("Parent set.");
				}
				else if (child->parents[1] == NULL) {
					child->parents[1] = parent;
					puts("Parent set.");
				}
				else {
					puts("The second person has already two parents.");
					return;
				}
				int i = 0;
				for (; i < 5; i++) {
					if (parent->children[i] == NULL)
						break;
				}
				if (i < 5) {
					parent->children[i] = child;
					puts("Child set.");
				}
				else{
					puts("No more children.");
				}
				return;
			}
			else
				parent = parent->next;
		}
		puts("Parent not found!");
	}
	else
		puts("Person not found!");
}

//Function to set Partner of other person
void setPartner(char *personName, char *partnerName){

	family_node person = head;
	while(person != NULL){
		if(strcmp(personName, person->name) == 0){
			break;
		}
		else{
			person = person->next;
		}
	}

	if (person != NULL) {
		if ((person->partner) != NULL) {
			puts("This person already has a partner.");
			return;
		}
		family_node partner = head;
		while(partner != NULL) {
			if(strcmp(partnerName, partner->name) == 0){
				if (person->partner == NULL) {
					person->partner = partner;
					partner->partner = person;
					puts("Partners are set.");
					return;
				}
				else {
					puts("The second person already has a partner.");
					return;
				}
			}
			else
				partner = partner->next;
		}
		if (partner == NULL){
			puts("Second person not found!");
		}
	}
	else
		puts("Person not found!");
}

//Function to print all persons
int printPerson(char *name){
	family_node temp = head;
	while(temp != NULL){
		if(strcmp(name, temp->name) == 0) {
			puts("=============================================");
			printf("Name: %s, Age: %d, Life Status: %s\n", temp->name, temp->age, temp->lifeStatus == 'A'?"Alive":"Dead");
			puts("=============================================");
			return 1;
		}
		temp = temp->next;
	}
	puts("Person not found!");
	return 0;
}

void printList(){
	family_node temp = head;
	puts("List of the persons:");
	puts("==================================================");
	while(temp != NULL){
		printf("Name: %s, Age: %d, Life Status: %s\n", temp->name, temp->age, temp->lifeStatus == 'A'?"Alive":"Dead");
		temp = temp->next;
	}
	puts("==================================================");
}

//Function to print parents.
void printParents(char *name){
	family_node temp = head;
	while(temp != NULL){
		if(strcmp(name, temp->name) == 0){
			if (temp->parents[0] != NULL) {
				printf("First Parent of %s is %s\n", name, temp->parents[0]->name);
				if (temp->parents[1] != NULL)
					printf("Second Parent of %s is %s\n", name, temp->parents[1]->name);
			}
			else{
				puts("This person has no parents.");
			}
			return;
		}
		else
			temp = temp->next;
	}
	puts("Person not found!");
}

//Function to print all the siblings
void printSiblings(char *name){
	family_node temp = head;
	while(temp != NULL){
		if(strcmp(name, temp->name) == 0){
			if (temp->parents[0] != NULL) {
				int i = 0;
				int notYet = 1;
				for (; i < 5; i++) {
					if (temp->parents[0]->children[i] != NULL && strcmp(name, temp->parents[0]->children[i]->name) != 0) {
						if (notYet) {
							printf("Siblings of %s are:\n", name);
							notYet = 0;
						}
						printf("%s\n", temp->parents[0]->children[i]->name);
					}
				}
			}
			else
				puts("This person has no sibling.");
			return;
		}
		else
			temp = temp->next;
	}
	puts("Person not found!");
}

//Function to print partner
void printPartner(char *name){
	family_node temp = head;
	while(temp != NULL){
		if(strcmp(name, temp->name) == 0){
			if (temp->partner != NULL) {
				printf("Partner of %s is %s\n", name, temp->partner->name);
			}
			else
				puts("This person has no partner.");
			return;
		}
		else
			temp = temp->next;
	}
	puts("Person not found!");
}

//Function to print children
void printChildren(char *name){
	family_node temp = head;
	while(temp != NULL){
		if(strcmp(name, temp->name) == 0){
			if (temp->children[0] != NULL) {
				printf("Children of %s are:\n", name);
				int i = 0;
				for (; i < 5; i++) {
					if (temp->children[i] != NULL) {
						printf("%s\n", temp->children[i]->name);
					}
				}
			}
			else
				puts("This person has no children.");
			return;
		}
		else
			temp = temp->next;
	}
	puts("Person not found!");
}

//Function to Save Tree
void saveTree(char *fileName) {

	FILE *cfPtr;

	if ((cfPtr = fopen(fileName, "w")) == NULL) {
		puts("File could not be opened.");
	}
	else {
		puts("Data is writing to the file...");
		family_node temp = head;

		while(temp != NULL){
			int parent1 = temp->parents[0] == NULL ? 0 : temp->parents[0]->id;
			int parent2 = temp->parents[1] == NULL ? 0 : temp->parents[1]->id;
			int partner = temp->partner == NULL ? 0 : temp->partner->id;
			int c[5];
			for (int i=0; i<5;i++) {
				c[i] = temp->children[i] == NULL ? 0 : temp->children[i]->id;
			}
			fprintf(cfPtr, " %d %20s %d %c %d %d %d %d %d %d %d %d\n", temp->id, temp->name, temp->age, temp->lifeStatus,
					parent1, parent2, partner, c[0],c[1],c[2],c[3],c[4]);
			temp = temp->next;
		}
		fclose(cfPtr); // fclose closes the file
		puts("Data has been successfully written to the file.");
	}
}

//Function to Load tree
void loadTree(char *fileName) {

	FILE *cfPtr;

	if ((cfPtr = fopen(fileName, "r")) == NULL) {
		puts("File could not be opened.");
	}
	else {
		puts("Data is loading from the file...");
		family_node temp = head;
		while(temp != NULL){
			head = head->next;
			free(temp);
			temp = head;
		}

		int id;
		char name[21];
		int age;
		char lifeStatus;
		char line[100];
		personId = 0;
		while(fgets(line, sizeof line, cfPtr)){
			sscanf(line,"%d %20s %d %c",&id, name, &age, &lifeStatus);
		    insert(id, name, age, lifeStatus);
		    if (id > personId)
		    	personId = id;
		}

		rewind(cfPtr);

		while(fgets(line, sizeof line, cfPtr)){
			int parent1=0;
			int parent2=0;
			int partner=0;
			int c[5]={0};

			sscanf(line,"%d %20s %d %c %d %d %d %d %d %d %d %d\n",&id, name, &age, &lifeStatus,
					&parent1, &parent2, &partner, &c[0],&c[1],&c[2],&c[3],&c[4]);
			family_node n = findNode(id);

			if ((parent1 != 0)) {
				family_node p = findNode(parent1);
				if (p != NULL)

					setParent(p->name,n->name);
			}
			if ((parent2 != 0)) {
				family_node p = findNode(parent2);
				if (p != NULL)
					setParent(p->name,n->name);
			}
			if ((partner != 0)) {
				family_node p = findNode(partner);
				if (p != NULL)
					setPartner(n->name,p->name);
			}
		}

		fclose(cfPtr); // fclose closes the file
		puts("Data has been successfully loaded to the file.");
	}
}

//Function to find person
family_node findNode(int id) {

	family_node temp = head;

	while(temp != NULL){
		if (temp->id == id)
			return temp;
		temp = temp->next;
	}

	return NULL;
}

void instructions()
{
    puts("");
    printf("******************* Family Tree Menu ********************\n"
           "**                                                     **\n"
           "** Please select from the options below:               **\n"
           "**                                                     **\n"
           "**  (0) Exit.                                          **\n"
           "**  (1) Add a new person.                              **\n"
           "**  (2) Set a person as a parent of another person.    **\n"
           "**  (3) Set a person as the partner of another person. **\n"
           "**  (4) Change the profile of a person.                **\n"
           "**  (5) Remove a person.                               **\n"
           "**  (6) Print all the persons.                         **\n"
           "**  (7) Print all the relatives of a person.           **\n"
           "**  (8) Save the tree into a file.                     **\n"
           "**  (9) Load the tree from a file.                     **\n"
           "*********************************************************\n");
           puts("");

}

