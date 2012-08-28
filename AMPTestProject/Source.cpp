/*
 *	\brief	A test between matrix multiplication on the CPU vs matrix multiplication on the GPU using C++ AMP
 *	\author	Christian Magnerfelt
 *	\date	2012.08.28
 */
#include <iostream>
#include <amp.h>
#include <array>

using namespace concurrency;
using namespace std;

/*
 *	\brief	A simple matrix class that supports multiplication
 */
class Matrix{
	public:
		Matrix(){}
		Matrix(std::array<std::array<int, 3>, 3> & arrayRef) : data(arrayRef){}

		Matrix operator*(Matrix & other){
			Matrix result;
			for(int i = 0; i < 3; ++i){
				for(int j = 0; j < 3; ++j){
					for(int k = 0; k < 3; ++k){
						result.data[i][j] += data[i][k] * other.data[k][j]; 
					}
				}
			}
			return result;
		}

		void print()
		{
			for(int i = 0; i < 3; ++i){
				for(int j = 0; j < 3; ++j){
					cout << data[i][j] << " ";
				}
				cout << "\n";
			}
		}

	private:
		std::array<std::array<int, 3>, 3> data;
};

int main (int argc, const char * argv){
	std::array<std::array<int, 3>, 3> values = {1, 1, 1, 1, 1, 1, 1, 1, 1};

	Matrix a (values);
	Matrix b (values);

	Matrix c = a * b;

	c.print();

	system("pause");
	return 0;
}