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
public:
    explicit DocumentHandler(QObject *parent = 0);
    QQuickTextDocument *document() const;
    void setDocument(QQuickTextDocument *document);
    QString fileName() const;
    QString fileType() const;
    QUrl fileUrl() const;
private:
    QQuickTextDocument *m_document;
    QTextDocument *textDocument() const;
    QUrl m_fileUrl;
    QMap<int, QString> errorsLine;//key - number line, value - text error
    void syntaxHighlighting();
    void errorHighlighting();
signals:
    void documentChanged();
    void fileUrlChanged();
    void loaded(const QString &text);
    void error(const QString &message);
public slots:
    void load(const QUrl &fileUrl);
};

#endif // DOCUMENTHANDLER_H
