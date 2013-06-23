#include "ParserExpr.h"

#include <QRegExp>

using namespace std;

//Constructors
ParserExpr::ParserExpr(const QString& expression) :
    _expression(expression) {

    if (!isSyntaxOk()) {
        throw SyntaxError();
    } else {
        formatExpr();
        _degree = calculateDegree();
        _nu = 2*(_degree - 1);
        //if (!isHomogen()) {
            //throw NotHomogen();
        //}
    }
}

ParserExpr::ParserExpr(const ParserExpr& parserExpression) {
    _expression = parserExpression._expression;
    _formatedExpr = parserExpression._formatedExpr;
    _degree = parserExpression._degree;
    _nu = parserExpression._nu;
}

//Destructor
ParserExpr::~ParserExpr() {
}

//Methodes publiques
QStringList ParserExpr::getMonomes() const {
    QStringList monomes = splitExpr(_formatedExpr);
    monomes.removeAt(0);
    return monomes;
}

double ParserExpr::getConstAt(int index) const {
    return getMonomes().at(index).split('*').at(0).toDouble();
}

QVector<int> ParserExpr::getExpoAt(int index) const{
    QVector<int> res;
    QString monome = getMonomes().at(index);
    res.append(monome.split("x^").at(1).split('*').at(0).toInt());
    res.append(monome.split("y^").at(1).split('*').at(0).toInt());
    res.append(monome.split("z^").at(1).toInt());
    return res;
}

int ParserExpr::getHigherDegree() const {
    int higherDegree = -1;
    QStringList monomesList = getMonomes();

    for (int k = 0; k < monomesList.size(); k++) {
        int currDegree = calculateDegree(monomesList.at(k));
        if (higherDegree < currDegree) {
            higherDegree = currDegree;
        }
    }

    return higherDegree;
}

double ParserExpr::getConstant(int xExpo, int yExpo, int zExpo) const {
    QStringList monomesList = getMonomes();

    for (int k = 0; k < monomesList.size(); k++) {
        QVector<int> currExpos = getExpoAt(k);
        int currXExpo = currExpos.at(0);
        int currYExpo = currExpos.at(1);
        int currZExpo = currExpos.at(2);
        if (xExpo == currXExpo && yExpo == currYExpo && zExpo == currZExpo) {
            return getConstAt(k);
        }
    }

    return 0.0;
}

//Méthodes privées
// Remove every blank in the string
void ParserExpr::clean(QString& polynome) const {
    QString polynomeTemp = "";
    for (int k = 0; k < polynome.size(); k++) {
        if (polynome.at(k) != ' ') {
            polynomeTemp += polynome.at(k);
        }
    }
    polynome = polynomeTemp;
}

/*!
 * Ajoute les signes + quand ils n'ont pas été mis.
 *
 * pré-condition : le monome doit juste avoir la constante et les lettres
 *                 avec ou sans exposants, le tout ici est d'ajouter des
 *                 signes + devant les signes -
 */
void ParserExpr::addPlusSign(QString& polynome) const {
    QStringList splittedExpr = polynome.split(QRegExp("[-]{1,1}"));
    QString tempPolynome = splittedExpr.at(0);

    //Si la taille de splittedExpr est égale à 1, notre expression ne contenait
    //pas de signe -, sinon elle en contenait au moins un et on travaille
    //dessus à partir de l'élément à l'a place'indice 1 dans la QStringList.
    if (splittedExpr.size() > 1) {
        for (int k = 1; k < splittedExpr.size(); k++) {
            tempPolynome += "+-" + splittedExpr.at(k);
        }
    }
    polynome = tempPolynome;
}

QStringList ParserExpr::splitExpr(const QString& expression) const {
    QStringList splittedExpr = expression.split(QRegExp("[+]{1,1}"));
    return splittedExpr;
}

/*!
 * Supprime tous les signes *
 */
void ParserExpr::removeMultSymb(QString& monome) const {
    QString monomeTemp = "";
    for (int k = 0; k < monome.size(); k++) {
        if (monome.at(k) != '*') {
            monomeTemp += monome.at(k);
        }
    }
    monome = monomeTemp;
}

/*!
 * Ajoute les ^1 quand ils n'ont pas été mis.
 *
 * pré-condition : le monome doit etre d'une des formes suivantes
 * _ 3x^2y^1z^3
 * _ -3x^2y^1z^3
 * _ -x^2y^1z^3
 * --> les exposants sont déjà là, les signes * ont été enlevés
 */
void ParserExpr::addExpoSymb(QString& monome) const{
    QString monomeTemp = "";
    for (int k = 0; k < monome.size(); k++) {
        QChar currLetter = monome.at(k);
        if (currLetter == 'x' || currLetter == 'y' || currLetter == 'z') {
            if (monome.size() == k+1) {
                monomeTemp +=  monome.at(k) + '^' + '1';
            } else if (monome.at(k+1) != '^') {
                monomeTemp +=  monome.at(k) + '^' + '1';
            } else {
                monomeTemp += monome.at(k);
            }
        } else {
            monomeTemp += monome.at(k);
        }
    }
    monome = monomeTemp;
}

/*!
 * Ajoute les x^0 (y^0 et z^0) quand ils n'ont pas été mis.
 *
 * pré-condition : le monome doit etre d'une des formes suivantes
 * _ 3x^2y^1z^3
 * _ -3x^2y^1z^3
 * _ -x^2y^1z^3
 * --> les exposants sont déjà là, les signes * ont été enlevés
 */
void ParserExpr::completeAndSort(QString& monome) const {
    QString constante = monome.split(QRegExp("[x-z]")).at(0);
    QString expoX = "x^", expoY = "y^", expoZ = "z^";
    QString beginWithX, beginWithY, beginWithZ;

    if (monome.contains('x')) {
        beginWithX = monome.split("x^").at(1);
        if (beginWithX.size() > 0)
            expoX += beginWithX.split(QRegExp("[x-z]")).at(0);
    } else {
        expoX += "0";
    }

    if (monome.contains('y')) {
        beginWithY = monome.split("y^").at(1);
        if (beginWithY.size() > 0)
            expoY += beginWithY.split(QRegExp("[x-z]")).at(0);
    } else {
        expoY += "0";
    }

    if (monome.contains('z')) {
        beginWithZ = monome.split("z^").at(1);
        if (beginWithZ.size() > 0)
            expoZ += beginWithZ.split(QRegExp("[x-z]")).at(0);
    } else {
        expoZ += "0";
    }

    monome = constante + expoX + "*" + expoY + "*" + expoZ;
}

/*!
 * Ajoute les signes * quand ils n'ont pas été mis.
 * Ajoute également la constante 1 devant les multiplications.
 *
 * pré-condition : le monome doit etre d'une des formes suivantes
 * _ 3x^2y^1z^3
 * _ -3x^2y^1z^3
 * _ -x^2y^1z^3
 * --> les exposants sont déjà là, les signes * ont été enlevés
 */
void ParserExpr::addConstant(QString& monome) const {
    QString constant = monome.split('x').at(0);
    QString variable = monome.remove(0, constant.size());
    if (constant.size() == 0) {
        constant = "1*";
    } else if (constant.at(0) == '-' && constant.size() == 1) {
        constant = "-1*";
    } else {
        constant += "*";
    }

    monome = constant + variable;
}

void ParserExpr::formatExpr() {
    QString formatedExpr = _expression;

    clean(formatedExpr);
    addPlusSign(formatedExpr);

    QStringList monomeList = splitExpr(formatedExpr);

    formatedExpr = "";
    for (int k = 0; k < monomeList.size(); k++) {
        QString currMonome = monomeList.at(k);
        removeMultSymb(currMonome);
        addExpoSymb(currMonome);
        completeAndSort(currMonome);
        addConstant(currMonome);
        formatedExpr += "+" + currMonome;
    }

    _formatedExpr = formatedExpr;
}

QVector<int> ParserExpr::getExponents(const QString &monome) const {
    QVector<int> res;
    res.append(monome.split("x^").at(1).split('*').at(0).toInt());
    res.append(monome.split("y^").at(1).split('*').at(0).toInt());
    res.append(monome.split("z^").at(1).toInt());
    return res;
}

/*!
 * On calcule le degré du monome en sommant les indices
 *
 * Pré-condition : le monome doit etre de la forme k*x^i*y^j*z*k
 */
int ParserExpr::calculateDegree() const {
    return calculateDegree(_formatedExpr.split('+').at(1));
}

int ParserExpr::calculateDegree(const QString& monome) const {
    QVector<int> exponents = getExponents(monome);
    return exponents.at(0) + exponents.at(1) + exponents.at(2);
}

bool ParserExpr::isHomogen() const {
    QStringList monomeList = _formatedExpr.split('+');

    for (int k = 2; k < monomeList.size(); k++) {
        if (_degree != calculateDegree(monomeList.at(k))) {
            return false;
        }
    }

    return true;
}

bool ParserExpr::isSyntaxOk() const {
    QRegExp exprPattern("[\\-]?[0-9.]*[\\*]?([xyz]([\\^][0-9]+)?[\\*]?){0,3}");

    QString cleanedAndWithPlus = QString(_expression);
    clean(cleanedAndWithPlus);
    addPlusSign(cleanedAndWithPlus);

    QStringList monomeList = splitExpr(cleanedAndWithPlus);
    for (int k = 0; k < monomeList.size(); k++) {
        if (!exprPattern.exactMatch(monomeList.at(k))) {
            return false;
        }
    }

    return true;
}

ostream& operator<<(ostream& os, const ParserExpr& parseExpr) {
    return os << "Expression de base : " << endl
       << parseExpr.getExpression().toStdString() << endl
       << "Expression formatée : " << endl
       << parseExpr.getFormatedExpr().toStdString();
}
/*
QVector<double> ParserExpr::makeVector() const {
    return makeVectorFromExpr(_degree, _formatedExpr);
}

QVector<double> ParserExpr::makeVectorFromExpr(int degree, const QString& formatedExpr) const {
    int size = ((degree + 1) * (degree + 2) / 2);
    QVector<double> res = QVector<double>(size, 0.0);

    QStringList monomeList = splitExpr(formatedExpr);

    for (int k = 1; k < monomeList.size(); k++) {
        QString currMonome = monomeList.at(k);
        QVector<int> exponents = getExponents(currMonome);
        double constant = currMonome.split('*').at(0).toDouble();
        int index = (degree - exponents.at(0)) * ((degree - exponents.at(0) + 1) / 2) + (exponents.at(2));
        //cerr << currMonome.toStdString() << endl;

        //cerr << index << endl;
        res.replace(index, constant + res.at(index));

    }

    return res;
}

QVector<QVector<double> > ParserExpr::giParExpr(int nu) const {
    QVector<QVector<double> > res;

    for (int i = 0; i <= nu; i++) {
        for (int j = 0; j <= i; j++) {
            QVector<int> exponents;
            //cerr << _nu - i << " " << i - j << " " << j << endl;
            exponents << nu - i << i - j << j;
            QVector<double> column = giMonomeParExpr(exponents, nu);
            //int sized = column.size();
            //cerr << sized << endl;
            res.append(column);
        }
    }

    return res;
}

QVector<double> ParserExpr::giMonomeParExpr(QVector<int> giExponents, int nu) const {

    QStringList monomesList = splitExpr(_formatedExpr);
    QString newFormatedExpr = "";

    //cerr << _formatedExpr.toStdString() << endl;

    for (int k = 1; k < monomesList.size(); k++) {
        QString currMonome = monomesList.at(k);
        QVector<int> exponents = getExponents(currMonome);
        int newExpoX = exponents.at(0) + giExponents.at(0);
        int newExpoY = exponents.at(1) + giExponents.at(1);
        int newExpoZ = exponents.at(2) + giExponents.at(2);
        QString currConst = currMonome.split('*').at(0);
        newFormatedExpr += '+' + currConst
                        + "*x^" + QString::number(newExpoX)
                        + "*y^" + QString::number(newExpoY)
                        + "*z^" + QString::number(newExpoZ);
    }
    //cerr << newFormatedExpr.toStdString() << endl;

    QVector<double> column = makeVectorFromExpr(nu + _degree, newFormatedExpr);
    //cerr << "bouh" << endl;

    return column;
}

string ParserExpr::toString(int nu) const {
    if (nu == -1)
        nu = _nu;
    return toString(giParExpr(nu));
}

string ParserExpr::toString(QVector<QVector<double> > matrix) const {
    QString res = "";
    for (int i = 0; i < matrix.size() - 1; i++) {
        for (int j = 0; j < matrix.at(0).size() - 1; j++) {
            res += QString::number(matrix.at(i).at(j)) + ",";
        }
        res += QString::number(matrix.at(i).at(matrix.at(0).size() - 1)) + ";";
    }
    for (int j = 0; j < matrix.at(0).size() - 1; j++) {
        res += QString::number(matrix.at(matrix.size() - 1).at(j)) + ",";
    }
    res +=  QString::number(matrix.at(matrix.size() - 1).at(matrix.at(0).size() - 1));

    return res.toStdString();
}
*/
