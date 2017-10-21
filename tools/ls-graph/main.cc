#include <iostream>
#include <fstream>

#include "tensorflow/core/framework/graph.pb.h"

namespace {

void Usage(char **argv) {
  std::cout << "Usage:\n  " << argv[0] << " <tf_model>\n";
  exit(1);
}

void PrintAttr(const tensorflow::AttrValue& value) {
  switch (value.value_case()) {
    case tensorflow::AttrValue::kS:
      std::cout << "<s>"<< value.s();
      break;

    case tensorflow::AttrValue::kI:
      std::cout << "<i>"<< value.i();
      break;

    case tensorflow::AttrValue::kF:
      std::cout << "<f>"<< value.f();
      break;

    case tensorflow::AttrValue::kB:
      std::cout << "<b> "<< value.b();
      break;

    case tensorflow::AttrValue::kType:
      std::cout << "<type> "<< DataType_Name(value.type());
      break;

    case tensorflow::AttrValue::kShape: {
      std::cout << "<shape> {";
      std::string str = "";
      for (int i = 0; i < value.shape().dim_size(); i++) {
        str += std::to_string(value.shape().dim(i).size()) + ",";
      }
      str = str.substr(0, str.length() - 1);
      std::cout << str << "}";
    } break;

    case tensorflow::AttrValue::kTensor:
      std::cout << "<tensor> ";
      break;

    case tensorflow::AttrValue::kList:
      std::cout << "<list> ";
      break;

    case tensorflow::AttrValue::kFunc:
      std::cout << "<func> ";
      break;

    case tensorflow::AttrValue::kPlaceholder:
      std::cout << "<placeholder> ";
      break;

    case tensorflow::AttrValue::VALUE_NOT_SET:
      std::cout << "<not_set> ";
      break;
  }
}

}

int main(int argc, char **argv) {
  if (argc != 2) {
    Usage(argv);
  }

  std::fstream input(argv[1], std::ios::in | std::ios::binary);

  tensorflow::GraphDef graph_pb;

  if (!input) {
    std::cerr << argv[1] << ": File not found." << std::endl;
    return -1;
  } else if (!graph_pb.ParseFromIstream(&input)) {
    std::cerr << "Failed to load tf model." << std::endl;
    return -1;
  }

  for (int i = 0; i < graph_pb.node_size(); i++) {
    std::cout << "node name: " << graph_pb.node(i).name() << "\n";
    std::cout << "node op: " << graph_pb.node(i).op() << "\n";
    std::cout << "node inputs: ";

    for (int j = 0; j < graph_pb.node(i).input_size(); j++) {
      std::cout << graph_pb.node(i).input(j) << " ";
    }

    std::cout << "\nnode attr:\n";

    for (auto& name: graph_pb.node(i).attr()) {
      std::cout << "  " << name.first << ": ";
      PrintAttr(name.second);
      std::cout << "\n";
    }

    std::cout << "\n\n";
  }
}
