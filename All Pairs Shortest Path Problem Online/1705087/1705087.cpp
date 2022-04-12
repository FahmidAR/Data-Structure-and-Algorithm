#include<bits/stdc++.h>

#define INF 999999
#define NULL_VALUE -999999
#define WHITE 1
#define GREY 2
#define BLACK 3
#define DEBUG 0
#define INDEX 1

using namespace std;

typedef pair<int,int> p;

class Edge {

  private:

    int u;
    int v;
    double w;

  public:

    Edge(int i,int j,double k)
    {
        u = i;
        v = j;
        w = k;
    }

    void setU(int i) {
      u = i;
    }

    void setV(int i) {
      v = i;
    }

    void setW(double i) {
      w = i;
    }

    int getU() {
      return u;
    }

    int getV() {
      return v;
    }

    double getW() {
      return w;
    }
};



class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	vector<Edge> edgeAll;
	//define other variables required for bfs such as color, parent, and dist
	//you must use pointers and dynamic allocation
    int *colorMarked;
    int *level;
    int *distD;
    int *parD;
    int *distB;
    int parentVertex;
    double ** disMatrix ;
    int ** parMatrix ;


public:
	Graph(bool dir = true);
	~Graph();
	void setnVertices(int n);
	void printGraph();
	void addEdge(int u, int v,double w);
	void rwEdge(int u, int v,double w);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int weighVal(int u,int v);
    void clearSpvalue();
    void floydWarshall();
    Edge* searchEdge(int u ,int v);
    void printDisMatrix();
    void printPreMatrix();
    double getShortestPath(int u, int v);
    void printShortestPath(int u, int v,bool flag);
    bool bellMand(int s);
    void dikstra(int s);
    void johnsonAlgo();

};

void Graph::dikstra(int s)
{
    priority_queue< p, vector <p>, greater<p> > pqd;

    for(int i=0;i<nVertices;i++)
    {
        distD[i]=INF;
        parD[i]=-1;
    }

    distD[s]=0;

    pqd.push(make_pair(0,s));

    int now, child;
    double weight;

    while(!pqd.empty())
    {
        now=pqd.top().second;
        pqd.pop();


        for(int k=0;k<edgeAll.size();k++)
        {
            Edge eg =edgeAll[k];

            if(eg.getU()==now)
            {
                child=eg.getV();
                weight=eg.getW();
            }

            if(distD[child]>distD[now]+weight)
            {
                distD[child]=distD[now]+weight;

                parD[child]=now;

                pqd.push(make_pair(distD[child],child));
            }
        }


    }

}


void Graph::johnsonAlgo()
{
    this->nVertices++;

    for(int i=0;i<nVertices-1;i++)
    {
        Edge eg(nVertices-1,i,0);

        this->nEdges++;

        edgeAll.push_back(eg);
    }

    if(!bellMand(nVertices-1))
    {

        for(int k=0;k<edgeAll.size();k++)
        {
            double w=edgeAll[k].getW()+distB[edgeAll[k].getU()]-distB[edgeAll[k].getV()];
            rwEdge(edgeAll[k].getU(),edgeAll[k].getV(),w);
        }

        for(int i=0;i<nVertices-1;i++)
        {
            removeEdge(nVertices-1,i);
        }

        this->nVertices--;

        for(int i=0;i<nVertices;i++)
        {
            dikstra(i);

            for(int k=0;k<nVertices;k++)
                {
                    int x=distB[k]-distB[i];
                    disMatrix[i][k]=distD[k]+x;
                    parMatrix[i][k]=parD[k];
                }

        }


        for(int k=0;k<edgeAll.size();k++)
        {
            double w=edgeAll[k].getW()+distB[edgeAll[k].getV()]-distB[edgeAll[k].getU()];
            rwEdge(edgeAll[k].getU(),edgeAll[k].getV(),w);
        }

    }
    else
    {
            cout<<" NEG EDGE CYCLE"<<endl;
    }




}

bool Graph::bellMand(int s)
{
    for(int i=0;i<nVertices;i++)
    {
        distB[i]=INF;
    }

    distB[s]=0;


    for(int run=0;run<nVertices-1;run++)
    {
        for(int k=0;k<edgeAll.size() ;k++)
        {
            Edge eg =edgeAll[k];

            int i=eg.getU();
            int j=eg.getV();

            if(distB[i]!=INT_MAX)

            {
                if(distB[i]+weighVal(i,j)<distB[j])
                {
                  //  cout<<i<<" "<<j<<endl;
                    distB[j]=distB[i]+weighVal(i,j);
                  //  cout<<j<<":"<<dist[j]<<endl;
                }
            }


        }
    }

    for(int run=0;run<nVertices-1;run++)
    {
        for(int k=0;k<edgeAll.size() ;k++)
        {
            Edge eg =edgeAll[k];

            int i=eg.getU();
            int j=eg.getV();

            if(distB[i]!=INT_MAX)

            {
                if(distB[i]+weighVal(i,j)<distB[j])
                {
                    return true;;
                }
            }

        }
    }

    return false;
}

Edge* Graph::searchEdge(int u, int v)
{
    vector<Edge>::iterator it;

    for( it =edgeAll.begin(); it <= edgeAll.end(); ++it)
    {


        if((*it).getU()==u&&(*it).getV()==v)
        {
            return &(*it);
        }
    }
}

double Graph::getShortestPath(int u, int v)
{
        return disMatrix[u][v];
}

void Graph::printShortestPath(int u, int v,bool flag)
{


    if(u==v)
    {
        cout<<u+INDEX<<" -->";
    }

    else if (parMatrix[u][v]==-1)
    {
        cout<<"No shortest path exist";
    }
    else
    {
        printShortestPath(u,parMatrix[u][v],true);

        cout<<v+INDEX<<"("<<weighVal(parMatrix[u][v],v)<<")";

        if(flag)
        cout<<" -->";

    }

}

void Graph::printDisMatrix()
{
    for(int i=0;i<nVertices ;i++)
    {
        for(int j=0;j<nVertices ;j++)
        {
            if(disMatrix[i][j]!=INF)
            cout<<disMatrix[i][j]<<" ";
            else
            cout<<"INF ";
        }
        cout<<endl;
    }
}
void Graph::printPreMatrix()
{
    for(int i=0;i<nVertices ;i++)
    {
        for(int j=0;j<nVertices ;j++)
        {
            if(parMatrix[i][j]==-1)
                cout<<"NIL ";
            else
                cout<<parMatrix[i][j]+INDEX<<" ";
        }
        cout<<endl;
    }
}

void Graph::printGraph()
{
    if(DEBUG)
    {
        for(int j=0; j<edgeAll.size(); j++)
        {
            Edge eg=edgeAll[j];

            cout<<"### DEBUG EDGE u v w "<<eg.getU()<<" "<<eg.getV()<<" "<<weighVal(eg.getU(),eg.getV())<<endl;
        }
    }


    printf("\nNumber of vertices: %d , Number of edges: %d \n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf(" %d :", i+INDEX);

        int flag = 0 ;

        for(int j=0; j<edgeAll.size(); j++)
        {
            Edge eg=edgeAll[j];

            if(eg.getU()==i&&flag)
            {
                cout<<"-->";
            }

            if(eg.getU()==i)
            {
                flag=1;
                cout<<" "<<eg.getV()+INDEX<<" ("<<eg.getW()<<") ";
            }
        }
        cout<<endl;
    }
}

int Graph::weighVal(int u,int v)
{
    for(int i=0; i<edgeAll.size(); i++)
    {
        Edge eg=edgeAll[i];

        if(eg.getU()==u&&eg.getV()==v)
        {
            return eg.getW();
        }
    }
}

void Graph::clearSpvalue()
{

    for(int i=0;i<nVertices ;i++)
    {
        for(int j=0;j<nVertices ;j++)
        {
                disMatrix[i][j]= INF;
                parMatrix[i][j]= -1;
        }
    }
}

void Graph::floydWarshall()
{
    for(int i=0;i<nVertices ;i++)
    {
        for(int j=0;j<nVertices ;j++)
        {
            if(isEdge(i,j))
            {
                disMatrix[i][j]= weighVal(i,j);
            }
            else
            {
                disMatrix[i][j]=INF;
            }




            if(i==j)
            {
                parMatrix[i][j]=-1;
                disMatrix[i][j]=0;
            }
            else if(disMatrix[i][j]!=INF)
            {
                parMatrix[i][j]=i;
            }
            else
            {
                parMatrix[i][j]=-1;
            }

        }
    }

    if(DEBUG)
    {
    for(int i=0;i<nVertices ;i++)
    {
        for(int j=0;j<nVertices ;j++)
        {

                cout<<"d "<<disMatrix[i][j]<<" ";
               // cout<<" p "<<parMatrix[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    }


    for(int k=0;k<nVertices ;k++)
    {
    for(int i=0;i<nVertices ;i++)
    {
        for(int j=0;j<nVertices ;j++)
        {
            if(disMatrix[i][k]!=INF&&disMatrix[k][j]!=INF)
            {

                if(disMatrix[i][k]+disMatrix[k][j]<disMatrix[i][j])
                {
                    disMatrix[i][j]=disMatrix[i][k]+disMatrix[k][j];
                    parMatrix[i][j]=parMatrix[k][j];
                }

            }

        }

        if(disMatrix[i][i]<0)
        {
            cout<<" NEG WEIGHT CYCLE"<<endl;
            return;
        }
    }
    }


}


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	disMatrix = 0 ;
	parMatrix = 0 ;
	parentVertex=0 ;
	directed = dir ; //set direction of the graph
	//define other variables to be initialized
	colorMarked=new int [10];
	distD=new int[10];
	parD=new int[10];
	distB=new int[10];
	level=new int[10];
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;

    disMatrix = new double*[nVertices];
    for(int i=0;i<nVertices;i++)
    {
        disMatrix[i] = new double[nVertices];
        for(int j=0;j<nVertices;j++)
            disMatrix[i][j] = INF; //initialize the matrix cells to 0
    }

    parMatrix = new int*[nVertices];
    for(int i=0;i<nVertices;i++)
    {
        parMatrix[i] = new int[nVertices];
        for(int j=0;j<nVertices;j++)
            parMatrix[i][j] = -1; //initialize the matrix cells to 0
    }



	if(colorMarked!=0) delete[] colorMarked ;
	colorMarked=new int [nVertices];

	if(level!=0) delete[] level ;
	level=new int [nVertices];

	if(distB!=0) delete[] distB ;
    distB=new int [nVertices+1];

    if(distD!=0) delete[] distD ;
    distD=new int [nVertices+1];

    if(parD!=0) delete[] parD ;
    parD=new int [nVertices+1];

}

void Graph::rwEdge(int u, int v,double w)
{
    vector<Edge>::iterator it;

    for( it =edgeAll.begin(); it != edgeAll.end(); ++it)
    {


        if((*it).getU()==u&&(*it).getV()==v)
        {
           (*it).setW(w);
        }
    }
}

void Graph::addEdge(int u, int v,double w)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range

    this->nEdges++ ;

	Edge eg(u,v,w);

	edgeAll.push_back(eg);

	if(DEBUG) cout<<"### DEBUG EDGE  "<<nEdges<<endl;

}

void Graph::removeEdge(int u, int v)
{

    if(isEdge(u,v))
    {
        this->nEdges--;

        vector<Edge>::iterator it;

    for( it =edgeAll.begin(); it <= edgeAll.end(); ++it)
    {


        if((*it).getU()==u&&(*it).getV()==v)
        {
            edgeAll.erase(it);
        }
    }

    }

    //write this function
}

bool Graph::isEdge(int u, int v)
{
    for(int i=0; i<edgeAll.size(); i++)
    {
        Edge eg=edgeAll[i];

        if(eg.getU()==u&&eg.getV()==v)
        {
            return true;
        }
    }
    return false;
}



Graph::~Graph()
{

    if(colorMarked) delete [] colorMarked;
    if(level) delete [] level;
    if(distB) delete [] distB;
    if(distD) delete [] distD;
    if(parD) delete [] parD;
    //write your destructor here
}

int main(void)
{
    int vertices , edges ;
    int u , v;
    double w;

    Graph g;

    cin>>vertices>>edges;

    g.setnVertices(vertices);

    for(int i=0;i<edges;i++)
    {
       // cout<<edges<<endl;

        cin>>u>>v>>w;

        u=u-INDEX;
        v=v-INDEX;
        w=w;

        g.addEdge(u,v,w);
    }

    cout<<"\n---  Graph Created.  ---"<<endl;
    cout<<"\###  ENJOY EVERY MONENT   ###\n"<<endl;

        while(1)
    {
        printf("1. APSP Matrix Clear . \n");
        printf("2. FLOYD WARSHALL Algorithm. \n");
        printf("3. JOHNSON Algorithm. \n");
        printf("4. Shortest path from U to V . \n");
        printf("5. Print Graph. \n");
        printf("6. Print Distance Matrix. \n");
        printf("7. Print Predecessor Matrix. \n");
        printf("8. Path including K \n");
        printf("9. Exit.\n");

        int ch;
        scanf("%d",&ch);\

        if(ch==1)
        {
            g.clearSpvalue();
            cout<<"### APSP Matrix Cleared  "<<endl;
        }
        else if(ch==2)
        {

            g.floydWarshall();
            cout<<"### FLOYD WARSHALL Algorithm Implemented"<<endl;
        }
        else if(ch==3)
        {
            g.johnsonAlgo();
            cout<<"### JOHNSON Algorithm Implemented"<<endl;
        }
        else if(ch==4)
        {
            //cout<<"### Give the input of vertices =";
            int u, v;
            cin>>u>>v;

            u=u-1;
            v=v-1;

            cout<<"Shortest Path Weight: "<<g.getShortestPath(u,v)<<endl;

            g.printShortestPath(u,v,false);

            cout<<endl;

        }
        else if(ch==5)
        {
            cout<<"### GRAPH: "<<endl;

            g.printGraph();

            cout<<endl;
        }
        else if(ch==6)
        {
            cout<<"### Distance Matrix: "<<endl;

            g.printDisMatrix();

            cout<<endl;
        }
        else if(ch==7)
        {
            cout<<"### Predecessor Matrix: "<<endl;

            g.printPreMatrix();

            cout<<endl;

        }
        else if(ch==8)
        {
            int u, v,k ,run=1;

            cin>>k;
            k=k-1;

            while(run)
            {
            cin>>u>>v;


            u=u-1;
            v=v-1;

            if((u==-1)&&(v==-1))
            {
                run=0;
            }

            cout<<"Shortest Path Weight: "<<g.getShortestPath(u,k)+g.getShortestPath(k,v)<<endl;

            g.printShortestPath(u,k,false);

            if(k!=v)
            {
                cout<<"-->";
            }

            g.printShortestPath(k,v,false);

            cout<<endl;


            }

        }
        else
        {
            cout<<"### Program Ended , Enjoy Life Now ^_^ "<<endl;
            break;
        }
    }

    return 0;
}
