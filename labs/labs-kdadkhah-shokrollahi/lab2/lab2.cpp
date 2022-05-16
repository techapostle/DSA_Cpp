/**************************************************/
/*                                                */
/*  Lab 2 Starter file                            */
/*                                                */
/*  Name: Kian Dadhah Shokrollahi                 */
/*  Student number: 119369205                     */
/*                                                */
/**************************************************/

/* remember to code these in a RECURSIVE only manner*/

unsigned long long factorial (unsigned int n){
  if (n <= 1)
    return 1;
  else
    return n * factorial(n - 1);
}
/* Worst case time complexity: 
* T(n) = O(n)
* Linear time
* */


unsigned long long power (unsigned int base, unsigned int n){
  if (n == 0)
    return 1;
  else
    return base * power(base, n-1);
}
/* Worst case time complexity:  
 * T(n) = O(n)
 * Linear time
 * */

unsigned long long fibonacci (unsigned int n){
  if (n <= 1)
    return n;
  else
    return fibonacci(n-1) + fibonacci(n-2);
}
