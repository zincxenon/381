package com.mycompany.app.Graph.datastructures;

import java.util.Comparator;

/**
 * Created by william on 3/2/16.
 */
public class EdgeComparator implements Comparator<Edge> {
    public int compare(Edge o1, Edge o2) {
        if (o1.getLength() < o2.getLength()) {
            return -1;
        } else if (o1.getLength() > o2.getLength()) {
            return 1;

        } else {
            return 0;
        }

    }
}
