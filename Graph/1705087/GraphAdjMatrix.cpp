#include<bits/stdc++.h>

#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3

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
    int *colorMarked;
    int *parentNode;
    int *level;
    int parentVertex;


public:
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	bool addEdge(int u, int v);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getInDegree(int u);
    int getOutDegree(int u);
    int getDegree(int u,bool out=true);
    void printAdjVertices(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
	void bfs(int source,bool draw=true); //will run bfs in the graph
    void bfs_run(int source,bool draw);
    void dfs(int source,bool draw=true);
    void dfs_run(int u,bool draw);
};

int Graph::getInDegree(int u)
{
    return getDegree(u, false);
}

int Graph::getOutDegree(int u)
{
    return getDegree(u, true);
}


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	matrix = 0 ;
	directed = dir ; //set direction of the graph
	//define other variables to be initialized
	colorMarked=new int [10];
	parentNode=new int [10];
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
	colorMarked=new int [nVertices];

    if(parentNode!=0) delete[] parentNode ;
	parentNode=new int [nVertices];

	if(level!=0) delete[] level ;
	level=new int [nVertices];

}

bool Graph::addEdge(int u, int v)
{
    //write your code here
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return false;
    matrix[u][v] = 1;
    if(!directed) matrix[v][u] = 1;

    return true;

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

void Graph::bfs(int source,bool draw)
{
    for(int i=0;i<nVertices;i++)
        colorMarked[i]=WHITE;

        bfs_run(source,draw);

        for(int i=0;i<nVertices;i++)
        {
            if(colorMarked[i]==WHITE)
            {
                bfs_run(i,draw);
            }
        }
}

void Graph::bfs_run(int source,bool draw)
{
 Queue q1;

    colorMarked[source]=GREY;
    parentNode[source]=-1;

    q1.enqueue(source);

    level[source]=0;

    while(!q1.empty())
    {
        parentVertex=q1.dequeue();

        if(draw)
            cout<<parentVertex<<" ";
        //colorMarked[parentVertex]=true;

        colorMarked[parentVertex]=BLACK;

        for(int i=0;i<nVertices;i++)
        {
            if(matrix[parentVertex][i]==1)
            {
                parentNode[i]=parentVertex;

                int childVertex=i;

                if(colorMarked[childVertex]==WHITE)
                    {
                        level[childVertex]=level[parentVertex]+1;
                        colorMarked[childVertex]=GREY;
                        q1.enqueue(childVertex);
                    }
            }

        }
    }

}

int Graph::getDist(int u, int v)
{

    bfs(u,false);
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    return level[v] ;
}

void Graph::dfs_run(int u,bool draw)
{
    colorMarked[u]=GREY;


    if(draw)
        cout<<u<<" ";

    for(int i=0;i<nVertices;i++)
    {
        if(matrix[u][i]==1)
        {


            int childVertex=matrix[u][i];

            parentNode[childVertex]=u;

            if(colorMarked[childVertex]==WHITE)
            {
                dfs_run(childVertex,draw);
            }

        }
    }

    colorMarked[u]=BLACK;
}

void Graph::dfs(int source, bool draw)
{

    for(int i=0;i<nVertices;i++)
    {
        colorMarked[i]=WHITE;
    }

    parentNode[source]=-1;
    dfs_run(source,draw);

    for(int i=0;i<nVertices;i++)
    {
        if(colorMarked[i]==WHITE)
        {
            parentNode[i]=-1;
            dfs_run(i,draw);
        }
    }



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
    if(parentNode) delete [] parentNode;
    if(level) delete [] level;
    //write your destructor here
}


//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void)
{

    printf("Enter your choice:\n");
    printf("1. Graph operation   2. staistics \n");

     int choice , opt;
    scanf("%d",&choice);

    if(choice == 1) opt = true;
    else if(choice == 2) opt = false;

    if(opt)
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
        printf("9. Run dfs. \n");
        printf("10. Print Graph \n11. Exit.\n");


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
                cout<<"### The degree In of "<<u<<"is :"<<g.getInDegree(u)<<endl;
                cout<<"### The degree Out of "<<u<<"is :"<<g.getOutDegree(u)<<endl;
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
            cout<<"### Give the input vertice =";
            int u;
            scanf("%d", &u);
            cout<<"### DFS =";
            g.dfs(u);
            cout<<endl;
        }
        else if(ch==10)
        {
            cout<<"### The graph is now ="<<endl;
            g.printGraph();
        }
        else if(ch==11)
        {
            cout<<"### The graph is deleted"<<endl;
            break;
        }
    }

    }

    else
    {
    int choice2,choice3;
    bool dir,select;
    printf("Enter your choice:\n");
    printf("1. directed graph   2. undirected graph\n");
    scanf("%d",&choice2);
    if(choice2 == 1) dir = true;
    else if(choice2 == 2) dir = false;

   srand(time(0));

    printf("1. Manual   2. Auto\n");
    scanf("%d",&choice3);
    if(choice3 == 1) select = true;
    else if(choice3 == 2) select = false;

    if(select)
    {
        int a,b;
        printf("Enter Verteces and Edges =");
        scanf("%d %d",&a,&b);



       int vertices=a;
        {
            cout<<"### The number of Vertices = "<<vertices<<endl;


            Graph g(dir);
            g.setnVertices(vertices);

            int endLimit=(vertices*vertices-vertices)/8;

            double totalTime;

            int edges=b;
            {
                cout<<"  --- When number of edges ="<<edges<<" ";





                for(int i=1; i<=edges; i++)
                {
                    //cout<<"  created edges ="<<i<<" ";
                    int u=(rand()%vertices);
                    int v=(rand()% vertices);

                    if(g.isEdge(u,v))
                    {
                        i=i-1;
                    }
                    else
                    {
                        g.addEdge(u,v);
                    }

                }

                cout<<"debug"<<endl;



                 totalTime=0;



                for(int runI=0;runI<10;runI++)
                {
                    int randSource=(rand()% vertices);



                    clock_t startTime, endTime;
                    double cpu_time_used;


                    startTime = clock();
                    g.bfs(randSource,false);
                    endTime = clock();

                    cpu_time_used = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;

                    //cout<<" BFS part time  "<<cpu_time_used<<endl;

                    totalTime=totalTime+cpu_time_used;
                }

                cout<<"      The avg time ( milli seceond ) needed is =  "<<totalTime/10<<endl;

                for(int i=0; i<vertices; i++)
                {
                    for(int j=0; j<vertices; j++)
                    {
                        if(g.isEdge(i,j))

                            g.removeEdge(i,j);

                    }
                }



            }

        //g.~Graph();

        cout<<endl;

        }
    }

    else
    {



        for(int vertices=1000;vertices<=16000;vertices=vertices*2)
        {
            cout<<"### The number of Vertices = "<<vertices<<endl;


            Graph g(dir);
            g.setnVertices(vertices);

            int endLimit=(vertices*vertices-vertices)/8;

            double totalTime;

            for(int edges=vertices;edges<=endLimit;edges=edges*2)
            {
                cout<<"  --- When number of edges ="<<edges<<" ";





                for(int i=1; i<=edges; i++)
                {
                    //cout<<"  created edges ="<<i<<" ";
                    int u=(rand()%vertices);
                    int v=(rand()% vertices);

                    if(g.isEdge(u,v))
                    {
                        i=i-1;
                    }
                    else
                    {
                        g.addEdge(u,v);
                    }

                }

                cout<<"debug"<<endl;



                 totalTime=0;



                for(int runI=0;runI<10;runI++)
                {
                    int randSource=(rand()% vertices);



                    clock_t startTime, endTime;
                    double cpu_time_used;


                    startTime = clock();
                    g.bfs(randSource,false);
                    endTime = clock();

                    cpu_time_used = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;

                    //cout<<" BFS part time  "<<cpu_time_used<<endl;

                    totalTime=totalTime+cpu_time_used;
                }

                cout<<"      The avg time ( milli seceond ) needed is =  "<<totalTime/10<<endl;

                for(int i=0; i<vertices; i++)
                {
                    for(int j=0; j<vertices; j++)
                    {
                        if(g.isEdge(i,j))

                            g.removeEdge(i,j);

                    }
                }



            }

        //g.~Graph();

        cout<<endl;

        }
    }





    }
    return 0;

}
