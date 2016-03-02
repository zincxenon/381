package com.mycompany.app.Graph.datastructures;

import java.util.ArrayList;

/**
 * Created by william on 3/1/16.
 */
public class Vertex<T> {
    T item;
    ArrayList<Vertex> neighbors;

    public ArrayList<Vertex> getNeighbors() {
        return neighbors;
    }

    public void setNeighbors(ArrayList<Vertex> neighbors) {
        this.neighbors = neighbors;
    }

    public Vertex(T item, ArrayList<Vertex> neighbors) {

        this.item = item;
        this.neighbors = neighbors;
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

}
