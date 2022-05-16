/****************************************************************/
/*                                                              */
/*   lab 2 tester file                                          */
/*                                                              */
/*   To compile: g++ lab2.cpp lab2tester.cpp -std=c++0x         */
/*                                                              */
/*                                                              */
/****************************************************************/

#include <iostream>
using namespace std;

unsigned long long factorial (unsigned int n);
unsigned long long power (unsigned int base, unsigned int n);
unsigned long long fibonacci (unsigned int n);

int main(void){

	unsigned long long correctFactorial[20]= {1,1,2,6,24,120,720,5040,40320,362880,3628800,39916800,479001600,
												6227020800, 87178291200, 1307674368000, 20922789888000, 355687428096000, 
												6402373705728000, 121645100408832000
											};
	unsigned long long  correctPower[40]= {1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,
											1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864, 134217728, 268435456, 
											536870912, 1073741824, 2147483648, 4294967296, 8589934592, 17179869184, 34359738368, 
											68719476736, 137438953472, 274877906944, 549755813888 
										  };
	unsigned long long correctFibonacci[40]={0,1,1,2,3,5,8,13,21,34,55,89,144,233,377,610,987,1597,2584,4181,6765,10946,17711,28657,
											46368,75025,121393,196418,317811,514229,832040,1346269,2178309,3524578,5702887,9227465,
											14930352, 24157817, 39088169, 63245986
										    };
	bool hasBug=false;
	for(unsigned int i=0;i<20;i++){
		unsigned long long rc=factorial(i);
		if(rc !=correctFactorial[i]){
			cout << "Error: factorial (" << i << ") = " << correctFactorial[i] << endl;
			cout << "Your function returned: " << rc << endl;
			hasBug=true;
		}
	}
	for(unsigned int i=0;i<40;i++){
		unsigned long long rc = power(2,i);
		if(rc !=correctPower[i]){
			cout << "Error: power(2, " << i << ") = " << correctPower[i] << endl;
			cout << "Your function returned: " << rc << endl;

			hasBug=true;
		}
	}
	for(unsigned int i=0;i<40;i++){
		unsigned long long rc = fibonacci(i);
		if(rc !=correctFibonacci[i]){
			cout << "Error: fibonacci (" << i << ") = " << correctFibonacci[i] << endl;
			cout << "Your function returned: " << rc << endl;
			hasBug=true;
		}
	}
	if(hasBug){
		cout << "Your code has a bug.  please fix." << endl;
		return 1;
	}
	else{
		cout << "Congrats! your code is now working" << endl;
		return 0;
	}
}
