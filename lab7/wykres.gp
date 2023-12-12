#!/usr/bin/gnuplot 

set term png enhanced size 600,300 

set size ratio -1
set dgrid3d
set o "psi-1000.png"
set contour
#set cntrparam levels 40 # lub ponizsze:
set cbr [-200:350]
set cntrparam levels increment -200,1,350
unset surface
set view map
unset key
splot "q2.txt" u 1:2:3 w l lt -1 palette  t '' 

