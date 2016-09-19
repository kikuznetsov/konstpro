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
    chooseOcean_ = new ChooseOcean();

    menu_->addItem("Export data", chooseOcean_);
    menu_->addItem("Overview data", textOverview_);


    WText* title = new WText("<h3>In-situ wave measurements from Sakhakin</h3>");

    WVBoxLayout* vBox = new WVBoxLayout();
    vBox->addWidget(title);
    WHBoxLayout* hBox = new WHBoxLayout();
    hBox->addWidget(menu_);
    hBox->addWidget(contentsMenu);
    vBox->addLayout(hBox);
    this->setLayout(vBox);
}
