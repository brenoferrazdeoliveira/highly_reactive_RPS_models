set terminal tikz size 8.4cm, 4.0cm fontscale 0.8 fulldoc \
header "\\usepackage{amsmath}"
set output sprintf("dst-%d.tex", @ARG1)

set xlabel offset 0.0, 0.0 "$t$"
set ylabel offset 0.0, 0.0 "$\\rho_\\mu$"
set ytics offset 1.0, 0.0 0.15
set xtics offset 0.0, 0.0 
set key at graph 0.38, 0.9 reverse Left samplen 1 width 2 horizontal center

set xrange [1000:6000]
set yrange [0.0:0.75]

set label "HC - $ABC$" at  5800, 0.62 right 

plot \
sprintf("../dat/dst-%d.dat", @ARG1) u ($0+1000):($1) w l lw 2.0 lc rgb "#A80966" t"$\\rho_A$",\
sprintf("../dat/dst-%d.dat", @ARG1) u ($0+1000):($2) w l lw 2.0 lc rgb "#00337A" t"$\\rho_B$",\
sprintf("../dat/dst-%d.dat", @ARG1) u ($0+1000):($3) w l lw 2.0 lc rgb "#DF9800" t"$\\rho_C$",\
sprintf("../dat/dst-%d.dat", @ARG1) u ($0+1000):($4) w l lw 2.0 lc rgb "#808080" t"$\\rho_E$"

unset output
