import os
import sys
import string
from Ganga import *

j=Job()
j.name = 'Geant4'
j.application = Executable( exe=File('/gridgroup/ilc/garillot/SDHCALSim/script/runWithScintillatorOnGrid.sh') , args=['arg1','arg2','arg3','arg4','arg5','arg6'] )
j.backend='CREAM'
j.backend.CE='lyogrid07.in2p3.fr:8443/cream-pbs-calice'
j.comment = 'Geant4 sim'

def frange(x, y, jump) :
    while y >= x - 1e-10 :
        if abs( round(y,0)-y ) < 1e-10 :
            yield int( round(y,0) )
        else :
            yield y
        y -= jump


particle=['pi-']
energy=[90,80,70,60,50,40,30,20,10,9,8,7,6,5,4,3,2,1]
model=['FTFP_BERT_HP']
version=['9.6']

par=[]


args = [ [p , str(e) , 2000 , s , m , v] for p in particle for e in energy for s in range(1,11) for m in model for v in version ]
for a in args :
    par.append(a)


par
s = ArgSplitter()
s.args=par
j.splitter=s

j.submit()

for subj in j.subjobs :
	subjComment = ""
	for arg in subj.application.args :
		subjComment = subjComment + " " + str(arg)
	subj.comment = str(subjComment)



