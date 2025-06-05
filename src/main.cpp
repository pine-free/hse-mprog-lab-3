#include <climits>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

#define quit_if(condition)                                                     \
  if (condition) {                                                             \
    print_usage(argv);                                                         \
    return 1;                                                                  \
  }

class Generator {
public:
  uint32_t generate() {
    throw std::logic_error("Generation function not implemented");
  }
};

/// Модификация метода срединных произведений. После взятия произведения будем
/// возводить полученное число в квадрат
class MiddleMulSquare : public Generator {
  uint32_t r0, r1;

  uint32_t get_num(uint32_t _r0, uint32_t _r1) {
    uint64_t tmp = std::pow(r0 * r1, 2);
    uint32_t res = (tmp >> 16) & 0xffffffff;
    // std::cout << _r0 << " " << _r1 << " " << res << std::endl;
    return res;
  }

public:
  MiddleMulSquare(uint32_t r0, uint32_t r1) : r0(r0), r1(r1) {}

  uint32_t generate() {
    uint32_t res = 0;
    uint32_t offset = 0;
    while (res == 0) {
      res = get_num(r0 + offset++, r1);
      if (res == 0) {
        // 2 is basically a magic constant figured out through trial and error here.
        // This prevents the generator devolving into zeroes... Hopefully
        res = r0 - 2;
      }
    }
    r0 = r1;
    r1 = res;
    return res;
  }
};

/// Модификация метода перемешивания. Вместо суммы чисел, будем брать квадрат
/// суммы
class ShuffleSquare : public Generator {};

/// Модификация линейного конгруентного метода. Добавляем ещё одно слагаемое,
/// формула принимает вид r_{i + 1} = (l * r_i^2 + k * r_i + b) mod M,
/// где M выбирается вместе с k
class SquareCongruentGenerator : public Generator {};

template <class G> void test_generator(G generator, int count) {
  for (int i = 0; i < count; ++i) {
    auto res = generator.generate();
    std::cout << res << std::endl;
    if (res == 0) {
      break;
    }
  }
}

void print_usage(char *argv[]) {
  std::cout << "USAGE: " << argv[0] << " GENERATOR COUNT <OPTIONS>\n";
  std::cout << "GENERATOR options:\n"
            << "0 - middle multiply square\n"
            << "1 - shuffle square\n"
            << "2 - square congruent generator\n";
  std::cout << "OPTIONS are specific seeds for the generator\n";
}

int main(int argc, char *argv[]) {

  quit_if(argc < 3);

  int gen_num = std::atoi(argv[1]);
  int gen_count = std::atoi(argv[2]);

  quit_if(gen_num < 0 || gen_num > 3);

  if (gen_num == 0) {
    quit_if(argc != 5);
    uint32_t r0 = std::atoi(argv[3]), r1 = std::atoi(argv[4]);
    auto gen = MiddleMulSquare(r0, r1);
    test_generator(gen, gen_count);
  } else if (gen_num == 1) {
    auto gen = ShuffleSquare();
    test_generator(gen, gen_count);
  } else {
    auto gen = SquareCongruentGenerator();
    test_generator(gen, gen_count);
  }
}
