#include"Candidate.h"
#include"Canditates.h"
#include<QApplication>
#include"Numbers.h"
#include"MainWindow.h"
#include"SetUpWindow.h"
#include"AppManager.h"
#include"PrivatKeyFixatator.h"
#include<QDial>
#include<QStyle>
#include<iostream>
int main(int argc,char* argv[])
{
    try
    {
        QApplication app(argc,argv);
        E_voting::AppManager *x = new E_voting::AppManager;
        x->exec();
        return app.exec();
    }

    catch(std::exception* e)
    {
        std::cout<<e->what();
    }
}
       
