//============================================================================
// Name        : stringsort.c
// Author      : Sruthy Krishnan
// Version     :
// Copyright   : Your copyright notice
// Description : String Sort Algorithm
//============================================================================

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct person_struct
{
char lastname[30];
char firstname[30];
char cityname[30];
}person_t;

int compare(const void *pa,const void *pb)
{
char *lna = ((person_t *)pa)->lastname;
char *lnb = ((person_t *)pb)->lastname;
return strcmp(lna,lnb);
}

person_t  dbasepeople[100];


int main()
{
FILE *fp;
fp = fopen("names.txt","r+");
if(fp!=NULL)
printf("File Exist\n");
else
{
printf("File not Exist\n");
return 1;
}
size_t ctr=0;
char str1[30], str2[30], str3[30];
printf("Names before sorting:\n");
while(fscanf(fp,"%s %s %s ",str1,str2,str3)!=EOF)
{
printf("%s %s %s \n",str1,str2,str3);
strcpy(dbasepeople[ctr].lastname,str1);
strcpy(dbasepeople[ctr].firstname,str2);
strcpy(dbasepeople[ctr].cityname,str3);
++ctr;
}

qsort(dbasepeople,ctr,sizeof(person_t),compare);
printf("\nSorted names:\n");
for(int i=0;i<ctr;i++)
{
printf("%s %s %s\n", dbasepeople[i].lastname,dbasepeople[i].firstname,dbasepeople[i].cityname);
}

fclose(fp);
return 0;
}
