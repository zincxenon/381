package com.mycompany.app.Graph.datastructures;

/**
 * Created by william on 3/1/16.
 */
public class CoordinateEdge extends Edge<Coordinate>  implements Comparable<Edge> {

    double length;

    public CoordinateEdge(Vertex<Coordinate> start, Vertex<Coordinate> end, double length) {
        super(start, end, length);
    }

    public double length() {
        return Math.sqrt(Math.pow(((Coordinate)getStart().getItem()).getX() - ((Coordinate)getEnd().getItem()).getX(), 2) + Math.pow(((Coordinate) getStart().getItem()).getY() - ((Coordinate) getEnd().getItem()).getY(), 2));
    }

    public int compareTo(Edge o) {
        return this.length() > ((CoordinateEdge) o).length() ? 1 : 0;
    }
}
