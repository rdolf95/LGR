#!/bin/bash

#trace_names=("alibaba_12" "alibaba_100" "alibaba_130" "alibaba_507" "alibaba_538" "alibaba_730" "alibaba_731" "alibaba_743" "alibaba_792" "alibaba_124" "alibaba_806")
#trace_names=("alibaba_507" "alibaba_792")
#trace_names=("alibaba_507")
#trace_names=("alibaba_727" "alibaba_804" "alibaba_806")
#trace_names=( "alibaba_810")
trace_names=("alibaba_100" "alibaba_130" "alibaba_538" "alibaba_730" "alibaba_743" "alibaba_792" "alibaba_806")


for (( i = 0 ; i < ${#trace_names[@]} ; i++ )) ; do
    #echo  >$(pwd)/log/stdout/reco1.0/"${trace_names[$i]}_3000.txt"
    #echo  >$(pwd)/log/stderr/reco1.0/"${trace_names[$i]}_3000.txt"
    #echo  >$(pwd)/log/stdout/reco2.0/"${trace_names[$i]}_3000.txt"
    #echo  >$(pwd)/log/stderr/reco2.0/"${trace_names[$i]}_3000.txt"
    echo  >$(pwd)/log/stdout/reco30.0/"${trace_names[$i]}_3000.txt"
    echo  >$(pwd)/log/stderr/reco30.0/"${trace_names[$i]}_3000.txt"
    echo  >$(pwd)/log/stdout/reco40.0/"${trace_names[$i]}_3000.txt"
    echo  >$(pwd)/log/stderr/reco40.0/"${trace_names[$i]}_3000.txt"
done

for (( i = 0 ; i < ${#trace_names[@]} ; i++ )) ; do
    #python3 script_ali_reco_selected.py ${trace_names[$i]} 3000 1.0 >>$(pwd)/log/stdout/reco1.0/"${trace_names[$i]}_3000.txt" 2>>$(pwd)/log/stderr/reco1.0/"${trace_names[$i]}_3000.txt" &
    #python3 script_ali_reco_selected.py ${trace_names[$i]} 3000 2.0 >>$(pwd)/log/stdout/reco2.0/"${trace_names[$i]}_3000.txt" 2>>$(pwd)/log/stderr/reco2.0/"${trace_names[$i]}_3000.txt" &
    python3 script_ali_reco_selected.py ${trace_names[$i]} 3000 30.0 >>$(pwd)/log/stdout/reco30.0/"${trace_names[$i]}_3000.txt" 2>>$(pwd)/log/stderr/reco30.0/"${trace_names[$i]}_3000.txt" &
    python3 script_ali_reco_selected.py ${trace_names[$i]} 3000 40.0 >>$(pwd)/log/stdout/reco40.0/"${trace_names[$i]}_3000.txt" 2>>$(pwd)/log/stderr/reco40.0/"${trace_names[$i]}_3000.txt" &
done
