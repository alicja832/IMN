#set term postscript size 20cm, 40cm color enhanced solid font "Helvetica, 10"

#
#
#   plik z danymi: x, y, u(x,y)
#
#
reset
set term png size 3000,2000 enhanced font "Helvetica, 24" lw 2
#set size 1,1
#set size square

set lmargin  4.5
set bmargin  4.0
set rmargin  4.5
set tmargin  4.0
set size square


set out "T.png"
set grid
set multiplot layout 2,5

set grid
#set object 1 rect from 0,0 to 0.5,0.55 fs solid noborder fc rgb "black" front # przeszkoda

#------------------------------------------------------------------------

set pm3d
set view map
unset surface

set palette rgbformulae 7,5,15 # paleta kolorow
#set palette rgbformulae 22,13,-31
#set palette rgbformulae 33,13,10

#set palette defined (-2 "blue", 0 "white", 16 "red")


#------------------------------------------------------------------------
set cbrange[0:40]
set title 'it=100'
set xlabel 'x'
set ylabel 'y'

splot [0:40][0:40] "T.dat" u 1:2:3 i 0 notitle

set cbrange[0:40]
set title 'it=200'
set xlabel 'x'
set ylabel 'y'

splot [0:40][0:40] "T.dat" u 1:2:3 i 1 notitle

# #------------------------------------------------------------------------
set cbrange[0:40]
set title 'it=500'
set xlabel 'x'
set ylabel 'y'

splot [0:40][0:40] "T.dat" u 1:2:3 i 2 notitle

#------------------------------------------------------------------------
set cbrange[0:40]
set title 'it=1000'
set xlabel 'x'
set ylabel 'y'

splot [0:40][0:40] "T.dat" u 1:2:3 i 3 notitle

# #------------------------------------------------------------------------
set cbrange[0:40]
set title 'it=2000'
set xlabel 'x'
set ylabel 'y'

splot [0:40][0:40] "T.dat" u 1:2:3 i 4 notitle

#------------------------------------------------------------------------
set cbrange[0:0.12]
set title 'it=100'
set xlabel 'x'
set ylabel 'y'

splot [0:40][0:40] "dT.dat" u 1:2:3 i 0 notitle

#------------------------------------------------------------------------

#set title 'u(x,y) it=3000, t='
#set xlabel 'x'
#set ylabel 'y'

#splot [0:400][0:90] "u_t.dat" u 1:2:3 i 2 notitle

#------------------------------------------------------------------------

#set title 'u(x,y) it=, t='
#set xlabel 'x'
#set ylabel 'y'

#splot [0:400][0:90] "u_t.dat" u 1:2:3 i 3 notitle

#------------------------------------------------------------------------


# # #------------------------------------------------------------------------
set cbrange[0:0.045]
set title 'it=200'
set xlabel 'x'
set ylabel 'y'

splot [0:40][0:40] "dT.dat" u 1:2:3 i 1 notitle

# #------------------------------------------------------------------------

# #set title 'u(x,y) it=5000, t='
# #set xlabel 'x'
# #set ylabel 'y'

# #splot [0:400][0:90] "u_t.dat" u 1:2:3 i 5 notitle


# #------------------------------------------------------------------------
set cbrange[0:0.0025]
set title 'it=500'
set xlabel 'x'
set ylabel 'y'

splot [0:40][0:40] "dT.dat" u 1:2:3 i 2 notitle

#------------------------------------------------------------------------

#set title 'u(x,y) it=7000, t='
#set xlabel 'x'
#set ylabel 'y'

#splot [0:400][0:90] "u_t.dat" u 1:2:3 i 7 notitle



# #------------------------------------------------------------------------
set cbrange[0:0.000016]
set title 'it=1000'
set xlabel 'x'
set ylabel 'y'

splot [0:40][0:40] "dT.dat" u 1:2:3 i 3 notitle
# #------------------------------------------------------------------------

# #set title 'u(x,y) it=9000, t='
# #set xlabel 'x'
# #set ylabel 'y'

# #splot [0:400][0:90] "u_t.dat" u 1:2:3 i 8 notitle


# # #------------------------------------------------------------------------
set cbrange[0:0.0000000007]
set title 'it=2000'
set xlabel 'x'
set ylabel 'y'

splot [0:40][0:40] "dT.dat" u 1:2:3 i 4 notitle

#------------------------------------------------------------------------



unset multiplot
reset

