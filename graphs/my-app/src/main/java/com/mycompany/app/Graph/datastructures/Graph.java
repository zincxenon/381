package com.mycompany.app.Graph.datastructures;

import java.util.*;

/**
 * Created by william on 3/1/16.
 */

public class Graph extends AbstractGraph {

    private boolean directed = true;
    private boolean cycleExists = false;
    List<Vertex> vertices;
    HashMap<Vertex, List<Edge>> vertexEdgeHashMap;

    public Graph() {
        List<Vertex> vertices = new ArrayList<Vertex>();
        HashMap<Vertex, List<Edge>> vertexEdgeHashMap = new HashMap<Vertex, List<Edge>>();
    }

    public Graph(boolean directed, HashMap<Vertex, List<Edge>> vertexEdgeHashMap, List<Vertex> vertices) {
        this.directed = directed;
        this.vertexEdgeHashMap = vertexEdgeHashMap;
        this.vertices = vertices;
    }

    @Override
    public void addVertex(Vertex v) {
        this.vertices.add(v);
        if (!vertexEdgeHashMap.containsKey(v)) {
            vertexEdgeHashMap.put(v, new ArrayList<Edge>());
        }
    }

    @Override
    public void addEdge(Edge e) {
        if (! this.vertices.contains(e.getStart())) {
            this.addVertex(e.getStart());
        }
        if (! this.vertices.contains(e.getEnd())) {
            this.addVertex(e.getEnd());
        }

        if (!vertexEdgeHashMap.containsKey(e.getStart())) {
            vertexEdgeHashMap.put(e.getStart(), new ArrayList<Edge>());
        }
        if (!directed) {
            if (!vertexEdgeHashMap.containsKey(e.getEnd())) {
                vertexEdgeHashMap.put(e.getEnd(), new ArrayList<Edge>());
            }
        }
        setCycleExists();
    }

    @Override
    public void removeVertex(Vertex v) {
        this.vertices.remove(v);
        vertexEdgeHashMap.remove(v);
        Set<Vertex> keys = vertexEdgeHashMap.keySet();
        for (Vertex k : keys) {
            for (Edge e : vertexEdgeHashMap.get(k)) {
                if (e.getEnd().equals(v)) {
                    vertexEdgeHashMap.get(k).remove(e);
                }
            }
        }
    }

    @Override
    public void removeEdge(Edge e) {
        Vertex startVertex = e.getStart();
        Vertex endVertex = e.getEnd();
        vertexEdgeHashMap.get(startVertex).remove(e);
        if (!directed) {
            vertexEdgeHashMap.get(endVertex).remove(e);
        }
    }

    public boolean isCyclic() {
        return this.cycleExists;
    }

    public void setCycleExists() {
        this.cycleExists = false;
        for (Vertex v : vertices) {
            Stack emptyStack = new Stack();
            dfs(this, v, emptyStack);
            if (this.cycleExists) {
                return;
            }
        }
    }

    public void dfs(Graph g, Vertex start, Stack s) {
        s.add(start);
        for (Vertex neighbor : getNeighbors(start)) {
            if (neighbor.isVisited()) {
                this.cycleExists = true;
                return;
            } else {
                start.setVisited(true);
                dfs(g, neighbor, s);
            }
        }
    }

    public ArrayList<Vertex> getNeighbors(Vertex v) {
        ArrayList<Vertex> neighbors = new ArrayList<Vertex>();
        for (Edge e : vertexEdgeHashMap.get(v)) {
            neighbors.add(e.getEnd());
        }
        return neighbors;
    }


}
