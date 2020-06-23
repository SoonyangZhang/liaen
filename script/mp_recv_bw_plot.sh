#! /bin/sh
instance=3
algo=liaen3
file1=mp_${algo}_bw_${instance}.txt
file2=${instance}_${algo}_2_dur_bw.txt
file3=${instance}_${algo}_3_dur_bw.txt
file4=${instance}_${algo}_1_dur_bw.txt
file5=${instance}_${algo}_4_dur_bw.txt
output=${algo}-${instance}-reno
gnuplot<<!
set xlabel "time/s" 
set ylabel "rate/kbps"
set xrange [0:300]
set yrange [0:5000]
set term "pdf"
set output "${output}-mp-recv.pdf"
plot "${file1}" u 1:2 title "mp" with lines lw 2 lc 1,\
"${file2}" u 1:2 title "flow2" with lines lw 2 lc 2,\
"${file3}" u 1:2 title "flow3" with lines lw 2 lc 3,\
"${file4}" u 1:2 title "subflow1" with lines lw 2 lc 4,\
"${file5}" u 1:2 title "subflow2" with lines lw 2 lc 6
set output
exit
!


