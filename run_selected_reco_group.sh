#!/bin/bash

#trace_names=("alibaba_12" "alibaba_100" "alibaba_130" "alibaba_507" "alibaba_538" "alibaba_730" "alibaba_731" "alibaba_743" "alibaba_792" "alibaba_124" "alibaba_806")
#trace_names=("alibaba_507" "alibaba_792")
#trace_names=("alibaba_507")
#trace_names=("alibaba_727" "alibaba_804" "alibaba_806")
trace_names=("alibaba_100" "alibaba_130" "alibaba_538" "alibaba_730" "alibaba_743" "alibaba_792" "alibaba_806" "alibaba_727")


for (( i = 0 ; i < ${#trace_names[@]} ; i++ )) ; do
    echo  >$(pwd)/log/stdout/group/reco10.0/"${trace_names[$i]}_3000.txt"
    echo  >$(pwd)/log/stderr/group/reco10.0/"${trace_names[$i]}_3000.txt"
done

for (( i = 0 ; i < ${#trace_names[@]} ; i++ )) ; do
    python3 script_ali_selected_group.py ${trace_names[$i]} 3000 >>$(pwd)/log/stdout/group/reco10.0/"${trace_names[$i]}_3000.txt" 2>>$(pwd)/log/stderr/group/reco10.0/"${trace_names[$i]}_3000.txt" &
done
