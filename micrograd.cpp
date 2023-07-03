#include <iostream>
#include <vector>
#include <memory>

// Stores a single scalar value, and its gradient.
class Value {
  public:
    double data;
    double gradient;
    char operand;
    std::vector<std::shared_ptr<Value> > children;

    Value(double in) {
      data = in;
      gradient = 0.00;
    }

    Value operator+(const Value& other) {
      Value result(data + other.data);
      result.operand = '+';
      result.addChild(std::make_shared<Value>(*this));
      result.addChild(std::make_shared<Value>(other));
      return result;
    };

    Value operator*(const Value& other) {
      Value result(data * other.data);
      result.operand = '*';
      result.addChild(std::make_shared<Value>(*this));
      result.addChild(std::make_shared<Value>(other));
      return result;
    };

    void addChild(std::shared_ptr<Value> child) {
      children.push_back(child);
    };

    void backward(double grad = 1.0) {
      // Set the gradient of the current node
      gradient += grad;

      if (operand == '*') {
        children[0] -> backward(grad * children[1]->data);
        children[1] -> backward(grad * children[0]->data);
      }
      if(operand == '+') {
        children[0] -> backward(grad * 1.00);
        children[1] -> backward(grad * 1.00);
      }
    };
};

int main() {
  // Leaf nodes
  auto A = std::make_shared<Value>(-2.00);
  auto B = std::make_shared<Value>(4.00);
  auto D = std::make_shared<Value>(3.00);

  // Intermediary node
  auto C = std::make_shared<Value>(*A * *B);

  // Output
  auto L = std::make_shared<Value>(*C + *D);

  L->backward();

  for(const auto& child : C->children) {
    std::cout << "Child: " << child->data << std::endl; 
    std::cout << "Child Gradient: " << child->gradient << std::endl; 
  }
  std::cout << "Operand: " << L->operand;

  return 0;
}