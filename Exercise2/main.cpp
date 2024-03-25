#include <iostream>
#include "Eigen/Eigen"
#include <Eigen/LU>
#include <Eigen/QR>
#include <Eigen/Dense>
using namespace Eigen;
using namespace std;

int main()
{
    Matrix2d A1 {
        {5.547001962252291e-01, -3.770900990025203e-02}, {8.320502943378437e-01, -9.992887623566787e-01}
    };

    Matrix2d A2 {
        {5.547001962252291e-01, -5.540607316466765e-01}, {8.320502943378437e-01, -8.324762492991313e-01}
    };

    Matrix2d A3 {
        {5.547001962252291e-01, -5.547001955851905e-01}, {8.320502943378437e-01, -8.320502947645361e-01}
    };
    //cout<<A1<<endl<<A2<<endl<<A3<<endl;

    Vector2d b1 {
        {-5.169911863249772e-01, 1.672384680188350e-01}
    };

    Vector2d b2 {
        {-6.394645785530173e-04, 4.259549612877223e-04}
    };

    Vector2d b3 {
        {-6.400391328043042e-10, 4.266924591433963e-10}
    };

    HouseholderQR<MatrixXd> qr(A1.rows(), A1.cols());
    qr.compute(A1);
    MatrixXd q1 = qr.householderQ()*MatrixXd::Identity(A1.rows(), A1.cols());
    MatrixXd temp1 = qr.matrixQR().triangularView<Upper>();
    MatrixXd r1 = temp1.topRows(A1.cols());
    cout<<"La matrice A1 si decompone in Q1= "<<endl<<q1<<endl<<"e R1= "<<endl<<r1<<endl;
    //cout<<A1.inverse()<<endl;

    MatrixXd y = (q1.inverse())*b1;
    MatrixXd xQR = (r1.inverse())*y;
    cout<<xQR<<endl;
    Vector2d x_real = Vector2d::Constant(-1);
    Vector2d x_errQR = x_real-xQR;
    cout<<"Errore relativo per decomposizione QR= "<<x_errQR.norm()/xQR.norm()<<endl;

    Vector2d xLU = A1.partialPivLu().solve(b1);
    Vector2d x_errLU = x_real-xLU;
    cout<<"Errore relativo per decomposizione LU= "<<x_errLU.norm()/xLU.norm()<<endl;

    //ripeti per tutti gli altri sistemi










    //HouseholderQR<MatrixXd> qr(A2.rows(), A2.cols());
    //qr.compute(A2);
    //MatrixXd q2 = qr.householderQ()*MatrixXd::Identity(A2.rows(), A2.cols());
    //MatrixXd temp2 = qr.matrixQR().triangularView<Upper>();
    //MatrixXd r2 = temp2.topRows(A2.cols());
    //cout<<"La matrice A2 si decompone in Q2= "<<endl<<q2<<endl<<"e R2= "<<endl<<r2<<endl;

    //HouseholderQR<MatrixXd> qr(A3.rows(), A3.cols());
    //qr.compute(A3);
    //MatrixXd q3 = qr.householderQ()*MatrixXd::Identity(A3.rows(), A3.cols());
    //MatrixXd temp3 = qr.matrixQR().triangularView<Upper>();
    //MatrixXd r3 = temp3.topRows(A3.cols());
    //cout<<"La matrice A1 si decompone in Q1= "<<endl<<q1<<endl<<"e R1= "<<endl<<r1<<endl;












  return 0;
}
