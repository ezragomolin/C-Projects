
/*
 ============================================================================
 Name        : database.c  ECSE-202_A6
 Author      : Ezra Gomolin 260926917
 Version     :
 Copyright   : MOST of this code and comment comes from Professor Ferrie's dbReader.c
 Description : A simple program to manage a small database of student
             : records using B-Trees for storage.
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// To make the "C" implementation completely analogous to Java, one has to create
// an object for each student record and attach it to a corresponding bNode
// object in a B-Tree data structure.  These objects are represented by the
// corresponding structure templates below.

#define MAXLEN 20
#define false 0
#define true !false


// Structure Templates

typedef struct SR {
    char Last[MAXLEN];
	char First[MAXLEN];
	int ID;
	int marks;
} SRecord;

typedef struct bN {				// The bNode object
	struct SR *Srec;
	struct bN *left;
	struct bN *right;
} bNode;



bNode *match;  //global variable to return matching student file

// Notice that there are two versions of add_node, inorder, and search.
// This is to accommodate sorting the database by last name OR student ID

//these functions  below are written at the end of the file, and this is practically
//all i had to write for this assignment
bNode *addNode_Name(bNode *root, SRecord *rec);
bNode *addNode_ID(bNode *root, SRecord *data);
bNode *makeNode(SRecord *data);

void inorder(bNode *root);
void search_Name(bNode *root, char *data);
void search_ID(bNode *root, int ID);
void str2upper(char *string);
void help();


// Main entry point is here.  Program uses the standard Command Line Interface

int main(int argc, char *argv[]) {

// Internal declarations

    FILE * NAMESIDS;        // File descriptor (an object)!
	FILE * MARKS;           // Will have two files open

    bNode *root_N;   		// Pointer to names B-Tree
    bNode *root_I;   		// Pointer to IDs B-Tree
    SRecord *Record;   		// Pointer to current record read in

	int NumRecords;
	char cmd[MAXLEN], sName[MAXLEN];
	int sID;

// Argument check
        if (argc != 3) {
                printf("Usage: sdb [Names+IDs] [marks] \n");
                return -1;
        }

// Attempt to open the user-specified file.  If no file with
// the supplied name is found, exit the program with an error
// message.

        if ((NAMESIDS=fopen(argv[1],"r"))==NULL) {
                printf("Can't read from file %s\n",argv[1]);
                return -2;
        }

        if ((MARKS=fopen(argv[2],"r"))==NULL) {
                printf("Can't read from file %s\n",argv[2]);
                fclose(NAMESIDS);
                return -2;
        }

// Initialize B-Trees by creating the root pointers;

   root_N=NULL;
   root_I=NULL;

//  Read through the NamesIDs and marks files, record by record.

	NumRecords=0;

	printf("Building database...\n");

	while(true) {

// 	Allocate an object to hold the current data

		Record = (SRecord *)malloc(sizeof(SRecord));
		if (Record == NULL) {
			printf("Failed to allocate object for data in main\n");
			return -1;
		}

//  Read in the data.  If the files are not the same length, the shortest one
//  terminates reading.

		int status = fscanf(NAMESIDS,"%s%s%d",Record->First,Record->Last,&Record->ID);
		if (status == EOF) break;
		status = fscanf(MARKS,"%d",&Record->marks);
		if (status == EOF) break;
		NumRecords++;

		root_N=addNode_Name(root_N,Record);
		root_I=addNode_ID(root_I,Record);




	}

// Close files once we're done

	fclose(NAMESIDS);
	fclose(MARKS);

	printf("Finished, %d records found...\n",NumRecords);


//
//  Simple Command Interpreter: - This is commented out until you implement the functions listed above
//

	while (1) {
	    printf("sdb: ");
	    scanf("%s",cmd);					  // read command
	    str2upper(cmd);
	    if (0) {							  // This is a temporary stub
	    	continue;
	    }


// List by Name

		if (strncmp(cmd,"LN",2)==0) {         // List all records sorted by name
			printf("Student Record Database sorted by Last Name\n\n");
			//printf("id %d", root_N->Srec->ID);
			if (root_N == NULL) {
				printf("null\n");
			}
			inorder(root_N);
			printf("\n");
		}

// List by ID

		else if (strncmp(cmd,"LI",2)==0) {    // List all records sorted by ID
			printf("Student Record Database sorted by Student ID\n\n");
			inorder(root_I);
			printf("\n");
		}

// Find record that matches Name

		else if (strncmp(cmd,"FN",2)==0) {    // List record that matches name
			printf("Enter name to search: ");
			scanf("%s",sName);
			match=NULL;
			search_Name(root_N,sName);
			if (match==NULL)
			  printf("There is no student with that name.\n");
	        else {
			  if (strlen(match->Srec->First)+strlen(match->Srec->Last)>15) {
				printf("\nStudent Name:\t%s %s\n",match->Srec->First,match->Srec->Last);
			  } else {
				printf("\nStudent Name:\t\t%s %s\n",match->Srec->First,match->Srec->Last);
			  }
			  printf("Student ID:\t\t%d\n",match->Srec->ID);
			  printf("Total Grade:\t\t%d\n\n",match->Srec->marks);
	        }
		}

// Find record that matches ID


		else if (strncmp(cmd,"FI",2)==0) {    // List record that matches ID
			printf("Enter ID to search: ");
			scanf("%d",&sID);
			match=NULL;
			search_ID(root_I,sID);
			if (match==NULL)
			  printf("There is no student with that ID.\n");
	        else {
			  if (strlen(match->Srec->First)+strlen(match->Srec->Last)>15) {
				printf("\nStudent Name:\t%s %s\n",match->Srec->First,match->Srec->Last);
			  } else {
				printf("\nStudent Name:\t\t%s %s\n",match->Srec->First,match->Srec->Last);
			  }
			   printf("Student ID:\t\t%d\n",match->Srec->ID);
			   printf("Total Grade:\t\t%d\n\n",match->Srec->marks);
	      }
		}



// Help

		else if (strncmp(cmd,"H",1)==0) {  // Help
			help();
		}

		else if (strncmp(cmd,"?",2)==0) {     // Help
			help();
		}

// Quit

		else if (strncmp(cmd,"Q",1)==0) {  // Help
			printf("Program terminated...\n");
			return 0;
		}

// Command not understood

		else {
			printf("Command not understood.\n");
		}
	}

}

//
//	Write and insert the functions listed in the prototypes here.
//

//creating the binary tree for names, almost identical to assignement 3
bNode *addNode_Name(bNode *root, SRecord *rec){
	bNode*current;
		if (root==NULL){
			root=makeNode(rec);
		}

		else{
			current=root;
			while(true){

				if(strcasecmp(rec->Last, current->Srec->Last) < 0){
					if(current->left==NULL){
					current->left=makeNode(rec);
					break;
					}
					else{
						current=current->left;
					}

				}
				else {
					if(current->right==NULL){
						current->right=makeNode(rec);
						break;
					}
					else{
						current=current->right;
					}
				}
			}

		}
return root;

}
//creating the binary tree for ID's almost identical to assignement 3
bNode *addNode_ID(bNode *root, SRecord *data){
	bNode *current;
	if (root==NULL){
		root=makeNode(data);
	}

	else{
		current=root;
		while(true){

			if(data->ID<current->Srec->ID){
				if(current->left==NULL){
				current->left=makeNode(data);
				break;

				}
				else{
					current=current->left;
				}

			}
			else{
				if(current->right==NULL){
					current->right=makeNode(data);
					break;
				}
				else{
					current=current->right;
				}
			}
		}

	}

	return root;

}
//making the actual node, almost identical to assignement 3
bNode*makeNode(SRecord *Srec){
	bNode*node=(bNode*)malloc(sizeof(bNode));
	node->Srec=Srec;
	node->left=NULL;
	node->right=NULL;
	return node;
}


//This traverses the names/id's in alphabetical order for names, and increasing numbers for IDs
void inorder(bNode *root){
	if(root->left!=NULL) inorder(root->left);
	printf("%-10s %-10s %10d %10d \n", root->Srec->First, root->Srec->Last,
			root->Srec->ID, root->Srec->marks);
	if (root->right !=NULL) inorder(root->right);
}

//recursive method for search functions (search_Name, search_ID)
//check status of data and decide which way to traverse the tree
//if it does not have to be traversed anymore, meaning data=data we want,
//than we set match equal to the root, meaning we found what were looking for
 void search_Name(bNode *root, char *data){
	 if (root!=NULL){

	 		if(strcasecmp(data, root->Srec->Last) < 0) search_Name(root->left, data);


	 		else if(strcasecmp(data, root->Srec->Last) > 0) search_Name(root->right,data);

	 		else{
	 				match=root;
	 				return;
	 		}
	 	}

}


void search_ID(bNode *root, int ID){

	if (root!=NULL){

		if(root->Srec->ID< ID) search_ID(root->right, ID);


		else if(root->Srec->ID> ID) search_ID(root->left,ID);

		else{
				match=root;
				return;
		}
	}

}




//
//  Convert a string to upper case
//



void str2upper (char *string) {
    int i;
    for(i=0;i<strlen(string);i++)
       string[i]=toupper(string[i]);
     return;
}

// Help
// prints command list

void help() {
	printf("LN List all the records in the database ordered by last name.\n");
	printf("LI List all the records in the database ordered by student ID.\n");
	printf("FN Prompts for a name and lists the record of the student with the corresponding name.\n");
	printf("FI Prompts for a ID and lists the record of the student with the Corresponding ID.\n");
	printf("HELP Prints this list.\n");
	printf("? Prints this list.\n");
	printf("Q Exits the program.\n\n");

	return;
}

