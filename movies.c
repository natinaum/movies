#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define END "!END!"
#define TABLE char * * *
#define PATH "./Movies.csv"


int count(char * INPUT,char muster){
	int c=0;
	int i=0;
	while(INPUT[i]!=0){
		if(INPUT[i]==muster){
			c++;
		}
		i++;
	}
	return c;
}

TABLE fromCSV(char * INPUT){
	int L=count(INPUT,'\n');
	int x=L+2;
	int C=count(INPUT,',');
	int y=(C+x-1)/(x-1);
	printf("x: %d\ty: %d\n",x,y);
	TABLE OUTPUT=malloc(sizeof(TABLE)*x);
	for(int i=0;i<x;i++){
		OUTPUT[i]=malloc(sizeof(char * *)*y);
	}
	for(int i=0;i<x;i++){
		for(int j=0;j<y;j++){
			OUTPUT[i][j]=malloc(sizeof(char *));
		}
	}
	int i=-1;
	int a=0;
	int b=0;
	int c=0;
	_Bool outside = 1;
	char tmp;
	while(INPUT[i+1]!=0){
		i++;
		if(INPUT[i]=='"'){
			outside=!outside;
			continue;
		}
		if(!outside){
			tmp=INPUT[i];
			OUTPUT[a][b][c]=tmp;
			c++;
		}
		if(outside){
			OUTPUT[a][b][c]=0;
			if(INPUT[i]==','){
				b++;
			}
			if(INPUT[i]=='\n'){
				b=0;
				a++;
			}
			c=0;
		}
	}
	i++;
	OUTPUT[x-1][0]=END;

	return OUTPUT;
}

int CSVstrLen(TABLE INPUT){
	int length=0;
	for(int i=0;strcmp(INPUT[i][0],END);i++){
		for(int j=0;j<3;j++){
			length=strlen(INPUT[i][j])+3;
		}
		length=length+1;
	}
	return length;
}
char * toCSV(TABLE INPUT){
	int c=0;
	int k=0;
	int l=CSVstrLen(INPUT);
	char * OUTPUT = malloc(l*sizeof(char *));
	for(int i=0;strcmp(INPUT[i][0],END);i++){
		for(int j=0;j<3;j++){
			k=0;
			if(j>0){
				OUTPUT[c]=',';
				c++;
			}
			OUTPUT[c]='"';
			c++;
			while(INPUT[i][j][k]!=0){
				OUTPUT[c]=INPUT[i][j][k];
				c++;
				k++;
			}
			OUTPUT[c]='"';
			c++;
			k++;
		}
		OUTPUT[c]='\n';
		c++;
	}
	return OUTPUT;
}

TABLE read(char * path){
	FILE *f = fopen(path,"r");
	if(f==NULL){
		fputs("OPEN FILE FAILED\n", stderr);
		return NULL;
	}
	fseek(f, 0L, SEEK_END);
	int sz = ftell(f);
	rewind(f);
	char * content = malloc(sz*sizeof(char *));
	while(fgets(content,sz,f)!=NULL);
	return fromCSV(content);
}



int main(){
	char *** TEST=read(PATH);
	char * Test2=toCSV(TEST);
	printf("%s",Test2);
	return 0;


}
