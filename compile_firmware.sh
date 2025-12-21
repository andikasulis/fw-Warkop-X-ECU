#!/usr/bin/env bash



export META_OUTPUT_ROOT_FOLDER=$(python3 -c "import os.path; print(os.path.relpath('generated', 'ext/rusefi/firmware'))")/
echo "META_OUTPUT_ROOT_FOLDER=$META_OUTPUT_ROOT_FOLDER"

export AUTOMATION_REF=`git branch --show-current`
cd ext/rusefi/firmware/
bash bin/compile.sh ../../../meta-info.env
