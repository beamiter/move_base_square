#!/usr/bin/env python3
# _*_ coding: utf-8- _*_
import numpy as np
import matplotlib.pyplot as plt
import os
import re
import matplotlib.path as mpath
import matplotlib.patches as mpatches

from matplotlib.path import Path
from matplotlib.patches import PathPatch
from matplotlib.patches import Ellipse

fname='sol.txt'
# fosname='obstacles.cfg'
# triname='triangle.cfg'
gridname="map.cfg"
resolution = 0.2
cellx = 100
celly = 50

f = open(fname)
vis=[]
while True:
    line = f.readline()
    if line:
        vis.append(line)
    else:
        break
f.close

# f = open(fosname)
# obs=[]
# while True:
#     line = f.readline()
#     if line:
#         obs.append(line)
#     else:
#         break
# f.close

# f = open(triname)
# tri=[]
# while True:
#     line = f.readline()
#     if line:
#         tri.append(line)
#     else:
#         break
# f.close

f = open(gridname)
grid=[]
while True:
    line = f.readline()
    if line:
        grid.append(line)
    else:
        break
f.close



#Plotting the discrete and continuous path

datalist = []
conlist = []
dislist = []

disx = []
disy = []
distheta = []

xlist = []
ylist = []
thetalist = []

# obslist = []
# trilist = []

gridlist = []


for j in range(10, len(grid)):
    gridlist.append(re.findall(r"\d*",grid[j]))

# for j in range(2, len(tri)):
#     trilist.append(re.findall(r"\d+\.?\d*",tri[j]))

# for j in range(2, len(obs)):
#     obslist.append(re.findall(r"\d+\.?\d*",obs[j]))

for j in range(len(vis)):
    datalist.append(re.findall(r"\d+\.?\d*",vis[j]))
    if len(datalist[j])==6:
        dislist.append(datalist[j])
    else:
        conlist.append(datalist[j])

for j in range(len(dislist)):
    # for n in range(3):
    #     dislist[j][n]=float(dislist[j][n])/5.0
    disx.append(dislist[j][0])
    disy.append(dislist[j][1])
    distheta.append(dislist[j][2])

for j in range(len(conlist)):
    for n in range(3):
        conlist[j][n]=float(conlist[j][n])/resolution
    xlist.append(conlist[j][0])
    ylist.append(conlist[j][1])
    thetalist.append(conlist[j][2])

#Plot the map

height = len(gridlist) - 1
width = len(gridlist[0])-2
realwidth = width/2

print height
print width

newlist = []
for i in range(height):
    for j in range(0, width, 2):
            newlist.append(gridlist[i][j])
# print newlist
result = []
result = [float(item)/255.0 for item in newlist]
# print result

narray = np.array(result)
narray.shape = height, realwidth
print narray.shape

ax = plt.subplot()

# image = np.random.uniform(size=(10, 10))
# image = np.zeros((30,20))

# image = np.ones([realwidth,height])

#The random image
# image = np.random.uniform(size=(height, realwidth))

# for row in image:
#     print row
# print image





# for row in gridlist:
#     print row
image = np.ones([height,realwidth])
narray = image - narray
ax.imshow(narray, cmap=plt.cm.gray, interpolation='nearest')
# ax.set_title('Map and Path')
# Move left and bottom spines outward by 10 points
ax.spines['left'].set_position(('outward', 1))
ax.spines['bottom'].set_position(('outward', 1))
# Hide the right and top spines
ax.spines['right'].set_visible(False)
ax.spines['top'].set_visible(False)
# Only show ticks on the left and bottom spines
ax.yaxis.set_ticks_position('left')
ax.xaxis.set_ticks_position('bottom')




#Adding obstacles

# vertices = []
# codes = []

# for j in range(len(obslist)):
#     codes += [Path.MOVETO] + [Path.LINETO]*3 + [Path.CLOSEPOLY]
#     vertices += [(obslist[j][0], obslist[j][1]), (obslist[j][2], obslist[j][3]),
#                  (obslist[j][4], obslist[j][5]), (obslist[j][6], obslist[j][7]), (0, 0)]

# #Adding triangles

# for j in range(len(trilist)):
#     codes += [Path.MOVETO] + [Path.LINETO]*2 + [Path.CLOSEPOLY]
#     vertices += [(trilist[j][0], trilist[j][1]), (trilist[j][2], trilist[j][3]),
#                  (trilist[j][4], trilist[j][5]), (0, 0)]

# codes += [Path.MOVETO] + [Path.LINETO]*2 + [Path.CLOSEPOLY]
# vertices += [(4, 4), (5, 5), (5, 4), (0, 0)]

# codes += [Path.MOVETO] + [Path.LINETO]*4 + [Path.CLOSEPOLY]
# vertices += [(4, 4), (5, 5), (5, 4), (1,2), (7,9), (0, 0)]

# vertices = np.array(vertices, float)
# path = Path(vertices, codes)

# pathpatch = PathPatch(path, facecolor='orange', edgecolor='green')

# ax = plt.subplot()
# ax.add_patch(pathpatch)

# ax.set_title('Adding obstacles')
# ax.dataLim.update_from_data_xy(vertices)
# ax.autoscale_view()

#Plot the graphes

line, = plt.plot(xlist, ylist, '*', label='path', color='red', linewidth=2)
dashes = [10, 10, 100, 10]  # 10 points on, 5 off, 100 on, 5 off
line.set_dashes(dashes)

disline, = plt.plot(disx, disy, '*', label='discrete path', color='blue', linewidth=2)
disdashes = [10, 10, 100, 10]  # 10 points on, 5 off, 100 on, 5 off
disline.set_dashes(disdashes)

#Plot ellipse

# delta = 45.0  # degrees
# laxis = 4;
# saxis = 2;
# center = [1,1]
# angles = np.arange(0, 360 + delta, delta)
# ells = [Ellipse((1, 1), 4, 2, a) for a in angles]
# a = plt.subplot(111, aspect='equal')
# a = plt.subplot()
# for e in ells:
#     e.set_clip_box(a.bbox)
#     e.set_alpha(0.1)
#     a.add_artist(e)
# ells = Ellipse((center[0],center[1]), laxis , saxis, delta)
# a = plt.subplot()
# ells.set_clip_box(a.bbox)
# ells.set_alpha(0.5)
# a.add_artist(ells)



plt.xlim(-2, cellx)
plt.ylim(-2, celly)
plt.xlabel("x pos")
plt.ylabel("y pos")
plt.title("path visualization")
plt.legend()
plt.show()
