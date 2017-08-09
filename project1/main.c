#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>
#define EXPR_REG ".+@.+\\.[a-z]+"

/*This program solves the following situation in C language:
	A blogger wants a Newsletter service in her blog, so the readers can be notified when the blogger send new posts to the blog. Every reader will be able to subscribe a nickname and a email. No repeats, of course. Everything will be saved in a file who only the blogger has acess.
	Operations: add (Subscribe), remove (Unsubscribe).

	Autor: @carolcruz
	
*/
//Abstract type of data that defines a subscriber, it has a name and a email
typedef struct Sub{
	char nickname[30];
	char email[80];
}subscriber;

int length; //length of the array
subscriber *allSubs; //array of all subscribers
FILE* arquivo; //file

//All functions:
int validEmail(char email[]);
int validNickname(char nickname[]);
void checkEmail(char email[]);
void checkNickname(char nickname[]);
int compare(char n1[], char n2[], char s1[], char s2[]);
void addSorted(subscriber aux);
int add(subscriber aux);
int removed(char nickname[], char email[]);
void unsubscribe(char n[], char e[]);
int binarySearch(char nickname[], char email[]);
int bbNickname(char n[]);
int bbEmail(char em[]);
void saveLength();
void saveSubs();
void getLength();
void getSubs();
int main();
void menuSubscribe();
void menuUnsubscribe();
void shutDown();
void mainMenu();

int main()
{
    getLength();
    getSubs();
    mainMenu();

    return 0;
}

//show the main menu and read the option of the user
void mainMenu(){

     printf("\t MYSTAR BLOG - NEWSLETTER \t \n \n");
     printf("1. SUBSCRIBE\n2.UNSUBSCRIBE\n3.EXIT\n");
     printf("Opcao: ");

     int opcao;
     scanf("%d", &opcao);

     if(opcao==1){
        system("clear");
        menuSubscribe();
     }
     else if(opcao==2){
        system("clear");
        menuUnsubscribe();
     }
     else shutDown();
}

//showed when user choose option 1 (subscribe)
void menuSubscribe(){
    subscriber aux;

    printf("Your nickname: ");
    scanf("\n");
    fgets(aux.nickname, 30, stdin);
    checkNickname(aux.nickname);
    fflush(stdin);

    printf("Your email: ");
    scanf("\n");
    fgets(aux.email, 80, stdin);
    checkEmail(aux.email);
    fflush(stdin);

    add(aux);
    printf("Subscribed!\n");
    printf("Press any key to continue.\n");
    getchar();
    system("clear");
    mainMenu();
}

//showed when user choose option 2 (unsubscribe)
void menuUnsubscribe(){
    char nick[30], email[80];

    printf("Your nickname: ");
    scanf("\n");
    fgets(nick, 30, stdin);
    fflush(stdin);

    printf("Your email: ");
    scanf("\n");
    fgets(email, 80, stdin);
    fflush(stdin);

    unsubscribe(nick, email);
    printf("Press any key to continue.\n");
    getchar();
    system("clear");
    mainMenu();
}

//showed when user choose option 3 (exit). Shut down the program saving the length and allSubs in the files before
void shutDown(){
    arquivo = fopen("subs.txt", "w");
    int i;
    for(i=0; i<length; i++){
        //printf("%s", allSubs[i].nickname);
        //printf("%s", allSubs[i].email);
        fprintf(arquivo, "%s", allSubs[i].nickname);
        fprintf(arquivo, "%s", allSubs[i].email);
    }
    //printf("%d\n", length);
    fclose(arquivo);

    arquivo = fopen("length.txt", "w");
    fprintf(arquivo, "%d", length);
    fclose(arquivo);
    exit(1);
}
//check if the nickname is valid, if true return 1, if false return -1
int validNickname(char nickname[]){
    int i, count = 0;

    if(nickname[0] == '\n')
        return -1;

    for(i = 0; i < strlen(nickname); i++){
        if(isalpha(nickname[i]) || isdigit(nickname[i]))
            count++;
    }

    if(count == (strlen(nickname)-1) && bbNickname(nickname)==-1)
        return 1;
    else
        return -1;
}

//check if the email is valid, if true return 1, if false return -1
int validEmail(char email[])
{
   regex_t reg;
   if(regcomp(&reg,EXPR_REG,REG_EXTENDED|REG_NOSUB) != 0)
      printf("Invalid expression!\n");
   else
   {
      if(regexec(&reg,email,0,(regmatch_t *)NULL,0) == 0 && bbEmail(email)==-1)
         return 1;
      else
         return -1;
   }
}


//user have try again if nickname is invalid
void checkNickname(char nickname[]){
    while(validNickname(nickname) == -1){
        if(bbNickname(nickname)!=-1) printf("Nickname already subscribed. Try again: ");
        else printf("Invalid nickname. Try again: ");
        fgets(nickname, 30, stdin);
        setbuf(stdin, NULL);
    }
}

//user have try again if email is invalid
void checkEmail(char email[]){
    while(validEmail(email) == -1){
        if(bbEmail(email)!=-1) printf("Email already subscribed. Try again: ");
        else printf("Invalid email. Try again: ");
        fgets(email, 80, stdin);
        setbuf(stdin, NULL);
    }
}

//compare the arrays
int compare(char n1[], char n2[], char s1[], char s2[]){
    return strcmp(n1, n2) > 0 ||
            strcmp(n1, n2) == 0 &&
            strcmp(s1, s2) > 0;
}

//add an element in the array sorted
void addSorted(subscriber aux) {
  	int i = length - 1;
	while (i >= 0 && compare(allSubs[i].nickname, aux.nickname, allSubs[i].email, aux.email)) {
    		allSubs[i+1] = allSubs[i];
    		i--;
  	}
  	allSubs[i+1] = aux;
  	length++;
}

int add(subscriber aux){ //add a new subscriber
    	if(binarySearch(aux.nickname, aux.email) != -1){
            printf("Already subscribed.\n");
            return 0;
    	}else{
        allSubs = (subscriber*)realloc(allSubs,(length+1)*sizeof(subscriber));
        addSorted(aux);
	}
}

//returns 1 if found and removed of the array, and -1 if not
int removed(char nickname[], char email[]){
	int i, a = -1;
    	if(binarySearch(nickname, email) != -1){
        	i = binarySearch(nickname, email);
        	while(i < length){
            		allSubs[i] = allSubs[i+1];
            		i++;
        	}
        	a = 1;
        	length--;
    	}

    	if(a == -1)
        return -1;
    else
        return 1;

}

//Unsubscribe the user
void unsubscribe(char n[], char e[]){
    if(removed(n, e) == 1)
        printf("Unsubscribed!\n");
    else
        printf("Not found.\n");
}

int binarySearch(char nickname[], char email[]){ //search the element on the array and return the position, if it's not in the array returns -1
 int e, m, d;     //e = esquerda, m = meio, d = direita
     e = 0;
     d = length-1;

    while(e <= d) {
        m = (e+d)/2;
        if( (strcmp(nickname, allSubs[m].nickname) == 0) && (strcmp(email, allSubs[m].email)) == 0){
            return m;
        }
        else if(strcmp(nickname, allSubs[m].nickname) == 0 && (strcmp(email, allSubs[m].email)) < 0)
            d = m - 1;

        else if(strcmp(nickname, allSubs[m].nickname) == 0 && (strcmp(email, allSubs[m].email)) > 0)
            e = m + 1;

        else if (strcmp(nickname, allSubs[m].nickname) < 0)
            d = m - 1;

        else if ( strcmp(nickname, allSubs[m].nickname) > 0)
            e = m + 1;
    }

    return -1;

}

//check if the nickname is already in the array. Returns -1 if false, and !=-1 if true
int bbNickname(char n[]) {
    int e, m, d;     //e = left, m = middle, d = rigth
    e = 0; d = length-1;

    while(e <= d) {
        m = (e+d)/2;
        if( strcmp(n, allSubs[m].nickname) == 0){
            return m;
        }
        if (strcmp(n, allSubs[m].nickname) < 0)
            d = m - 1;
        else if (strcmp(n, allSubs[m].nickname) > 0)
            e = m + 1;
    }
    return -1;
}

//check if the email is already in the array. Returns -1 if false, and !=-1 if true
int bbEmail(char em[]) {
    int e, m, d;     //e = left, m = middle, d = rigth
    e = 0; d = length-1;

    while(e <= d) {
        m = (e+d)/2;
        if( strcmp(em, allSubs[m].email) == 0){
            return m;
        }
        if (strcmp(em, allSubs[m].email) < 0)
            d = m - 1;
        else if (strcmp(em, allSubs[m].email) > 0)
            e = m + 1;
    }
    return -1;
}

//save the length in the file
void saveLength(){
    arquivo = fopen("length.txt", "wt");
    fprintf(arquivo, "%d", length);
    fclose(arquivo);
}

//save the array in the file
void saveSubs(){
    int i;
    saveLength();
    arquivo = fopen("subs.txt", "w");
      for(i = 0; i <= length; i++){
        fprintf(arquivo, "%s", allSubs[i].nickname);
        fprintf(arquivo, "%s", allSubs[i].email);
      }
    fclose(arquivo);
}

//get the length from the file
void getLength(){
    arquivo = fopen("length.txt", "r");
    fscanf(arquivo, "%d", &length);
    fclose(arquivo);
}

//get all subscribers from the file
void getSubs(){
    getLength();
    allSubs = calloc(length+1,sizeof(subscriber));
    int i;
    arquivo = fopen("subs.txt", "rt");
    for(i = 0; i <= length; i++){
        fgets(allSubs[i].nickname, 30, arquivo);
        fgets(allSubs[i].email, 80, arquivo);
    }
    fclose(arquivo);
}

