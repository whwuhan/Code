import numpy as np
from mpl_toolkits.mplot3d.axes3d import Axes3D
import matplotlib.pyplot as plt
import my_tree as my_tr
branches=[]
filename="./L1/tree5_missing_1.skel"    #tree2_missing_3    tree2_noise_3  tree4_8375  tree4_vdensity_2
f=open(filename)
while True:
    line=f.readline()
    if line.startswith("CN"):
        n=int(line.split()[1]) #分支数
        for i in range(n):
            line=f.readline()
            m=int(line.split()[1]) #分支的点数
            branch=[]
            for j in range(m):
                line=f.readline()
                values=line.split()
                branch.append([float(values[0]),float(values[1]),float(values[2])])
            branches.append(branch)
        break
f.close()
fig = plt.figure()
axes3d = Axes3D(fig)
for branch in branches:
    branch=np.array(branch)
    x=branch[:,0]
    y=branch[:,1]
    z=branch[:,2]
    axes3d.plot(x,y,z)
plt.show()

branches=my_tr.create_my_tree(branches,k=50,e_cos=0.5,e_dir=10)#连接骨架
fig = plt.figure()
axes3d = Axes3D(fig)
for branch in branches:
    branch=np.array(branch)
    x=branch[:,0]
    y=branch[:,1]
    z=branch[:,2]
    axes3d.plot(x,y,z)
plt.show()





