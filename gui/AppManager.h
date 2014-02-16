#include"MainWindow.h"
#include"SetUpWindow.h"
#include"ElGamalEncrypter.h"
#include"ElGamalDecrypter.h"
#include"DBManager.h"
#include"PrivatKeyFixatator.h"
#include<QVector>
#include<QPair>
#ifndef APP_MANAGER_H
#define APP_MANAGER_H
namespace E_voting
{

class AppManager :public QObject
{
    Q_OBJECT
public:
    AppManager(QObject * parrent = 0);
    void exec();
    QVector<QPair<ElGamalEncrypter::key_type,ElGamalEncrypter::key_type> >
        encryptNumbers(const QVector<int>&numbersToEncrypt);
private slots:
    void addCandidate(const QString&);
    void setGenerator(const QString &);
    void setBasePrime(const QString&);
    void setNumbersCount(int);
    void setUpEnded();
    void handleNumSelected();
//    void getSelectedNumber(const int);
    void handleCandidateChecked(const Candidate*);
    void handelPrivateKeyFixed(const QString&  );
    void HandleNumberFreezed(size_t);
    void handCandidateSelected();

private:
    size_t m_secureNumber;
    QVector<QPair<ElGamalEncrypter::key_type,ElGamalEncrypter::key_type> > chipherVector;
    MainWindow* m_mainWindow;
    PrivateKeyFixator* m_fixator;
    SetUpWindow* m_setUpWindow;
    ElGamalEncrypter* m_encrypter;
    ElGamalDecrypter* m_decryptor;
    DBManager* m_dbManager;
    void startVoting();

};
}
#endif



