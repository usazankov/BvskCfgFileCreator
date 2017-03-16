#include "maincontroller.h"

MainController* MainController::p_contr=Q_NULLPTR;

MainController::MainController(QObject *parent) : QObject(parent)
{
    p_type=0;
    parser=Q_NULLPTR;
    doc=Q_NULLPTR;
}

bool MainController::parsingCalibrateOrTermoCalibrate()
{
    if(doc!=Q_NULLPTR){
        doc->clearErrorsInfo();
        parser = new ParserTableOfDouble(doc->document()->textDocument()->toPlainText());
        try{
            parser->read();
        }catch(ParserTableOfDouble::ParsingEx ex){
            ErrorsHandle::sendMessage("Error on "+QString::number(ex.numberStrEx)+": "+ex.infoEx, ErrorsHandle::Error);
            doc->addErrorInfo(ex.numberStrEx, ex.infoEx);
            doc->errorHighlighting();
            return 0;
        }
        CheckerInputData checker;
        try{
            parser->accept(&checker);
        }catch(CheckerInputData::CheckingEx ex){
            ErrorsHandle::sendMessage("Error on "+QString::number(ex.numberStrEx)+": "+ex.infoEx, ErrorsHandle::Error);
            doc->addErrorInfo(ex.numberStrEx, ex.infoEx);
            doc->errorHighlighting();
            return 0;
        }
        if(checker.isValid()){
            ErrorsHandle::sendMessage("Input data is valid", ErrorsHandle::Good);
            return 1;
        }else{
            ErrorsHandle::sendMessage("Error: Input data is not valid", ErrorsHandle::Error);
            return 0;
        }

    }else{
        ErrorsHandle::sendMessage("Error: DocumentHandler is null", ErrorsHandle::Error);
        return 0;
    }
    return 0;
}

bool MainController::processingCalibrate()
{
    if(parsingCalibrateOrTermoCalibrate()){
        if(p_type==0){
            GetterInputData getter;
            parser->accept(&getter);
            InputCalibrateData *d=getter.getInputData();
            displayCalibrate(d);
            CalculatorCalibrateData calculator(d);
            calculator.process();
            resultTxt=calculator.result();
            ErrorsHandle::sendMessage(resultTxt);
            return 1;
        }
    }else
        return 0;
}

void MainController::displayCalibrate(InputCalibrateData *d) const
{
    QString txt;
    for (const auto& v : d->data) {
        txt+="Сектор №"+QString::number(v.first+1)+"<br>";
        foreach (InputCalibrateData::FormatStr value, v.second) {
            txt+="Aцу = "+QString::number(value.Acu.toDegrees())+
                    " Bцу = "+QString::number(value.Bcu.toDegrees())+
                    " Aизм = "+QString::number(value.Aizm.toDegrees())+
                    " Bизм = "+QString::number(value.Bizm.toDegrees())+
                    "<br>";
        }
    }
    ErrorsHandle::sendMessage(txt);
}

QString MainController::result() const
{
    return resultTxt;
}

void MainController::saveResultToFile(const QUrl &path) const
{
    QString pathToFile=path.toLocalFile();
    if(!pathToFile.isEmpty()){
        if(!pathToFile.endsWith(".cfg"))
            pathToFile.append(".cfg");
    }
    QFile file(pathToFile);
    if(!file.open(QIODevice::WriteOnly)){
        ErrorsHandle::sendMessage("Not saved",ErrorsHandle::Error);return;
    }
    QTextStream stream_file(&file);
    QString result=doc->document()->textDocument()->toPlainText();
    stream_file<<result;
    file.close();
    ErrorsHandle::sendMessage("Saved",ErrorsHandle::Good);
}

DocumentHandler *MainController::docHandler() const
{
    return doc;
}

void MainController::setDocHandler(DocumentHandler *value)
{
    doc = value;
}

int MainController::typeProcess() const
{
    return p_type;
}

void MainController::setTypeProcess(int type)
{
    this->p_type=type;
}

MainController::~MainController()
{
    delete parser;
}

MainController *MainController::getInstance()
{
    if(p_contr==Q_NULLPTR){
        p_contr=new MainController;
        return p_contr;
    }else
        return p_contr;
}

bool MainController::process()
{
    if(p_type==0||p_type==1){
        ErrorsHandle::sendMessage("Start parsing...");
        if(processingCalibrate())
            return 1;
        else
            return 0;
    }
}

void MainController::check()
{

}
