package com.mycompany.app.Graph.algorithms;

import com.mycompany.app.Graph.datastructures.Graph;
import com.mycompany.app.Graph.datastructures.Vertex;

import java.util.ArrayList;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.Stack;

/**
 * Created by william on 3/1/16.
 */
public class DFS {

    public void dfs(Graph g, Vertex start, Stack s) {
        s.add(start);
        for (Vertex neighbor : (ArrayList<Vertex>) start.getNeighbors()) {
            if (!neighbor.isVisited()) {
                start.setVisited(true);
                dfs(g, neighbor, s);
            }
        }
        s.pop();
    }

}
