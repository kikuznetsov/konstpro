#include "homepage.h"
#include <Wt/WVBoxLayout>
#include <Wt/WHBoxLayout>

HomePage::HomePage(WContainerWidget *parent):WContainerWidget(parent){

    shortText = new WText("<h3>Breifly abreifly abreifly abreifly abreifly abreifly abreifly abreifly abreifly about me...</h3>");
    cnt  = new Content("homePage.html",parent);
    ava = new WImage(WLink("konst.png"));
    ava->setMaximumSize(200,200);

    //разметка
    WVBoxLayout* vBox = new Wt::WVBoxLayout();
    WHBoxLayout* hBox = new WHBoxLayout();
    vBox->addLayout(hBox);
        hBox->addWidget(ava);
        hBox->addWidget(shortText);
    vBox->addWidget(cnt);

    this->setLayout(vBox);
}
