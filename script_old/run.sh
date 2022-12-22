#!/bin/bash

trace_names=("alibaba_30" "alibaba_130" "alibaba_150" "alibaba_230" "alibaba_401")
#trace_names=("alibaba_12" "alibaba_100" "alibaba_130" "alibaba_507" "alibaba_538" "alibaba_730" "alibaba_731" "alibaba_743" "alibaba_755" "alibaba_792")
config_names=("inval0_pe3000.txt" "inval0_pe5000.txt" "reco5.0_pe3000.txt" "reco10.0_pe3000.txt" "reco20.0_pe3000.txt" "reco5.0_pe5000.txt" "reco10.0_pe5000.txt" "reco20.0_pe5000.txt")


#for (( i = 0 ; i < ${#trace_names[@]} ; i++ )) ; do
    #echo  >$(pwd)/log/stdout/vanila/"${trace_names[$i]}_3000.txt"
    #echo  >$(pwd)/log/stderr/vanila/"${trace_names[$i]}_3000.txt"
#done

for (( i = 0 ; i < ${#trace_names[@]} ; i++ )) ; do
    echo  >$(pwd)/log/stdout/reco/"${trace_names[$i]}_3000_reco10.0.txt"
    echo  >$(pwd)/log/stderr/reco/"${trace_names[$i]}_3000_reco10.0.txt"
    echo  >$(pwd)/log/stdout/reco/"${trace_names[$i]}_3000_reco20.0.txt"
    echo  >$(pwd)/log/stderr/reco/"${trace_names[$i]}_3000_reco20.0.txt"
done

echo 'alibaba_30 alibaba_130 alibaba_150 alibaba_230 alibaba_401 3000 5000'

for (( i = 0 ; i < ${#trace_names[@]} ; i++ )) ; do
    #python3 script_ali.py ${trace_names[$i]} 3000 >>$(pwd)/log/stdout/vanila/"${trace_names[$i]}_3000.txt" 2>>$(pwd)/log/stderr/vanila/"${trace_names[$i]}_3000.txt" &
    python3 script_ali_reco.py ${trace_names[$i]} 3000 10.0 >>$(pwd)/log/stdout/reco/"${trace_names[$i]}_3000_reco10.0.txt" 2>>$(pwd)/log/stderr/reco/"${trace_names[$i]}_3000_reco10.0.txt" &
    python3 script_ali_reco.py ${trace_names[$i]} 3000 20.0 >>$(pwd)/log/stdout/reco/"${trace_names[$i]}_3000_reco20.0.txt" 2>>$(pwd)/log/stderr/reco/"${trace_names[$i]}_3000_reco20.0.txt" &

done