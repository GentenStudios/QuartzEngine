# Copyright (c) 2019 Vyom Fadia
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

import os
import sys
from argparse import ArgumentParser

utfPrefix = chr(0xef) + chr(0xbb) + chr(0xbf)

def recurseAndUpdate(dir,  oldCopyright, copyright, excludeDirList):
    filenames = os.listdir(dir)
    for filename in filenames:
        fullFilename = os.path.realpath(os.path.join(dir, filename))
        if (os.path.dirname(fullFilename) in excludeDirList):
            continue

        if (os.path.isdir(fullFilename)):
            recurseAndUpdate(fullFilename, oldCopyright, copyright, excludeDirList)
        else:
            if fullFilename.endswith(".cpp") or fullFilename.endswith(".hpp"):
                fileData = open(fullFilename, "r+").read()
                
                isUTF = False
                if fileData.startswith(utfPrefix):
                    isUTF = True
                    fileData = fileData[3:]
                
                if oldCopyright != None:
                    if fileData.startswith(oldCopyright):
                        fileData = fileData[len(oldCopyright):] + "\n"

                if not (fileData.startswith(copyright)):
                    print("Updating " + filename)
                    fileData = copyright + fileData

                    if (isUTF):
                        open(fullFilename, "w").write(utfPrefix + fileData)
                    else:
                        open(fullFilename, "w").write(fileData)

if __name__ == '__main__':
    parser = ArgumentParser()
    parser.add_argument("-c", "--copyright-file", dest="copyright", help="The file to read the copyright from.", required = True)
    parser.add_argument("-o", "--old-copyright-file", dest="oldCopyright", help="The file to read the OLD copyright from.", required = False)
    parser.add_argument('-e','--exclude-list', nargs='*', dest="excludes", help='Set the list of directories to exclude', required = False)

    args = parser.parse_args()

    if not args.copyright:
        parser.error('A Copyright file is REQUIRED. Use -c or --copyright-file to get information about it. Use the -h or --help CLI parameters for more help.')

    try: oldCopyright = open(args.oldCopyright, "r").read()
    except:
        print("[WARNING] An old copyright file was not provided, continuing with an empty value for the old copyright.") 
        oldCopyright = ""
    
    try: newCopyright = open(args.copyright, "r").read()
    except FileNotFoundError:
        print("[ERROR] The filename you provided for the NEW copyright to insert is incorrect, please amend the value and rerun the command.")
        exit()

    excludes = []
    if args.excludes != None:
        for exclude in args.excludes:
            excludes.append(os.path.realpath(exclude))
            
    recurseAndUpdate(os.path.realpath(__file__) + "../", oldCopyright, newCopyright, excludes) # QUARTZ EDIT
