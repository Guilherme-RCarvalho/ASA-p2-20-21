//---------------------------------------------------------------------------//
//                                                                           //
//     IST-2020/2021    2 Semestre  ASA-Pedro Monteiro                       //
//     19/05/2021   18:14       2 Projeto                                    //
//     Jose Mateus              ist196884                                    //
//     Guilherme Carvalho       ist196868                                    //
//     Mooshak: 1700                                                         //
//---------------------------------------------------------------------------//

//---------------------------------------------------------------------------//
//                                                                           //
//                                   INIT                                    //
//                                                                           //
//---------------------------------------------------------------------------//



#include <stdlib.h>
#include <iostream>
#include <cstdio>
#include <list>
#include <memory>
#include <queue>
#include <climits>

using namespace std;



//---------------------------------------------------------------------------//
//                                                                           //
//                            GRAPH REPRESENTATION                           //
//                                                                           //
//---------------------------------------------------------------------------//

// A structure to represent a edge between
// two vertex
struct Edge
{
    int v ;  // Vertex v (or "to" vertex)
             // of a directed edge u-v. "From"
             // vertex u can be obtained using
             // index in adjacent array.
 
    int flow ; // flow of data in edge
 
    int C;    // capacity
 
    int rev ; // To store index of reverse
              // edge in adjacency list so that
              // we can quickly find it.
};
 
// Residual Graph
class Graph
{
    int V; // number of vertex
    int *level ; // stores level of a node
    vector< Edge > *adj;
public :
    Graph(int V)
    {
        adj = new vector<Edge>[V];
        this->V = V;
        level = new int[V];
    }
 
    // add edge to the graph
    void addEdge(int u, int v, int C)
    {
        // Forward edge : 0 flow and C capacity
        Edge a{v, 0, C, (int)adj[v].size()};
 
        // Back edge : 0 flow and 0 capacity
        Edge b{u, 0, 0, (int)adj[u].size()};
 
        adj[u].push_back(a);
        adj[v].push_back(b); // reverse edge
    }
 
    bool BFS(int s, int t);
    int sendFlow(int s, int flow, int t, int ptr[]);
    int DinicMaxflow(int s, int t);
};



//----------------------------------------------------------------------------------------------------------------------------------------------//
//                                                                                                                                              //
//   Algorithm used: Dinic's Algorithm.                                                                                                         //
//   Implemented from: https://www.geeksforgeeks.org/dinics-algorithm-maximum-flow/ (c++ solution).                                             //
//   New Methods implemented: Transform the input.                                                                                              //
//                                                                                                                                              //
//   Steps to implement the algorithm:                                                                                                          //
//          (1) Add all edges information to build the graph. O(E)                                                                              //
//          (2) In each iteration, we construct new level graph and find blocking flow. It can be proved that the number of levels increase     //
//              at least by one in every iteration (Refer the below reference video for the proof). So the outer loop runs at most O(V) times.  //
//               |                                                                                                                              //
//          (3)  ->>  Sending multiple more flows until a blocking flow is reached takes O(VE) time.  Resulting Complexity: O (V²E)             //
//                                                                                                                                              //
//----------------------------------------------------------------------------------------------------------------------------------------------//



// Finds if more flow can be sent from s to t.
// Also assigns levels to nodes.
bool Graph::BFS(int s, int t)
{
    for (int i = 0 ; i < V ; i++){
        level[i] = -1;
    }
 
    level[s] = 0;  // Level of source vertex
 
    // Create a queue, enqueue source vertex
    // and mark source vertex as visited here
    // level[] array works as visited array also.
    list< int > q;
    q.push_back(s);
 
    vector<Edge>::iterator i ;
    while (!q.empty()){
        int u = q.front();
        q.pop_front();
        for (i = adj[u].begin(); i != adj[u].end(); i++){
            Edge &e = *i;
            if (level[e.v] < 0  && e.flow < e.C){
                // Level of current vertex is,
                // level of parent + 1
                level[e.v] = level[u] + 1;
 
                q.push_back(e.v);
            }
        }
    }
 
    // IF we can not reach to the sink we
    // return false else true
    return level[t] < 0 ? false : true ;
}
 
// A DFS based function to send flow after BFS has
// figured out that there is a possible flow and
// constructed levels. This function called multiple
// times for a single call of BFS.
// flow : Current flow send by parent function call
// start[] : To keep track of next edge to be explored.
//           start[i] stores  count of edges explored
//           from i.
//  u : Current vertex
//  t : Sink
int Graph::sendFlow(int u, int flow, int t, int start[])
{

    // Sink reached
    if (u == t){
        return flow;
    }
 
    // Traverse all adjacent edges one -by - one.
    for (  ; start[u] < (int)adj[u].size(); start[u]++){ 
        // Pick next edge from adjacency list of u
        Edge &e = adj[u][start[u]];
                                     
        if (level[e.v] == level[u]+1 && e.flow < e.C){
            // find minimum flow from u to t    
            int curr_flow = min(flow, e.C - e.flow);

            int temp_flow = sendFlow(e.v, curr_flow, t, start);
            
 
            // flow is greater than zero
            if (temp_flow > 0){
                // add flow  to current edge
                e.flow += temp_flow;
 
                // subtract flow from reverse edge
                // of current edge
                adj[e.v][e.rev].flow -= temp_flow;
                return temp_flow;
            }
        }
    }

    return 0;
}
 
// Returns maximum flow in graph
int Graph::DinicMaxflow(int s, int t)
{
    // Corner case
    if (s == t){
        return -1;
    }
 
    int total = 0;  // Initialize result
 
    // Augment the flow while there is path
    // from source to sink
    while (BFS(s, t) == true){ // O(V)
        // store how many edges are visited
        // from V { 0 to V }
        int *start = new int[V+1] {0};
 
        // while flow is not zero in graph from S to D
        while (int flow = sendFlow(s, INT_MAX, t, start)) //O(VE)
 
            // Add path flow to overall flow
            total += flow;
    }
 
    // return maximum flow
    return total;
}




//---------------------------------------------------------------------------//
//                                                                           //
//                                  MAIN                                     //
//                                                                           //
//---------------------------------------------------------------------------//
 
int main(){

    int np, ncost;


    if(scanf("%d %d\n", &np, &ncost) < 1){
        clog << "There has been an error reading the input";
        return 0; 
    }

   
   Graph g(np+2);
   //vamos ler o custo de cada processo em cada processador
   int cost1, cost2, edge1, edge2;
   for(int i=1; i <= np; i++){

      if(scanf("%d %d\n", &cost1, &cost2) < 1){
        clog << "There has been an error reading the input";
        return 0; 
      }

      g.addEdge(0, i, cost1);
      g.addEdge(i, 0, cost1);
      g.addEdge(i, np+1, cost2);
      g.addEdge(np+1, i, cost2);
      
   }

   //vamos ler o custo de comunicacao entre processos
   for(int i = 1; i <= ncost; i++){
      
      if(scanf("%d %d %d\n", &edge1, &edge2, &cost1) < 1){
           clog << "There has been an error reading the input";
           return 0; 
      }

      g.addEdge(edge1, edge2, cost1);
      g.addEdge(edge2, edge1, cost1);
   }
    
    printf("%d\n", g.DinicMaxflow(0, np+1));
    return 0;
}


