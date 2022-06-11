package src;

import java.util.HashMap;

import java.util.ArrayList;

public class Graph<T, S> {

  private HashMap<T, HashMap<T, S>> nodeMap;
  private boolean directed_graph;

  public Graph(boolean direct) {
    this.nodeMap = new HashMap<T, HashMap<T, S>>();
    this.directed_graph = direct;
  }

  public void addNode(T elem) throws Exception {
    if (this.containsNode(elem))
      throw new Exception("Graph addNode: Node already exists");
    else
      this.nodeMap.put(elem, new HashMap<T, S>());
  }

  public void addEdge(T node1, T node2, S label) throws Exception {
    if (this.containsEdge(node1, node2))
      throw new Exception("Graph addEdge: Edge already exists");
    else {
      (this.nodeMap.get(node1)).put(node2, label);
      if (!isDirected())
        this.nodeMap.get(node2).put(node1, label);
    }
  }

  public boolean isDirected() {
    return this.directed_graph;
  }

  public boolean containsNode(T node) {
    if (this.nodeMap.containsKey(node))
      return true;
    return false;
  }

  public boolean containsEdge(T node1, T node2) {
    if (this.containsNode(node1) && this.containsNode(node2)) {
      if (this.nodeMap.get(node1).containsKey(node2))
        return true;
    }
    return false;
  }

  public void removeNode(T node) throws Exception {

    if (!this.containsNode(node))
      throw new Exception("Graph removeNode; Graph doesn't contain the specified node");

    this.nodeMap.remove(node);
    for (HashMap<T, S> adjNodes : this.nodeMap.values()) {
      adjNodes.remove(node);
    }
  }

  public void removeEdge(T node1, T node2) throws Exception {

    if (this.containsNode(node1) && this.containsNode(node2)) {
      if (this.nodeMap.get(node1).containsKey(node2)) {
        this.nodeMap.get(node1).remove(node2);
        if (!isDirected())
          this.nodeMap.get(node2).remove(node1);
      } else
          throw new Exception("Graph removeEdge: Edge does not exist");
    } else
        throw new Exception("Graph removeEdge: Graph does not contains the specified node/s");
  }

  public int getNodesNum() {
    return nodeMap.size();
  }

  public int getEdgesNum() {
    int edges_num = 0;
    for (HashMap<T, S> adjNodes : this.nodeMap.values()) {
      edges_num += adjNodes.size();
    }
    if (isDirected()) {
      return edges_num;
    } else {
      return edges_num / 2;
    }
  }

  public ArrayList<T> getNodes() {
    ArrayList<T> listOfNodes = new ArrayList<>();
    for (T nodesTmp : this.nodeMap.keySet()) {
      listOfNodes.add(nodesTmp);
    }
    return listOfNodes;
  }

  public ArrayList<T> getAdjNodes(T node) throws Exception {
    if (!this.containsNode(node))
      throw new Exception("Graph getAdjNodes: Graph doesn't contain the specified node");
    
      ArrayList<T> adjList = new ArrayList<>();
    for (T nodesTmp : this.nodeMap.get(node).keySet()) {
      adjList.add(nodesTmp);
    }
    return adjList;
  }

  public ArrayList<Edge<T, S>> getEdges() {
    ArrayList<Edge<T, S>> edgeList = new ArrayList<Edge<T, S>>();
    for (T nodeTmp : this.nodeMap.keySet()) {
      for (T edgeTmp : this.nodeMap.get(nodeTmp).keySet()) {
        edgeList.add(new Edge<T, S>(nodeTmp, edgeTmp, this.nodeMap.get(nodeTmp).get(edgeTmp)));
      }
    }
    return edgeList;
  }

  public S getLabel(T node1, T node2) throws Exception {
    if(!this.containsEdge(node1, node2))
      throw new Exception("Graph getLabel: Edge does not exist");
    
    return this.nodeMap.get(node1).get(node2);
  }

  @Override
  public String toString() {
    String res = "";
    for (T vertex : this.getNodes()) {
      try {
        res = res + vertex.toString() + ": " + this.getAdjNodes(vertex).toString() + "\n";
      } catch (Exception e) {
        e.printStackTrace();
      }
    }
    return res;
  }

}