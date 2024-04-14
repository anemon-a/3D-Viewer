#ifndef MODEL_PARSER_H
#define MODEL_PARSER_H

#include <cmath>
#include <fstream>
#include <stack>
#include <string>
#include <vector>

namespace s21 {

enum class Type { None, Vertex, Facet };

class Parser {
 public:
  Parser() : count_of_vertexes_(0), count_of_facets_(0), count_of_edges_(0){};
  ~Parser(){};
  std::vector<int> GetFacets() { return facets_; };
  std::vector<double> GetVertexes() { return vertexes_; };
  const std::vector<double>& GetVertexesReference() { return vertexes_; };
  int GetCountOfVertexes() { return count_of_vertexes_; }
  int GetCountOfFacets() { return count_of_facets_; }
  int GetCountOfEdges() { return count_of_edges_; }
  void ParseFile(const std::string filename);

 private:
  int CountF(std::string str);
  int CountVAndF(std::string filename);
  void FillMatrixPolygons(std::string filename);
  void FillVertexes(std::string& str, int* count_of_v);
  void FillFacets(std::string& str, int* count_of_f);
  Type IsVertexOrFacet(std::string& str);

  std::vector<int> facets_;
  std::vector<double> vertexes_;
  int count_of_vertexes_;
  int count_of_facets_;
  int count_of_edges_;
};

}  // namespace s21

#endif  // MODEL_PARSER_H
