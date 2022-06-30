# ReplacingTemplates
The program replaces templates in files.

<p align="center">
   <img src="https://img.shields.io/badge/C%2B%2B-17-blue" alt="C++ Version">
   <img src="https://img.shields.io/badge/version-1.0-yellow" alt="Application Version">
   <img src="https://img.shields.io/badge/license-MIT-red" alt="License">
</p>

## The program searches and replacement of templates for provided values.

### About
The program makes the following:
- Collects a list of files, directories and all subdirectories.
- In each of the files, it changes all occurrences of the template to the replacement text.
- It works multithread.
- Upon completion, it informs the user that the work is done.

### Documentation
The program receives settings from the configuration file - config.txt, located in the root catalog.
The configuration file of the program contains the following entries:
1. The number of threads.
2. The address of the root directory with files and directories.
3. Listing templates and their replacements (unlimited number).

_For example, "<%COLOR%>" is a template, "BLACK" is a replacement. In all files, the template will change to the replacement text after the program is running._

**Listing templates and their replacements is not checked by the program for correctness!**
**Templates must be formed according to the rules of std::regex.**

### Developers

- [Valendovsky](https://github.com/valendovsky)

### License
Project ReplacingTemplates is distributed under the MIT license.

---

## Программа осуществляет поиск и замену шаблонных данных на предоставленные значения.

### О проекте
Программа делает следующее:
- Парсит каталог файлов/папок произвольной вложенности.
- В каждом из файлов меняет все вхождения шаблона на текст замены.
- Работает в несколько потоков.
- По завершению сообщает пользователю, что работа выполнена.

### Документация
Программа получает настройки из конфигурационного файла - config.txt, расположенного в корневом каталоге.
Конфигурационный файл программы содержит следующие данные:
1. Количество потоков на парсинг файлов.
2. Адрес корневой директории с файлами и папками.
3. Перечисление шаблонов и их замен (неограниченное количество).

_Например, "<%COLOR%>" - шаблон, "BLACK" - замена. Во всех файлах шаблон изменится на текст замены после работы программы._

**Перечисление шаблонов и их замен не проверяется программой на корректность данных!**
**Шаблоны необходимо формировать по правилам std::regex.**

### Разработчики

- [Valendovsky](https://github.com/valendovsky)

### Лицензия
Проект ReplacingTemplates распространяется под лицензией MIT.
