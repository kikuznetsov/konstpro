#include "homepage.h"
#include <Wt/WVBoxLayout>
#include <Wt/WHBoxLayout>

HomePage::HomePage(WContainerWidget *parent):WContainerWidget(parent){

    header_ = new Content("header.xhtml",parent);

    cnt_  = new Content("homePage.xhtml",parent);

    ava_ = new WImage(WLink("images/ava.png"));
    ava_->setMaximumSize(300,300);
    ava_->setMinimumSize(100,100);



    loadCPU_ = new LoadProc();

    //разметка
    WVBoxLayout* vBox = new Wt::WVBoxLayout();
    WHBoxLayout* hBox = new WHBoxLayout();
    vBox->addLayout(hBox);
        hBox->addWidget(ava_);
        hBox->addWidget(header_);
    vBox->addWidget(cnt_);
    vBox->addWidget(loadCPU_);

    this->setLayout(vBox);
}
