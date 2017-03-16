# Kmeans
K-means algorithm on c++ with [Eigen](http://eigen.tuxfamily.org/index.php) and [OpenMP](https://es.wikipedia.org/wiki/OpenMP) support.

## Requirements
- [Eigen](http://eigen.tuxfamily.org/index.php) instaled in `/usr/local/eigen3` for example, if you installed it in other place modify the `Makefile` and use your directory instead.
- A compiler with [OpenMP](https://es.wikipedia.org/wiki/OpenMP) support.

## Compile
To compile just run `make` and it will compile and generate the executable file `kmeans`

## Run
Execute `./kmeans k n d t b < input > output` for example.

Where: 
- **k** is the number of centroids you want to use
- **n** is the number of data points in the file (rows)
- **d** is the number of dimensions of each point (columns)
- **t** is the number of iterations you want to run
- **b** is the number of randomly selected points that will be used as the mini-batch
- **input** is the input file (stdin) that must have at least **n** rows with **d** columns of numeric values representing the coordinates of the points
- **output** is the output file (stdout) that will have **k** rows with **d** columns of numeric values representing the coordinates of the resulting centroids
