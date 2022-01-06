#! /usr/bin/env python
import os, sys
import subprocess
import time
import argparse
from utils import *


def main():
    parser = argparse.ArgumentParser(description='Create all necessary files for a brand-new analysis.')
    parser.add_argument('name', metavar='name', type=str, nargs=1,
                        help='The name of the new analysis, choose wisely, you might have to stick with it for a longer time!')

    args = parser.parse_args()
    name = args.name[0]
    print green('--> Creating new analysis setup for analysis: %s' % (name))

    leafpath = os.environ['LEAFPATH']


    # create main folder and Analyzer/Plotter/Generator/Tuplizer subfolders
    ensureDirectory(os.path.join(leafpath, name, 'Analyzer'))
    ensureDirectory(os.path.join(leafpath, name, 'Plotter'))
    ensureDirectory(os.path.join(leafpath, name, 'Generator'))
    ensureDirectory(os.path.join(leafpath, name, 'Tuplizer'))

    # create necessary subfolders
    subfolders = ['include', 'src', 'lib', 'obj', 'config']
    for folder in subfolders:
        ensureDirectory('%s' % (os.path.join(leafpath, name, 'Analyzer', folder)))

    # define placeholders and desired replacements
    placeholder_dict = {
        '$MYANALYSISNAME': name,
        '$MYEVENTCLASS' : '%sEvent' % (name),
        '$MYTOOLNAME' : '%sTool' % (name),
        '$MYHISTNAME' : '%sHists' % (name),
        '$MYUSERNAME' : os.environ['USER'],
        '$MYANALYZERPATH': os.environ['ANALYZERPATH'],
        '$MYLEAFPATH': os.environ['LEAFPATH']
    }



    # create makefile
    createNewMakefile(leafpath, name, placeholder_dict)

    # create all new header files
    createNewIncludes(leafpath, name, placeholder_dict)

    # create all new source files
    createNewSources(leafpath, name, placeholder_dict)

    # create all new source files
    createNewConfigs(leafpath, name, placeholder_dict)

    # create all new source files
    createTestSampleXMLs(leafpath, name, placeholder_dict)

    # create all new source files
    createNewPostAnalyzer(leafpath, name, placeholder_dict)

    # create all new source files
    createNewPlotterXMLs(leafpath, name, placeholder_dict)

    # update Makefile.local
    updateMakefileLocal(leafpath, name)




def createNewMakefile(basefolder, name, placeholders):
    command = 'cp templates/Makefile_template %s/Makefile' % (os.path.join(basefolder, name, 'Analyzer'))
    os.system(command)
    replace_placeholders('%s/Makefile' % (os.path.join(basefolder, name, 'Analyzer')), placeholders)

def createNewIncludes(basefolder, name, placeholders):
    command = 'cp templates/Linkdef_template.hpp %s/include/Linkdef.hpp' % (os.path.join(basefolder, name, 'Analyzer'))
    os.system(command)

    command = 'cp templates/Event_template.h %s/include/%s.h' % (os.path.join(basefolder, name, 'Analyzer'), placeholders['$MYEVENTCLASS'])
    os.system(command)

    command = 'cp templates/Hists_template.h %s/include/%s.h' % (os.path.join(basefolder, name, 'Analyzer'), placeholders['$MYHISTNAME'])
    os.system(command)

    replace_placeholders('%s/include/Linkdef.hpp' % (os.path.join(basefolder, name, 'Analyzer')), placeholders)
    replace_placeholders('%s/include/%s.h' % (os.path.join(basefolder, name, 'Analyzer'), placeholders['$MYEVENTCLASS']), placeholders)
    replace_placeholders('%s/include/%s.h' % (os.path.join(basefolder, name, 'Analyzer'), placeholders['$MYHISTNAME']), placeholders)

def createNewSources(basefolder, name, placeholders):
    command = 'cp templates/Event_template.cc %s/src/%s.cc' % (os.path.join(basefolder, name, 'Analyzer'), placeholders['$MYEVENTCLASS'])
    os.system(command)
    command = 'cp templates/Tool_template.cc %s/src/%s.cc' % (os.path.join(basefolder, name, 'Analyzer'), placeholders['$MYTOOLNAME'])
    os.system(command)
    command = 'cp templates/Hists_template.cc %s/src/%s.cc' % (os.path.join(basefolder, name, 'Analyzer'), placeholders['$MYHISTNAME'])
    os.system(command)

    replace_placeholders('%s/src/%s.cc' % (os.path.join(basefolder, name, 'Analyzer'), placeholders['$MYEVENTCLASS']), placeholders)
    replace_placeholders('%s/src/%s.cc' % (os.path.join(basefolder, name, 'Analyzer'), placeholders['$MYTOOLNAME']), placeholders)
    replace_placeholders('%s/src/%s.cc' % (os.path.join(basefolder, name, 'Analyzer'), placeholders['$MYHISTNAME']), placeholders)

def createNewConfigs(basefolder, name, placeholders):
    command = 'cp templates/config_template.xml %s/config/%s.xml' % (os.path.join(basefolder, name, 'Analyzer'), placeholders['$MYANALYSISNAME'])
    os.system(command)
    command = 'cp templates/Configuration.dtd %s/config/' % (os.path.join(basefolder, name, 'Analyzer'))
    os.system(command)

    replace_placeholders('%s/config/%s.xml' % (os.path.join(basefolder, name, 'Analyzer'), placeholders['$MYANALYSISNAME']), placeholders)

def createTestSampleXMLs(basefolder, name, placeholders):
    command = 'cp templates/TestData.xml %s/.testsamples/' % (os.environ['LEAFPATH'])
    os.system(command)
    command = 'cp templates/TestBackground.xml %s/.testsamples/' % (os.environ['LEAFPATH'])
    os.system(command)
    command = 'cp templates/TestSignal_M1000.xml %s/.testsamples/' % (os.environ['LEAFPATH'])
    os.system(command)
    command = 'cp templates/TestSignal_M2000.xml %s/.testsamples/' % (os.environ['LEAFPATH'])
    os.system(command)

    replace_placeholders('%s/.testsamples/TestData.xml' % (os.environ['LEAFPATH']), placeholders)
    replace_placeholders('%s/.testsamples/TestBackground.xml' % (os.environ['LEAFPATH']), placeholders)
    replace_placeholders('%s/.testsamples/TestSignal_M1000.xml' % (os.environ['LEAFPATH']), placeholders)
    replace_placeholders('%s/.testsamples/TestSignal_M2000.xml' % (os.environ['LEAFPATH']), placeholders)

def createNewPostAnalyzer(basefolder, name, placeholders):
    command = 'cp -r templates/PostAnalyzerTemplate %s/PostAnalyzer' % (os.path.join(basefolder, name, 'Analyzer'))
    os.system(command)

    replace_placeholders('%s/PostAnalyzer/steer.py' % (os.path.join(basefolder, name, 'Analyzer')), placeholders)

def createNewPlotterXMLs(basefolder, name, placeholders):
    ensureDirectory(os.path.join(basefolder, name, 'Plotter'))
    command = 'cp templates/PlotterXML/* %s/' % (os.path.join(basefolder, name, 'Plotter'))
    os.system(command)
    command = 'mv %s/Template.xml %s/Default.xml' % (os.path.join(basefolder, name, 'Plotter'), os.path.join(basefolder, name, 'Plotter'))
    os.system(command)

    replace_placeholders('%s/Default.xml' % (os.path.join(basefolder, name, 'Plotter')), placeholders)


def updateMakefileLocal(basefolder, name):
    need_to_update = True
    newlines = []
    fullmakefilepath = os.path.join(basefolder, 'Analyzer', 'Makefile.local')
    if os.path.isfile(fullmakefilepath):
        with open(fullmakefilepath, 'r') as f:
            lines = f.readlines()
            for l in lines:
                if 'subdirs := %s' % (os.path.join(basefolder, name, 'Analyzer')) in l or 'subdirs += %s' % (os.path.join(basefolder, name, 'Analyzer')) in l:
                    need_to_update = False
                newlines.append(l)

    if need_to_update:
        if len(newlines) is 0:
            newline = 'subdirs := %s' % (os.path.join(basefolder, name, 'Analyzer'))
        else:
            newline = 'subdirs += %s' % (os.path.join(basefolder, name, 'Analyzer'))
        newlines.append(newline)
        with open(fullmakefilepath, 'w') as f:
            for l in newlines:
                f.write(l)



def replace_placeholders(filename, placeholder_dict):
    newlines = []
    with open(filename, 'r') as f:
        lines = f.readlines()
        newlines = []
        for line in lines:
            newline = line
            for key in placeholder_dict.keys():
                newline = newline.replace(key, placeholder_dict[key])
            newlines.append(newline)
    create_new_file_with_lines(filename, newlines)

def create_new_file_with_lines(filename, lines):
    with open(filename, 'w') as f:
        for l in lines:
            f.write(l)









if __name__ == '__main__':
    main()
