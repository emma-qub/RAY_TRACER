#include <QApplication>
#include <QtGui>

#include "MainWindow.h"
//#include "Solver.h"



#include "MatrixOpp.h"


int main(int argc, char** argv) {

    //ImplicitSurface s(Color(), Material(), "x^3+x^2y+x^2z+xy^2+xyz+xz^2+y^3+y^2z+yz^2+z^3+x^2+xy+xz+y^2+yz+z^2+x+y+z-9");
    //ImplicitSurface s(Color(), Material(), "x^2+y^2+z^2-9");
    //ImplicitSurface s(Color(), Material(), "2x^4-3xy+5xz^2+yz^2-xy+4y-6+2z^3+3z^2y^2");
    //ImplicitSurface s(Color(), Material(), "x^2+y^2+z^2-9");
    /*cerr << s.getEquation().toStdString() << endl;
    cerr << s.getParsedEq().getFormatedExpr().toStdString() << endl;
    cerr << s.getConstant() << endl;
    cerr << s.getDeg1Mat() << endl;
    cerr << s.getDeg2Mat() << endl;
    cerr << s.getDeg3Mat() << endl;
    cerr << s.getDeg4Mat() << endl;*/
    //cerr << s.normal(Vector3(3, 1, 2)) << endl;
    //cerr << s.ensIntersect(Ray(Vector3(-4, 0, 0), Vector3(1, 0, 0))).at(0) << endl;
    //cerr << s.ensIntersect(Ray(Vector3(-4, 0, 0), Vector3(1, 0, 0))).at(1) << endl;


    //vector<double> sol3 = Solver::getRealSortedSol(Solver::solve3degree(.0, .0, .0, .0));
    //vector<double> sol3 = Solver::getRealSortedSol(Solver::solve3degree(1.0, 2.0, 1.0, 0.0));
    //vector<double> sol3 = Solver::getRealSortedSol(Solver::solve3degree(1.0, 0.0, -1.0, 0.0));
    //vector<double> sol3 = Solver::getRealSortedSol(Solver::solve3degree(1.0, -3.0, 3.0, -1.0));
    //vector<double> sol3 = Solver::getRealSortedSol(Solver::solve3degree(1.0, -2.0, -1.0, 2.0));

    //vector<double> sol3 = Solver::solve4degree(1.0, 4.0, 6.0, 4.0, 1.0);
    //vector<double> sol3 = Solver::solve4degree(1.0, -4.0, 6.0, -4.0, 1.0);
    //vector<double> sol3 = Solver::solve4degree(1.0, 2.0, 0.0, -2.0, -1.0);
    //vector<double> sol3 = Solver::solve4degree(1.0, 4.0, 3.0, -4.0, -4.0);
    //vector<double> sol3 = Solver::solve4degree(1.0, 0.0, -5.0, 0.0, 4.0);
    //vector<double> sol3 = Solver::solve4degree(1.0, 0.0, -2.0, 0.0, 1.0);
    //vector<double> sol3 = Solver::solve4degree(1.0, 3.0, 3.0, 1.0, 0.0);
    //vector<double> sol3 = Solver::solve4degree(1.0, 1.0, -1.0, -1.0, 0.0);
    //vector<double> sol3 = Solver::solve4degree(1.0, 2.0, -1.0, -2.0, 0.0);
    //vector<double> sol3 = Solver::solve4degree(1.0, 0.0, 0.0, 0.0, 1.0);
    /*

    for (int k = 0; k < sol3.size(); k++) {
        qDebug() << sol3.at(k);
    }

    cerr << "#######################" << endl;

    int k = 0;
    for (; k < sol3.size(); k++) {
        if (sol3.at(k) >= 0) {
            break;
        }
    }

    sol3.erase(sol3.begin(), sol3.begin()+k);

    for (int k = 0; k < sol3.size(); k++) {
        qDebug() << sol3.at(k);
    }

    //*/

    //vector<double> sol3 = Solver::getRealSortedSol(Solver::solve4degree(1.0, 1.0, -3.0, -1.0, 2.0));
    //vector<double> sol3 = Solver::getRealSortedSol(Solver::solve4degree(1.0, 0.0, -2.0, 0.0, 1.0));
    //vector<double> sol3 = Solver::getRealSortedSol(Solver::solve4degree(1.0, -4.0, 6.0, -4.0, 1.0));

/*
    cerr << "(2, 5, -12)" << endl;
    for (int k = 0; k < sol3.size(); k++) {
        cerr << sol3.at(k) << endl;
    }


    Vector3 OM(0, 0, 1);
    Vector3 Oz(0, 1, 0);
    double _theta = atan((cross_product(OM, Oz)).norm() / dot_product(OM, Oz));

    QMessageBox::information(0, "Test0", QSt
            vector<double> sol1 = Solver::solve2degree(2, 5, -12);ring::number(_theta/M_PI));

    Ray ray(Vector3(0, 0, 0),
            Vector3(0, 1, 0)
         );

    Vector3 origin = ray[0];
    Vector3 direction = ray[1];
    Ray newRay(Vector3(-sin(_theta)*origin[0] + _translation[0], cos(_theta)*origin[1] + _translation[1], origin[2]+_translation[2]),
               Vector3(cos(_theta)*direction[0], sin(_theta)*direction[1], direction[2]));


    Quadrics qSphere(Color(), Material(), 1, 1, 1, 0, 0, 0, 0, 0, 0, -9);
    Sphere sphere(Color(), Material(), Vector3(), 3);



    for (int i = -40; i < 40; i++) {
        for (int j = -30; j < 30; j++) {
            Ray ray(Vector3(-10, 0, 0), Vector3(1, i, j));

            vector<double> qInter = qSphere.ensIntersect(ray);
            vector<double> inter = sphere.ensIntersect(ray);

            if (qInter.size() > 0 &&  inter.size() > 0) {

                cerr << qInter.at(0) << " " << inter.at(0) << endl;
            }
        }
    }


    Ray ray(Vector3(-10, 0, 0), Vector3(1, 0, 0));

    vector<double> qInter = qSphere.ensIntersect(ray);
    vector<double> inter = sphere.ensIntersect(ray);

    cerr << "qInter " << endl;
    for (int k = 0; k < qInter.size(); k++) {
        cerr << qInter.at(k) << endl;
    }

    cerr << "inter " << endl;
    for (int k = 0; k < inter.size(); k++) {
        cerr << inter.at(k) << endl;
    }

    Vector3 qNormal = qSphere.normal(ray.getPoint(qInter.at(0)));
    cerr << "qNormal " << endl << qNormal << endl;

    Vector3 normal = sphere.normal(ray.getPoint(inter.at(0)));
    cerr << "normal " << endl << normal << endl;

/*


    QStringList params;
    params << "x^2-y^2-z^2" << "2xz" << "2xy" << "x^2+y^2+z^2";
    Surface sphere = Surface(Color(), Material(), params);

    Ray rayon(Vector3(0, -2, 0), Vector3(0, 1, 0));

    cerr << "Intersections" << endl;
    vector<double> inter = sphere.ensIntersect(rayon);
    for (int k = 0; k < inter.size(); k++) {
        cerr << inter.at(k) << endl;
    }



    MatrixOpp mo;
    itpp::mat test = "7.11726e-16 0; 0 2.24717e-16";
    cerr << test << endl;
    cerr << mo.rank(test, pow(10, -10)) << endl;

    //itpp::mat test = "1.40508 -1.2714; 0.354598 0.490605";
    //itpp::vec testSing = svd(test);
    //cerr << test << endl;
    //cerr << testSing << endl;

    //itpp::mat testDel = "1.40508 -1.2714 0.354598 -1.2714 0.490605; 1.40508 -1.2714 0.354598 -1.2714 0.490605";
    //testDel.del_cols(3, 4);
    //cerr << testDel << endl;


    /*
    itpp::mat MatA="-0.107357 -0.0510009 0.830732 0.216346 0.0731312 0.545236 0.598673 0.435944 -0.174946 -0.0154371 0.0188213; 0.394865 0.684388 -0.609272 -0.00989498 0.0179188 -0.0925767 0.445025 0.890383 -0.0217646 0.834316 -0.571974; -0.0386261 -0.126441 0.0246027 0.46594 0.752696 0.316755 0.543039 0.534491 -0.762077 -0.332822 0.558157; -0.172559 1.07088 -0.00299878 0.601361 -0.119217 -0.300484 -0.123059 0.256296 0.430866 -0.801376 0.317803; -0.178008 0.0443514 -0.322137 -0.269033 0.756054 0.325227 0.24626 0.29693 1.14214 0.472322 0.349494; -0.0274508 -0.259354 -0.383347 0.14874 0.275636 -0.348788 -0.0465805 0.731172 -0.188873 -0.609764 0.361292";
    itpp::mat MatB="-0.119899 -0.0323817 0.428454 0.0186514 0.00329174 0.0354584 0.278651 0.233471 -0.0232638 -0.00133084 -0.00467978; 0.0330396 0.318083 -0.163199 0.0262524 0.0825663 -0.0136418 -0.0788958 0.43979 -0.104738 0.414932 -0.283949; 0.0191853 0.0191573 -0.132727 0.188931 0.385542 0.145688 0.177995 -0.032711 -0.386778 -0.0134809 0.245401; -0.00388032 0.542053 0.00900084 0.0919673 -0.0771502 -0.0154893 -0.0814925 0.164284 0.112838 -0.385796 0.260114; -0.100031 0.0119408 -0.136066 -0.21962 0.422891 0.168009 0.166844 0.0380245 0.507365 0.0156707 0.0228195; 0.0429022 -0.132374 -0.138398 0.0694264 -0.0216792 -0.0100782 -0.091603 0.366442 0.0347433 -0.304529 0.0720361";

    Pencil pen(MatA, MatB);

    std::cerr << "########################################" << std::endl;
    std::cerr << "A=" << pen.A << std::endl;
    std::cerr << "B=" << pen.B << std::endl;
    std::cerr << "########################################" << std::endl;
    //*/

//*

    QApplication app(argc, argv);

    QSplashScreen* splash = new QSplashScreen(QPixmap("misc/splash.png"), Qt::WindowStaysOnTopHint);
    splash->show();

    splash->showMessage("Loading...", Qt::AlignBottom, Qt::white);

    MainWindow window;
    window.show();

    qApp->setStyleSheet("QStringListModel QAbstractItemView { border: 2px solid darkgray; selection-background-color: lightgray; }");

    splash->finish(&window);

    return app.exec();
//*/
}
