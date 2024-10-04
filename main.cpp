//矩阵定义与基本运算
#include <Eigen/Core>
//额外的矩阵运算
#include <Eigen/Dense>
#include <spdlog/spdlog.h>
#include "formatter.hpp"
//Matrix <Scalar, Rows, Cols, Options>

using Eigen::Matrix2d;
using Eigen::Vector2d;

long id = 2234116136;
const double step = 0.5;
const double derta = 0.01;
const int x = 827;
const int y = 1709;
const double d = 1e-8;

double f (Vector2d v){
    return v.x() * v.x() + v.y() * v.y();
}

double dv_p (Vector2d v, int pt) {
    Vector2d vp = v;
    vp(pt, 0) = (v(pt, 0) + d);
    return (f(vp) - f(v)) / d;
}

Matrix2d Hes (Vector2d v){
    Matrix2d cur;
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            if (i != j) {
                cur << 0,0,
                    0,0;
            }
            else {
                cur << 2,0,
                    0,2;
            }
        }
    }
    cur = cur.inverse().eval();
    return cur;
}

int main(){
    spdlog::set_level(spdlog::level::debug);

    Vector2d v((id % x) * 1.0, (id % y) * 1.0);
    while (true) {
        spdlog::debug(v);
        Vector2d dv(2 * v.x(), 2 * v.y()); // 梯度
        Matrix2d Hessian;
        Hessian = Hes(v);
        Vector2d vt = v - (step * (Hessian * dv));
        if ((vt - v).norm() < derta) {
            spdlog::info(f(vt));
            break;
        }
        else {
            v = vt;
        }
    }
    return 0;
}