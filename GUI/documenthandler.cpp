#include "documenthandler.h"

DocumentHandler::DocumentHandler(QObject *parent) : QObject(parent),m_document(Q_NULLPTR)
{
    errorsLine[12-1]="ff";
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
    const QString filePath = QQmlFile::urlToLocalFileOrQrc(m_fileUrl);
    const QString fileName = QFileInfo(filePath).fileName();
    if (fileName.isEmpty())
        return QStringLiteral("untitled.txt");
    return fileName;
}

QString DocumentHandler::fileType() const
{
    return QFileInfo(fileName()).suffix();
}

QUrl DocumentHandler::fileUrl() const
{
    return m_fileUrl;
}

QTextDocument *DocumentHandler::textDocument() const
{
    if (!m_document)
        return nullptr;
    return m_document->textDocument();
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
        QTextCharFormat format;
        QColor color(255,0,0);
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

void DocumentHandler::load(const QUrl &fileUrl)
{
    if (fileUrl == m_fileUrl)
        return;
    QQmlEngine *engine = qmlEngine(this);
    if (!engine) {
        qWarning() << "load() called before DocumentHandler has QQmlEngine";
        return;
    }

    const QUrl path = QQmlFileSelector::get(engine)->selector()->select(fileUrl);
    const QString fileName = QQmlFile::urlToLocalFileOrQrc(path);
    if (QFile::exists(fileName)) {
        QFile file(fileName);
        if (file.open(QFile::ReadOnly)) {
            QTextStream stream(&file);
            stream.setFieldAlignment(QTextStream::AlignLeft);
            QString txt;
            while(!stream.atEnd()){
                txt+=stream.readLine()+"\n<br>";
            }
            if (QTextDocument *doc = textDocument())
                doc->setModified(false);

            emit loaded(txt);
            syntaxHighlighting();
            errorHighlighting();
        }
    }

    m_fileUrl = fileUrl;
    emit fileUrlChanged();
}
