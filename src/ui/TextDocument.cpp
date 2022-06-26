#include "TextDocument.h"

TextDocument::TextDocument() {

}

QQuickTextDocument* TextDocument::document() const
{
    return  m_document;
}

void TextDocument::setDocument(QQuickTextDocument *document)
{
    if (document != m_document)
    {
        m_document = document;
        emit documentChanged();
    }
}

void TextDocument::insertImage(const QString& url){
    QTextImageFormat format;
    format.setName(url);
    format.setWidth(20);
    format.setHeight(20);
    textCursor().insertImage(format, QTextFrameFormat::InFlow);
}

QTextDocument* TextDocument::textDocument() const
{
    if (m_document)
        return m_document->textDocument();
    else return nullptr;
}

QTextCursor TextDocument::textCursor() const
{
    QTextDocument *doc = textDocument();
    if (!doc)
        return QTextCursor();

    QTextCursor cursor = QTextCursor(doc);
    if (m_selectionStart != m_selectionEnd)
    {
        cursor.setPosition(m_selectionStart);
        cursor.setPosition(m_selectionEnd, QTextCursor::KeepAnchor);
    }
    else
    {
        cursor.setPosition(m_cursorPosition);
    }

    return cursor;
}

int TextDocument::cursorPosition() const
{
    return m_cursorPosition;
}

void TextDocument::setCursorPosition(int position)
{
    if (position != m_cursorPosition)
    {
        m_cursorPosition = position;
        emit cursorPositionChanged();
    }
}

int TextDocument::selectionStart() const
{
    return m_selectionStart;
}

void TextDocument::setSelectionStart(int position)
{
    if (position != m_selectionStart)
    {
        m_selectionStart = position;
        emit selectionStartChanged();
    }
}

int TextDocument::selectionEnd() const
{
    return m_selectionEnd;
}

void TextDocument::setSelectionEnd(int position)
{
    if (position != m_selectionEnd)
    {
        m_selectionEnd = position;
        emit selectionEndChanged();
    }
}

QString TextDocument::plainText(){
    return textDocument()->toPlainText();
}
