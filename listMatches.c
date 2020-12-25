/*
  listMatches.c

	This is not grep. it only looks for the entered string in all the names for all the cards
	and then prints the serial number of the card and the name records
	
	parameters:
		in_str - name of the file containing the data base.
		name - string to be searched for.

	operation:
	- if name is not on the command line, prompt user for it.
	- open the file referenced by in_str.
	- when serial:= is found save it in serial variable.
	- when name:= is found, print serial varible and name:= record
*/

#include </home/dev/Desktop/pgms/cards/cards.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{

	int c;
	int i;
	char buff[MAX_INPUT];
	char serial[MAX_INPUT];
	char name[MAX_INPUT];
	char in_str[MAX_INPUT];

	if (argc == 1){
		printf("Search the names in a specified data base for a string in order to get\n");
		printf("the serial number(s) for cards.\n\n");
		printf("no data base specified, exiting...\n");
		exit(0);
	}

	/* how long is the input filename (and path) */
	c=0;
	while (argv[1][c] != 0) c++;

	if (c<1 || c>MAX_INPUT) {
		printf("Zero lentgh file name is a strange error.\n");
		exit(0);
	}

	i=0;
	while (i!=c) {
		if (argv[1][i] >= ' ') in_str[i]=argv[1][i];
		i++;
	}
	in_str[i]=0;

	if (argc == 3) {
		/* if card name provided on the command line */
		c=0;
		while (argv[2][c] != 0) c++;

		if (c<1 || c>MAX_INPUT) {
			printf("Invalid name\n");
			exit(0);
		}
		i=0;
		while (i!=c) {
			if (argv[2][i] >= ' ') name[i]=argv[2][i];
			i++;
		}
		name[i]=0;
	}

	/* get search string if not from command line */
	if (argc == 2) {
		printf("enter the name string: ");
		fgets(name,MAX_INPUT,stdin);
		c=0;
		while(name[c] != 0){
			if (name[c] < ' ') name[c] = 0;
			c++;
		}
	}
	
	/* at this point, name holds a string to be searched for */

	printf("list matches for %s in %s\n", name, in_str);
	FILE *file = fopen(in_str, "r" );
	if (file==0){
		printf("could not open the file %s\n",in_str);
		exit(0);
	}

	/* go through each record in the file */
	while (fgets(buff, MAX_INPUT,file) != NULL){
		if (strncmp("serial:=", buff, 8)==0) {
			/* hold on to this serial until the next */
			c=0;
			/* copy the serial number to another buffer */
			while (buff[c] != 0){
				/* gets rid of the lf etc */
				if (buff[c] <= ' ') buff[c] = ' ';
				serial[c] = buff[c];
				c++;
			}
			serial[c]='\0';
		} /* end processing serial number */
		if (strncmp("name:=", buff, 6)==0) {
			if (strstr(buff, name) != NULL) {
				printf("%s %s", serial, buff);
			}  /* print if a match */
		} /* end processing name record */
	} /* end loop through card file */

	fclose(file);
	exit(0);
}

