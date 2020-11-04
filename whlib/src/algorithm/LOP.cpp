#include <algorithm/LOP.h>
#include <basic/point_cloud.h>
#include <basic/point3d.h>
#include <utils/string_lib.h>
#include <cmath>
using namespace std;
using namespace Eigen;
using namespace wh::basic;
using namespace wh::alg;
using namespace wh::utils::io;
using namespace wh::utils;
//构造函数
wh::alg::LOPParameter::LOPParameter():iter(10),h(1.0),mu(0.45),amount(1000){}

wh::alg::LOPParameter::LOPParameter(int iter,int amount,double r,double h,double mu):
iter(iter),amount(amount),h(h),mu(mu)
{}

wh::alg::LOP::LOP(){}

wh::alg::LOP::LOP(
                std::string& fileName,
                Eigen::MatrixXd& X,
                Eigen::MatrixXd& P,
                LOP_PARAMETER& parameters):fileName(fileName),X(X),P(P),parameters(parameters){
                    Point_cloud pointCloud;
                    load_point_cloud_obj(fileName,&pointCloud);
                    P = pointCloud.points;
                }

void wh::alg::LOP::setFileName(const std::string fileName){
    this->fileName = fileName;
}

void wh::alg::LOP::init(){
    if(fileName == ""){
        cout<< "init() 请先设置原始点云路径" <<endl;
        return ;
    }
    auto fileNameSplit = split(fileName,"./\\");
    string outFileName = fileNameSplit[fileNameSplit.size()-2];
    Point_cloud pointCloud;
    load_point_cloud_obj(fileName,&pointCloud);
    P = pointCloud.points;
    if(P.rows() != 0 && P.cols() != 0){
        X = Eigen::MatrixXd::Random(parameters.amount,P.cols()) * P.maxCoeff();
        string randSaveName = outFileName + "_rand.obj";
        cout<< "随机初始化点云保存到文件:"<< randSaveName <<endl;
        Point_cloud randPointCloud(X);
        save_point_cloud_obj(randSaveName,&randPointCloud);

        MatrixXd X = getXPrime1();//从随机点得到初始迭代点
        cout<<"正在获取初始迭代点"<<endl;
        string initSaveName = outFileName + "_init.obj";
        cout<< "初始迭代点云保存到文件:"<< initSaveName <<endl;
        Point_cloud initPointCloud(X);
        save_point_cloud_obj(initSaveName,&initPointCloud);
    }else{
        cerr<<"init() LOP初始化失败，没有获取原始点云" << endl;
    }
}

void wh::alg::LOP::run(){
    if(P.rows() == 0 || P.cols() == 0){
        cerr<<"run() 没有原始点云"<<endl;
        return;
    }
    if(X.rows() == 0 || X.cols() == 0){
        cerr<<"run() 没有使用init()初始化参数"<<endl;
        return;
    }
    auto fileNameSplit = split(fileName,"./\\");
    string outFileName = fileNameSplit[fileNameSplit.size()-2];
    for(int iter=0;iter<parameters.iter;iter++){
        cout<<"第"<<iter+1<<"次迭代开始"<<endl;
        X = LOPOuter(X,P);
        string saveName = outFileName+"_iter_"+to_string(iter+1)+".obj";
        cout<<"第"<<iter+1<<"次迭代结束，保存到文件"<< saveName <<endl;
        Point_cloud pointCloud(X);
        save_point_cloud_obj(saveName,&pointCloud);
    }
}


double wh::alg::LOP::theta(double r){
    return exp( (-pow(r,2)) / pow(parameters.h/4, 2));
}

double wh::alg::LOP::eta(double r){
    return 1/3 * pow(r,3);
}

Eigen::MatrixXd wh::alg::LOP::getXPrime1(){
    int xSize = X.rows();
    int pSize = P.rows();
    RowVector3d resTop;
    double resBottom = 0.0;
    MatrixXd XPrime(X.rows(), X.cols());
    for(int i=0;i<xSize;i++){
        for(int j=0;j<pSize;j++){
            resTop += P.row(j) * theta( (P.row(j)-X.row(i)).norm());
            resBottom += theta( (P.row(j)-X.row(i)).norm());
        }
        XPrime.row(i) = resTop / resBottom;
        resTop = RowVector3d(0,0,0);
        resBottom = 0.0;
    }
    // cout<<"getXPrime1"<<endl;
    return XPrime;
}

double wh::alg::LOP::getAlpha(const Eigen::RowVector3d& xPrime,const Eigen::RowVector3d& p){
    double resTop = theta((xPrime-p).norm());
    double resBottom = (xPrime-p).norm();
    // cout<<"getAlpha"<<endl;
    return resTop / resBottom;
}

double wh::alg::LOP::getBeta(const Eigen::RowVector3d& x,const Eigen::RowVector3d& xPrime){
    double resTop = theta((xPrime-x).norm());
    double resBottom = (xPrime-x).norm();
    // cout<<"getBeta"<<endl;
    return resTop * resBottom;
}
Eigen::RowVector3d wh::alg::LOP::LOPInner(const Eigen::RowVector3d& xPrime){
        RowVector3d fir;
        RowVector3d sec;
        int xSize = X.rows();
        int pSize = P.rows();
        // cout<<"getAlpha"<<endl;
        double alphaTotal = 0.0;
        for(int j=0;j<pSize;j++){
            alphaTotal += getAlpha(xPrime,P.row(j));
        }
        for(int j=0;j<pSize;j++){
            fir += (P.row(j) * getAlpha(xPrime,P.row(j))) / alphaTotal;
        }

        double betaTotal = 0.0;
        for(int i=0;i<xSize;i++){
            if(xPrime != X.row(i)){
                betaTotal += getBeta(X.row(i),xPrime);
            }
        }
        for(int i=0;i<xSize;i++){
            if(xPrime != X.row(i)){
                sec += (xPrime - X.row(i)) * getBeta(X.row(i),xPrime) / betaTotal;
            }
        }
        // cout<<"LOPInner"<<endl;
        return fir + parameters.mu * sec;
    }

Eigen::MatrixXd wh::alg::LOP::LOPOuter(const Eigen::MatrixXd& X,const Eigen::MatrixXd& P){
    int xSize = X.rows();
    MatrixXd XPrimeKAddOne(X.rows(),X.cols());
    for(int i=0;i<xSize;i++){
        XPrimeKAddOne.row(i) = LOPInner(X.row(i));
    }
    return XPrimeKAddOne;
}