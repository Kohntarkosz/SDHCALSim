#!/bin/bash

particle=$1
energy=$2
nevent=$3
seed=$4
model=$5
version=$6

source /gridgroup/ilc/garillot/SDHCALSim/script/loadG4Version.sh ${version}

export SIMEXE=${SIMDIR}/SDHCALSim

source /gridgroup/ilc/garillot/SDHCALSim/script/run.sh ${particle} ${energy} ${nevent} ${seed} ${model}


#upload

filenameslcio=single_${particle}_${energy}GeV_I${seed}.slcio
filenameroot=single_${particle}_${energy}GeV_I${seed}.root

mv test.slcio ${filenameslcio}
mv test.root ${filenameroot}

#location=/grid/calice/SDHCAL/garillot/SimCalorimeterHit/Geant4.${version}/${model}
location=/grid/calice/SDHCAL/garillot/PolyaStudies/SimCalorimeterHit

./gridgroup/ilc/garillot/uploadOnGrid.py ${filenameslcio} ${location}
./gridgroup/ilc/garillot/uploadOnGrid.py ${filenameslcio} ${location}/ControlFiles

rm ${filenameslcio}
rm ${filenameroot}
rm test.slcio



#source /gridgroup/ilc/garillot/SDHCALSim/script/uploadFilesToGrid.sh single_${particle}_${energy}GeV_I${seed} /grid/calice/SDHCAL/garillot/SimCalorimeterHit/Geant4.${version}/${model}


