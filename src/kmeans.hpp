#ifndef KMEANS_H_
#define KMEANS_H_

#include <iostream>
#include <cmath>
#include <Eigen/Dense>
#include <omp.h>
#include "utils.hpp"

using namespace Eigen;

class kmeans
{
	public:
		int k, n, d;
		VectorXd membership, counter;
		MatrixXd points, centroids, mini_batch;
		kmeans(MatrixXd points, MatrixXd centroids, int t, int b);
	private:
		int assign_step(MatrixXd points, MatrixXd centroids);
		int asignar(VectorXd point, MatrixXd centroids);
		double euclidian_distance(VectorXd point, VectorXd centroid);
		void update_step(MatrixXd points, MatrixXd centroids);
};
#endif
