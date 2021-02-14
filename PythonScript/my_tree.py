import numpy as np

def create_my_tree(branches,k=15,e_cos=0.8,e_dir=10):#k:最近的k个点  e_cos：夹角cos的精度   e_dir距离精度
    '''连接骨架'''
    vertices,edges=branches_to_v_e(branches)#branches转化为邻接矩阵
    one_vertices,one_vertices_inx=get_one_vertices(branches=branches)#获取度为1的点坐标和坐标索引
    k_nearest_neighbor_inx=get_k_neighbor(vertices,one_vertices,branches,k)#度为1的点最近的k个点   k_nearest_neighbor_inx：首位为当前点索引
    k_nearest_neighbor_inx=get_one_right_vertices(branches,vertices,k_nearest_neighbor_inx)#进行筛选
    directions=get_directions(branches)#分支的方向

    np_k_n_i=np.array(k_nearest_neighbor_inx)
    np_vs=np.array(vertices)
    res_branches=branches.copy()
    for i in range(len(k_nearest_neighbor_inx)):
        for index in k_nearest_neighbor_inx[i]:
            if (vertices[index] not in branches[int(i/2)]) and (k_nearest_neighbor_inx[i][0]!=-1):#不在同一分支上，且端点不在其他分支端点处
                #计算连线的方向单位向量
                dir_temp=np_vs[index]-np_vs[np_k_n_i[i][0]]
                dir_temp=dir_temp/(((dir_temp**2).sum(axis=0))**0.5)#单位化
                #print(dir_temp,'向量')
                cos=dir_temp.dot(directions[i])#点乘
                print(cos,'cos角度')
                if cos>=e_cos and cos>=0:#要符合精度
                    if i%2==0:
                        res_branches[int(i/2)].insert(0,vertices[index])
                        break
                    else:
                        res_branches[int(i/2)].append(vertices[index])
                        break
                #print(cos,'角度')
    return res_branches
     

def branches_to_v_e(branches):
    '''branches转化为邻接矩阵和点数组'''
    #生成点数组
    vertices=[]#点坐标
    for i in branches:
        for j in i:
            vertices.append(j)

    #生成邻接矩阵
    x=len(vertices)
    edges=np.zeros(shape=(x,x))
    length=0
    for i in branches:
        for j in range(len(i)-1):
            edges[length][length+1]=1
            edges[length+1][length]=1
            length=length+1
        length=length+1
    #vertices=np.array(vertices)
    #edges=np.array(edges)
    print('邻接矩阵\n',vertices,'\n',edges)
    return vertices,edges


def get_one_vertices(vertices=[],edges=[],branches=[]):
    '''找到度为1的点（分支端点）'''
    #邻接矩阵获得度为1的点
    if  len(vertices) and len(edges):
        count=0   #点的度数
        vertices=np.array(vertices)
        n=vertices.shape[0] 
        one_vertices=np.zeros(shape=(0,3))#one_vertices:度数为1的点的坐标
        one_vertices_inx=np.zeros(shape=(0))#one_vertices_inx:度数为1的点的坐标的索引
        for i in range(n):
            for j in range(n):
                if edges[i][j]==1:
                    count=count+1
            if count==1: 
                one_vertices=np.r_[one_vertices,[vertices[i]]]#将度为1的点坐标放入one_vertices
                one_vertices_inx=np.append(one_vertices_inx,i)#将度为1的点的坐标索引放入one_vertices_inx
            count=0
        print(one_vertices,one_vertices_inx)
        return one_vertices,one_vertices_inx
    else:#用branches获得度为1的点
        one_vertices=[]
        one_vertices_inx=[]
        inx_temp=0
        for branch in branches: 
            one_vertices.append(branch[0])
            one_vertices_inx.append(inx_temp)
            inx_temp=inx_temp+len(branch)-1 
            one_vertices.append(branch[-1])
            one_vertices_inx.append(inx_temp)
            inx_temp=inx_temp+1
        one_vertices=np.array(one_vertices)
        one_vertices_inx=np.array(one_vertices_inx)
        print('度为1的点\n',one_vertices,'\n',one_vertices_inx)
        return one_vertices,one_vertices_inx
                      
def get_k_neighbor(vertices,one_vertices,branches,k):
    '''获得度为1的点的K个最近的邻居'''
    #用邻接矩阵获得最近的k个点
    #distances=np.zeros(shape=(0,len(vertices)))#distances:所有度为1的点到其他点距离的平方
    distances=[]
    for i in one_vertices:
        distance=[]#当前度为1的点到其他点距离的平方
        for j in vertices:
            distance.append(((i-j)**2).sum(axis=0))#获得当前度为1的点到其他店的距离的平方
            #print(distance)   
        distances.append(distance)

    k_nearest_neighbor_inx=[]
    distances_temp=distances.copy()#直接赋值是传地址
    infinite=float('inf')#无穷大           
    for i in range(len(distances_temp)):#for循环里面依旧是传地址
        inx_temp=[]#暂时存放当前度为1的点最近k个点的索引，首位为当前节点
        for j in range(k+1):#循环k+1次，因为要找出除当前点外离得最近的k个点
            min_dis=distances_temp[i][0]#最短距离初始化
            min_dis_inx=0#最短距离索引初始化 
            for h in range(len(vertices)):
                if distances_temp[i][h]<min_dis:
                    min_dis=distances_temp[i][h]#更新最短距离
                    min_dis_inx=h#最短距离的索引
            inx_temp.append(min_dis_inx)#把最近的k个点放进数组
            distances_temp[i][min_dis_inx]=infinite#赋值为无穷大
        k_nearest_neighbor_inx.append(inx_temp)
        #print(distances_temp)
        #print(inx_temp)
    print('最近的k个点\n',k_nearest_neighbor_inx)
    return k_nearest_neighbor_inx

def get_one_right_vertices(branches,vertices,k_nearest_neighbor_inx):#k_nearest_neighbor_inx：首位是端点坐标
    '''筛选出端点（度为1的点）不在其他分支上的点或者在其他分支上，但同样是端点的点'''
    for i in range(len(k_nearest_neighbor_inx)):
        for j in range(len(branches)):
            if j!=int(i/2):
                if (vertices[k_nearest_neighbor_inx[i][0]] in branches[j]) and (k_nearest_neighbor_inx[i][0]!=branches[j][0]) and (k_nearest_neighbor_inx[i][0]!=branches[j][-1]):
                    k_nearest_neighbor_inx[i][0]=-1
    k_nearest_neighbor_inx=np.array(k_nearest_neighbor_inx)
    print(k_nearest_neighbor_inx)
    return k_nearest_neighbor_inx

def get_directions(branches):
    '''获取分支两端方向的单位向量'''
    #branches：分支坐标  n:端点处取第n个点计算分支方向
    directions=np.zeros(shape=(0,3))#端点处分支方向
    branches=np.array(branches)
    for branch in branches:
        mid=int(len(branch)/2)
        branch=np.array(branch)
        dir_0=np.array([0,0,0])#分支两端的方向
        dir_1=np.array([0,0,0])
        dir_0=branch[0]-branch[mid]
        dir_1=branch[-1]-branch[mid]
        #化成单位向量
        dir_0=dir_0/(((dir_0**2).sum(axis=0))**0.5)
        dir_1=dir_1/(((dir_1**2).sum(axis=0))**0.5)
        directions=np.append(directions,[dir_0],axis=0)#赋值，赋值，赋值！！！！！！！！！！！！！！！！！！！
        directions=np.append(directions,[dir_1],axis=0)
    print('分支方向\n',directions)
    return directions



    