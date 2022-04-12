#include<bits/stdc++.h>

using namespace std;

//Fahmid-Al-Rifat
//1705087

#define dbg 1

void swapValue(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

class PiorityQueue
{
    public:

    int capacity;
    int sizeHeap;
    int *arrayheap;

    public:

        PiorityQueue ();
        PiorityQueue (int cap);
        ~PiorityQueue ();

        int parent(int i) { return (i-1)/2; }
        int left(int i) { return (2*i + 1); }
        int right(int i) { return (2*i + 2); }
        void maxHeapify( int idx);

        void Insert(int key);
        int FindMax();
        int ExractMax();
        int FindLargerCount(int x,int i);
        void IncreaseKey(int pos,int key) ;
        void DecreaseKey(int pos,int key) ;
        void print( ) ;
};

PiorityQueue::~PiorityQueue()
{
    if(arrayheap) delete [] arrayheap;
}

PiorityQueue::PiorityQueue (int cap)
{
    sizeHeap=0;
    capacity=cap;
    arrayheap= new int[cap] ;
}

PiorityQueue::PiorityQueue ()
{
    sizeHeap=0;
    capacity=1;
    arrayheap= new int[capacity] ;
}

void PiorityQueue::maxHeapify( int idx)
{
    int  leftChild, rightChild,largest;

    largest = idx;
    leftChild = left(idx);
    rightChild = right(idx);

    if (leftChild < sizeHeap && arrayheap[leftChild]>arrayheap[idx])
        largest = leftChild;

    if (rightChild < sizeHeap && arrayheap[rightChild]>arrayheap[largest])
        largest = rightChild;

    if (largest != idx)
    {

        swapValue(&arrayheap[largest], &arrayheap[idx]);

        maxHeapify( largest);
    }
}


void PiorityQueue::Insert(int key)
{
    sizeHeap++;
    int *temp;

    if (sizeHeap>capacity)
	{

		capacity = 1+ capacity ;
		temp = new int[capacity] ;

        for( int i = 0; i < sizeHeap ; i++ )
        {
            temp[i] = arrayheap[i] ;
        }
        delete[] arrayheap ;
        arrayheap = temp ;
	}

	arrayheap[sizeHeap-1]=key;
    int i=sizeHeap-1;

	while(i!=0&&arrayheap[parent(i)]<arrayheap[i])
    {
        swapValue(&arrayheap[parent(i)],&arrayheap[i]);
        i=parent(i);
    }

}



int PiorityQueue::FindMax()
{
    if(sizeHeap)
    {
        return arrayheap[0];
    }
    else
    {
        if(dbg)
        cout<<" No element in heap"<<endl;
        return -1;
    }
}

int PiorityQueue::FindLargerCount(int x,int i)
{
    if(i>=sizeHeap) return 0;
    if(arrayheap[i]>x) return 1+FindLargerCount(x,2*i+1)+FindLargerCount(x,2*i+2);
    else return 0;

}

int PiorityQueue::ExractMax()
{
    if(!sizeHeap)
    {
        if(dbg)
        cout<<" No element in heap"<<endl;
        return -1;
    }

    int minValue=arrayheap[0];
    arrayheap[0]=arrayheap[sizeHeap-1];
    sizeHeap--;
    maxHeapify(0);
    return minValue;
}


void PiorityQueue::IncreaseKey(int pos,int key)
{
    arrayheap[pos]=key;

    while(pos!=0&&arrayheap[parent(pos)]<arrayheap[pos])
    {
        swapValue(&arrayheap[parent(pos)],&arrayheap[pos]);
        pos=parent(pos);
    }
}


void PiorityQueue::DecreaseKey(int pos,int key)
{
    arrayheap[pos]=key;
    maxHeapify(pos);
}


void PiorityQueue::print( )
{
    if(dbg)
    cout<<" Elements are= ";

    for(int i=0 ; i<sizeHeap;i++)
    {
        cout<<arrayheap[i]<<" ";
    }
}






int main(void)
{
    cout<<"### Piority Queue ###"<<endl;
    cout<<"### Indexing  / position started from zero ###"<<endl;
    cout<<"### 1705087  ###"<<endl;
    cout<<endl;

    PiorityQueue pq ;

    while(1)
    {
        printf("1. Insert \n");
        printf("2. FindMax \n");
        printf("3. ExtractMax \n");
        printf("4. Increase Key \n");
        printf("5. Decrease Key \n");
        printf("6. Print Heap \n");
        printf("7. Find larger then given \n");
        printf("8. Exit \n");

        int ch;
        scanf("%d",&ch);

        if(ch==1)
        {
            cout<<"### Give the key =";
            int key;
            cin>>key;
            pq.Insert(key);
            cout<<"### Key added "<<endl;
        }
        else if(ch==2)
        {
            cout<<"### The Max is =";
            cout<<pq.FindMax()<<endl;

        }
        else if(ch==3)
        {
            cout<<"### The Max is =";
            cout<<pq.ExractMax()<<endl;
            cout<<"### Max is Erxtracted "<<endl;
        }
        else if(ch==4)
        {
            int pos , key;

            cout<<"### Give the position=";
            cin>>pos;

            cout<<"### Give the key=";
            cin>>key;

            pq.IncreaseKey(pos,key);

            cout<<"### Wanted position value increased "<<endl;

        }
        else if(ch==5)
        {
               int pos , key;

             cout<<"### Give the position=";
             cin>>pos;

            cout<<"### Give the key=";
            cin>>key;

            pq.DecreaseKey(pos,key);

            cout<<"### Wanted position value decreased "<<endl;
        }
        else if(ch==6)
        {
            pq.print();
            cout<<endl;

        }
        else if(ch==7)
        {
            cout<<"### Give the key =";
            int key;
            cin>>key;
            cout<<"### The number of larger element then key is "<<pq.FindLargerCount(key,0)<<endl;

        }
        else if(ch==8)
        {
            cout<<"### The priority queue is deleted"<<endl;
            break;
        }

    }

}

