import polyscope as ps
import polyscope_show as pss
import io_obj as io

if __name__ == "__main__":
    # point_cloud_path = "../ExperimentData/normalization/down_sampled"
    point_cloud_path = "/Users/wuhan/wuhan/CodingSpace/MultilevelDividedSkeletonExtraction/ExperimentData/normalization/obj/tree4_84336_nor.obj"
    point_cloud = io.load_point_cloud_obj(point_cloud_path)
    pss.init()
    pss.add_point_cloud(point_cloud,radius=0.00146)

    # #读取boundingbox
    # bounding_box_path = "/Users/wuhan/wuhan/CodingSpace/MultilevelDividedSkeletonExtraction/ExperimentData/normalization/obj/tree4_84336_nor_bounding_box.obj"
    # points,edges = io.load_curves_obj(bounding_box_path)
    # pss.add_skeleton(points,edges)
    pss.show()