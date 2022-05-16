
#include "lab3.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <cstring>

bool test1(std::string& error); 
bool test2(std::string& error); 
bool test3(std::string& error); 
bool test4(std::string& error); 
bool test5(std::string& error); 
bool test6(std::string& error);
bool test7(std::string& error);
bool test8(std::string& error);
bool test9(std::string& error);
bool test10(std::string& error);
bool test11(std::string& error);
bool test12(std::string& error);
bool test13(std::string& error);
bool test14(std::string& error);
bool test15(std::string& error);
bool test16(std::string& error);
bool test17(std::string& error);
bool test18(std::string& error);

const int numTests=18;
typedef bool (*TestPtr)(std::string&);
bool isSame(int array1[],int array2[],int size1,int size2);

int main(void){
    TestPtr runTest[numTests]={test1, test2, test3, test4, test5, 
                               test6, test7,test8, test9, test10,
                               test11,test12, test13, test14, test15,
                           	   test16, test17, test18};
    std::string testSummary[numTests]={

                            "DList: push_front() starting with empty list",
                            "DList: push_back() starting with empty list",
                            "DList: push_front() 3 times then push_back() 3 times",
                            "DList: push_back() 3 times then push_front() 3 times",
                            "DList: pop_front() and pop_back() on empty list",
                            "DList: pop_front() on non-empty list",
                            "DList: pop_back() on non-empty list",
                            "DList: alternating pop_front()/pop_back() on non-empty list",
                            "DList: calling push functions after pop functions",


                            "Sentinel: push_front() starting with empty list",
                            "Sentinel: push_back() starting with empty list",
                            "Sentinel: push_front() 3 times then push_back() 3 times",
                            "Sentinel: push_back() 3 times then push_front() 3 times",
                            "Sentinel: pop_front() and pop_back() on empty list",
                            "Sentinel: pop_front() on non-empty list",
                            "Sentinel: pop_back() on non-empty list",
                            "Sentinel: alternating pop_front()/pop_back()",
                            "Sentinel: calling push functions after pop functions"

                        };
    std::string msg;
    bool result=true;
    int numPassed=0;
    for(int i=0;result && i<numTests;i++){
        result = runTest[i](msg);
        if(!result){
            std::cout << "Test " << i+1 <<" - "<< testSummary[i]<< ": failed." << std::endl;
            std::cout << msg << std::endl;
        }
        else{
            numPassed++;
            std::cout << "Test " << i+1 <<" - "<< testSummary[i]<< ": passed." << std::endl;
        }
    }
    if(numPassed == numTests){
        std::cout << "Congratulations! You have passed testing for Lab3" << std::endl;
        return 0;
    }
    else{
        std::cout << "Looks like you still have some work left to do" << std::endl;
        return 1;
    }
}

bool test1(std::string& error){
	DList<int> list;
	int numItems;
	int data[10];
	int correct[10]={9,8,7,6,5,4,3,2,1,0};
	int reverseCorrect[10]={0,1,2,3,4,5,6,7,8,9};

	int* pcorrect=correct+9;
	bool isGood=true;
	int i;
	for(i=0;isGood && i<10;i++){
		list.push_front(i);
		numItems=list.getData(data);
		if(!isSame(data,pcorrect,numItems,i+1)){
			isGood=false;
		}
		pcorrect--;
	}
	if(!isGood){
		error="Error 1: with DList::push_front()\n";
		error+="bug occured after ";
		error+=std::to_string(i);
		error+="values were added";
	}
	else{
		numItems=list.getReverseData(data);
		if(!isSame(data,reverseCorrect,numItems,10)){
			isGood=false;
			error="Error 1b: with DList::push_front()\n";
			error+="check prev_ links";
		}
	}
	return isGood;
}

bool test2(std::string& error){
	DList<int> list;
	int numItems;
	int data[10];
	int correct[10]={0,1,2,3,4,5,6,7,8,9};
	int reverseCorrect[10]={9,8,7,6,5,4,3,2,1,0};

	bool isGood=true;
	int i;
	for(i=0;isGood && i<10;i++){
		list.push_back(i);
		numItems=list.getData(data);
		if(!isSame(data,correct,numItems,i+1)){
			isGood=false;
		}
	}
	if(!isGood){
		error="Error 2: with DList::push_back()\n";
		error+="bug occured after ";
		error+=std::to_string(i);
		error+="values were added";
	}
	else{
		numItems=list.getReverseData(data);
		if(!isSame(data,reverseCorrect,numItems,10)){
			isGood=false;
			error="Error 2b: with DList::push_back()\n";
			error+="check prev_ links";
		}

	}
	return isGood;

}


bool test3(std::string& error){
	DList<int> list;
	int numItems;
	int data[6];
	int correct[6]={2,1,0,3,4,5};
	int reverseCorrect[6]={5,4,3,0,1,2};

	int* pcorrect=correct+2;
	bool isGood=true;
	int i;
	for(i=0;isGood && i<3;i++){
		list.push_front(i);
		numItems=list.getData(data);
		if(!isSame(data,pcorrect,numItems,i+1)){
			isGood=false;
		}
		pcorrect--;
	}
	if(!isGood){
		error="Error 3: with DList::push_front()\n";
		error+="bug occured after ";
		error+=std::to_string(i);
		error+="values were added";
	}
	else{
		for(i=3;isGood && i<6;i++){
			list.push_back(i);
			numItems=list.getData(data);
			if(!isSame(data,correct,numItems,i+1)){
				isGood=false;
			}		
		}
		if(!isGood){
			error="Error 3b: with DList::push_back() after calling push_front\n";
		}
	}

	if(isGood){
		numItems=list.getReverseData(data);
		if(!isSame(data,reverseCorrect,numItems,6)){
			isGood=false;
			error="Error 3c: with DList::push_front() and/or push_back()\n";
			error+="check prev_ links";
		}
	}
	return isGood;
}


bool test4(std::string& error){
	DList<int> list;
	int numItems;
	int data[6];
	int correct[6]={5,4,3,0,1,2};
	int reverseCorrect[6]={2,1,0,3,4,5};

	int* pcorrect=correct+3;
	bool isGood=true;
	int i;
	for(i=0;isGood && i<3;i++){
		list.push_back(i);
		numItems=list.getData(data);
		if(!isSame(data,pcorrect,numItems,i+1)){
			isGood=false;
		}
		
	}
	if(!isGood){
		error="Error 4: with DList::push_back()\n";
		error+="bug occured after ";
		error+=std::to_string(i);
		error+="values were added";
	}
	else{
		for(i=3;isGood && i<6;i++){
			list.push_front(i);
			pcorrect--;
			numItems=list.getData(data);
			if(!isSame(data,pcorrect,numItems,i+1)){
				isGood=false;
			}		
		}
		if(!isGood){
			error="Error 4b: with DList::push_front() after calling push_back\n";
		}
	}

	if(isGood){
		numItems=list.getReverseData(data);
		if(!isSame(data,reverseCorrect,numItems,6)){
			isGood=false;
			error="Error 4c: with DList::push_front() and/or push_back()\n";
			error+="check prev_ links";
		}
	}
	return isGood;
}

bool test5(std::string& error){
	DList<int> list;
	list.pop_front();
	int correct[1];
	int data[1];
	int numItems=list.getData(data);
	bool isGood=true;

	if(numItems!=0){
		error="Error 5: with DList::pop_front() on empty list\n";
		isGood=false;
	}
	else{
		list.pop_back();
		numItems=list.getData(data);
		if(numItems!=0){
			error="Error 5b: with DList::pop_back() on empty list\n";
			isGood=false;
		}
	}
	return isGood;
}

bool test6(std::string& error){
	DList<int> list;

	int data[10];
	int correct[10]={9,8,7,6,5,4,3,2,1,0};
	int reverseCorrect[10]={0,1,2,3,4,5,6,7,8,9};
	int numItems;
	int* pcorrect=correct;
	bool isGood=true;
	int i;
	for(i=0;i<10;i++){
		list.push_front(i);
	}
	for(i=0;isGood && i<10;i++){
		list.pop_front();
		numItems=list.getData(data);
		pcorrect++;
		if(!isSame(data,pcorrect,numItems,9-i)){
			isGood=false;
			error="Error 6: with DList::pop_front()\n";
			error+="bug occured after ";
			error+=std::to_string(i+1);
			error+=" values were pop_front()";
		}
		else{
			numItems=list.getReverseData(data);
			if(!isSame(data,reverseCorrect,numItems,9-i)){
				isGood=false;
				error="Error 6b: with DList::pop_front()\n";
				error+="Check prev_ links\n";
				error+="bug occured after ";
				error+=std::to_string(i+1);
				error+=" values were pop_front()";
			}
		}

	}
	return isGood;
}

bool test7(std::string& error){
	DList<int> list;

	int data[10];
	int correct[10]={9,8,7,6,5,4,3,2,1,0};
	int reverseCorrect[10]={0,1,2,3,4,5,6,7,8,9};
	int numItems;
	int* pcorrect=reverseCorrect;
	bool isGood=true;
	int i;
	for(i=0;i<10;i++){
		list.push_front(i);
	}
	for(i=0;isGood && i<10;i++){
		list.pop_back();
		numItems=list.getData(data);
		pcorrect++;
		if(!isSame(data,correct,numItems,9-i)){
			isGood=false;
			error="Error 7: with DList::pop_back()\n";
			error+="bug occured after ";
			error+=std::to_string(i+1);
			error+=" values were pop_back()";
		}
		else{
			numItems=list.getReverseData(data);
			if(!isSame(data,pcorrect,numItems,9-i)){
				isGood=false;
				error="Error 7b: with DList::pop_back()\n";
				error+="Check prev_ links\n";
				error+="bug occured after ";
				error+=std::to_string(i+1);
				error+=" values were pop_back()";
			}
		}

	}
	return isGood;
}

bool test8(std::string& error){
	DList<int> list;

	int data[10];
	int correct[10]={9,8,7,6,5,4,3,2,1,0};
	int reverseCorrect[10]={0,1,2,3,4,5,6,7,8,9};
	int numItems;
	int* pcorrect=correct;
	int* rcorrect=reverseCorrect;
	bool isGood=true;
	int i;
	for(i=0;i<10;i++){
		list.push_front(i);
	}
	for(i=0;isGood && i<10;i++){
		if (i%2==0){
			list.pop_front();
			pcorrect++;
		}
		else{
			list.pop_back();
			rcorrect++;
		}

		numItems=list.getData(data);
		if(!isSame(data,pcorrect,numItems,9-i)){
			isGood=false;
			error="Error 8: with DList::pop_back() and pop_front() alternating\n";
		}
		else{
			numItems=list.getReverseData(data);
			if(!isSame(data,rcorrect,numItems,9-i)){
				isGood=false;
				error="Error 8b: with DList::pop_back() and pop_front() alternating\n";
			}
		}

	}
	return isGood;
}

bool test9(std::string& error){
	DList<int> list;

	int data[10];
	int correct[10]={9,8,7,6,5,4,3,2,1,0};
	int reverseCorrect[10]={0,1,2,3,4,5,6,7,8,9};
	int numItems;
	int* pcorrect=correct;
	int* rcorrect=reverseCorrect;
	bool isGood=true;
	int i;
	for(i=0;i<10;i++){
		list.push_front(i);
	}
	list.pop_front();
	list.pop_front();
	list.pop_back();
	list.pop_back();

	list.push_front(8);
	list.push_front(9);
	numItems=list.getData(data);
	if(!isSame(data,correct,numItems,8)){
		isGood=false;
		error="Error 9: bug when push_front() is called after pop_front/pop_back calls\n";
	}
	else{
		numItems=list.getReverseData(data);
		if(!isSame(data,reverseCorrect+2,numItems,8)){
			isGood=false;
			error="Error 9b: bug when push_front() is called after pop_front/pop_back calls\n";
			error+="check prev_ links";
		}
	}
	if(isGood){
		list.push_back(1);
		list.push_back(0);
		numItems=list.getData(data);
		if(!isSame(data,correct,numItems,10)){
			isGood=false;
			error="Error 9c: bug when push_back() is called after pop_front/pop_back calls\n";
		}
		else{
			numItems=list.getReverseData(data);
			if(!isSame(data,reverseCorrect,numItems,10)){
				isGood=false;
				error="Error 9d: bug when push_back() is called after pop_front/pop_back calls\n";
				error+="check prev_ links";
			}
		}

	}

	return isGood;
}



bool test10(std::string& error){
	Sentinel<int> list;
	int numItems;
	int data[10];
	int correct[10]={9,8,7,6,5,4,3,2,1,0};
	int reverseCorrect[10]={0,1,2,3,4,5,6,7,8,9};

	int* pcorrect=correct+9;
	bool isGood=true;
	int i;
	for(i=0;isGood && i<10;i++){
		list.push_front(i);
		numItems=list.getData(data);
		if(!isSame(data,pcorrect,numItems,i+1)){
			isGood=false;
		}
		pcorrect--;
	}
	if(!isGood){
		error="Error 10: with Sentinel::push_front()\n";
		error+="bug occured after ";
		error+=std::to_string(i);
		error+="values were added";
	}
	else{
		numItems=list.getReverseData(data);
		if(!isSame(data,reverseCorrect,numItems,10)){
			isGood=false;
			error="Error 10b: with Sentinel::push_front()\n";
			error+="check prev_ links";
		}
	}
	return isGood;
}

bool test11(std::string& error){
	Sentinel<int> list;
	int numItems;
	int data[10];
	int correct[10]={0,1,2,3,4,5,6,7,8,9};
	int reverseCorrect[10]={9,8,7,6,5,4,3,2,1,0};

	bool isGood=true;
	int i;
	for(i=0;isGood && i<10;i++){
		list.push_back(i);
		numItems=list.getData(data);
		if(!isSame(data,correct,numItems,i+1)){
			isGood=false;
		}
	}
	if(!isGood){
		error="Error 11: with Sentinel::push_back()\n";
		error+="bug occured after ";
		error+=std::to_string(i);
		error+="values were added";
	}
	else{
		numItems=list.getReverseData(data);
		if(!isSame(data,reverseCorrect,numItems,10)){
			isGood=false;
			error="Error 11b: with Sentinel::push_back()\n";
			error+="check prev_ links";
		}

	}
	return isGood;

}


bool test12(std::string& error){
	Sentinel<int> list;
	int numItems;
	int data[6];
	int correct[6]={2,1,0,3,4,5};
	int reverseCorrect[6]={5,4,3,0,1,2};

	int* pcorrect=correct+2;
	bool isGood=true;
	int i;
	for(i=0;isGood && i<3;i++){
		list.push_front(i);
		numItems=list.getData(data);
		if(!isSame(data,pcorrect,numItems,i+1)){
			isGood=false;
		}
		pcorrect--;
	}
	if(!isGood){
		error="Error 12: with Sentinel::push_front()\n";
		error+="bug occured after ";
		error+=std::to_string(i);
		error+="values were added";
	}
	else{
		for(i=3;isGood && i<6;i++){
			list.push_back(i);
			numItems=list.getData(data);
			if(!isSame(data,correct,numItems,i+1)){
				isGood=false;
			}		
		}
		if(!isGood){
			error="Error 12b: with Sentinel::push_back() after calling push_front\n";
		}
	}

	if(isGood){
		numItems=list.getReverseData(data);
		if(!isSame(data,reverseCorrect,numItems,6)){
			isGood=false;
			error="Error 3c: with Sentinel::push_front() and/or push_back()\n";
			error+="check prev_ links";
		}
	}
	return isGood;
}


bool test13(std::string& error){
	Sentinel<int> list;
	int numItems;
	int data[6];
	int correct[6]={5,4,3,0,1,2};
	int reverseCorrect[6]={2,1,0,3,4,5};

	int* pcorrect=correct+3;
	bool isGood=true;
	int i;
	for(i=0;isGood && i<3;i++){
		list.push_back(i);
		numItems=list.getData(data);
		if(!isSame(data,pcorrect,numItems,i+1)){
			isGood=false;
		}
		
	}
	if(!isGood){
		error="Error 13: with Sentinel::push_back()\n";
		error+="bug occured after ";
		error+=std::to_string(i);
		error+="values were added";
	}
	else{
		for(i=3;isGood && i<6;i++){
			list.push_front(i);
			pcorrect--;
			numItems=list.getData(data);
			if(!isSame(data,pcorrect,numItems,i+1)){
				isGood=false;
			}		
		}
		if(!isGood){
			error="Error 13b: with Sentinel::push_front() after calling push_back\n";
		}
	}

	if(isGood){
		numItems=list.getReverseData(data);
		if(!isSame(data,reverseCorrect,numItems,6)){
			isGood=false;
			error="Error 13c: with Sentinel::push_front() and/or push_back()\n";
			error+="check prev_ links";
		}
	}
	return isGood;
}

bool test14(std::string& error){
	Sentinel<int> list;
	list.pop_front();
	int correct[1];
	int data[1];
	int numItems=list.getData(data);
	bool isGood=true;

	if(numItems!=0){
		error="Error 14: with Sentinel::pop_front() on empty list\n";
		isGood=false;
	}
	else{
		list.pop_back();
		numItems=list.getData(data);
		if(numItems!=0){
			error="Error 14b: with Sentinel::pop_back() on empty list\n";
			isGood=false;
		}
	}
	return isGood;
}

bool test15(std::string& error){
	Sentinel<int> list;

	int data[10];
	int correct[10]={9,8,7,6,5,4,3,2,1,0};
	int reverseCorrect[10]={0,1,2,3,4,5,6,7,8,9};
	int numItems;
	int* pcorrect=correct;
	bool isGood=true;
	int i;
	for(i=0;i<10;i++){
		list.push_front(i);
	}
	for(i=0;isGood && i<10;i++){
		list.pop_front();
		numItems=list.getData(data);
		pcorrect++;
		if(!isSame(data,pcorrect,numItems,9-i)){
			isGood=false;
			error="Error 15: with Sentinel::pop_front()\n";
			error+="bug occured after ";
			error+=std::to_string(i+1);
			error+=" values were pop_front()";
		}
		else{
			numItems=list.getReverseData(data);
			if(!isSame(data,reverseCorrect,numItems,9-i)){
				isGood=false;
				error="Error 15b: with Sentinel::pop_front()\n";
				error+="Check prev_ links\n";
				error+="bug occured after ";
				error+=std::to_string(i+1);
				error+=" values were pop_front()";
			}
		}

	}
	return isGood;
}

bool test16(std::string& error){
	Sentinel<int> list;

	int data[10];
	int correct[10]={9,8,7,6,5,4,3,2,1,0};
	int reverseCorrect[10]={0,1,2,3,4,5,6,7,8,9};
	int numItems;
	int* pcorrect=reverseCorrect;
	bool isGood=true;
	int i;
	for(i=0;i<10;i++){
		list.push_front(i);
	}
	for(i=0;isGood && i<10;i++){
		list.pop_back();
		numItems=list.getData(data);
		pcorrect++;
		if(!isSame(data,correct,numItems,9-i)){
			isGood=false;
			error="Error 16: with Sentinel::pop_back()\n";
			error+="bug occured after ";
			error+=std::to_string(i+1);
			error+=" values were pop_back()";
		}
		else{
			numItems=list.getReverseData(data);
			if(!isSame(data,pcorrect,numItems,9-i)){
				isGood=false;
				error="Error 16b: with Sentinel::pop_back()\n";
				error+="Check prev_ links\n";
				error+="bug occured after ";
				error+=std::to_string(i+1);
				error+=" values were pop_back()";
			}
		}

	}
	return isGood;
}

bool test17(std::string& error){
	Sentinel<int> list;

	int data[10];
	int correct[10]={9,8,7,6,5,4,3,2,1,0};
	int reverseCorrect[10]={0,1,2,3,4,5,6,7,8,9};
	int numItems;
	int* pcorrect=correct;
	int* rcorrect=reverseCorrect;
	bool isGood=true;
	int i;
	for(i=0;i<10;i++){
		list.push_front(i);
	}
	for(i=0;isGood && i<10;i++){
		if (i%2==0){
			list.pop_front();
			pcorrect++;
		}
		else{
			list.pop_back();
			rcorrect++;
		}

		numItems=list.getData(data);
		if(!isSame(data,pcorrect,numItems,9-i)){
			isGood=false;
			error="Error 17: with Sentinel::pop_back() and pop_front() alternating\n";
		}
		else{
			numItems=list.getReverseData(data);
			if(!isSame(data,rcorrect,numItems,9-i)){
				isGood=false;
				error="Error 17b: with Sentinel::pop_back() and pop_front() alternating\n";
			}
		}

	}
	return isGood;
}

bool test18(std::string& error){
	Sentinel<int> list;

	int data[10];
	int correct[10]={9,8,7,6,5,4,3,2,1,0};
	int reverseCorrect[10]={0,1,2,3,4,5,6,7,8,9};
	int numItems;
	int* pcorrect=correct;
	int* rcorrect=reverseCorrect;
	bool isGood=true;
	int i;
	for(i=0;i<10;i++){
		list.push_front(i);
	}
	list.pop_front();
	list.pop_front();
	list.pop_back();
	list.pop_back();

	list.push_front(8);
	list.push_front(9);
	numItems=list.getData(data);
	if(!isSame(data,correct,numItems,8)){
		isGood=false;
		error="Error 18: bug when push_front() is called after pop_front/pop_back calls\n";
	}
	else{
		numItems=list.getReverseData(data);
		if(!isSame(data,reverseCorrect+2,numItems,8)){
			isGood=false;
			error="Error 18b: bug when push_front() is called after pop_front/pop_back calls\n";
			error+="check prev_ links";
		}
	}
	if(isGood){
		list.push_back(1);
		list.push_back(0);
		numItems=list.getData(data);
		if(!isSame(data,correct,numItems,10)){
			isGood=false;
			error="Error 18c: bug when push_back() is called after pop_front/pop_back calls\n";
		}
		else{
			numItems=list.getReverseData(data);
			if(!isSame(data,reverseCorrect,numItems,10)){
				isGood=false;
				error="Error 18d: bug when push_back() is called after pop_front/pop_back calls\n";
				error+="check prev_ links";
			}
		}

	}

	return isGood;
}
bool isSame(int array1[],int array2[],int size1,int size2){
	bool rc=true;
	if(size1!=size2){
		rc=false;
	}
	else{

		for(int i=0;rc && i<size1;i++){
			if(array1[i]!=array2[i]){
				rc=false;
			}
		}
	}
	return rc;
}
