#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include <stack>
#include <vector>

using namespace std;

// دالة لفحص إذا كان التاج هو Closing Tag
bool isClosingTag(const string& tag) {
    return (tag.size() > 2 && tag[0] == '<' && tag[1] == '/');
}

// دالة لفحص إذا كان التاج هو Opening Tag
bool isOpeningTag(const string& tag) {
    return (tag.size() > 1 && tag[0] == '<' && tag[1] != '/');
}

// دالة لفصل النصوص والتاجات عن بعض
vector<string> prettierfunction(const string& content) {
    vector<string> result;
    regex tagPattern(R"(<[^>]+>)"); // نمط للتعرف على التاجات (الـ opening و الـ closing)
    auto wordsBegin = sregex_iterator(content.begin(), content.end(), tagPattern);
    auto wordsEnd = sregex_iterator();

    size_t lastPos = 0;
    for (auto i = wordsBegin; i != wordsEnd; ++i) {
        // الحصول على التاج
        string tag = i->str();
        size_t pos = i->position();

        // إضافة النص بين التاجات إلى النتيجة إذا كان هناك نص بين التاجات
        if (pos > lastPos) {
            result.push_back(content.substr(lastPos, pos - lastPos)); // النص بين التاجات
        }

        result.push_back(tag); // إضافة التاج نفسه
        lastPos = pos + tag.size();
    }

    // إضافة النص بعد آخر تاج
    if (lastPos < content.size()) {
        result.push_back(content.substr(lastPos));
    }

    return result;
}

// دالة لمعالجة الملف بالكامل وتنسيقه
void processXMLFile(const string& fileName) {
    ifstream inputFile(fileName);
    if (!inputFile) {
        cerr << "Error opening file for reading: " << fileName << endl;
        return;
    }

    string line;
    string fullContent;

    // قراءة كامل الملف في متغير واحد
    while (getline(inputFile, line)) {
        fullContent += line; // تجميع كل الأسطر معًا
    }

    inputFile.close();

    vector<string> parts = splitXMLContent(fullContent); // فصل التاجات والنصوص من النص الكامل

    int indentLevel = 0;
    stringstream formattedContent; // لتخزين النص النهائي المُنسق
    stack<string> tagStack; // لتخزين التاجات المفتوحة في الذاكرة

    // التعامل مع كل جزء بشكل منفصل (تاج أو نص)
    for (const string& part : parts) {
        string trimmedPart = part;
        // إزالة المسافات الزائدة
        size_t start = trimmedPart.find_first_not_of(" \t");
        if (start != string::npos) {
            trimmedPart = trimmedPart.substr(start);
        } else {
            trimmedPart = "";
        }

        // إذا كان السطر يحتوي على Opening Tag أو Closing Tag
        if (isOpeningTag(trimmedPart)) {
            // إضافة التاج المفتوح إلى الذاكرة
            tagStack.push(trimmedPart);
            formattedContent << string(indentLevel * 4, ' ') << trimmedPart << endl;
            indentLevel++; // إضافة مسافة إضافية بعد الـ opening tag
        } else if (isClosingTag(trimmedPart)) {
            // إذا كان الـ closing tag مفقودًا، نترك سطر فارغ
            if (!tagStack.empty()) {
                    if ("</" + tagStack.top().substr(1) == trimmedPart) {
                tagStack.pop(); // إزالة التاج المفتوح من الذاكرة
                indentLevel--; // إزالة المسافة بعد الـ closing tag
                formattedContent << string(indentLevel * 4, ' ') << trimmedPart << endl;
            }else{
         tagStack.pop();
            indentLevel--;   // تقليل مستوى العمق
            formattedContent << string(indentLevel * 4, ' ') << trimmedPart << endl;

            } }else {
                formattedContent << string(indentLevel * 4, ' ') << "" << endl;
                tagStack.pop(); // ترك سطر فارغ
            }
        } else {
            // إذا كان السطر يحتوي على نص بين التاجات
            if (!trimmedPart.empty()) { // تجاهل النص الفارغ
                formattedContent << string(indentLevel * 4, ' ') << trimmedPart << endl;
            }
        }
    }

    // كتابة المحتوى المُنسق في نفس الملف (بدون طباعة)
    ofstream outputFile(fileName, ios::trunc); // نستخدم trunc لكتابة الملف من جديد
    if (!outputFile) {
        cerr << "Error opening file for writing: " << fileName << endl;
        return;
    }

    outputFile << formattedContent.str(); // كتابة النص المنسق

    outputFile.close();
}

int main() {
    string fileName = "Untitled1.txt"; // اسم الملف
    prettierfunction(fileName); // المعالجة للطباعة بتنسيق XML صحيح
    return 0;
}
