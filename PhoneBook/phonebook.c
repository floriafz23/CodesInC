/* Lab 9
 * Student: Floria Fang Zhang
 * Purpose: Create a code in C using structures and linked lists.
 */

#include <stdio.h>
#include <stdlib.h>
#include "contactList.h"
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// IF IT'S EASIER, YOU NEED NOT BE OVERLY GENERAL/FLEXIBLE
// BUT CAN ASSUME THESE LIMITS
#define MAXCONTACTS 30 /* max # of contacts */
#define MAXPHONES 10 /* max # of phone numbers for each contact */

#define PHONE_NUMBER_MAX_LENGTH 12

//define types of structures: inside phonebook is all of contacts, and each contact has a name and phone number(s)
typedef struct number{
	char* phoneNumber;
	struct number *next;
}Number;

typedef struct contacts{
	char* personName;
	Number *contactNumber;
	struct contacts *next;
}Contacts;

typedef struct phonebook{
	Contacts *contactInfo;
}Phonebook;


//createContact: create a contact (name, numbers)
Contacts *createContact(int i){
	
	Contacts *newContact = (Contacts*)malloc(sizeof(Contacts));
	newContact->personName = contactList[i];
	newContact->next = NULL;
	
	return newContact;
}

//createNumber: create numbers for a specific contact
Number *createNumber(int i){
	
	Number *newNumber = (Number*)malloc(sizeof(Number));
	newNumber->phoneNumber = contactList[i];
	newNumber->next = NULL;
	
	return newNumber;
}

// alphabetizeContact: insert a contact into the phonebook in alphabetic order
Phonebook *alphabetizeContact(Phonebook *phonebook, Contacts *newContact){
	
	//if phonebook is empty, assign newcontact to beginning of phonebook
	if(phonebook->contactInfo == NULL)
		phonebook->contactInfo = newContact;
	
	//compare strings (alphabetically), if newcontact is smaller: newcontact to beginning of phonebook
	else if(strcmp(phonebook->contactInfo->personName , newContact->personName) > 0 ){
		newContact-> next = phonebook -> contactInfo;
		phonebook->contactInfo = newContact;
	}
	
	//compare strings (alphabetically) until newContact is not smaller, then assign to spot
	else{
		Contacts *currentContact = phonebook -> contactInfo;
		while(currentContact->next != NULL && strcmp(currentContact->next->personName , newContact->personName) < 0 ){
			currentContact = currentContact->next;
		}
		newContact->next = currentContact -> next;
		currentContact->next = newContact;
	}
	
	return phonebook;
}

/* convertInputToDataStructure
 * Takes the information in contactList.h and puts it into a data
 * structure of your choosing, however: 1 mark of the lab will be
 * for using structs with pointers in your solution.
 * You might also want to consider the outputs from the program
 * (see the menu printed in printMenu) since some structures will
 * make this easier than others.
 */
void convertInputToDataStructure(Phonebook *phonebook) {
	
	//declare variables and initialize
	Contacts *newContact;
	Number *newNumber;
	
	phonebook -> contactInfo = NULL;
	
	//for all items of contactList, create contacts and numbers
	for(int i=0; i< sizeof(contactList)/sizeof(char*); i++){
		//if item is alphabetical, create contact
		if(isalpha(*contactList[i])){
			newContact = createContact(i);
		}
		//if item is numerical, create number
		else if(isdigit(*contactList[i])){
			newNumber = createNumber(i);
			
			//insert into newContact -> contactNumber (at beginning of list)
			newNumber->next = newContact ->contactNumber;
			newContact -> contactNumber = newNumber;
			
		}
		
		// enter into contact w/ phones into phonebook (alphabetically) when contact is complete
		if(i<sizeof(contactList)/sizeof(char*)-2){
			if(isalpha(*contactList[i+1])){
				phonebook = alphabetizeContact(phonebook,newContact);
			}
		}
		else if(i== (sizeof(contactList)/sizeof(char*)-1)){
			phonebook = alphabetizeContact(phonebook,newContact);
		}
	}

}

//deleteNumber: delete and free numbers for a contact
void deleteNumber(Number *contactNumber){
	if(contactNumber != NULL){
		deleteNumber(contactNumber->next);
		free(contactNumber);
	}
}

//deleteContacts: delete and free contacts
void deleteContacts(Contacts *contactHead){
	if(contactHead != NULL){
		deleteNumber(contactHead->contactNumber);
		deleteContacts(contactHead->next);
		free(contactHead);
	}
}

//deletePhonebook: delete and free phonebook
void deletePhonebook(Phonebook *phonebook){
	if(phonebook != NULL){
		deleteContacts(phonebook->contactInfo);
		free(phonebook);
	}
}

//ListAllContacts: print contacts in alphabetical order
void ListAllContacts(Phonebook *phonebook){
	//declare variables and initialize
	Contacts *currentContact = phonebook -> contactInfo;
	
	while(currentContact != NULL){
		//print contact name
		printf("Name: %s\n", currentContact->personName);
		printf("Phone(s):");
		
		//print contact phone numbers 
		Number *currentNumber = currentContact->contactNumber;
		while(currentNumber != NULL){
			printf(" %s", currentNumber->phoneNumber);
			currentNumber = currentNumber->next;
		}
		currentContact = currentContact ->next;
		printf("\n");
	}
}

/*
 * printMenu - Prints out the user menu
 */
void printMenu() {
   printf("\n\nEnter a command by number\n");
   printf("1. List all contacts in alphabetical order\n");
   printf("2. Print phone(s) for a contact\n");
   printf("3. Find duplicate entries\n");
   printf("4. Delete contact\n");
   printf("5. Exit the program\n");
   printf("Your input: ");
}

//eliminate trailing \n
char* rtrim(char* str){
   int i;
   for (i = strlen(str) - 1; i >= 0 && str[i] == '\n'; i--)
      str[i] = '\0';
   return str;
}

//PrintContact: print a contact given an input name
void PrintContact(Phonebook *phonebook) {
	//declare variables
	char nameInput[50];
	bool validInput = false;
	
	//ask user for input and scan input
	printf("Enter name: ");
	fgets(nameInput,50,stdin);
	
	Contacts *currentContact = phonebook -> contactInfo;
	while(currentContact != NULL){
		//compare inputed name with contact name
		int comparison = strcmp(rtrim(currentContact->personName), rtrim(nameInput));
		//if input name and contact name are the same print the name and numbers
		if(comparison==0){
			printf("Name: %s\n", currentContact->personName);
			printf("Phone(s):");
			
			Number *currentNumber = currentContact->contactNumber;
			while(currentNumber != NULL){
				printf(" %s", currentNumber->phoneNumber);
				currentNumber = currentNumber->next;
			}
			printf("\n");
			validInput = true;
		}
		currentContact = currentContact ->next;
	}
	//if input name isn't any contact name, print contact not found
	if(validInput == false)
		printf("Contact not found\n");
}




/* DeleteContact deletes a contact from the list
 * The user must enter the name of the contact to delete
 */
void DeleteContact(Phonebook *phonebook) {
	// declare all variables
	char nameInput[50];
	
	//ask user for input and scan input
	printf("Enter name: ");
	fgets(nameInput,50,stdin);
	
	//assign current to head and previous to NULL
	Contacts *previousContact = NULL;
	Contacts *currentContact = phonebook -> contactInfo;
	int comparison = 1;
	while(currentContact != NULL && comparison != 0){
		//compare contact name with inputted name
		comparison = strcmp(rtrim(currentContact->personName), rtrim(nameInput));
		//if contact name and inputted name match, leave loop
		if(comparison == 0)
			break;
		previousContact = currentContact;
		currentContact = currentContact ->next;
		
	}
	
	// assign contact previous to desired to point to next structure
	if(currentContact !=NULL){
		if(previousContact != NULL)
			previousContact->next = currentContact->next;
		else
			phonebook->contactInfo = currentContact->next;
		//delete contact and free structure
		deleteNumber(currentContact->contactNumber);
		free(currentContact);
	}

}


/* findDuplicates finds the names of contacts with 
 * a phone number in common
 */
void FindDuplicates(Phonebook *phonebook) {
	//declare variables
	Contacts *currentContact = phonebook -> contactInfo;
	Contacts *nextContact = phonebook->contactInfo ->next;
	
	//create loops: start with first contact, first number, compare with second contact, first number, and each element increases in backwards order
	while(currentContact != NULL){
		nextContact = currentContact->next;
		Number *currentNumber = currentContact->contactNumber;
		while(currentNumber != NULL){
			while(nextContact != NULL){
				Number *nextNumber = nextContact->contactNumber;
				while(nextNumber != NULL){
					//compare current number with next number
					int comparison = strcmp(currentNumber->phoneNumber,nextNumber->phoneNumber);
					//if current number equals next number, print 
					if(comparison==0)
						printf("%s and %s have a phone number in common\n", currentContact->personName, nextContact->personName);
					nextNumber = nextNumber->next;
				}
				nextContact = nextContact ->next;
			}
			currentNumber = currentNumber->next;
		}
		currentContact = currentContact->next;
	}

}


int main()
{
   // first move data from contactList.h to a data structure
	Phonebook *phonebook= (Phonebook*)malloc(sizeof(Phonebook));
	convertInputToDataStructure(phonebook);
  
	char notDone = 1;
	while (notDone) {
		printMenu();
		char userChoice[100];
		char* s = fgets(userChoice, sizeof(userChoice), stdin);
		if (!s)
		{
			printf("Wrong input\n");
			continue;
		}
		s = rtrim(s); /* eliminate trailing \n */
		//printf("selection = %s\n", s);
		int userSelection = atoi(s);

		switch (userSelection) {
			case 1: ListAllContacts(phonebook); break;
			case 2: PrintContact(phonebook); break;
			case 3: FindDuplicates(phonebook); break;
			case 4: DeleteContact(phonebook); break;
			case 5: notDone = 0; break;
			default: printf("Bad command...\n"); break;
		}
	}

	//delete and free phonebook
	deletePhonebook(phonebook);

   return 0;
}
