//
// Created by andrzej on 8/17/22.
//

#ifndef EDITWRITE_EDIEXCEPTION_H
#define EDITWRITE_EDIEXCEPTION_H


//#include <QException>
#include <QString>

class EdiException//: public QException
{
//    QString m_text;
public:
    explicit EdiException(/*QString  text=""*/){};// noexcept :m_text(std::move(text)) {}
    /*virtual const QChar* what()
    {
        return m_text.data();
    }
    void raise() const override { throw *this; }
    EdiException *clone() const override { return new EdiException(*this); }*/
};

#endif //EDITWRITE_EDIEXCEPTION_H
