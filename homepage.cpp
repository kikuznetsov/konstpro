#include "homepage.h"
#include <Wt/WVBoxLayout>
#include <Wt/WHBoxLayout>

HomePage::HomePage(WContainerWidget *parent):WContainerWidget(parent){

    header_ = new Content("header.xhtml",parent);

    cnt_  = new Content("homePage.xhtml",parent);

    ava_ = new WImage(WLink("konst.png"));
    ava_->setMaximumSize(200,200);

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
