#!/bin/bash

trace_names=("alibaba_12" "alibaba_100" "alibaba_130" "alibaba_507" "alibaba_538" "alibaba_730" "alibaba_731" "alibaba_743" "alibaba_792" "alibaba_124" "alibaba_806")
#trace_names=("alibaba_507" "alibaba_792")
#trace_names=("alibaba_507")
#trace_names=("alibaba_124" "alibaba_806" "alibaba_823")

for (( i = 0 ; i < ${#trace_names[@]} ; i++ )) ; do
    echo  >$(pwd)/log/stdout/temp/"${trace_names[$i]}_3000.txt"
    echo  >$(pwd)/log/stderr/temp/"${trace_names[$i]}_3000.txt"
    #echo  >$(pwd)/log/stdout/reco30.0/"${trace_names[$i]}_3000.txt"
    #echo  >$(pwd)/log/stderr/reco30.0/"${trace_names[$i]}_3000.txt"
    #echo  >$(pwd)/log/stdout/reco40.0/"${trace_names[$i]}_3000.txt"
    #echo  >$(pwd)/log/stderr/reco40.0/"${trace_names[$i]}_3000.txt"
done

for (( i = 0 ; i < ${#trace_names[@]} ; i++ )) ; do
    python3 script_ali_selected.py ${trace_names[$i]} 3000 >>$(pwd)/log/stdout/temp/"${trace_names[$i]}_3000.txt" 2>>$(pwd)/log/stderr/temp/"${trace_names[$i]}_3000.txt" &
    #python3 script_ali_selected.py ${trace_names[$i]} 3000 >>$(pwd)/log/stdout/14days/vanila/"${trace_names[$i]}_3000.txt" 2>>$(pwd)/log/stderr/14days/vanila/"${trace_names[$i]}_3000.txt" &
    #python3 script_ali_reco_selected.py ${trace_names[$i]} 3000 10.0 >>$(pwd)/log/stdout/reco10.0/"${trace_names[$i]}_3000.txt" 2>>$(pwd)/log/stderr/reco10.0/"${trace_names[$i]}_3000.txt" &
    #python3 script_ali_reco_selected.py ${trace_names[$i]} 3000 5.0 >>$(pwd)/log/stdout/reco5.0/"${trace_names[$i]}_3000.txt" 2>>$(pwd)/log/stderr/reco5.0/"${trace_names[$i]}_3000.txt" &
    #python3 script_ali_reco_selected.py ${trace_names[$i]} 3000 20.0 >>$(pwd)/log/stdout/reco20.0/"${trace_names[$i]}_3000.txt" 2>>$(pwd)/log/stderr/reco20.0/"${trace_names[$i]}_3000.txt" &
    #python3 script_ali_reco_selected.py ${trace_names[$i]} 3000 30.0 >>$(pwd)/log/stdout/reco30.0/"${trace_names[$i]}_3000.txt" 2>>$(pwd)/log/stderr/reco30.0/"${trace_names[$i]}_3000.txt" &
    #python3 script_ali_reco_selected.py ${trace_names[$i]} 3000 40.0 >>$(pwd)/log/stdout/reco40.0/"${trace_names[$i]}_3000.txt" 2>>$(pwd)/log/stderr/reco40.0/"${trace_names[$i]}_3000.txt" &

    #python3 script_ali_reco_selected.py ${trace_names[$i]} 3000 20.0 >>$(pwd)/log/stdout/reco20.0/"${trace_names[$i]}_3000.txt" 2>>$(pwd)/log/stderr/reco20.0/"${trace_names[$i]}_3000.txt" &
done
