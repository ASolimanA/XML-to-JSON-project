#include "adapter.h"

string QtAdapter::to_string(QString qstring) {
    return qstring.toStdString();
}


QString QtAdapter::to_qstring(string string) {
    return QString::fromStdString(string);
}