#!/bin/bash
if [[ $# -eq 0 ]] ; then
    echo 'specify file'
    exit 1
fi
convert $1 txt:- | cut -d 'g' -f 1 | sed 's/[(][0-9, ]*[)]//g' |sed '2,$ s/,/:/g' | sed '1,$ s/[ ]*//g' |\
    gawk -F: '
                BEGIN {
                    row = $2;
                    total = 0;
                    printf("#x y");
                }   
                {
                    if($2 != row){
                        printf("%d %d\n",row, total);
                        row = $2;
                        total = 0;
                    }
                    if($3 == "#000000"){
                        total++;
                    }
                }
             ' > histograms_y.dat
convert -rotate 90 $1 txt:- | cut -d 'g' -f 1 | sed 's/[(][0-9, ]*[)]//g' |sed '2,$ s/,/:/g' | sed '1,$ s/[ ]*//g' |\
    gawk -F: '
                BEGIN {
                    row = $2;
                    total = 0;
                    printf("#x y");
                }   
                {
                    if($2 != row){
                        printf("%d %d\n",row, total);
                        row = $2;
                        total = 0;
                    }
                    if($3 == "#000000"){
                        total++;
                    }
                }
             ' > histograms_x.dat

echo "
reset;
set terminal png size 1280,960;
set output '$1_graph.png';

d(y) = (\$0 == 0) ? (y1 = y, 1/0) : (y2 = y1, y1 = y, y1-y2);
d2(x,y) = (\$0 == 0) ? (x1 = x, y1 = y, 1/0) : (x2 = x1, x1 = x, y2 = y1, y1 = y, (y1-y2)/(x1-x2));

# offset for derivatives (half the x spacing)
dx = 1;

set multiplot layout 4, 1;

plot 'histograms_x.dat' title 'x-as histograms' with line;
plot 'histograms_y.dat' title 'y-as histograms' with line;

plot 'histograms_x.dat' u (\$1-dx):(d(\$2)) title 'x-as histograms derivative' with line;
plot 'histograms_y.dat' u (\$1-dx):(d(\$2)) title 'y-as histograms derivative' with line;

unset multiplot;" | gnuplot

rm histograms_x.dat
rm histograms_y.dat