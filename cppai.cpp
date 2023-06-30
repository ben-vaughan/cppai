// Import vector library
#include <vector>

// Example Matrix:
std::vector<double> x_values = {1.0, 2.0, 3.0, 4.0, 5.0};
std::vector<double> y_values = {2.0, 3.0, 5.0, 7.0, 9.0};

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
    matrix[i][0] = 1.0;       // for the intercept, or bias coefficient
    matrix[i][1] = input[i];  // feature value
  }

  return matrix;
}


std::vector<std::vector<double>> transposeMatrix(const std::vector<std::vector<double>>& input) {
  int rows = input.size();
  int cols = input[0].size();

  // Create empty tranpose matrix
  std::vector<std::vector<double>> transpose(cols, std::vector<double>(rows));

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      transpose[j][i] = input[i][j];
    }
  }
  return transpose;
}


std::vector<std::vector<double>> identityMatrix(int size) {
  // Create empty matrix
  std::vector<std::vector<double>> identity(size, std::vector<double>(size));

  for (int i = 0; i < size; ++i) {
    identity[i][i] = 1;
  }
  return identity;
}


int determinantMatrix(std::vector<std::vector<double>>) {
  
}


// std::vector<std::vector<double>> inverseMatrix(std::vector<std::vector<double>>& input) {

// }


// Calculate Coefficients: The formula for calculating the coefficients in OLS is β = (X^T * X)^-1 * X^T * Y. You'll need to write functions to calculate the transpose of a matrix, the matrix multiplication, and the inverse of a matrix.
// Compute X-transpose and multiply it with X.
// Compute the inverse of the result (let's call this A).
// Multiply X-transpose with the output vector Y.
// Multiply the result of the previous step (let's call this B) with A to get your β.