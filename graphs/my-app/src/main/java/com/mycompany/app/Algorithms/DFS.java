package com.mycompany.app.Algorithms;

import com.mycompany.app.Graph.Graph;
import com.mycompany.app.Graph.Vertex;

import java.util.ArrayList;
import java.util.PriorityQueue;
import java.util.Queue;

/**
 * Created by william on 3/1/16.
 */
public class DFS {

    public void dfs(Graph g, Vertex start) {
        Queue<Vertex> q = new PriorityQueue<Vertex>();
        q.add(start);
        while (!q.isEmpty()) {
            Vertex v = q.remove();
            System.out.println("visited vertex " + v);
            ArrayList<Vertex> neighbors = v.getNeighbors();
            for (Vertex neigh : neighbors) {
                q.add(neigh);
            }
//            for (Vertex neighbor : v.getNeighbors()) {
//                q.add(neighbor);
//
//            }
        }

    }

}
