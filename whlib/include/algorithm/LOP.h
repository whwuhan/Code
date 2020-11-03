#ifndef LOP_H
#define LOP_H
#include <Eigen/Dense>
namespace wh
{
    namespace alg
    {
        double theta(double r, double h=1);
        double eta(double r);
        Eigen::MatrixXd getXPrime1(const Eigen::MatrixXd& X,const Eigen::MatrixXd& P);
        double getAlpha(const Eigen::RowVector3d& xPrime, const Eigen::RowVector3d& p);
        double getBeta(const Eigen::RowVector3d& x,const Eigen::RowVector3d& xPrime);
        Eigen::RowVector3d LOPInner(
            const Eigen::RowVector3d& xPrime,
            const Eigen::MatrixXd& X,
            const Eigen::MatrixXd& P,
            double mu=0.45);
        Eigen::MatrixXd LOP(const Eigen::MatrixXd& X,const Eigen::MatrixXd& P);
    }// namespace alg
} // namespace wh

#endif