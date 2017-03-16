#include <iostream>
#include <cstdlib>
#include <Eigen/Dense>
#include "kmeans.hpp"
#include "utils.hpp"

using namespace Eigen;

int main(int argc, char** argv)
{
	std::cout.precision(10);
	if (argc < 6){
		std::cout << "Insuficient args " << std::endl;
		exit (0);
	}
	int k = atoi(argv[1]);
	int n = atoi(argv[2]);
	int d = atoi(argv[3]);
	int t = atoi(argv[4]);
	int b = atoi(argv[5]);

	//asignacion de memoria
	MatrixXd data = MatrixXd::Zero(n, d);

	//lectura de datos
	for (int i=0; i<n;i++)
	{
		for (int j=0; j<d; j++)
			std::cin >> data(i,j);
	}

	//se asignan los primeros k datos
	MatrixXd means = data.block(0, 0, k, d);

	Utils utils;
	kmeans kmeans(data, means, t, b);

	for (int i=0; i<k;i++)
	{
		for (int j=0; j<d; j++)
			std::cout << means(i, j) << " ";
		std::cout << std::endl;
	}
	return 0;
}
