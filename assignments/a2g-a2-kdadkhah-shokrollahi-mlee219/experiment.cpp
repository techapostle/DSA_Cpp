/**************************************************************************/
/*                                                                        */
/*   Experiment 1                                                         */
/*                                                                        */
/*   To compile: g++ experiment1.cpp timer.cpp -std=c++0x                 */
/*   Alter this main to help answer your first experiment question        */
/*                                                                        */
/**************************************************************************/

#include "table.h"
#include "timer.h"
#include <string>
#include <iostream>
#include <cstdlib>

const int maxRecords=2000000;

void createData(std::string keys[],int data[],int max);
int main(int argc, char* argv[]){

	if(argc != 3){
		std::cout << "usage: a.out numrecords capacity" << std::endl;
		return 0;
	}

    std::string* keys = new std::string[maxRecords];        //list of test cases. 
    int* data=new int[maxRecords];
    createData(keys,data,maxRecords);

    int numrecords=atoi(argv[1]);
    size_t cap=atoi(argv[2]);


    std::cout << "number of records: " << numrecords << std::endl;
    std::cout << "capacity: " << cap << std::endl;

    LPTable<int> table1(cap);
    ChainingTable<int> table2(cap);


    //create a timer
    Timer T;
 

    for(int i=0;i<numrecords;i++){
    	//start the timer.  think of this like its a stop watch.
    	//this is like pressing the start button
    	T.start();   
    	table1.update(keys[i],data[i]);

    	//stop the timer.  this is like pressing pause on a stop watch
    	T.stop();
    }
    std::cout << "LP Table Time: " << T.currtime() << std::endl;

    Timer T2;
    for(int i=0;i<numrecords;i++){
    	T2.start();
    	table2.update(keys[i],data[i]);
    	T2.stop();
    }
    std::cout << "Chaining Table Time: " << T2.currtime() << std::endl;

}




void createData(std::string keys[],int data[],int max){
	FILE* fp=fopen("dictionary.txt","r");
	int i=0;
	std::string front="A_";
	char curr[50];
	while(fscanf(fp,"%s\n",curr)==1){
		keys[i]=curr;
		data[i]=rand()%100;
		i++;                      
	}
	int numWords=i;
	int j=0;
	while(i<max){
		keys[i]=front+keys[j];
		data[i]=rand()%100;
		i++;
		j++;
		if(j==numWords){
			front[0]+=1;
			j=0;
		}
	}
}

