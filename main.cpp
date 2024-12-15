#include <QApplication>
#include <QWidget>
#include <QFile>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QProcess>
#include <QUiLoader>
#include <QStringList>
#include <QMessageBox>
#include <iostream>
#include <QDir>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);    
    QStringList arguments = QCoreApplication::arguments();
    
    if (arguments.size() < 2) {
        return -1; 
    }    

    QString uiFilePath = QCoreApplication::applicationDirPath() + "/UIData.ui";
    
    QUiLoader loader;    
    QFile file(uiFilePath);
    if (!file.open(QFile::ReadOnly)) {
        return -1; 
    }    
    QWidget *mainWindow = loader.load(&file);
    file.close();    

    if (!mainWindow) {
        return -1; 
    }

    QLabel *descriptionLabel = mainWindow->findChild<QLabel*>("Description");
    QLineEdit *passwordLineEdit = mainWindow->findChild<QLineEdit*>("PasswordLine");
    QPushButton *provideButton = mainWindow->findChild<QPushButton*>("ProvideButton");
    QPushButton *cancelButton = mainWindow->findChild<QPushButton*>("CancelButton");    

    QString command = arguments[1];
    QStringList sudoArgs = arguments.mid(2);      

    descriptionLabel->setText(QString("\"%1\" is requesting superuser privileges. Enter the password or decline the request").arg(command));    

    QObject::connect(provideButton, &QPushButton::clicked, [&]() {
        QString password = passwordLineEdit->text();        
        if (password.isEmpty()) {
            return; 
        }        
        QString sudoCommand = "callsudo -S " + command + " " + sudoArgs.join(" ");        
        QProcess process;
        
        process.setProcessChannelMode(QProcess::MergedChannels);         
        process.start("bash", QStringList() << "-c" << "echo " + password + " | " + sudoCommand);        
        process.waitForFinished();        
        QByteArray output = process.readAll();        
        if (process.exitStatus() == QProcess::NormalExit && process.exitCode() == 0) {
            std::cout << output.toStdString() << std::endl;              
            mainWindow->close();
        } else {
            QMessageBox::warning(mainWindow, "Error", "Invalid password.");
        }
    });

    QObject::connect(cancelButton, &QPushButton::clicked, [&]() {
        mainWindow->close();
    });

    mainWindow->show();
    return app.exec();
}
