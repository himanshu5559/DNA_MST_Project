import json
import networkx as nx
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np
import random

# Load MST from JSON file
with open("mst.json", "r") as f:
    mst_data = json.load(f)

nodes = [n["id"] for n in mst_data["nodes"]]
labels = {n["id"]: n["id"] for n in mst_data["nodes"]}
edges = [(e["source"], e["target"], e["weight"]) for e in mst_data["edges"]]
k = mst_data.get("k", 1)

# Create graph
G = nx.Graph()
G.add_nodes_from(nodes)

# Layout for visualization (force-directed)
pos = nx.spring_layout(G, seed=42, k=1.5)

# Color palette for clusters
color_palette = [
    "#00b4d8", "#ff6b6b", "#ffd166", "#06d6a0",
    "#8338ec", "#ff9f1c", "#118ab2", "#ef476f"
]

# Setup figure
fig, ax = plt.subplots(figsize=(9, 7))
fig.patch.set_facecolor("#0d1b2a")
ax.set_facecolor("#0d1b2a")
ax.axis("off")

# Draw initial nodes (skyblue)
node_colors = ["#90e0ef" for _ in nodes]
nx.draw_networkx_nodes(G, pos, node_color=node_colors, node_size=900, edgecolors="white", linewidths=2, ax=ax)
nx.draw_networkx_labels(G, pos, labels, font_size=12, font_weight="bold", font_color="white", ax=ax)

# For animation
edge_list = []
texts = []

def update(frame):
    ax.clear()
    ax.set_facecolor("#0d1b2a")
    ax.axis("off")

    # Add nodes
    nx.draw_networkx_nodes(G, pos, node_color=node_colors, node_size=900, edgecolors="white", linewidths=2, ax=ax)
    nx.draw_networkx_labels(G, pos, labels, font_size=12, font_weight="bold", font_color="white", ax=ax)

    if frame < len(edges):
        u, v, w = edges[frame]
        G.add_edge(u, v, weight=w)
        edge_list.append((u, v, w))

    # Detect connected components for coloring
    components = list(nx.connected_components(G))
    if len(components) <= k:
        # Color clusters when k clusters formed
        cluster_map = {}
        for idx, comp in enumerate(components):
            for node in comp:
                cluster_map[node] = color_palette[idx % len(color_palette)]
        node_colors[:] = [cluster_map[n] for n in nodes]

    # Draw all edges added so far
    if edge_list:
        nx.draw_networkx_edges(G, pos, edgelist=[(u, v) for u, v, _ in edge_list],
                               width=3, edge_color="#ff9f1c", style="solid", ax=ax)
        nx.draw_networkx_edge_labels(G, pos,
                                     edge_labels={(u, v): w for u, v, w in edge_list},
                                     font_color="white", ax=ax)

    # Title text
    ax.set_title(f"DNA Evolution Tree Animation\nStep {frame+1}/{len(edges)}",
                 fontsize=14, color="white", pad=20, weight="bold")

ani = animation.FuncAnimation(fig, update, frames=len(edges), interval=2000, repeat=False)
plt.show()
