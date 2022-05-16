/**************************************************/
/*                                                */
/*  Lab 1 Starter file                            */
/*                                                */
/*  Name: Kian Dadkhah Shokrollahi                */
/*  Student number: 119369205                     */
/*                                                */
/**************************************************/

/* remember to code these in an iterative only manner*/

unsigned long long factorial (unsigned int n){
  unsigned long long rc = 1;
  for (unsigned int i = 2; i <= n; i++) {
    rc *= i;
  }
  return rc;
}

unsigned long long power (unsigned int base, unsigned int n){
  unsigned long long rc = 1;
  for (unsigned i = 0; i < n; i++) {
    rc *= base;
  }
  return rc;
}

unsigned long long fibonacci (unsigned int n){
  unsigned long long t1 = 0, t2 = 1;
  unsigned long long rc = 1;
  if (n == 0) {
    return n;
  }
  for (unsigned int i = 1; i < n; i++) {
    rc = t1 + t2; // new number = sum of last two terms
    t1 = t2; // second term is assigned to current first term to make it the next first term
    t2 = rc; // new number is assigned to current second term to make it the next second term 
  }
  return rc;
}
