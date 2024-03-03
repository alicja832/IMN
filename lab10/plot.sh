# Skrypt gnuplot do generowania wykresu energii od czasu

reset

set term png size 4000,2000 enhanced font "Helvetica, 24" lw 2
#set size 1,1
#set size square
set lmargin  4.5
set bmargin  4.0
set rmargin  4.5
set tmargin  4.0


set out "lab10.png"
set grid
set multiplot layout 2,3

set title "E(t)"      # Tytuł wykresu
set xlabel "t"                        # Oś X - Czas
set ylabel "E"                      # Oś Y - Energia
set yrange [0:0.9]                    # Zakres dla osi Y

# Wczytaj dane z pliku
plot 'E0.100000.txt' using 1:2 with lines title '{/Symbol b} =0.1',\
 'E1.000000.txt' using 1:2 with lines title '{/Symbol b} =1.0',\
 'E0.000000.txt' using 1:2 with lines title '{/Symbol b} =0.0'
#------------------------------------------------------------------------

set title "E(t),{/Symbol a} = 1"      # Tytuł wykresu
set xlabel "t"                        # Oś X - Czas
set ylabel "E"                      # Oś Y - Energia
set yrange [0:0.0035]                    # Zakres dla osi Y

# Wczytaj dane z pliku
plot 'Ea1.000000.txt' using 1:2 with lines title '{/Symbol b} =1.0 {/Symbol a} =1.0'

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
set cbrange[-1:1]
set title '{/Symbol b}=0.0,{/Symbol a} =0.0'
set xlabel 'x'
set ylabel 'y'

splot [0:50][0:16] "U0.000000.txt" u 1:2:3 notitle

set cbrange[-1:1]
set title '{/Symbol b}=0.1,{/Symbol a} =0.0'
set xlabel 'x'
set ylabel 'y'

splot  [0:50][0:16] "U0.100000.txt" u 1:2:3 notitle

set cbrange[-0.2:1.2]
set title '{/Symbol b}=1.0,{/Symbol a} =0.0'
set xlabel 'x'
set ylabel 'y'

splot  [0:50][0:16] "U1.000000.txt" u 1:2:3 notitle


set cbrange[-0.05:0.04]
set title '{/Symbol b}=1.0,{/Symbol a} =1.0'
set xlabel 'x'
set ylabel 'y'

splot  [0:50][0:16] "Ua1.000000.txt" u 1:2:3 notitle


