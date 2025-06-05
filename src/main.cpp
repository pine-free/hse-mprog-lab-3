#include <stdexcept>

class Generator {
protected:
  typedef unsigned long long ull;

public:
  ull generate() {
    throw std::logic_error("Generation function not implemented");
  }
};

/// Модификация метода срединных произведений. После взятия произведения будем
/// возводить полученное число в квадрат
class MiddleMulSquare : public Generator {};

/// Модификация метода перемешивания. Вместо суммы чисел, будем брать квадрат
/// суммы
class ShuffleSquare : public Generator {};

/// Модификация линейного конгруентного метода. Добавляем ещё одно слагаемое,
/// формула принимает вид r_{i + 1} = (l * r_i^2 + k * r_i + b) mod M,
/// где M выбирается вместе с k
class SquareCongruentGenerator : public Generator {};
