#include <windows.h>
#include <fcntl.h> 
#include <io.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <conio.h>

int set_screen_size(int x, int y)
{
	HANDLE hcon;
	SMALL_RECT size;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	size.Bottom=y-1;
	size.Top=0;
	size.Left=0;
	size.Right=x-1;
	SetConsoleWindowInfo(hcon,TRUE,&size);
	return TRUE;
}

int main(int argc,char *argv[])
{
	int i,j,k;
	char a;
	set_screen_size(80,66);
	for(i=0;i<256/4;i++){
		for(j=0;j<4;j++){
			k=i+(j*256/4);
			if(k>=' ')
				a=k;
			else if(k<7)
				a=k;
			else if(k>10 && k<13)
				a=k;
			else if(k>13 && k<' ')
				a=k;
			else
				a='.';
			if(k=='\0')
				printf("0x%02X %3i \\0 |  ",k,k);
			else if(k=='\a')
				printf("0x%02X %3i \\a |  ",k,k);
			else if(k=='\b')
				printf("0x%02X %3i \\b |  ",k,k);
			else if(k=='\t')
				printf("0x%02X %3i \\t |  ",k,k);
			else if(k=='\f')
				printf("0x%02X %3i \\f |  ",k,k);
			else if(k=='\n')
				printf("0x%02X %3i \\n |  ",k,k);
			else if(k=='\r')
				printf("0x%02X %3i \\r |  ",k,k,a);
			else
				printf("0x%02X %3i %c  |  ",k,k,a);
		}
		printf("\n");
	}
	printf("\\a=beep (bel)\n");
	getch();
}