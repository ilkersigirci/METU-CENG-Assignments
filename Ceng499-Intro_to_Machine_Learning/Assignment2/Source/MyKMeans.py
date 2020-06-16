#!/usr/bin/env python
# -*- coding: utf-8 -*-

import numpy as np
from scipy.spatial import distance
#from sklearn.cluster import KMeans

EPSILON = 0.0001

# numpy.sqrt(numpy.sum((x-y)**2))
# numpy.linalg.norm(a-b)
# distance.cdist([[1,2]], arr, 'euclidean')

class MyKMeans:
    """K-Means clustering similar to sklearn 
    library but different.
    https://goo.gl/bnuM33

    But still same.

    Parameters
    ----------
    n_clusters : int, optional, default: 8
        The number of clusters to form as well as the number of
        centroids to generate.
    init_method : string, optional, default: 'random'
        Initialization method. Values can be 'random', 'kmeans++'
        or 'manual'. If 'manual' then cluster_centers need to be set.
    max_iter : int, default: 300
        Maximum number of iterations of the k-means algorithm for a
        single run.
    random_state : int, RandomState instance or None, optional, default: None
        If int, random_state is the seed used by the random number generator;
        If RandomState instance, random_state is the random number generator;
        If None, the random number generator is the RandomState instance used
        by `np.random`.
    cluster_centers : np.array, used only if init_method is 'manual'.
        If init_method is 'manual' without fitting, these values can be used
        for prediction.
    """

    def __init__(self, init_method="random", n_clusters=3, max_iter=300, random_state=None, cluster_centers=[]):
        self.init_method = init_method
        self.n_clusters = n_clusters
        self.max_iter = max_iter
        self.random_state = np.random.RandomState(random_state)
        if init_method == "manual":
            self.cluster_centers = cluster_centers
        else:
            self.cluster_centers = []

    def fit(self, X):
        """Compute k-means clustering.
        Parameters
        ----------
        X : array-like, shape=(n_samples, n_features)
            Training instances to cluster.
        Returns
        ----------
        self : MyKMeans
        """
        self.labels = np.zeros(X.shape[0], dtype = int)
        temp = np.array(self.cluster_centers)
        for k in range(self.max_iter):
            for i in range(X.shape[0]):
                distArr = distance.cdist([X[i]], self.cluster_centers, 'euclidean')
                minIndex = np.argmin(distArr[0])
                self.labels[i] = minIndex
            for i in range(len(self.cluster_centers)):            
                sumVal = np.zeros((self.cluster_centers.shape[1]))
                number = 0
                for j in range(X.shape[0]):
                    if i == self.labels[j]:
                        sumVal += X[j]
                        number += 1      
                
                if(number == 0):
                    number = 1
                newCent = sumVal / float(number)
                temp[i] = newCent

            #if np.sqrt(np.sum((self.cluster_centers - temp)**2)) < EPSILON:

            if np.linalg.norm(self.cluster_centers - temp) < EPSILON:
                break
            else:
                self.cluster_centers = np.array(temp)

        return self

    def initialize(self, X):
        """ Initialize centroids according to self.init_method
        Parameters
        ----------
        X : array-like, shape=(n_samples, n_features)
            Training instances to cluster.
        Returns
        ----------
        self.cluster_centers : array-like, shape=(n_clusters, n_features)
        """
        array = np.zeros((self.n_clusters,X.shape[1]))

        if(self.init_method == "random"):            
            j = 0
            randNumArray = self.random_state.permutation(X.shape[0])[:self.n_clusters]

            for i in randNumArray:
                array[j] = X[i]
                j = j+1

        if(self.init_method == "kmeans++"):
            array = []
            array2 = []
            randNum = self.random_state.randint(X.shape[0]) 
            array.append(X[randNum].tolist())
            for i in range(self.n_clusters-1):
                eucSum = 0
                eucMax = 0
                for j in X:
                    if j.tolist() in array:
                        continue
                    distArr = distance.cdist([j], array, 'euclidean')
                    eucSum = distArr.sum()
                    if(eucSum) > eucMax:
                        array2 = j.tolist()
                        eucMax = eucSum

                array.append(array2)

        if(self.init_method != "manual"):       
            self.cluster_centers = np.array(array,dtype=float)

        return self.cluster_centers
                    
        

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
        X = np.array(X)
        self.labels = np.zeros(X.shape[0],dtype = int ) 
        for i in range(X.shape[0]):
            distArr = distance.cdist([X[i]], self.cluster_centers, 'euclidean')
            minIndex = np.argmin(distArr)
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
    if __name__ == "__main__":
        X = np.array([[1, 2], [1, 4], [1, 0],
                      [4, 2], [4, 4], [4, 0]])

        kmeans = MyKMeans(n_clusters=2, random_state=0, init_method='kmeans++')
        print kmeans.initialize(X)
        # [[4. 4.]
        #  [1. 0.]]
        kmeans = MyKMeans(n_clusters=2, random_state=0, init_method = 'random')
        print kmeans.initialize(X)
        # [[4. 0.]
        #  [1. 0.]]
        
        kmeans.fit(X)
        print kmeans.labels
        # array([1, 1, 1, 0, 0, 0])
        print kmeans.predict([[0, 0], [4, 4]])
        # array([1, 0])
        print kmeans.cluster_centers
        # array([[4, 2],
        #       [1, 2]])