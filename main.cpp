#include <iostream>
#include <fstream>
#include <sstream>
#include <nlohmann/json.hpp>

using ordered_json = nlohmann::ordered_json;

void cmakePresets(){
    // Создаем JSON объект и заполняем его данными
    ordered_json jsonObject;

    jsonObject["version"] = 2;
    jsonObject["configurePresets"] = ordered_json::array({
        {
            {"name", "vcpkg"},
            {"generator", "Ninja"},
            {"binaryDir", "${sourceDir}/build"},
            {"cacheVariables", {
                {"CMAKE_TOOLCHAIN_FILE", "$env{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"}
            }}
        }
    });

    std::ofstream file("CmakePresets.json");
    if(file.is_open()){
        file << jsonObject.dump(4);
        file.close();
        std::cout << "File CMakePresets.json complete!" << std::endl;
    } else {
        std::cerr << "CMakePresets error" << std::endl;
    }
}

void cmakeUserPresets(){
    // Создаем JSON объект и заполняем его данными
    ordered_json jsonObject;

    jsonObject["version"] = 2;
    jsonObject["configurePresets"] = ordered_json::array({
        {
            {"name", "default"},
            {"inherits", "vcpkg"},
            {"environment", {
                {"VCPKG_ROOT", "C:/Users/vadla/vcpkg"}
            }}
        }
    });

    std::ofstream file("CmakeUserPresets.json");
    if(file.is_open()){
        file << jsonObject.dump(4);
        file.close();
        std::cout << "File CMakeUserPresets.json complete!" << std::endl;
    } else {
        std::cerr << "CMakeUserPresets error" << std::endl;
    }
}

void vcpkgConf(){
    ordered_json jsonObject;
    // Заполняем поле "default-registry"
    jsonObject["default-registry"] = {
        {"kind", "git"},
        {"baseline", "cff6ed45719c0162fa7065fdac90506a0add812c"},
        {"repository", "https://github.com/microsoft/vcpkg"}
    };

    // Заполняем массив "registries"
    jsonObject["registries"] = ordered_json::array({
        {
            {"kind", "artifact"},
            {"location", "https://github.com/microsoft/vcpkg-ce-catalog/archive/refs/heads/main.zip"},
            {"name", "microsoft"}
        }
    });

    std::ofstream file("vcpkg-configuration.json");
    if(file.is_open()){
        file <<jsonObject.dump(4);
        file.close();
        std::cout << "File vcpkg-configuration.json complete!" << std::endl;
    } else {
        std::cerr << "vcpkg-configuration error" << std::endl;
    }
}

void vcpkg(std::vector<std::string> libraries){
    ordered_json jsonObject;
    jsonObject["dependencies"] = ordered_json::array({
        libraries
    });

    std::ofstream file("vcpkg.json");
    if(file.is_open()){
        file << jsonObject.dump(4);
        file.close();
        std::cout << "File vcpkg.json complete!" << std::endl;
    } else {
        std::cerr << "vcpkg error" << std::endl;
    }
}

void createJson() {
    std::string input;
    std::vector<std::string> libraries;

    std::cout << "Input library names separated by spaces, then press Enter: " << std::endl;
    std::getline(std::cin, input);

    // Разбиваем строку на отдельные библиотеки
    std::istringstream stream(input);
    std::string library;
    while (stream >> library) {
        libraries.push_back(library);
    }

    // Вызываем методы для создания файлов
    cmakePresets();
    cmakeUserPresets();
    vcpkgConf();
    vcpkg(libraries);

    system("pause");
}
int main(){
    createJson();
}