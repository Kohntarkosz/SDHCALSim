#!/bin/bash

particle=$1
energy=$2
nevent=$3
seed=$4
model=$5
version=$6

source /gridgroup/ilc/garillot/SDHCALSim/script/loadG4Version.sh ${version}

source /gridgroup/ilc/garillot/SDHCALSim/script/run.sh ${particle} ${energy} ${nevent} ${seed} ${model}

source /gridgroup/ilc/garillot/SDHCALSim/script/uploadFilesToGrid.sh single_${particle}_${energy}GeV_I${seed} /grid/calice/SDHCAL/garillot/SimCalorimeterHit/Geant4.${version}/${model}


