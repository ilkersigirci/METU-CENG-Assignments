#!/usr/bin/env python
# -*- coding: utf-8 -*-

import numpy as np
from scipy.spatial import distance

class MyKMedoids:
    """KMedoids implementation parametric with 'pam' and 'clara' methods.

    Parameters
    ----------
    n_clusters : int, optional, default: 3
        The number of clusters to form as well as the number of medoids to
        determine.
    max_iter : int, default: 300
        Maximum number of iterations of the k-medoids algorithm for a
        single run.
    method : string, default: 'pam'
        If it is pam, it applies pam algorithm to whole dataset 'pam'.
        If it is 'clara' it selects number of samples with sample_ratio and applies
            pam algorithm to the samples. Returns best medoids of all trials
            according to cost function.
    sample_ratio: float, default: .2
        It is used if the method is 'clara'
    clara_trials: int, default: 10,
        It is used if the method is 'clara'
    random_state : int, RandomState instance or None, optional, default: None
        If int, random_state is the seed used by the random number generator;
        If RandomState instance, random_state is the random number generator;
        If None, the random number generator is the RandomState instance used
        by `np.random`.

    Examples

    """

    def __init__(self, n_clusters=3, max_iter=300, method='clara', sample_ratio=.2, clara_trials=10, random_state=0):
        self.n_clusters = n_clusters
        self.max_iter = max_iter
        self.method = method
        self.sample_ratio = sample_ratio
        self.clara_trials = clara_trials
        self.random_state = np.random.RandomState(random_state)
        self.best_medoids = []
        self.min_cost = float('inf')

    def fit(self, X):
        """Compute k-medoids clustering. If method is 'pam'
        Parameters
        ----------
        X : array-like, shape=(n_samples, n_features)
            Training instances to cluster.
        Returns
        ----------
        self : MyKMedoids
        """
        self.X = X
        
        if self.method == "pam":

            self.best_medoids, self.min_cost = self.pam(X)

        if self.method == "clara":
            self.min_cost = float('inf')
            for _ in range(self.clara_trials):
                mySample = self.sample()
                temp_medoids, tempMin_cost = self.pam(mySample)
                self.clusters = self.generate_clusters(temp_medoids, X)
                tempMin_cost = self.calculate_cost(temp_medoids, self.clusters)
                if(tempMin_cost < self.min_cost):
                    self.min_cost = tempMin_cost
                    bestMed = temp_medoids
            self.best_medoids = bestMed       

        return self

    def sample(self):
        """Samples from the data with given sample_ratio.

        Returns
        -------
        X : {array-like, sparse matrix}, shape = [n_samples, n_features]
            New data to transform.
        """
        sample = self.random_state.permutation(self.X)[:int(self.sample_ratio*len(self.X))]
        return sample

    def pam(self, X):
        """
        kMedoids - PAM
        See more : http://en.wikipedia.org/wiki/K-medoids
        The most common realisation of k-medoid clustering is the Partitioning Around Medoids (PAM) algorithm and is as follows:[2]
        1. Initialize: randomly select k of the n data points as the medoids
        2. Associate each data point to the closest medoid. ("closest" here is defined using any valid distance metric, most commonly Euclidean distance, Manhattan distance or Minkowski distance)
        3. For each medoid m
            For each non-medoid data point o
                Swap m and o and compute the total cost of the configuration
        4. Select the configuration with the lowest cost.
        5. repeat steps 2 to 4 until there is no change in the medoid.
        Parameters
        ----------
        X : {array-like, sparse matrix}, shape = [n_samples, n_features]
            New data to transform.
        Returns
        -------
        best_medoids, min_cost : tuple, shape [n_samples,]
            Best medoids found and the cost according to it.
        """
        
        min_cost = float('inf')
        medoids = np.zeros((self.n_clusters,X.shape[1]))
        tempMedoids = np.array(medoids)      
        randNumArray = self.random_state.permutation(X.shape[0])[:self.n_clusters]
        
        for i in range(self.n_clusters):
            index = randNumArray[i]
            medoids[i] = X[index]
        clusters = self.generate_clusters(medoids, X)
        min_cost = self.calculate_cost(medoids, clusters)
        for _ in range(self.max_iter):
            tempMedoids = np.array(medoids)
            for i in range(len(medoids)):
                for j in range(len(X)):
                    if X[j].tolist() in medoids.tolist():
                        continue
                    temp = np.array(medoids[i])
                    medoids[i] = X[j]
                    tempCost = self.calculate_cost(medoids, clusters)
                    if tempCost >= min_cost:
                        medoids[i] = np.array(temp)
                    else:
                        min_cost = tempCost
            if medoids.tolist() == tempMedoids.tolist():
                break

        return medoids, min_cost

    def generate_clusters(self, medoids, samples):
        """Generates clusters according to distance to medoids. Order
        is same with given medoids array.
        Parameters
        ----------
        medoids: array_like, shape = [n_clusters, n_features]
        samples: array-like, shape = [n_samples, n_features]
        Returns
        -------
        clusters : array-like, shape = [n_clusters, elemens_inside_cluster, n_features]
        """

        clusters = []
        new = []
        labels = np.zeros(samples.shape[0], dtype = int)
        for i in range(samples.shape[0]):
            distArr = distance.cdist([samples[i]], medoids, 'euclidean')
            minIndex = np.argmin(distArr)
            labels[i] = minIndex
        
        for i in range(len(medoids)):
            new = []
            for j in range(len(labels)):
                if i == labels[j]:
                    new.append(samples[j])

            clusters.append(new)
        return clusters

    def calculate_cost(self, medoids, clusters):
        """Calculates cost of each medoid's cluster with squared euclidean function.
        Parameters
        ----------
        medoids: array_like, shape = [n_clusters, n_features]
        clusters: array-like, shape = [n_clusters, elemens_inside_cluster, n_features]
        Returns
        -------
        cost : float
            total cost of clusters
        """
        totalCost = 0

        for i in range(len(medoids)):
            for j in range(len(clusters[i])):
                totalCost += np.sum((medoids[i]-clusters[i][j])**2)

        return totalCost


    def predict(self, X):
        """Predict the closest cluster each sample in X belongs to.
        In the vector quantization literature, `cluster_centers` is called
        the code book and each value returned by `predict` is the index of
        the closest code in the code book.
        Parameters
        ----------
        X : array-like, shape = [n_samples, n_features]
            New data to predict.
        Returns
        -------
        labels : array, shape [n_samples,]
            Index of the cluster each sample belongs to.
        """
        self.labels = np.zeros(X.shape[0], dtype = int)
        for i in range(X.shape[0]):
            distArr = distance.cdist([X[i]], self.best_medoids, 'euclidean')
            minIndex = np.argmin(distArr[0])
            self.labels[i] = minIndex

        return self.labels

    def fit_predict(self, X):
        """Compute cluster centers and predict cluster index for each sample.
        Convenience method; equivalent to calling fit(X) followed by
        predict(X).
        Parameters
        ----------
        X : {array-like, sparse matrix}, shape = [n_samples, n_features]
            New data to transform.
        Returns
        -------
        labels : array, shape [n_samples,]
            Index of the cluster each sample belongs to.
        """
        return self.fit(X).predict(X)


if __name__ == "__main__":
    X = np.array([np.array([2., 6.]),
                  np.array([3., 4.]),
                  np.array([3., 8.]),
                  np.array([4., 7.]),
                  np.array([6., 2.]),
                  np.array([6., 4.]),
                  np.array([7., 3.]),
                  np.array([7., 4.]),
                  np.array([8., 5.]),
                  np.array([7., 6.])

                  ])

    kmedoids = MyKMedoids(n_clusters=2, random_state=0,sample_ratio=.2, method='pam')
    print kmedoids.fit_predict(X)
    # [1 1 1 1 0 0 0 0 0 0]
    print kmedoids.best_medoids
    # [array([7., 4.]), array([2., 6.])]
    print kmedoids.min_cost
    # 28.0