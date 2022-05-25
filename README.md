# ReplacingTemplates
The program replaces templates in files.

## The program searches and replacement of templates for provided values.

The program makes the following:

- Collects a list of files, directories and all subdirectories.

- In each of the files, it changes all occurrences of the template to the replacement text.

- It works in several threads.

- Upon completion, it informs the user that the work is done.

The program receives settings from the configuration file - config.txt, located in the root catalog.

The configuration file of the program contains the following entries:

1. The number of files for file processing.

2. The address of the root directory with files and directories.

3. Listing templates and their replacements (unlimited number).

_For example, "<%COLOR%>" is a template, "BLACK" is a replacement. In all files, the template will change to the replacement text after the program is running._

**Listing templates and their replacements is not checked by the program for correctness!**

---

## Программа осуществляет поиск и замену данных в шаблонах.

Программа делает следующее:

- Парсит каталог файлов/папок произвольной вложенности.

- В каждом из файлов меняет все вхождения шаблона на текст замены.

- Работает в несколько потоков.

- По завершению сообщает пользователю, что работа выполнена.

Программа получает настройки из конфигурационного файла - config.txt, расположенного в корневом каталоге.

Конфигурационный файл программы содержит следующие данные:

1. Количество потоков на парсинг файлов.

2. Адрес корневой директории с файлами и папками.

3. Перечисление шаблонов и их замен (неограниченное количество).

_Например, "<%COLOR%>" - шаблон, "BLACK" - замена. Во всех файлах шаблон изменится на текст замены после работы программы._

**Перечисление шаблонов и их замен не проверяется программой на корректность данных!**
