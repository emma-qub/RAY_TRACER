#include "ImplicitSurface.h"
#include "Solver.h"

#include <algorithm>

using namespace std;

ImplicitSurface::ImplicitSurface(const Color &color, const Material &material, const QString &equation) :
    Shape(color, material),
    _equation(equation) {

    _parsedEq = ParserExpr(_equation);

    initMatrixAdConstant();
    initMatrixDerivated();

    //cerr << _deg4Mat << endl << _deg3Mat << endl << _deg2Mat << endl << _deg1Mat << endl;
}

ImplicitSurface::ImplicitSurface(const ImplicitSurface &implcitSurface) :
    Shape(implcitSurface._color, implcitSurface._material) {
    _equation = implcitSurface._equation;
    _parsedEq = implcitSurface._parsedEq;
    _deg4Mat = implcitSurface._deg4Mat;
    _deg3Mat = implcitSurface._deg3Mat;
    _deg2Mat = implcitSurface._deg2Mat;
    _deg1Mat = implcitSurface._deg1Mat;
    _deg4MatDerX = implcitSurface._deg4MatDerX;
    _deg4MatDerY = implcitSurface._deg4MatDerY;
    _deg4MatDerZ = implcitSurface._deg4MatDerZ;
    _deg3MatDerX = implcitSurface._deg3MatDerX;
    _deg3MatDerY = implcitSurface._deg3MatDerY;
    _deg3MatDerZ = implcitSurface._deg3MatDerZ;
    _deg2MatDerX = implcitSurface._deg2MatDerX;
    _deg2MatDerY = implcitSurface._deg2MatDerY;
    _deg2MatDerZ = implcitSurface._deg2MatDerZ;
    _deg1MatDerX = implcitSurface._deg1MatDerX;
    _deg1MatDerY = implcitSurface._deg1MatDerY;
    _deg1MatDerZ = implcitSurface._deg1MatDerZ;
    _constant = implcitSurface._constant;
}

ImplicitSurface::~ImplicitSurface() {
}

void ImplicitSurface::initMatrixAdConstant() {
    _constant = 0.0;
    _deg4Mat = doubleMat(5, 5);
    _deg3Mat = doubleMat(4, 4);
    _deg2Mat = doubleMat(3, 3);
    _deg1Mat = doubleMat(2, 2);

    QStringList monomesList = _parsedEq.getMonomes();
    for (int k = 0; k < monomesList.size(); k++) {
        QVector<int> currExpos =  _parsedEq.getExpoAt(k);
        int currXExpo = currExpos.at(0);
        int currYExpo = currExpos.at(1);
        int currZExpo = currExpos.at(2);
        int currDegree = currXExpo + currYExpo + currZExpo;
        int currConstant = _parsedEq.getConstAt(k);

        switch(currDegree) {
        case 0:
            _constant += currConstant;
            break;
        case 1:
            _deg1Mat.setElementK(currYExpo, currXExpo, _deg1Mat(currYExpo, currXExpo) + currConstant);
            break;
        case 2:
            _deg2Mat.setElementK(currYExpo, currXExpo, _deg2Mat(currYExpo, currXExpo) + currConstant);
            break;
        case 3:
            _deg3Mat.setElementK(currYExpo, currXExpo, _deg3Mat(currYExpo, currXExpo) + currConstant);
            break;
        case 4:
            _deg4Mat.setElementK(currYExpo, currXExpo, _deg4Mat(currYExpo, currXExpo) + currConstant);
            break;
        default:
            break;
        }
    }
}

void ImplicitSurface::initMatrixDerivated() {
    _deg4MatDerX = derivateX(_deg4Mat);
    _deg4MatDerY = derivateY(_deg4Mat);
    _deg4MatDerZ = derivateZ(_deg4Mat);

    _deg3MatDerX = derivateX(_deg3Mat);
    _deg3MatDerY = derivateY(_deg3Mat);
    _deg3MatDerZ = derivateZ(_deg3Mat);

    _deg2MatDerX = derivateX(_deg2Mat);
    _deg2MatDerY = derivateY(_deg2Mat);
    _deg2MatDerZ = derivateZ(_deg2Mat);

    _deg1MatDerX = derivateX(_deg1Mat);
    _deg1MatDerY = derivateY(_deg1Mat);
    _deg1MatDerZ = derivateZ(_deg1Mat);
}

doubleMat ImplicitSurface::derivateX(const doubleMat& matrix) const {
    int deg = matrix.nbLines() - 1;
    doubleMat derivatedMatrix(deg, deg);

    for (int i = deg-1; i >=0 ; i--) {
        for (int j = (deg-1-i); j >= 0; j--) {
            derivatedMatrix.setElementK(i, j, (j+1) * matrix(i, j+1));
        }
    }

    return derivatedMatrix;
}

doubleMat ImplicitSurface::derivateY(const doubleMat& matrix) const {
    int deg = matrix.nbLines() - 1;
    doubleMat derivatedMatrix(deg, deg);

    for (int i = deg-1; i >=0 ; i--) {
        for (int j = (deg-1-i); j >= 0; j--) {
            derivatedMatrix.setElementK(i, j, (i+1) * matrix(i+1, j));
        }
    }

    return derivatedMatrix;
}

doubleMat ImplicitSurface::derivateZ(const doubleMat& matrix) const {
    int deg = matrix.nbLines() - 1;
    doubleMat derivatedMatrix(deg, deg);

    for (int i = deg-1; i >=0 ; i--) {
        for (int j = (deg-1-i); j >= 0; j--) {
            derivatedMatrix.setElementK(i, j, (deg - (i+j)) * matrix(i, j));
        }
    }

    return derivatedMatrix;
}

double ImplicitSurface::evaluate(const Vector3& ptIntersect, const doubleMat& matrix) const {
    double res = 0.0;
    double x0 = ptIntersect[0];
    double y0 = ptIntersect[1];
    double z0 = ptIntersect[2];
    double deg = matrix.nbColumns() - 1;

    // Lecture de la matrice dans l'ordre lexicographique de la base x^i*y^j*z^k
    for (int i = deg; i >=0 ; i--) {
        for (int j = (deg-i); j >= 0; j--) {
            res += matrix(j, i)*pow(x0, i)*pow(y0, j)*pow(z0, deg - (i+j));
        }
    }

    return res;
}

Vector3 ImplicitSurface::normal(const Vector3& ptIntersect) const {
    double x = evaluate(ptIntersect, _deg4MatDerX)
             + evaluate(ptIntersect, _deg3MatDerX)
             + evaluate(ptIntersect, _deg2MatDerX)
             + evaluate(ptIntersect, _deg1MatDerX);
    double y = evaluate(ptIntersect, _deg4MatDerY)
             + evaluate(ptIntersect, _deg3MatDerY)
             + evaluate(ptIntersect, _deg2MatDerY)
             + evaluate(ptIntersect, _deg1MatDerY);
    double z = evaluate(ptIntersect, _deg4MatDerZ)
             + evaluate(ptIntersect, _deg3MatDerZ)
             + evaluate(ptIntersect, _deg2MatDerZ)
             + evaluate(ptIntersect, _deg1MatDerZ);

    return Vector3(x, y, z);
}

vector<double> ImplicitSurface::ensIntersect(const Ray& rayon) const {
    vector<double> res;

    double ox = rayon[0][0];
    double oy = rayon[0][1];
    double oz = rayon[0][2];
    double dx = rayon[1][0];
    double dy = rayon[1][1];
    double dz = rayon[1][2];

    double a4 = _deg4Mat(0, 4);
    double b4 = _deg4Mat(1, 3);
    double c4 = _deg4Mat(0, 3);
    double d4 = _deg4Mat(2, 2);
    double e4 = _deg4Mat(1, 2);
    double f4 = _deg4Mat(0, 2);
    double g4 = _deg4Mat(3, 1);
    double h4 = _deg4Mat(2, 1);
    double i4 = _deg4Mat(1, 1);
    double j4 = _deg4Mat(0, 1);
    double k4 = _deg4Mat(4, 0);
    double l4 = _deg4Mat(3, 0);
    double m4 = _deg4Mat(2, 0);
    double n4 = _deg4Mat(1, 0);
    double o4 = _deg4Mat(0, 0);
    double a3 = _deg3Mat(0, 3);
    double b3 = _deg3Mat(1, 2);
    double c3 = _deg3Mat(0, 2);
    double d3 = _deg3Mat(2, 1);
    double e3 = _deg3Mat(1, 1);
    double f3 = _deg3Mat(0, 1);
    double g3 = _deg3Mat(3, 0);
    double h3 = _deg3Mat(2, 0);
    double i3 = _deg3Mat(1, 0);
    double j3 = _deg3Mat(0, 0);
    double a2 = _deg2Mat(0, 2);
    double b2 = _deg2Mat(1, 1);
    double c2 = _deg2Mat(0, 1);
    double d2 = _deg2Mat(2, 0);
    double e2 = _deg2Mat(1, 0);
    double f2 = _deg2Mat(0, 0);
    double a1 = _deg1Mat(0, 1);
    double b1 = _deg1Mat(1, 0);
    double c1 = _deg1Mat(0, 0);
    double a0 = _constant;


    double alpha = 0.0;
    alpha += a4*pow(dx, 4);
    alpha += b4*pow(dx, 3)*dy;
    alpha += c4*pow(dx, 3)*dz;
    alpha += d4*pow(dx, 2)*pow(dy, 2);
    alpha += e4*pow(dx, 2)*dy*dz;
    alpha += f4*pow(dx, 2)*pow(dz, 2);
    alpha += g4*dx*pow(dy, 3);
    alpha += h4*dx*pow(dy, 2)*dz;
    alpha += i4*dx*dy*pow(dz, 2);
    alpha += j4*dx*pow(dz, 3);
    alpha += k4*pow(dy, 4);
    alpha += l4*pow(dy, 3)*dz;
    alpha += m4*pow(dy, 2)*pow(dz, 2);
    alpha += n4*dy*pow(dz, 3);
    alpha += o4*pow(dz, 4);
    double beta = 0.0;
    beta += a4*4*ox*pow(dx, 3);
    beta += b4*(3*ox*pow(dx, 2)*dy+pow(dx, 3)*oy);
    beta += c4*(3*ox*pow(dx, 2)*dz+pow(dx, 3)*oz);
    beta += d4*2*(ox*dx*pow(dy, 2)+pow(dx, 2)*oy*dy);
    beta += e4*(2*ox*dx*dy*dz+pow(dx, 2)*(oy*dz+dy*oz));
    beta += f4*2*(ox*dx*pow(dz, 2)+pow(dx, 2)*oz*dz);
    beta += g4*(3*oy*pow(dy, 2)*dx+pow(dy, 3)*ox);
    beta += h4*(2*oy*dy*dx*dz+pow(dy, 2)*(ox*dz+dx*oz));
    beta += i4*(2*oz*dz*dx*dy+pow(dz, 2)*(ox*dy+dx*oy));
    beta += j4*(3*oz*pow(dz, 2)*dx+pow(dz, 3)*ox);
    beta += k4*4*oy*pow(dy, 3);
    beta += l4*(3*oy*pow(dy, 2)*dz+pow(dy, 3)*oz);
    beta += m4*2*(oy*dy*pow(dz, 2)+pow(dy, 2)*oz*dz);
    beta += n4*(3*oz*pow(dz, 2)*dy+pow(dz, 3)*oy);
    beta += o4*4*oz*pow(dz, 3);
    beta += a3*pow(dx, 3);
    beta += b3*pow(dx, 2)*dy;
    beta += c3*pow(dx, 2)*dz;
    beta += d3*pow(dy, 2)*dx;
    beta += e3*dx*dy*dz;
    beta += f3*pow(dz, 2)*dx;
    beta += g3*pow(dy, 3);
    beta += h3*pow(dy, 2)*dz;
    beta += i3*pow(dz, 2)*dy;
    beta += j3*pow(dz, 3);
    double gamma = 0.0;
    gamma += a4*6*pow(ox, 2)*pow(dx, 2);
    gamma += b4*3*(pow(ox, 2)*dx*dy+ox*pow(dx, 2)*oy);
    gamma += c4*3*(pow(ox, 2)*dx*dz+ox*pow(dx, 2)*oz);
    gamma += d4*(pow(ox, 2)*pow(dy, 2)+4*ox*dx*oy*dy+pow(dx, 2)*pow(oy, 2));
    gamma += e4*(pow(ox, 2)*dy*dz+2*ox*dx*(oy*dz+dy*oz)+pow(dx, 2)*oy*oz);
    gamma += f4*(pow(ox, 2)*pow(dz, 2)+4*ox*dx*oz*dz+pow(dx, 2)*pow(oz, 2));
    gamma += g4*3*(pow(oy, 2)*dy*dx+oy*pow(dy, 2)*ox);
    gamma += h4*(pow(oy, 2)*dx*dz+2*oy*dy*(ox*dz+dx*oz)+pow(dy, 2)*ox*oz);
    gamma += i4*(pow(oz, 2)*dx*dy+2*oz*dz*(ox*dy+dx*oy)+pow(dz, 2)*ox*oy);
    gamma += j4*3*(pow(oz, 2)*dz*dx+oz*pow(dz, 2)*ox);
    gamma += k4*6*pow(oy, 2)*pow(dy, 2);
    gamma += l4*3*(pow(oy, 2)*dy*dz+oy*pow(dy, 2)*oz);
    gamma += m4*(pow(oy, 2)*pow(dz, 2)+4*oy*dy*oz*dz+pow(dy, 2)*pow(oz, 2));
    gamma += n4*3*(pow(oz, 2)*dz*dy+oz*pow(dz, 2)*oy);
    gamma += o4*6*pow(oz, 2)*pow(dz, 2);
    gamma += a3*3*ox*pow(dx, 2);
    gamma += b3*(2*ox*dx*dy+pow(dx, 2)*oy);
    gamma += c3*(2*ox*dx*dz+pow(dx, 2)*oz);
    gamma += d3*(2*oy*dy*dx+pow(dy, 2)*ox);
    gamma += e3*((ox*dy+dx*oy)*dz+dx*dy*oz);
    gamma += f3*(2*oz*dz*dx+pow(dz, 2)*ox);
    gamma += g3*3*oy*pow(dy, 2);
    gamma += h3*(2*oy*dy*dz+pow(dy, 2)*oz);
    gamma += i3*(2*oz*dz*dy+pow(dz, 2)*oy);
    gamma += j3*3*oz*pow(dz, 2);
    gamma += a2*pow(dx, 2);
    gamma += b2*dx*dy;
    gamma += c2*dx*dz;
    gamma += d2*pow(dy, 2);
    gamma += e2*dy*dz;
    gamma += f2*pow(dz, 2);
    double delta = 0.0;
    delta += a4*4*pow(ox, 3)*dx;
    delta += b4*(pow(ox, 3)*dy+3*pow(ox, 2)*dx*oy);
    delta += c4*(pow(ox, 3)*dz+3*pow(ox, 2)*dx*oz);
    delta += d4*2*(pow(ox, 2)*oy*dy+ox*dx*pow(oy, 2));
    delta += e4*(pow(ox, 2)*(oy*dz+dy*oz)+2*ox*dx*oy*oz);
    delta += f4*2*(pow(ox, 2)*oz*dz+ox*dx*pow(oz, 2));
    delta += g4*(pow(oy, 3)*dx+3*pow(oy, 2)*dy*ox);
    delta += h4*(pow(oy, 2)*(ox*dz+dx*oz)+2*oy*dy*ox*oz);
    delta += i4*(pow(oz, 2)*(ox*dy+dx*oy)+2*oz*dz*ox*oy);
    delta += j4*(pow(oz, 3)*dx+3*pow(oz, 2)*dz*ox);
    delta += k4*4*pow(oy, 3)*dy;
    delta += l4*(pow(oy, 3)*dz+3*pow(oy, 2)*dy*oz);
    delta += m4*2*(pow(oy, 2)*oz*dz+oy*dy*pow(oz, 2));
    delta += n4*(pow(oz, 3)*dy+3*pow(oz, 2)*dz*oy);
    delta += o4*4*pow(oz, 3)*dz;
    delta += a3*3*pow(ox, 2)*dx;
    delta += b3*(pow(ox, 2)*dy+2*ox*dx*oy);
    delta += c3*(pow(ox, 2)*dz+2*ox*dx*oz);
    delta += d3*(pow(oy, 2)*dx+2*oy*dy*ox);
    delta += e3*(ox*oy*dz+(ox*dy+dx*oy)*oz);
    delta += f3*(pow(oz, 2)*dx+2*oz*dz*ox);
    delta += g3*3*pow(oy, 2)*dy;
    delta += h3*(pow(oy, 2)*dz+2*oy*dy*oz);
    delta += i3*(pow(oz, 2)*dy+2*oz*dz*oy);
    delta += j3*3*pow(oz, 2)*dz;
    delta += a2*2*ox*dx;
    delta += b2*(ox*dy+dx*oy);
    delta += c2*(ox*dz+dx*oz);
    delta += d2*2*oy*dy;
    delta += e2*(oy*dz+dy*oz);
    delta += f2*2*oz*dz;
    delta += a1*dx;
    delta += b1*dy;
    delta += c1*dz;
    double epsilon = 0.0;
    epsilon += a4*pow(ox, 4);
    epsilon += b4*pow(ox, 3)*oy;
    epsilon += c4*pow(ox, 3)*oz;
    epsilon += d4*pow(ox, 2)*pow(oy, 2);
    epsilon += e4*pow(ox, 2)*oy*oz;
    epsilon += f4*pow(ox, 2)*pow(oz, 2);
    epsilon += g4*ox*pow(oy, 3);
    epsilon += h4*ox*pow(oy, 2)*oz;
    epsilon += i4*ox*oy*pow(oz, 2);
    epsilon += j4*ox*pow(oz, 3);
    epsilon += k4*pow(oy, 4);
    epsilon += l4*pow(oy, 3)*oz;
    epsilon += m4*pow(oy, 2)*pow(oz, 2);
    epsilon += n4*oy*pow(oz, 3);
    epsilon += o4*pow(oz, 4);
    epsilon += a3*pow(ox, 3);
    epsilon += b3*pow(ox, 2)*oy;
    epsilon += c3*pow(ox, 2)*oz;
    epsilon += d3*ox*pow(oy, 2);
    epsilon += e3*ox*oy*oz;
    epsilon += f3*ox*pow(oz, 2);
    epsilon += g3*pow(oy, 3);
    epsilon += h3*pow(oy, 2)*oz;
    epsilon += i3*oy*pow(oz, 2);
    epsilon += j3*pow(oz, 3);
    epsilon += a2*pow(ox, 2);
    epsilon += b2*ox*oy;
    epsilon += c2*ox*oz;
    epsilon += d2*pow(oy, 2);
    epsilon += e2*oy*oz;
    epsilon += f2*pow(oz, 2);
    epsilon += a1*ox;
    epsilon += b1*oy;
    epsilon += c1*oz;
    epsilon += a0;


    /*double alpha = 0.0;
    double beta = 0.0;*/
/*
    cerr << "a2:" << a2 << endl;
    cerr << "b2:" << b2 << endl;
    cerr << "c2:" << c2 << endl;
    cerr << "d2:" << d2 << endl;
    cerr << "e2:" << e2 << endl;
    cerr << "f2:" << f2 << endl;
    cerr << "a1:" << a1 << endl;
    cerr << "b1:" << b1 << endl;
    cerr << "c1:" << c1 << endl;
    cerr << "a0:" << a0 << endl;

    double alpha = a2*dx*dx + d2*dy*dy + f2*dz*dz
                 + 2*b2*dx*dy + 2*c2*dx*dz + 2*e2*dy*dz;
    double beta = 2*a2*ox*dx + 2*d2*oy*dy + 2*f2*oz*dz
                + 2*b2*(ox*dy+oy*dx) + 2*c2*(ox*dz+oz*dx) + 2*e2*(oy*dz+oz*dy)
                + a1*dx + b1*dy + c1*dz;
    double gamma = a2*ox*ox + d2*oy*oy + f2*oz*oz
                + 2*b2*ox*oy + 2*c2*ox*oz + 2*e2*oy*oz
                + a1*ox + b1*oy + c1*oz + a0;
    double delta = beta*beta - 4*alpha*gamma;
    delta = sqrt(delta);
    if (delta == 0 && -beta / (2 * alpha) > 0) {
        res.push_back(-beta / (2 * alpha));
    } else if (delta > 0) {
        double t1 = (-beta - delta) / (2 * alpha);
        double t2 = (-beta + delta) / (2 * alpha);
        if (t1 > 0)
            res.push_back(t1);
        if (t2 > 0)
            res.push_back(t2);
    }

*/
    if (alpha != 0) {
        res = Solver::solve4degree(alpha, beta, gamma, delta, epsilon);
    } else {
        if (beta != 0) {
            res = Solver::solve3degree(beta, gamma, delta, epsilon);
        } else {
            if (gamma != 0) {
                res = Solver::solve2degree(gamma, delta, epsilon);
            }
        }
    }
    int k = 0;
    for (; k < res.size(); k++) {
        if (res.at(k) >= 0) {
            break;
        }
    }

    res.erase(res.begin(), res.begin()+k);

    sort(res.begin(), res.end());
    return res;
}

bool ImplicitSurface::belongsTo(const Vector3& ptIntersect) const {
    return false;
}


Shape* ImplicitSurface::clone() const {
    return new ImplicitSurface(*this);
}
