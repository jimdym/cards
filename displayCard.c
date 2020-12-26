/*
  displayCard.c
  * 
	parameters:
		data base name
		optionally serial of card to be displayed

	1. prompt user for serial if not already provided on command line
	2. open the file referenced by in_str. 
	3.  scan until serial is found
	4. print records until next serial

*/

#include </home/dev/Desktop/pgms/cards/cards.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int c;
	int l;
	int i;
	int found_ser;
	int found_next;
	char buff[MAX_INPUT];
	char buff1[MAX_INPUT];
	char in_str[MAX_INPUT];
	char ser[80];
	char serno[180];

	if (argc == 1){
		printf("no data base specified, exiting...\n");
		exit(0);
	}
	/* how long is the input filename (and path) */
	c=0;
	while (argv[1][c] != 0) c++;

	if (c<1 || c>MAX_INPUT) {
		printf("Invalid data base file name\n");
		exit(0);
	}

	i=0;
	while (i!=c) {
		if (argv[1][i] >= ' ') in_str[i]=argv[1][i];
		i++;
	}
	in_str[i]=0;

	if (argc==3){
		c=0;
		while (argv[2][c] != 0) c++;

		if (c<1 || c>MAX_INPUT) {
			printf("invalid serial specified.\n");
			exit(0);
		}

		i=0;
		while (i!=c) {
			if (argv[2][i] >= ' ') ser[i]=argv[2][i];
			i++;
		}
		ser[i]=0;
		c++; /* to make it come out the same as from data entry */
	}

	if (argc ==2){
		printf("enter the serial number of the person: ");
		fgets(ser,MAX_INPUT,stdin);
		c=0;
		while(ser[c] != 0){
			if (ser[c] < ' ') ser[c] = 0;
			c++;
		}
	}

	c = 8 + c -1; /* for use in strncmp */
	serno[0]=0;
	strcat(serno, "serial:=");
	strcat(serno, ser);

	FILE *file = fopen(in_str, "r" );
	if (file==0){
		printf("could not open the file %s\n",in_str);
		exit(1);
	}

	/* loop to find serno */
	found_ser=FALSE;
	while ((fgets(buff, MAX_INPUT,file) != NULL) && found_ser == FALSE){
		if (strncmp(serno, buff, c)==0) {
			found_ser=TRUE;
		}
	} /* end looking for serial */

	if (found_ser==TRUE){
		printf("%s", buff);
		found_next=FALSE;
		while ((fgets(buff, MAX_INPUT,file) != NULL) && found_next ==FALSE){
			if (strncmp("serial:=", buff, 8) !=0){
				printf("%s", buff);
			} else found_next = TRUE;
		}
	}

	fclose(file);
	exit(0);
}

