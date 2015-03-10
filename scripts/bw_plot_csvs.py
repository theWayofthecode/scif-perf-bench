import csv
import numpy
import pylab
import sys

base = '/home/asantogi/mnt/SCIF-primitives-performance/data/'
name = sys.argv[1]
filename=base+'csv/'+name
print filename

with open(filename, 'r') as csvfile:
        reader = csv.reader(csvfile, delimiter='\t')
        title = '16 MB payload [MIC - > HOST]'
        header = ['msg_len',' bandwidth']
        x = []
        y = []
        i = 0;
        for row in reader:
            x.append(float (row[0])/1024.0)
            y.append(float (row[1]))

        
        #plot
        
        pylab.xlabel(header[0]+' [KB]')
        pylab.ylabel(header[1]+' [MB/s]')
        
        pylab.title(title)
        
        pylab.yticks(numpy.arange(10, 80, 10))
        pylab.ylim(15, 65)
        
        pylab.xticks(numpy.arange(0, 14, 2))
        pylab.xlim(0, 13)
        
        pylab.plot(x, y, marker='.')
        pylab.savefig(base+'plot/'+name+'.png', bbox_inches='tight')
        
