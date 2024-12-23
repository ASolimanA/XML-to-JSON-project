#include "adapter.h"


string QtAdapter::to_string(QString qstring) {
    return qstring.toStdString();
}


QString QtAdapter::to_qstring(string string) {
    return QString::fromStdString(string);
}

template <class T>
QVector<T> QtAdapter::to_qvector(vector<T> vec) {
    
    return QVector<T>::fromStdVector(vec);
}

template <class T>
vector<T> QtAdapter::to_vector(QVector<T> qvec) {
    return qvec.toStdVector();
}

void QtAdapter::setVerifyContent(QString content, Validator* validator) {
    vector<string> fileContent;
    QStringList lines = content.split("\n");
    for (const auto& line : lines) {
        fileContent.push_back(line.toStdString());
    }
    validator->setFileContent(fileContent);
}