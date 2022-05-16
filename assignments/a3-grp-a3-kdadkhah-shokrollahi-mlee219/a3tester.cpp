/**************************************************************************/
/*                                                                        */
/*   A3 tester file                                                       */
/*                                                                        */
/*   To compile: g++ a3tester.cpp timer.cpp -std=c++0x                    */
/*                                                                        */
/**************************************************************************/

#include "threadedtree.h"
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

const int numTests=9;
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
bool operator <(const Record& a, const Record& b);



template <typename T>
void mergeSort(T arr[],int size);


template <typename T>
void printLists(const ThreadedTree<T>& tree,const T array[],int sz);


int main(void){
    TestPtr runTest[numTests]={test1, test2, test3, test4 , test5, 
                               test6 , test7, test8, test9 };
    std::string testSummary[numTests]={
                            "empty trees, size(), empty(), c/begin(), c/end()",
                            "insert(), size(), empty(), c/begin(), c/end()",
                            "increment operators pre and postfix",
                            "decrement operators pre and postfix",
                            "return values from increment operators",
                            "return values from decrement operators",
                            "iterator find() function return",
                            "const_iterator find() const function return",
                            "large data check"
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
        std::cout << "Congratulations! You have passed testing for A3" << std::endl;
        return 0;
    }
    else{
        std::cout << "Looks like you still have some work left to do" << std::endl;
        return 1;
    }
}
/* test1: Create an empty tree, check size(), empty(), begin(), end() 
   cbegin() and cend()
   functions.  test returns true if passed, false otherwise
*/
bool test1(std::string& error){
   ThreadedTree<Record> theTree;
    int result;
    bool rc=true;
    result=theTree.size();
    if(result != 0){
        rc=false;
        error = "Error 1a: size() function returned ";
        error += std::to_string(result);
        error += " on an empty tree, should return 0." ;        
    }
    if(rc && theTree.empty()==false){
        rc=false;
        error = "Error 1b: empty() function returned false on empty tree, should return true";
    }
    if(rc && theTree.begin() != theTree.end()){
        error = "Error 1c: tree is empty, begin() and end() should return iterator to same node";
        rc=false;
    }
    if(rc && theTree.cbegin() != theTree.cend()){
        error = "Error 1d: tree is cempty, cbegin() and cend() should return iterator to same node";
        rc=false;
    }
    return rc;
}

/*test2: test insertion and size(), empty(), begin() and end() are consistent*/
bool test2(std::string& error){
    Record recs[20]={
        {"the",1},
        {"quick",2},
        {"brown ",3},
        {"fox",4},
        {"jumped",5},
        {"over",6},
        {"lazy",7},
        {"dog",8},
        {"Calvin",9},
        {"and",10},
        {"Hobbes",11},
        {"night",12},
        {"watch",13},
        {"captain",14},
        {"carrot",15},
        {"lilac",16},
        {"lavender",17},
        {"lily",18},
        {"coffee",19},
        {"tea",20}
    };
    ThreadedTree<Record> theTree;
    int treeSize;
    bool rc=true;
    for(int i=0;i<20;i++){
        theTree.insert(recs[i]);
    }
    treeSize = theTree.size();
    if(treeSize != 20){
        rc=false;
        error = "Error 2a: size() function returned ";
        error += std::to_string(treeSize);
        error += ".  size() should return 20" ;        
    }
    if(rc && theTree.empty() == true){
        rc=false;
        error = "Error 2b: empty() function returned true on a non-empty tree";
    }
    if(rc && theTree.begin() == theTree.end()){
        error = "Error 2c: tree is not empty, begin() and end() should return iterator to different nodes";
        rc=false;        
    }
    if(rc && theTree.cbegin() == theTree.cend()){
        error = "Error 2d: tree is not empty, cbegin() and cend() should return iterator to different nodes";
        rc=false;        
    }
    return rc;
}

/*test3: test ++ operators ensuring tree items are in correct order*/
bool test3(std::string& error){
    Record recs[20]={
        {"the",1},
        {"quick",2},
        {"brown ",3},
        {"fox",4},
        {"jumped",5},
        {"over",6},
        {"lazy",7},
        {"dog",8},
        {"Calvin",9},
        {"and",10},
        {"Hobbes",11},
        {"night",12},
        {"watch",13},
        {"captain",14},
        {"carrot",15},
        {"lilac",16},
        {"lavender",17},
        {"lily",18},
        {"coffee",19},
        {"tea",20}
    };

    ThreadedTree<Record> theTree;
    bool rc=true;
    int treeSize;
    for(int i=0;rc && i<20;i++){
        theTree.insert(recs[i]);
    }
    mergeSort(recs,20);
    ThreadedTree<Record>::iterator it= theTree.begin();
    for(int i=0;rc && i<20;i++){
        if(*it != recs[i]){
            error = "Error 3a: Incorrect data at node.\n  Data at node # ";
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

    ThreadedTree<Record>::const_iterator it2= theTree.cbegin();
    for(int i=0;rc && i<20;i++){
        if(*it2 != recs[i]){
            error = "Error 3b: Incorrect data at node.\n  Data at node # ";
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

    it= theTree.begin();
    for(int i=0;rc && i<20;i++){
        if(*it != recs[i]){
            error = "Error 3c: Incorrect data at node.\n  Data at node # ";
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

    it2= theTree.cbegin();
    for(int i=0;rc && i<20;i++){
        if(*it2 != recs[i]){
            error = "Error 3d: Incorrect data at node.\n  Data at node # ";
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
        {"the",1},
        {"quick",2},
        {"brown ",3},
        {"fox",4},
        {"jumped",5},
        {"over",6},
        {"lazy",7},
        {"dog",8},
        {"Calvin",9},
        {"and",10},
        {"Hobbes",11},
        {"night",12},
        {"watch",13},
        {"captain",14},
        {"carrot",15},
        {"lilac",16},
        {"lavender",17},
        {"lily",18},
        {"coffee",19},
        {"tea",20}
    };
    ThreadedTree<Record> theTree;

    bool rc=true;
    int treeSize;
    for(int i=0;rc && i<20;i++){
        theTree.insert(recs[i]);
    }
    mergeSort(recs,20);
    ThreadedTree<Record>::iterator it = theTree.end();
    for(int i=0;rc && i<20;i++){
        it--;
        if(*it != recs[19-i]){
            error = "Error 4a: Incorrect data at node.\n  Data at node # ";
            error += std::to_string(i+1);
            error += "(numbered from 1):";
            error += (*it).toString();
            error += "The correct data is";
            error += recs[i].toString();
            error += "\nbug probably in either insert() or iterator::operator--(int)";
            rc=false;
        }
    }

    ThreadedTree<Record>::const_iterator it2 = theTree.cend();
    for(int i=0;rc && i<20;i++){
        it2--;
        if(*it2 != recs[19-i]){
            error = "Error 4b: Incorrect data at node.\n  Data at node # ";
            error += std::to_string(i+1);
            error += "(numbered from 1):";
            error += (*it2).toString();
            error += "The correct data is";
            error += recs[i].toString();
            error += "\nbug probably in either insert() or const_iterator::operator--(int)";
            rc=false;
        }

    }

    it = theTree.end();
    for(int i=0;rc && i<20;i++){
        --it;
        if(*it != recs[19-i]){
            error = "Error 4c: Incorrect data at node.\n  Data at node # ";
            error += std::to_string(i+1);
            error += "(numbered from 1):";
            error += (*it).toString();
            error += "The correct data is";
            error += recs[i].toString();
            error += "\nbug probably in either insert() or iterator::operator--()";
            rc=false;
        }

    }

    it2 = theTree.cend();
    for(int i=0;rc && i<20;i++){
        --it2;
        if(*it2 != recs[19-i]){
            error = "Error 4d: Incorrect data at node.\n  Data at node # ";
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
        {"the",1},
        {"quick",2},
        {"brown ",3},
        {"fox",4},
        {"jumped",5},
        {"over",6},
        {"lazy",7},
        {"dog",8},
        {"Calvin",9},
        {"and",10},
        {"Hobbes",11},
        {"night",12},
        {"watch",13},
        {"captain",14},
        {"carrot",15},
        {"lilac",16},
        {"lavender",17},
        {"lily",18},
        {"coffee",19},
        {"tea",20}
    };

    ThreadedTree<Record> theTree;
    bool rc=true;
    int treeSize;
    for(int i=19;rc && i>=0;i--){
        theTree.insert(recs[i]);
    }
    Record rec;
    mergeSort(recs,20);
    ThreadedTree<Record>::iterator it= theTree.begin();
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
    ThreadedTree<Record>::const_iterator it2= theTree.cbegin();
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



    it = theTree.begin();

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
    it2= theTree.cbegin();
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
        {"the",1},
        {"quick",2},
        {"brown ",3},
        {"fox",4},
        {"jumped",5},
        {"over",6},
        {"lazy",7},
        {"dog",8},
        {"Calvin",9},
        {"and",10},
        {"Hobbes",11},
        {"night",12},
        {"watch",13},
        {"captain",14},
        {"carrot",15},
        {"lilac",16},
        {"lavender",17},
        {"lily",18},
        {"coffee",19},
        {"tea",20}
    };

    ThreadedTree<Record> theTree;
    bool rc=true;
    int treeSize;
    for(int i=19;rc && i>=0;i--){
        theTree.insert(recs[i]);
    }
    ThreadedTree<Record>::iterator it= theTree.end();
    it--;
    mergeSort(recs,20);
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
    ThreadedTree<Record>::const_iterator it2= theTree.cend();
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


    it = theTree.end();

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
    it2= theTree.cend();
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

/*Test 7: Test iterator find()*/
bool test7(std::string& error){
    Record recs[20]={
        {"the",1},
        {"quick",2},
        {"brown ",3},
        {"fox",4},
        {"jumped",5},
        {"over",6},
        {"lazy",7},
        {"dog",8},
        {"Calvin",9},
        {"and",10},
        {"Hobbes",11},
        {"night",12},
        {"watch",13},
        {"captain",14},
        {"carrot",15},
        {"lilac",16},
        {"lavender",17},
        {"lily",18},
        {"coffee",19},
        {"tea",20}
    };

    ThreadedTree<Record> theTree;
    ThreadedTree<Record>::iterator result;
    ThreadedTree<Record>::iterator it;
    bool rc=true;
    int treeSize;
    for(int i=0;rc && i<15;i++){
        theTree.insert(recs[i]);
    }
    mergeSort(recs,15);
    for(int i=0;rc && i<15;i++){
        result=theTree.find(recs[i]);
        if(result == theTree.end()){
            rc=false;
            error = "Error 7a: item that should have been in the linked tree was not found\n";
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
        result=theTree.find(recs[i]);
        if(result != theTree.end()){
            rc=false;
            error = "Error 7c: searching for an item that should not be in the tree resulted in something that isn't cend() \n";
            error += "item being searched for: ";
            error += recs[i].toString();
        }        
    }
    return rc;
}

/*Test 8: Test const_iterator find() const*/
bool test8(std::string& error){
    Record recs[20]={
        {"the",1},
        {"quick",2},
        {"brown ",3},
        {"fox",4},
        {"jumped",5},
        {"over",6},
        {"lazy",7},
        {"dog",8},
        {"Calvin",9},
        {"and",10},
        {"Hobbes",11},
        {"night",12},
        {"watch",13},
        {"captain",14},
        {"carrot",15},
        {"lilac",16},
        {"lavender",17},
        {"lily",18},
        {"coffee",19},
        {"tea",20}
    };

    ThreadedTree<Record> theTree;
    ThreadedTree<Record>::const_iterator result;
    ThreadedTree<Record>::const_iterator it;
    bool rc=true;
    int treeSize;
    for(int i=0;rc && i<15;i++){
        theTree.insert(recs[i]);
    }
    mergeSort(recs,15);
    for(int i=0;rc && i<15;i++){
        result=theTree.find(recs[i]);
        if(result == theTree.end()){
            rc=false;
            error = "Error 8a: item that should have been in the linked tree was not found\n";
            error += "item being searched for: ";
            error += recs[i].toString();
        }
        else if(*result != recs[i]){
            rc=false;
            error = "Error 8b: item found was not the one being searched for\n";
            error += "item found: ";
            error += (*result).toString();
            error += "item being searched for: ";
            error += recs[i].toString();
        }
    }
    for(int i=15;rc && i<20;i++){
        result=theTree.find(recs[i]);
        if(result != theTree.end()){
            rc=false;
            error = "Error 8c: searching for an item that should not be in the tree resulted in something that isn't cend() \n";
            error += "item being searched for: ";
            error += recs[i].toString();
        }        
    }
    return rc;
}

/*Test 9: Large array testing*/
bool test9(std::string& error){
    Timer T;
    bool rc=true;
    int arraySize=500000;
    int* recs=new int[arraySize];
    ThreadedTree<int> theTree; 
    for(int i=0;i<arraySize;i++){
        recs[i]=i+1;
    }
    for(int i=arraySize-1;i>0;i--){
        int choice=rand()%(i+1);
        std::swap(recs[i],recs[choice]);
    }
    T.start();
    for(int i=0;i<arraySize;i++){
        theTree.insert(recs[i]);
    }
    T.stop();
    mergeSort(recs,arraySize);
    ThreadedTree<int>::iterator it;
    ThreadedTree<int>::const_iterator it2;

    T.start();
    it=theTree.begin();
    for(int i=0;rc && i<arraySize;i++){
        if(*it != recs[i]){
            error = "Error 9a: Incorrect data at node.\nData at node # ";
            error += std::to_string(i+1);
            error += "(numbered from 1): ";
            error += std::to_string(*it);
            error += "The correct data is: ";
            error += std::to_string(recs[i]);
            error += "\nbug probably in either insert() or iterator::operator++(int)";
            rc=false;
        }
        *it+=1;
        it++;
    }
    it2=theTree.cbegin();
    for(int i=0;rc && i<arraySize;i++){
        if(*it2 != recs[i]+1){
            error = "Error 9b: Incorrect data at node.\nData at node # ";
            error += std::to_string(i+1);
            error += "(numbered from 1): ";
            error += std::to_string(*it);
            error += "The correct data is: ";
            error += std::to_string(recs[i]+1);
            error += "\nbug probably in either insert() or iterator::operator++()";
            rc=false;
        }
        ++it2;
    }

    it=theTree.end();
    for(int i=arraySize-1;rc && i>0;i--){
        *(--it)-=1;
        if(*it != recs[i]){
            error = "Error 9a: Incorrect data at node.\n  Data at node # ";
            error += std::to_string(i+1);
            error += "(numbered from 1):";
            error += std::to_string(*it);
            error += "The correct data is";
            error += std::to_string(recs[i]);
            error += "\nbug probably in either insert() or iterator::operator++(int)";
            rc=false;
        }
    }

    it2=theTree.cend();
    for(int i=arraySize-1;rc && i>0;i--){
        it2--;
        if(*it2 != recs[i]){
            error = "Error 9a: Incorrect data at node.\n  Data at node # ";
            error += std::to_string(i+1);
            error += "(numbered from 1):";
            error += std::to_string(*it);
            error += "The correct data is";
            error += std::to_string(recs[i]);
            error += "\nbug probably in either insert() or iterator::operator++(int)";
            rc=false;
        }
    }
    T.stop();

    std::cout << "Test 9 took " << T.currtime() << " seconds" << std::endl;
    delete [] recs;
    return rc;
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






/*this function isn't called by main but if you want to get a closer look at the
difference between your tree and the data, just make a call to this function*/
template <typename T>
void printTrees(const ThreadedTree<T>& tree,const T array[],int sz){
    std::cout << "your size() returned: " << tree.size() << std::endl;
    std::cout << "correct size returned: " << sz << std::endl;
    auto it=tree.begin();
    for(int i=0;i<sz;i++,(it==tree.end())?it:it++){
        std::cout << "correct: "  << array[i];
        if(it!=tree.end()){
            std::cout << " your tree: " << *it << std::endl;
        }
        else{
            std::cout << "your tree: " << "<no data>" <<  std::endl;
        }
    }

    std::cout << "************************************************" << std::endl;
    tree.print();
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

/*this is the wrapper function that "main" uses.  The world see's this and
  use this. The actual work is done by the other MergeSort() function*/
template <typename T>
void mergeSort(T arr[],int size){
    T* tmp=new T[size];
    mergeSort(arr,tmp,0,size-1);
    delete [] tmp;
}