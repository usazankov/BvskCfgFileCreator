#include "documenthandler.h"

DocumentHandler::DocumentHandler(QObject *parent) : QObject(parent),m_document(Q_NULLPTR)
{

}

QQuickTextDocument *DocumentHandler::document() const
{
    return m_document;
}

void DocumentHandler::setDocument(QQuickTextDocument *document)
{
    if (document == m_document)
        return;
    m_document = document;
    emit documentChanged();
}

QString DocumentHandler::fileName() const
{
    const QString filePath = QQmlFile::urlToLocalFileOrQrc(m_fileUrl[0]);
    const QString fileName = QFileInfo(filePath).fileName();
    if (fileName.isEmpty())
        return QStringLiteral("untitled.txt");
    return fileName;
}

QString DocumentHandler::fileType() const
{
    return QFileInfo(fileName()).suffix();
}

void DocumentHandler::setTextColor(const QString &txt)
{
    QColor c(txt);
    defaultTextColor=c;
    emit textColorChanged();
}

void DocumentHandler::setBackgroundColor(const QString &color)
{
    QColor c(color);
    defaultBackgroundColor=c;
    emit backgroundColorChanged();
}

QList<QUrl> DocumentHandler::fileUrl() const
{
    return m_fileUrl;
}

void DocumentHandler::addErrorInfo(int numberStr, const QString &txt)
{
    errorsLine[numberStr-1]=txt;
}

QTextDocument *DocumentHandler::textDocument() const
{
    if (!m_document)
        return nullptr;
    return m_document->textDocument();
}

void DocumentHandler::toDefaultHighlighting()
{
    if (QTextDocument *doc = textDocument()){
        QTextCharFormat format;
        format.setForeground(QBrush(defaultTextColor));
        format.setBackground(QBrush(defaultBackgroundColor));
        QTextCursor cursor(doc);
        cursor.select(QTextCursor::Document);
        cursor.mergeCharFormat(format);
        syntaxHighlighting();
    }
}

void DocumentHandler::syntaxHighlighting()
{
    if (QTextDocument *doc = textDocument()){
        QTextCharFormat format;
        QColor color(0,128,0);
        format.setForeground(QBrush(color));
        int pos=0;
        QTextCursor cursor(doc);
        QString text=doc->toPlainText();
        do{
            pos=text.indexOf(Syntax::comment,pos);
            if(pos!=-1){
                cursor.setPosition(pos);
                int end_pos=text.indexOf("\n",pos);
                cursor.setPosition(end_pos, QTextCursor::KeepAnchor);
                if (!cursor.hasSelection())
                    cursor.select(QTextCursor::WordUnderCursor);
                cursor.mergeCharFormat(format);
                ++pos;
            }

        }while(pos!=-1);

    }
}

void DocumentHandler::errorHighlighting()
{
    if (QTextDocument *doc = textDocument()){
        toDefaultHighlighting();
        QTextCharFormat format;
        QColor color(207,81,81);
        QColor color_text(255,255,255);
        format.setBackground(QBrush(color));
        format.setForeground(QBrush(color_text));
        QTextCursor cursor(doc);
        QString text=doc->toPlainText();
        QTextStream stream(&text);
        int countLine=0;
        int pos=0;
        while(!stream.atEnd()){
            QString line=stream.readLine();
            if(errorsLine.contains(countLine)){
                pos=text.indexOf(line);
                cursor.setPosition(pos);
                int end_pos=text.indexOf("\n",pos);
                cursor.setPosition(end_pos, QTextCursor::KeepAnchor);
                if (!cursor.hasSelection())
                    cursor.select(QTextCursor::WordUnderCursor);
                cursor.mergeCharFormat(format);
            }
            ++countLine;
        }
    }
}

void DocumentHandler::clearErrorsInfo()
{
    errorsLine.clear();
}

void DocumentHandler::load(const QList<QUrl> &fileUrls)
{
    if (fileUrls == m_fileUrl)
        return;
    QQmlEngine *engine = qmlEngine(this);
    if (!engine) {
        qWarning() << "load() called before DocumentHandler has QQmlEngine";
        return;
    }
    QTextStream stream;
    QString txt;
    for(int i=0;i<fileUrls.size();++i){
        QUrl path = QQmlFileSelector::get(engine)->selector()->select(fileUrls[i]);
        const QString fileName = QQmlFile::urlToLocalFileOrQrc(path);
        if (QFile::exists(fileName)) {
            QFile file(fileName);
            if (file.open(QFile::ReadOnly)) {
                stream.setDevice(&file);
                stream.setFieldAlignment(QTextStream::AlignLeft);
                while(!stream.atEnd()){
                    txt+=stream.readLine()+"\n";
                }
                if (QTextDocument *doc = textDocument())
                    doc->setModified(false);
                ErrorsHandle::sendMessage(fileName+" loaded");
            }
        }
    }
    emit loaded(txt);
    syntaxHighlighting();
    errorHighlighting();
    m_fileUrl = fileUrls;
    emit fileUrlChanged();
}
