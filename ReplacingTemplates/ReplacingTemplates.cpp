// ReplacingTemplates.cpp : программа осуществляет поиск и замену данных в шаблонах
// Программа делает следующее:
// 1) Парсит каталог файлов/папок произвольной вложенности
// 2) В каждом из файлов меняет все вхождения шаблона на текст замены
// 3) Работает в несколько потоков
// 4) По завершению сообщает пользователю, что работа выполнена
// Конфигурационный файл программы содержит следующие данные:
// 1) Количество потоков на парсинг файлов
// 2) Адрес корневой директории с файлами и папками
// 3) Перечисление шаблонов и их замен (неограниченное количество)
// Например, "<%COLOR%>" - шаблон, "BLACK" - замена. Во всех файлах шаблон изменится на текст замены после работы программы
// Перечисление шаблонов и их замен не проверяется программой на корректность данных!

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <mutex>
#include <filesystem>
#include <vector>
#include <regex>



// Адрес конфигурационного файла
const char* g_configFile = "config.txt";
// Псевдоним типа строки с адресом файла для замены
using pathString = std::u8string;

// Мютексы
std::mutex stdOutMtx; // для работы с std::cout
std::mutex pathMtx;   // для работы со списком файлов - std::vector<pathString> filesName;


// Выводит информацию в консоль
void printInfo(const std::string & strInfo)
{
    stdOutMtx.lock();
    std::cout << strInfo << std::endl;
    stdOutMtx.unlock();
}

// Получает настройки из конфигурационного файла
// directoryName, replaceValue - параметры вывода
short getConfig(std::string& directoryName, std::map<std::string, std::string>& replaceValue)
{
    std::ifstream in(g_configFile);
    if (!in.is_open())
    {
        printInfo("ERROR: Failed to open config file!");

        return -1;
    }

    short countThread;
    in >> countThread;
    if (in.fail() || (countThread < 1))
    {
        printInfo("ERROR: Incorrect number of threads.");
        return -1;
    }
    in.ignore(32767, '\n');

    std::getline(in, directoryName);
    if (in.fail())
    {
        printInfo("ERROR: There is no directory in the config file.");
        return -1;
    }

    while (!in.eof())
    {
        std::string templateStr;
        std::string valueStr;

        in >> templateStr >> valueStr;

        if (templateStr != "")
            replaceValue[templateStr] = valueStr;
    }

    in.close();
    return countThread;
}

// Рекурсивно обходит директорию и получает адреса всех файлов
// filePath - параметр вывода
void getFiles(const std::string& directoryName, std::vector<pathString>& filePath)
{
    std::filesystem::path catalog(directoryName);
    for (const auto& element : std::filesystem::recursive_directory_iterator(catalog))
    {
        std::filesystem::path file = element.path();

        // Если отсутствует расширение, считаем каталогом, а не файлом
        if (file.extension() != "")
        {
            filePath.push_back(file.u8string());
        }
    }
}

// Считывает содержимое файла в переменную
// textFile - параметр вывода
bool readFile(const pathString& fileName, std::string& textFile)
{
    std::ifstream in(fileName);
    if (!in.is_open())
    {
        printInfo("ERROR: Failed to open inFile.");

        return false;
    }

    std::string str;
    // Чтобы избежать увеличения количества пустых строк в файле
    std::getline(in, str);

    while (!in.eof())
    {
        textFile += (str + '\n');
        std::getline(in, str);
    }
    textFile += str;

    in.close();
    return true;
}

// Заменяет подстроки в файле соответствующие шаблонам
bool replacement(std::string& textFile, const std::map<std::string, std::string>& replaceValue)
{
    bool result(false); // замен не было

    for (const auto& element : replaceValue)
    {
        std::regex pattern(element.first);
        if (std::regex_search(textFile, pattern))
        {
            textFile = std::regex_replace(textFile, pattern, element.second);

            result = true; // есть замена
        }
    }

    return result;
}

// Перезаписывает файл
bool rewriteFile(const pathString& fileName, std::string& textFile)
{
    std::ofstream out(fileName);
    if (!out.is_open())
    {
        printInfo("ERROR: Failed to open outFile.");

        return false;
    }

    out << textFile;
    out.close();
    return true;
}

// Заменяет значения в файлах, очищая список файлов для обработки
void changeValue(std::vector<pathString>& filesName, const std::map<std::string, std::string>& replaceValue)
{
    // Работает пока не закончатся файлы
    while (!filesName.empty())
    {
        pathMtx.lock();
        pathString file = filesName.back();
        // Файл ушёл в обработку, удаляем его из списка ожидания
        filesName.pop_back();
        pathMtx.unlock();

        std::string textFile;

        if (!readFile(file, textFile))
            continue;

        // Если есть замены, перезаписываем файл
        if (replacement(textFile, replaceValue))
            rewriteFile(file, textFile);
    }
}


int main()
{
    std::cout << "The program is running.\n";

    // Получаем настройки
    std::string directoryName;
    std::map<std::string, std::string> replaceValue;
    short countThread = getConfig(directoryName, replaceValue);
    if (countThread < 1)
    {
        std::cin.get();
        return -1;
    }

    // Проверка валидности адреса каталога
    if (!std::filesystem::exists(directoryName))
    {
        printInfo("ERROR: The directory does not exist.");

        std::cin.get();
        return -1;
    }

    // Проверка предоставления шаблонов
    if (replaceValue.empty())
    {
        printInfo("ERROR: There are no values for replacement.");

        std::cin.get();
        return -1;
    }

    // Получаем адреса всех файлов в каталоге
    std::vector<pathString> filesName;
    getFiles(directoryName, filesName);



    return 0;
}
