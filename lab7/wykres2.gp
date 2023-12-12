#!/usr/bin/gnuplot 

set term png enhanced size 600,300 

set size ratio -1
set dgrid3d
set o "ksi-1000.png"
set contour
#set cntrparam levels 40 # lub ponizsze:
set cbr [-55:-50]
set cntrparam levels increment -55,0.5,-50
unset surface
set view map
unset key
splot "q1.txt" u 1:2:3 w l lt -1 palette  t '' 
