package graph;

/**
 * 
 * It represents the edge between two nodes.
 * @param <T> : type of the nodes 
 * @param <S> : type of the edge's weight
 */
public class Edge<T, S> {

  private T node1;
  private T node2;
  private S label;

  public Edge(T node1, T node2, S lab){
    this.node1 = node1;
    this.node2 = node2;
    this.label = lab;
  }

  public T getNode1(){
    return node1;
  }

  public T getNode2(){
    return node2;
  }

  public S getLabel(){
    return label;
  }

  public String toString(){
    return "node 1 = " + this.node1 + ", node 2 = " + this.node2 + ", label = " + this.label;
  }

  @Override 
  public boolean equals(Object obj) {
    if (obj == null) {
      return false;
    }
    if (!(obj instanceof Edge)) {
      return false;
    }
    if (this == obj) {
      return true;
    }
    @SuppressWarnings({"unchecked"})
    Edge<T,S> tmp = (Edge<T,S>)obj;
    if(this.node1.equals(tmp.getNode1()) && this.node2.equals(tmp.getNode2()) && this.label.equals(tmp.getLabel()))
      return true;
    else 
      return false;
  }

}