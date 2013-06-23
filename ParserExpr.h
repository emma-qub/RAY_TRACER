#ifndef PARSEREXPR_H
#define PARSEREXPR_H

#include <QString>
#include <QStringList>
#include <QVector>

#include <iostream>

class ParserExpr {

public:

    class SyntaxError : public std::exception {
    public:
        const char* what() const throw() {
            return "Syntax error";
        }
    };

    class NotHomogen : public std::exception {
    public:
        const char* what() const throw() {
            return "Expression not homogen";
        }
    };

    ParserExpr(const QString& expression = QString());
    ParserExpr(const ParserExpr& parserExpression);
    virtual ~ParserExpr();

    QString getExpression() const { return _expression; }
    QString getFormatedExpr() const { return _formatedExpr; }
    int getDegree() const { return _degree; }
    int getNu() const { return _nu; }

    QStringList getMonomes() const;
    QVector<int> getExpoAt(int index) const;
    double getConstAt(int index) const;

    int getHigherDegree() const;
    double getConstant(int xExpo, int yExpo, int zExpo) const;

    friend std::ostream& operator<<(std::ostream& os, const ParserExpr& parseExpr2);

private:
    QString _expression;
    QString _formatedExpr;
    int _degree;
    int _nu;

    void clean(QString& polynome) const;
    void addPlusSign(QString& polynome) const;
    QStringList splitExpr(const QString& expression) const;
    void removeMultSymb(QString& monome) const;
    void addExpoSymb(QString& monome) const;
    void completeAndSort(QString& monome) const;
    void addConstant(QString& monome) const;
    void formatExpr();

    QVector<int> getExponents(const QString& monome) const;
    int calculateDegree() const;
    int calculateDegree(const QString& monome) const;

    bool isHomogen() const;
    bool isSyntaxOk() const;

};

#endif // PARSEREXPR_H
