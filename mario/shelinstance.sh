#!/bin/sh
# shelscript for generating the needed files for testing the complexity


myPhraseProc="Enter the minimum number of processes wanted (minimum 2)"
myPhraseProcMax="Enter the max number of processes wanted (has to be bigger than the last number inserted"
myPhraseNumFinalFiles="Enter the number of files you want to generate"
myPhraseStaticCost="Enter the max amount for processes (it will be fixed for all tests needs to be a positive num)"
errorMessage1="The maximum number of processes is lower the the smalest"
errorMessage2="The minimum number of processes is 2, including it"

limitProc=2
#echo $limitProc

echo $myPhraseProc
read minProc
echo "[DEBUG] minProc: $minProc"

echo $myPhraseProcMax
read maxProc
echo "[DEBUG] maxProx: $maxProc"

echo $myPhraseNumFinalFiles
read numFinalFilesProc
echo "[DEBUG] finalProc: $numFinalFilesProc"

echo $myPhraseStaticCost
read maxProcCost
echo "[DEBUG] minProc: $maxProcCost"

if [ "$minProc" -lt "$limitProc" ]
then 
    echo $errorMessage2
fi

if [ "$maxProc" -lt "$minProc" ] 
then
    echo $errorMessage1
    exit -1
fi

aux=$( expr $maxProc - $minProc)

step=expr $aux/$myNumFinalFiles #error here
echo "[debug] step: $step"

while [ $minProc -le $maxProc ] 
do
    ./gen2proc $minProc $maxProcCost > numProc${minProc}-cost${cost}.txt
    exit -1
    minProc=$( expr $minProc + $step )
done