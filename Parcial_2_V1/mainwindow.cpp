#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include <math.h>
/*struct Eng_Pow//estructura para almacenar mas facil los datos
{
    double Tiempo;
    double Volt;
    double Cur;
};*/

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->Tester,SIGNAL(clicked(bool)),this,SLOT(Lectura()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::Lectura()
{
    //struct Eng_Pow HOLDER;
    FILE *f = fopen("C:/Users/Ing. Gadiel Pardo/Desktop/Parcial 2/vi_1.dat", "rb");
    if(f==nullptr)
    {
        qDebug()<<"No se pudo abrir el archivo";
    }
    //determino nro de elementos-----------------//
    fseek(f,0,SEEK_END);//voy a final
    int TamByte = ftell(f); //extraigo tamaño en Bytes
    int Cant= TamByte/sizeof(double);//determino nro de floats
    qDebug()<<Cant;//cantidad de datos doubles
    fseek(f,0,SEEK_SET);//vuelvo al inicio
    //-------------------------------------------////200 lineas
    int x=Cant/3;
    I.resize(x);
    V.resize(x);
    T.resize(x);
    for(int i=0;i<x;i++)
    {
        fread(&T[i],sizeof(double),1,f);
        fread(&V[i],sizeof(double),1,f);
        fread(&I[i],sizeof(double),1,f);
    }
    ui->Qwindows->addGraph();
    ui->Qwindows->addGraph();
    ui->Qwindows->graph(0)->setData(T,V);
    QPen pen;
    pen.setColor(Qt::red);
    ui->Qwindows->graph(1)->setData(T,I);
    ui->Qwindows->graph(1)->setPen(pen);//cambio color
    ui->Qwindows->rescaleAxes();
    ui->Qwindows->replot();
   //--------Determino fi --------------//
    double Tfi=Two(I,T);
    qDebug()<<Tfi;
    //angulo de desfase
    float Ang=(3.1415)/(0.01*Tfi);
    //--------PUNTO 3 Calculo de RMS--------------//

    double IRMS = RMS(I,T,x);
    double VRMS = RMS(V,T,x);
    ui->IrmsLine->setText(Qstring::number(IRMS));
    ui->VrmsLine->setText(Qstring::number(VRMS));
    //Calculo de Potencia
    double P = (IRMS*VRMS*cos(Ang));
    fclose(f);
}

int MainWindow::ROOTER(QVector<double> I)
{
    //full Porcesador
     int PreRoot;
     int band=0;
     for(int i=0;band!=1;i++)
     {
         qDebug()<<"Estoy dentro";
         if(I[i]<0&&(I[i+1])<0)
         {

         }else
         {
            PreRoot=i;
            band=1;
            qDebug()<<PreRoot;
         }
     }
     return PreRoot;
}

double MainWindow::Two(QVector<double>I,QVector<double>t)//funcion que determina el tiempo para punto 2
{//esta funcion calcula la recta entre dos puntos y el punto cero podra haberse adapato bisection.
    int Rootr = ROOTER(I);

    float Pendiente=((I[Rootr]-I[Rootr+1])/(t[Rootr]-t[Rootr+1]));
    float root;
    int band=0;
    for(int i=0;band!=1;i++)
    {
        if((Pendiente*i)==0)
        {
            root=i;//es el valor donde la reca es cero.
            band=1;
        }
    }
  return root;
}

float MainWindow::RMS(QVector<double>I,QVector<double>t,int tam)
{
  float RMSS = sqrt((1/(t[tam]-t[0])*Integral(I,t,tam)));//Calculo de rms

}

float MainWindow::Integral(QVector<double>I,QVector<double>t,int tam)
{
    Suma =0;
    for(int i=0;i+1<=tam;i++)
    {
        a=((t[i+1]-t[i]) *I[i]);
        b= (a*a*a)/3;
        suma= suma + b;//suma rieman
    }
    return suma;
}






