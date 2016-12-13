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

source /gridgroup/ilc/garillot/newUpload.sh ${filenameslcio} ${location}
source /gridgroup/ilc/garillot/newUpload.sh ${filenameroot} ${location}/ControlFiles

rm ${filenameslcio}
rm ${filenameroot}
rm Oldtest.slcio
