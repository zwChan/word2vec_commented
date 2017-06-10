import sys
from infer import Embeddings

embeddingFile = sys.argv[1]
analogiesFile = sys.argv[2]
e = Embeddings.load(embeddingFile)
questions = file(analogiesFile)

for line in questions:
   cat, q1,q2,q3,a = line.lower().strip().split()
   try:
      print cat,q1,q2,q3,a,e.analogy(q2,q1,q3,1)[1]
   except:
      print "MISSING"
