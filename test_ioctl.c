#include <sys/ioctl.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//Declarations

//int check_line_length(char* filename,int pos);
//bool check_if_newline(char* input,int count);
char buffer[20] = {0};
int	main(int argc,char *argv[])
{
	struct winsize ws;
	if (ioctl(0,TIOCGWINSZ,&ws)!=0) {
		fprintf(stderr,"TIOCGWINSZ:%s\n",strerror(errno));
		exit(-1);
	}
	printf("row=%d, col=%d, xpixel=%d, ypixel=%d\n",
	ws.ws_row,ws.ws_col,ws.ws_xpixel,ws.ws_ypixel);

	FILE* fd = fopen(argv[1],"r");
	//printf("%s\n",argv[1]); nur zum probieren ob es die richtige File nimmt.

	printf("\n");
	int line = 0;
	int page_number = 0;
	char* input;
	bool end = false;
	while(!end)
	{
		//int length = check_line_length(argv[1],pos);
		//pos = length;
		if(feof(fd))
		{
			printf("You have reached the last page of this text.\n");
			end = true;
		}
		else if(line != ws.ws_row-2)
		{
			char* string = fgets(buffer,ws.ws_col,fd);
			line++;
			if(string == buffer)
			{
				printf("%s",string);
			}
		}
		else{
			printf("Write 'return' to go to the next page, or write 'b return' to go back a page\n");
			scanf("%c",input);
			if(input == 'return'){line = 0;page_number++;}
			else if(input == 'b return' && page_number != 0){
				page_number--;
				line = 0;
			}
			else{
				printf("This action was not possible\n");
			}
		}

		//end = check_if_newline(buffer,read_count);Aufrufen der Probe Funktion "check_if_newline".
	}





	fclose(fd);
	return 0;
}
/*int check_line_length(char* filename,int pos)
{
	FILE* file = fopen(filename,"r");
	char* output;
	char input[20] = {0};
	output = fgets(input,20,file);

	int count = 0;
	while (output[0] != '\n' && !feof(file)) {
		output = fgets(input,20,file);

		for (int i = 0; i < 20; i++) {
			count++;
			if(output[i] == '\n')
			{
				fclose(file);
				return count;
			}
		}
	}
	fclose(file);
	return count;
}*/ // Falsche Idee gehabt. Funktioniert halbwegs.
/*bool check_if_newline(char* input,int count)
{
	for (int i = 0; i < count; i++) {
		if(input[i] == '\n')
		{
			return true;
		}
	}
	return false;
}*/ // Eine Funktion die das Zeilen Ende findet. Nicht verlangt! Nur zum üben.
