#!/bin/bash

export LFC_HOST=grid-lfc.desy.de

filename=$1
location=$2

echo UploadFilesToGrid
echo ${filename}
echo ${location}

filenameslcio=${filename}.slcio
filenameroot=${filename}.root

mv test.slcio ${filenameslcio}
mv test.root ${filenameroot}

STORAGE_SITE=lyogrid06.in2p3.fr

source /gridgroup/ilc/Arnaud/carefulUpload.sh ${filenameslcio} ${location}
source /gridgroup/ilc/Arnaud/carefulUpload.sh ${filenameroot} ${location}/ControlFiles

#lcg-del -a --vo calice lfn:${location}/${filename}.slcio
#lcg-cr --vo calice -d $STORAGE_SITE file:./${filename}.slcio -l lfn:${location}/${filename}.slcio

#lcg-del -a --vo calice lfn:${location}/ControlFiles/${filename}.root
#lcg-cr --vo calice -d $STORAGE_SITE file:./${filename}.root -l lfn:${location}/ControlFiles/${filename}.root

rm ${filenameslcio}
rm ${filenameroot}
rm Oldtest.slcio
