#! /bin/sh
file1=liaen3_fair.txt
file2=lia_fair.txt
file3=olia_fair.txt
file4=mpwest_fair.txt
file5=mpveno_fair.txt
output=fair-reno-noloss
gnuplot<<!
set grid
set key bottom left
set xlabel "index" 
set ylabel "Jain's fairness index"
set xtics -1,1,8
set yrange [0.92:1.01]
set term "pdf"
set output "${output}-fair.pdf"
plot "${file1}" u 1:2 title "liaen" with lines lw 2,\
"${file2}" u 1:2 title "lia" with lines lw 2 ,\
"${file4}" u 1:2 title "mWestwood" with linespoints lw 2,\
"${file5}" u 1:2 title "MPVeno" with linespoints lw 2
set output
exit
!
gnuplot<<!
set grid
set key bottom left
set xlabel "index" 
set ylabel "Jain's fairness index"
set xtics -1,1,8
set yrange [0.92:1.01]
set term "png"
set output "${output}-fair.png"
plot "${file1}" u 1:2 title "liaen" with lines lw 2,\
"${file2}" u 1:2 title "lia" with lines lw 2 ,\
"${file4}" u 1:2 title "mWestwood" with linespoints lw 2,\
"${file5}" u 1:2 title "MPVeno" with linespoints lw 2
set output
exit
!

