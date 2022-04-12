#include<bits/stdc++.h>

#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999

using namespace std;

class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
	if (length == queueMaxSize)
	{
		int * tempData ;
		//allocate new memory space for tempList
		queueMaxSize = 2 * queueMaxSize ;
		tempData = new int[queueMaxSize] ;
		int i, j;
		j = 0;
		for( i = rear; i < length ; i++ )
		{
			tempData[j++] = data[i] ; //copy items from rear
		}
		for( i = 0; i < rear ; i++ )
		{
			tempData[j++] = data[i] ; //copy items before rear
		}
		rear = 0 ;
		front = length ;
		delete[] data ; //free the memory allocated before
		data = tempData ; //make list to point to new memory
	}

	data[front] = item ; //store new item
	front = (front + 1) % queueMaxSize ;
	length++ ;
}


bool Queue::empty()
{
	if(length == 0) return true ;
	else return false ;
}


int Queue::dequeue()
{
	if(length == 0) return NULL_VALUE ;
	int item = data[rear] ;
	rear = (rear + 1) % queueMaxSize ;  // circular queue implementation
	length-- ;
	return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************


//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	int ** matrix ; //adjacency matrix to store the graph
	//define other variables required for bfs such as color, parent, and dist
	//you must use pointers and dynamic allocation
        bool *colorMarked;
    int *level;
    int parentVertex;


public:
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	void addEdge(int u, int v);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getDegree(int u,bool out=true);
    void printAdjVertices(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
	void bfs(int source); //will run bfs in the graph
};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	matrix = 0 ;
	directed = dir ; //set direction of the graph
	//define other variables to be initialized
	colorMarked=new bool [10];
	level=new int[10];
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;

	//allocate space for the matrix
    matrix = new int*[nVertices];
    for(int i=0;i<nVertices;i++)
    {
        matrix[i] = new int[nVertices];
        for(int j=0;j<nVertices;j++)
            matrix[i][j] = 0; //initialize the matrix cells to 0
    }


	if(colorMarked!=0) delete[] colorMarked ;
	colorMarked=new bool [nVertices];

	if(level!=0) delete[] level ;
	level=new int [nVertices];

}

void Graph::addEdge(int u, int v)
{
    //write your code here
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
    matrix[u][v] = 1;
    if(!directed) matrix[v][u] = 1;

}

void Graph::removeEdge(int u, int v)
{
    matrix[u][v] = 0;
    if(!directed) matrix[v][u] = 0;
    //write this function
}

bool Graph::isEdge(int u, int v)
{
    return matrix[u][v];
    //returns true if (u,v) is an edge, otherwise should return false
}

int Graph::getDegree(int u,bool out)
{
    if(!directed)
    {
        int countDeg=0;
        for(int j=0; j<nVertices;j++)
            {
                if(matrix[u][j]==1)
                    countDeg++;
            }
        for(int j=0; j<nVertices;j++)
            {
                if(matrix[j][u]==1)
                    countDeg++;
            }
        return countDeg;

    }
    if(out)
    {
        int countDeg=0;
        for(int j=0; j<nVertices;j++)
            {
                if(matrix[u][j]==1)
                    countDeg++;
            }
        return countDeg;
    }
    else
    {
        int countDeg=0;
        for(int j=0; j<nVertices;j++)
            {
                if(matrix[j][u]==1)
                    countDeg++;
            }
        return countDeg;
    }

    //returns the degree of vertex u
}

void Graph::printAdjVertices(int u)
{
    for(int j=0; j<nVertices;j++)
        {
            if(matrix[u][j]==1)
                printf(" %d", j);
        }
    //prints all adjacent vertices of a vertex u
}

bool Graph::hasCommonAdjacent(int u, int v)
{
     for(int i=0; i<nVertices;i++)
        {
            for(int j=0; j<nVertices;j++)
            {
                if(matrix[u][i]&&matrix[v][j])
                    return true;
            }

        }
    return false;
    //returns true if vertices u and v have common adjacent vertices

}

void Graph::bfs(int source)
{
 Queue q1;

    for(int i=0;i<nVertices;i++)
        colorMarked[i]=false;

    colorMarked[source]=true;
    q1.enqueue(source);

    level[source]=0;

    while(!q1.empty())
    {
        parentVertex=q1.dequeue();
        cout<<parentVertex<<" ";
        //colorMarked[parentVertex]=true;

        for(int i=0;i<nVertices;i++)
        {
            if(matrix[parentVertex][i]==1)
            {
                int childVertex=i;

                if(!colorMarked[childVertex])
                    {
                        level[childVertex]=level[parentVertex]+1;
                        colorMarked[childVertex]=true;
                        q1.enqueue(childVertex);
                    }
            }

        }
    }

}

int Graph::getDist(int u, int v)
{

    bfs(u);
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    return level[v] ;
}


void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<nVertices;j++)
        {
            if(matrix[i][j]==1)
                printf(" %d", j);
        }
        printf("\n");
    }
}

Graph::~Graph()
{
    if(colorMarked) delete [] colorMarked;
    if(level) delete [] level;
    //write your destructor here
}


//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void)
{
    int n;
    int choice;
    bool dir;
    printf("Enter your choice:\n");
    printf("1. directed graph   2. undirected graph\n");
    scanf("%d",&choice);
    if(choice == 1)dir = true;
    else if(choice == 2)dir = false;

    Graph g(dir);
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    g.setnVertices(n);

    while(1)
    {
        printf("1. Add edge. \n");
        printf("2. Remove edge. \n");
        printf("3. Edge between. \n");
        printf("4. Get degree . \n");
        printf("5. Print adjacent vertices of. \n");
        printf("6. Is there common between . \n");
        printf("7. Run bfs. \n");
        printf("8. Get distance between. \n");
        printf("9. Print Graph \n10. Exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            cout<<"### Give the input of vertices =";
            int u, v;
            scanf("%d%d", &u, &v);
            g.addEdge(u, v);
            cout<<"### Edge added "<<endl;
        }
        else if(ch==2)
        {
            cout<<"### Give the input of vertices =";
            int u, v;
            scanf("%d%d", &u, &v);
            g.removeEdge(u, v);
            cout<<"### Edge removed if exist"<<endl;
        }
        else if(ch==3)
        {
            cout<<"### Give the input of vertices =";
            int u, v;
            scanf("%d%d", &u, &v);
            if(g.isEdge(u, v))
                cout<<"### There is edge between u and v "<<endl;
            else
                cout<<"### There is no edge between u and v "<<endl;

        }
        else if(ch==4)
        {
             cout<<"### Give the input vertice =";
            int u;
            scanf("%d", &u);
            if(!dir)
            {

            cout<<"### The degree of "<<u<<"is :"<<g.getDegree(u)<<endl;
            }
            else
            {
                cout<<"### The degree of "<<u<<"is :"<<g.getDegree(u,true)<<endl;
            }
        }
        else if(ch==5)
        {
            cout<<"### Give the input vertice =";
            int u;
            scanf("%d", &u);
            cout<<"### The adjacent of "<<u<<" is :";
            g.printAdjVertices(u);
            cout<<endl;
        }
        else if(ch==6)
        {
            cout<<"### Give the input of vertices =";
            int u, v;
            scanf("%d%d", &u, &v);
            if(g.hasCommonAdjacent(u, v))
                cout<<"### There is common between u and v "<<endl;
            else
                cout<<"### There is no common between u and v "<<endl;

        }
        else if(ch==7)
        {
            cout<<"### Give the input vertice =";
            int u;
            scanf("%d", &u);
            cout<<"### BFS =";
            g.bfs(u);
            cout<<endl;

        }
        else if(ch==8)
        {
            cout<<"### Give the input of vertices =";
            int u, v;
            scanf("%d%d", &u, &v);
            cout<<"### Distance ="<<g.getDist(u,v)<<endl;
        }
        else if(ch==9)
        {
            cout<<"### The graph is now ="<<endl;
            g.printGraph();
        }
        else if(ch==10)
        {
            cout<<"### The graph is deleted"<<endl;
            break;
        }
    }

}
