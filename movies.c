#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define END "!END!"
#define TABLE char * * *
#define PATH "./Movies.csv"


int count(char * INPUT,char muster){ //counts how often a given character is found in INPUT
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

TABLE fromCSV(char * INPUT){//translates a plain csv string into a rectangular array
	int L=count(INPUT,'\n');//counts lines 
	int x=L+1;//calculate x dimension off TABLE
	int C=count(INPUT,',');//counts , cause , are field delimiter in csv
	int y=(C+x-1)/(x-1);//calculate y dimension
	//Reserve Space for Table:
	TABLE OUTPUT=malloc(sizeof(TABLE)*x);
	for(int i=0;i<x;i++){
		OUTPUT[i]=malloc(sizeof(char * *)*y);
	}
	for(int i=0;i<x;i++){
		for(int j=0;j<y;j++){
			OUTPUT[i][j]=malloc(sizeof(char)*200);
		}
	}
	//go through csv string and write each line and field in own array field
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
	//Add End Marker
	i++;
	OUTPUT[x-1][0]=END;
	//return
	return OUTPUT;
}

int CSVstrLen(TABLE INPUT){
	//Takes Table and calculate how many characters a csv version would have
	int length=0;
	for(int i=0;strcmp(INPUT[i][0],END);i++){
		for(int j=0;j<3;j++){
			length=length+strlen(INPUT[i][j])+3;
		}
		length=length+1;
	}
	return length;
}
char * toCSV(TABLE INPUT){//takes table and return string in csv format
	int c=0;
	int k=0;
	int l=CSVstrLen(INPUT);
	char * OUTPUT = malloc(+l*sizeof(char *));
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
	OUTPUT[c]=0;
	return OUTPUT;
}

TABLE read(char * path){//read file with csv and returns a TABLE
	//Open File and check if process was successfull
	FILE *f = fopen(path,"r");
	if(f==NULL){
		fputs("OPEN FILE FAILED\n", stderr);
		return NULL;
	}
	//get file length
	fseek(f, 0L, SEEK_END);
	int sz = ftell(f);
	rewind(f);
	// reserve space for File Content and tmp
	char * content = malloc(sz*sizeof(char *));
	*content=0;
	char * tmp=malloc(50);
	//read file into content and close file
	while(fgets(tmp,50,f)!=NULL)
		strcat(content,tmp);
	fclose(f);
	//return TABLE generated from content String
	return fromCSV(content);
}

_Bool write(char * path, TABLE INPUT){
	FILE * FP = fopen(path, "w");
	if(FP==NULL){
		fputs("FAILED TO OPEN FILE",stderr);
		return 0;
	}
	fprintf(FP,"%s",toCSV(INPUT));
	fclose(FP);
	return 1;
}

void show(int id, int f,TABLE INPUT){
	if(id == 0){
		int max[3]={0};
		int len;
		for(int i=0;strcmp(INPUT[i][0],END);i++){
			for(int j=0;j<3;j++){
				len=strlen(INPUT[i][j]);
				if(max[j]<len){
					max[j]=len;
				}
			}
		}


		for(int i=0;strcmp(INPUT[i][0],END);i++){
			if(i>0) printf("%3d  ",i); else printf(" id  ");
			for(int j=0;j<3;j++){
				printf("%s",INPUT[i][j]);
				for(int k=0;k<4+max[j]-strlen(INPUT[i][j]);k++)
					printf(" ");
	

			}
			printf("\n");
		}
		return;
	}
	if(f==0){
		printf("%d: ",id);
		for(int j=0;j<3;j++){
			printf("%s\t",INPUT[id][j]);
		}
		printf("\n");
		return;
	}
	printf("%s",INPUT[id][f-1]);
	return;
}

TABLE add(char ** entry, TABLE INPUT){
	printf("add1\n");
	int sz=0;
	while(strcmp(INPUT[sz][0],END))sz++;
	TABLE OUTPUT=malloc(sizeof(TABLE)*(sz+2));
	for(int i=0;i<sz;i++){
		OUTPUT[i]=INPUT[i];
	}
	printf("add2\n");
	OUTPUT[sz]=entry;
	printf("add3\n");
	OUTPUT[sz+1]=malloc(sizeof(char**)*3);
	printf("add4\n");
	OUTPUT[sz+1][0]=malloc(sizeof(char*)*10);
	printf("add5\n");
	OUTPUT[sz+1][0][0]=0;
	strcat(OUTPUT[sz+1][0],END);
	return OUTPUT;
}


int main(){
	char ** entry=malloc(3*sizeof(char*));
	entry[0]="Film";
	entry[1]="Watched";
	entry[2]="RATING";
	TABLE TEST=read(PATH);
	show(0,0,add(entry,TEST));
	write("./Test.csv",TEST);
	return 0;
}
