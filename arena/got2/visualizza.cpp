#include <fstream>
#include <iostream>
#include <unordered_set>

using namespace std;

const string BG_COLOR = "FFFFFF";

const string DOT_GRAPH =
    ("graph G {\n"
     "    size = 26\n"
     "    ratio = expand\n"
     "    overlap = ipsep\n"
     "    bgcolor = \"#" +
     BG_COLOR +
     "\"\n"
     "    outputorder=\"edgesfirst\"\n"
     "    edge [colorscheme = set312]\n"
     "    node [shape = point, margin = 0, width = 0.1]\n\n");
const string TAB = "    ";

int main(int argc, char **argv) {
  if (argc < 2) {
    cerr << "Usage: ./visualizza <input_file>" << endl;
    exit(EXIT_FAILURE);
  }
  ifstream in(argv[1]);
  if (!in.is_open()) {
    cerr << "Input file not found" << endl;
    exit(EXIT_FAILURE);
  }
  int N, M;
  in >> N >> M;
  cout << DOT_GRAPH;
  for (int e = 0; e < M; e++) {
    int u, v;
    in >> u >> v;
    cout << TAB << u << " -- " << v << "\n";
  }
  cout << "\n}\n";

  return 0;
}
