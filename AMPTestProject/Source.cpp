/*
 *	\brief	A test between matrix multiplication on the CPU vs matrix multiplication on the GPU using C++ AMP
 *	\author	Christian Magnerfelt
 *	\date	2012.08.28
 */
#include <iostream>
#include <algorithm>
#include <amp.h>
#include <array>
#include <vector>

using namespace concurrency;

/*
 *	\brief	A simple matrix class that supports multiplication
 */

class Matrix3x3{
	public:
		Matrix3x3(){
			for(int i = 0; i<3; ++i){
				for(int j = 0; j<3; ++j){
					data[i][j] = 0;	
				}
			}
		}

		Matrix3x3(const std::array<int, 9> & arrayRef){
			for(int i = 0; i<3; ++i){
				for(int j = 0; j<3; ++j){
					data[i][j] = arrayRef[i*3 + j];	
				}
			}
		}

		Matrix3x3 operator*(Matrix3x3 & other){
			Matrix3x3 result;
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
					std::cout << data[i][j] << " ";
				}
				std::cout << "\n";
			}
		}

	private:
		std::array<std::array<int, 3>, 3> data;
};

class ParallelMatrix3x3
{
public:
	ParallelMatrix3x3() : N(3), M(3), av(N,M,data){
		std::fill(data.begin(), data.end(), 0);
	}
	ParallelMatrix3x3(std::array<int,9> & v) : N(3), M(3), data(v), av(N,M,data){}

	ParallelMatrix3x3 operator*(ParallelMatrix3x3 & other){
		ParallelMatrix3x3 result;
		parallel_for_each(av.extent,[](index<2> idx) restrict(amp){

		});
	}

private:
	const size_t N;
	const size_t M;
	std::array<int,9> data;
	array_view<int, 2 > av;
};

int main (int argc, const char * argv){
	std::array<int,9> data = {1, 1, 1, 1, 1, 1, 1, 1, 1};
	std::for_each(data.begin(), data.end(),[](int & value){
		std::cout << value << " ";
	});
	std::cout << std::endl;

	Matrix3x3 a (data);
	Matrix3x3 b (data);

	Matrix3x3 c = a * b;

	c.print();

	system("pause");
	return 0;
}