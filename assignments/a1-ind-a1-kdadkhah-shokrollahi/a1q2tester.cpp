/**************************************************************************/
/*                                                                        */
/*   A1 part2 tester file                                                 */
/*                                                                        */
/*   To compile: g++ a1q2tester.cpp timer.cpp -std=c++0x                  */
/*   NOTE: if you are working in windows, change the #define              */
/*   PLATFORM line in timer.h, see comments in that file                  */
/*                                                                        */
/**************************************************************************/

#include "dlist.h"
#include "timer.h"
#include <string>
#include <iostream>
#include <cstdlib>


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
const int numTests=13;
typedef bool (*TestPtr)(std::string&);
struct Record{
    std::string word_;
    int count_;
    std::string toString() const{ 
        std::string s="{";
        s+= word_;
        s+= ",";
        s+= std::to_string(count_);
        s+= "}";
        return s;
    }
};
std::ostream& operator<<(std::ostream& os, const Record rec);
bool operator==(const Record& a,const Record& b);
bool operator!=(const Record& a,const Record& b);
void swap(int& a,int& b);

template <typename T>
void mergeArray(T arr[],T tmp[],int startA,int startB,int endB);
template <typename T>
void mergeSort(T arr[],T tmp[],int start,int end);
template <typename T>
void mergeSort(T arr[],int size);
template <typename T>
void removeItem(T arr[],int idx,int sz);
template <typename T>
void duplicateArray(T dest[], const T src[],int sz);
template<typename T>
typename DList<T>::iterator setIterator(DList<T>& list, int idx);
template <typename T>
int search(const T& data, T arr[],int sz);


int main(void){
    TestPtr runTest[numTests]={test1, test2, test3, test4, test5, 
                               test6, test7, test8, test9, test10,
                               test11,test12,test13
                           };
    std::string testSummary[numTests]={
                            "empty lists, size(), empty(), c/begin(), c/end()",
                            "insert(), size(), empty(), c/begin(), c/end()",
                            "insert(), increment operators pre and postfix",
                            "decrement operators pre and postfix",
                            "return values from increment operators",
                            "return values from decrement operators",
                            "search() function return value",
                            "erase(iterator)",
                            "sort(begin(),end())",
                            "sort(from,to)",
                            "copy constructor",
                            "copy assignment operator",
                            "large data set and timing run"
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
        std::cout << "Congratulations! You have passed testing for A1 part 1" << std::endl;
        return 0;
    }
    else{
        std::cout << "Looks like you still have some work left to do" << std::endl;
        return 1;
    }
}
/* test1: Create an empty list, check size(), empty(), begin(), end() 
   cbegin() and cend()
   functions.  test returns true if passed, false otherwise
*/
bool test1(std::string& error){
    DList<Record> theList;
    int result;
    bool rc=true;
    result=theList.size();
    if(result != 0){
        rc=false;
        error = "Error 1a: size() function returned ";
        error += std::to_string(result);
        error += " on an empty list, should return 0." ;        
    }
    if(rc && theList.empty()==false){
        rc=false;
        error = "Error 1b: empty() function returned false on empty list, should return true";
    }
    if(rc && theList.begin() != theList.end()){
        error = "Error 1c: list is empty, begin() and end() should return iterator to same node";
        rc=false;
    }
    if(rc && theList.cbegin() != theList.cend()){
        error = "Error 1d: list is cempty, cbegin() and cend() should return iterator to same node";
        rc=false;
    }
    return rc;
}

/*test2: test insertion and * operators and size(), empty(), begin() and end() are consistent*/
bool test2(std::string& error){
    Record recs[20]={
        {"the",19},
        {"quick",17},
        {"brown ",4},
        {"fox",9},
        {"jumped",10},
        {"over",16},
        {"lazy",12},
        {"dog",8},
        {"Calvin",1},
        {"and",3},
        {"Hobbes",2},
        {"night",15},
        {"watch",20},
        {"captain",5},
        {"carrot",6},
        {"lilac",13},
        {"lavender",11},
        {"lily",14},
        {"coffee",7},
        {"tea",18}
    };
    DList<Record> theList1;
    DList<Record> theList2;


    bool rc=true;
    DList<Record>::iterator it1=theList1.insert(theList1.begin(),recs[0]);
    DList<Record>::iterator it2=theList2.insert(theList2.end(),recs[0]);
   
    if(theList1.size() != 1){
        rc=false;
        error = "Error 2a: size() function returned ";
        error += std::to_string(theList1.size());
        error += ".  size() should return 1" ;        
    }
    if(rc && theList2.size() != 1){
        rc=false;
        error = "Error 2b: size() function returned ";
        error += std::to_string(theList2.size());
        error += ".  size() should return 1" ;        
    }
    if(rc && theList1.empty() == true){
        rc=false;
        error = "Error 2c: empty() function returned true on a non-empty list";
    }
    if(rc && theList2.empty() == true){
        rc=false;
        error = "Error 2d: empty() function returned true on a non-empty list";
    }
    if(rc && theList1.begin() == theList1.end()){
        error = "Error 2d: list is not empty, begin() and end() should return iterator to different nodes";
        rc=false;        
    }  
    if(rc && theList2.begin() == theList2.end()){
        error = "Error 2e: list is not empty, begin() and end() should return iterator to different nodes";
        rc=false;        
    }
    if(rc && theList1.cbegin() == theList1.cend()){
        error = "Error 2f: list is not empty, cbegin() and cend() should return iterator to different nodes";
        rc=false;        
    }
    if(rc && theList2.cbegin() == theList2.cend()){
        error = "Error 2g: list is not empty, cbegin() and cend() should return iterator to different nodes";
        rc=false;        
    }
    if(rc && *(theList1.begin())!= recs[0]){
        error = "Error 2h: first node in list should match record inserted. It does not\n";
        error +="Your data: ";
        error += (*theList1.begin()).toString();
        error += "\nCorrect data: ";
        error += recs[0].toString();
        rc=false;  
    }
    if(rc && *(theList2.begin())!= recs[0]){
        error = "Error 2i: first node in list should match record inserted. It does not\n";
        error +="Your data: ";
        error += (*theList2.begin()).toString();
        error += "\nCorrect data: ";
        error += recs[0].toString();
        rc=false;  
    }
    if(rc && *(theList1.cbegin())!= recs[0]){
        error = "Error 2j: first node in list should match record inserted. It does not\n";
        error +="Your data: ";
        error += (*theList1.cbegin()).toString();
        error += "\nCorrect data: ";
        error += recs[0].toString();
        rc=false;  
    }
    if(rc && *(theList2.cbegin())!= recs[0]){
        error = "Error 2k: first node in list should match record inserted. It does not\n";
        error +="Your data: ";
        error += (*theList2.cbegin()).toString();
        error += "\nCorrect data: ";
        error += recs[0].toString();
        rc=false;  
    }
    if(rc && it1 != theList1.begin()){
        error = "Error 2l: return value from insert() does not point to correct node\n";
        rc=false;  
    }
    if(rc && it2 != theList2.begin()){
        error = "Error 2m: return value from insert() does not point to correct node\n";
        rc=false;  
    }
    return rc;
}

/*test3: further test insertion() function and ++ operators*/
bool test3(std::string& error){
    Record recs[20]={
        {"the",19},
        {"quick",17},
        {"brown ",4},
        {"fox",9},
        {"jumped",10},
        {"over",16},
        {"lazy",12},
        {"dog",8},
        {"Calvin",1},
        {"and",3},
        {"Hobbes",2},
        {"night",15},
        {"watch",20},
        {"captain",5},
        {"carrot",6},
        {"lilac",13},
        {"lavender",11},
        {"lily",14},
        {"coffee",7},
        {"tea",18}
    };

    DList<Record> theList;
    bool rc=true;
    int listSize;
    DList<Record>::iterator it;

    for(int i=0;rc && i<20;i+=2){
        it=theList.insert(theList.end(),recs[i]);
        if(*it != recs[i]){
            error = "Error 3a: Incorrect return value from insert().\n";
            error += "returned node needs to contain inserted value";
            rc=false;
        }
    }
    it=theList.begin();
    for(int i=0; rc && i<20;i+=2){
        if(*it != recs[i]){
            error = "Error 3b: Incorrect data at node.\n  Data at node # ";
            error += std::to_string(i+1);
            error += "(numbered from 1):";
            error += (*it).toString();
            error += "The correct data is";
            error += recs[i].toString();
            error += "\nbug probably in either insert() or iterator::operator++(int)";
            rc=false;
        }
        it++;
    }
    
    DList<Record>::iterator curr= theList.begin();
    curr++;
    for(int i=1;rc && i<20;i+=2){
        it=theList.insert(curr,recs[i]);
        curr++;
        if(*it != recs[i]){
            error = "Error 3c: Incorrect return value from insert().\n";
            error += "returned node needs to contain inserted value";
            rc=false;
        }
    }
    it=theList.begin();
    for(int i=0;rc && i<20;i++){
        if(*it != recs[i]){
            error = "Error 3d: Incorrect data at node.\n  Data at node # ";
            error += std::to_string(i+1);
            error += "(numbered from 1):";
            error += (*it).toString();
            error += "The correct data is";
            error += recs[i].toString();
            error += "\nbug probably in either insert() or iterator::operator++(int)";
            rc=false;
        }
        it++;
    }

    DList<Record>::const_iterator it2= theList.cbegin();
    for(int i=0;rc && i<20;i++){
        if(*it2 != recs[i]){
            error = "Error 3e: Incorrect data at node.\n  Data at node # ";
            error += std::to_string(i+1);
            error += "(numbered from 1):";
            error += (*it2).toString();
            error += "The correct data is";
            error += recs[i].toString();
            error += "\nbug probably in either insert() or const_iterator::operator++(int)";
            rc=false;
        }
        it2++;
    }

    it= theList.begin();
    for(int i=0;rc && i<20;i++){
        if(*it != recs[i]){
            error = "Error 3f: Incorrect data at node.\n  Data at node # ";
            error += std::to_string(i+1);
            error += "(numbered from 1):";
            error += (*it).toString();
            error += "The correct data is";
            error += recs[i].toString();
            error += "\nbug probably in either insert() or iterator::operator++()";
            rc=false;
        }
        ++it;
    }

    it2= theList.cbegin();
    for(int i=0;rc && i<20;i++){
        if(*it2 != recs[i]){
            error = "Error 3g: Incorrect data at node.\n  Data at node # ";
            error += std::to_string(i+1);
            error += "(numbered from 1):";
            error += (*it2).toString();
            error += "The correct data is";
            error += recs[i].toString();
            error += "\nbug probably in either insert() or const_iterator::operator++(int)";
            rc=false;
        }
        ++it2;
    }

    return rc;
}

/*test 4: test decrement (--) operators*/
bool test4(std::string& error){
    Record recs[20]={
        {"the",19},
        {"quick",17},
        {"brown ",4},
        {"fox",9},
        {"jumped",10},
        {"over",16},
        {"lazy",12},
        {"dog",8},
        {"Calvin",1},
        {"and",3},
        {"Hobbes",2},
        {"night",15},
        {"watch",20},
        {"captain",5},
        {"carrot",6},
        {"lilac",13},
        {"lavender",11},
        {"lily",14},
        {"coffee",7},
        {"tea",18}
    };
    DList<Record> theList;
    DList<Record>::iterator it;
    bool rc=true;
    int listSize;
    for(int i=0;rc && i<20;i++){
        it=theList.insert(theList.begin(),recs[i]);
        if(*it != recs[i]){
            error = "Error 4a: Incorrect return value from insert().\n";
            error += "returned node needs to contain inserted value";
            rc=false;
        }

    }
    it = theList.end();
    for(int i=0;rc && i<20;i++){
        it--;
        if(*it != recs[i]){
            error = "Error 4b: Incorrect data at node.\n  Data at node # ";
            error += std::to_string(i+1);
            error += "(numbered from 1):";
            error += (*it).toString();
            error += "The correct data is";
            error += recs[i].toString();
            error += "\nbug probably in either insert() or iterator::operator--(int)";
            rc=false;
        }
    }

    DList<Record>::const_iterator it2 = theList.cend();
    for(int i=0;rc && i<20;i++){
        it2--;
        if(*it2 != recs[i]){
            error = "Error 4c: Incorrect data at node.\n  Data at node # ";
            error += std::to_string(i+1);
            error += "(numbered from 1):";
            error += (*it2).toString();
            error += "The correct data is";
            error += recs[i].toString();
            error += "\nbug probably in either insert() or const_iterator::operator--(int)";
            rc=false;
        }

    }

    it = theList.end();
    for(int i=0;rc && i<20;i++){
        --it;
        if(*it != recs[i]){
            error = "Error 4d: Incorrect data at node.\n  Data at node # ";
            error += std::to_string(i+1);
            error += "(numbered from 1):";
            error += (*it).toString();
            error += "The correct data is";
            error += recs[i].toString();
            error += "\nbug probably in either insert() or iterator::operator--()";
            rc=false;
        }

    }

    it2 = theList.cend();
    for(int i=0;rc && i<20;i++){
        --it2;
        if(*it2 != recs[i]){
            error = "Error 4e: Incorrect data at node.\n  Data at node # ";
            error += std::to_string(i+1);
            error += "(numbered from 1):";
            error += (*it2).toString();
            error += "The correct data is";
            error += recs[i].toString();
            error += "\nbug probably in either insert() or const_iterator::operator--(int)";
            rc=false;
        }

    }

    return rc;

}


/*test 5: Test return values of increment operators*/
bool test5(std::string& error){
    Record recs[20]={
        {"the",19},
        {"quick",17},
        {"brown ",4},
        {"fox",9},
        {"jumped",10},
        {"over",16},
        {"lazy",12},
        {"dog",8},
        {"Calvin",1},
        {"and",3},
        {"Hobbes",2},
        {"night",15},
        {"watch",20},
        {"captain",5},
        {"carrot",6},
        {"lilac",13},
        {"lavender",11},
        {"lily",14},
        {"coffee",7},
        {"tea",18}
    };

    DList<Record> theList;
    bool rc=true;
    int listSize;
    for(int i=0;rc && i<20;i++){
        theList.insert(theList.end(),recs[i]);
    }
    Record rec;
    DList<Record>::iterator it= theList.begin();
    for(int i=0;rc && i<20;i++){
        if((rec = *(it++)) != recs[i]){
            error = "Error 5a: data in node at referred to by *(it++) is not correct\n  Data at node # ";
            error += std::to_string(i+1);
            error += "(numbered from 1):";
            error += (rec).toString();
            error += "The correct data is";
            error += recs[i].toString();
            error += "\nbug probably return of postfix iterator";
            rc=false;
        }
    }
    DList<Record>::const_iterator it2= theList.cbegin();
    for(int i=0;rc && i<20;i++){
        if((rec = *(it2++)) != recs[i]){
            error = "Error 5b: data in node at referred to by *(it++) is not correct\n  Data at node # ";
            error += std::to_string(i+1);
            error += "(numbered from 1):";
            error += (rec).toString();
            error += "The correct data is";
            error += recs[i].toString();
            error += "\nbug probably return of postfix const_iterator";
            rc=false;
        }
    }



    it = theList.begin();

    for(int i=0;rc && i<20;i++){
        if(i<19 && (rec = *(++it)) != recs[i+1] ){
            error = "Error 5c: data in node at referred to by *(++it) is not correct\n  Data at node # ";
            error += std::to_string(i+2);
            error += "(numbered from 1):";
            error += rec.toString();
            error += "The correct data is";
            error += recs[i].toString();
            error += "\nbug probably return of prefix iterator";
            rc=false;
  
        }
    }
    it2= theList.cbegin();
    for(int i=0;rc && i<20;i++){
        if(i<19 && (rec = *(++it2)) != recs[i+1] ){
            error = "Error 5d: data in node at referred to by *(++it) is not correct\n  Data at node # ";
            error += std::to_string(i+2);
            error += "(numbered from 1):";
            error += rec.toString();
            error += "The correct data is";
            error += recs[i].toString();
            error += "\nbug probably return of prefix const_iterator";
            rc=false;

        }
    }

    return rc;
}

/*Test 6: Test return values of decrement operators*/
bool test6(std::string& error){
    Record recs[20]={
        {"the",19},
        {"quick",17},
        {"brown ",4},
        {"fox",9},
        {"jumped",10},
        {"over",16},
        {"lazy",12},
        {"dog",8},
        {"Calvin",1},
        {"and",3},
        {"Hobbes",2},
        {"night",15},
        {"watch",20},
        {"captain",5},
        {"carrot",6},
        {"lilac",13},
        {"lavender",11},
        {"lily",14},
        {"coffee",7},
        {"tea",18}
    };

    DList<Record> theList;
    bool rc=true;
    int listSize;
    for(int i=0;i<20;i++){
        theList.insert(theList.end(),recs[i]);
    }
    DList<Record>::iterator it= theList.end();
    it--;
    Record rec;
    for(int i=19;rc && i>0;i--){
        if((rec = *(it--)) != recs[i]){
            error = "Error 6a: data in node at referred to by *(it--) is not correct\n  Data at node # ";
            error += std::to_string(i+1);
            error += "(numbered from 1):";
            error += rec.toString();
            error += "The correct data is";
            error += recs[i].toString();
            error += "\nbug probably return of postfix iterator";
            rc=false;
        }
    }
    DList<Record>::const_iterator it2= theList.cend();
    it2--;
    for(int i=19;rc && i>0;i--){
        if((rec = *(it2--)) != recs[i]){
            error = "Error 6b: data in node at referred to by *(it--) is not correct\n  Data at node # ";
            error += std::to_string(i+1);
            error += "(numbered from 1):";
            error += rec.toString();
            error += "The correct data is";
            error += recs[i].toString();
            error += "\nbug probably return of postfix const_iterator";
            rc=false;
        }
    }


    it = theList.end();

    for(int i=19;rc && i>0;i--){
        if((rec = *(--it)) != recs[i] ){
            error = "Error 6c: data in node at referred to by *(++it) is not correct\n  Data at node # ";
            error += std::to_string(i+2);
            error += "(numbered from 1):";
            error += rec.toString();
            error += "The correct data is";
            error += recs[i].toString();
            error += "\nbug probably return of prefix iterator";
            rc=false;
  
        }
    }
    it2= theList.cend();
    for(int i=19;rc && i>=0;i--){
        if((rec = *(--it2)) != recs[i] ){
            error = "Error 6d: data in node at referred to by *(++it) is not correct\n  Data at node # ";
            error += std::to_string(i+2);
            error += "(numbered from 1):";
            error += rec.toString();
            error += "The correct data is";
            error += recs[i].toString();
            error += "\nbug probably return of prefix iterator";
            rc=false;

        }
    }

    return rc;

}

/*Test 7: Test search()*/
bool test7(std::string& error){
    Record recs[20]={
        {"the",19},
        {"quick",17},
        {"brown ",4},
        {"fox",9},
        {"jumped",10},
        {"over",16},
        {"lazy",12},
        {"dog",8},
        {"Calvin",1},
        {"and",3},
        {"Hobbes",2},
        {"night",15},
        {"watch",20},
        {"captain",5},
        {"carrot",6},
        {"lilac",13},
        {"lavender",11},
        {"lily",14},
        {"coffee",7},
        {"tea",18}
    };

    DList<Record> theList;
    DList<Record>::iterator result;
    DList<Record>::iterator it;
    bool rc=true;
    int listSize;
    Record mirror[20];
    for(int i=0;rc && i<15;i++){
        theList.insert(theList.end(),recs[i]);
        mirror[i]=recs[i];
    }
    for(int i=0;rc && i<15;i++){
        result=theList.search(recs[i]);
        if(result == theList.end()){
            rc=false;
            error = "Error 7a: item that should have been in the linked list was not found\n";
            error += "item being searched for: ";
            error += recs[i].toString();
        }
        else if(*result != recs[i]){
            rc=false;
            error = "Error 7b: item found was not the one being searched for\n";
            error += "item found: ";
            error += (*result).toString();
            error += "item being searched for: ";
            error += recs[i].toString();
        }
    }
    for(int i=15;rc && i<20;i++){
        result=theList.search(recs[i]);
        if(result != theList.end()){
            rc=false;
            error = "Error 7d: searching for an item that should not be in the list resulted in something that isn't cend() \n";
            error += "item being searched for: ";
            error += recs[i].toString();
        }        
    }
    return rc;
}

/*Test 8: Test erase(it)*/
bool test8(std::string& error){
    Record recs[20]={
        {"the",19},
        {"quick",17},
        {"brown ",4},
        {"fox",9},
        {"jumped",10},
        {"over",16},
        {"lazy",12},
        {"dog",8},
        {"Calvin",1},
        {"and",3},
        {"Hobbes",2},
        {"night",15},
        {"watch",20},
        {"captain",5},
        {"carrot",6},
        {"lilac",13},
        {"lavender",11},
        {"lily",14},
        {"coffee",7},
        {"tea",18}
    };

    DList<Record> theList;
    DList<Record>::iterator result;
    DList<Record>::iterator it;
    Record mirror[20];
    bool rc=true;

    for(int i=0;i<20;i++){
        theList.insert(theList.end(),recs[i]);
        mirror[i]=recs[i];
    }
    for(int i=19; i>= 17;i-- ){
        it=setIterator(theList,i);
        result=theList.erase(it);
        if(result!=theList.end()){
            rc=false;
            error = "Error 8a: when last item in list is erased, return value should be end()";
        }
        else{
            if(theList.search(mirror[i]) != theList.end()){
                rc=false;
                error = "Error 8b: when last item in list is erased, item should not be found in list";
            }
            else if(theList.size() != i){
                rc=false;
                error = "Error 8c: size() is not correct after erase(it) of last node\n your function returned: ";
                error += std::to_string(theList.size());
                error += ".  It should return: ";
                error += std::to_string(i);

            }
        }
    }
    DList<Record>::const_iterator it2=theList.cbegin();
    for(int i=0;rc && i<17;i++){
        if(*it2 !=mirror[i]){
            rc=false;
            error = "Error 8d: a record that was not erased is no longer in list";
        }
        it2++;
    }
    if(rc && it2!=theList.cend()){
        rc=false;
        error = "Error 8e: the list has more records than expected after erasing from end of list";
    }
    for(int i=0;rc && i< 3 ;i++ ){
        it=theList.begin();
        result=theList.erase(it);
        if(result != theList.begin()){
            rc=false;
            error = "Error 8f: when first item in list is erased, return value should be begin()";
        }
        else{
            if(theList.search(mirror[0]) != theList.end()){
                rc=false;
                error = "Error 8g: when first item in list is erased, item should not be found in list";
            }
            else if(theList.size() != 16-i){
                rc=false;
                error = "Error 8h: size() is not correct after erase(it) of first node\n Your function returned: ";
                error += std::to_string(theList.size());
                error += ".  It should return:";
                error += std::to_string(16-i);
            }
        }
        removeItem(mirror,0,17-i);
    }

    it2=theList.cbegin();
    for(int i=0;rc && i<14;i++){
        if(*it2 !=mirror[i]){
            rc=false;
            error = "Error 8i: a record that was not erased is no longer in list";
        }
        it2++;
    }
    if(rc && it2!=theList.cend()){
        rc=false;
        error = "Error 8j: the list has more records than expected after erasing from end of list";
    }

    int listSize=14;
    DList<Record>::iterator next;
    for(int i=1; i< listSize ;i++ ){
        next=setIterator(theList,i);
        result=theList.erase(next++);
        if(result != next){
            rc=false;
            error = "Error 8k: when erasing a node, return value is not the next node in list";
        }
        else{
            if(theList.search(mirror[i]) != theList.end()){
                rc=false;
                error = "Error 8l: when a node in list is erased, item should not be found in list";
            }
            else if(theList.size() != listSize-1){
                rc=false;
                error = "Error 8m: size() is not correct after erase(it) of first node\n Your function returned: ";
                error += std::to_string(theList.size());
                error += ".  It should return:";
                error += std::to_string(16-i);

            }
        }
        removeItem(mirror,i,listSize);
        listSize--;
    }
    it2=theList.cbegin();
    for(int i=0;rc && i<listSize;i++){
        if(*it2 !=mirror[i]){
            rc=false;
            error = "Error 8n: a record that was not erased is no longer in list";
        }
        it2++;
    }
    if(rc && it2!=theList.cend()){
        rc=false;
        error = "Error 8o: the list has more records than expected after erasing from end of list";
    }


    return rc;

}
/*Test 9: test sort(from,to)*/
bool test9(std::string& error){
    Record recs[20]={
        {"the",19},
        {"quick",17},
        {"brown ",4},
        {"fox",9},
        {"jumped",10},
        {"over",16},
        {"lazy",12},
        {"dog",8},
        {"Calvin",1},
        {"and",3},
        {"Hobbes",2},
        {"night",15},
        {"watch",20},
        {"captain",5},
        {"carrot",6},
        {"lilac",13},
        {"lavender",11},
        {"lily",14},
        {"coffee",7},
        {"tea",18}
    };
    bool rc=true;
    DList<Record> theList;
    DList<Record>::const_iterator it;

    for(int i=0;rc && i<20;i++){
        theList.insert(theList.end(),recs[i]);
    }
    theList.sort(theList.begin(), theList.end());
    mergeSort(recs,20);
    it=theList.begin();
    for(int i=0;rc && i<20;i++){
        if(*it != recs[i]){
            rc=false;
            error="Error 9a: records are not in correct order after calling sort(begin(), end()\n";
            error += "Your record: ";
            error += (*it).toString();
            error += "correct data: ";
            error += recs[i].toString();                             
        }
        it++;
    }
    it=theList.cend();
    for(int i=19;rc && i>=0;i--){
        if(*(--it) != recs[i]){
            rc=false;
            error="Error 9b: records are not in correct order after calling sort(begin(), end()\n";
            error += "check your previous pointers\n";
            error += "Your record: ";
            error += (*it).toString();
            error += "correct data: ";
            error += recs[i].toString();                             
        }
    }


    return rc;
}


/*Test 10: test sort(from,to)*/
bool test10(std::string& error){
    Record recs[20]={
        {"the",19},
        {"quick",17},
        {"brown ",4},
        {"fox",9},
        {"jumped",10},
        {"over",16},
        {"lazy",12},
        {"dog",8},
        {"Calvin",1},
        {"and",3},
        {"Hobbes",2},
        {"night",15},
        {"watch",20},
        {"captain",5},
        {"carrot",6},
        {"lilac",13},
        {"lavender",11},
        {"lily",14},
        {"coffee",7},
        {"tea",18}
    };
    bool rc=true;
    DList<Record> theList;
    DList<Record>::iterator it1;
    DList<Record>::iterator it2;
    DList<Record>::const_iterator it;

    for(int i=0;rc && i<20;i++){
        theList.insert(theList.end(),recs[i]);
    }
    it1=theList.begin();
    it2=theList.end();
    for(int i=0;i<5;i++){
        it1++;
        it2--;
    }
    theList.sort(it1,it2);
    mergeSort(recs+5,10);
    it=theList.cbegin();
    for(int i=0;rc && i<20;i++){
        if(*it != recs[i]){
            rc=false;
            error="Error 10a: records are not in correct order after calling sort(from,to)\n";
            error += "Your record: ";
            error += (*it).toString();
            error += "correct data: ";
            error += recs[i].toString();                             
        }
        it++;
    }
    it=theList.cend();
    for(int i=19;rc && i>=0;i--){
        if(*(--it) != recs[i]){
            rc=false;
            error="Error 10b: records are not in correct order after calling sort(from,to)\n";
            error += "check your previous pointers\n";
            error += "Your record: ";
            error += (*it).toString();
            error += "correct data: ";
            error += recs[i].toString();                             
        }
    }
    it1=theList.begin();
    it2=it1;
    it2++;
    theList.sort(it1,it2);
    it=theList.cbegin();
    for(int i=0;rc && i<20;i++){
        if(*it != recs[i]){
            rc=false;
            error="Error 10c: records are not in correct order after calling sort on 1 node partitions\n";
            error += "Your record: ";
            error += (*it).toString();
            error += "correct data: ";
            error += recs[i].toString();                             
        }
        it++;
    }
    it=theList.cend();
    for(int i=19;rc && i>=0;i--){
        if(*(--it) != recs[i]){
            rc=false;
            error="Error 10d: records are not in correct order after calling sort on 1 node partitions\n";
            error += "check your previous pointers\n";
            error += "Your record: ";
            error += (*it).toString();
            error += "correct data: ";
            error += recs[i].toString();                             
        }
    }
    it1=theList.begin();
    it2=setIterator(theList,12);
    mergeSort(recs,12);
    theList.sort(it1,it2);
    it=theList.cbegin();
    for(int i=0;rc && i<20;i++){
        if(*it != recs[i]){
            rc=false;
            error="Error 10e: records are not in correct order after calling sort from first 12 nodes partitions\n";
            error += "Your record: ";
            error += (*it).toString();
            error += "correct data: ";
            error += recs[i].toString();                             
        }
        it++;
    }
    it=theList.cend();
    for(int i=19;rc && i>=0;i--){
        if(*(--it) != recs[i]){
            rc=false;
            error="Error 10f: records are not in correct order after calling sort from first 12 nodes partitions\n";
            error += "check your previous pointers\n";
            error += "Your record: ";
            error += (*it).toString();
            error += "correct data: ";
            error += recs[i].toString();                             
        }
    }
    it1=theList.end();
    it2=setIterator(theList,12);
    mergeSort(recs+12,8);
    theList.sort(it2,it1);
    it=theList.cbegin();
    for(int i=0;rc && i<20;i++){
        if(*it != recs[i]){
            rc=false;
            error="Error 10g: records are not in correct order after calling sort on last 8 nodes in list\n";
            error += "Your record: ";
            error += (*it).toString();
            error += "correct data: ";
            error += recs[i].toString();                             
        }
        it++;
    }
    it=theList.cend();
    for(int i=19;rc && i>=0;i--){
        if(*(--it) != recs[i]){
            rc=false;
            error="Error 10h: records are not in correct order after calling sort on last 8 nodes in list\n";
            error += "check your previous pointers\n";
            error += "Your record: ";
            error += (*it).toString();
            error += "correct data: ";
            error += recs[i].toString();                             
        }
    }
    return rc;

}



/*Test 11: Test copy constructor Operator*/
bool test11(std::string& error){
    Record recs[20]={
        {"the",19},
        {"quick",17},
        {"brown ",4},
        {"fox",9},
        {"jumped",10},
        {"over",16},
        {"lazy",12},
        {"dog",8},
        {"Calvin",1},
        {"and",3},
        {"Hobbes",2},
        {"night",15},
        {"watch",20},
        {"captain",5},
        {"carrot",6},
        {"lilac",13},
        {"lavender",11},
        {"lily",14},
        {"coffee",7},
        {"tea",18}
    };

    DList<Record> theList;
    DList<Record>::iterator origIt;
    DList<Record>::iterator copyIt;
    bool rc=true;

    for(int i=0;rc && i<20;i++){
        theList.insert(theList.end(),recs[i]);
    }

    DList<Record> copy=theList;

    if(copy.size() != theList.size()){
        rc=false;
        error = "Error 11a: list created with copy constructor does not properly copy the size";
    }
    if(rc && copy.empty()){
        rc=false;
        error = "Error 11b: list created with copy constructor is empty()";
    }
    origIt=theList.begin();
    copyIt=copy.begin();
    while(rc && origIt!=theList.end()){
        if(copyIt == copy.end()){
            rc=false;
            error = "Error 11c: duplicate list has less nodes than original";            
        }
        if(rc && *origIt != *copyIt){
            rc=false;
            error = "Error 11d: duplicate list does not have same data as original";            
        }
        if(rc && &(*origIt) == &(*copyIt)){
            rc=false;
            error = "Error 11e: deep copy does not appear to have been made";            
        }
        origIt++;
        copyIt++;
    }
    if(rc && copyIt!=copy.end()){
        rc=false;
        error = "Error 11f: duplicate list appears to have more nodes than original";            
    }

    return rc;
}
/*Test 12: Test copy assignment operator*/
bool test12(std::string& error){
    Record recs[20]={
        {"the",19},
        {"quick",17},
        {"brown ",4},
        {"fox",9},
        {"jumped",10},
        {"over",16},
        {"lazy",12},
        {"dog",8},
        {"Calvin",1},
        {"and",3},
        {"Hobbes",2},
        {"night",15},
        {"watch",20},
        {"captain",5},
        {"carrot",6},
        {"lilac",13},
        {"lavender",11},
        {"lily",14},
        {"coffee",7},
        {"tea",18}
    };

    DList<Record> theList;
    DList<Record>::iterator origIt;
    DList<Record>::iterator copyIt;
    DList<Record> copy1;
    DList<Record> copy2;
    bool rc=true;
    int i;
    for(i=0;i<20;i++){
        theList.insert(theList.end(),recs[i]);
        copy1.insert(copy1.end(),recs[i]);
    }
    for(i=5;i<15;i++){
        copy2.insert(copy2.end(),recs[i]);
    }

    copy1=copy2;

    if(copy1.size() != copy2.size()){
        rc=false;
        error = "Error 12a: list assigned to by copy assignment does not properly copy the size";
    }
    if(rc && copy1.empty()){
        rc=false;
        error = "Error 12b: list assigned to by copy assignment is empty()";
    }
    origIt=copy2.begin();
    copyIt=copy1.begin();
    i=5;
    while(rc && origIt!=copy2.end()){
        if(copyIt == copy1.end()){
            rc=false;
            error = "Error 12c: duplicate list has less nodes than original";            
        }
        if(rc && *origIt != *copyIt){
            rc=false;
            error = "Error 12d: duplicate list does not have same data as original";            
        }
        if(rc && *copyIt != recs[i++]){
            rc=false;
            error = "Error 12e: duplicate list does not match record added to list";  
        }
        if(rc && &(*origIt) == &(*copyIt)){
            rc=false;
            error = "Error 12f: deep copy does not appear to have been made";  
        }
        origIt++;
        copyIt++;
    }
    if(rc && copyIt!=copy1.end()){
        rc=false;
        error = "Error 12g: duplicate list appears to have more nodes than original";            
    }

    copy1 = copy2 = theList;

    if(copy1.size() != copy2.size() || copy1.size() !=theList.size()){
        rc=false;
        error = "Error 12h: list assigned to by copy assignment does not properly copy the size";
    }
    if(rc && (copy1.empty() || copy2.empty())){
        rc=false;
        error = "Error 12i: list assigned to by copy assignment is empty()";
    }
    origIt=theList.begin();
    copyIt=copy1.begin();
    while(rc && origIt!=theList.end()){
        if(copyIt == copy1.end()){
            rc=false;
            error = "Error 12j: duplicate list has less nodes than original";            
        }
        if(rc && *origIt != *copyIt){
            rc=false;
            error = "Error 12k: duplicate list does not have same data as original";            
        }
        if(rc && &(*origIt) == &(*copyIt)){
            rc=false;
            error = "Error 12l: deep copy does not appear to have been made";            
        }
        origIt++;
        copyIt++;
    }
    if(rc && copyIt!=copy1.end()){
        rc=false;
        error = "Error 12m: duplicate list appears to have more nodes than original";            
    }
    origIt=theList.begin();
    copyIt=copy2.begin();
    while(rc && origIt!=theList.end()){
        if(copyIt == copy2.end()){
            rc=false;
            error = "Error 12n: duplicate list has less nodes than original";            
        }
        if(rc && *origIt != *copyIt){
            rc=false;
            error = "Error 12o: duplicate list does not have same data as original";            
        }
        if(rc && &(*origIt) == &(*copyIt)){
            rc=false;
            error = "Error 12p: deep copy does not appear to have been made";            
        }
        origIt++;
        copyIt++;
    }
    if(rc && copyIt!=copy2.end()){
        rc=false;
        error = "Error 12q: duplicate list appears to have more nodes than original";            
    }

    return rc;   
}

/*Test 13: Timing runs on large data sets*/
bool test13(std::string& error){
    int listSize=20000;
    Timer t;
    bool rc=true;
    int* array=new int[listSize];
    for(int i=0;i<listSize;i++){
        array[i]=i+1;
    }

    for(int i=0;i<listSize;i++){
        int pick = rand()%(listSize-i);
        swap(array[pick],array[listSize-i-1]);
    }   

    DList<int> theList;
    DList<int> copy2;
    for(int i=listSize-1;i>=0;i--){
        t.start();
        theList.insert(theList.begin(),array[i]);
        t.stop();
        copy2.insert(copy2.begin(),array[i]);

    }

    std::cout << listSize << " insert(): " << t.currtime() << std::endl;
    DList<int>::const_iterator it;
    it=theList.cbegin();
    for(int i=0;rc && i<listSize;i++){
        if(*it !=array[i]){
            rc=false;
            error = "Error 13a: insertion error on large data set\n";
            error += "Your record: ";
            error += std::to_string(*it);
            error += "correct data ";
            error += std::to_string(array[i]);

        }
        it++;
    }
    t.reset();
    t.start();
    DList<int> copy1 = theList;
    t.stop();
    std::cout << "copy constructor on list with " << listSize << " nodes: " << t.currtime() << std::endl;
    it = theList.cbegin();
    for(int i=0;rc && i<listSize;i++){
        if(*it !=array[i]){
            rc=false;
            error = "Error 13b: copy constructor error on large data set\n";
            error += "Your record: ";
            error += std::to_string(*it);
            error += "correct data ";
            error += std::to_string(array[i]);
        }
        it++;
    }
    t.reset();
    t.start();
    copy2 = theList;
    t.stop();
    std::cout << "assignment operator on list with " << listSize << " nodes: " << t.currtime() << std::endl;
    it = theList.cbegin();
    for(int i=0;rc && i<listSize;i++){
        if(*it !=array[i]){
            rc=false;
            error = "Error 13c: assignment operator error on large data set\n";
            error += "Your record: ";
            error += std::to_string(*it);
            error += "correct data ";
            error += std::to_string(array[i]);
        }
        it++;
    }
    t.reset();
    t.start();
    DList<int> copy3=std::move(theList);
    t.stop();
    std::cout << "move constructor on list with " << listSize << " nodes: " << t.currtime() << std::endl;
    it = copy3.cbegin();
    for(int i=0;rc && i<listSize;i++){
        if(*it !=array[i]){
            rc=false;
            error = "Error 13d: move constructor error on large data set\n";
            error += "Your record: ";
            error += std::to_string(*it);
            error += "correct data ";
            error += std::to_string(array[i]);
        }
        it++;
    }
    t.reset();
    t.start();
    copy2=std::move(copy3);
    copy1=std::move(copy2);
    t.stop();
    std::cout << "move assignment on list with " << listSize << " nodes: " << t.currtime() << std::endl;
    it = copy1.cbegin();
    for(int i=0;rc && i<listSize;i++){
        if(*it !=array[i]){
            rc=false;
            error = "Error 13e: move assignment error on large data set\n";
            error += "Your record: ";
            error += std::to_string(*it);
            error += "correct data ";
            error += std::to_string(array[i]);
        }
        it++;
    }


    delete [] array;
    return rc;
}

void swap(int& a,  int& b){
    int tmp=a;
    a=b;
    b=tmp;
}
std::ostream& operator<<(std::ostream& os, const Record rec){
    os << rec.word_;
    return os;
}
bool operator==(const Record& a,const Record& b){
    bool rc=false;
    if(a.word_==b.word_ && a.count_==b.count_){
        rc=true;
    }
    return rc;
}
bool operator!=(const Record& a,const Record& b){
    return !(a==b);
}
bool operator <(const Record& a, const Record& b){
    bool rc=false;
    if(a.word_ < b.word_){
        rc=true;
    }
    return rc;
}



template <typename T>
void removeItem(T arr[],int idx,int sz){
    for(int i=idx;i<sz-1;i++){
        arr[i]=arr[i+1];
    }
}



template <typename T>
void duplicateArray(T dest[], const T src[],int sz){
    for(int i=0;i<sz;i++){
        dest[i]=src[i];
    }
}

template <typename T>
int search(const T& data, T arr[],int sz){
    int rc=-1;
    for(int i=0;rc==-1 && i<sz;i++){
        if(arr[i]==data){
            rc=i;
        }
    }
    return rc;
}


//returns iterator to the idx'th node in the list
template <typename T>
typename DList<T>::iterator setIterator(DList<T>& list, int idx){
    typename DList<T>::iterator it=list.begin();
    for(int i=0;i<idx;i++){
        it++;
    }
    return it;
}

template <typename T>
void mergeSort(T arr[],T tmp[],int start,int end){
  //if the array is more than one element big
    if(start<end){
        int mid=(start+end)/2;
        mergeSort(arr,tmp,start,mid);
        mergeSort(arr,tmp,mid+1,end);
        mergeArray(arr,tmp,start,mid+1,end);
    }
}
/*function merges the two halfs of a sorted array together.
  The arrays are defined from arr[startA]to arr[startB-1] and arr[startB]
to arr[endB]*/

template <typename T>
void mergeArray(T arr[],T tmp[],int startA,int startB,int endB){
    int aptr=startA;
    int bptr=startB;
    int idx=startA;
    while(aptr < startB && bptr < endB+1){
        if(arr[aptr] < arr[bptr]){
            tmp[idx++]=arr[aptr];
            aptr++;
        }
        else{
            tmp[idx++]=arr[bptr];
            bptr++;
        }
    }
//merge function only does one of the two following loops
    while(aptr<startB){
        tmp[idx]=arr[aptr];
        idx++;
        aptr++;    
    }
    while(bptr < endB+1){
        tmp[idx++]=arr[bptr];
        bptr++;
    }

//copy back into arr
    for(int i=startA;i<=endB;i++){
        arr[i]=tmp[i];
    }
}

/*this is the wrapper function that "main" uses.  The world see's this and
  use this. The actual work is done by the other MergeSort() function*/
template <typename T>
void mergeSort(T arr[],int size){
    T* tmp=new T[size];
    mergeSort(arr,tmp,0,size-1);
    delete [] tmp;
}

