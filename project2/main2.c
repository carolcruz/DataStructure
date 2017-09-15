#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct d{ //declaration of type dishes
	char name[50];
	float price;
	struct d *nextDish;
}dishes;

typedef struct no{ //declaration of type node
	dishes dish;
	struct no *nextNode;
}node;

dishes *begList=NULL, *endList=NULL; //global pointers that points to the beginning and end of a dishes's linked list
node *begQueue=NULL, *endQueue=NULL; ////global pointers that points to the beginning and end of a node's queue
FILE *file;

void addList(char name[], float price){
    if(begList == NULL){
        dishes *newNode = (dishes*)malloc(sizeof(dishes));
        strcpy(newNode->name, name);
        newNode->price = price;
        newNode->nextDish = NULL;
        begList = newNode;
        endList = newNode;
    }else{
        dishes *newNode = (dishes*)malloc(sizeof(dishes));
        strcpy(newNode->name, name);
        newNode->price = price;
        newNode->nextDish = NULL;
        endList->nextDish = newNode;
        endList = newNode;
    }
}

void addQueue(dishes dish){
	if(begQueue == NULL){
		node *newNode = (node*)malloc(sizeof(node));
		newNode->dish = dish;
		newNode->nextNode = NULL;
		begQueue = newNode;
		endQueue = newNode;
	}else{
		node *newNode = (node*)malloc(sizeof(node));
		newNode->dish = dish;
		newNode->nextNode = NULL;
		endQueue->nextNode = newNode;
		endQueue = newNode;
	}
	//printf("Request done sucessfully!\n");
}

void #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


/* The data structures used in this programs:
			- queue (that represents a request queue)
			- list (the represents the menu)
			- file (that saves the menu in secondary memory, to maintain the data)
The operations:
	Queue -> insert, delete, print
	List -> insert, delete, print, change
*/

typedef struct d{ //declaration of type dishes
	char name[50];
	float price;
	struct d *nextDish;
}dishes;

typedef struct no{ //declaration of type node
	dishes dish;
	struct no *nextNode;
}node;

dishes *begList=NULL, *endList=NULL; //global pointers that points to the beginning and end of a dishes's linked list
node *begQueue=NULL, *endQueue=NULL; ////global pointers that points to the beginning and end of a node's queue
FILE *file;

//Functions that implement operations - Linked List:
void addList(char name[], float price); //add a new element to the dishes's linked list
void removeList(char name[]); //remove an element to the dishes's linked list
void printList(); //print the list of dishes (Menu)
void saveList(); //save the list of dishes (Menu) on a file
void getList(); //get the dishes from the file
void changeDishName(char nameDish[]); //change the name of a dish
void changeDishPrice(char nameDish[]);//change the price of a dish

//Functions that implement operations - Queue:
void addQueue(dishes dish); //add a new request in the queue
void printQueue(); //print the queue of requests
void removeQueue(); //remove from the queue. Remembering: in a queue the deletion is always in the beginning

//Functions that implements the interaction with the user:
void menu0();
void menu1();
void menu2();
void menu3();
void menu4();
void menu5();
void menu6();
void menu7();
void menu8();
void menuPassword();
//Main:
int main();

void addList(char name[], float price){
	if(begList == NULL){
		dishes *newNode = (dishes*)malloc(sizeof(dishes));
		strcpy(newNode->name, name);
		newNode->price = price;
		newNode->nextDish = NULL;
		begList = newNode;
		endList = newNode;
	}else{
		dishes *newNode = (dishes*)malloc(sizeof(dishes));
		strcpy(newNode->name, name);
		newNode->price = price;
		newNode->nextDish = NULL;
		endList->nextDish = newNode;
		endList = newNode;
	}
	//printf("Added to the Menu.\n");
}
void removeList(char name[]){
	dishes *aux=NULL, *ant=NULL;
	aux = begList;
	ant = begList;
	int a=0;
	while(aux!=NULL){
		if(strcmp(name, aux->name)==0){
			if(aux==begList){
				begList = aux->nextDish;
				free(aux);
				printf("Dish removed of Menu.\n");
				a++;
			}else if(aux==endList){
					endList = ant;
					ant->nextDish = NULL;
					free(aux);
					printf("Dish removed of Menu.\n");
					a++;
				}else{
					ant = aux->nextDish;
					free(aux);
					printf("Dish removed of Menu.\n");
					a++;
				}

		}
		ant = aux;
		aux = aux->nextDish;
	}
	if(a==0) printf("Not found.\n");

}
void addQueue(dishes dish){
	if(begQueue == NULL){
		node *newNode = (node*)malloc(sizeof(node));
		newNode->dish = dish;
		newNode->nextNode = NULL;
		begQueue = newNode;
		endQueue = newNode;
		file = fopen("sales.dat", "a+b");
        fwrite(&newNode->dish.price, sizeof(float), 1, file);
        fclose(file);
	}else{
		node *newNode = (node*)malloc(sizeof(node));
		newNode->dish = dish;
		newNode->nextNode = NULL;
		endQueue->nextNode = newNode;
		endQueue = newNode;
		file = fopen("sales.dat", "a+b");
        fwrite(&newNode->dish.price, sizeof(float), 1, file);
        fclose(file);
	}
	printf("Request done sucessfully!\n");
}
void removeQueue(){
	node *aux=NULL;
	aux = begQueue;
	begQueue = begQueue->nextNode;
	free(aux);
}
void printList(){
	dishes *aux=NULL;
	aux = begList;
	int i=1;
	while(aux!=NULL){
		printf("%d- %s %.2f\n", i, aux->name, aux->price);
		aux=aux->nextDish;
		i++;
	}
}
void printQueue(){
	node *aux=NULL;
	aux = begQueue;
	dishes aux2;
	int i=1;
	while(aux!=NULL){
        aux2 = aux->dish;
		printf("%d- %s  %.2f\n", i, aux2.name, aux2.price);
		aux = aux->nextNode;
	}
}
void saveList(){
    file = fopen("dishes.dat", "w+b");
    dishes *aux;
    aux = begList;
    while(aux!=NULL){
        fwrite(&aux, sizeof(dishes), 1, file);
        aux = aux->nextDish;
    }
	fclose(file);
}
void getList(){
	file = fopen("dishes.dat", "r+b");
	dishes aux;
	fseek(file, 0, 0);
	do{
		fread(&aux, sizeof(dishes), 1, file);
		if(!feof(file)){
			addList(aux.name, aux.price);
			//printf("%s %f", aux.name, aux.price);
		}
	}while(!feof(file));
	fclose(file);
}
void changeDishName(char nameDish[]){
	dishes *aux=NULL;
	aux = begList;
	char newName[50];
	int a=0;
	//float newPrice
	while(aux!=NULL){
		if(strcmp(nameDish, aux->name)==0){
			printf("New name of the dish: ");
			fgets(newName, 50, stdin);
			strcpy(aux->name,newName);
			printf("Name changed successfully!\n");
			a++;
		}
		aux = aux->nextDish;
	}
	if(a==0) printf("Not found.\n");
}
void changeDishPrice(char nameDish[]){
	dishes *aux=NULL;
	aux = begList;
	int a=0;
	//char newName[50];
	float newPrice;
	while(aux!=NULL){
		if(strcmp(nameDish, aux->name)==0){
			printf("New price of the dish: ");
			scanf("%f", &newPrice);
			aux->price = newPrice;
            a++;
            printf("Price changed successfully!\n");
		}
		aux = aux->nextDish;
	}
	if(a==0) printf("Not found.\n");
}
void menu0(){
    printf("\t KODEL'S RESTAURANT \t \n \n");
    printf("Date (dd/mm/aa): ");
    char data[8];
    fgets(data, 8, stdin);
    fflush(stdin);
    file = fopen("sales.dat", "a+b");
    fwrite(data, sizeof(char), 8, file);
    fclose(file);
    system("clear");
    //printf("Press any key to continue.");
    getchar();
    menu1();
}
void menu1(){
    printf("\t KODEL'S RESTAURANT \t \n \n");
    printf("1. Client\n2. Kitchen\n0. Exit\n");
    int option;
    printf("Option: ");
    scanf("%d", &option);
    //getc(option);
    //scanf("\n");
    if(option == 0) exit(1);
    else if(option == 1){
        system("clear");
        //printf("Press any key to continue.");
        getchar();
        menu2();
    }
    else {
        system("clear");
        //printf("Press any key to continue.");
        getchar();
        menuPassword();
    }
}
void menu2(){
    printf("\t KODEL'S RESTAURANT: Client \t \n \n");
    printf("1. View Menu\n2. Back\n");
    int option;
    printf("Option: ");
    scanf("%d", &option);
    if(option == 0){
        system("clear");
        //printf("Press any key to continue.");
        getchar();
        menu1();
    }
    else if(option == 1){
        system("clear");
        //printf("Press any key to continue.");
        getchar();
        menu3();
    }else if(option==2){
        //getchar();
        //printf("Press any key to continue.");
        getchar();
        system("clear");
        menu1();
    }
}
void menu3(){
    printf("\t KODEL'S RESTAURANT: Menu \t \n \n");
    printList();
    printf("\n1. Place Order\n0. Back\n");
    int option;
    printf("Option: ");
    scanf("%d", &option);
    if(option == 0){
        //printf("Press any key to continue.");
        getchar();
        system("clear");
        menu1();
    }
    else if(option == 1){
        int dish, i=1;
        printf("Your dish: ");
        scanf("%d", &dish);
        dishes *aux;
        dishes aux2;
        aux = begList;
        while(aux!=NULL){
            if(i == dish){
              strcpy(aux2.name, aux->name);
              aux2.price = aux->price;
              addQueue(aux2);
              i++;
            }
            aux = aux->nextDish;
        }
       // printf("Order successfully!\n");
        getchar();
        printf("Press any key to continue.");
        getchar();
        system("clear");
        menu3();
    }
}
void menuPassword(){
    int password;
    printf("Password: ");
    scanf("%d", &password);
    if(password == 1503){
        system("clear");
        //printf("Press any key to continue.");
        getchar();
        menu4();
    }
    else{
        getchar();
        printf("Wrong password.\nPress any key to continue.");
        getchar();
        system("clear");
        menu1();
    }

}
void menu4(){
     printf("\t KODEL'S RESTAURANT: Kitchen \t \n \n");
     printf("1. Dishes Queue\n2. Add to Menu\n3. Remove from Menu\n4. Change Menu\n0. Back\n");
     int option;
     printf("Option: ");
     scanf("%d", &option);
     switch(option){
        case 0:
            system("clear");
            getchar();
            menu1();
        case 1:
            system("clear");
            getchar();
            menu8();
        case 2:
           system("clear");
            getchar();
            menu5();
        case 3:
            system("clear");
            getchar();
            menu6();
        case 4:
            system("clear");
            getchar();
            menu7();
     }
}
void menu5(){
    printf("\t KODEL'S RESTAURANT: Add to Menu \t \n \n");
    char name[50];
    float price;
    dishes aux;
    printf("Name: ");
    fgets(name, 50, stdin);
    fflush(stdin);
    printf("Price: ");
    scanf("%f", &price);
    addList(name, price);
    getchar();
    printf("Added successfully!\nPress any key to continue.");
    getchar();
    system("clear");
    menu4();
}
void menu6(){
    printf("\t KODEL'S RESTAURANT: Remove from Menu \t \n \n");
    char name[50];
    printf("Name of the dish you wanna remove: ");
    fgets(name, 50, stdin);
    fflush(stdin);
    removeList(name);
    printf("Press any key to continue.\n");
    //getchar();
    getchar();
    system("clear");
    menu4();
}
void menu7(){
    printf("\t KODEL'S RESTAURANT: Change Menu \t \n \n");
    printf("1. Change name\n2. Change Price\n0.Back\nOption: ");
    int option;
    scanf("%d", &option);
    char cn[50];
    switch(option){
        case 0:
            getchar();
            system("clear");
            menu4();
        case 1:
            printf("Current name: ");
            scanf("\n");
            fgets(cn, 50, stdin);
            fflush(stdin);
            changeDishName(cn);
            printf("Press any key to continue. \n");
            getchar();
            system("clear");
            menu7();
        case 2:
            printf("Dish's name: ");
            scanf("\n");
            fgets(cn, 50, stdin);
            fflush(stdin);
            changeDishPrice(cn);
            printf("Press any key to continue. \n");
            getchar();
            system("clear");
            menu7();

        default:
            menu4();
    }

}
void menu8(){
        int done;
        do{
            printf("\t KODEL'S RESTAURANT: Dishes Queue \t \n \n");
            printQueue();
            printf("1. Done\n0. Back\nOption: ");
            scanf("%d", &done);
            if(done == 1) removeQueue();
            //printf("Press any key to continue.");
            getchar();
            system("clear");
        }while(done!=0);
        //system("clear");
        menu4();
}
int main(){
    getList();
    menu0();
    //printList();
    saveList();
    return 0;
}
menu0(){
    printf("1. Add to Menu\n2. Add to queue");
    printf("Option: ");
    int option;
    scanf("%d", &option);
    switch(option){
        case 1:
            char name[50];
            float price;
            scanf("%s %.2f", name, &price);
            addList(name, price);
        case 2:

    }

}



int main(){



    return 0;
}
