from compiletools import codeobject
import sys
import os

if len(sys.argv) < 2:
    print('Usage: ./python3 createimage.py <fname>')

filename = sys.argv[1]

if not os.path.isabs(filename):
    filename = os.path.abspath(filename)


path, file = os.path.split(filename)

outputname = os.path.join(path, file.split('.')[0] + '.img')

co = codeobject()

with open(filename, 'r') as f:
    co.addstring(f.read())

img = co.create_image()

with open(outputname, 'wb') as f:
    f.write(img)
