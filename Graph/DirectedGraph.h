
#ifndef DIRECTED_GRAPH_H
#define DIRECTED_GRAPH_H

#include <iostream>
#include <ostream>
#include <vector>
#include <queue>
#include <string>
#include <limits>
#include "../AVL/AVL.h"
#include "../data_structs/basic_priority_queue.h"

using std::vector;
using std::ostream;
using std::cout;
using std::endl;
using std::queue;
using std::string;

template<typename T>
class DirectedGraph{
    public:
        class Edge;

        class Vertex{

            friend ostream& operator<<(ostream& os, const Vertex& v){
                os << v.data << ":\tadj. list: ";
                for(Edge e : v.outgoingEdges)
                    os << e.end->data << ", ";
                return os;
            }

            public:
                Vertex(){}
                Vertex(const T& data) : data(data){}

                T data;
                Vertex* predecessor = nullptr;
                vector<Edge> outgoingEdges;
                bool visited = false;
                int weight = 0;

                bool weightCompare = false;

                //number of incoming edges
                int inDegree = 0;

                //used for temporary computation (like in topo sort)
                int tempInDegree = 0;

                bool operator<(const Vertex& v) const{
                    if(weightCompare)
                        return weight < v.weight;
                    return data < v.data;
                }

                bool operator>(const Vertex& v) const{
                    if(weightCompare)
                        return weight > v.weight;
                    return data > v.data;
                }

                bool operator>=(const Vertex& v) const{
                    if(weightCompare)
                        return weight >= v.weight;
                    return data >= v.data;
                }

                bool operator==(const Vertex& v) const{
                    if(weightCompare)
                        return weight == v.weight;
                    return data == v.data;
                }
        };

        class Edge{
            public:
                Edge() :
                    start(nullptr), end(nullptr){}
                int weight;
                Vertex* start;
                Vertex* end;
                bool operator==(const Edge& e){
                    return *start == *(e.start) && *end == *(e.end);
                }
        };

        DirectedGraph(){}
        ~DirectedGraph(){}

        void addVertex(const T& entry){
            vertices.insert(Vertex(entry));
        }

        void removeVertex(const T& target){
            vertices.remove(Vertex(target));
        }

        void addEdge(const T& start, const T& end, int weight = 1){
           typename AVL<Vertex>::Iterator startItr = vertices.get(Vertex(start));
           typename AVL<Vertex>::Iterator endItr = vertices.get(Vertex(end));

            //check if vertices were found
            if(startItr != vertices.end() && endItr != vertices.end()){

                //create directed edge between start and end
                Edge e;
                e.start = &startItr.getData();
                e.end = &endItr.getData();
                e.weight = weight;

                //add edge to start vertex
                startItr.getData().outgoingEdges.push_back(e);
                endItr.getData().inDegree++;
            }
        }

        void removeEdge(const T& start, const T& end){
           typename AVL<Vertex>::Iterator startItr = vertices.get(Vertex(start));
           typename AVL<Vertex>::Iterator endItr = vertices.get(Vertex(end));

            //check if vertices were found
            if(startItr != vertices.end() && endItr != vertices.end()){

                //create directed edge between start and end
                Edge e;
                e.start = &startItr.getData();
                e.end = &endItr.getData();

                //remove edge from start vertex
                vector<Edge>* v = &(startItr.getData().outgoingEdges);
                for(int i = 0; i < v->size(); i++)
                    if(e == v->at(i)){
                        v->erase(v->begin() + i);
                        break;
                    }
                endItr.getData().inDegree--;
            }
        }

        //do a BFS on the entire graph relative to the start vertex
        void BFS(const T& start){
            typename AVL<Vertex>::Iterator itr = vertices.get(Vertex(start));

            //start found
            if(itr != vertices.end()){
                //reset visit booleans to false - and predecessors to null
                typename AVL<Vertex>::Iterator i;
                i = vertices.begin();
                while(i.hasNext()){
                    Vertex* v = &i.next();
                    v->visited = false;
                    v->predecessor = nullptr;
                }

                //create queue and insert first element
                queue<Vertex*> q;
                itr.getData().visited = true;
                q.push(&itr.getData());

                //queue not empty
                while(!q.empty()){
                    Vertex* v = q.front();
                    q.pop();

                    //go through all neighbors
                    for(Edge e : v->outgoingEdges){

                        //unvisited
                        if(!e.end->visited){
                            e.end->visited = true;
                            e.end->predecessor = v;
                            q.push(e.end);
                        }
                    }
                }
            }
        }

        //shortest path using BFS
        void shortestPath(const T& start, const T& end){
            typename AVL<Vertex>::Iterator startItr = vertices.get(Vertex(start));
            typename AVL<Vertex>::Iterator endItr = vertices.get(Vertex(end));

            //found
            if(startItr != vertices.end() && endItr != vertices.end()){
                Vertex current = endItr.getData();
                string path = "";

                //while we can traverse back to the end
                while(current.predecessor){
                    path = " -> " + current.data + path;
                    current = *current.predecessor;
                }
                path = "Path: " + current.data + path;
                cout << path;
            }
        }

        //perform dijkstra's shortest path on the graph
        //relative to start
        void dijkstra(const T& start){
            typename AVL<Vertex>::Iterator itr = vertices.get(Vertex(start));

            if(itr != vertices.end()){

                basic_priority_queue<Vertex*> pq;

                //Vertices: reset visit booleans to false , predecessors to null, and weights to "infinity"
                typename AVL<Vertex>::Iterator i;
                i = vertices.begin();
                while(i.hasNext()){
                    Vertex* v = &i.next();
                    v->weightCompare = true;
                    v->predecessor = nullptr;
                    v->weight = 10000000;

                    //fill the container with the unvisited verticex
                    pq.insert(v);
                }
                //itr is pointing to start
                //Set starting point weight;
                itr.getData().weight = 0;
                pq.update(&itr.getData());

                while(!pq.empty()){
                    Vertex* current = pq.extractMin();
                    pq.pop();

                    //reset weight compare to false - (for correct comparisons inside AVL tree container)
                    current->weightCompare = false;

                    for(Edge e : current->outgoingEdges){
                        Vertex* adj = e.end;

                        //update Vertex weight from current to adj
                        //if there is a new shorter path to adj
                        int newWeight = current->weight + e.weight;
                        if(newWeight < adj->weight){
                            adj->predecessor = current;
                            adj->weight = newWeight;
                            //restructure pq
                            pq.update(adj);
                        }
                    }
                }
            }
        }

        //display each vertex and their adjacent vertices
        void display(){
            typename AVL<Vertex>::Iterator itr;
            itr = vertices.begin();
            while(itr.hasNext())
                cout << itr.next() << endl;
        }

        //display the predecessor vertex for each vertex from the most recent BFS
        void displayPredecessorLinks(){
            typename AVL<Vertex>::Iterator itr;
            itr = vertices.begin();
            while(itr.hasNext()){
                Vertex v = itr.next();
                cout << "Vertex: " << v.data << " pred is: ";

                //if predecessor exists
                if(v.predecessor != nullptr)
                    cout << v.predecessor->data << endl;
                else
                    cout << "NULL\n";
            }
        }

        //takes in a containers to store the data of vertices in topo order.
        bool topoSort(vector<T>& container){
            //tempIndegree to the original indegree
            typename AVL<Vertex>::Iterator itr = vertices.begin();
            while(itr.hasNext()){
                Vertex* v = &itr.next();
                v->tempInDegree = v->inDegree;
            }

            //queue up all vertices with indegrees of zero
            //No incoming edges
            queue<Vertex*> q;
            itr = vertices.begin();
            while(itr.hasNext()){
                Vertex* v = &itr.next();
                if(v->inDegree == 0)
                    q.push(v);
            }

            int i = 0;
            while(!q.empty()){
                //obtain a vertex with no incoming edges
                Vertex* v = q.front(); q.pop();

                //store in container
                container.push_back(v->data);
                ++i;

                for(Edge e : v->outgoingEdges){
                    Vertex* adj = e.end;

                    //since we popped v from the queue,
                    //adj, has one less incoming edge
                    adj->tempInDegree--;

                    //if it has indegree of 0, then that is the next
                    //vertices we can visit
                    if(adj->tempInDegree == 0)
                        q.push(adj);
                }
            }
            //cycle found
            if(i != vertices.size())
                return false;
            return true;
        }


        //retrieve vertex data
        const Vertex* find(const T& target){
            typename AVL<Vertex>::Iterator i = vertices.get(Vertex(target));
            if(i != vertices.end())
                return &i.getData();
            return nullptr;
        }

        void clear(){
            vertices.clear();
        }

    private:
        //container of vertices for the graph
        AVL<Vertex> vertices;
};

#endif
