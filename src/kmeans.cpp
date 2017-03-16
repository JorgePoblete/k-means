#include "kmeans.hpp"

kmeans::kmeans(MatrixXd points, MatrixXd centroids, int t, int b)
{
	Utils utils;
	membership = VectorXd::Zero(b);
	counter = VectorXd::Zero(b);

	mini_batch = MatrixXd::Zero(b, points.cols());

	utils.seed_random();

	int changed;
	do
	{
		//mini-batch creation loop
		for (int i=0; i<b; i++)
		{
			int row = utils.get_random() * n;
			mini_batch.row(i) = points.row(row);
		}
		changed = assign_step(mini_batch, centroids);
		update_step(mini_batch, centroids);
		t--;
	} while (t > 0 && changed > 0);
}

int kmeans::assign_step(MatrixXd mini_batch, MatrixXd centroids)
{
	int changed = 0, kmin;

	#pragma omp parallel for schedule(static) private(kmin)
	for (int i=0; i<mini_batch.rows(); i++)
	{
		kmin = asignar(mini_batch.row(i), centroids);
		if (membership(i) != kmin)
			#pragma omp atomic
			changed = changed + 1;
		membership(i) = kmin;
	}

	return changed;
}

int kmeans::asignar(VectorXd point, MatrixXd centroids)
{
	int kmin;
	double dmin,dist;
	dmin = 99e99;
	kmin = 0;
	for (int c=0; c<centroids.rows(); c++)
	{
		dist = euclidian_distance(point, centroids.row(c));
		if (dmin > dist)
		{
			dmin = dist;
			kmin = c;
		}
	}
	return kmin;
}

double kmeans::euclidian_distance(VectorXd point, VectorXd centroid)
{
	return (point - centroid).squaredNorm();
}

void kmeans::update_step(MatrixXd points, MatrixXd centroids)
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
