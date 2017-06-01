import sys,os
from collections import Counter
import re,string
import gzip
if len(sys.argv) < 4:
   print (
   """
   args: threshold   input-dir  output-path filter-of-input-filename
   """
   )
   sys.exit(1)

print (sys.argv)
wc = Counter()
thr = int(sys.argv[1])
dir = sys.argv[2]
outputFile= sys.argv[3]
filter = sys.argv[4]
wCnt = 0

def count(f):
   global wc,wCnt
   # amod(agents-7, anti-HIV-1-6)
   rWordExtract = re.compile("(\\w+)\\((\\S+)-\\d+, (\\S+)-\\d+\\)")
   for l in f.readlines():
      wCnt += 1
      if wCnt % 1000000 == 0:
         print >> sys.stderr,wCnt,len(wc)
      m = rWordExtract.findall(l.strip())
      #print m
      if (len(m) > 0 and len(m[0]) == 3):
         rel,head,mod = m[0]
         if len(head.strip(string.punctuation)) == 0 or len(mod.strip(string.punctuation))==0: continue
         wc.update((head.strip(),))
         wc.update((mod.strip(),))


def output(wc,outputFile):
   with open(outputFile,'w+') as of:
      for w,c in sorted([(w,c) for w,c in wc.iteritems() if c >= thr and w != ''],key=lambda x:-x[1]):
         # print "%s\t%d\n" % (w,c)
         of.write("%s\t%d\n" % (w,c))

def walk_dir(dir,func,filter):
    rfilter = re.compile(filter)
    for root, dirs, files in os.walk(dir, True):
        for name in files:
            filePath = os.path.join(root,name)
            if rfilter.match(filePath) is None: continue
            print("processing: %s" %(filePath))
            if (filePath.endswith('.gz')):
               with gzip.open(filePath,'r') as f:
                  func(f)
            else:
               with open(filePath,'r') as f:
                  func(f)

walk_dir(dir, count, filter)
output(wc,outputFile)
