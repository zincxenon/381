package com.mycompany.app.Graph.datastructures;

import junit.framework.Assert;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;

/**
 * Created by william on 3/1/16.
 */
public class GraphTest {

    final Vertex<Integer> p1 = new Vertex<Integer>(10);
    final Vertex<Integer> p2 = new Vertex<Integer>(11);
    final Vertex<Integer> p3 = new Vertex<Integer>(21);
    final Vertex<Integer> p4 = new Vertex<Integer>(22);
    final Vertex<Integer> p5 = new Vertex<Integer>(13);
    final Vertex<Integer> p6 = new Vertex<Integer>(10);
    final Vertex<Integer> p7 = new Vertex<Integer>(10);

    @Before
    public void setUp() throws Exception {

    }

    @Test
    public void testVertexEquality() {
        Assert.assertFalse(p1.equals(p2));
        Assert.assertFalse(p2.equals(p1));
        Assert.assertFalse(p1.equals(p3));
        Assert.assertFalse(p3.equals(p1));
        Assert.assertFalse(p1.equals(p4));
        Assert.assertFalse(p4.equals(p1));

        Assert.assertTrue(p1.equals(p7) && p1.hashCode()==p7.hashCode());
        Assert.assertFalse(p5.equals(p1) && p5.hashCode()==p6.hashCode());
    }



    @Test
    public void testEdgeEquality() {
        final Edge<Integer> e1 = new Edge<Integer>(p1, p2, 1);
        final Edge<Integer> e2 = new Edge<Integer>(p2, p1, 1);
        final Edge<Integer> e3 = new Edge<Integer>(p1, p2, 2);
        final Edge<Integer> e4 = new Edge<Integer>(p1, p3, 1);
        final Edge<Integer> e5 = new Edge<Integer>(p4, p2, 1);

        Assert.assertFalse(e1.equals(e2));
        Assert.assertFalse(e2.equals(e1));
        Assert.assertFalse(e1.equals(e3));
        Assert.assertFalse(e3.equals(e1));
        Assert.assertFalse(e1.equals(e3));
        Assert.assertFalse(e3.equals(e1));
        Assert.assertFalse(e1.equals(e4));
        Assert.assertFalse(e4.equals(e1));
    }

    @Test
    public void testBasic() throws Exception {

    }


    @Test
    public void testEdges() throws Exception {

    }

    @Test
    public void testAddVertices() throws Exception {

    }

    @Test
    public void testAddEdges() throws Exception {

    }

    @Test
    public void testVertexEdgeHashMap() throws Exception {

    }


    @After
    public void tearDown() throws Exception {


    }
}
