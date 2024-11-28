set terminal tikz size 8.4cm, 4.5cm fontscale 0.8 fulldoc \
header "\\usepackage{amsmath}"
set output "dft.tex"

set xlabel offset 0.0, 0.0 "$f$"
set ylabel offset 0.0, 0.0 "$10^{-5}\\times\\langle|\\rho_\\mu(f)|\\rangle^2$"
set ytics offset 1.0, 0.0 
set xtics offset 0.0, 0.0 20
set key at graph 0.85, 0.75 reverse Left samplen 1 width 2 center spacing 1.5

set xrange [1:200]
set yrange [0:10]

set label "HC - $ABC$" at 180, 2 right 

plot \
"../dat/dft-avg.dat" u ($0):($1*1.0e+5) w l lw 2.0 lc rgb "#A80966" t"$\\rho_A$",\
"../dat/dft-avg.dat" u ($0):($3*1.0e+5) w l lw 2.0 lc rgb "#00337A" t"$\\rho_B$",\
"../dat/dft-avg.dat" u ($0):($5*1.0e+5) w l lw 2.0 lc rgb "#DF9800" t"$\\rho_C$"

unset output
