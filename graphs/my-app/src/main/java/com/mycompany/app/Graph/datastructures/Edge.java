package com.mycompany.app.Graph.datastructures;

/**
 * Created by william on 3/1/16.
 */
public class Edge<T> {
    Vertex<T> start, end;

    public Edge(double length, Vertex<T> end, Vertex<T> start) {
        this.end = end;
        this.length = length;
        this.start = start;
    }

    public void setLength(double length) {

        this.length = length;
    }

    double length;

    public double getLength() {
        return length;
    }

    public Edge(Vertex<T> start, Vertex<T> end) {
        this.start = start;
        this.end = end;

    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Edge<?> edge = (Edge<?>) o;

        if (Double.compare(edge.length, length) != 0) return false;
        if (start != null ? !start.equals(edge.start) : edge.start != null) return false;
        return !(end != null ? !end.equals(edge.end) : edge.end != null);

    }

    @Override
    public int hashCode() {
        int result = start != null ? start.hashCode() : 0;
        result = 31 * result + (end != null ? end.hashCode() : 0);
        return result;
    }

    public Vertex<T> getEnd() {

        return end;
    }

    public void setEnd(Vertex<T> end) {
        this.end = end;
    }

    public Vertex<T> getStart() {
        return start;
    }

    @Override
    public String toString() {
        return "Edge{" +
                "end=" + end.getItem() +
                ", start=" + start.getItem() +
                '}';
    }

    public void setStart(Vertex<T> start) {
        this.start = start;
    }
}
