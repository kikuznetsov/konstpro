#include <Wt/WHBoxLayout>
#include <Wt/WVBoxLayout>
#include <Wt/WStackedWidget>
#include "oceandata.h"

#include "oceansession.h"

OceanData::OceanData(WContainerWidget *parent):WContainerWidget(parent){


    //db connection created
    db_ = OceanSession::createConnectionPool("test.db");

    Wt::WStackedWidget *contentsMenu = new Wt::WStackedWidget();// Create a stack where the contents will be located.

    //menu_ = new Wt::WMenu(contentsMenu, Wt::Vertical,parent);
    menu_ = new Wt::WMenu(contentsMenu, Wt::Vertical,parent);
    menu_->setStyleClass("nav nav-pills nav-stacked");
    menu_->setMaximumSize(200,WLength::Auto);



    // Add menu items using the default lazy loading policy.
    //chooseOcean_ = new ChooseOcean(contentsMenu);
//    menu_->addItem("About measurements", new WText("This data was collected by group of scientist..."));
//    menu_->addItem("Map", new MapOcean(wtCont));
//    menu_->addItem("Export data", new ChooseOcean(wtCont));

    //parent->addWidget(contentsMenu);
    //mapOcean_ = new MapOcean(wtCont);
    WContainerWidget* wtContMap = new WContainerWidget(parent);
    mapOcean_  = new MapOcean(wtContMap);
    WContainerWidget* wtContPlot = new WContainerWidget(parent);
    plotdata_  = new Plotdata(*db_, wtContPlot);
    menu_->addItem("About measurements", new WText("This data was collected by group of scientist..."));
    menu_->addItem("Map", wtContMap);
    menu_->addItem("Export data", wtContPlot);
//    menu_->itemSelected().connect(std::bind([=] (Wt::WMenuItem *item) {
//        wtContPlot->clear();
//        if(item->text()=="Export data"){
//           plotdata_  = new Plotdata(*db_, wtContPlot);
//        }
//    }, std::placeholders::_1));


    WText* title = new WText("<h2>In-situ wave measurements on shelf zone of Sakhalin Island</h2>");

    WVBoxLayout* vBox = new WVBoxLayout();
    vBox->addWidget(title);
    WHBoxLayout* hBox = new WHBoxLayout();
    hBox->addWidget(menu_);
    hBox->addWidget(contentsMenu);
    vBox->addLayout(hBox);
    this->setLayout(vBox);
}
//        MapOcean* mapocean = new MapOcean(wtCont);
//    }));
