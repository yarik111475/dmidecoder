#include <vector>
#include <iostream>
#include <QJsonObject>
#include <QJsonDocument>

#include "dmi/Decoder.h"
#include "dmi/Structure.h"

int main(int argc,char* argv[]){
    Decoder dmi_decoder{};
    const std::vector<std::pair<QString,QJsonObject>>& dmi_list {dmi_decoder.decode_information()};
    if(!dmi_list.empty()){
        for(const std::pair<QString,QJsonObject>& dmi: dmi_list){
            if(!dmi.second.isEmpty()){
                std::cout<<QJsonDocument(dmi.second).toJson().toStdString();
            }
        }
    }
    else{
        if(!dmi_decoder.error().empty()){
            std::cerr<<dmi_decoder.error()<<std::endl;
            //std::getchar();
            return EXIT_FAILURE;
        }
    }
    //std::getchar();
    return EXIT_SUCCESS;
}
