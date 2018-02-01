#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Sukhbir Singh
//656070034
//CS 201 Fall 2016
//Project 3
//Movie Review Hashtable
/*
Description: In this project, I create a hash table using two files containing data
pertaining to movies. This hash table method allows for faster finding of movies and all
reviews.
*/

typedef struct movie * MOV;
typedef struct genre * GENRE;
typedef struct review * REV;

struct genre
    {
    char *name;
    GENRE next;
    };


struct movie
    {
    char *name;
    GENRE nextGenre;
    MOV nextMovie;
    REV nextReview;
    };

struct review
    {
    float stars;
    int userid;
    REV next;
    };

void scrape_newlines(char *input)
    {
    	if (!input) { return; }
    	int i;
    	int len;
    	len = strlen(input);
    	for (i=0; i<len; i++) {
    		if (*(input + i) == 10 || *(input + i) == 13) {
    			if (*(input + i + 1) == 0) {
    				*(input + i) = 0;
    			} else {
    				*(input + i) = 0;
    			}
    		}
    	}
    	return;
    }

int hashValue(char * S, int size)
{
    //returns integer value based on data from MOV
    int val =0;
    int len = strlen(S);
    //printf("\nString len: %i",len);
    int i;

    for (i=0;i<len;i++)
    {
        val += i* S[i] * S[i] * S[i];
        val = val % size;
    }



    return val ;//% size;
}



void getLine(FILE *file, char * word)
    {
    fscanf(file,"%[^\n]%*c",word);
    //printf("\n%s",word);
    }


GENRE insertGEN(GENRE head, char * name)
{
    if (head==NULL)
    {
        head = malloc(sizeof(struct genre));
        head ->name = malloc(sizeof(char)*250);
        strcpy(head->name,name);
        head->next=NULL;
    }
    else
        {
        GENRE temp = head;
        GENRE newGEN = malloc(sizeof(struct genre));
        newGEN->next=NULL;
        newGEN -> name = malloc(sizeof(char)*250);
        strcpy(newGEN->name,name);
        while (temp->next!=NULL)
            temp = temp->next;

        temp ->next = newGEN;
        }
    return head;

}

GENRE listGenres(char * genres)
{

    GENRE head = NULL;
    char * temp= malloc(sizeof(char)*250);
    int finished = 0;
    int marker = 0;
    int end = strlen(genres);
    while (!finished)
    {

        strcpy(temp,marker + genres);
        strtok(temp,"|");
        marker += 1 + strlen(temp);//Adding gets rid of vertical bar
        head = insertGEN(head,temp);
        if (marker >= end)
            finished=1;
    }
    free(temp);
    return head;
    /*GENRE head = NULL;
    int len = strlen(genres);
    char * tempstr = malloc(sizeof(char)*250);
    int marker = 0;
    int i;
    for(i=0;i<len+1;i++)
    {
        if (genres[i]=='|' || genres[i]=='\0')
        {
            genres[i]='\0';
            strcpy(tempstr,marker+genres);
            head = insertGEN(head,tempstr);
            marker = i+1;

        }
    }
    */


}
void token1 (char *word, char * movie_name, char * genres )
{

    char ch;
    int inc=0;
    int namefound = 0;

    while (!namefound)
    {
        ch = *(word+inc);
        inc++;
        if (ch==',')
        {
            ch = *(word+inc);
            if (ch != ' ')
                namefound = 1;
        }

    }
    memcpy(movie_name,word,inc);
    *(movie_name+inc - 1) = '\0';
    strcpy(genres,word+inc);


}//end token



MOV insertMOV(MOV head, char * name, char * genres)
{
    if (head==NULL)
    {
        head = malloc(sizeof(struct movie));
        head ->name = malloc(sizeof(char)*250);
        strcpy(head->name,name);
        head->nextMovie=NULL;
        head->nextGenre=NULL;
        head->nextReview=NULL;
        head -> nextGenre = listGenres(genres);
    }

    else
        {
        MOV temp = head;
        MOV newMOV = malloc(sizeof(struct movie));
        newMOV->nextMovie=NULL;
        newMOV -> name = malloc(sizeof(char)*250);
        newMOV -> nextGenre = NULL;
        newMOV -> nextGenre = listGenres(genres);
        newMOV -> nextReview = 0;
        strcpy(newMOV->name,name);
    while (temp->nextMovie!=NULL)
        temp = temp->nextMovie;

    temp ->nextMovie = newMOV;
        }
    return head;

}



void makeHashTable(FILE *fileptr,int hashtab [],int size, MOV database[])
{
    /*Fills a hash table with pointers to movie structs*/
    char *word = malloc(sizeof(char)*250);
    char *mov_name = malloc(sizeof(char)*250);
    char *genres = malloc(sizeof(char)*250);
    int index;
    int count = 0;


    getLine(fileptr,word);//Eliminate First line


    while (getc(fileptr)!=EOF)
        {
        fseek(fileptr,-1,SEEK_CUR);
        getLine(fileptr,word);
        token1(word,mov_name,genres);
        index = hashValue(mov_name,size);
        //if (index==336) printf("\n%s",mov_name);
        hashtab[index]++;
        //printf("\nh1");
        database[index] = insertMOV(database[index],mov_name,genres);

        //printf("h2");
        }
    free(mov_name);
    free(genres);
    free(word);


}
void token2(char * word, int * user, float * stars, char * mov_name)
{
    //Since there is finite amount of elements, tokenizing is easy
    char * tok = malloc(sizeof(char)*250);
    char buff[20] = "";
    strcpy(tok,word);
    //printf("%s",tok);
    //getchar();
    strtok(tok,",");


    *user = atoi(tok);//Get user ID

    int len1 = strlen(tok) + 1 ;//Add 2 to exclude comma

    strcpy(tok,len1+word);

    strtok(tok,",");//tok contains rating
    int i;
    for (i=0;i<strlen(tok);i++)
        buff[i]= *(tok+i);
    buff[i]='\0';

    sscanf(buff,"%f",stars);

    //printf("\n%s %s %f",tok,buff,*stars);

    int len2 = strlen(tok) + 1;

    strcpy(mov_name,len1+len2 + word);
    printf("%s\n", mov_name);
    scrape_newlines(mov_name);
    //printf("\n%s",mov_name);
    //getchar();

    free(tok);
    //get user id


}

REV insertREV(REV head, int user, float stars)
{
        if (head==NULL)
    {
            printf("gns1\n");
        head = malloc(sizeof(struct review));
        head->stars = stars;
        head->userid = user;
        head->next=NULL;
    }
    else
        {
                printf("gns2\n");
        REV temp = head;
        REV newREV = malloc(sizeof(struct review));
        newREV->next=NULL;
        newREV->stars=stars;
        newREV->userid=user;
    while (temp->next!=NULL)
        temp = temp->next;

    temp ->next = newREV;
        }
    return head;


}

void augmentTable(FILE *fileptr,int size,MOV database[])
{
    /*Modify table to include access to genres and reviews */
    float stars =0;
    int user=0;
    char *word = malloc(sizeof(char)*250);
    char *mov_name = malloc(sizeof(char)*250);
    int index;
    int count = 0;
    MOV temp=NULL;

    getLine(fileptr,word);//Eliminate First line

    while (getc(fileptr)!=EOF)
        {
        fseek(fileptr,-1,SEEK_CUR);
        getLine(fileptr,word);
        //printf("\nh1");
        token2(word,&user,&stars,mov_name);
        printf("h2\n");
        index = hashValue(mov_name,size);
        temp = database[index];
        count++;
       //if (count<10) printf("\naug:%i %.2f",user,stars);
        //Check which of the
        if (temp !=NULL)
        {
            printf("h1\n");
            while (temp->nextMovie!=NULL)
                {

                if (strcmp(mov_name,temp->name)==0 || temp->nextMovie==NULL)
                    break;
                temp=temp->nextMovie;
                }
                //printf("h2");
                //printf("\nh3");
            if ( temp!=NULL && strcmp(mov_name,temp->name)==0)
            {   //
                printf("h4\n");
                temp->nextReview = insertREV(temp->nextReview,user,stars);
                printf("h5\n");
            }
        }
        //Check which of the
        //database[index]->nextReview = insertREV(database[index]->nextReview,,genres);


        }
    free(temp);
    free(mov_name);
    free(word);

}


void printGEN(GENRE head)
{

    if (head==NULL)
        printf("\nNULL2");
    else
    {

        while(head!=NULL)
        {
            printf("\n\t%s",head->name);
            head= head->next;
        }
    }

}

float avgREV(REV head)
{
    float avg = 0;
    if (head==NULL)
        printf(" NULL3");
    else
    {
        int count = 0;
        float sum =0;


        while(head!=NULL)
        {
            count++;
            sum+=head->stars;
            head= head->next;
        }
        avg = sum/count;
    }
    return avg;
}

void printREV(REV head)
{

    if (head==NULL)
        printf(" NULL3");
    else
    {

        while(head!=NULL)
        {
            printf(" %i:%.2f ",head->userid,head->stars);
            head= head->next;
        }
    }

}





void printMOV(MOV head)
{
    printf("\n----------");
    if (head==NULL)
        printf("\nNULL1");
    else
    {

        while(head!=NULL)
        {
            printf("\n%s",head->name);
            printREV(head->nextReview);
            printGEN(head->nextGenre);
            head= head->nextMovie;

        }
    }
    printf("\n----------");
}




int main(void)
{


    //
    int HTsize=20000;
    int hashTab[HTsize];
    MOV database[HTsize];
    int i;
    for (i=0;i<HTsize;i++)
    {
        hashTab[i]=0;
        database[i]=NULL;
    }
    //Get user input for movie
    printf("\nWelcome to the movie review database! Read README.txt");
    printf("\nEnter movie names with title included.");
    printf("\nMake sure movies_proj.csv and ratings_names.csv exist in same folder");
    char buffer[80];



    FILE *fileptr = fopen("movies_proj.csv","r");
    makeHashTable(fileptr,hashTab,HTsize,database);
    fclose(fileptr);
    printf("\n\nStatus: Hash Table Created with name and genres");
    printf("\nNow proceed to adding reviews (Errors are a result of unavailable memory)");
    printf("\nIn the event of error, try waiting a few seconds before re-executing code.");
    printf("\nUnfortunately, this may take several tries.");


    fileptr = fopen("ratings_names.csv","r");
    augmentTable(fileptr,HTsize,database);
    fclose(fileptr);
    printf("\n\nStatus: Reviews successfully added");

    int cont = 1;
    int found;
    int index1;
    MOV iter;
    int count1 = 0;
    float avg;

    char * mystr = malloc(sizeof(char)*250);
    while (cont)
    {
    found = 0;
    printf("\n\nEnter Movie Title (or -1 to exit): ");

    scanf("%[^\n]%*c",buffer);//I use same method as in my project 2 for input, I like this method

    printf("\nYou Entered: %s",buffer);
    //printf("\nlen:%i",strlen(buffer));
    if (buffer[0]=='-' && buffer[1]=='1' )
        {
        cont = 0;
        continue;
        }

    strcpy(mystr,buffer);
    index1 = hashValue(mystr,HTsize);
    if (database[index1] != NULL)
        {


            iter = database[index1];
            while(iter!=NULL)
                {
                    //printf("\n%s",iter->name);
                    if (strcmp(iter->name,mystr)==0)
                        {
                        found =1;
                        break;
                        }
                    iter=iter->nextMovie;
                }

        }

        if (found)
        {
            printf("\nFound!");
            printf("\nReviews (userid:stars)");
            printREV(iter->nextReview);
            avg = avgREV(iter->nextReview);
            printf("\nAverage Review:%.2f",avg);
        }
        else
            printf("\nNot found");
    }

    free(mystr);
    printf("\nGoodBye!");
    //The code below serves to free memory
    MOV temp1,temp2;
    GENRE temp4,temp5;
    REV temp6,temp7;

    for (i=0;i<HTsize;i++)
    {
        if (database[i]!=NULL)
        {
            temp1 = database[i];

            while(temp1!=NULL)
            {
                temp4 = temp1->nextGenre;
                while(temp4!=NULL)
                {
                    temp5 = temp4;
                    temp4 = temp4->next;
                    free(temp5->name);
                    free(temp5);
                }
                free(temp4);

                temp6 = temp1->nextReview;
                while(temp6!=NULL)
                {
                    temp7 = temp6;
                    temp6 = temp6->next;
                    free(temp7);
                }
                free(temp6);

                temp2 = temp1;
                temp1 = temp1->nextMovie;
                free(temp2->name);
                free(temp2);

            }

        }
    }

return 0;
}
