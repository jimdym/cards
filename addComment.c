/*
  addComment.c

	This file and addName work the same way. they insert a new record into a file by creating a new file

	parameters:
		in_str - name of the file containing the data base.
		out_str - name of temp file to contain the new data base.
		optionally serial

	prompt the user for the comment if serial not on command line

	open the file referenced by in_str.

	scan in_str, writing each record to out_str

	when the serial is found, continue until the next serial is found, 

	write the comment, then the next serial and resume scanning and writing.

*/

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
	char comment[MAX_INPUT];
	char ser[MAX_INPUT];
	char serno[MAX_INPUT]; /* holds the serial to be updated */
	int slen; /* length of the serial number string for compare */
	char buff[MAX_INPUT]; /* buffer for input file */
	char buff1[MAX_INPUT];
	char in_str[MAX_INPUT]; /* input data base */
	char out_str[MAX_INPUT]; /* new data base */

	if (argc < 3 || argc > 4){
		printf("Wrong number of arguments specified...\n");
		printf("Syntax: ./add_comments data_base new_data_base [serial]\n");
		exit(0);
	}
	/* read the passed filenames */
	c=0;
	while (argv[1][c] != 0) c++;
	i=0;
	while (i!=c) {
		if (argv[1][i] >= ' ') in_str[i]=argv[1][i];
		i++;
	}
	in_str[i]=0; /* the current data base */

	c=0;
	while (argv[2][c] != 0) c++;
	i=0;
	while (i!=c) {
		if (argv[2][i] >= ' ') out_str[i]=argv[2][i];
		i++;
	}
	out_str[i]=0; /* the temporary copy of the data base */

	/* if there's a serial number on the command line */
	if (argc==4){
		c=0;
		while (argv[3][c] != 0) c++;
		i=0;
		while (i!=c) {
			if (argv[3][i] >= ' ') ser[i]=argv[3][i];
			i++;
		}
		ser[i]=0;
		c++;
	}

	/* get date as a string in a buffer because we're going to add a comment */
	time_t rawtime;
	struct tm *info;
	char buffer[80];
	char res[80]; /* buffer to hold time stamp for the comment */
	time( &rawtime );
	info = localtime( &rawtime );
	strftime(buffer,80,"%F - %I:%M%p", info);

	v=0;
	for (i=0;i<10;i++){
		if (buffer[i]>='0' && buffer[i] <='9'){
			res[v]=buffer[i];
			v++;
		}
	}
	res[v]=0; /* the time stamp format i prefer */

	if (argc == 3){
		/* prompt user for serial number he can get that from list_names */
		printf("Use list_names to find the appropriate serial.\n");
		printf("Enter the serial you wish to add a comment to: ");
		fgets(ser,MAX_INPUT,stdin);
		/* format the serial number */
		c=0;
		while(ser[c] != 0){
			if (ser[c] < ' ') ser[c] = 0;
			c++;
		}
	}

	/* ser is the serial of the card to which we're going to add the comment */

	slen = 8 + c -1; /* for use in strncmp */
	serno[0]=0;
	strcat(serno, "serial:=");
	strcat(serno, ser);

	printf("Enter the comment: ");
	fgets(comment,MAX_INPUT,stdin);

	/* the comment at this point is in comment */

	FILE *file = fopen(in_str, "r" );
	if (file==0){
		printf("could not open the file %s\n",in_str);
		printf("crashing out.\n");
		exit(0);
	}

	FILE *ofile = fopen(out_str, "w"); 

	/* loop through the data base writing it to the new data base file */
	while (fgets(buff, MAX_INPUT,file) != NULL){
		fputs(buff,ofile);
		if (strncmp(serno, buff, slen)==0) { /* keep going until the next serial number
												then insert the comment before that */
			while (fgets(buff, MAX_INPUT, file) != NULL) {
				if (strncmp("serial:=",buff,8) == 0){
					fprintf(ofile,"comment:=%s %s",res, comment);
					fputs(buff,ofile);
					break;
				}
				fputs(buff, ofile);
			}
		}
	} /* end while looping through file */	

	fclose(ofile);
	fclose(file);

	printf("\n\nBe sure to rename the temporary file if you're happy with it.\n");
	printf("and encourage your local programmer to automat the process.\n");

	exit(0);
}

