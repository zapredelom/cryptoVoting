#include"AppManager.h"
#include"Primality.h"
#include<iostream>
#include<assert.h>
#include<stdexcept>
#include<utility>
#include<sstream>
#include<QMessageBox>
#include"Primality.h"
namespace E_voting
{
AppManager::AppManager(QObject *parrent) :
    QObject(parrent)
{
    m_dbManager = new DBManager();
    m_dbManager->init();
    m_secureNumber = 0;
    m_fixator = new PrivateKeyFixator;
    m_mainWindow = new MainWindow;
    m_setUpWindow = new SetUpWindow;
    m_encrypter = new ElGamalEncrypter();
    m_decryptor = new ElGamalDecrypter();
    m_encrypter->set_base(Primality::instance().get_random_integer());

    connect(m_setUpWindow,SIGNAL(addCandidate(const QString&)),
            this, SLOT(addCandidate(const QString&)));

    connect(m_setUpWindow,SIGNAL(setGenerator(const QString&)),
            this, SLOT(setGenerator(const QString&)));

    connect(m_setUpWindow,SIGNAL(setNumbersCount(int)),
            this, SLOT(setNumbersCount(int)));

    connect(m_setUpWindow,SIGNAL(ok()),this,SLOT(setUpEnded()));

    connect(m_mainWindow,SIGNAL(numberSelected()),this,SLOT(handleNumSelected()));

    connect(m_mainWindow,SIGNAL(candidatSelected(const Candidate * )),
            this,SLOT(handleCandidateChecked(const Candidate*)));

    connect( m_setUpWindow,SIGNAL(setBasePrime(const QString&)),
            this,SLOT(setBasePrime(const QString&)));

    connect( m_mainWindow,SIGNAL(numberFreezed(size_t)),this,SLOT(HandleNumberFreezed(size_t)));

    connect(m_fixator,SIGNAL(privatKeyFixed(const QString&)),
            this ,SLOT(handelPrivateKeyFixed(const QString&)));

    connect(m_mainWindow,SIGNAL(freezCandidates()),
            this,SLOT(handCandidateSelected()));
}

void AppManager::exec()
{
    m_setUpWindow->show();

}

void AppManager::setUpEnded()
{
    m_mainWindow->setNumbersRange();
    m_setUpWindow->close();
    //m_fixator->show();
    startVoting();
}

void AppManager::handelPrivateKeyFixed(const QString& op)
{

    m_decryptor->set_generator(m_encrypter->getGenerator());
    m_decryptor->set_y(m_encrypter->getY());
    m_decryptor->set_base(m_encrypter->getBase());
    m_decryptor->set_private_key((ElGamalBase::key_type(op.toStdString()))%(m_encrypter->getBase()));
    m_fixator->close();
    startVoting();


}

void AppManager::startVoting()
{
    m_mainWindow->show();
    m_mainWindow->generateRandomNumbers();
}

void AppManager::handleNumSelected()
{
    m_encrypter->generateSessionPrivateKey();
    m_mainWindow->setClocklReadOnly(false);
    m_mainWindow->enableFreezing(true);
    m_mainWindow->enableSelecting(false);
    chipherVector = encryptNumbers(m_mainWindow->getNumVector());
}

QVector<QPair<ElGamalEncrypter::key_type,ElGamalEncrypter::key_type> >
     AppManager::encryptNumbers(const QVector<int>& op)
{
    QVector<QPair<ElGamalEncrypter::key_type,ElGamalEncrypter::key_type> > ret;
    QPair<ElGamalEncrypter::key_type,ElGamalEncrypter::key_type> tmp;
    std::pair<ElGamalEncrypter::key_type,ElGamalEncrypter::key_type> std_tmp;
    for(int i =0;i< op.size();i++)
    {
        std_tmp = m_encrypter->encrypt( ElGamalEncrypter::key_type(op.at(i)));
        tmp.first = std_tmp.first;
        tmp.second = std_tmp.second;
        ret.push_back(tmp);
    }
    return ret;
}

void AppManager:: handleCandidateChecked(const Candidate* op)
{
    m_mainWindow->setClockValue(m_secureNumber + op->getNumber());

}

void AppManager::addCandidate(const QString& op)
{
    m_mainWindow->addCandidate(op);
    m_fixator->addCandidate(op);
}

void AppManager::setGenerator(const QString& op)
{
    ElGamalEncrypter::key_type tmp = ElGamalEncrypter::key_type(op.toStdString());
    m_encrypter->set_generator(tmp);
    
}

void AppManager::setBasePrime(const QString& op)
{
    ElGamalEncrypter::key_type tmp = ElGamalEncrypter::key_type(op.toStdString());
    m_encrypter->set_base(tmp);
}

void AppManager::setNumbersCount(int op)
{
    m_mainWindow->setNumbersCount(op);
}

void AppManager::HandleNumberFreezed(size_t op)
{
    m_mainWindow->setClockValue(op);
    m_mainWindow->setClocklReadOnly(true);
    m_mainWindow->enableFreezing(false);
    m_mainWindow->enableCandidates(true);
    m_secureNumber = op;
    std::stringstream stream;
    stream<<op;
    std::string op_string;
    op_string = stream.str();
    m_dbManager->addSecureNumber(op_string);
}

void AppManager::handCandidateSelected()
{
    std::string voter  = "unnamed voter";
    std::stringstream stream;
    stream<<rand();
    std::string op_string;
    op_string = stream.str();
    voter += op_string;
    m_dbManager->addElector(voter);
    std::string election = "( ";
    m_encrypter->set_y(Primality::instance().get_random_integer());
    std::pair<ElGamalBase::key_type,ElGamalBase::key_type> chiphertext;
    ElGamalBase::key_type tmp (m_mainWindow->getClockValue());
    chiphertext = m_encrypter->encrypt(tmp);
    election+= chiphertext.first.toString();
    election+=" ; ";
    election+=chiphertext.second.toString();
    election+=")";
    m_dbManager->addElection(election);
    m_dbManager->writeToDB();
    m_dbManager->finalize();
    QMessageBox * information = new QMessageBox();
    std::string message = "hello voter you have voted for candidate X";
    information->setText(QString::fromStdString( message));
    information->show();
    m_mainWindow->close();
}
}
