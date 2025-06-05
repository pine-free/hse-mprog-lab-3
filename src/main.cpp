#include <stdexcept>
#include <iostream>
#include <cstdlib>

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

template <class G> void test_generator(G generator, int count) {
  for (int i = 0; i < count; ++i) {
    std::cout << generator.generate() << std::endl;
  }
}

void print_usage(char* argv[]) {
    std::cout << "USAGE: " << argv[0] << " GENERATOR COUNT\n";
    std::cout << "GENERATOR options:\n"
              << "0 - middle multiply square\n"
              << "1 - shuffle square\n"
              << "2 - square congruent generator\n";
  
}

int main(int argc, char* argv[]) {

  if (argc != 3) {
    print_usage(argv);
    return 1;
  }

  int gen_num = std::atoi(argv[1]);
  int gen_count = std::atoi(argv[2]);

  if (gen_num < 0 || gen_num > 3) {
    print_usage(argv);
    return 1;
  }

  if (gen_num == 0) {
    auto gen = MiddleMulSquare();
    test_generator(gen, gen_count);
  } else if (gen_num == 1) {
    auto gen = ShuffleSquare();
    test_generator(gen, gen_count);
  } else {
    auto gen = SquareCongruentGenerator();
    test_generator(gen, gen_count);
  }
}
