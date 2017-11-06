from cyaron import *

io = IO(file_prefix="in")

g=Graph.hack_spfa(1500,weight_limit=(1, 20),self_loop=False, repeated_edges=False)

io.input_writeln(g)
