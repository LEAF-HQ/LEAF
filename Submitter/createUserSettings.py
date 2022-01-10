#! /usr/bin/env python
import argparse
from UserSpecificSettings import *

def main():

    parser = argparse.ArgumentParser(description='Create JSON files for user, when providing a minimal set of settings.')
    parser.add_argument('--username', '-u', action='store', type=str, dest='username')
    parser.add_argument('--email',    '-e', action='store', type=str, dest='email')
    parser.add_argument('--cluster',  '-k', action='store', type=str, dest='cluster')

    args = parser.parse_args()

    UserSpecificSettings(username=args.username, email=args.email, cluster=args.cluster).SaveJSON()


if __name__ == '__main__':
    main()
