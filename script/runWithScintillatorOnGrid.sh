#!/bin/bash

particle=$1
energy=$2
nevent=$3
seed=$4
model=$5
version=$6

source /gridgroup/ilc/garillot/SDHCALSim/script/loadG4Version.sh ${version}

export SIMEXE=${SIMDIR}/SDHCALSimWithScintillator

source /gridgroup/ilc/garillot/SDHCALSim/script/run.sh ${particle} ${energy} ${nevent} ${seed} ${model}


#upload

filenameslcio=single_${particle}_${energy}GeV_I${seed}.slcio
filenameroot=single_${particle}_${energy}GeV_I${seed}.root

mv wScintillator.slcio ${filenameslcio}
mv wScintillator.root ${filenameroot}

location=/grid/calice/SDHCAL/garillot/SimCalorimeterHit/WithScintillator/Geant4.${version}/${model}

./gridgroup/ilc/garillot/uploadOnGrid.py ${filenameslcio} ${location}
./gridgroup/ilc/garillot/uploadOnGrid.py ${filenameslcio} ${location}/ControlFiles

rm ${filenameslcio}
rm ${filenameroot}
rm OldwScintillator.slcio

