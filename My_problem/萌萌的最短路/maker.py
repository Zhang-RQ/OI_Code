from cyaron import *
io=IO(file_prefix="in",disable_output=True)
n=1000000
m=2000000
graph = Graph.graph(n, m, self_loop=False,repeated_edges=False,directed=True, weight_limit=(1,200))
io.input_writeln(n,m,1)
io.input_writeln(graph)
