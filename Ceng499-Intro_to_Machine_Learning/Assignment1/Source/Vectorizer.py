#!/usr/bin/env python
# -*- coding: utf-8 -*-
import nltk
import numpy as np
import math
from collections import Counter

class Vectorizer:
    def __init__(self, min_word_length=3, max_df=1.0, min_df=0.0):
        self.min_word_length = min_word_length
        self.max_df=max_df
        self.min_df=min_df
        self.term_df_dict = {}
        np.set_printoptions(threshold=np.nan)

    def fit(self, raw_documents):
        """Generates vocabulary for feature extraction. Ignores words shorter than min_word_length and document frequency
        not between max_df and min_df.

        :param raw_documents: list of string for creating vocabulary
        :return: None
        """
        self.document_count = len(raw_documents)
        # TODO: Implement this method
        self.tokenized=[]
        self.setTokenized=[]
        self.vocabulary=[]
        c=Counter()
        for i in raw_documents:    #tokenized
            self.tokenized.append(nltk.word_tokenize(i))
        for i in range(self.document_count):   #remove duplicates
            self.setTokenized.append(list(set(self.tokenized[i])))
        for i in self.setTokenized: #count
            c.update(i)
        for i in c:
            count=c[i]/float(self.document_count)
            length=len(i)
            if(count>=self.min_df and count<=self.max_df and length>=self.min_word_length):
                self.vocabulary.append(i)
        for i in c:
            if i in self.vocabulary:
                self.term_df_dict[i]=c[i]/float(self.document_count)
        
        return self.vocabulary

    def _transform(self, raw_document, method):
        """Creates a feature vector for given raw_document according to vocabulary.

        :param raw_document: string
        :param method: one of count, existance, tf-idf
        :return: numpy array as feature vector
        """
        # TODO: Implement this method
        row=len(self.vocabulary)
        token=nltk.tokenize.word_tokenize(raw_document)
        result=np.zeros(row,dtype=float)
        if method=="existance":
            for i in token:
                if i in self.vocabulary:
                    result[self.vocabulary.index(i)]=1
        if method=="count":
            for i in token:
                if i in self.vocabulary:
                    #result[self.vocabulary.index(i)]++ calismiyor
                    result[self.vocabulary.index(i)]+=1

        """ TF-IDF(term, document) = TF(term, document)*IDF(term)
        TF(term, document) = Number of times term appears in document
        IDF(term) = log e ( 1 + Total number of documents /
                            1 + Total number of documents where term contained
                          )+1 """
        
        if method=="tf-idf":
            for i in token:
                if i in self.vocabulary:
                    totalWord=self.term_df_dict[i]*self.document_count
                    tf=token.count(i)/float(len(token))
                    idf=math.log((1+self.document_count)/(1+totalWord))+1
                    tfidf=tf*idf
                    result[self.vocabulary.index(i)]=tfidf
            norm=np.linalg.norm(result)
            if norm != 0.0:
                result=result/float(norm)
        return result

    def transform(self, raw_documents, method="tf-idf"):
        """For each document in raw_documents calls _transform and returns array of arrays.

        :param raw_documents: list of string
        :param method: one of count, existance, tf-idf
        :return: numpy array of feature-vectors
        """
        # TODO: Implement this method
        #row=len(raw_documents)
        column=len(self.vocabulary) 
        vector=np.zeros((len(raw_documents),column),dtype=float)
        #for i in range(self.document_count):
        for i in range(len(raw_documents)):
            vector[i]=self._transform(raw_documents[i],method)
        return vector

    def fit_transform(self, raw_documents, method="tf-idf"):
        """Calls fit and transform methods respectively.

        :param raw_documents: list of string
        :param method: one of count, existance, tf-idf
        :return: numpy array of feature-vectors
        """
        # TODO: Implement this method
        self.fit(raw_documents)
        return self.transform(raw_documents,method)

    def get_feature_names(self):
        """Returns vocabulary.

        :return: list of string
        """
        try:
            self.vocabulary
        except AttributeError:
            print "Please first fit the model."
            return []
        return self.vocabulary

    def get_term_dfs(self):
        """Returns number of occurances for each term in the vocabulary in sorted.

        :return: array of tuples
        """
        return sorted(self.term_df_dict.iteritems(), key=lambda (k, v): (v, k), reverse=True)

if __name__=="__main__":
    v = Vectorizer(min_df=0.25, max_df=0.75)
    contents = [
     "this is the first document",
     "this document is the second document",
     "and this is the third one",
     "is this the first document",
 ]
    v.fit(contents)
    print v.get_feature_names()
    existance_vector = v.transform(contents, method="existance")        
    print existance_vector
    count_vector = v.transform(contents, method="count")        
    print count_vector
    tf_idf_vector = v.transform(contents, method="tf-idf")
    print tf_idf_vector