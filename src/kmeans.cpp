#include "kmeans.hpp"

kmeans::kmeans(){}

MatrixXd kmeans::cluster(MatrixXd points, MatrixXd centroids, int t, int b)
{
	Utils utils;
	membership = VectorXd::Zero(b);
	counter = VectorXd::Zero(b);

	mini_batch = MatrixXd::Zero(b, points.cols());
	this->centroids = centroids.block(0,0, centroids.rows(), centroids.cols());

	utils.seed_random();

	do
	{
		//mini-batch creation loop
		for (int i=0; i<b; i++)
		{
			int row = utils.get_random() * points.rows();
			mini_batch.row(i) = points.row(row);
		}
		assign_step(mini_batch);
		update_step(mini_batch);
		t--;
	} while (t > 0);
	return this->centroids;
}

void kmeans::assign_step(MatrixXd mini_batch)
{
	#pragma omp parallel for schedule(static)
	for (int i=0; i<mini_batch.rows(); i++)
	{
		membership(i) = asignar(mini_batch.row(i));
	}
}

int kmeans::asignar(RowVectorXd point)
{
	MatrixXf::Index index;
	(centroids.rowwise() - point).rowwise().norm().minCoeff(&index);
	return index;
}

void kmeans::update_step(MatrixXd points)
{
	double learning_rate;
	int c;
	for (int i=0; i<membership.rows(); i++)
	{
		c = membership(i);
		counter(c)++;
		learning_rate = 1 / counter(c);

		centroids.row(c) = ((1 - learning_rate)*centroids.row(c)) + (learning_rate * points.row(i));
	}
}
