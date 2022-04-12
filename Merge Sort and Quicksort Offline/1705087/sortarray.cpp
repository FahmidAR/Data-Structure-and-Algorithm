#include <bits/stdc++.h>
using namespace std;

void Merge(int arr[],int l,int m,int r);

void Mergesort(int arr[],int left,int right)
{
    if(left<right) // untill array has element
    {
        int mid ;
        mid = left+(right-left)/2;//division

        Mergesort(arr,left,mid);//first half

        Mergesort(arr,mid+1,right);//second half

        Merge(arr,left,mid,right);//merging
    }
}

void Merge(int arr[],int l,int m,int r)
{
    int i,j,k,n1,n2;

    n1=m-l+1;//for left
    n2=r-m;//for right


    int L[n1],R[n2];

    for(int i=0;i<n1;i++)
    {
        L[i]=arr[l+i];//filling left
    }

    for(int  j=0;j<n2;j++)
    {
        R[j]=arr[m+1+j];//filling right
    }

    i=0;j=0; k=l;

    while( i<n1 && j<n2 )
    {
       if(L[i]<R[j]) // compare and insert
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

    while(i<n1) // if extra
    {
        arr[k]=L[i];
        i++;k++;
    }

    while(j<n2)//if extra
    {
        arr[k]=R[j];
        j++;k++;
    }



}


void swap(int* x, int* y) //swap
{
    int temp;
     temp = *x;
    *x = *y;
    *y = temp;
}


int partition (int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1); // last element

    for (int j = low; j <= high - 1; j++)
    {

        if (arr[j] <= pivot) // if less then pivot
        {
            i++; // upper of smaller
            swap(&arr[j], &arr[i]);
        }
    }
    swap(&arr[i + 1], &arr[high]); // placeing pivot at perfect place
    return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high) // untill one element
    {
        int q = partition(arr, low, high);

        quickSort(arr, low, q - 1); // first half of pivot
        quickSort(arr, q + 1, high); // last half of pivot
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

void accending(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n-1; i++)

    for (j = 0; j < n-i-1; j++)
        if (arr[j] > arr[j+1])
            swap(&arr[j], &arr[j+1]);
}

void deccending(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n-1; i++)

    for (j = 0; j < n-i-1; j++)
        if (arr[j] <arr[j+1])
            swap(&arr[j], &arr[j+1]);
}

void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main()
{
    int choice, n,*arrayTest;
    clock_t startTime, endTime;
    double cpu_time_used;

    while(1)
    {
        printf("1. Generate average case\n");
        printf("2. Generate best case\n");
        printf("3. Generate worst case\n");
        printf("4. Apply Merge sort\n");
        printf("5. Apply Quicksort\n");
        printf("6. Print array\n");
        printf("> ");
        scanf("%d", &choice);

        srand(time(0));

        switch(choice)
        {
        case 1:
            printf("### Number of elements: ");
            scanf("%d", &n);

            arrayTest=new int[n];

            for(int i = 0;i < n; i++)
             {
                arrayTest[i] = (rand()% INT_MAX)+1;
             }

            break;

        case 2:
            printf("### Number of elements: ");
            scanf("%d", &n);

            arrayTest=new int[n];

            for(int i = 0;i < n; i++)
             {
                arrayTest[i] = (rand()% INT_MAX)+1;
             }

             accending(arrayTest,n);

            break;

        case 3:
            printf("### Number of elements: ");
            scanf("%d", &n);

           arrayTest=new int[n];

            for(int i = 0;i < n; i++)
             {
                arrayTest[i] = (rand()% INT_MAX)+1;
             }
             deccending(arrayTest,n);

            break;

        case 4:
            printf("### Applying merge sort\n");

            startTime = clock();
            Mergesort(arrayTest,0,n-1);
            endTime = clock();
            cpu_time_used = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;

            cout<<"### Time taken to finish : "<<fixed << cpu_time_used<< setprecision(10)<<endl;

            break;

        case 5:
            printf("### Applying quicksort\n");

            startTime = clock();
            quickSort(arrayTest,0,n-1);
            endTime = clock();
            cpu_time_used = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;

            cout<<"### Time taken to finish : "<<fixed << cpu_time_used<< setprecision(10)<<endl;

            break;

        case 6:
            printf("### Array\n");

            printArray(arrayTest,n);

            break;
        }
    }
}

