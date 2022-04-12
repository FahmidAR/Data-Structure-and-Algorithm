#include<bits/stdc++.h>
using namespace std;

void Merge(int arr[],int arr2[],int l,int m,int r);

void Mergesort(int arr[],int arr2[],int left,int right)
{
    if(left<right) // untill array has element
    {
        int mid ;

        mid = left+(right-left)/2;//division

        Mergesort(arr,arr2,left,mid);//first half

        Mergesort(arr,arr2,mid+1,right);//second half

        Merge(arr,arr2,left,mid,right);//merging
    }
}

void Merge(int arr[],int arr2[],int l,int m,int r)
{
    int i,j,k,n1,n2;

    n1=m-l+1;//for left
    n2=r-m;//for right


    int L[n1],R[n2];
    int L2[n1],R2[n2];

    for(int i=0;i<n1;i++)
    {
        L[i]=arr[l+i];//filling left
        L2[i]=arr2[l+i];//filling left
    }

    for(int  j=0;j<n2;j++)
    {
        R[j]=arr[m+1+j];//filling right
        R2[j]=arr2[m+1+j];//filling right
    }

    i=0;j=0; k=l;

    while( i<n1 && j<n2 )
    {
       if(L[i]<R[j]) // compare and insert
       {
           arr[k] = L[i];
           arr2[k] = L2[i];
           i++;
           k++;
       }
       else
       {
           arr[k] = R[j];
           arr2[k] = R2[j];
           j++;
           k++;
       }
    }

    while(i<n1) // if extra
    {
        arr[k]=L[i];
        arr2[k]=L2[i];
        i++;k++;
    }

    while(j<n2)//if extra
    {
        arr[k]=R[j];
        arr2[k]=R2[j];
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

int main()
{
    int sizeArray;


    cout<<" Enter the activity size to generate = ";

    cin>>sizeArray;

    int startTime[sizeArray], finishTime[sizeArray];

    for(int i=0; i<sizeArray; i++)
    {
        int a=420;
        int b=420;

        while(a==b)
        {

        a= (rand()% INT_MAX)+1;
        b= (rand()% INT_MAX)+1;

        }

        if(a>b)
        {
            startTime[i]=b;
            finishTime[i]=a;
        }
        else
        {
            startTime[i]=a;
            finishTime[i]=b;

        }

    }

    cout<<"\n # Before Sort Activities # "<<endl;

    for(int i=0; i<sizeArray; i++)
    {
        cout<<"("<<startTime[i]<<","<<finishTime[i]<<")"<<endl;
    }

     Mergesort(finishTime,startTime,0,sizeArray-1);

    cout<<"\n # After Sort Activities # "<<endl;

    for(int i=0; i<sizeArray; i++)
    {
        cout<<"("<<startTime[i]<<","<<finishTime[i]<<")"<<endl;
    }

    cout<<"\n # Max Activities that can be chosed = # "<<endl;

    int i_take , i_overlap;

    i_take=0;
    cout<<"("<<startTime[i_take]<<","<<finishTime[i_take]<<")"<<endl;

    for(i_overlap=1;i_overlap<sizeArray;i_overlap++)
    {

        if(startTime[i_overlap]>=finishTime[i_take])
        {
            //cout<<"("<<startTime[i_overlap]<<","<<finishTime[i_overlap]<<")"<<endl;
            i_take=i_overlap;
            cout<<"("<<startTime[i_take]<<","<<finishTime[i_take]<<")"<<endl;
        }
    }

    return 0;
}
