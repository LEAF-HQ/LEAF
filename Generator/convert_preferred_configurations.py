import os, sys, time, math

infilename = 'preferred_configurations.txt'
outfilename = 'preferred_configurations.py'

with open(infilename, 'r') as infile:
    lines = infile.readlines()
    print len(lines)

config_dict = {}
mlqs = []
mc1s = []
for line in lines:
    line = line.strip()
    if line[0] is '#': continue
    else:
        values = line.split()
        mlq = values[0]
        logmc1 = values[1]
        deltamps = values[2]

        mlq_out = int(float(mlq))
        mc1_out = int(round(10**float(logmc1))) # txt file gives log_10(mc1)
        mps_out = int((1+float(deltamps))*mc1_out) if float(deltamps) > 0 else 0 # txt file gives delta_psi = (mps-mc1)/(mc1)
        if mps_out is 0: continue

        if mlq_out not in mlqs:
            config_dict[mlq_out] = {}
            mlqs.append(mlq_out)
        # if mlq_out not in mlqs: mlqs.append(mlq_out)
        # if mc1_out not in mc1s: mc1s.append(mc1_out)
        # print mlq_out, mc1_out, mps_out
        newline = '{\'mlq\': %i, \'mc1\': %i, \'mps\': %i, \'dps\': %.4f},\n' % (mlq_out, mc1_out, mps_out, float(deltamps))
        print newline
        config_dict[mlq_out][mc1_out] = (mps_out, float(deltamps))
        # config_dict[mlq_out][mc1_out] = newline
        # newlines.append(newline)

# for m in mlqs:
#     config_dict[m] = {}

# print config_dict
newlines = []
newlines.append('# Dictionary order -- 1st key: MLQ -- 2nd key: MC1 -- content:\n')
newlines.append('# (MPS [GeV], DeltaPsi)\n')
newlines.append('preferred_configurations = {\n')

print config_dict.keys()
print config_dict[9730]
for mlq in config_dict.keys():
    print mlq
    newlines.append('%5i: {\n' % (mlq))
    for mc1 in config_dict[mlq].keys():
        print mc1
        newlines.append('%9i: (%5i, %.4f),\n' % (mc1, config_dict[mlq][mc1][0], config_dict[mlq][mc1][1]))


    newlines.append('     },\n')
newlines.append('}\n')



# newlines.append('}\n')
print newlines

with open(outfilename, 'w') as outfile:
    for l in newlines:
        outfile.write(l)
