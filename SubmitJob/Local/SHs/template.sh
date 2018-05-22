#!/bin/sh

run_exec () {
    CMD="$EXEC"; echo ${CMD}; ${CMD};
}

echo "`whoami` @ `hostname` : `pwd`"

CMD="source $SETVAR"; echo ${CMD}; ${CMD};

echo " ------------------------ "
echo " ---------- ENVS -------- "
echo " ------------------------ "
echo ""
env
echo ""
echo " ------------------------ "
echo " ------------------------ "
echo ""

HOME=`pwd`
UNIQUE="$$_$RANDOM"
SANDBOX=/data/$UNIQUE
while [[ -d $SANDBOX ]]; do
    UNIQUE="$$_$RANDOM"
    SANDBOX=/data/$UNIQUE
    echo "Searching for a free SandBox dir !"
done
mkdir -vp $SANDBOX
cd $SANDBOX
pwd

run_exec

ls -altrh
mv -v *.root *.txt ${OUTDIR}
rm -rfv "$SANDBOX"
