import ROOT
from root_numpy import root2array, rec2array
from DNNutils import *

def Root2Pandas(input_filename, output_filename, output_folder, branches, columns, chunksize, treename, category):
    if len(branches)!= len(columns):
        raise ValueError('Branches and columns have different lenght: '+str(len(branches))+', '+str(len(columns)))
    print green('  --> Creating numpy arrays for input sample %s' % (input_filename))
    inputfile = ROOT.TFile.Open(input_filename)
    tree = inputfile.Get(treename)
    entries = tree.GetEntriesFast()
    inputfile.Close()

    maxidx = int(entries/float(chunksize)) + 1
    if entries % chunksize == 0:
        maxidx -= 1
    print green('    --> Producing %i files with %i events each.' % (maxidx, chunksize))
    for i in range(maxidx):
        print green('      --> Working on file number: %i (%3.2f%%)' % (i+1, float(i+1)/maxidx * 100.))
        start, stop = (i*chunksize,(i+1)*chunksize)
        mymatrix = rec2array(root2array(filenames=input_filename, treename=treename, branches=branches, start=start, stop=stop))
        df = pd.DataFrame(mymatrix,columns=columns)
        df['category'] = [category]*len(df)
        outname = os.path.join(output_folder, '%s_%i.pkl' % (output_filename, i))
        SavePandas(df, outname)

class ConvertRootToInputsBase():
    def __init__(self, inputdir, outdir, chunksize=200000, treename='AnalysisTree', namebranch_weight=('Events.GenEvent.Event.weight','event_weight')):
        self.inputdir = inputdir
        self.outdir = outdir
        self.chunksize = chunksize
        self.treename = treename
        self.namebranch_weight = namebranch_weight

    def LoadDependanciesBase(self, libname='libLEAFClasses.so'):
        ROOT.gSystem.Load(libname)

    def LoadDependancies(self, classname=None):
        self.LoadDependanciesBase()
        if classname:
            self.LoadDependanciesBase(classname)

    def DefineSamples(self):
        raise NotImplementedError('DefineSamples method is not initialized. Fix this.')

    def DefineVariables(self):
        raise NotImplementedError('DefineVariables method is not initialized. Fix this.')

    def Convert(self):
        samples = self.DefineSamples()
        branches, columns = self.DefineVariables()
        branches.append(self.namebranch_weight[0])
        columns.append(self.namebranch_weight[1])
        for name, info in samples.items():
            vars = {
                'input_filename':os.path.join(self.inputdir, info.filename),
                'output_filename':info.samplename,
                'output_folder':self.outdir,
                'branches':branches,
                'columns':columns,
                'chunksize':self.chunksize,
                'treename':self.treename,
                'category':info.category
            }
            Root2Pandas(**vars)
