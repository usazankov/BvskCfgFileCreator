#ifndef DOCUMENTHANDLER_H
#define DOCUMENTHANDLER_H

#include <QObject>
#include <QQuickTextDocument>
#include <QFileInfo>
#include <QQmlFile>
#include <QQmlFileSelector>
#include <QFileSelector>
#include <QTextCursor>
#include <QTextBlock>
#include <QTextList>
namespace Syntax {
const QString comment="#";
}
class DocumentHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQuickTextDocument *document READ document WRITE setDocument NOTIFY documentChanged)
    Q_PROPERTY(QString fileName READ fileName NOTIFY fileUrlChanged)
    Q_PROPERTY(QString fileType READ fileType NOTIFY fileUrlChanged)
    Q_PROPERTY(QUrl fileUrl READ fileUrl NOTIFY fileUrlChanged)
    Q_PROPERTY(QString textColor WRITE setTextColor NOTIFY textColorChanged)
    Q_PROPERTY(QString backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
public:
    explicit DocumentHandler(QObject *parent = 0);
    QQuickTextDocument *document() const;
    void setDocument(QQuickTextDocument *document);
    QString fileName() const;
    QString fileType() const;
    void setTextColor(const QString &txt);
    void setBackgroundColor(const QString &color);
    QUrl fileUrl() const;
    void addErrorInfo(int numberStr, const QString &txt);
    Q_INVOKABLE void errorHighlighting();
    void clearErrorsInfo();
private:
    QQuickTextDocument *m_document;
    QTextDocument *textDocument() const;
    QUrl m_fileUrl;
    QMap<int, QString> errorsLine;//key - number line, value - text error
    void toDefaultHighlighting();
    void syntaxHighlighting();
    QColor defaultTextColor;
    QColor defaultBackgroundColor;
signals:
    void documentChanged();
    void fileUrlChanged();
    void loaded(const QString &text);
    void error(const QString &message);
    void textColorChanged();
    void backgroundColorChanged();
public slots:
    void load(const QUrl &fileUrl);
};

#endif // DOCUMENTHANDLER_H
