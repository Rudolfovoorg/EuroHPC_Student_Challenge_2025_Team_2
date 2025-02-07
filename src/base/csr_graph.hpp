#ifndef CSR_GRAPH_HPP
#define CSR_GRAPH_HPP

#include "graph.hpp"
#include "dimacs.hpp"

#include <memory>

/*
    TODO: otherwise could be possible to impose a rewriting of the vertices when the topology changes
        - like RemoveVertex(int w, bool reorder=false);
    TODO: write docs
*/

class CSRGraph : public Graph {
    public:
        static CSRGraph* LoadFromDimacs(const std::string& file_name);

        CSRGraph()=default;
        CSRGraph(const CSRGraph& other)=default;

        // -------------------- MODIFIERS --------------------
        virtual void AddEdge(int v, int w) override;
        virtual void RemoveEdge(int v, int w) override;

        virtual int AddVertex() override;
        virtual void RemoveVertex(int v) override;
        virtual void SetVertices(std::vector<int>& vertices);

        virtual void MergeVertices(int v, int w) override;
        
        virtual void SetColoring(const std::vector<unsigned short>& colors) override;
        virtual void SetColoring(int vertex, unsigned short color) override;
        virtual void ClearColoring() override;

        // -------------------- ORDERING ----------------------
        virtual void OrderByDegree(bool ascending=true) override;
        virtual void OrderByExdegree(bool ascending=true) override;
        virtual void OrderByColor(bool ascending=true) override;

        // --------------------- GETTERS ----------------------
        virtual void GetNeighbours(int vertex, std::vector<int> &result) const override;
        virtual void GetNeighbours(int vertex, std::set<int> &result) const override;

        virtual bool HasEdge(int v, int w) const override;

        virtual void GetUnorderedVertices(std::set<int> &result) const override;
        virtual const std::vector<int>& GetVertices() const override;
        virtual int GetVertexByIndex(int index) const override;
        virtual const std::set<int>& GetDeletedVertices() const override;

        virtual size_t GetNumVertices() const override;
        virtual size_t GetNumEdges() const override;

        virtual unsigned int GetDegree(int vertex) const override;
        virtual const std::vector<int>& GetDegrees() const override;
        virtual void GetDegrees(std::vector<int>& result) const override;
        virtual unsigned int GetMaxDegree() const override;
        virtual int GetVertexWithMaxDegree() const override;

        virtual std::vector<int> GetMergedVertices(int vertex) const override;
        virtual std::vector<unsigned short> GetColoring() const override ;
        virtual unsigned short GetColor(int vertex) const override;

        virtual std::unique_ptr<Graph> Clone() const override;

        virtual ~CSRGraph() = default;

    private:
        CSRGraph(const Dimacs& dimacs_graph);
        void _ComputeCacheDegrees() const;

        /**
         * @brief number of edges in the graph
         * @details needed since _edges contains duplicated vertices (but it is not true
         *          that _nEdges = 1/2 * num_elements_of(_edges) since loops are not 
         *          duplicated)
         */
        size_t _nEdges;
        /**
         * @brief vertices of the graph, in the particular order required
         */
        std::vector<int> _vertices;        
        /**
         * @brief vertex with the highest value which was ever added to this graph
         */
        mutable int _max_vertex;
        /**
         * @brief vertices removed throughout the living of this graph
         */
        std::set<int> _removed_vertices;
        /**
         * @brief edges contained in this graph. 
         *        _edges[v] contains w iff _edges[w] contains v
         */
        std::vector<std::vector<int>> _edges;
        /**
         * @brief degrees of the graph
         * @todo finish this, it shouldn't be invalidated but accordingly updated
         */
        mutable std::vector<int> _degrees;

        int              _index_of_max_degree;

        /**
         * @brief coloring assigned to the graph
         */
        std::vector<unsigned short> _coloring;
        /**
         * @brief _merged_vertices[v] contains w iff w graph.MergeVertices(v,w) was called
         *        previously
         */
        std::vector<std::vector<int>> _merged_vertices;

};

#endif // CSR_GRAPH_HPP