package com.mycompany.app.Graph;

/**
 * Created by william on 3/1/16.
 */
public class Coordinate {
    public int getX() {
        return x;
    }

    public void setX(int x) {
        this.x = x;
    }

    public int getY() {
        return y;
    }

    public void setY(int y) {
        this.y = y;
    }

    int x, y;

    public Coordinate(int x, int y) {
        this.x = x;
        this.y = y;
    }
}
