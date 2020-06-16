from math import sqrt

class Assignment3:

  def __init__(self):
    # Stored as dictionary since dictionary key lookup is O(1) 
    self.aminoAcid_A, self.aminoAcid_B  = {}, {}
    self.pairs, self.adj, self.groups = [], [], []

  def parseFile(self, input):
    with open(input) as file:
      for line in file:
        if(line[:4] != 'ATOM'): continue
        if(line[17:20].strip() != "GLY" and line[12:16].strip() != "CB"): continue;
        if(line[17:20].strip() == "GLY" and line[12:16].strip() != "CA"): continue;
        
        residueName = line[17:20].strip()
        chainId = line[21].strip()
        resSeq = int(line[22:26].strip()) - 2
        coord  = ( float(line[30:38].strip()), float(line[38:46].strip()), float(line[46:54].strip()) )
        chain = self.aminoAcid_A if chainId == "A" else self.aminoAcid_B  # assignment doesn't deep copy

        chain[resSeq] = {
          "residueName": residueName,
          "coord": coord,
        }

  def isClose(self, coord_A, coord_B):
    distance = sqrt( sum((a - b)**2 for a, b in zip(coord_A, coord_B)) )
    return distance < 8

  def createPairs(self):
    for (resSeq_A, atom_A) in self.aminoAcid_A.items():
      for (resSeq_B, atom_B) in self.aminoAcid_B.items():      
        if self.isClose(atom_A["coord"], atom_B["coord"]):
          self.pairs.append((resSeq_A, resSeq_B))

  def isSameGroup(self, pair1, pair2):

    #  A1-A2, B1-B2, A1-B2, or A2-B1  
    A1 = self.aminoAcid_A[pair1[0]]["coord"] # O(1)
    B1 = self.aminoAcid_B[pair1[1]]["coord"]
    A2 = self.aminoAcid_A[pair2[0]]["coord"]
    B2 = self.aminoAcid_B[pair2[1]]["coord"]

    resultCond = self.isClose(A1, A2) or self.isClose(B1, B2) or self.isClose(A1, B2) or self.isClose(A2, B1)
    return resultCond

  def addEdge(self, i, j):

    # make an undirected graph
    self.adj[i].append(j) 
    self.adj[j].append(i)

  def DFS(self, temp, v, visited): 
  
    visited[v] = True
    temp.append(v)

    for i in self.adj[v]: 
      if visited[i] == False:
        temp = self.DFS(temp, i, visited) 
    return temp

  def BFS(self, v, visited):

    result, queue = [], []
    queue.append(v)
    result.append(v)
    visited[v] = True

    while queue: 
      v = queue.pop(0)

      for index in self.adj[v]:
        if visited[index] == False: 
          queue.append(index)
          result.append(index)
          visited[index] = True

    return result

  def makeGroup(self):

    self.adj = [[] for i in range(len(self.pairs))] 

    for i in range(len(self.pairs)): # O(n^2) TODO: decrease complexity
      for j in range(len(self.pairs)):
        if(i == j): continue
        if(self.isSameGroup(self.pairs[i], self.pairs[j])):
          self.addEdge(i,j);	

    visited = [False] * (len(self.pairs)) 
    groups = []
    for v in range(len(self.pairs)): 
      if visited[v] == False: 
        groups.append(self.BFS(v, visited)) 
        #groups.append(self.DFS([], v, visited)) # possible stack overflow 
    self.groups = groups
  
  def printGroups(self):

    print(f'There are {len(self.pairs)} interacting pairs.')

    for ind, group in enumerate(self.groups):
      for i in group:
        print("Group {index}: {residueName_A}({resSeq_A})-{residueName_B}({resSeq_B})".format(
          index = ind + 1,
          residueName_A = self.aminoAcid_A[self.pairs[i][0]]["residueName"],
          resSeq_A = self.pairs[i][0],
          residueName_B = self.aminoAcid_B[self.pairs[i][1]]["residueName"],
          resSeq_B = self.pairs[i][1]
        ))

    print(f'Number of groups = {len(self.groups)}')


if __name__ == "__main__":
  
  solution = Assignment3()
  solution.parseFile("4ix3.pdb") # id's are given as "id-2" in the file.
  solution.createPairs()
  solution.makeGroup()
  solution.printGroups()