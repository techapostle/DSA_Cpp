/************************************************************/
/*  Lab 4 tester                                            */
/*  To compile:                                             */
/*     g++ lab4tester.cpp -std=c++0x                        */
/*  To run:                                                 */
/*     ./a.out                                              */
/************************************************************/

#include "lab4.h"

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


const int numTests=9;
typedef bool (*TestPtr)(std::string&);
bool isSame(int array1[],int array2[],int size1,int size2);

int main(void){
    TestPtr runTest[numTests]={test1, test2, test3, test4, test5, 
                               test6, test7, test8, test9
                           	   };
    std::string testSummary[numTests]={

                            "cbegin/cend/begin/end/== and != ",
                            "DList const_iterator/iterator prefix ++ and * ",
                            "Sentinel const_iterator/iterator prefix ++ and * ",
                            "DList const_iterator/iterator prefix -- ",
                            "Sentinel const_iterator/iterator prefix -- ",
                            "DList const_iterator/iterator postfix ++ ",                           
							"Sentinel const_iterator/iterator postfix ++ ", 
							"DList const_iterator/iterator postfix -- ",  
							"Sentinel const_iterator/iterator postfix -- ", 
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
        std::cout << "Congratulations! You have passed testing for Lab4" << std::endl;
        return 0;
    }
    else{
        std::cout << "Looks like you still have some work left to do" << std::endl;
        return 1;
    }
}

bool test1(std::string& error){
	DList<int> regular;
	Sentinel<int> sentinel;
	DList<int>::iterator a = regular.begin();
	Sentinel<int>::iterator b = sentinel.begin();
	bool isGood=true;
	error="";
	if(a != regular.end() || a != regular.cend() ||
	   !(a==regular.end()) || !(a==regular.cend())){
		error += "error 1a: c/begin() or c/end() bug for DList\n";
		error += "error could also be in == or !=";
		isGood=false;
	}
	if(b != sentinel.end() || b != sentinel.cend() || 
	   !(b==sentinel.end()) || !(b==sentinel.cend())){
		error+= "error 1b: c/begin() or c/end() bug for Seninel\n";
		error+="error could also be in == or !=";
		isGood=false;
	}
	return isGood;
}

bool test2(std::string& error){
	DList<int> list;
	int listValues[5]={4,3,2,1,0};
	bool isGood=true;
	error="";
	for(int i=0;i<5;i++){
		list.push_front(i);
	}
	DList<int>::const_iterator it;
	int j=0;
	for(it=list.cbegin();isGood && it!=list.cend();++it,j++){
		if(*it != listValues[j]){
			isGood=false;
		}
	}
	if(!isGood){
		error+="Error 2a: check your DList prefix ++ const_iterator (++it)\n";
		return false;
	}
	j=1;
	for(it=list.cbegin();isGood && j<5;j++){
		if(*(++it) != listValues[j]){
			isGood=false;
		}
	}
	if(!isGood){
		error+="Error 2b: check return value from DList prefix++ const_iterator\n";
		return false;
	}

	DList<int>::iterator it2;
	j=0;
	for(it2=list.begin();isGood && it2!=list.end();++it2,j++){
		if(*it2 != listValues[j]){
			isGood=false;
		}
	}
	if(!isGood){
		error+="Error 2c: check your DList prefix ++ iterator (++it)\n";
		return false;
	}
	j=1;
	for(it2=list.begin();isGood && j<5;j++){
		if(*(++it2) != listValues[j]){
			isGood=false;
		}
	}
	if(!isGood){
		error+="Error 2d: check return value from DList prefix++ iterator\n";
		return false;
	}

	for(it2=list.begin();it2!=list.end();++it2){
		*it2+=1;
	}


	j=0;
	for(it2=list.begin();isGood && it2!=list.end();++it2,j++){
		if(*it2 != listValues[j]+1){
			isGood=false;
		}
	}
	if(!isGood){
		error+="Error 2e: updating value through iterator does not appear to work\n";
		return false;
	}

	return isGood;
}


bool test3(std::string& error){
	Sentinel<int> list;
	int listValues[5]={4,3,2,1,0};
	bool isGood=true;
	error="";
	for(int i=0;i<5;i++){
		list.push_front(i);
	}
	Sentinel<int>::const_iterator it;
	int j=0;
	for(it=list.cbegin();isGood && it!=list.cend();++it,j++){
		if(*it != listValues[j]){
			isGood=false;
		}
	}
	if(!isGood){
		error+="Error 3a: check your Sentinel prefix ++ const_iterator (++it)\n";
		return false;
	}
	j=1;
	for(it=list.cbegin();isGood && j<5;j++){
		if(*(++it) != listValues[j]){
			isGood=false;
		}
	}
	if(!isGood){
		error+="Error 3b: check return value from Sentinel prefix++ const_iterator\n";
		return false;
	}

	Sentinel<int>::iterator it2;
	j=0;
	for(it2=list.begin();isGood && it2!=list.end();++it2,j++){
		if(*it2 != listValues[j]){
			isGood=false;
		}
	}
	if(!isGood){
		error+="Error 3c: check your Sentinel prefix ++ iterator (++it)\n";
		return false;
	}
	j=1;
	for(it2=list.begin();isGood && j<5;j++){
		if(*(++it2) != listValues[j]){
			isGood=false;
		}
	}
	if(!isGood){
		error+="Error 3d: check return value from Sentinel prefix++ iterator\n";
		return false;
	}

	for(it2=list.begin();it2!=list.end();++it2){
		*it2+=1;
	}


	j=0;
	for(it2=list.begin();isGood && it2!=list.end();++it2,j++){
		if(*it2 != listValues[j]+1){
			isGood=false;
		}
	}
	if(!isGood){
		error+="Error 3e: updating value through iterator does not appear to work\n";
		return false;
	}

	return isGood;
}


bool test4(std::string& error){
	DList<int> list;
	int listValues[5]={4,3,2,1,0};
	bool isGood=true;
	error="";
	for(int i=0;i<5;i++){
		list.push_front(i);
	}
	DList<int>::const_iterator it=list.cend();
	int j=5;
	while(isGood && it != list.cbegin()){
		--it;
		if(*(it)!=listValues[--j]){
			isGood=false;
		}
	}
	if(!isGood){
		error+="Error 4a: check DList prefix -- const_iterator";
		return false;
	}

	j=5;
	while(isGood && it != list.cbegin()){
		if(*(--it)!=listValues[--j]){
			isGood=false;
		}
	}

	if(!isGood){
		error+="Error 4b: check return value from DList prefix -- const_iterator";
		return false;
	}



	DList<int>::iterator it2=list.end();
	j=5;
	while(isGood && it2 != list.begin()){
		--it2;
		if(*(it2)!=listValues[--j]){
			isGood=false;
		}
	}
	if(!isGood){
		error+="Error 4c: check DList prefix -- iterator";
		return false;
	}

	j=5;
	while(isGood && it2 != list.begin()){
		if(*(--it2)!=listValues[--j]){
			isGood=false;
		}
	}

	if(!isGood){
		error+="Error 4d: check return value from DList prefix -- iterator";
		return false;
	}

	return isGood;
}


bool test5(std::string& error){
	Sentinel<int> list;
	int listValues[5]={4,3,2,1,0};
	bool isGood=true;
	error="";
	for(int i=0;i<5;i++){
		list.push_front(i);
	}
	Sentinel<int>::const_iterator it=list.cend();
	int j=5;
	while(isGood && it != list.cbegin()){
		--it;
		if(*(it)!=listValues[--j]){
			isGood=false;
		}
	}
	if(!isGood){
		error+="Error 5a: check Sentinel prefix -- const_iterator";
		return false;
	}

	j=5;
	while(isGood && it != list.cbegin()){
		if(*(--it)!=listValues[--j]){
			isGood=false;
		}
	}

	if(!isGood){
		error+="Error 5b: check return value from Sentinel prefix -- const_iterator";
		return false;
	}



	Sentinel<int>::iterator it2=list.end();
	j=5;
	while(isGood && it2 != list.begin()){
		--it2;
		if(*(it2)!=listValues[--j]){
			isGood=false;
		}
	}
	if(!isGood){
		error+="Error 5c: check Sentinel prefix -- iterator";
		return false;
	}

	j=5;
	while(isGood && it2 != list.begin()){
		if(*(--it2)!=listValues[--j]){
			isGood=false;
		}
	}

	if(!isGood){
		error+="Error 5d: check return value from Sentinel prefix -- iterator";
		return false;
	}

	return isGood;
}

bool test6(std::string& error){
	DList<int> list;
	int listValues[5]={4,3,2,1,0};
	bool isGood=true;
	error="";
	for(int i=0;i<5;i++){
		list.push_front(i);
	}
	DList<int>::const_iterator it;
	int j=0;
	for(it=list.cbegin();isGood && it!=list.cend();it++,j++){
		if(*it != listValues[j]){
			isGood=false;
		}
	}
	if(!isGood){
		error+="Error 6a: check your DList postfix ++ const_iterator (++it)\n";
		return false;
	}
	j=0;
	for(it=list.cbegin();isGood && j<5;j++){
		if(*(it++) != listValues[j]){
			isGood=false;
		}
	}
	if(!isGood){
		error+="Error 6b: check return value from DList postfix ++ const_iterator\n";
		return false;
	}

	DList<int>::iterator it2;
	j=0;
	for(it2=list.begin();isGood && it2!=list.end();it2++,j++){
		if(*it2 != listValues[j]){
			isGood=false;
		}
	}
	if(!isGood){
		error+="Error 6c: check your DList postfix ++ iterator (++it)\n";
		return false;
	}
	j=0;
	for(it2=list.begin();isGood && j<5;j++){
		if(*(it2++) != listValues[j]){
			isGood=false;
		}
	}
	if(!isGood){
		error+="Error 6d: check return value from DList postfix ++ iterator\n";
		return false;
	}
	it2=list.begin();
	while(it2!=list.end()){
		*(it2++)+=1;
	}


	j=0;
	for(it2=list.begin();isGood && it2!=list.end();it2++,j++){
		if(*it2 != listValues[j]+1){
			isGood=false;
		}
	}
	if(!isGood){
		error+="Error 6e: updating value through iterator does not appear to work\n";
		return false;
	}

	return isGood;
}

bool test7(std::string& error){
	Sentinel<int> list;
	int listValues[5]={4,3,2,1,0};
	bool isGood=true;
	error="";
	for(int i=0;i<5;i++){
		list.push_front(i);
	}
	Sentinel<int>::const_iterator it;
	int j=0;
	for(it=list.cbegin();isGood && it!=list.cend();it++,j++){
		if(*it != listValues[j]){
			isGood=false;
		}
	}
	if(!isGood){
		error+="Error 7a: check your Sentinel postfix ++ const_iterator (++it)\n";
		return false;
	}
	j=0;
	for(it=list.cbegin();isGood && j<5;j++){
		if(*(it++) != listValues[j]){
			isGood=false;
		}
	}
	if(!isGood){
		error+="Error 7b: check return value from Sentinel postfix ++ const_iterator\n";
		return false;
	}

	Sentinel<int>::iterator it2;
	j=0;
	for(it2=list.begin();isGood && it2!=list.end();it2++,j++){
		if(*it2 != listValues[j]){
			isGood=false;
		}
	}
	if(!isGood){
		error+="Error 7c: check your Sentinel postfix ++ iterator (++it)\n";
		return false;
	}
	j=0;
	for(it2=list.begin();isGood && j<5;j++){
		if(*(it2++) != listValues[j]){
			isGood=false;
		}
	}
	if(!isGood){
		error+="Error 7d: check return value from Sentinel postfix ++ iterator\n";
		return false;
	}
	it2=list.begin();
	while(it2!=list.end()){
		*(it2++)+=1;
	}


	j=0;
	for(it2=list.begin();isGood && it2!=list.end();it2++,j++){
		if(*it2 != listValues[j]+1){
			isGood=false;
		}
	}
	if(!isGood){
		error+="Error 7e: updating value through iterator does not appear to work\n";
		return false;
	}

	return isGood;
}


bool test8(std::string& error){
	DList<int> list;
	int listValues[5]={4,3,2,1,0};
	bool isGood=true;
	error="";
	for(int i=0;i<5;i++){
		list.push_front(i);
	}
	DList<int>::const_iterator it=list.cend();
	int j=4;
	while(isGood && it != list.cbegin()){
		it--;
		if(*(it)!=listValues[j--]){
			isGood=false;
		}
	}
	if(!isGood){
		error+="Error 8a: check DList postfix -- const_iterator";
		return false;
	}

	j=4;
	while(isGood && it != list.cbegin()){
		if(*(it--)!=listValues[j--]){
			isGood=false;
		}
	}

	if(!isGood){
		error+="Error 8b: check return value from DList postfix -- const_iterator";
		return false;
	}



	DList<int>::iterator it2=list.end();
	j=4;
	while(isGood && it2 != list.begin()){
		it2--;
		if(*(it2)!=listValues[j--]){
			isGood=false;
		}
	}
	if(!isGood){
		error+="Error 8c: check DList postfix -- iterator";
		return false;
	}

	j=4;
	while(isGood && it2 != list.begin()){
		if(*(it2--)!=listValues[j--]){
			isGood=false;
		}
	}

	if(!isGood){
		error+="Error 8d: check return value from DList postfix -- iterator";
		return false;
	}

	return isGood;
}

bool test9(std::string& error){
	Sentinel<int> list;
	int listValues[5]={4,3,2,1,0};
	bool isGood=true;
	error="";
	for(int i=0;i<5;i++){
		list.push_front(i);
	}
	Sentinel<int>::const_iterator it=list.cend();
	int j=4;
	while(isGood && it != list.cbegin()){
		it--;
		if(*(it)!=listValues[j--]){
			isGood=false;
		}
	}
	if(!isGood){
		error+="Error 9a: check Sentinel postfix -- const_iterator";
		return false;
	}

	j=4;
	while(isGood && it != list.cbegin()){
		if(*(it--)!=listValues[j--]){
			isGood=false;
		}
	}

	if(!isGood){
		error+="Error 9b: check return value from Sentinel postfix -- const_iterator";
		return false;
	}



	Sentinel<int>::iterator it2=list.end();
	j=4;
	while(isGood && it2 != list.begin()){
		it2--;
		if(*(it2)!=listValues[j--]){
			isGood=false;
		}
	}
	if(!isGood){
		error+="Error 9c: check Sentinel postfix -- iterator";
		return false;
	}

	j=4;
	while(isGood && it2 != list.begin()){
		if(*(it2--)!=listValues[j--]){
			isGood=false;
		}
	}

	if(!isGood){
		error+="Error 9d: check return value from Sentinel postfix -- iterator";
		return false;
	}

	return isGood;
}

