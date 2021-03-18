
import os
# "process.mixData.input.fileNames = cms.untracked.vstring(['/store/mc"

f = open('pset_03_dr.py', 'r')
lines = f.readlines()
newlines = []
mixdataline = ''
for line in lines:
    if not 'process.mixData.input.fileNames = cms.untracked.vstring([' in line:
        newlines.append(line)
        continue
    print 'found mixdataline, going to separate it.'
    newline_import = 'from mixdata import mixdatalist\n'
    newlines.append(newline_import)
    newline = 'process.mixData.input.fileNames = cms.untracked.vstring(mixdatalist)\n'
    newlines.append(newline)

    mixdataline = line
    mixdataline = mixdataline.replace('process.mixData.input.fileNames = cms.untracked.vstring(', 'mixdatalist = ')
    mixdataline = mixdataline.replace('])', ']')


print len(lines)
print len(newlines)
f.close()
f = open('pset_03_dr.py', 'w')
for l in newlines:
    f.write(l)
f.close()

f=open('mixdata.py', 'w')
f.write(mixdataline)
f.close()
