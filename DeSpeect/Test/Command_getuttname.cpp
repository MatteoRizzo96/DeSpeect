#include "gtest/gtest.h"
#include "../Model/Command/header/setspeectconfigcommand.h"
#include "../Model/SpeectWrapper/header/Speect.h"
#include "../Model/Command/header/createaudiocommand.h"
#include "../Model/Command/header/commandlist.h"
#include <fstream>

TEST(Command, getuttnamesuccess){
    Speect* s=new Speect();
    CommandList::CommandBuilder* builder=new CommandList::CommandBuilder(s);
    CommandList* commands;
    commands=builder->getCommandList();
    commands->getRelationNames();
    commands->getRelation("");
    commands=builder->LoadConfig(Configuration::Voice, "./cmu_arctic_slt/voice.json").getCommandList();
    commands->executeAll();
    commands->clearErrorState();
    std::string name=commands->getUttTypeNames().begin()->c_str();
    EXPECT_EQ(name, "text");
    delete s;
    delete commands;
    delete builder;
}

TEST(Command, getutterancefail){
    Speect* s=new Speect();
    CommandList::CommandBuilder* builder=new CommandList::CommandBuilder(s);
    std::list<std::string> l;
    l.push_back("Tokenize");
    CommandList* cmdl=builder->WithProcessors(l).getCommandList();
    cmdl->executeAll();
    EXPECT_EQ(*(cmdl->getErrorState().begin()), "Failure: Utterance not Initialized Operation status:No error");
    delete s;
    delete builder;
}

TEST(Command, getutterancefailurewithaudio){
    Speect* s=new Speect();
    CommandList::CommandBuilder* builder=new CommandList::CommandBuilder(s);
    std::list<std::string> l;
    l.push_back("Tokenize");
    CommandList* cmdl=builder->SaveAudio("nome.wav").getCommandList();
    cmdl->executeAll();
    EXPECT_EQ(*(++cmdl->getErrorState().begin()), "Generating audio to File:nome.wav  Failed: Utterance is not initialized");
    delete s;
    delete builder;
}
