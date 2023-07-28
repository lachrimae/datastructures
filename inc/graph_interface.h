#ifndef H_GRAPH_INTERFACE
#define H_GRAPH_INTERFACE

#include <optional>
#include <vector>

namespace curran {

template <typename VKey, typename VVal, typename EKey, typename EVal>
class GraphInterface {
public:
    Graph() {}
    virtual ~Interface() {}
    virtual bool adjacent(VKey x, VKey y) = 0;
    virtual std::vector<VKey> neighbours(VKey x) = 0;
    virtual void add_vertex(VKey x) = 0;
    virtual void remove_vertex(VKey x) = 0;
    virtual void add_edge(VKey x, VKey y, EKey e) = 0;
    virtual void remove_edge(VKey x, VKey y) = 0;
    virtual std::optional<VVal> get_vertex_value(VKey key) = 0;
    virtual void set_vertex_value(VKey key, VVal val) = 0;
    virtual std::optional<EVal> get_edge_value(EKey key) = 0;
    virtual void set_edge_value(EKey key, EVal val) = 0;
};

} // namespace curran

#endif // H_GRAPH_INTERFACE
