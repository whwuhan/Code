#include <iostream>
#include <basic/cube.h>
#include <utils/io/io_obj.h>
#include <basic/abstract_data_type/octree.h>
using namespace std;
using namespace wh::basic;
using namespace wh::basic::adt;
using namespace wh::utils::io;
using namespace Eigen;
int main(){
    Polygon_mesh mesh;
    load_polygon_mesh_obj("Bunny_mesh.obj",&mesh);
    
    // mesh.tri_mesh_subdivision();
    // set<Edge> unordered_edges=mesh.creat_ordered_edges();
    // for(auto iter=unordered_edges.begin();iter!=unordered_edges.end();iter++){
    //     cout<<iter->fir_ver_index<<" "<<iter->sec_ver_index<<endl;
    // }

    // auto unordered_edges=mesh.creat_unordered_edges();
    // auto res=mesh.find_edge_near_faces(unordered_edges);
    // for(auto iter_1=res.begin();iter_1!=res.end();iter_1++){
    //     for(auto iter_2=(*iter_1).second.begin();iter_2!=(*iter_1).second.end();iter_2++){
    //         cout<<"faces:"<<(*iter_2)<<" ";
    //     }
    //     cout<<endl;
    // }

    save_polygon_mesh_obj("Bunny_mesh_1.obj",&mesh);
}