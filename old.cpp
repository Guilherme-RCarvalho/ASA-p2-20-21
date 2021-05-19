//LOG
//  change implementation from old web_copy to new main

//---------------------------------------------------------------------------//
//                                                                           //
//     IST-2020/2021    2 Semestre  ASA-Pedro Monteiro                       //
//     15/04/2021   18:14     1 Projeto                                      //
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

using namespace std;

void makeGraph(int np, int ndep);

//---------------------------------------------------------------------------//
//                                                                           //
//                                GRAPH CLASS                                //
//                                                                           //
//---------------------------------------------------------------------------//


class Graph{
    int _nnode;
    int _edge;

    list<int> *_adjList;     //adjacency list
    int *_info;               //array of ints that will contain information

public:
    Graph(int nnode, int nedge);
    void addEdge(int source, int dest);
    void printGraph();
    void topologicalSearch();
    
    void cleanGraph();


};



//Graph constructor
Graph::Graph(int nnode, int nedge){
    this->_nnode = nnode;
    this->_edge = nedge;
    _adjList = new list<int>[nnode];

    _info = new int[nnode]{0};

}

//Add a connection from source to dest
void Graph::addEdge(int source, int dest){
    _adjList[source].push_back(dest);
}

void Graph::printGraph(){
    cout << endl;
    for(int counter = 0; counter < this->_nnode; counter ++){
        cout << counter << " : ";
        for(list<int>::iterator i = _adjList[counter].begin(); i != _adjList[counter].end(); i++){
            cout << *i << " ";
        }
        cout << endl;
    }       
    cout << endl;

}


//----------------------------------------------------------------------------------------------------------------------------------------------//
//                                                                                                                                              //
//   Algorithm used: Kahn's Algorithm (considering the graph is a DAG).                                                                         //
//   Partially implemented from: https://www.geeksforgeeks.org/topological-sorting-indegree-based-solution/ (c++ solution).                     //
//   Methods implemented: (1) Discover how many interactions are needed to reach all nodes.                                                     //  
//                        (2) Calculate the longest possible path.                                                                              //
//                                                                                                                                              //
//   Steps to implement the algorithm:                                                                                                          //
//          (1) Add all edges information to build the graph. O(E)                                                                              //
//          (2) Compute the indegree of all the vertices. O(V+E)                                                                                //
//              ADDED! Counter to save initial number of vertices with indegree = 0. This will be                                               //
//                 minimum number of interactions.                                                                                              //
//          (3) Create a queue that is initialized with all the vertices with indegree = 0. O(V)                                                //  
//          (4) For each vertice in the queue, remove it's edges one by one.                                                                    //
//              Update the indegree of the adjacent vertices. If a vertice reaches indegree = 0, add it to the queue.                           //  
//              Repeat until queue is empty.                                                                                                    //
//              ADDED! Keep track of longest path: When adding a vertice to the queue, update his path value and save the max value.            //
//              O(V+E)                                                                                                                          //
//          (5) Print result and claer memory.                                                                                                  //
//                                                                                                                                              //
//----------------------------------------------------------------------------------------------------------------------------------------------//


void Graph::topologicalSearch(){

    //Array where I will store all of the indegrees
	int *indegree;
    indegree = new int[this->_nnode]{0};
    


    //Calculate all the indegrees
    for(int source = 0; source < this->_nnode; source++){
        list<int>::iterator it;
        for(it = _adjList[source].begin(); it != _adjList[source].end(); it++){
            // cout << *it << endl;
            indegree[*it]++;
        }
    }

    
    //Create the queue where the nodes with indegree 0 will be stored
    queue<int> myQueue;
    for(int counter = 0; counter < this->_nnode; counter++){
        if(indegree[counter] == 0){
            myQueue.push(counter);
        }
    }

    //print the number of interventions needed for all the dominos to fall
    cout << myQueue.size();
    int maxPath = 0;

    while(!myQueue.empty()){
        int source = myQueue.front();
        myQueue.pop();

        //update the indegrees for all the dest reached from source
        list<int>::iterator it;
        for(it = _adjList[source].begin(); it != _adjList[source].end(); it++){
            //if indegree becomes zero:
            //  add to queue 
            //  make dest info = source info + 1;
            if(--indegree[*it] == 0){
                _info[*it] = _info[source] + 1;

                //Update maxPath without making branches                 
                maxPath = _info[*it] * (maxPath < _info[*it]) + maxPath * (maxPath >= _info[*it]);


                myQueue.push(*it);

            }
        }
    }

    cout << " " << maxPath + 1 << endl;
    // for(int counter = 0; counter < this->_nnode; counter++){
    //     cout << counter << " -> " << indegree[counter] << endl;
    // }
    // for(int counter = 0; counter < this->_nnode; counter++){
    //     cout << "Path" << " -> " << _info[counter] << endl;
    // }
    // delete[] indegree;

}

void Graph::cleanGraph(){
    // cout << "Graph has been cleared" << endl;
    delete[] _adjList;
    delete[] _info;
    
    // cout << "Pointer List: " << sizeof(_adjList[0]) << endl;
    
}


//---------------------------------------------------------------------------//
//                                                                           //
//                                  MAIN                                     //
//                                                                           //
//---------------------------------------------------------------------------//

int main(){


    int np, ndep;

    if(scanf("%d %d\n", &np, &ndep) < 1){
        clog << "There has been an error reading the input";
        return 0; 
    }

    // cout << "This is the number of pieces: " << np << "\n";
    // cout << "This is the number of dep: " << ndep << "\n";

    makeGraph(np, ndep);

    return 0;
}

void makeGraph(int np, int ndep){
    
    Graph myGraph(np, ndep);
    int source, dest;

    for(; ndep > 0; ndep--){
        if(scanf("%d %d\n", &source, &dest) < 1){
            clog << "There has been an error reading the input";        
        }
        // cout << "Going from: " << source << " to: " << dest << endl;
        //convert it to 0 index 
        myGraph.addEdge(source-1, dest-1);

    }
    
    // myGraph.printGraph();
    myGraph.topologicalSearch();
    // myGraph.cleanGraph();

}



