// Import vector library
#include <vector>
#include <iostream>


// Function to create a design matrix for a given matrix.
// I: any matrix of dimension n x m
// O: a design matrix of dimension n x m
std::vector<std::vector<double> > designMatrix(const std::vector<double>& input) {
  // Retrieve the number of elements in the 'input' vector. The design matrix needs to be correctly sized.
  int size = input.size();
  std::vector<std::vector<double> > matrix(size, std::vector<double>(2));

  for (int i = 0; i < size; ++i) {
    matrix[i][0] = 1.0;       // for the intercept, or bias coefficient
    matrix[i][1] = input[i];  // feature value
  }
  return matrix;
}


// Function to transpose a matrix.
// I: any matrix of dimension n x m
// O: a transposed matrix of dimension m x n
std::vector<std::vector<double> > transposeMatrix(const std::vector<std::vector<double> >& input) {
  int rows = input.size();
  int cols = input[0].size();

  std::vector<std::vector<double> > transpose(cols, std::vector<double>(rows));

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      transpose[j][i] = input[i][j];
    }
  }
  return transpose;
}


// Function to create an identity matrix of given size.
// I: size of matrix, n
// O: an identity matrix of size n x n
std::vector<std::vector<double> > identityMatrix(int size) {
  std::vector<std::vector<double> > identity(size, std::vector<double>(size));

  for (int i = 0; i < size; ++i) {
    identity[i][i] = 1;
  }
  return identity;
}

// Function to calculate a base determinant of a 2 x 2 matrix.
// I: a matrix of size 2 x 2
// O: the determinant of that 2 x 2 matrix
double calculateBaseDeterminant(std::vector<std::vector<double> >& input) {
  if (input.size() != 2 || input[0].size() != 2) {
    throw std::invalid_argument("The input matrix is not 2x2.");
  }
  double determinant = (input[0][0] * input[1][1]) - (input[1][0] * input[0][1]);
  return determinant;
}

// Function to calculate the determinant of any square matrix.
// I: a matrix of size n x n
// O: the determinant of the input matrix.
double calculateDeterminant(std::vector<std::vector<double> >& input) {
  // Running total of the determinant
  double determinant = 0;

  // Check if the matrix is a base case, or 2 x 2; if so, recursion exits.
  if (input.size() == 2 && input[0].size() == 2) {
    determinant += calculateBaseDeterminant(input);
    return determinant;
  }

  // Laplace Expansion
  // Iterate through the first row, calculating the determinants of nested matrices.
  // i is the current column being expanded upon.
  for(int i = 0; i < input[0].size(); i++) {
    // Create submatrix of size [n-1] x [n-1]
    std::vector<std::vector<double> > subMatrix(input.size() - 1, std::vector<double>(input.size() - 1));

    // Iterate through the outer matrix, starting at 1 to skip the first row.
    for (int j = 1; j < input.size(); j++) {
      int subColIndex = 0;

      // Inner loop to iterate through columns
      for (int k = 0; k < input[j].size(); k++) {
        // Skip the column being expanded upon.
        if (k != i) {
          subMatrix[j-1][subColIndex] = input[j][k];
          subColIndex++;
        }
      }
    }
    double sign = (i % 2 == 0) ? 1 : -1;
    double subDeterminant = calculateDeterminant(subMatrix);
    determinant += sign * input[0][i] * subDeterminant;
  }
  return determinant;
}

// Function to multiply two matrices by each other.
// I: two matrices, matrixA and matrixB.
// O: the product of two matrices.
std::vector<std::vector<double> > multiplyMatrices(const std::vector<std::vector<double> >& matrixA, const std::vector<std::vector<double> >& matrixB) {
  // Check if the matrices can be multiplied
  if (matrixA[0].size() != matrixB.size()) {
    throw std::invalid_argument("Matrices cannot be multiplied.");
  }

  int numRowsA = matrixA.size();
  int numColsA = matrixA[0].size();
  int numRowsB = matrixB.size();
  int numColsB = matrixB[0].size();

  // Create the resulting matrix with the appropriate dimensions
  std::vector<std::vector<double> > result(numRowsA, std::vector<double>(numColsB));

  // Perform matrix multiplication
  for (int i = 0; i < numRowsA; ++i) {
    for (int j = 0; j < numColsB; ++j) {
      double sum = 0.0;
      for (int k = 0; k < numColsA; ++k) {
        sum += matrixA[i][k] * matrixB[k][j];
      }
      result[i][j] = sum;
    }
  }

  return result;
}

std::vector<double> multiplyMatrixWithVector(const std::vector<std::vector<double>>& matrix, const std::vector<double>& vector) {
  if (matrix[0].size() != vector.size()) {
    throw std::invalid_argument("Matrix and vector dimensions do not match.");
  }

  int numRows = matrix.size();
  int numCols = matrix[0].size();

  std::vector<double> result(numRows);

  for (int i = 0; i < numRows; ++i) {
    double sum = 0.0;
    for (int j = 0; j < numCols; ++j) {
      sum += matrix[i][j] * vector[j];
    }
    result[i] = sum;
  }

  return result;
}

// Function to divide a matrix by a scalaer.
// I: a matrix, divisible scalar.
// O: a matrix divided by the scalar.
void divideMatrix(std::vector<std::vector<double> >& matrix, double scalar) {
  int numRows = matrix.size();
  int numCols = matrix[0].size();

  for (int i = 0; i < numRows; ++i) {
    for (int j = 0; j < numCols; ++j) {
      matrix[i][j] /= scalar;
    }
  }
}


std::vector<std::vector<double> > inverseMatrix(std::vector<std::vector<double> >& input) {
  std::vector<std::vector<double> > transpose = transposeMatrix(input);
  std::vector<std::vector<double> > product = multiplyMatrices(transpose, input);

  int determinant = calculateDeterminant(product);

  if (determinant == 0) {
    throw std::runtime_error("Determinant is 0; matrix is not invertible.");
  }

  std::vector<std::vector<double> > adjugateMatrix = identityMatrix(input.size());
  divideMatrix(adjugateMatrix, determinant);
  return adjugateMatrix;
}

// Calculate coefficients of design matrix X and target variable Y.
std::vector<std::vector<double> > calculateCoefficients(std::vector<double>& X, std::vector<double> Y) {
  std::vector<std::vector<double>> XTX = multiplyMatrices(transposeMatrix(designMatrix(X)), designMatrix(X));
  std::vector<std::vector<double>> XTX_inverse = inverseMatrix(XTX);

  // Convert Y to a 2D matrix
  std::vector<std::vector<double>> Y_2D(Y.size(), std::vector<double>(1));
  for (int i = 0; i < Y.size(); ++i) {
    Y_2D[i][0] = Y[i];
  }

  std::vector<std::vector<double>> XTY = multiplyMatrices(transposeMatrix(designMatrix(X)), Y_2D);
  std::vector<std::vector<double>> coefficients = multiplyMatrices(XTX_inverse, XTY);
  
  return coefficients;
}


int main() {
  // Create a sample matrix for testing
  std::vector<double> matrix = {2, 4, 6, 8};

  // Create a sample target variable
  std::vector<double> target = {4, 8, 12, 16};

  // Print the matrix
  // Print the target variable
  std::cout << "Target Variable:\n";
  for (const auto& elem : target) {
      std::cout << elem << " ";
  }
  std::cout << "\n";

  std::vector<std::vector<double>> coefficients = calculateCoefficients(matrix, target);
  // Print coefficients
  std::cout << "Coefficients:\n";
  for (const auto& row : coefficients) {
      for (const auto& elem : row) {
          std::cout << elem << " ";
      }
      std::cout << "\n";
  }

  return 0;
}