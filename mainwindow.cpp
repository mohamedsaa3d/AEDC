#include "mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initSidePanel();
    initGUIelements();
    initAppCache();
    initDashboard();
    //initPeriodicThreads();

    SiePanelClick("dashboard"); // Set default Tab for Dashboard


    //----------------------------

    auto header=ui->treeWidget->header();
    QTreeWidgetItem *tools = new QTreeWidgetItem(ui->treeWidget);
    tools->setExpanded(true);

    header->setSectionResizeMode(0, QHeaderView::Stretch);
    header->setSectionResizeMode(1, QHeaderView::Stretch);
    //header->setSectionResizeMode(2, QHeaderView::Stretch);
    header->setStretchLastSection(false);

//    for( int i = 0; i < ui->treeWidget->topLevelItemCount(); ++i )
//    {
//       QTreeWidgetItem *item = ui->treeWidget->topLevelItem( i ); //CEO

//       item->setExpanded(true);
//       item->setBackgroundColor(0, QColor(214,184,46,100));
//       item->setBackgroundColor(1, QColor(214,184,46,100));

//       ui->label->setText( item->text(0) );

//       QString text = item->text(0);

//       qDebug() << "\tChild(0) :: " << item->text(0);

//       //#################################################################

//       for( int i = 0; i < item->childCount(); ++i ) //VICE
//       {
//            item->child(i)->setExpanded(true);
//            item->child(i)->setBackgroundColor(0, QColor(214,184,46,100));
//            item->child(i)->setBackgroundColor(1, QColor(214,184,46,100));

//            qDebug() << "\t\tChild(1) :: " << item->child(i)->text(0);

//            //#################################################################

//            for( int j = 0; j < item->child(i)->childCount(); ++j ) //SECTORS
//            {
//                 item->child(i)->child(j)->setExpanded(true);
//                 item->child(i)->child(j)->setBackgroundColor(0, QColor(214,184,46,100));
//                 item->child(i)->child(j)->setBackgroundColor(1, QColor(214,184,46,100));

//                 qDebug() << "\t\t\tChild(2) :: " << item->child(i)->child(j)->text(0);

//                 //#################################################################

//                 for( int k = 0; k < item->child(i)->child(j)->childCount(); ++k ) //Administration
//                 {
//                      item->child(i)->child(j)->child(k)->setExpanded(true);
//                      item->child(i)->child(j)->child(k)->setBackgroundColor(0, QColor(214,184,46,100));
//                      item->child(i)->child(j)->child(k)->setBackgroundColor(1, QColor(214,184,46,100));

//                      qDebug() << "\t\t\t\tChild(3) :: " << item->child(i)->child(j)->child(k)->text(0);


//                 }


//            }

//       }



//       // Do something with item ...
//    }






    //===============================================================

    //-------------------------------------------------------------- Table Header
    QHeaderView* DailyAreasTableHeader = ui->DailyAreasTableWidget->horizontalHeader();
    DailyAreasTableHeader->setSectionResizeMode(QHeaderView::Stretch);
    DailyAreasTableHeader->setSectionResizeMode( 0, QHeaderView::Fixed );
    QStringList DailyAreasTableHeaderList;
    DailyAreasTableHeaderList << "المنطقة" << "عدد" << "قيمة الأصدار الكلى" << "عدد" << "قيمة الأصدار الجاري" ;
    ui->DailyAreasTableWidget->setHorizontalHeaderLabels(DailyAreasTableHeaderList);
    ui->DailyAreasTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->DailyAreasTableWidget->verticalHeader()->setVisible(false); // Hide vertical row numbers






    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("db4free.net");
    db.setDatabaseName("sa3doon_db_mit");
    db.setUserName("sa3doon");
    db.setPassword("123456789");
    //db.setConnectOptions("CLIENT_SSL=1;CLIENT_IGNORE_SPACE=1");
    db.setPort(3306);

    bool ok = db.open();

    qDebug() << "DB Status: " << ok;

    if(!ok)
    {
        return;
    }

    QSqlQuery query;

    query.prepare( "CREATE TABLE IF NOT EXISTS MilinkCoC (id INTEGER UNIQUE PRIMARY KEY, firstname VARCHAR(30), lastname VARCHAR(30))" );

    if(query.exec())
    {
        qDebug() << "Table created";
    }
    else
    {
        qDebug() << ("Error");
        qDebug() << ("MySQL error:" + QString( query.lastError().text() ) );
        qDebug() << ("MySQL error code:"+ QString::number(query.lastError().number()));
    }


    qDebug() << "DB Tables: "<< db.tables();


    query.exec("INSERT INTO MilinkCoC (id, firstname, lastname) "
               "VALUES (1002, 'Mohamed', 'Saad')");

    query.exec("SELECT id FROM MilinkCoC");

    while (query.next())
    {
        int employeeId = query.value(0).toInt();
        qDebug() << " >> employeeId = "<< employeeId;
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setWindowMaximized()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();


     QTimer::singleShot(10, this, [=]()
      {
         int MainWindow_Height = screenGeometry.height();
         int MainWindow_Width_Expanded = screenGeometry.width();
         this->setFixedSize( MainWindow_Width_Expanded , MainWindow_Height-40 );
      });
}

//#######################################################################################

void MainWindow::initSidePanel()
{
    awesome = new QtAwesome( qApp );
    awesome->initFontAwesome();     // This line is important as it loads the font and initializes the named icon map

    QVariantMap options;

    options.insert( "color", QColor(255,255,255));
    options.insert( "color-active", QColor(255,255,255));
    //options.insert( "color-disabled", QColor(2,10,255)); //Color if the button is disabled

    ui->Menu_Dashboard_PB->setIcon( awesome->icon( fa::th, options ));
    ui->Menu_Bills_PB->setIcon( awesome->icon( fa::briefcase, options ));
    ui->Menu_Pay_PB->setIcon( awesome->icon( fa::creditcard, options ));
    ui->Menu_Areas_PB->setIcon( awesome->icon( fa::streetview, options ));
    ui->Menu_Employees_PB->setIcon( awesome->icon( fa::users , options ));
    ui->Menu_Operations_PB->setIcon( awesome->icon( fa::car, options ));
    ui->Menu_Reports_PB->setIcon( awesome->icon( fa::linechart , options ));
    ui->Menu_Settings_PB->setIcon( awesome->icon( fa::sliders, options ));
    ui->Menu_About_PB->setIcon( awesome->icon( fa::info, options ));


//    QPixmap logoP(":/Resourese/SoundTracks/Images/Logos/milink_logo_white.png"); // load pixmap
//    // get label dimensions
//    int w = ui->sidepanelLogo->width() - 5;
//    int h = ui->sidepanelLogo->height() - 5;

//    // set a scaled pixmap to a w x h window keeping its aspect ratio
//    ui->sidepanelLogo->setPixmap(logoP.scaled(w,h,Qt::KeepAspectRatio));

    attachSidePanelSignals();

}

void MainWindow::initGUIelements()
{
//    initJobInfoTab();
//    initHistoricalGraphsTab();
//    initConnectionTab();
//    initDrillerCaddieTab();
//    initToolConfigTab();
//    initOnlineTab();
//    initAutocalTab();
//    initMemoryTab();
//    initSettingsTab();
//    initfirmwareloaderTab();
//    initPositionControlTab();
//    initCertificationCenterTab();
//    initEmailTab();
//    initDebugLog();

//    ui->sidePanelMilinkVersion->setText(QString("%1").arg(GIT_CURRENT_VERSION));
//    ui->build_version_label->setText(QString("Build: %1 - %2").arg(GIT_CURRENT_BRANCH).arg(GIT_CURRENT_COMMIT));

//    ui->aboutText_version->setText(QString("This release version of Milink is [ %1 ], build [ %2 ].").arg(GIT_CURRENT_VERSION).arg(GIT_CURRENT_COMMIT));

}

void MainWindow::initDashboard()
{

//    LoggedUserLabel = ui->loggedUser_Label;


    ui->calendarWidget->setSelectedDate(QDate::currentDate());

    ui->dashboardWellName_Label->setText(this->cachedData->value("job/wellname").toString());
    ui->dashboardRigName_Label->setText(this->cachedData->value("job/rigname").toString());
    ui->dashboardClientName_Label->setText(this->cachedData->value("job/client").toString());



}

void MainWindow::attachSidePanelSignals()
{
    QObject::connect( ui->Menu_Dashboard_PB  , &QPushButton::clicked , this , [=](){SiePanelClick( "dashboard" );} );
    QObject::connect( ui->Menu_Bills_PB      , &QPushButton::clicked , this , [=](){SiePanelClick( "bills" );} );
    QObject::connect( ui->Menu_Pay_PB        , &QPushButton::clicked , this , [=](){SiePanelClick( "payment" );} );
    QObject::connect( ui->Menu_Areas_PB      , &QPushButton::clicked , this , [=](){SiePanelClick( "areas" );} );
    QObject::connect( ui->Menu_Employees_PB  , &QPushButton::clicked , this , [=](){SiePanelClick( "employees" );} );
    QObject::connect( ui->Menu_Operations_PB , &QPushButton::clicked , this , [=](){SiePanelClick( "operations" );} );
    QObject::connect( ui->Menu_Reports_PB    , &QPushButton::clicked , this , [=](){SiePanelClick( "reports" );} );
    QObject::connect( ui->Menu_Settings_PB   , &QPushButton::clicked , this , [=](){SiePanelClick( "settings" );} );
    QObject::connect( ui->Menu_About_PB      , &QPushButton::clicked , this , [=](){SiePanelClick( "about" );} );

}

void MainWindow::initAppCache()
{
     cachedData = new QSettings("AEDC", "AEDC Cache"); //For saving cached data

    if(cachedData->value("general/sync_auto").toString() == "true")
    {

    }
    else if(cachedData->value("general/sync_auto").toString() == "false")
    {

    }
    else
    {

    }



}

void MainWindow::SiePanelClick(QString ButtonName)
{
    //################################################ The If conditions must be ordered same as UI Stacked Pages order
    int i=0;

    if( ButtonName== "dashboard" )
    {
        initDashboard(); //Re-initialize dashboard elements to update any changed data
        ui->stackedWidget->setCurrentIndex(i);
        ui->Menu_Dashboard_PB->setChecked(true);
    }
    else
    {
        ui->Menu_Dashboard_PB->setChecked(false);
        i++;
    }
    //--------------------------------------------------
    if( ButtonName== "bills" )
    {
        ui->stackedWidget->setCurrentIndex(i);
        ui->Menu_Bills_PB->setChecked(true);
    }
    else
    {
        ui->Menu_Bills_PB->setChecked(false);
        i++;
    }
    //--------------------------------------------------
    if( ButtonName== "payment" )
    {
        ui->stackedWidget->setCurrentIndex(i);
        ui->Menu_Pay_PB->setChecked(true);
    }
    else
    {
        ui->Menu_Pay_PB->setChecked(false);
        i++;
    }
    //--------------------------------------------------
    if( ButtonName== "areas" )
    {
        ui->stackedWidget->setCurrentIndex(i);
        ui->Menu_Areas_PB->setChecked(true);
    }
    else
    {
        ui->Menu_Areas_PB->setChecked(false);
        i++;
    }
    //--------------------------------------------------
    if( ButtonName== "employees" )
    {
        ui->stackedWidget->setCurrentIndex(i);
        ui->Menu_Employees_PB->setChecked(true);
    }
    else
    {
        ui->Menu_Employees_PB->setChecked(false);
        i++;
    }
    //--------------------------------------------------
    if( ButtonName== "operations" )
    {
        ui->stackedWidget->setCurrentIndex(i);
        ui->Menu_Operations_PB->setChecked(true);
    }
    else
    {
        ui->Menu_Operations_PB->setChecked(false);
        i++;
    }
    //--------------------------------------------------
    if( ButtonName== "reports" )
    {
        ui->stackedWidget->setCurrentIndex(i);
        ui->Menu_Reports_PB->setChecked(true);
    }
    else
    {
        ui->Menu_Reports_PB->setChecked(false);
        i++;
    }
    //--------------------------------------------------
    if( ButtonName== "settings" )
    {
        ui->stackedWidget->setCurrentIndex(i);
        ui->Menu_Settings_PB->setChecked(true);
    }
    else
    {
        ui->Menu_Settings_PB->setChecked(false);
        i++;
    }
    //--------------------------------------------------
    if( ButtonName== "about" )
    {
        ui->stackedWidget->setCurrentIndex(i);
        ui->Menu_About_PB->setChecked(true);
    }
    else
    {
        ui->Menu_About_PB->setChecked(false);
        i++;
    }
    //--------------------------------------------------


}

void MainWindow::on_id_cursorPositionChanged(int arg1, int arg2)
{

        // console.log("nationalIDdecoding");

        bool ValidID1 = false;
        bool ValidID2 = false;
        bool ValidID3 = false;
        bool ValidID4 = false;





        QString national_id = ui->id->text().trimmed();

        uint8_t id_length = national_id.size();


        //------------------------- checking number of digits --------------------
       qDebug() << "id_length = " + id_length ;

        if(  id_length!=14  )
        {
            return;
            ValidID1 = false;
        }
        else
        {
            ValidID1 = true;
        }


        //------------------------- checking first digit --------------------

        if(  (  ( national_id[0] != "2" ) &&  ( national_id[0] != "3" )  ) && id_length>=1  )
        {
            ValidID2 = false;
        }
        else
        {
            ValidID2 = true;
        }

        //------------------------- checking DOB --------------------

        if(id_length==14)
        {
            QString DOB = QString("%1%2 / %3%4 / 19%5%6").arg(national_id[5])
                                                         .arg(national_id[6])
                                                          .arg(national_id[3])
                                                          .arg(national_id[4])
                                                          .arg(national_id[1])
                                                          .arg(national_id[2]);


            ui->bod->setText( DOB );

            qDebug() <<  "DOB = " + DOB;
        }



         //------------------------- checking Gender --------------------

        qDebug() << "checking Gender  national_id[12]).toLatin1 : " << national_id[12].toLatin1() ;


         if( national_id[12] != "" )
         {
            if( (national_id[12]).toLatin1() %2 == 0 )
            {
                ui->gender->setText( "أنثى" );
            }
            else
            {
                ui->gender->setText( "ذكر" );
            }
            ValidID3 = true;
         }
         else
         {
            ui->gender->setText( "" );
            ValidID3 = false;
         }

         //------------------------- checking Govern --------------------
         QString govCode = "00";

         if( (national_id[7]!= "")  &&  (national_id[8] != "") )
         {
            ValidID4 = true;

            govCode = QString("%1%2").arg(national_id[7]).arg(national_id[8]);



            int govCodeNum = govCode.toInt();

            qDebug() << "govCodeNum : " << govCodeNum;

            switch(govCodeNum)
            {
                case 1:
                    ui->gov->setText( "القاهرة" ); break;
                case 2:
                    ui->gov->setText( "الإسكندرية" ); break;
                case 3:
                    ui->gov->setText( "بورسعيد" ); break;
                case 4:
                    ui->gov->setText( "السويس" ); break;
                case 11:
                    ui->gov->setText( "دمياط" ); break;
                case 12:
                    ui->gov->setText( "الدقهلية" ); break;
                case 13:
                    ui->gov->setText( "الشرقية" ); break;
                case 14:
                    ui->gov->setText( "القليوبية" ); break;
                case 15:
                    ui->gov->setText( "كفر الشيخ" ); break;
                case 16:
                    ui->gov->setText( "الغربية" ); break;
                case 17:
                    ui->gov->setText( "المنوفية" ); break;
                case 18:
                    ui->gov->setText( "البحيرة" ); break;
                case 19:
                    ui->gov->setText( "الإسماعيلية" ); break;
                case 21:
                    ui->gov->setText( "الجيزة" ); break;
                case 22:
                    ui->gov->setText( "بني سويف" ); break;
                case 23:
                    ui->gov->setText( "الفيوم" ); break;
                case 24:
                    ui->gov->setText( "المنيا" ); break;
                case 25:
                    ui->gov->setText( "أسيوط" ); break;
                case 26:
                    ui->gov->setText( "سوهاج" ); break;
                case 27:
                    ui->gov->setText( "قنا" ); break;
                case 28:
                    ui->gov->setText( "أسوان" ); break;
                case 29:
                    ui->gov->setText( "الأقصر" ); break;
                case 31:
                    ui->gov->setText( "البحر الأحمر" ); break;
                case 32:
                    ui->gov->setText( "الوادي الجديد" ); break;
                case 33:
                    ui->gov->setText( "مطروح" ); break;
                case 34:
                    ui->gov->setText( "شمال سيناء" ); break;
                case 35:
                    ui->gov->setText( "جنوب سيناء" ); break;
                case 88:
                    ui->gov->setText( "خارج مصر" ); break;
                default:
                    ui->gov->setText( "" );
                    ValidID4 = false;
                    break;
            }

         }
         else
         {
            ui->gender->setText( "" );
            ValidID4 = false;
         }



        //-----------------------------------------------------------------
        if(ValidID1 && ValidID2 && ValidID3 && ValidID4)
        {
            //ID_ERROR_CONTAINER.style.display = "none";
            qDebug() << "Valid ID";
        }
        else
        {
            //ID_ERROR_CONTAINER.style.display = "block";
            qDebug() << "Not Valid ID";
        }


}
