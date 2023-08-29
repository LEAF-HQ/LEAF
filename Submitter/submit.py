#! /usr/bin/env python
# This folder's code is largely inspired by https://github.com/UHH2/SFrameBatch

# main "executable" that takes as an argument the XML file and handles submission, monitoring, and hadd'ing of the files
import os, sys
import subprocess
import time
import argparse
from utils import *
from Submitter import *
import ROOT
from ROOT import kError


def main():
    parser = argparse.ArgumentParser(description='Program that takes as an argument the XML file and handles submission, monitoring, and hadd\'ing of the files.')
    parser.add_argument('xmlfilename', metavar='XMLFILENAME', type=str, nargs=1, help='Name of the XML file')
    parser.add_argument('--clean',           '-c', action='store_true', default=False, dest='clean',              help='Clean up: remove the local and the remote workdir')
    parser.add_argument('--divide',          '-d', action='store_true', default=False, dest='divide',             help='Divide XMLFILENAME into chunks, create workdir.')
    parser.add_argument('--recount',         '-r', action='store_true', default=False, dest='recount',            help='Recount events before splitting xml files.')
    parser.add_argument('--local',           '-l', action='store',                     dest='ncores',   type=int, help='Run split jobs locally on NCORES cores')
    parser.add_argument('--cluster',         '-k', action='store',      default='',    dest='cluster',  type=str, help='Overwrite cluster settings defined in UserSpecificSettings')
    parser.add_argument('--submit',          '-s', action='store_true', default=False, dest='submit',             help='Submit split jobs to cluster')
    parser.add_argument('--output',          '-o', action='store_true', default=False, dest='output',             help='Check the status of the expected output files')
    parser.add_argument('--add',             '-a', action='store_true', default=False, dest='add',                help='Add split files back together for samples that are fully processed. Incomplete samples are not added.')
    parser.add_argument('--forceadd',        '-f', action='store_true', default=False, dest='forceadd',           help='Force hadding with hadd\'s \'-f\' flag. Also has an effect if used without \'--add\'.')
    parser.add_argument('--notreeadd',       '-t', action='store_true', default=False, dest='notreeadd',          help='Add split files without adding the trees. By default does not apply the force-add')
    parser.add_argument('--allowincomplete', '-i', action='store_true', default=False, dest='allowincomplete',    help='Ignore the non-existent files and does the hadd nonetheless')
    parser.add_argument('--plothadd',        '-p', action='store_true', default=False, dest='hadd',               help='Hadd files to groups used for plotting and further analysis. Will always force.')
    parser.add_argument('--group-with-tree', '-g', action='store_true', default=False, dest='groupwithtree',      help='Hadd files to groups and keep the tree (which makes it useful only for further processing). Will always force.')
    parser.add_argument('--use-se',                action='store_true', default=False, dest='use_se',             help='Allow submitter to use the SE director. Should only be necessary when the output directory is not mounted on current system.')

    args = parser.parse_args()
    xmlfilename = os.path.abspath(args.xmlfilename[0])
    if not xmlfilename.endswith('.xml'):
        raise ValueError(red('The name of the xml-file does not end with \'.xml\'. I don\'t believe you...'))

    run_local = args.ncores is not None
    is_to_add = args.add or args.forceadd or args.notreeadd
    nargs     = sum([1 for x in vars(args) if vars(args)[x] is True])

    # Build submitter object, this will already parse the XML file
    submitter = Submitter(xmlfilename=xmlfilename, use_se=args.use_se)

    # create workdir locally and remotely (for output), create txt file with expected output files, split XML file into many smaller ones for individual jobs
    if args.clean:
        if nargs > 1:
            raise AttributeError('More than one argument given together with \'-c\' option. This is unsafe.')
        submitter.Clean()
    if args.divide:     submitter.Divide(recount=args.recount)
    if args.output:     submitter.Output()
    if args.submit:     submitter.Submit(cluster=args.cluster)
    if run_local:       submitter.RunLocal(ncores=args.ncores)
    if is_to_add:       submitter.Add(force=args.forceadd, ignoretree=args.notreeadd, allowincomplete=args.allowincomplete)
    if args.hadd:       submitter.Hadd(ignoretree=True)
    if args.groupwithtree: submitter.Hadd(ignoretree=False)



























if __name__ == '__main__':
    main()
