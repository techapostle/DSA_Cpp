#include <iostream>
#include <cstdlib>
#include <cstdio>

const int MAX = 1000;
unsigned int challenge(unsigned int data[], unsigned int numData, unsigned int goal);
int readLines(const char* fname, char* line[],int max);

int main(int argc, char* argv[]){

	char* lines[2000]={0};
	int numLines=readLines("lab1challenge.txt",lines,1000);
	unsigned int values[2000];
	for(int i=0;i<numLines;i++){
		values[i]=atoi(lines[i]);
	}
	std::cout << challenge(values,numLines,2020) << std::endl;
}

/* This function finds the two values in the array data that 
sum to goal and returns their product. */
unsigned int challenge(unsigned int data[], unsigned int numData, unsigned int goal){

}

int readLines(const char* fname, char* line[],int max){
	FILE* fp=fopen(fname,"r");
	int rc=0;
	if(!fp){
		std::cout << "unable to open " << fname << std::endl;
		return 0;
	}
	else{
		size_t len;
		while(rc<max && getline(&line[rc], &len, fp)!=-1 ){
			//fscanf(fp,"%[^\n]\n",line[rc]);
			int lineLength=strlen(line[rc]);
			line[rc][lineLength-1]='\0';
			rc++;
		}
		fclose(fp);
	}
	return rc;

}