#include<bits/stdc++.h>
//#include <windows.h>
using namespace std;

// Fahmid - 1705087_Two

void printSet(char *setA,int sizeA)
{
     cout<<" \nSet elements are =\n "<<endl;

     for(int i = 0;i < sizeA; i++)
     {
        cout<<"Element in position  "<<i+1<<" is "<<setA[i]<<endl;
     }

     cout<<endl;

}

void printPowerSet(char *setA, int set_sizeA)
{

    cout<<" \nPower Set elements are =\n "<<endl;

    unsigned long long  int pow_set_size = 1;

    for(int i=0;i<set_sizeA;i++)
    {
        pow_set_size*=2;
    }

   // cout<<"size of power set ="<<pow_set_size<<endl;

    for(unsigned long long int setElement = 0; setElement < pow_set_size; setElement++)
    {
    for(int elementVarriaty = 0; elementVarriaty <set_sizeA ;elementVarriaty++)
    {

        if(setElement & ((unsigned long long int)1 << elementVarriaty))
            cout << setA[elementVarriaty];
    }
    cout <<" ";
    }
    cout << endl;
}

int main()
{
    int n,r;
    cout<<"Enter the SET size which to genarate = ";
    cin>> n;

    char setA[n];

    for(int i=0;i<n;i++)
    {
        switch (rand() %3)
     {
       case 0: setA[i]=65 + rand() % (( 90+ 1 ) - 65);
               break;
       case 1: setA[i]=48 + rand() % ((57+ 1 ) - 48);
                break;
       case 2: setA[i]=97 + rand() % (( 122+ 1 ) - 97);

     }

    }

     printSet(setA,n);

     clock_t startTime, endTime;

     startTime = clock();
     printPowerSet(setA,n);
     endTime = clock();

     cout<<"\nPower Set Algo needed time "<<fixed << ((double) (endTime - startTime)) / CLOCKS_PER_SEC<< setprecision(9)<<endl;

     return 0;
}
