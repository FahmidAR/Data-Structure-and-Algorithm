#include<bits/stdc++.h>
using namespace std;


class SET{

    int *data;
    int *parent;
    int *rankH;
    int *univ;
    int maxSize=100;
    int currentSize=0;

    public:

    SET()
    {
        data=(int *)malloc(sizeof(int)*maxSize);
        parent=(int *)malloc(sizeof(int)*maxSize);
        rankH=(int *)malloc(sizeof(int)*maxSize);
        univ=(int *)malloc(sizeof(int)*maxSize);
    }

    SET(int x)
    {
        maxSize=x;
        data=(int *)malloc(sizeof(int)*maxSize);
        parent=(int *)malloc(sizeof(int)*maxSize);
        rankH=(int *)malloc(sizeof(int)*maxSize);
        univ=(int *)malloc(sizeof(int)*maxSize);
    }


    void makeSet(int x);
    int findSet(int x);
    void unionSet(int x,int y);
    void printSet(int x);

};

void SET::makeSet(int x)
{
    univ[currentSize]=x;

    currentSize++;
    if(x>maxSize)
    {
        maxSize=x;
        data=(int *)realloc(data,sizeof(int)*maxSize);
        parent=(int *)realloc(parent,sizeof(int)*maxSize);
        rankH=(int *)realloc(rankH,sizeof(int)*maxSize);

    }

    if(currentSize>maxSize)
    {
        int uniSize=currentSize;
        univ=(int *)realloc(data,sizeof(int)*uniSize);
    }

    parent[x]=x;
    rankH[x]=0;

}

int SET::findSet(int x)
{
    if(x!=parent[x])
        parent[x]=findSet(parent[x]);
    return parent[x];
}

void SET::unionSet(int x,int y)
{
    if(findSet(x)==findSet(y)) return;

    if(rankH[x]>=rankH[y])
    {
        parent[y]=x;
    }
    else
    {
        parent[x]=y;
    }

    if(rankH[x]==rankH[y])
        rankH[y]++;

}

 void SET::printSet(int x)
 {
     int parent=findSet(x);

     cout<<"The subset is = ";

     for(int i=0;i<currentSize;i++)
     {
         if(findSet(univ[i])==parent)

            cout<<univ[i]<<" ";
     }
     cout<<endl;
 }

int main()
{

    int  m=0, input,input2;
    SET s1(12);

    do
            {
                cout<<"\n ******************** "<<endl;
                cout<<" Set Operation  "<<endl;
                cout<<" ******************** "<<endl;

                cout<<" Press 1 for Make set "<<endl;
                cout<<" Press 2 for Find set "<<endl;
                cout<<" Press 3 for Union set "<<endl;
                cout<<" Press 4 for  Print "<<endl;
                cout<<" Press 5 for Quit \n"<<endl;

                cout<<" ### Enter CHOICE  = ";
                cin>>m;

                switch (m)
               {
                   case 1:

                       cout<<" ### Enter input to meke set =";


                       cin>>input;

                       s1.makeSet(input);

                       cout<<" ### Set created SUCCESSFULLY"<<endl;

                        break;

                   case 2:

                       cout<<" ### Enter input to find =";

                       cin>>input;

                       cout<<" ### The parent is ="<<s1.findSet(input)<<endl;

                        break;

                   case 3:
                       cout<<" ### Enter inputs to union =";

                       cin>>input>>input2;

                       s1.unionSet(input,input2);

                       cout<<" ### Unioned SUCCESSFULLY"<<endl;


                        break;

                   case 4:

                       cout<<" ### Enter input to print =";

                        cin>>input;

                        s1.printSet(input);

                        break;


                   case 5:  cout<<" ### Program closed "<<endl;;
                            break;

                   default: printf("Enter choice again");
                            break;
               }
            }
            while(m!=5);
return 0;

}

