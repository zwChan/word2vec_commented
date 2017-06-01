import sys,re,os,gzip
from collections import defaultdict

"""
Transform the output of Stanford NLP dependency parsing to input of word2vecf
-------------------------
input example:
nsubj(Inhibits-2, Losartan-1)
root(ROOT-0, Inhibits-2)
amod(Activation-5, Nuclear-3)
compound(Activation-5, Factor-B-4)
dobj(Inhibits-2, Activation-5)

output:

"""
print(sys.argv)
if len(sys.argv) < 4:
   print (
   """
   args: vocab-file input-dir  output-dir filter-of-input-filename
   """
   )
   sys.exit(1)


vocab_file = sys.argv[1]
dir_in = sys.argv[2]
filter = sys.argv[4]
dir_out = sys.argv[3]
lower=True

def read_vocab(fh):
   v = {}
   for line in fh:
      if lower: line = line.lower()
      line = line.strip().split()
      if len(line) != 2: continue
      v[line[0]] = int(line[1])
   return v

vocab = set(read_vocab(file(vocab_file)).keys())
print >> sys.stderr,"vocab:",len(vocab)

def transform(f,of):
   rWordExtract = re.compile( "(\\w+)\\((\\S+)-\\d+, (\\S+)-\\d+\\)")
   i = 1
   for l in f.readlines():
      if i % 100000 == 0: print >> sys.stderr,i
      m = rWordExtract.findall(l.strip())
      if (len(m) > 0 and len(m[0]) == 3):
         i += 1
         rel,head,mod = m[0]
         head = head.strip()
         mod  = mod.strip()
         rel  = rel.strip()

         if mod not in vocab: continue
         if rel == 'adpmod': continue # this is the prep. we'll get there (or the PP is crappy)
         if rel == 'punct': continue
         if head not in vocab: continue
         # print head,"_".join((rel,mod))
         # print mod,"I_".join((rel,head))
         of.write("%s %s_%s\n" % (head,rel,mod))
         of.write("%s %sI_%s\n" % (mod,rel,head))


def walk_dir(dir_in,func,filter,dir_out):
    rfilter = re.compile(filter)
    for root, dirs, files in os.walk(dir_in, True):
        for name in files:
            filePath = os.path.join(root,name)
            ofPath = os.path.join(dir_out,"wc_" + name)
            if rfilter.match(filePath) is None: continue
            print("processing: %s" %(filePath))
            if (filePath.endswith('.gz')):
               with gzip.open(filePath,'r') as f:
                  with gzip.open(ofPath,'w+') as of:
                     func(f,of)
            else:
               with open(filePath,'r') as f:
                   with open(ofPath,'w+') as of:
                     func(f,of)

walk_dir(dir_in, transform, filter, dir_out)

