#ifndef H_ADJACENCY_LIST
#define H_ADJACENCY_LIST

#include "graph_interface"
#include <vector>

namespace curran {

template <typename VKey, typename VVal, typename EKey, typename EVal>
struct Vertex {
    VKey key;
    std::optional<VVal> val;
    std::vector<Edge<EKey, EVal>> neighbours;
}

template <typename VKey, typename VVal, typename EKey, typename EVal>
class AdjacencyList : public GraphInterface {
private:
    // store the vertices in a map
};

} // namespace curran

#endif // H_ADJACENCY_LIST
