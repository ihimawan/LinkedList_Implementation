//
//  main.c
//  LAB6
//
//  Created by Indri Himawan on 7/28/14.
//  Copyright (c) 2014 Indri. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct lists{
    char name[15];
    char phone[11];
    struct lists *next;
};

typedef struct lists node;

int find_name(char text[]); // finds the name and returns its location
int find_pnum(char pnum[]); // finds phone number and returns its location
void insert(char text[], char pnum[], int n); // will insert data
void delete(int where); // will delete data
void print(); // to print the linked list
void print_1(int middle_location); // prints the searched data with the person before and after
void print_2(int location_start); // prints the displayed searched data with the next two people
int where_to_put_name(char text[]); // tells where the data should be put based on name
int where_to_put_phone(char pnum[]); // tells where the data should be put based on phone number
void storedata(int argc); //initializes the data
void menu_display(int argc); // displays the menu

node *first; // first points to the first node

int main(int argc, const char * argv[])
{
    if (argc==2){
        if (strcmp(argv[1], "-p")!=0){
            printf("Invalid Command.");
            return 0;
        }
    }else if(argc>2){
        printf("Too many arguments.");
        return 0;
    }
    
    char command_no;
    char text[15];
    char pnum[11];
    char ch[2];
    int where, location;
    
    first=NULL;
    
    storedata(argc); //initializing data
    
    menu_display(argc); //displays menu

    while(command_no!='q'){ //q terminates the program
        
        printf("==================================================\n\n");
        printf("Enter command: ");
        scanf(" %c", &command_no);
        
        while (getchar() != '\n'); //skips to end of line (?)
        
        switch (command_no) {
            case '1': //display [WORKS!]
                print();
                break;
                
            case '2': //insert [WORKS!]
                printf("Input the name and phone (separated by space):\n");
                scanf("%s %s", text, pnum);
                    
                //checks if the phone number already exists
                location=find_pnum(pnum);
                if (location>0) {
                    printf("Phone number already exists, enter other phone number.\n\n");
                    break;
                }
                
                //inserting
                
                if (argc==1) {
                    where = where_to_put_name(text);
                }else{
                    where = where_to_put_phone(pnum);
                }
                
                insert(text, pnum, where);
                printf("%s is saved successfully.\n\n", text);
                print_1(where);
                break;
                
            case '3': //delete [WORKS!]
                printf("Input the name: \n");
                scanf("%s", text);
                where=find_name(text);
                if (where>0) {
                    delete(where);
                    printf("%s is deleted successfully.\n\n", text);
                }else{
                    printf("%s is not found.\n\n", text);
                }
                break;
                
            case '4': //search
                
                printf("Search with name(press n) or phone(press p)?\n");
                scanf("%s", ch);
                
                if (strcmp(ch,"n")==0){ //searching based on name
                    printf("Input the name: ");
                    scanf("%s", text);
                    location = find_name(text);
                    if (location>0) {
                        print_2(location);
                    }else{
                        printf("%s is not found\n\n", text);
                    }
                    
                }else if (strcmp(ch, "p")==0){ //searching based on phone number
                    printf("Input the phone number: ");
                    scanf("%s", pnum);
                    location = find_pnum(pnum);
                    if (location>0) {
                        print_2(location);
                    }else{
                        printf("%s is not found\n\n", pnum);
                    }
                    
                }else{ //if command is invalid
                    printf("Command is invalid.");
                }
                
                break;
                
            
            case 'q':
                
                printf("Exiting the program.\n\n");
                printf("==================================================\n\n");
                break;
            
            default: //invalid code
                printf("Invalid code, try again\n\n");
                break;
        }
    }
}


int where_to_put_name(char text[]){ // tells where the data should be put based on name [WORKS!]
    int where=1;
    node *temp;
    temp=first;
    
    if (first==NULL) {
        return where;
    }
    
    while (strcmp(text,temp->name)>=0) { //
        temp=temp->next;
        where++;
        if (temp==NULL) {
            return where;
        }
        
    }
    return where;
}

int where_to_put_phone(char pnum[]){ // tells where the data should be put based on phone number
    int where=1;
    node *temp;
    temp=first;
    
    if (first==NULL) {
        return where;
    }
    
    while (strcmp(pnum,temp->phone)>=0) { //
        temp=temp->next;
        where++;
        if (temp==NULL) {
            return where;
        }
        
    }
    return where;
}

int find_name(char text[]){ // finds the name and returns where it is [WORKS!]
    node *temp;
    temp=first;
    
    int where=1;
    
    if (temp==NULL) {
        return -1;
    }
    
    while ((strcmp(temp->name,text)!=0)) {
        temp=temp->next;
        if (temp==NULL) {
            return -1;
            break;
        }
        where++;
    }
    
    return where;
}

int find_pnum(char pnum[]){ // finds phone number and returns where it is [WORKS!]
    node *temp;
    temp=first;
    
    int where=1;
    
    if (temp==NULL) {
        return -1;
    }
    
    while ((strcmp(temp->phone,pnum)!=0)) {
        temp=temp->next;
        if (temp==NULL) {
            return -1;
            break;
        }
        where++;
    }
    
    return where;
}

void insert(char text[], char pnum[], int where){ // will insert data [WORKS!]
    node *temp;
    temp = (node *)malloc(sizeof(node));
    
    //insert the data
    strcpy(temp->name, text);
    strcpy(temp->phone, pnum);
    temp->next=NULL;
    
    if (where==1) { //if inserting the data as the first node
        temp->next=first;
        first=temp;
        return;
    }
    
    int i;
    
    node *temp2; //temp will point to the node before 'where'
    temp2=first;
    
    for (i=0; i<where-2; i++){ //making temp2 point to the node before 'where'
        temp2=temp2->next;
    }
    
    temp->next=temp2->next;
    temp2->next=temp;
}

void delete(int where){ //will delete data [WORKS!]
    node *temp;
    int i;
    
    temp=first;
    
    if(where==1){ //if deleting the first node
        first=temp->next; //head now points to the second node
        free(temp);
        return; //done
    }

    for (i=0; i<where-2; i++){ //making temp point to the node before 'where'
        temp=temp->next;
    }
    
    node *temp2;
    temp2=temp->next;
    temp->next=temp2->next;
    
    free(temp2);
}

void print() //print the entire linked list [WORKS!]
{
    node *temp;
    temp = first;
    
    printf("\n");
    while (temp != NULL){
        printf("%s %s\n", temp->name, temp->phone);
        temp=temp->next; //go to te next node
    }
    printf("\n");
}

void print_2(int location_start) // prints the displayed searched data with the next two people [WORKS!]
{
    int i,j;
    node *temp;
    temp=first;
    
    printf("\n");
    
    for (i=1; i<location_start ;i++) // will make temp point to the starting node
        temp=temp->next;
    
    for (j=0; j<3; j++){
        printf("%s %s\n", temp->name, temp->phone);
        temp=temp->next;
        if (temp==NULL) {
            break;
        }
    }
    printf("\n");
}

void storedata(int argc){ //initializes the data
    
    if (argc==1) {
        insert("Edward", "8067945007", where_to_put_name("Edward"));
        insert("Jack", "8067945005", where_to_put_name("Jack"));
        insert("Joshua", "8067945004", where_to_put_name("Joshua"));
        insert("James", "8067945003", where_to_put_name("James"));
        insert("Matthew", "8067945002", where_to_put_name("Matthew"));
        insert("Harold", "8067945001", where_to_put_name("Harold"));
    }else{
        insert("Edward", "8067945007", where_to_put_name("8067945007"));
        insert("Jack", "8067945005", where_to_put_name("8067945005"));
        insert("Joshua", "8067945004", where_to_put_name("8067945004"));
        insert("James", "8067945003", where_to_put_name("8067945003"));
        insert("Matthew", "8067945002", where_to_put_name("8067945002"));
        insert("Harold", "8067945001", where_to_put_name("8067945001"));
    }

}

void print_1(int middle_location){ // prints the searched data with the person before and after
    node *temp;
    temp=first;
    
    if (middle_location==1) {
        printf("%s %s\n", temp->name, temp->phone);
        temp=temp->next;
        if(temp==NULL){
            
        }else{
            printf("%s %s\n", temp->name, temp->phone);
        }
        return;
    }
    
    for(int i=1; i<middle_location-1; i++){ //will make temp point to the node before middle_location
        temp=temp->next;
    }

    for (int j=0; j<3; j++) {
        printf("%s %s\n", temp->name, temp->phone);
        temp=temp->next;
        if (temp==NULL) {
            break;
        }
    }
    
    printf("\n");
    
}

void menu_display(int argc){ // displays the menu
    
    if (argc==1) {
        printf("This program stores the people's records by order of NAME.\n\n");
    }else{
        printf("This program stores the people's records by order of PHONE NUMBER.\n\n");
    }
    
    printf("Available Commands: \n");
    printf("1 - Displays all stored data\n");
    printf("2 - Inserts data\n");
    printf("3 - Deletes a data\n");
    printf("4 - Searches for a data\n");
    printf("q - Quits program\n\n");
    
}
