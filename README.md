🚀 DNA Mutation Analysis & Evolutionary Clustering

A bioinformatics pipeline for analyzing DNA mutations, computing genetic similarity, and visualizing evolutionary relationships using Minimum Spanning Tree (MST)-based clustering.

📌 Features

📂 FASTA Input – Reads DNA sequences from .fasta files.

🧬 Mutation & Similarity Analysis – Computes Hamming distance and mutation patterns.

🌳 Phylogenetic Tree Construction – Builds MST to represent evolutionary distance.

🎨 Interactive Visualization – Python + NetworkX + Matplotlib animations to show step-by-step cluster formation.

🔬 Real-world Testing – Validated on COVID-19 DNA sequence datasets.

🛠️ Tech Stack

💻 C++ → Core algorithm for mutation distance & MST generation

🐍 Python → Visualization & animation of evolutionary tree

📦 Libraries: networkx, matplotlib, numpy, json

⚡ Usage

1️⃣ Prepare sequences

Add DNA sequences in sequences.fasta.

2️⃣ Run C++ Analysis

g++ analysis.cpp -o analysis ./analysis sequences.fasta > mst.json

3️⃣ Visualize with Python

python visualize.py

✅ An animated evolutionary tree will be displayed.

📊 Example Visualization

👉 (Insert screenshot or GIF here)

🌟 Applications

🔬 Genetic mutation analysis

🦠 Virus evolution tracking (e.g., COVID-19)

🌱 Phylogenetic clustering & bioinformatics research

👨‍💻 Author

Himanshu Saini

📧 himanshu.saini@iitg.ac.in
