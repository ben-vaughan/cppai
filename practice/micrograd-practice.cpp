// Define a Value object
#include <iostream>

class Value {
  public:
    char operand;
    double data;
    double gradient;
    std::vector<std::shared_ptr<Value> > children;

  Value(double in) {
    data = in;
  }

  Value operator+(const Value& other) {
    Value result = Value(data + other.data);
    result.operand = '+';
    result.addChild(std::make_shared<Value>(*this));
    result.addChild(std::make_shared<Value>(other));
    return result;
  }

  Value operator*(const Value& other) {
    Value result = Value(data * other.data);
    result.operand = '*';
    result.addChild(std::make_shared<Value>(*this));
    result.addChild(std::make_shared<Value>(other));
    return result;
  }

  void addChild(std::shared_ptr<Value> child) {
    children.push_back(child);
  }

  void backward(double grad = 1.0) {
    gradient += grad;

    if(operand == '+') {
      children[0] -> backward(grad * 1.00);
      children[1] -> backward(grad * 1.00);
    }
    if(operand == '*') {
      // Multiplying the current gradient (chain rule)
      children[0] -> backward(grad * children[1] -> data);
      children[1] -> backward(grad * children[0] -> data);
    }
  }
};

int main() {
  // Creates a 'Value' object, assigning A a shared pointer to the node.
  auto A = std::make_shared<Value>(2.00);
  auto B = std::make_shared<Value>(-4.00);
  auto C = std::make_shared<Value>(9.00);

  auto D = std::make_shared<Value>(*A * *B);
  auto E = std::make_shared<Value>(*B * *C);

  auto L = std::make_shared<Value>(*D + *E);

  L->backward();

  std::cout << "Data [D]: " << E->data << std::endl;
  for (const auto& child : E->children) {
    std::cout << "Child Data: " << child->data << std::endl;
    std::cout << "Child Gradient: " << child->gradient << std::endl;
  }

  return 0;
}