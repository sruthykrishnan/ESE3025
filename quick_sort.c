//============================================================================
// Name        : quick_sort.c
// Author      : Sruthy Krishnan
// Version     :
// Copyright   : Your copyright notice
// Description : Quick Sort Algorithm 
//============================================================================

#include <stdlib.h>
#include <stdio.h>
int compar(const void *pa, const void *pb)
{
int a = *(const int *)pa;
int b = *(const int *)pb;
int ret = 0;
if(a<b)
ret = -1;
else if(a>b)
ret = 1;
return ret;
}
int main()
{
int myarr[] = {8, 32, -76, 4025, 0, 3, -329, 5412, 6};
size_t L = sizeof(myarr)/sizeof(int);
printf(" Numbers before sorting\n");
int i;
for(i=0; i<L; ++i)
printf(" %d", myarr[i]);
printf("\n");

qsort((void *)myarr, L, sizeof(int), compar);
printf(" Numbers after sorting\n");
for(i=0; i<L; ++i)
printf(" %d", myarr[i]);
return 0;
}
