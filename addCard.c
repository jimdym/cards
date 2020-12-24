/*
  addCard.c
  
	add a card to the data base. Note for a new card file use a text
	editor to create a new file with serial:=1 as the only thing in it

	parameters:
		in_str - name of the file containing the data base.
		name - initial card name or title
	syntax:
		$addCard dbname "card name"

	1. open the file referenced by in_str. find the last serial. A future 
		change would be to ask user if file should be created.
	2. prompt user for information about the card to be added: name, initial comment.
	2.1. add a DTS to the start of each comment record.
	3. write collected recordsd to the end of the file
	4. write new serial record to end of file

*/

/* to compile make sure there is a complete path to cards.h */

#include </home/dev/Desktop/pgms/cards/3x5/cards.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>


int main(int argc, char *argv[])
{
	int c;
	int i;
	int v;
	int valid; /* flag for valid user input */
	int fci; /* flash card indicator */
	char buff[MAX_INPUT];
	char name[MAX_INPUT];
	char buff1[MAX_INPUT];
	char in_str[MAX_INPUT];

	if (argc == 1){
		printf("syntax: ./add_person filename [person name]\n");
		printf("\nAdds records (for person name) in the data base specified in filename.\n");
		printf("If person name is not specified, the program prompts for one, and then\n");
		printf("prompts for a comment\n");
		printf("no data base specified, exiting...\n");
		exit(0);
	}
	/* check length of the input filename (and path) */
	c=0;
	while (argv[1][c] != 0) c++;

	if (c<1 || c>MAX_INPUT) {
		printf("Invalid data base file name\n");
		exit(0);
	}
	/* get the card file name */
	i=0;
	while (i!=c) {
		if (argv[1][i] >= ' ') in_str[i]=argv[1][i];
		i++;
	}
	in_str[i]=0;

	if (argc == 3){
		/* extract the card name here */
		c=0;
		while (argv[2][c] != 0) c++;

		if (c<1 || c>MAX_INPUT) {
			printf("Invalid card title to be added to the data base\n");
			exit(0);
		}

		i=0;
		while (i!=c) {
			if (argv[2][i] >= ' ') name[i]=tolower(argv[2][i]);
			i++;
		}
		name[i]=0;
	}

	/* get date as a string in a buffer */
	time_t rawtime;
	struct tm *info;
	char buffer[80];
	char res[80];
	time( &rawtime );
	info = localtime( &rawtime );
	strftime(buffer,80,"%F - %I:%M%p", info);

	c=0;
	for (i=0;i<10;i++){
		if (buffer[i]>='0' && buffer[i] <='9'){
			res[c]=buffer[i];
			c++;
		}
	}
	res[c]=0;

	FILE *file = fopen(in_str, "r" );

	/* find the last serial number */
	if (file==0){
		printf("could not open the file %s\n",in_str);
		printf("file probably does not exist.\n");
		exit(0);
	}
	while (fgets(buff, MAX_INPUT,file) != NULL){
		if (strncmp("serial:=", buff, 8)==0) {
			strcpy(buff1, buff);
		}
	} /* end while looping through file */	

	fclose(file);

	c=8;
	i=0;
	while (buff1[c] != 0){
		buff[i] = buff1[c];
		i++;
		c++;
	}
	buff[i]=0;
	v=atoi(buff);
	v++; 
	/* 
		v holds the last serial number currently on file to be used when the new 
		card is added to the end of the file.
	*/

	if (argc != 3) {
		/* prompt the user for the name if it wasn't already provided */
		printf("Enter the card name: ");
		fgets(buff,MAX_INPUT,stdin);
		/* make it lower case */
		i=0;
		while (buff[i] != 0) {
			name[i] = tolower(buff[i]);
			i++;
		}
		name[i]=0;
	}
	/* and a comment */
	printf("Enter a comment: ");
	fgets(buff1,MAX_INPUT,stdin);
	/* append these to the file along with the new serial */
	file = fopen(in_str, "a" );
	fprintf(file,"name:=%s\n",name);
	if (fci != 0) fprintf(file,"fci:=%d\n",fci);
	fprintf(file,"comment:=%s %s\n",res,buff1);
	fprintf(file,"serial:=%d\n",v);
	fclose(file);

	exit(0);
}

