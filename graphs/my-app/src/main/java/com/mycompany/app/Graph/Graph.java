package com.mycompany.app.Graph;

/**
 * Created by william on 3/1/16.
 */


import java.util.*;


public class Graph<T> extends AbstractGraph{

    public boolean directed = true;

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Graph<?> graph = (Graph<?>) o;

        if (directed != graph.directed) return false;
        if (vertices != null ? !vertices.equals(graph.vertices) : graph.vertices != null) return false;
        if (vertexEdgeHashMap != null ? !vertexEdgeHashMap.equals(graph.vertexEdgeHashMap) : graph.vertexEdgeHashMap != null)
            return false;
        return !(edges != null ? !edges.equals(graph.edges) : graph.edges != null);

    }

    @Override
    public int hashCode() {
        int result = (directed ? 1 : 0);
        result = 31 * result + (vertices != null ? vertices.hashCode() : 0);
        result = 31 * result + (vertexEdgeHashMap != null ? vertexEdgeHashMap.hashCode() : 0);
        result = 31 * result + (edges != null ? edges.hashCode() : 0);
        return result;
    }

    public boolean isDirected() {
        return directed;
    }

    public void setDirected(boolean directed) {
        this.directed = directed;
    }

    public Graph(boolean directed, List<Edge<T>> edges, HashMap<Vertex<T>, List<Edge<T>>> vertexEdgeHashMap, List<Vertex<T>> vertices) {
        this.directed = directed;
        this.edges = edges;
        this.vertexEdgeHashMap = vertexEdgeHashMap;
        this.vertices = vertices;
    }

    List<Vertex<T>> vertices = new ArrayList<Vertex<T>>();
    HashMap<Vertex<T>, List<Edge<T>>> vertexEdgeHashMap = new HashMap<Vertex<T>, List<Edge<T>>>();
    List<Edge<T>> edges = new ArrayList<Edge<T>>();

    public Graph(List<Edge<T>> edges, List<Vertex<T>> vertices) {
        this.vertexEdgeHashMap = new HashMap<Vertex<T>, List<Edge<T>>>();
        this.edges = edges;
        this.vertices = vertices;
        for (Edge edge : edges) {
            Vertex start = edge.getStart();
            Vertex end = edge.getEnd();
            if (! vertexEdgeHashMap.containsKey(start)) {
                List<Edge<T>> startEdges = new ArrayList<Edge<T>>();
                edges.add(edge);
                vertexEdgeHashMap.put(start, startEdges);
            } else {
                vertexEdgeHashMap.get(start).add(edge);
            }
        }

    }

    public Graph(List<Edge<T>> edges, HashMap<Vertex<T>, List<Edge<T>>> vertexEdgeHashMap, List<Vertex<T>> vertices) {
        this.edges = edges;
        this.vertexEdgeHashMap = vertexEdgeHashMap;
        this.vertices = vertices;
    }

    public List<Edge<T>> getEdges() {
        return edges;
    }

    public void setEdges(List<Edge<T>> edges) {
        this.edges = edges;
    }

    public HashMap<Vertex<T>, List<Edge<T>>> getVertexEdgeHashMap() {
        return vertexEdgeHashMap;
    }

    public void setVertexEdgeHashMap(HashMap<Vertex<T>, List<Edge<T>>> vertexEdgeHashMap) {
        this.vertexEdgeHashMap = vertexEdgeHashMap;
    }

    public List<Vertex<T>> getVertices() {
        return vertices;
    }

    public void setVertices(List<Vertex<T>> vertices) {
        this.vertices = vertices;
    }

    @Override
    public String toString() {
        return "Graph{" +
                "edges=" + edges +
                ", vertices=" + vertices +
                ", vertexEdgeHashMap=" + vertexEdgeHashMap +
                '}';
    }

    @Override
    public void addVertex(Vertex v) {
        this.vertices.add(v);
        if (! vertexEdgeHashMap.containsKey(v)) {
            vertexEdgeHashMap.put(v, new ArrayList<Edge<T>>());
        }
        if (! directed) {
            if (! vertexEdgeHashMap.containsKey(v)) {
                vertexEdgeHashMap.put(v, new ArrayList<Edge<T>>());
            }
        }
    }

    @Override
    public void addEdge(Edge e) {
        this.addVertex(e.getStart());
        this.addVertex(e.getEnd());
        e.getStart().getNeighbors().add(e.getEnd());

        this.edges.add(e);
        if (! vertexEdgeHashMap.containsKey(e.getStart())) {
            vertexEdgeHashMap.put(e.getStart(), new ArrayList<Edge<T>>());
        }
        if (! directed) {
            if (! vertexEdgeHashMap.containsKey(e.getEnd())) {
                vertexEdgeHashMap.put(e.getEnd(), new ArrayList<Edge<T>>());
            }
            e.getEnd().getNeighbors().add(e.getStart());
        }

    }

    @Override
    public void print() {
        for (Vertex t : vertexEdgeHashMap.keySet()) {
            String s = "Vertex " + t.getItem().toString() + ": \n";

            for (Edge e : vertexEdgeHashMap.get(t)) {
                s += e.toString();
                s += "\n";

            }
            System.out.println(s);
        }
    }

}
