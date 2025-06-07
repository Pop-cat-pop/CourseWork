#ifndef PARSER_HPP
#define PARSER_HPP

#include <cstdlib>  // Для atof()
#include <cstring>  // Для strncmp()
#include <cmath>    // Для NAN

class Formatter
{
public:
  static Formatter& Instance()
  {
    static Formatter inst;
    return inst;
  }

  // Основной метод для парсинга строки в float (формат XX.XX)
  float ParseFloat(const char* str)
  {
    if (str == nullptr || strlen(str) == 0) {
      return NAN;  // Возвращаем "не число" при ошибке
    }

    // Пропускаем начальные пробелы
    while (*str == ' ') str++;

    // Проверяем специальные случаи (например, команды)
    if (strncmp(str, "T=", 2) == 0) {
      return atof(str + 2);  // Парсим значение после "T="
    }
    else if (strncmp(str, "V=", 2) == 0) {
      return atof(str + 2);  // Парсим значение после "V="
    }

    // Стандартный парсинг числа
    return atof(str);
  }

  // Альтернативный метод с проверкой успешности парсинга
  bool TryParse(const char* str, float& result)
  {
    result = ParseFloat(str);
    return !std::isnan(result);
  }

private:
  Formatter() = default;  // Приватный конструктор для Singleton
  ~Formatter() = default;
};

#endif