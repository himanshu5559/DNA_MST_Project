/*#include <bits/stdc++.h>
#include "dsu.h"
#include "dna_utils.h"
using namespace std;

struct Edge {
    int u, v, w;
};

int main() {
    int n, k, metric;
    cout << "Enter number of DNA sequences: ";
    cin >> n;

    vector<string> dna(n);
    cout << "Enter each DNA sequence:\n";
    for (int i = 0; i < n; i++) cin >> dna[i];

    cout << "Choose distance metric: 1 = Hamming, 2 = Edit Distance\n";
    cin >> metric;

    cout << "Enter number of clusters (k): ";
    cin >> k;

    // Build all edges
    vector<Edge> edges;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int dist = (metric == 1) ? hammingDistance(dna[i], dna[j])
                                     : editDistance(dna[i], dna[j]);
            edges.push_back({i, j, dist});
        }
    }
    sort(edges.begin(), edges.end(), [](auto &a, auto &b) { return a.w < b.w; });

    DSU dsu(n);
    int clusters = n;
    int totalCost = 0;
    vector<Edge> mstEdges;

    for (auto &e : edges) {
        if (clusters == k) break; // stop when k clusters formed
        if (dsu.find(e.u) != dsu.find(e.v)) {
            dsu.unite(e.u, e.v);
            mstEdges.push_back(e);
            totalCost += e.w;
            clusters--;
        }
    }

    cout << "\n--- DNA Evolution Tree (MST/Clusters) ---\n";
    cout << "Clusters formed: " << clusters << "\n";
    cout << "Total Mutation Cost: " << totalCost << "\n";

    for (auto &e : mstEdges) {
        cout << "DNA " << e.u << " <--> DNA " << e.v
             << " (diff = " << e.w << ")\n";
    }

    // Export to JSON for visualization
    ofstream fout("mst.json");
    fout << "{\n  \"nodes\": [\n";
    for (int i = 0; i < n; i++) {
        fout << "    {\"id\": " << i << ", \"label\": \"" << dna[i] << "\"}";
        if (i != n - 1) fout << ",";
        fout << "\n";
    }
    fout << "  ],\n  \"edges\": [\n";
    for (size_t i = 0; i < mstEdges.size(); i++) {
        auto &e = mstEdges[i];
        fout << "    {\"source\": " << e.u << ", \"target\": " << e.v
             << ", \"weight\": " << e.w << "}";
        if (i != mstEdges.size() - 1) fout << ",";
        fout << "\n";
    }
    fout << "  ]\n}";
    fout.close();

    cout << "\nGraph exported to mst.json for visualization.\n";
}
*/
#include <bits/stdc++.h>
#include "dsu.h"
#include "dna_utils.h"
using namespace std;

struct Edge {
    int u, v, w;
};

int main() {
    string fasta_file = "input.fasta";
    vector<string> dna;
    ifstream fin(fasta_file);
    if (!fin) {
        cerr << "Could not open FASTA file: " << fasta_file << endl;
        return 1;
    }

    string line, seq;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        if (line[0] == '>') {
            if (!seq.empty()) {
                dna.push_back(seq);
                seq.clear();
            }
        } else {
            seq += line;
        }
    }
    if (!seq.empty()) dna.push_back(seq); // last sequence

    int n = dna.size();
    cout << "Loaded " << n << " sequences from " << fasta_file << endl;

    int metric, k;
    cout << "Choose distance metric: 1 = Hamming, 2 = Edit Distance\n";
    cin >> metric;
    cout << "Enter number of clusters (k): ";
    cin >> k;

    // Build all edges
    vector<Edge> edges;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int dist = (metric == 1) ? hammingDistance(dna[i], dna[j])
                                     : editDistance(dna[i], dna[j]);
            edges.push_back({i, j, dist});
        }
    }
    sort(edges.begin(), edges.end(), [](auto &a, auto &b) { return a.w < b.w; });

    DSU dsu(n);
    int clusters = n;
    int totalCost = 0;
    vector<Edge> mstEdges;

    for (auto &e : edges) {
        if (clusters == k) break;
        if (dsu.find(e.u) != dsu.find(e.v)) {
            dsu.unite(e.u, e.v);
            mstEdges.push_back(e);
            totalCost += e.w;
            clusters--;
        }
    }

    cout << "\n--- DNA Evolution Tree (MST/Clusters) ---\n";
    cout << "Clusters formed: " << clusters << "\n";
    cout << "Total Mutation Cost: " << totalCost << "\n";

    for (auto &e : mstEdges) {
        cout << "seq" << (e.u+1) << " <--> seq" << (e.v+1)
             << " (diff = " << e.w << ")\n";
    }

    // Export to JSON for visualization
    ofstream fout("mst.json");
    fout << "{\n  \"nodes\": [\n";
    for (int i = 0; i < n; i++) {
        fout << "    {\"id\": \"seq" << (i+1) << "\", \"label\": \"" << dna[i] << "\"}";
        if (i != n - 1) fout << ",";
        fout << "\n";
    }
    fout << "  ],\n  \"edges\": [\n";
    for (size_t i = 0; i < mstEdges.size(); i++) {
        auto &e = mstEdges[i];
        fout << "    {\"source\": \"seq" << (e.u+1) << "\", \"target\": \"seq" << (e.v+1)
             << "\", \"weight\": " << e.w << "}";
        if (i != mstEdges.size() - 1) fout << ",";
        fout << "\n";
    }
    fout << "  ]\n}";
    fout.close();

    cout << "\nGraph exported to mst.json for visualization.\n";
}