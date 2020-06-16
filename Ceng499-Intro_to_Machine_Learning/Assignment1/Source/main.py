from ExperimentSuite import ExperimentSuite
import tensorflow as tf
from Vectorizer import Vectorizer
from datetime import datetime

DEFAULT_EPOCH = 75
DEFAULT_LAYERS = (512,)
DEFAULT_ACTIVATION = tf.nn.relu
DEFAULT_LOSS = "categorical_hinge"


if __name__ == "__main__":
    # TODO: Make your experiments here
    es = ExperimentSuite()
    v=Vectorizer(max_df=0.97,min_df=0.5)
    """ print datetime.now() 
    v1=v.fit_transform(es.train_contents,"tf-idf")
    print v1
    print datetime.now() """
    
    print datetime.now()    
    trainx=v.fit_transform(es.train_contents,"count")
    testx=v.transform(es.test_contents,"count")
    tbCallBack=tf.keras.callbacks.TensorBoard(log_dir='./Graph',histogram_freq=0,write_graph=True,write_images=True)
    result=es.train_model(DEFAULT_LAYERS,tbCallBack,trainx,es.train_y,testx,es.test_y,DEFAULT_LOSS,DEFAULT_ACTIVATION,DEFAULT_EPOCH)
    print result
    print datetime.now()