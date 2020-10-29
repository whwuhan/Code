#include <basic/edge.h>
using namespace wh::basic;
using namespace std;
Edge::Edge():fir_ver_index(0),sec_ver_index(0){

}

Edge::Edge(unsigned int fir_ver_index,unsigned int sec_ver_index,bool unordered){
    //unordered:是否无序
    if(unordered){
        if(fir_ver_index<sec_ver_index){
        this->fir_ver_index=fir_ver_index;
        this->sec_ver_index=sec_ver_index;
        }else{
            this->fir_ver_index=sec_ver_index;
            this->sec_ver_index=fir_ver_index;
        }
    }else{
        this->fir_ver_index=fir_ver_index;
        this->sec_ver_index=sec_ver_index;
    }
}

bool Edge::operator<(const Edge& edge)const{
    if(fir_ver_index<edge.fir_ver_index){
        return true;
    }else if(fir_ver_index==edge.fir_ver_index){
        if(sec_ver_index<edge.sec_ver_index) return true;
    }
    return false;
}