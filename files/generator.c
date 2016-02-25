#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

typedef struct {
  uint64_t a, b;
} FibonacciGenerator;

static void
fibonacci_generator_init (FibonacciGenerator *gen)
{
  *gen = (FibonacciGenerator) { .a = 1, .b = 1 };
}

static uint64_t
fibonacci_generator_next (FibonacciGenerator *gen)
{
  uint64_t a = gen->a, b = gen->b;
  gen->a = b;
  gen->b = a + b;
  return a;
}



int
main (void)
{
  FibonacciGenerator g;
  fibonacci_generator_init (&g);

  while (1) {
    printf ("%" PRIu64 "\n", fibonacci_generator_next (&g));
  }
}
