using namespace std;
#include <iostream>
#include "pugixml.hpp"
#include <iostream>
#include <sstream>
#include <cstring>
#include <vector>
#include <string>
#include <fstream>
#include <fstream>
#include <algorithm>

// tag::impl[]
std::vector<std::string>FileNames_without_h;
std::vector<std::string>FileNames_update;
std::vector<std::string>FileNames_update_new;
std::vector<std::string>Project_Dir;
std::string included;
std::string macros;
std::vector <std::string>Package_dir;
std::vector<std::string> Package_found;
std::vector<std::string> Name;
int found;
int number_of_lines = 0;
std::string line;
std::ifstream myfile("tree2.xml");
std::vector<std::string> Lines;
int reanumber;
std::string otsitav = "macros=\"DeviceHeaderFile=$";
std::size_t found1;
std::string asendatav1 ="(";
std::string asendatav2 =")";



std::vector<std::string> split(std::string str, char delimiter)
{
    std::vector<std::string> internal;
    std::stringstream ss(str); // Turn the string into a stream.
    std::string tok;

    while(getline(ss, tok, delimiter))
    {
        internal.push_back(tok);
    }

    return internal;
}
struct simple_walker: pugi::xml_tree_walker
{
    std::vector<std::string> FileNames;

    virtual bool for_each(pugi::xml_node& node)
    {

        // for (int i = 0; i < depth(); ++i) outputFile << "  "; // indentation

        //outputFile <<  ": name='" << node.value() << "', value='" << node.value() << "'\n";
        for (pugi::xml_attribute attr=node.first_attribute();attr;attr=attr.next_attribute()) {
            //{outputFile<<attr.name()<<":"<<attr.value()<<"´\n";}
            if (strcmp(attr.name(), "file_name") == 0) {
                std::string nimi1{attr.value()};
                FileNames.push_back(nimi1);
            }
            else if (strcmp(attr.name(), "c_user_include_directories") == 0)
            {
                included=attr.value();
            }
            else if (strcmp(attr.name(), "macros")==0)
            {
                std::string prodir(attr.value());
                Package_dir.push_back(prodir);
            }
            else if (strcmp(attr.name(), "Name")==0)
            {
                std::string project_name(attr.value());
                Name.push_back(project_name);

            }
        }
        return true; // continue traversal
    }
};


int main()
{


    ofstream inputFile;
    inputFile.open ("output1.xml");

    while (std::getline(myfile, line)) {
        ++number_of_lines;
        Lines.push_back(line);
    }

    for (int i = 0; i < Lines.size(); i++) {
        found1 = Lines[i].find(otsitav);
        if (found1 != std::string::npos) {
            reanumber = i;
        }
    }

    std::replace(Lines[reanumber].begin(), Lines[reanumber].end(),'(','{');
    std::replace(Lines[reanumber].begin(), Lines[reanumber].end(),')','}');

    for (int b=0; b<Lines.size();b++)
    {
        inputFile<<Lines[b];

    }


    inputFile.close();

    pugi::xml_document doc;
    if (!doc.load_file("output1.xml")) return -1;
    ofstream outputFile;
    outputFile.open ("Project2.txt");


    // tag::traverse[]
    simple_walker walker;
    doc.traverse(walker);
    // end::traverse[]
    for(int i=0; i<walker.FileNames.size(); ++i)
    {


        if (walker.FileNames[i].substr(walker.FileNames[i].length()-2)!=".h")
        {
            FileNames_without_h.push_back (walker.FileNames[i]);
        }
    }



    for (int j = 0; j<FileNames_without_h.size(); j++)
    {
        if (FileNames_without_h[j].at(0)=='.' && FileNames_without_h[j].at(1)=='.')
        {
            std::string temp = FileNames_without_h[j].substr(2);
            FileNames_update.push_back(temp);
        }
        else {std::string abc= "/"+FileNames_without_h[j];
            Project_Dir.push_back(abc);}


    }

    for (int s = 0; s<FileNames_update.size(); s++)
    {
        if (FileNames_update[s].substr(0,9) == std::string("/nrf-base"))
        {
            std::string temp2 = FileNames_update[s].substr(9);
            FileNames_update_new.push_back(temp2);
        }
        else if (FileNames_update[s].substr(0,5)==std::string("/test"))
        {

        }

        else{FileNames_update_new.push_back(FileNames_update[s]);}


    }

    std::string Package = Package_dir[0];
    std::vector <std::string> Pckage = split(Package,';');

    for (int p=0; p<Pckage.size(); p++)
    {
        found = Pckage[p].find("$");

        if (found!=std::string::npos)
        {
            std::string package_dir= Pckage[p].substr(found);
            Package_found.push_back(package_dir);
        }
    }
    string name = Name[0];

    outputFile<< "Set(PROJECT_NAME "<<name<<")"<<std::endl;
    outputFile<<"set(SDK_ROOT ../nrf-base)"<<std::endl;
    outputFile<<"set(SRC_ROOT ../)"<<std::endl;
    outputFile<<"set(ProjectDir .)"<<std::endl;
    outputFile<<"set(PackagesDir ~/Library/SEGGER/SEGGER\\ Embedded\\ Studio/v3/packages"<<std::endl;
    outputFile<<std::endl<< "set(SRC_FILES:" ;

    for (int p=0; p<Package_found.size();p++)
    {
        outputFile<<Package_found[p]<<std::endl;
    }

    for (int z=0; z<Project_Dir.size();z++)
    {
        outputFile<<"${ProjectDir}";
        outputFile<<Project_Dir[z]<<std::endl;
    }


    for (int k=0; k<FileNames_update_new.size(); k++)
    {
        outputFile<<"${SRC_ROOT}";
        outputFile<<FileNames_update_new[k] <<std::endl;
    }

    outputFile<< ")"<< std::endl<<"set(INC FOLDERS ";

    std::vector <std::string> include = split(included,';');
    for (int l=0; l<include.size(); l++){
        outputFile<<include[l]<<std::endl;

    }

    outputFile<< ")"<<std::endl;

    outputFile<<"set(CFLAGS -Wall -Werror -Wextra  NO_VTOR_CONFIG -DNRF52 -DNRF52832_XXAA -DNRF52_PAN_12 -DNRF52_PAN_15 -DNRF52_PAN_20 -DNRF52_PAN_31 -DNRF52_PAN_36 -DNRF52_PAN_51 -DNRF52_PAN_54 -DNRF52_PAN_55 -DNRF52_PAN_58 -DNRF52_PAN_64 -DNRF52_PAN_74 -DSWI_DISABLE0 -mcpu=cortex-m4 -mthumb -mabi=aapcs -O3 -g3 -mfloat-abi=hard -mfpu=fpv4-sp-d16 -ffunction-sections -fdata-sections -fno-strict-aliasing -fno-builtin --short-enums )"<<std::endl;
    outputFile<<"set(CXXFLAGS -Wall -Werror -Wextra)"<<std::endl;
    outputFile<<"cmake_minimum_required(VERSION 2.4.0)"<<std::endl;
    outputFile<<"project(${PROJECT_NAME})"<<std::endl;
    outputFile<<"list(APPEND CFLAGS \"-undef\" \"-D__GNUC__\")"<<std::endl;
    outputFile<<"list(FILTER CFLAGS EXCLUDE REGEX mcpu)"<<std::endl;
    outputFile<<"string(REPLACE \";\" \" \" CFLAGS \"${CFLAGS}\")"<<std::endl;
    outputFile<<"set(CMAKE_C_FLAGS ${CFLAGS})"<<std::endl;
    outputFile<<"include_directories(${INC_FOLDERS})"<<std::endl;
    outputFile<<"add_executable(${PROJECT_NAME} ${SRC_FILES})"<<std::endl;
    outputFile.close();


}

