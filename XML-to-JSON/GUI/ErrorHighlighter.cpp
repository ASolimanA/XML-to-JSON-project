#include "ErrorHighlighter.h"
#include <QString>


ErrorHighlighter::ErrorHighlighter(QTextDocument *parent, Validator* validator)
    : QSyntaxHighlighter(parent) {
    // Initialize the format
    setPositions(validator);
    error_char_format.setUnderlineColor(Qt::red);
    error_char_format.setUnderlineStyle(QTextCharFormat::WaveUnderline);
}



void ErrorHighlighter::highlightBlock(const QString &text) {
    int blockNumber = currentBlock().blockNumber();
    for (const auto &pos : e_positions) {
        int line_no = pos[0];
        int char_no = pos[1];
        if (blockNumber == line_no) {
            setFormat(char_no, 1, error_char_format);
        }
    }
}

void ErrorHighlighter::setHighlights(Validator* validator) {
    setPositions(validator);
    rehighlight();
}

void ErrorHighlighter::setPositions(Validator* validator) {
    // Set the error positions QVector
    vector<array<int, 2>> std_positions = validator->get_error_places();
    e_positions = QList<std::array<int, 2>>(std_positions.begin(), std_positions.end());
}