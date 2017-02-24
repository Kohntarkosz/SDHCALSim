import os
import sys
import string
from Ganga import *

j=Job()
j.name = 'Geant4'
j.application = Executable( exe=File('/gridgroup/ilc/garillot/SDHCALSim/script/runElectronsForTuning.py') , args=['arg1','arg2','arg3','arg4'] )
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



energy = [10 , 15 , 20 , 25 , 30 , 40 , 50 , 85]
model = ['FTFP_BERT_HP' , 'QGSP_BERT_HP']

par=[]
args = [ [str(e) , 2000 , s , m] for e in energy for s in range(0,10,1) for m in model ]
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



