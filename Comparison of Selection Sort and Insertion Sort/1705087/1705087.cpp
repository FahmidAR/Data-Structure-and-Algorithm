
#include<bits/stdc++.h>
//#include <windows.h>
using namespace std;

// Fahmid - 1705087_Two

void printArray(int *arr,int sizeA)
{
     for(int i = 0;i < sizeA; i++)
     {
        cout<<"Element in index "<<i<<" is "<<arr[i]<<endl;
     }
}


void insertionSort(int arr[], int SizeA)
{

    // take all and place in the perfect position

    int i,j,temp ;

    for (i = 1; i < SizeA; i++)
    {
        temp = arr[i];

        j=i-1;
		while((temp<arr[j]) && (j>=0))
		{
			arr[j+1]=arr[j];
			j=j-1;
		}
        arr[j+1]=temp;
    }
}

void selectionSort(int arr[], int SizeA)
{

    // Always swap with min

    int i, j, min_idx , temp;

    for (i = 0; i < SizeA-1; i++)
    {
        min_idx = i;

        for (j = i+1; j < SizeA; j++)
        {
            if (arr[j] < arr[min_idx])
            min_idx = j;
        }

        temp=arr[i];
        arr[i]=arr[min_idx];
        arr[min_idx]=temp;

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



int main()
{
// TEST ARRAY
   //int arr[]={6,1,2,3,4,5,1,7,8,9,10}; //

   int arraySize,arraySize2, key ,maxRange;

   cout<<"Enter the array size = ";
   //arraySize=sizeof(arr)/sizeof(arr[0]);
   cin>> arraySize;

   arraySize2=arraySize;
   int arr[arraySize],arr2[arraySize2];
   int arrBest[arraySize],arr2Best[arraySize2];
   int arrWorst[arraySize],arr2Worst[arraySize2];

   cout<<"Enter the max inteager size (-1 for max range) = ";
   cin>> maxRange;

   if(maxRange==-1) maxRange=999999999999;

   //int *arr=getRandomArray(arraySize,maxRange);
    srand(time(0));

     for(int i = 0;i < arraySize; i++)
     {
        arr[i] = (rand()% maxRange)+1;
        arr2[i]=arr[i];
        arrBest[i]=arr[i];
        arr2Best[i]=arr[i];
        arrWorst[i]=arr[i];
        arr2Worst[i]=arr[i];
     }

     sort(arrBest,arrBest+arraySize);
     sort(arr2Best,arr2Best+arraySize);
     sort(arrWorst, arrWorst+arraySize, greater<int>());
     sort(arr2Worst, arr2Worst+arraySize, greater<int>());


     clock_t startTime, endTime;
     double cpu_time_used;


     cout<<"### Insertation sort ###"<<endl;


     startTime = clock();
     insertionSort(arr,arraySize);
     endTime = clock();

     //printArray(arr,arraySize);
     cpu_time_used = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;
     cout<<"Avg Insertation sort needed time "<<fixed << cpu_time_used<< setprecision(9)<<endl;

     startTime = clock();
     insertionSort(arrBest,arraySize);
     endTime = clock();

     cpu_time_used = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;
     cout<<"Best Insertation sort needed time "<<fixed << cpu_time_used<< setprecision(9)<<endl;

     startTime = clock();
     insertionSort(arrWorst,arraySize);
     endTime = clock();

     cpu_time_used = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;
     cout<<"Wrost Insertation sort needed time "<<fixed << cpu_time_used<< setprecision(9)<<endl;




     cout<<"### Selection sort ###"<<endl;



     startTime = clock();
     selectionSort(arr2,arraySize2);
     endTime = clock();

     //printArray(arr2,arraySize2);
     cpu_time_used = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;
     cout<<"Avg Selection sort needed time "<<fixed << cpu_time_used<< setprecision(9)<<endl;

     startTime = clock();
     selectionSort(arr2Best,arraySize2);
     endTime = clock();

     cpu_time_used = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;
     cout<<"Best Selection sort needed time "<<fixed << cpu_time_used<< setprecision(9)<<endl;

     startTime = clock();
     selectionSort(arr2Worst,arraySize2);
     endTime = clock();

     cpu_time_used = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;
     cout<<"Worst Selection sort needed time "<<fixed << cpu_time_used<< setprecision(9)<<endl;

   return 0;
}

