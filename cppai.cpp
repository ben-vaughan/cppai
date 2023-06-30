// Import vector library
#include <vector>

// Function to create an identity matrix
// Return type is a vector of doubles nested within a vector of doubles.
// The '&' symbol is used to create a reference to the original vector instead of making a copy of it.
// const: the function will not change the incoming vector. Changing 'input' will result in an error.
// &: 'input' is a reference to a vector of doubles. As a reference, it is accessing the original variable.
// input: the name given to the reference in the parameter list.
std::vector<std::vector<double>> designMatrix(const std::vector<double>& input) {
  // Retrieve the number of elements in the 'input' vector. The design matrix needs to be correctly sized.
  int size = input.size();
  // Creates the design matrix. 'matrix' is the name of the matrix.
  // Has a 'size' number of rows, where each row is a std::vector<double>(2) of size 2.
  // All elements are default initialised to 0.0.
  // matrix(size, std::vector<double>(2)) - number of elements, each element has another vector with 2 elements in it.
  std::vector<std::vector<double>> matrix(size, std::vector<double>(2));

  for (int i = 0; i < size; ++i) {
    matrix[i][0] = 1.0;     // for the intercept, or bias coefficient
    matrix[i][1] = input[i] // feature value
  }
}