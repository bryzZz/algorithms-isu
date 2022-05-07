import random
import matplotlib.pyplot as plt
import networkx as nx
from networkx.drawing.nx_pydot import graphviz_layout

class Node:
    node_id = 0

    def __init__(self):
        self._id = Node.node_id
        self.left = None
        self.right = None

        Node.node_id += 1
    
    def __str__(self) -> str:
        return f"Node {self._id}"

def gen_binary_tree(max_level = 3):
    level = 0
    root = Node()
    _gen_tree(root, level, max_level)
    return root

def _gen_tree(root: Node, level, max_level):
    level += 1
    if level >= max_level:
        return
    if random.random() > 0.25:
        root.left = Node()
        _gen_tree(root.left, level, max_level)
    if random.random() > 0.25:
        root.right = Node()
        _gen_tree(root.right, level, max_level)

def count_nodes(node: Node):
    if node is None:
        return 0
    return 1 + count_nodes(node.left) + count_nodes(node.right)

def preorder(node: Node):
    if node is not None:
        print(node, end=" ")
        preorder(node.left)
        preorder(node.right)

root = gen_binary_tree(3)

preorder(root)

# tree = nx.Graph()
# tree.add_nodes_from(nodes)
# tree.add_edges_from(edges)

# plt.figure(figsize = (10, 10))
# pos = graphviz_layout(tree, prog="dot")
# nx.draw(tree, pos, with_labels = True, font_size = 22)
# plt.show()

