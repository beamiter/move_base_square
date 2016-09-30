#!/usr/bin/env python3
# _*_ coding: utf-8- _*_
import numpy as np
import matplotlib.pyplot as plt
import os
import re

from matplotlib.path import Path
from matplotlib.patches import PathPatch

fname='sol.txt'
f = open(fname)
i=0
vis=[]
while True:
    line = f.readline()
    if line:
        if i>=0:
            # print line
            vis.append(line)
            i=i+1
        else:
            break
    else :
        break
f.close
# print vis[0]
datalist = []
conlist = []
dislist = []
disx = []
disy = []
distheta = []
xlist = []
ylist = []
thetalist = []

for j in range(len(vis)):
    datalist.append(re.findall(r"\d+\.?\d*",vis[j]))
    if len(datalist[j])==6:
        dislist.append(datalist[j])
    else:
        conlist.append(datalist[j])

for j in range(len(dislist)):
    for n in range(3):
        dislist[j][n]=float(dislist[j][n])/5.0
    disx.append(dislist[j][0])
    disy.append(dislist[j][1])
    distheta.append(dislist[j][2])

for j in range(len(conlist)):
    xlist.append(conlist[j][0])
    ylist.append(conlist[j][1])
    thetalist.append(conlist[j][2])

#Adding obstacles

vertices = []
codes = []

codes = [Path.MOVETO] + [Path.LINETO]*3 + [Path.CLOSEPOLY]
vertices = [(46/5, 20/5), (46/5, 30/5), (54/5, 30/5), (54/5, 20/5), (0, 0)]

codes += [Path.MOVETO] + [Path.LINETO]*3 + [Path.CLOSEPOLY]
vertices += [(16/5, 20/5), (16/5, 30/5), (24/5, 30/5), (24/5, 20/5), (0, 0)]

codes += [Path.MOVETO] + [Path.LINETO]*3 + [Path.CLOSEPOLY]
vertices += [(71/5, 20/5), (71/5, 30/5), (79/5, 30/5), (79/5, 20/5), (0, 0)]

codes += [Path.MOVETO] + [Path.LINETO]*3 + [Path.CLOSEPOLY]
vertices += [(46/5, 5/5), (46/5, 15/5), (54/5, 15/5), (54/5, 5/5), (54/5, 5/5)]

codes += [Path.MOVETO] + [Path.LINETO]*3 + [Path.CLOSEPOLY]
vertices += [(16/5, 5/5), (16/5, 15/5), (24/5, 15/5), (24/5, 5/5), (0, 0)]

codes += [Path.MOVETO] + [Path.LINETO]*3 + [Path.CLOSEPOLY]
vertices += [(71/5, 5/5), (71/5, 15/5), (79/5, 15/5), (79/5, 5/5), (0, 0)]

codes += [Path.MOVETO] + [Path.LINETO]*3 + [Path.CLOSEPOLY]
vertices += [(46/5, 35/5), (46/5, 45/5), (54/5, 45/5), (54/5, 35/5), (0, 0)]

codes += [Path.MOVETO] + [Path.LINETO]*3 + [Path.CLOSEPOLY]
vertices += [(16/5, 35/5), (16/5, 45/5), (24/5, 45/5), (24/5, 35/5), (0, 0)]

codes += [Path.MOVETO] + [Path.LINETO]*3 + [Path.CLOSEPOLY]
vertices += [(71/5, 35/5), (71/5, 45/5), (79/5, 45/5), (79/5, 35/5), (0, 0)]

# codes += [Path.MOVETO] + [Path.LINETO]*2 + [Path.CLOSEPOLY]
# vertices += [(4, 4), (5, 5), (5, 4), (0, 0)]

vertices = np.array(vertices, float)
path = Path(vertices, codes)

pathpatch = PathPatch(path, facecolor='orange', edgecolor='green')

fig, ax = plt.subplots()
ax.add_patch(pathpatch)
ax.set_title('Adding obstacles')

ax.dataLim.update_from_data_xy(vertices)
ax.autoscale_view()

#Plot the graphes

line, = plt.plot(xlist, ylist, '*', label='path', color='red', linewidth=2)
dashes = [10, 10, 100, 10]  # 10 points on, 5 off, 100 on, 5 off
line.set_dashes(dashes)

disline, = plt.plot(disx, disy, '*', label='discrete path', color='blue', linewidth=2)
disdashes = [10, 10, 100, 10]  # 10 points on, 5 off, 100 on, 5 off
disline.set_dashes(disdashes)

plt.xlabel("x pos")
plt.ylabel("y pos")
plt.title("path visualization")
plt.legend()
plt.show()
