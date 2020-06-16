#!/usr/bin/env python
# -*- coding: utf-8 -*-
import numpy as np
from scipy.spatial import distance

class MyKNeighborsClassifier:
    """Classifier implementing the k-nearest neighbors vote similar to sklearn 
    library but different.
    https://goo.gl/Cmji3U

    But still same.
    
    Parameters
    ----------
    n_neighbors : int, optional (default = 5)
        Number of neighbors to use by default.
    method : string, optional (default = 'classical')
        method for voting. Possible values:
        - 'classical' : uniform weights.  All points in each neighborhood
          are weighted equally.
        - 'weighted' : weight points by the inverse of their distance.
          in this case, closer neighbors of a query point will have a
          greater influence than neighbors which are further away.
        - 'validity' weights are calculated with distance and multiplied
          of validity for each voter.  
        Note: implementing kd_tree is bonus.
    norm : {'l1', 'l2'}, optional (default = 'l2')
        Distance norm. 'l1' is manhattan distance. 'l2' is euclidean distance.
    Examples
    --------
    """
    def __init__(self, n_neighbors=5, method='classical', norm='l2'):
        self.n_neighbors = n_neighbors
        self.method = method
        self.norm = norm
        self.labels = []
        self.distinct_labels = []
        self.data = []

    def fit(self, X, y):
        """Fit the model using X as training data and y as target values
        Parameters
        ----------
        X : array-like, shape (n_query, n_features),
            Training data. 
        y : array-like, shape = [n_samples] 
            Target values.
        """
        self.data = X
        self.labels = y
        self.distinct_labels = list(set(self.labels))

        if(self.method == "validity"):
            self.fitValidity = np.zeros(len(X))
            for i in range(len(X)):
                distArr = distance.cdist([X[i]], self.data, 'cityblock') if self.norm == 'l1' else distance.cdist([X[i]], self.data, 'euclidean')
                neighIndexArr = np.argpartition(distArr[0], self.n_neighbors)
                tempLabels = np.zeros(len(self.distinct_labels))

                for j in range(self.n_neighbors+1):
                    neighIndex = neighIndexArr[j]
                    neighLabel = self.labels[neighIndex]
                    dists = distArr[0][neighIndex]
                    
                    if dists != 0:  # neighIndex != i
                        tempLabels[neighLabel] += 1 / dists
                
                tempLabels = tempLabels / sum(tempLabels)
                fittedLabel = tempLabels[self.labels[i]]
                self.fitValidity[i] = fittedLabel

            
    def predict(self, X):
        """Predict the class labels for the provided data
        Parameters
        ----------
        X : array-like, shape (n_query, n_features),
            Test samples.
        Returns
        -------
        y : array of shape [n_samples]
            Class labels for each data sample.
        """
        if len(self.labels) == 0:
            raise ValueError("You should fit first!")
        
        tempLabels = np.zeros(len(self.distinct_labels))

        if(self.method == "classical"):
            classical = [] 
            for i in range(len(X)):
                distArr = distance.cdist([X[i]], self.data, 'cityblock') if self.norm == 'l1' else distance.cdist([X[i]], self.data, 'euclidean')
                neighIndexArr = np.argpartition(distArr[0], self.n_neighbors)
                tempLabels = np.zeros(len(self.distinct_labels))

                for j in range(self.n_neighbors):
                    neighIndex = neighIndexArr[j]
                    neighLabel = self.labels[neighIndex]
                    tempLabels[neighLabel] += 1

                predictedLabel = np.argmax(tempLabels)
                classical.append(predictedLabel)

            return classical

        if(self.method == "weighted"):
            weighted = [] 
            for i in range(len(X)):
                distArr = distance.cdist([X[i]], self.data, 'cityblock') if self.norm == 'l1' else distance.cdist([X[i]], self.data, 'euclidean')
                neighIndexArr = np.argpartition(distArr[0], self.n_neighbors)
                tempLabels = np.zeros(len(self.distinct_labels))

                for j in range(self.n_neighbors):
                    neighIndex = neighIndexArr[j]
                    neighLabel = self.labels[neighIndex]
                    dists = distArr[0][neighIndex]
                    tempLabels[neighLabel] += 1 / (1e-15 + dists)

                predictedLabel = np.argmax(tempLabels)
                weighted.append(predictedLabel)

            return weighted

        if(self.method == "validity"):
            validity = []
            for i in range(len(X)):
                distArr = distance.cdist([X[i]], self.data, 'cityblock') if self.norm == 'l1' else distance.cdist([X[i]], self.data, 'euclidean')
                neighIndexArr = np.argpartition(distArr[0], self.n_neighbors)
                tempLabels = np.zeros(len(self.distinct_labels))

                for j in range(self.n_neighbors):
                    neighIndex = neighIndexArr[j]
                    neighLabel = self.labels[neighIndex]
                    dists = distArr[0][neighIndex]
                    val = self.fitValidity[neighIndex]
                    tempLabels[neighLabel] += val * (1 / (1e-15 + dists))

                predictedLabel = np.argmax(tempLabels)
                validity.append(predictedLabel)

            return validity
        
        
    def predict_proba(self, X, method=None):
        """Return probability estimates for the test data X.
        Parameters
        ----------
        X : array-like, shape (n_query, n_features),
            Test samples.
        method : string, if None uses self.method.
        Returns
        -------
        p : array of shape = [n_samples, n_classes]
            The class probabilities of the input samples. Classes are ordered
            by lexicographic order.
        """
        if(method == "classical"):
            classical = [] 
            for i in range(len(X)):
                distArr = distance.cdist([X[i]], self.data, 'cityblock') if self.norm == 'l1' else distance.cdist([X[i]], self.data, 'euclidean')
                neighIndexArr = np.argpartition(distArr[0], self.n_neighbors)
                tempLabels = np.zeros(len(self.distinct_labels))

                for j in range(self.n_neighbors):
                    neighIndex = neighIndexArr[j]
                    neighLabel = self.labels[neighIndex]
                    tempLabels[neighLabel] += 1

                predictedLabel = tempLabels / sum(tempLabels)
                classical.append(predictedLabel)

            return classical

        if(method == "weighted"):
            weighted = [] 
            for i in range(len(X)):
                distArr = distance.cdist([X[i]], self.data, 'cityblock') if self.norm == 'l1' else distance.cdist([X[i]], self.data, 'euclidean')
                neighIndexArr = np.argpartition(distArr[0], self.n_neighbors)
                tempLabels = np.zeros(len(self.distinct_labels))

                for j in range(self.n_neighbors):
                    neighIndex = neighIndexArr[j]
                    neighLabel = self.labels[neighIndex]
                    dists = distArr[0][neighIndex]
                    tempLabels[neighLabel] += 1 / (1e-15 + dists)

                predictedLabel = tempLabels / sum(tempLabels)
                weighted.append(predictedLabel)

            return weighted

        if(method == "validity"):
            validity = []
            for i in range(len(X)):
                distArr = distance.cdist([X[i]], self.data, 'cityblock') if self.norm == 'l1' else distance.cdist([X[i]], self.data, 'euclidean')
                neighIndexArr = np.argpartition(distArr[0], self.n_neighbors)
                tempLabels = np.zeros(len(self.distinct_labels))

                for j in range(self.n_neighbors):
                    neighIndex = neighIndexArr[j]
                    neighLabel = self.labels[neighIndex]
                    dists = distArr[0][neighIndex]
                    val = self.fitValidity[neighIndex]
                    tempLabels[neighLabel] += val * (1 / (1e-15 + dists))

                predictedLabel = tempLabels / sum(tempLabels)
                validity.append(predictedLabel)

            return validity        

if __name__=='__main__':
    X = [[0], [1], [2], [3]]
    y = [0, 0, 1, 1]
    neigh = MyKNeighborsClassifier(n_neighbors=3, method="validity")
    neigh.fit(X, y)
    #neigh.predict(X)
    n = 0.9
    print(neigh.predict_proba([[n]], method='classical'))
    # [[0.66666667 0.33333333]]
    print(neigh.predict_proba([[n]], method='weighted'))
    # [[0.92436975 0.07563025]]
    print(neigh.predict_proba([[n]], method='validity'))
    # [[0.92682927 0.07317073]]