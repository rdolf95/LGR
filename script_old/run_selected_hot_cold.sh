#!/bin/bash

#trace_names=("alibaba_12" "alibaba_100" "alibaba_130" "alibaba_538" "alibaba_730" "alibaba_731" "alibaba_743")
trace_names=("alibaba_507" "alibaba_792")

for (( i = 0 ; i < ${#trace_names[@]} ; i++ )) ; do
    echo  >$(pwd)/log/stdout/hot_cold/"${trace_names[$i]}_3000.txt"
    echo  >$(pwd)/log/stderr/hot_cold/"${trace_names[$i]}_3000.txt"
done

for (( i = 0 ; i < ${#trace_names[@]} ; i++ )) ; do
    python3 script_ali_selected_hot_cold.py ${trace_names[$i]} 3000 >>$(pwd)/log/stdout/hot_cold/"${trace_names[$i]}_3000.txt" 2>>$(pwd)/log/stderr/hot_cold/"${trace_names[$i]}_3000.txt" &
done

#"alibaba_507"