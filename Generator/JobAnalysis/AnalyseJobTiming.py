#!/usr/bin/env python

import os
import sys
import time
from datetime import datetime
import parse
from argparse import ArgumentParser
import ROOT
import numpy as np


def stripLine(line, pattern): 
	line = line.replace(pattern, "")
	t = time.strptime(line, "%H:%M:%S")
	dt = datetime.fromtimestamp(time.mktime(t))
	timevalue = dt.hour + dt.minute/60.
	return timevalue



def PromptYesNo(answerasbool=False): 
	# Inspired from Fabrice Couderc 
	rep = ''
	while not rep in [ 'yes', 'no' ]:
		rep = raw_input( "(type 'yes' or 'no'): " ).lower()
	if (answerasbool): 
		if (rep == 'yes'): 
			return True
		else: 
			return False
	return rep

def HoldUntilKeyPress(otherThanEnter=False): 
	# Inspired from Fabrice Couderc 
	rep = ''
	if otherThanEnter: 
		while rep in [ "" ]:
			rep = raw_input( "Press a key to continue... " ).lower()
	else:
		rep = raw_input( "Press a key to continue... " ).lower()
	
	return

if __name__ == "__main__":

	parser = ArgumentParser(description="JobTimeAnalysis")
	parser.add_argument('filename', action="store", type=str, help="Which time list you want to analyse")
	parser.add_argument("--threshold", dest="threshold", action="store", type=float, default=0., help="The threshold above which you want to consider the time")
	parser.add_argument("--prefix", dest="prefix", action="store", type=str, default="Execution time: ", help="The prefix of the time string in the input file")
	parser.add_argument("--debug", dest="debug", action="store_true", default=False, help="Turn on debug output")
	parser.add_argument("--save", dest="save", action="store", type=str, default="", help="Save histogram under provided name")

	options = parser.parse_args()

	with open(options.filename, "r") as timingfile:
		content = timingfile.readlines()
		if (options.debug): print content
		timedistribution = []
		for line in content: 
			timevalue = stripLine(line.rstrip(), options.prefix)
			if (timevalue > options.threshold): 
				timedistribution.append(timevalue)

		if (options.debug): print timedistribution

		canvas = ROOT.TCanvas("canvas", "canvas", 800, 600)

		histo = ROOT.TH1D("timedistribution", "Time distribution", 50, -0.5, 12.5)

		#for value in timedistribution: 
		#	histo.Fill(value)
		
		histo.FillN(len(timedistribution)-1, np.asarray(timedistribution, 'd'), np.asarray(np.ones(len(timedistribution)), 'd'))

		histo.Draw()
		canvas.Draw()

		if (options.save): 
			canvas.Print(options.save)

		HoldUntilKeyPress()

