package com.mycompany.app.Graph.algorithms;

import com.mycompany.app.Graph.datastructures.Edge;
import com.mycompany.app.Graph.datastructures.Graph;
import com.mycompany.app.Graph.datastructures.Vertex;

import java.util.*;

/**
 * Created by william on 3/1/16.
 */
public class BFS {

    Queue<Vertex> visitOrder = new PriorityQueue<Vertex>();

    public BFS() {
    }

    public static void bfsPrint(Graph g, Vertex start) {
        Queue<Vertex> q = new PriorityQueue<Vertex>();
        q.add(start);
        while (!q.isEmpty()) {
            Vertex v = q.remove();
            System.out.println("visited vertex " + v);
            ArrayList<Vertex> neighbors = g.getNeighbors(v);
            for (Vertex neigh : neighbors) {
                q.add(neigh);
            }
        }

    }

    public void bfsOrdered(Graph g, Vertex start) {
        this.visitOrder = new PriorityQueue<Vertex>();
        Queue<Vertex> q = new PriorityQueue<Vertex>();
        q.add(start);
        while (!q.isEmpty()) {
            Vertex v = q.remove();
//            System.out.println("visited vertex " + v);
            this.visitOrder.add(v);
            ArrayList<Vertex> neighbors = g.getNeighbors(v);
            for (Vertex neigh : neighbors) {
                q.add(neigh);
            }
        }
    }

    public Queue<Vertex> getVisitOrder() {
        return visitOrder;
    }

    public void setVisitOrder(Queue<Vertex> visitOrder) {
        this.visitOrder = visitOrder;
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
        final Edge<Integer> e1_2 = new Edge<Integer>(v1, v2, 7);
        final Edge<Integer> e1_3 = new Edge<Integer>(v1, v3, 9);

        {
            edges.add(e1_2);
            edges.add(e1_3);
        }
        HashMap ve = new HashMap();
        ve.put(v1, edges);

        final Graph graph = new Graph(false, ve, (List) vertices);
        System.out.println(graph);

        BFS.bfsPrint(graph, v1);

        BFS b = new BFS();

        System.out.println("==============================================");
        System.out.println("starting at v1");
        System.out.println("==============================================");
        b.bfsOrdered(graph, v1);


        System.out.println("==============================================");
        System.out.println("starting at v2");
        System.out.println("==============================================");
        b.bfsOrdered(graph, v2);

        System.out.println("==============================================");
        System.out.println("starting at v3");
        System.out.println("==============================================");
        b.bfsOrdered(graph, v3);

        System.out.println("==============================================");
        System.out.println("starting at v4");
        System.out.println("==============================================");
        b.bfsOrdered(graph, v4);

        System.out.println("==============================================");
        System.out.println("starting at v5");
        System.out.println("==============================================");
        b.bfsOrdered(graph, v5);


    }
}
