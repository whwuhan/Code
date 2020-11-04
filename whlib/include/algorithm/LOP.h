#ifndef LOP_H
#define LOP_H
#include <Eigen/Dense>
#include <utils/io/io_obj.h>
namespace wh{
    namespace alg{
        typedef struct LOPParameter{
            int iter;   //迭代次数
            int amount; //采样点数
            double h;   //theta范围半径
            double mu;  //不动点迭代权重
            LOPParameter();
            LOPParameter(int iter,int amount,double r,double h,double mu);
        } LOP_PARAMETER;
        class LOP{
        public:
            LOP();
            LOP(
                std::string& fileName,
                Eigen::MatrixXd& X,
                Eigen::MatrixXd& P,
                LOP_PARAMETER& parameters
            );
            std::string fileName;//点云文件路径
            Eigen::MatrixXd X;  //初始点云
            Eigen::MatrixXd P;  //采样原始点云
            struct LOPParameter parameters;//其他参数
            void setFileName(const std::string fileName);
            void init();//初始化
            void run();//开始运行
        private:
            double theta(double r);
            double eta(double r);
            Eigen::MatrixXd getXPrime1();
            double getAlpha(const Eigen::RowVector3d& xPrime, const Eigen::RowVector3d& p);
            double getBeta(const Eigen::RowVector3d& x,const Eigen::RowVector3d& xPrime);

            Eigen::RowVector3d LOPInner(const Eigen::RowVector3d& xPrime);

            Eigen::MatrixXd LOPOuter(const Eigen::MatrixXd& X,const Eigen::MatrixXd& P);
        };
        

    }// namespace alg
} // namespace wh

#endif