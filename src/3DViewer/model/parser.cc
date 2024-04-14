#include "../model/parser.h"

void s21::Parser::ParseFile(const std::string filename) {
  vertexes_.clear();
  facets_.clear();
  count_of_facets_ = 0;
  count_of_vertexes_ = 0;
  count_of_edges_ = 0;
  CountVAndF(filename);
  FillMatrixPolygons(filename);
}

int s21::Parser::CountVAndF(std::string filename) {
  std::ifstream file(filename);
  std::string line;

  if (file.is_open()) {
    while (std::getline(file, line)) {
      Type type = IsVertexOrFacet(line);
      if (type == Type::Vertex)
        count_of_vertexes_++;
      else if (type == Type::Facet) {
        count_of_facets_++;
        int n = 1;
        while (n <= static_cast<int>(line.length())) {
          if (isdigit(line[n])) {
            count_of_edges_++;
            while (isdigit(line[n]) || line[n] == '/') {
              n++;
            }
          }
          n++;
        }
      }
    }
    file.close();
  } else {
    throw std::runtime_error("Unable to open file!");
  }
  facets_.resize(count_of_edges_ * 2);
  return 0;
}

void s21::Parser::FillMatrixPolygons(std::string filename) {
  std::ifstream file(filename);
  std::string line;
  int count_of_v = 0;
  int count_of_f = 0;
  while (std::getline(file, line)) {
    Type type = IsVertexOrFacet(line);
    if (type == Type::Vertex) {
      FillVertexes(line, &count_of_v);
    } else if (type == Type::Facet) {
      FillFacets(line, &count_of_f);
    }
  }
}

void s21::Parser::FillVertexes(std::string& str, int* count_of_v) {
  double x = 0.0, y = 0.0, z = 0.0;
  sscanf(str.c_str(), "v %lf %lf %lf", &x, &y, &z);
  vertexes_.push_back(x);
  vertexes_.push_back(y);
  vertexes_.push_back(z);
  *count_of_v += 3;
}

void s21::Parser::FillFacets(std::string& str, int* count_of_f) {
  int count = 1;
  int temp = 0;
  int flag = 0;
  for (int i = 0; i < static_cast<int>(str.length()); i++) {
    if (isdigit(str[i])) {
      (*count_of_f)++;
      if (count == 1) {
        sscanf(&str[i], "%d", &temp);
        temp--;
      } else {
        int temp2 = 0;
        sscanf(&str[i], "%d", &temp2);
        temp2--;
        facets_[(*count_of_f) - 1] = temp2;
        (*count_of_f)++;
        facets_[(*count_of_f) - 1] = temp2;
        if (count == CountF(str)) {
          (*count_of_f)++;
          flag = 1;
        }
      }
      while (isdigit(str[i]) || str[i] == '/') {
        i++;
      }
      if ((count == 1) || (flag == 1)) {
        facets_[(*count_of_f) - 1] = temp;
      }
      count++;
    }
  }
}

s21::Type s21::Parser::IsVertexOrFacet(std::string& str) {
  if ((str[0] == 'v') && (str[1] == ' '))
    return Type::Vertex;
  else if ((str[0] == 'f') && (str[1] == ' '))
    return Type::Facet;
  return Type::None;
}

int s21::Parser::CountF(std::string str) {
  int n = 1;
  int count_f = 0;
  while (n <= static_cast<int>(str.length())) {
    if (isdigit(str[n])) {
      count_f++;
      while (isdigit(str[n]) || str[n] == '/') {
        n++;
      }
    }
    n++;
  }
  return count_f;
}
