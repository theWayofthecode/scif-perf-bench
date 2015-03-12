import csv
import numpy
import pylab
import sys

filename = sys.argv[1]
title = sys.argv[2]
print filename

with open(filename, 'r') as csvfile:
        reader = csv.reader(csvfile, delimiter='\t')
        header = ['Block size',' bandwidth']
        x = []
        y = []
        i = 0;
        for row in reader:
            x.append((float (row[0]) * 0x40) / 0x100000)
            y.append(float (row[1]))

        
        #plot
        
        pylab.xlabel(header[0]+' [MB]')
        pylab.ylabel(header[1]+' [MB/s]')
        
        pylab.title(title)
        pylab.xscale('log', basex=2)
#        pylab.yticks(numpy.arange(10, 80, 10))
#        pylab.ylim(15, 65)
#        
#        pylab.xticks(numpy.arange(0, 14, 2))
#        pylab.xlim(0, 13)
        
        pylab.plot(x, y, marker='.')
        pylab.savefig(filename+'.png', bbox_inches='tight')
        
