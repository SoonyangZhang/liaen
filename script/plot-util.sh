#! /bin/sh
loss=l50
file1=liaen3${loss}_util.txt
file2=lia${loss}_util.txt
file3=olia${loss}_util.txt
file4=mpwest${loss}_util.txt
file5=mpveno${loss}_util.txt
output=${loss}
gnuplot<<!
set key bottom left
set xlabel "index" 
set ylabel "utility"
set xtics -1,1,8
set yrange [0.2:1.2]
set grid
set term "pdf"
set output "${output}-util.pdf"
plot "${file1}" u 1:2 title "liaen" with lines lw 2 lc 1,\
"${file2}" u 1:2 title "lia" with lines lw 2 lc 2,\
"${file3}" u 1:2 title "olia" with lines lw 2 lc 3,\
"${file4}" u 1:2 title "mWestwood" with lines lw 2 lc 4,\
"${file5}" u 1:2 title "MPVeno" with lines lw 2 lc 6
set output
exit
!


