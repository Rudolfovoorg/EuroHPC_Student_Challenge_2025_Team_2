
#include "branch_n_bound_seq.hpp"
#include "dimacs.hpp"
#include "csr_graph.hpp"
#include "branching_strategy.hpp"
#include "clique_strategy.hpp"
#include "color.hpp"

#include "test_common.hpp"

#include <iostream>

int main() {

    Dimacs dimacs;
    std::string file_name = "10_vertices_graph.col";

    if ( !dimacs.load(file_name.c_str()) ) {
        std::cout << dimacs.getError() << std::endl;
    }

    CSRGraph* graph = CSRGraph::LoadFromDimacs(file_name);

    RandomBranchingStrategy branching_strategy(graph->GetNumVertices());
    StubCliqueStrategy clique_strategy;
    GreedyColorStrategy color_strategy;

    BranchNBoundSeq solver(branching_strategy, clique_strategy, color_strategy, "log.txt");

    int chromatic_number = solver.Solve(*graph, 10, 500);

    std::cout << "Chromatic number: " << chromatic_number << std::endl;

    return 0;
}
