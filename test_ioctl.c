#include <sys/ioctl.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//Declarations
void print_page(FILE *file, struct winsize *ws);
void flip_pages(FILE *file, struct winsize *ws, int page);
//int check_line_length(char* filename,int pos);
//bool check_if_newline(char* input,int count);
char buffer[20] = {0};
int	main(int argc,char *argv[])
{
	FILE* fd = fopen(argv[1],"r");
	struct winsize ws;
	if (ioctl(0,TIOCGWINSZ,&ws)!=0) {
		fprintf(stderr,"TIOCGWINSZ:%s\n",strerror(errno));
		exit(-1);
	}
	flip_pages(fd, &ws, 0);
	printf("row=%d, col=%d, xpixel=%d, ypixel=%d\n",
	ws.ws_row,ws.ws_col,ws.ws_xpixel,ws.ws_ypixel);


	//printf("%s\n",argv[1]); nur zum probieren ob es die richtige File nimmt.

	fclose(fd);
	return 0;
}
void print_page(FILE *file, struct winsize *ws) {
    char *buffer = malloc(sizeof(char) * (ws->ws_col + 1));
    for (int i = 0; i < ws->ws_row && !feof(file); i++) {
        fgets(buffer, ws->ws_col, file);
        printf("%s", buffer);
    }
    free(buffer);
}

void flip_pages(FILE *file, struct winsize *ws, int page) {
    rewind(file);
    if (file == 0)return;
    char c;
    int count = 0;
    while (count <= page) {
        system("clear");
        print_page(file, ws);
        count++;
    }
    c = getchar();
    if (c == '\n' && !feof(file)) {
        flip_pages(file, ws, page + 1);
    } else if (c == 'b' && page > 0) {
        while (c != '\n')
            c = getchar();
        flip_pages(file, ws, page - 1);
    } else if (c != '\n') {
        while (c != '\n')
            c = getchar();
        flip_pages(file, ws, page);
    }

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
