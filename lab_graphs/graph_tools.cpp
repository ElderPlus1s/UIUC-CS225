/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"
// #include <iostream>

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph& graph)
{
    /* Your code here! */
    vector<Vertex> V = graph.getVertices();
    for (int i = 0; i < (int)V.size(); i++) {
        graph.setVertexLabel(V[i], "UNEXPLORED");
    }
    vector<Edge> E = graph.getEdges();
    int min_index = 0;
    for (int i = 0; i < (int)E.size(); i++) {
        graph.setEdgeLabel(E[i].source, E[i].dest, "UNEXPLORED");
        if (E[min_index].weight > E[i].weight) {
            min_index = i;
        }
    }
    graph.setEdgeLabel(E[min_index].source, E[min_index].dest, "MIN");
    queue<Vertex> q;
    Vertex x = graph.getStartingVertex();
    q.push(x);
    graph.setVertexLabel(x, "VISITED");
    while (!q.empty()) {
        x = q.front();
        q.pop();
        vector<Vertex> ad = graph.getAdjacent(x);
        for (int i = 0; i < (int)ad.size(); i++) {
            Vertex v = ad[i];
            if (graph.getVertexLabel(v) == "UNEXPLORED") {
                q.push(v);
                graph.setVertexLabel(v, "VISITED");
                if (graph.getEdgeLabel(x, v) != "MIN") {
                    graph.setEdgeLabel(x, v, "DISCOVERY");
                }
            } else {
                if (graph.getEdgeLabel(x, v) == "UNEXPLORED") {
                    graph.setEdgeLabel(x, v, "CROSS");
                }
            }
        }
    }
    // graph.initSnapshot("MINWEIGHT");
    // graph.snapshot();
    return E[min_index].weight;
}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
    /* Your code here! */
    // using std::cout;
    // using std::endl;
    int MAX = 0x3f3f3f;
    unordered_map<Vertex, int> dist;
    unordered_map<Vertex, Vertex> fath;
    vector<Vertex> V = graph.getVertices();
    for (int i = 0; i < (int)V.size(); i++) {
        dist[V[i]] = MAX;
        graph.setVertexLabel(V[i], "UNEXPLORED");
    }
    dist[start] = 0;
    while (1) {
        Vertex x;
        for (int i = 0; i < (int)V.size(); i++) {
            if (graph.getVertexLabel(V[i]) == "UNEXPLORED") {
                x = V[i];
                break;
            }
        }
        for (int i = 0; i < (int)V.size(); i++) {
            // cout<<dist[V[i]]<<" ";
            if (graph.getVertexLabel(V[i]) == "UNEXPLORED" && dist[V[i]] < dist[x]) {
                x = V[i];
            }
        }
        // cout<<endl;
        // cout<<(int)x<<endl;
        if (x == end || graph.getVertexLabel(x) == "VISITED") {
            break;
        }
        graph.setVertexLabel(x, "VISITED");
        vector<Vertex> adj = graph.getAdjacent(x);
        for (int i = 0; i < (int)adj.size(); i++) {
            Vertex v = adj[i];
            if (graph.getVertexLabel(v) == "UNEXPLORED" && dist[v] > dist[x] + 1) {
                dist[v] = dist[x] + 1;
                fath[v] = x;
            }
        }
    }
    Vertex tmp = end;
    // cout<<"SSS:"<<dist[end]<<endl;
    while (tmp != start) {
        graph.setEdgeLabel(tmp, fath[tmp], "MINPATH");
        tmp = fath[tmp];
    }
    // graph.initSnapshot("MINPATH");
    // graph.snapshot();
    return dist[end];
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
    /* Your code here! */
    using std::sort;
    unordered_map<Vertex, int> vtoi;
    vector<Vertex> V = graph.getVertices();
    for (int i = 0; i < (int)V.size(); i++) {
        vtoi[V[i]] = i;
    }
    vector<Edge> E = graph.getEdges();
    sort(E.begin(), E.end(), cmp);
    DisjointSets dset;
    dset.addelements((int)V.size());
    for (int i = 0; i < (int)E.size(); i++) {
        Vertex a = E[i].source;
        Vertex b = E[i].dest;
        if (dset.find(vtoi[a]) != dset.find(vtoi[b])) {
            dset.setunion(vtoi[a], vtoi[b]);
            graph.setEdgeLabel(a, b, "MST");
        }
    }
    // graph.initSnapshot("MST");
    // graph.snapshot();
}

bool GraphTools::cmp(const Edge &a, const Edge &b) {
    return a.weight < b.weight;
}