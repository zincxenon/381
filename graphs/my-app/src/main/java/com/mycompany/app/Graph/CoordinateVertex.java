package com.mycompany.app.Graph;

/**
 * Created by william on 3/1/16.
 */
public class CoordinateVertex extends Vertex<Coordinate> {


    public CoordinateVertex(Coordinate item) {
        super(item);
    }

    public int getX() {
        return item.getX();
    }
    public int getY() {
        return item.getY();
    }

}
