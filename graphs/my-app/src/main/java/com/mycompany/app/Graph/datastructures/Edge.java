package com.mycompany.app.Graph.datastructures;

/**
 * Created by william on 3/1/16.
 */
public class Edge<T> {

    Vertex<T> start;
    Vertex<T> end;
    double length;

    public Edge(Vertex<T> start, Vertex<T> end, double length) {
        this.start = start;
        this.end = end;
        this.length = length;
    }

    public Vertex<T> getEnd() {
        return end;
    }

    public void setEnd(Vertex<T> end) {
        this.end = end;
    }

    public double getLength() {
        return length;
    }

    public void setLength(double length) {
        this.length = length;
    }

    public Vertex<T> getStart() {
        return start;
    }

    public void setStart(Vertex<T> start) {
        this.start = start;
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
        int result;
        long temp;
        result = start != null ? start.hashCode() : 0;
        result = 31 * result + (end != null ? end.hashCode() : 0);
        temp = Double.doubleToLongBits(length);
        result = 31 * result + (int) (temp ^ (temp >>> 32));
        return result;
    }
}
