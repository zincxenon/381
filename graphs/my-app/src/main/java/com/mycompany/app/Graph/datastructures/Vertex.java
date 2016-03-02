package com.mycompany.app.Graph.datastructures;

import java.util.ArrayList;

/**
 * Created by william on 3/1/16.
 */
public class Vertex<T> {
    boolean visited = false;

    public boolean isVisited() {
        return visited;
    }

    public void setVisited(boolean visited) {
        this.visited = visited;
    }

    T item;
//
//    public ArrayList<Vertex> getNeighbors() {
//        return neighbors;
//    }
//
//    public void setNeighbors(ArrayList<Vertex> neighbors) {
//        this.neighbors = neighbors;
//    }
//
//    public void addNeighbor(Vertex v) {
//        this.neighbors.add(v);
//    }
//
//    public void removeNeighbor(Vertex v) {
//        this.neighbors.remove(v);
//    }

    public Vertex(T item, ArrayList<Vertex> neighbors) {

        this.item = item;
//        this.neighbors = neighbors;
    }

    public Vertex (T item) {
        this.item = item;
    }


    public T getItem() {
        return item;
    }

    public void setItem(T item) {
        this.item = item;
    }

    @Override
    public String toString() {
//
//        String s = "[";
//        for (Vertex v : getNeighbors()) {
//            s += v.getItem() + ", ";
//        }
//        s += "]";
        return "Vertex{" +
                "item=" + item +
//                ", " + s +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Vertex<?> vertex = (Vertex<?>) o;

        if (visited != vertex.visited) return false;
        return !(item != null ? !item.equals(vertex.item) : vertex.item != null);

    }

    @Override
    public int hashCode() {
        int result = (visited ? 1 : 0);
        result = 31 * result + (item != null ? item.hashCode() : 0);
        return result;
    }
}
