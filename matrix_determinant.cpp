#include <iostream>
using namespace std;

// C++ program to find Determinant of a matrix
// Solve it by cofactor method
// 参考: https://www.youtube.com/watch?v=umXgFjqPfsk

// Dimension of input square matrix
const int N = 3;

/* function for displaying the matrix */
void display(int mat[N][N], int row, int col) {
    cout << "[DEBUG] display a matrix" << endl;
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) cout << " " << mat[i][j];

		cout << endl;
	}
    cout << "[DEBUG] done with displaying a matrix" << endl;
}

// Function to get cofactor of mat[p][q] in temp[][]. n is current dimension of mat[][]
void getCofactor(int mat[N][N], int temp[N][N], int p, int q, int n) {
    int i = 0, j = 0;  // fill temp by putting non 0 values on mostleft corner
	for (int row = 0; row < n; ++row) {
	    for (int col = 0; col < n; ++col) {
		    // Copying into temporary matrix only those element which are not in given row and col
		    if (row != p && col != q) {
			    temp[i][j] = mat[row][col];
                ++j;
                if (j == n-1) {
                    ++i;
                    j = 0;
                }
		    }
	    }
    }
}

/* Recursive function for finding determinant of matrix.
n is current dimension of mat[][]. */
int determinantOfMatrix(int mat[N][N], int n) {
    int res = 0; // Initialize result

	// Base case : if matrix contains single element
    if (n == 1) return mat[0][0];

    int temp[N][N] = {0}; // To store cofactors

    int sign = 1; // To store sign multiplier, simplified from (-1)^(i+j), i and j are ith row and jth col starts with 1

	// Iterate for each element of first row
    for (int f = 0; f < n; ++f) {
	    // Getting Cofactor of mat[0][f]
	    getCofactor(mat, temp, 0, f, n);

        display(temp, N, N);

	    res += sign * mat[0][f] * determinantOfMatrix(temp, n - 1);

	    // terms are to be added with alternate sign
	    sign = -sign;
	}

    return res;
}

int main() {
    // int mat[N][N] = {
    //                     {1, 3},
    //                     {2, 4}
    //                 };

    int mat[N][N] = {
                        {3, 1, 2},
					    {-1, -2, 5},
					    {2, 4, 1}
                    };

	// int mat[N][N] = { { 1, 0, 2, -1 },
	// 				{ 3, 0, 0, 5 },
	// 				{ 2, 1, 4, -3 },
	// 				{ 1, 0, 5, 0 } };
    //
    
    int res = determinantOfMatrix(mat, N);
	cout <<"Determinant of the matrix is: " << res << endl;
	return 0;
}

