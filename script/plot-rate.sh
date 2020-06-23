#! /bin/sh
loss=l10
file1=treeliaen3${loss}_rate.txt
file2=treelia${loss}_rate.txt
file3=treeolia${loss}_rate.txt
file4=treempwest${loss}_rate.txt
file5=treempveno${loss}_rate.txt
output=subflow-${loss}
gnuplot<<!
set key top left
set xlabel "index" 
set ylabel "rate/kbps"
set xtics -1,1,8
set yrange [500:2500]
set grid
set term "pdf"
set output "${output}-rate.pdf"
plot "${file1}" u 1:2 title "liaen" with linespoints lw 2 ,\
"${file2}" u 1:2 title "lia" with linespoints lw 2 ,\
"${file4}" u 1:2 title "mWestwood" with linespoints lw 2 ,\
"${file5}" u 1:2 title "MPVeno" with linespoints lw 2 
set output
exit
!

gnuplot<<!
set key top left
set xlabel "index" 
set ylabel "rate/kbps"
set xtics -1,1,8
set yrange [500:2500]
set grid
set term "png"
set output "${output}-rate.png"
plot "${file1}" u 1:2 title "liaen" with linespoints lw 2 ,\
"${file2}" u 1:2 title "lia" with linespoints lw 2 ,\
"${file4}" u 1:2 title "mWestwood" with linespoints lw 2 ,\
"${file5}" u 1:2 title "MPVeno" with linespoints lw 2 
set output
exit
!



