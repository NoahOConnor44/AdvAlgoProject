class GraphNode
  attr_accessor :name, :neighbors

  def initialize(name)
    @name = name
    @neighbors = []
  end

  def add_edge(node, weight)
    @neighbors << [node, weight]
  end
end

class Graph
  attr_accessor :nodes

  def initialize
    @nodes = []
  end

  def find_node_by_name(name)
    @nodes.select{ |node| node.name == name }.first
  end

  def find_or_add_node(node_name)
    if @nodes.select{ |node| node.name == node_name }.count == 0
      new_node = GraphNode.new(node_name)
      @nodes << new_node
      return new_node
    else
      return @nodes.select{ |node| node.name == node_name }.first
    end
  end

end

graph = Graph.new

begin
lines = File.readlines(ARGV[0])
rescue Errno::ENOENT => e
  p e
  return
end

total_nodes = lines[0]

lines[1..-1].each do |line|
  node_1, node_2, weight = line.split(' ')
  graph_node1 = graph.find_or_add_node(node_1) if node_1
  graph_node2 = graph.find_or_add_node(node_2) if node_2

  if graph_node1 && graph_node2
    graph_node1.add_edge(graph_node2, weight.to_f)
    graph_node2.add_edge(graph_node1, weight.to_f)
  end
end

edges = []
set_of_edges = graph.nodes.each do |node|
  node.neighbors.each do |n|
    edges << [node, n[1], n[0]]
  end
end

sorted_edges = edges.uniq.sort_by{ |e| e[1] }.reverse

@acycic_graphs = []
def dfs(visited_set, current_node)
  current_node.neighbors.each do |n|
    if current_node.name != n[0].name && not(visited_set.include?(n[0].name))
      visited_set << n[0].name
      dfs(visited_set, n[0])
      @acycic_graphs << visited_set.dup
      visited_set.delete_if { |el| el == n[0].name }
    else
      visited_set
    end
  end
end

sorted_edges.each do |edge|
  dfs([], edge[0])
end

path_weights = {}
@acycic_graphs.uniq.each do |path|
  weight = 0
  curr = graph.find_node_by_name(path[0])
  path[1..-1].each do |node_name|
    weight = weight + curr.neighbors.select{|el| el[0].name == node_name}.first[1]
    curr = curr.neighbors.select{|el| el[0].name == node_name}.first[0]
  end
  path_weights[path] = weight
end

p path_weights.sort_by{ |k,v| v }.reverse.first
