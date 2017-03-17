#ifndef KMEANS_H_
#define KMEANS_H_

#include <iostream>
#include <Eigen/Dense>
#include <cmath>
#include <omp.h>
#include "utils.hpp"

using namespace Eigen;

class kmeans
{
	public:
		int k, n, d;
		VectorXd membership, counter;
		MatrixXd points, centroids, mini_batch;
		kmeans();
		MatrixXd cluster(MatrixXd points, MatrixXd centroids, int t, int b);
	private:
		void assign_step(MatrixXd points);
		int asignar(RowVectorXd point);
		void update_step(MatrixXd points);
};
#endif
