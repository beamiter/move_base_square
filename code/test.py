import numpy as np
from matplotlib.path import Path
from matplotlib.patches import PathPatch
import matplotlib.pyplot as plt


vertices = []
codes = []

codes = [Path.MOVETO] + [Path.LINETO]*3 + [Path.CLOSEPOLY]
vertices = [(46, 20), (46, 30), (54, 30), (54, 20), (0, 0)]

codes += [Path.MOVETO] + [Path.LINETO]*3 + [Path.CLOSEPOLY]
vertices += [(16, 20), (16, 30), (24, 30), (24, 20), (0, 0)]

codes += [Path.MOVETO] + [Path.LINETO]*3 + [Path.CLOSEPOLY]
vertices += [(71, 20), (71, 30), (79, 30), (79, 20), (0, 0)]

codes += [Path.MOVETO] + [Path.LINETO]*3 + [Path.CLOSEPOLY]
vertices += [(46, 5), (46, 15), (54, 15), (54, 5), (54, 5)]

codes += [Path.MOVETO] + [Path.LINETO]*3 + [Path.CLOSEPOLY]
vertices += [(16, 5), (16, 15), (24, 15), (24, 5), (0, 0)]

codes += [Path.MOVETO] + [Path.LINETO]*3 + [Path.CLOSEPOLY]
vertices += [(71, 5), (71, 15), (79, 15), (79, 5), (0, 0)]

codes += [Path.MOVETO] + [Path.LINETO]*3 + [Path.CLOSEPOLY]
vertices += [(46, 35), (46, 45), (54, 45), (54, 35), (0, 0)]

codes += [Path.MOVETO] + [Path.LINETO]*3 + [Path.CLOSEPOLY]
vertices += [(16, 35), (16, 45), (24, 45), (24, 35), (0, 0)]

codes += [Path.MOVETO] + [Path.LINETO]*3 + [Path.CLOSEPOLY]
vertices += [(71, 35), (71, 45), (79, 45), (79, 35), (0, 0)]

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


plt.show()
