#ifndef ADAPTER_H_
#define ADAPTER_H_

#include <string>
#include <QString>
#include <QVector>

#include "validation.h"

using namespace std;

class QtAdapter {
public:
    string to_string(QString qstring);
    QString to_qstring(string string);
    template <class T>
    QVector<T> to_qvector(vector<T> vec);
    template <class T>
    vector<T> to_vector(QVector<T> qvec);
    void setVerifyContent(QString content, Validator* validator);
    QString getfilecontent(Validator* validator);
};

#endif //ADAPTER_H_