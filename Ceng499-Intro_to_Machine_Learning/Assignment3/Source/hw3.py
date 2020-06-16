import numpy as np
import sys

def forward(transitionPath, estimatePath, observationPath):
    transitionMatrix = np.loadtxt(transitionPath)
    estimateMatrix = np.loadtxt(estimatePath)
    observationMatrix = np.loadtxt(observationPath,dtype = int)
    
    N = transitionMatrix.shape[0]
    T = observationMatrix.shape[0]
    forward = np.zeros((N,T))

    for s in range(1,N-1):
        forward[s][0] = transitionMatrix[0][s] * estimateMatrix[s][observationMatrix[0]]

    for t in range(1,T):
        for s in range(1,N-1):
            mySum = 0
            for i in range(1,N-1):
                mySum += forward[i][t-1] * transitionMatrix[i][s] * estimateMatrix[s][observationMatrix[t]]
                
            forward[s][t] = mySum
            
    mySum = 0
    for s in range(1,N-1):
        mySum += forward[s][T-1] * transitionMatrix[s][N-1]
    
    forward[N-1][T-1] = mySum

    result = forward[N-1][T-1]

    print result

def viterbi(transitionPath, estimatePath, observationPath):
    
    transitionMatrix = np.loadtxt(transitionPath)
    estimateMatrix = np.loadtxt(estimatePath)
    observationMatrix = np.loadtxt(observationPath,dtype = int)
    
    N = transitionMatrix.shape[0]
    T = observationMatrix.shape[0]
    viterbi = np.zeros((N,T))
    backPointer = np.zeros((N,T),dtype = int)
    for s in range(1,N-1):
        viterbi[s][0] = transitionMatrix[0][s] * estimateMatrix[s][observationMatrix[0]]
        backPointer[s][0] = 0

    for t in range(1,T):
        for s in range(1,N-1):
            myMax = 0
            for i in range(1,N-1):
                tempMax = viterbi[i][t-1] * transitionMatrix[i][s] * estimateMatrix[s][observationMatrix[t]]
                if(tempMax > myMax) : myMax = tempMax
            viterbi[s][t] = myMax
            
            myMax = 0
            index = 0
            for i in range(1,N-1):
                tempMax = viterbi[i][t-1] * transitionMatrix[i][s]
                if(tempMax > myMax) : 
                    myMax = tempMax
                    index = i
            backPointer[s][t] = index
    
    myMax = 0
    index = 0
    for s in range(1,N-1):
        tempMax = viterbi[s][T-1] * transitionMatrix[s][N-1]
        if(tempMax > myMax) : 
            myMax = tempMax
            index = s
    viterbi[N-1][T-1] = myMax
    backPointer[N-1][T-1] = index

    result = []
    index = backPointer[N-1][T-1]
    result.insert(0,index)
    
    for i in range(T, 1, -1):
        index = backPointer[index][i-1]
        result.insert(0,index)

    print result

if __name__ == "__main__":

    function  = sys.argv[1]
    transitionPath = "./" + sys.argv[2]
    estimatePath  = "./" + sys.argv[3]
    observationPath = "./" + sys.argv[4]

    if(function == "viterbi") : viterbi(transitionPath, estimatePath, observationPath)
    if(function == "forward") : forward(transitionPath, estimatePath, observationPath)