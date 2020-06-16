#!/usr/bin/env python
# -*- coding: utf-8 -*-

#from scipy.ndimage import imread

from scipy import misc
from PIL import Image
import numpy as np
from sklearn.utils import shuffle
from MyKMeans import MyKMeans

class ColorQuantizer:
    """Quantizer for color reduction in images. Use MyKMeans class that you implemented.
    
    Parameters
    ----------
    n_colors : int, optional, default: 64
        The number of colors that wanted to exist at the end.
    random_state : int, RandomState instance or None, optional, default: None
        If int, random_state is the seed used by the random number generator;
        If RandomState instance, random_state is the random number generator;
        If None, the random number generator is the RandomState instance used
        by `np.random`.

    Read more from:
    http://scikit-learn.org/stable/auto_examples/cluster/plot_color_quantization.html
    """
    
    def __init__(self, n_colors=64, random_state=None):

        self.random_state = random_state
        self.n_colors = n_colors
    
    def read_image(self, path):
        """Reads jpeg image from given path as numpy array. Stores it inside the
        class in the image variable.
        
        Parameters
        ----------
        path : string, path of the jpeg file
        """
        self.image = misc.imread(path)
        self.w, self.h, self.d  = tuple(self.image.shape)
        self.image = np.reshape(self.image, (self.w * self.h, self.d))

    def recreate_image(self, path_to_save):
        """Reacreates image from the trained MyKMeans model and saves it to the
        given path.
        
        Parameters
        ----------
        path_to_save : string, path of the png image to save
        """
        self.image = np.reshape(self.image, (self.w, self.h, self.d))
        misc.imsave(path_to_save, self.image)

    def export_cluster_centers(self, path):
        """Exports cluster centers of the MyKMeans to given path.

        Parameters
        ----------
        path : string, path of the txt file
        """
        np.savetxt(path,self.myKmeans.cluster_centers)
        
    def quantize_image(self, path, weigths_path, path_to_save):
        """Quantizes the given image to the number of colors given in the constructor.
        
        Parameters
        ----------
        path : string, path of the jpeg file
        weigths_path : string, path of txt file to export weights
        path_to_save : string, path of the output image file
        """
        
        self.read_image(path)        
        shuffled = np.array(self.image)
        np.random.shuffle(shuffled)
        
        self.myKmeans = MyKMeans(random_state=self.random_state, n_clusters=self.n_colors, max_iter=600, init_method="random")
        self.initCenter = self.myKmeans.initialize(self.image)
        
        self.myKmeans.fit(shuffled[:7777])
        myLabels = self.myKmeans.predict(self.image)
        myCenters = self.myKmeans.cluster_centers
        self.export_cluster_centers(weigths_path)

        dim2 = self.w * self.h
        result = []
        for i in range(dim2):
            result.append(myCenters[myLabels[i]])

        self.image = np.array(result)
        self.recreate_image(path_to_save)
        
        
        

if __name__=='__main__':

    """ path = "/mnt/d/DERS/0000GITHUB/Machine-Learning/THE2/Docs/ankara.jpg"
    centers = "/mnt/d/DERS/0000GITHUB/Machine-Learning/THE2/Docs/ankara_centers.txt"
    save = "/mnt/d/DERS/0000GITHUB/Machine-Learning/THE2/Docs/ankara.jpg" """
    
    path = "/mnt/d/DERS/0000GITHUB/Machine-Learning/THE2/Docs/metu.jpg"
    centers = "/mnt/d/DERS/0000GITHUB/Machine-Learning/THE2/Docs/metu_centers.txt"
    save = "/mnt/d/DERS/0000GITHUB/Machine-Learning/THE2/Docs/metu.jpg"

    img = ColorQuantizer()
    img.quantize_image(path, centers, save)