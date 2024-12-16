#ifndef ADAPTER_H_
#define ADAPTER_H_

#include <string>
#include <Qtcore/QString>

using namespace std;

class QtAdapter {
    string to_string(QString qstring);
    QString to_qstring(string string);
};


#endif //ADAPTER_H_