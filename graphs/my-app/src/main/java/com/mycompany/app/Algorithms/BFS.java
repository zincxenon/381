package com.mycompany.app.Algorithms;

import java.util.ArrayList;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Queue;
import com.mycompany.app.Graph.*;
/**
 * Created by william on 3/1/16.
 */
public class BFS {

    public void bfs(Graph g, Vertex start) {
        Queue<Vertex> q = new PriorityQueue<Vertex>();
        q.add(start);
        while (!q.isEmpty()) {
            Vertex v = q.remove();
            System.out.println("visited vertex " + v);
            ArrayList<Vertex> neighbors = v.getNeighbors();
            for (Vertex neigh : neighbors) {
                q.add(neigh);
            }
        }

    }

    public static void main(String[] args) {
        final List<Vertex<Integer>> vertices = new ArrayList<Vertex<Integer>>();
        final Vertex<Integer> v1 = new Vertex<Integer>(1);
        final Vertex<Integer> v2 = new Vertex<Integer>(2);
        final Vertex<Integer> v3 = new Vertex<Integer>(3);
        final Vertex<Integer> v4 = new Vertex<Integer>(4);
        final Vertex<Integer> v5 = new Vertex<Integer>(5);
        final Vertex<Integer> v6 = new Vertex<Integer>(6);
        final Vertex<Integer> v7 = new Vertex<Integer>(7);
        final Vertex<Integer> v8 = new Vertex<Integer>(8);
        {
            vertices.add(v1);
            vertices.add(v2);
            vertices.add(v3);
            vertices.add(v4);
            vertices.add(v5);
            vertices.add(v6);
            vertices.add(v7);
            vertices.add(v8);
        }

        final List<Edge<Integer>> edges = new ArrayList<Edge<Integer>>();
        final Edge<Integer> e1_2 = new Edge<Integer>(7, v1, v2);
        final Edge<Integer> e1_3 = new Edge<Integer>(9, v1, v3);
        final Edge<Integer> e1_6 = new Edge<Integer>(14, v1, v6);
        final Edge<Integer> e2_3 = new Edge<Integer>(10, v2, v3);
        final Edge<Integer> e2_4 = new Edge<Integer>(15, v2, v4);
        final Edge<Integer> e3_4 = new Edge<Integer>(11, v3, v4);
        final Edge<Integer> e3_6 = new Edge<Integer>(2, v3, v6);
        final Edge<Integer> e5_6 = new Edge<Integer>(9, v5, v6);
        final Edge<Integer> e4_5 = new Edge<Integer>(6, v4, v5);
        final Edge<Integer> e1_7 = new Edge<Integer>(1, v1, v7);
        final Edge<Integer> e1_8 = new Edge<Integer>(1, v1, v8);
        {
            edges.add(e1_2);
            edges.add(e1_3);
            edges.add(e1_6);
            edges.add(e2_3);
            edges.add(e2_4);
            edges.add(e3_4);
            edges.add(e3_6);
            edges.add(e5_6);
            edges.add(e4_5);
            edges.add(e1_7);
            edges.add(e1_8);
        }

        final Graph<Integer> graph = new Graph<Integer>(edges, vertices);

    }
}