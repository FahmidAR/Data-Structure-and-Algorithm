
#include<bits/stdc++.h>
//#include <windows.h>
using namespace std;

// Fahmid - 1705087

void printArray(int *arr,int sizeA)
{
     for(int i = 0;i < sizeA; i++)
     {
        cout<<"Element in index "<<i<<" is "<<arr[i]<<endl;
     }
}


void Merge(int arr[],int l,int m,int r);

void Mergesort(int arr[],int left,int right)
{
    if(left<right)
    {
        int mid ;
        mid = left+(right-left)/2;

        Mergesort(arr,left,mid);

        Mergesort(arr,mid+1,right);

        Merge(arr,left,mid,right);
    }
}

void Merge(int arr[],int l,int m,int r)
{
    int i,j,k,n1,n2;

    n1=m-l+1;
    n2=r-m;


    int L[n1],R[n2];

    for(int i=0;i<n1;i++)
    {
        L[i]=arr[l+i];
    }

    for(int  j=0;j<n2;j++)
    {
        R[j]=arr[m+1+j];
    }

    i=0;j=0; k=l;

    while( i<n1 && j<n2 )
    {
       if(L[i]<R[j])
       {
           arr[k] = L[i];
           i++;
           k++;
       }
       else
       {
           arr[k] = R[j];
           j++;
           k++;
       }
    }

    while(i<n1)
    {
        arr[k]=L[i];
        i++;k++;
    }

    while(j<n2)
    {
        arr[k]=R[j];
        j++;k++;
    }



}


int * getRandomArray(int sizeA,int maxRange) {

    int  *arrR;

    srand(time(0));

     for(int i = 0;i < sizeA; i++)
     {
        arrR[i] = (rand()% maxRange)+1;
     }

   return arrR;
}

int linearSearch(int arr[],int sizeA, int key)
{
    for(int i=0;i<sizeA;i++)
    {
        if(arr[i]==key)
            return i;
    }

    return -1;
}

int binarySearch(int arr[],int sizeA, int key)
{
    int mid;
    int left=0;
    int right=sizeA-1;


   while (left<=right) {

        mid = left + (right - left) / 2;

        //cout<<mid<<" "<<left<<" "<<right<<endl;

        if (arr[mid] == key)
            return mid;

        else if (arr[mid] < key)
            left = mid + 1;

        else
            right = mid - 1;
    }

    return -1;
}


int main()
{
// TEST ARRAY
   //int arr[]={6,1,2,3,4,5,1,7,8,9,10}; //

   int arraySize, key ,maxRange;

   cout<<"Enter the array size = ";
   //arraySize=sizeof(arr)/sizeof(arr[0]);
   cin>> arraySize;


   int arr[arraySize];


   cout<<"Enter the max inteager size (-1 for max range) = ";
   cin>> maxRange;

   if(maxRange==-1) maxRange=999999999999;

   //int *arr=getRandomArray(arraySize,maxRange);
    srand(time(0));

     for(int i = 0;i < arraySize; i++)
     {
        arr[i] = (rand()% maxRange)+1;
     }

    key=(rand()% maxRange)+1;
    cout<<"Generated key is = "<<key<<endl;;


   Mergesort(arr,0,arraySize);
   printArray(arr,arraySize);

     clock_t startTime, endTime;
     double cpu_time_used;

     startTime = clock();
     //long int start = GetTickCount();
     cout<<"BinarySearch index "<<binarySearch(arr,arraySize,key)<<endl;
     endTime = clock();
     //long int end = GetTickCount();
     cpu_time_used = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;
     cout<<"BinarySearch needed time "<<fixed << cpu_time_used<< setprecision(9)<<endl;
     //cout << "BinarySearch needed time "<< double(end - start)<<" milliseconds \n";

     startTime = clock();
     cout<<"LinearSearch index "<<linearSearch(arr,arraySize,key)<<endl;
     endTime = clock();
     cpu_time_used = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;
     cout<<"Linear needed time "<<fixed << cpu_time_used<< setprecision(9)<<endl;

   return 0;
}
