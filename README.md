#ドロネーの三角形分割
import numpy as np
from scipy.spatial import Delaunay

point=np.loadtxt("jimentest.txt")
pointg=[] #地面の座標用の配列
pointgz=[]
for i in range(len(point)):
    if point[i][3]==1: #ラベルが地面だったら
        pointg.append([point[i][0],point[i][1]]) #x,yの座標を入れる
        pointgz.append([point[i][0],point[i][1],point[i][2]]) #x,y,zの座標を保管しておく

trig=Delaunay(pointg) #ドロネーの三角形分割
indexg=trig.simplices #三角形分割された添え字

pointb=[] #建物の座標用の配列
pointbz=[]
for i in range(len(point)):
    if point[i][3]==0: #ラベルが建物だったら
        pointb.append([point[i][0],point[i][1]]) #x,yの座標を入れる
        pointbz.append([point[i][0],point[i][1],point[i][2]]) #x,y,zの座標を保管しておく

trib=Delaunay(pointb) #ドロネーの三角形分割
indexb=trib.simplices #三角形分割された添え字

for i in range(len(pointgz)): #y座標を-1倍して向きを変えた
    pointgz[i][1]*=-1
for i in range(len(pointbz)): #y座標を-1倍して向きを変えた
    pointbz[i][1]*=-1
    
#ここからVRMLを記述
f =  open('vrml.wrl', 'w', encoding='utf-8')
f.write("#VRML V2.0 utf8\n")
f.write("Shape {\n  geometry IndexedFaceSet {\n\tcoord Coordinate {\n\t\t\tpoint [ \n")
for i in range(len(pointgz)):
    f.write(str(pointgz[i][0])+ " " + str(pointgz[i][2])+ " " + str(pointgz[i][1]) + " ,\n" )
f.write("]\n }\n coordIndex[\n")
for i in range(len(indexg)):
    f.write(str(indexg[i][0])+ ", " + str(indexg[i][1]) + ", " + str(indexg[i][2]) + ", -1,\n" )

f.write("\t\t]\n }\n\tappearance Appearance {\n\t\tmaterial Material {\n\t\t\tdiffuseColor 0 1 0\n }\n}\n}\n")


f.write("Shape {\n  geometry IndexedFaceSet {\n\tcoord Coordinate {\n\t\t\tpoint [ \n")
for i in range(len(pointbz)):
    f.write(str(pointbz[i][0])+ " " + str(pointbz[i][2])+ " " + str(pointbz[i][1]) + " ,\n" )
f.write("]\n }\n coordIndex[")
for i in range(len(indexb)):
    f.write(str(indexb[i][0])+ ", " + str(indexb[i][1]) + ", " + str(indexb[i][2]) + ", -1,\n" )


f.write("\t\t]\n }\n\tappearance Appearance {\n\t\tmaterial Material {\n\t\t\tdiffuseColor 1 0 1\n }\n}\n}\n")
f.close()

"""
f = open('datag.txt','w')
with open('datag.txt', 'w') as f:
    for i in range(len(pointgz)):
        print(pointgz[i][0],pointgz[i][2],pointgz[i][1],file=f)

f = open('datab.txt','w')
with open('datab.txt', 'w') as f:
    for i in range(len(pointbz)):
        print(pointbz[i][0],pointbz[i][2],pointbz[i][1],file=f)


f = open('indexg.txt','w')
with open('indexg.txt', 'w') as f:
    for i in range(len(indexg)):
        print(indexg[i][0],indexg[i][1],indexg[i][2],file=f)

f = open('indexb.txt','w')
with open('indexb.txt', 'w') as f:
    for i in range(len(indexb)):
        print(indexb[i][0],indexb[i][1],indexb[i][2],file=f)
"""
