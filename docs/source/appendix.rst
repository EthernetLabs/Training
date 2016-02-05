.. _appendix:

.. _gnu_plot:

Settings GNU-Plot
=================


--------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#!/usr/bin/gnuplot

#

# Plot trigonometric functions with Gnuplot. 

#

# AUTHOR: Hagen Wierstorf 

reset

# wxt

set terminal wxt size 350,262 enhanced font 'Verdana,10' persist

# png

#set terminal pngcairo size 350,262 enhanced font 'Verdana,10'

#set output 'plotting_functions.png'

# svg

#set terminal svg size 350,262 fname 'Verdana, Helvetica, Arial, sans-serif' \

#fsize '10'

#set output 'plotting_functions.svg'

# Line styles

set border linewidth 1.5

set style line 1 linecolor rgb '#0060ad' linetype 1 linewidth 2  # blue

set style line 2 linecolor rgb '#dd181f' linetype 1 linewidth 2  # red

# Legend

set key at 6.1,1.3

# Axes label 

set xlabel 'x'

set ylabel 'y'

# Axis ranges

set xrange[-2*pi:2*pi]

set yrange[-1.5:1.5]

# Axis labels

set xtics ("-2Ï€" -2*pi, "-Ï€" -pi, 0, "Ï€" pi, "2Ï€" 2*pi)

set ytics 1

set tics scale 0.75

# Functions to plot

a = 0.9

f(x) = a * sin(x)

g(x) = a * cos(x)

# Plot

plot f(x) title 'sin(x)' with lines ls 1, \

     g(x) notitle with lines ls 2

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Now we save our file as introduction.gnu and execute it by running the following command in BASH under Linux.

$ gnuplot introduction.gnu


**Syntax:**
       plot {[ranges]}

            {[function] | {"[datafile]" {datafile-modifiers}}}

            {axes [axes] } { [title-spec] } {with [style] }

            {, {definitions,} [function] ...}

where either a [function] or the name of a data file enclosed in quotes is supplied. For more complete descriptions, type: help plot help plot with help plot using or help plot smooth . 

Customization
--------------

      Create a title:                  > set title "Force-Deflection Data" 

      Put a label on the x-axis:       > set xlabel "Deflection (meters)"

      Put a label on the y-axis:       > set ylabel "Force (kN)"

      Change the x-axis range:         > set xrange [0.001:0.005]

      Change the y-axis range:         > set yrange [20:500]

      Have Gnuplot determine ranges:   > set autoscale

      Move the key:                    > set key 0.01,100

      Delete the key:                  > unset key

      Put a label on the plot:         > set label "yield point" at 0.003, 260 

      Remove all labels:               > unset label

      Plot using log-axes:             > set logscale

      Plot using log-axes on y-axis:   > unset logscale; set logscale y 

      Change the tic-marks:            > set xtics (0.002,0.004,0.006,0.008)

      Return to the default tics:      > unset xtics; set xtics auto

MULTI-PLOT 
----------

Gnuplot can plot more than one figure in a frame ( like subplot in matlab ) i.e., try: 

      set multiplot;                  # get into multiplot mode

      set size 1,0.5;  

      set origin 0.0,0.5;   plot sin(x); 

      set origin 0.0,0.0;   plot cos(x)

      unset multiplot                         # exit multiplot mode

In gnuplot, exponentiation uses ``**, not ^. x^2 = x**2.``

Variable define : plot [t=-4:4] exp(-t**2 / 2), t**2 / 16

Plotting Data 
-------------

Discrete data contained in a file can be displayed by specifying the name of the data file (enclosed in quotes) on the plot or splot command line. Data files should have the data arranged in columns of numbers. Columns should be separated by white space (tabs or spaces) only, (no commas). Lines beginning with a # character are treated as comments and are ignored by Gnuplot. A blank line in the data file results in a break in the line connecting data points. 

For example your data file, force.dat , might look like: 

      # This file is called   force.dat

      # Force-Deflection data for a beam and a bar

===========	=========	==========
Deflection	Col-Force       Beam-Force 
===========	=========	==========
0.000              0              0   
0.001            104             51
0.002            202            101
0.003            298            148
0.0031           290            149
0.004            289            201
0.0041           291            209
0.005            310            250
0.010            311            260
0.020            280            240

===========	=========	==========

You can display your data by typing: 

      gnuplot>  plot  "force.dat" using 1:2 title 'Column', \

                      "force.dat" using 1:3 title 'Beam'

Do not type blank space after the line continuation character, "\" .

Your data may be in multiple data files. In this case you may make your plot by using a command like: 

      gnuplot>  plot  "fileA.dat" using 1:2 title 'data A', \

                      "fileB.dat" using 1:3 title 'data B'

For information on plotting 3-D data, type: 

      gnuplot>  help splot datafile


