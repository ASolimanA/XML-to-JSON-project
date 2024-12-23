// ...existing code...
#ifndef ERRORHIGHLIGHTER_H
#define ERRORHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QVector>
#include "adapter.h"
#include "validation.h"

class ErrorHighlighter : public QSyntaxHighlighter {
    Q_OBJECT

public:
    ErrorHighlighter(QTextDocument *parent);
    void setHighlights(Validator* validator);


protected:
    void highlightBlock(const QString &text) override;

private:
    QVector<std::array<int,2>> e_positions;
    QTextCharFormat error_char_format;
    
    void setPositions(Validator* validator);
};

#endif // ERRORHIGHLIGHTER_H
