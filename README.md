## Задача

Спроектировать и реализовать класс для парсинга аргументов командной строки.

## Тесты

В качестве тестового фреймворка используется [GoogleTest](https://google.github.io/googletest/). Каждый тест представляет из себя функцию, в рамках которой проверяются некоторые условия за счет [assert'ов](https://google.github.io/googletest/reference/assertions.html).  Предложенные тесты используют только два различных assert'a:

    - ASSERT_TRUE  - проверяет, что выражение является истинным (в противном случае тест неуспешен)
    - ASSERT_EQ    - проверяет, что аргументы эквивалентны

Например, тест

```cpp
TEST(ArgParserTestSuite, StringTest) {
    ArgParser parser("My Parser");
    parser.AddStringArgument("param1");

    ASSERT_TRUE(parser.Parse(SplitString("app --param1=value1")));
    ASSERT_EQ(parser.GetStringValue("param1"), "value1");
}
```

Проверяет, что

 - Вызов `parser.Parse(SplitString("app --param1=value1"))` вернет `true`
 - Вызов `parser.GetStringValue("param1")` вернет `"value1"`

## Реализация

Реализация должна находится в библиотеке [argparser](lib/CMakeLists.txt). Изначально в библиотеке есть один класс, при необходимости добавляйте новые файлы, классы, функции и т.д. в библиотеку.

### Примеры запуска

Пример программы с использованием парсера находится в [bin](bin/main.cpp). Программа умеет складывать или умножать переданные ей аргументы.

*labwork4 --sum 1 2 3 4 5*

*labwork4 --mult 1 2 3 4 5*

