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
typedef struct{
	int val;
	char *descrip1;
	char *descrip2;
}VALS;
VALS val[]={
	{0,"NUL","Null char"},
	{1,"SOH","Start of Heading"},
	{2,"STX","Start of Text"},
	{3,"ETX","End of Text"},
	{4,"EOT","End of Transmission"},
	{5,"ENQ","Enquiry"},
	{6,"ACK","Acknowledgment"},
	{7,"BEL","Bell"},
	{8,"BS","Back Space"},
	{9,"HT","Horizontal Tab"},
	{10,"LF","Line Feed"},
	{11,"VT","Vertical Tab"},
	{12,"FF","Form Feed"},
	{13,"CR","Carriage Return"},
	{14,"SO","Shift Out / X-On"},
	{15,"SI","Shift In / X-Off"},
	{16,"DLE","Data Line Escape"},
	{17,"DC1","Device Control 1 (oft. XON)"},
	{18,"DC2","Device Control 2"},
	{19,"DC3","Device Control 3 (oft. XOFF)"},
	{20,"DC4","Device Control 4"},
	{21,"NAK","Negative Acknowledgement"},
	{22,"SYN","Synchronous Idle"},
	{23,"ETB","End of Transmit Block"},
	{24,"CAN","Cancel"},
	{25,"EM","End of Medium"},
	{26,"SUB","Substitute"},
	{27,"ESC","Escape"},
	{28,"FS","File Separator"},
	{29,"GS","Group Separator"},
	{30,"RS","Record Separator"},
	{31,"US","Unit Separator"}
};
int by_name(VALS *v1,VALS *v2)
{
	return strcmp(v1->descrip1,v2->descrip2);
}
int by_val(VALS *v1,VALS *v2)
{
	return v1->val<v2->val ? -1: v1->val==v2->val? 0:1;
}
int show_symbols(int sort_by_name)
{
	int i;
	if(sort_by_name)
		qsort(&val,sizeof(val)/sizeof(VALS),sizeof(VALS),by_name);
	else
		qsort(&val,sizeof(val)/sizeof(VALS),sizeof(VALS),by_val);
	for(i=0;i<sizeof(val)/sizeof(VALS);i++){
		printf("%2i,0x%02X,%3s,%s\n",val[i].val,val[i].val,val[i].descrip1,val[i].descrip2);
	}
	return 0;
}
int main(int argc,char *argv[])
{
	int i,j,k;
	char a;
again:
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
	printf("\\a=beep (bel) F1 symbols sorted name F2 by value\n");
	k=getch();
	if(k==0 || k==0xE0)
		k=getch();
	if(k==0x3B || k==0x3C){
		show_symbols(k==0x3B);
		k=getch();
		if(k==0 || k==0xE0)
			k=getch();
		goto again;
	}
}