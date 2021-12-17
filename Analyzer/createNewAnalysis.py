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


    # create main folder
    ensureDirectory(name)

    # create necessary subfolders
    subfolders = ['include', 'src', 'lib', 'obj', 'config']
    for folder in subfolders:
        ensureDirectory('%s/%s' % (name, folder))

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
    createNewMakefile(name, placeholder_dict)

    # create all new header files
    createNewIncludes(name, placeholder_dict)

    # create all new source files
    createNewSources(name, placeholder_dict)

    # create all new source files
    createNewConfigs(name, placeholder_dict)

    # create all new source files
    createTestSampleXMLs(name, placeholder_dict)

    # create all new source files
    createNewPostAnalyzer(name, placeholder_dict)

    # create all new source files
    createNewPlotterXMLs(name, placeholder_dict)

    # update Makefile.local
    updateMakefileLocal(name)




def createNewMakefile(name, placeholders):
    command = 'cp templates/Makefile_template %s/Makefile' % (name)
    os.system(command)
    replace_placeholders('%s/Makefile' % (name), placeholders)

def createNewIncludes(name, placeholders):
    command = 'cp templates/Linkdef_template.hpp %s/include/Linkdef.hpp' % (name)
    os.system(command)

    command = 'cp templates/Event_template.h %s/include/%s.h' % (name, placeholders['$MYEVENTCLASS'])
    os.system(command)

    command = 'cp templates/Hists_template.h %s/include/%s.h' % (name, placeholders['$MYHISTNAME'])
    os.system(command)

    replace_placeholders('%s/include/Linkdef.hpp' % (name), placeholders)
    replace_placeholders('%s/include/%s.h' % (name, placeholders['$MYEVENTCLASS']), placeholders)
    replace_placeholders('%s/include/%s.h' % (name, placeholders['$MYHISTNAME']), placeholders)

def createNewSources(name, placeholders):
    command = 'cp templates/Event_template.cc %s/src/%s.cc' % (name, placeholders['$MYEVENTCLASS'])
    os.system(command)
    command = 'cp templates/Tool_template.cc %s/src/%s.cc' % (name, placeholders['$MYTOOLNAME'])
    os.system(command)
    command = 'cp templates/Hists_template.cc %s/src/%s.cc' % (name, placeholders['$MYHISTNAME'])
    os.system(command)

    replace_placeholders('%s/src/%s.cc' % (name, placeholders['$MYEVENTCLASS']), placeholders)
    replace_placeholders('%s/src/%s.cc' % (name, placeholders['$MYTOOLNAME']), placeholders)
    replace_placeholders('%s/src/%s.cc' % (name, placeholders['$MYHISTNAME']), placeholders)

def createNewConfigs(name, placeholders):
    command = 'cp templates/config_template.xml %s/config/%s.xml' % (name, placeholders['$MYANALYSISNAME'])
    os.system(command)
    command = 'cp templates/Configuration.dtd %s/config/' % (name)
    os.system(command)

    replace_placeholders('%s/config/%s.xml' % (name, placeholders['$MYANALYSISNAME']), placeholders)

def createTestSampleXMLs(name, placeholders):
    command = 'cp templates/TestData.xml %s/.testsamples/' % (os.environ['LEAFPATH'])
    os.system(command)
    command = 'cp templates/TestBackground.xml %s/.testsamples/' % (os.environ['LEAFPATH'])
    os.system(command)
    command = 'cp templates/TestSignal.xml %s/.testsamples/' % (os.environ['LEAFPATH'])
    os.system(command)

    replace_placeholders('%s/.testsamples/TestData.xml' % (os.environ['LEAFPATH']), placeholders)
    replace_placeholders('%s/.testsamples/TestBackground.xml' % (os.environ['LEAFPATH']), placeholders)
    replace_placeholders('%s/.testsamples/TestSignal.xml' % (os.environ['LEAFPATH']), placeholders)

def createNewPostAnalyzer(name, placeholders):
    command = 'cp -r templates/PostAnalyzerTemplate %s/PostAnalyzer' % (name)
    os.system(command)

    replace_placeholders('%s/PostAnalyzer/steer.py' % (name), placeholders)

def createNewPlotterXMLs(name, placeholders):
    command = 'cp -r templates/PlotterXML %s/%s' % (os.environ['PLOTTERPATH'], name)
    os.system(command)
    command = 'mv %s/%s/Template.xml %s/%s/Default.xml' % (os.environ['PLOTTERPATH'], name, os.environ['PLOTTERPATH'], name)
    os.system(command)

    replace_placeholders('%s/%s/Default.xml' % (os.environ['PLOTTERPATH'], name), placeholders)


def updateMakefileLocal(name):
    need_to_update = True
    newlines = []
    if os.path.isfile('Makefile.local'):
        with open('Makefile.local', 'r') as f:
            lines = f.readlines()
            for l in lines:
                if 'subdirs := %s' % (name) in l or 'subdirs += %s' % (name) in l:
                    need_to_update = False
                newlines.append(l)

    if need_to_update:
        if len(newlines) is 0:
            newline = 'subdirs := %s' % (name)
        else:
            newline = 'subdirs += %s' % (name)
        newlines.append(newline)
        with open('Makefile.local', 'w') as f:
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
