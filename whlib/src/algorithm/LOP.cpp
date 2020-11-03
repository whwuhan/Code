#include <algorithm/LOP.h>
#include <basic/point_cloud.h>
#include <basic/point3d.h>
#include <cmath>
using namespace std;
using namespace Eigen;
using namespace wh::basic;
using namespace wh::alg;
double wh::alg::theta(double r, double h){
    return exp( (-pow(r,2)) / pow(h/4, 2));
}

double wh::alg::eta(double r){
    return 1/3 * pow(r,3);
}

Eigen::MatrixXd wh::alg::getXPrime1(const Eigen::MatrixXd& X,const Eigen::MatrixXd& P){
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

double wh::alg::getAlpha(const Eigen::RowVector3d& xPrime,const Eigen::RowVector3d& p){
    double resTop = theta((xPrime-p).norm());
    double resBottom = (xPrime-p).norm();
    // cout<<"getAlpha"<<endl;
    return resTop / resBottom;
}

double wh::alg::getBeta(const Eigen::RowVector3d& x,const Eigen::RowVector3d& xPrime){
    double resTop = theta((xPrime-x).norm());
    double resBottom = (xPrime-x).norm();
    // cout<<"getBeta"<<endl;
    return resTop * resBottom;
}
Eigen::RowVector3d wh::alg::LOPInner(
    const Eigen::RowVector3d& xPrime,
    const Eigen::MatrixXd& X,
    const Eigen::MatrixXd& P,
    double mu
    ){
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
        return fir + mu * sec;
    }

Eigen::MatrixXd wh::alg::LOP(const Eigen::MatrixXd& X,const Eigen::MatrixXd& P){
    int xSize = X.rows();
    MatrixXd XPrimeKAddOne(X.rows(),X.cols());
    for(int i=0;i<xSize;i++){
        XPrimeKAddOne.row(i) = LOPInner(X.row(i),X,P);
    }
    return XPrimeKAddOne;
}