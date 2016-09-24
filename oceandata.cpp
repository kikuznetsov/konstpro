#include <Wt/WHBoxLayout>
#include <Wt/WVBoxLayout>
#include <Wt/WStackedWidget>
#include "oceandata.h"

OceanData::OceanData(WContainerWidget *parent):WContainerWidget(parent){

    // Create a stack where the contents will be located.
    Wt::WStackedWidget *contentsMenu = new Wt::WStackedWidget();

    menu_ = new Wt::WMenu(contentsMenu, Wt::Vertical,parent);
    menu_->setStyleClass("nav nav-pills nav-stacked");
    menu_->setWidth(100);



    // Add menu items using the default lazy loading policy.
    textOverview_ = new WText("Here will be a map with overview of experiments ..............................................");
    //chooseOcean_ = new ChooseOcean(contentsMenu);
    WContainerWidget* wtCont = new WContainerWidget();
    menu_->addItem("Overview data",textOverview_);
    menu_->addItem("Export data", wtCont);
    menu_->itemSelected().connect(std::bind([=] (Wt::WMenuItem *item) {
        wtCont->clear();
        if(item->text()=="Export data"){
            chooseOcean_ = new ChooseOcean(wtCont);
        }
    }, std::placeholders::_1));



    WText* title = new WText("<h3>In-situ wave measurements from Sakhakin</h3>");

    WVBoxLayout* vBox = new WVBoxLayout();
    vBox->addWidget(title);
    WHBoxLayout* hBox = new WHBoxLayout();
    hBox->addWidget(menu_);
    hBox->addWidget(contentsMenu);
    vBox->addLayout(hBox);
    this->setLayout(vBox);
}
