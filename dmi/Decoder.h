#ifndef DECODER_H
#define DECODER_H

#include <vector>
#include <string>
#include <QtCore>
#include <QJsonObject>
#include "Entry.h"
#include "Structure.h"

class Decoder
{
private:
    std::string error_str_ {};
    //const std::string entry_path_ {"/home/yaroslav/dmi_tables/centos/smbios_entry_point"};
    //const std::string table_path_ {"/home/yaroslav/dmi_tables/centos/DMI"};
    const std::string entry_path_ {"/sys/firmware/dmi/tables/smbios_entry_point"};
    const std::string table_path_ {"/sys/firmware/dmi/tables/DMI"};
    std::vector<std::string> anchors_ {};
    bool checksum(const std::vector<char> &data);

    Entry t_point_;
    Structure t_structure_;
    std::vector<Structure> structure_list_ {};
    std::vector<std::pair<QString,QJsonObject>> dmi_list_{};

    bool decode_entry();
    std::vector<Structure> decode_table();
    QJsonObject decode_structure(const Structure& dmi, int type);

public:
    explicit Decoder(){
        //fill predefined anchors
        anchors_.push_back("_SM_");
        anchors_.push_back("_SM3_");
    };
    ~Decoder()=default;
    inline std::string error()const{
        return error_str_;
    } 
    std::vector<std::pair<QString,QJsonObject>> decode_information();

private:
    //Type 0
    QJsonObject bios_information(const Structure& dmi);

    //Type 1
    QJsonObject system_information(const Structure& dmi);

    //Type 2
    QJsonObject baseboard_information(const Structure& dmi);

    //Type 3
    QJsonObject chassis_information(const Structure& dmi);

    //Type 4
    QJsonObject processor_information(const Structure& dmi);

    //Type 5, Obsolete
    QJsonObject memory_controller_information(const Structure& dmi);

    //Type 6, Obsolete
    QJsonObject memory_module_information(const Structure& dmi);

    //Type 7
    QJsonObject cache_information(const Structure& dmi);

    //Type 8
    QJsonObject port_connector_information(const Structure& dmi);

    //Type 9
    QJsonObject system_slot_information(const Structure& dmi);

    //Type 10
    QJsonObject onboard_device_information(const Structure& dmi);

    //Type 11
    QJsonObject oem_strings(const Structure& dmi);

    //Type 12
    QJsonObject system_configuration_options(const Structure& dmi);

    //Type 13
    QJsonObject bios_language_information(const Structure& dmi);

    //for decode additional structures with associations
    void group_associations(const Structure& dmi);

    //Type 16
    QJsonObject physical_memory_array(const Structure& dmi);

    //Type 17
    QJsonObject memory_device(const Structure& dmi);

    //Type 18
    QJsonObject memory_error_information(const Structure& dmi);

    //Type 21
    QJsonObject builtin_pointing_device(const Structure& dmi);

    //Type 22
    QJsonObject portable_battery(const Structure& dmi);

    //Type 26
    QJsonObject voltage_probe(const Structure& dmi);

    //Type 27
    QJsonObject cooling_device(const Structure& dmi);

    //Type 28
    QJsonObject temperature_probe(const Structure& dmi);

    //Type 29
    QJsonObject electrical_current_probe(const Structure& dmi);

    //Type 34
    QJsonObject management_device_information(const Structure& dmi);

    //Type 41, Obsolete
    QJsonObject onboard_device_extended_information(const Structure& dmi);

    //Type 44
    QJsonObject processor_additional_information(const Structure& dmi);
};

#endif // DECODER_H
