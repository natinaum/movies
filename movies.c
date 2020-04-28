#include<stdio.h>
#include<stdlib.h>
int count(char * INPUT,char muster){
	int c=0;
	int i=0;
	while(INPUT[i]!=0){
		if(INPUT[i]==muster){
			c++;
		}
		i++;
	}
	printf("%c %d\n",muster,c);
	return c;
}

char * * * fromCSV(char * INPUT){
	printf("INIT FROMCSV\n");
	int size = 2*2*8;
	printf("SIZE: %d\n",size);
	char * * * OUTPUT=malloc(sizeof(char * *)*2);
	for(int i=0;i<2;i++){
		OUTPUT[i]=malloc(sizeof(char * *)*2);
	}

	for(int i=0;i<2;i++){
		for(int j=0;j<2;j++){
			OUTPUT[i][j]=malloc(sizeof(char *));
		}
	}
	if(OUTPUT==0) printf("WHY\n"); else printf("OK\n");
	int i=-1;
	int a=0;
	int b=0;
	int c=0;
	_Bool outside = 1;
	char tmp;
	printf("ADDR: 0x%010x\n",*OUTPUT);
	printf("MAIN LOOP FROMCSV\n");
	while(INPUT[i+1]!=0){
		i++;
		printf("%d\n",i);
		if(INPUT[i]=='"'){
			outside=!outside;
			continue;
		}
		printf("outside\n");
		if(!outside){
			printf("%d, %d, %d\n",a,b,c);
			tmp=INPUT[i];
			OUTPUT[a][b][c]=tmp;
			c++;
		}
		printf("outside end\n");
		if(outside){
			printf("1\n");
			OUTPUT[a][b][c]=0;
			printf("1\n");
			if(INPUT[i]==','){
				b++;
			}
			printf("2\n");
			if(INPUT[i]=='\n'){
				b=0;
				a++;
			}
			printf("3\n");
			c=0;
		}
	}

	printf("END FROMCSV\n");
	return OUTPUT;
}

int main(){
	char *** TEST=fromCSV("\"HALLO\",\"WELT\"\n\"Wie\",\"gehts\"");
	for(int i=0;i<2;i++){
		for(int j=0;j<2;j++){
			printf("%s\t",TEST[i][j]);
		}
		printf("\n");
	}
	return 0;


}
