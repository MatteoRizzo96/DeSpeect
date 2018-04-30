#include "gtest/gtest.h"
#include <QApplication>
#include <commandlist.h>
#include <unistd.h>
//#define GetCurrentDir getcwd

#include "ui_view.h"
#include "modelview.h"
#include <QFileDialog>
#include <graphmanager.h>
#include <loadplugincommand.h>
#include <setspeectconfigcommand.h>
#include <uttprocessorcommand.h>
#include "relation.h"
#include "QTextStream"
#include <QFont>
#include <QProcess>

TEST(View, Graphprint){
    int argc;
    char **argv=NULL;
    QApplication app(argc,argv);
    Speect* sTest=new Speect();
    CommandList::CommandBuilder* builder=new CommandList::CommandBuilder(sTest);
    ModelView mv(builder);
    mv.requestConfiguration("./cmu_arctic_slt/voice.json", Configuration::Voice);
    mv.loadSelectedProcessor();
    builder->LoadConfig(Configuration::UtteranceText,"hi").getCommandList()->executeAll();
    mv.runSingleStep();
    mv.requestProcessorRun();
    mv.requestAudioSave("test.wav");
    mv.utteranceTypeChanged();
    mv.loadSelectedProcessor();
    mv.findNode("Token","",false);
    mv.findNode("Token","",true);
    sTest->getUttTypeName();
    EXPECT_TRUE(NULL!=sTest->getUtterance()->getUtterance());

    delete builder;
    delete sTest;
}

TEST(View, Graphprintcomplete){
    int argc;
    char **argv=NULL;
    QApplication app(argc,argv);
    Speect* sTest=new Speect();
    CommandList::CommandBuilder* builder=new CommandList::CommandBuilder(sTest);
    ModelView mv(builder);
    mv.requestConfiguration("./cmu_arctic_slt/voice.json", Configuration::Voice);
    mv.loadSelectedProcessor();
    builder->LoadConfig(Configuration::UtteranceText,"hi").getCommandList()->executeAll();
    Ui::View* ui = mv.getUiView();
    ui->UtteranceText->setPlainText("hi");
    mv.runSingleStep();
    mv.requestProcessorRun();
    sTest->getUttTypeName();
    EXPECT_TRUE(NULL!=sTest->getUtterance()->getUtterance());

    delete builder;
    delete sTest;
}
