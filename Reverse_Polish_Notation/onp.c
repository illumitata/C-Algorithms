/*
 Transform the algebraic expression with brackets into RPN form
 (Reverse Polish Notation). Two-argument operators: +, -, *, /, ^
 (priority from the lowest to the highest), brackets ( ). Operands:
 only letters: a,b,...,z. Assume that there is only one RPN form
 (no expressions like a*b*c). Text grouped in [ ] does not appear
 in the input file. All input is fully parenthesised format (as in examples):
 3
 (a+(b*c))
 ((a+b)*(z+x))
 ((a+t)*((b+(a+c))^(c+d)))

 @illumitata 2018
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Stack {
  int top;
  unsigned capacity;
  int* array;
};

struct Stack* createStack(unsigned capacity) {
  struct Stack* stack = (struct Stack*) calloc(1, sizeof(struct Stack));
  stack->capacity = capacity;
  stack->top = -1;
  stack->array = (int*) calloc(stack->capacity, sizeof(int));
  return stack;
}

int is_full(struct Stack* stack) {
  return stack->top == stack->capacity - 1;
}

int is_empty(struct Stack* stack) {
  return stack->top == -1;
}

void push(struct Stack* stack, int item) {
  if (is_full(stack))
    return;
  stack->array[++stack->top] = item;
}

int pop(struct Stack* stack) {
  if (is_empty(stack))
      return 0;
  return stack->array[stack->top--];
}

char* get_line() {

  char *line = malloc(sizeof(char) * 400);
  char *linep = line;
  size_t lenmax = 400;
  size_t len = lenmax;
  int c;

  if(line == NULL)
    return NULL;

  while(1) {
      c = fgetc(stdin);
      if(c == EOF)
        break;

      if(--len == 0) {
        len = lenmax;
        char * linen = realloc(linep, lenmax *= 2);

        if(linen == NULL) {
            free(linep);
            return NULL;
        }
        line = linen + (line - linep);
        linep = linen;
      }

      if((*line++ = c) == '\n')
        break;
  }

  *line = '\0';
  return linep;
}

char* convert_expression(char* input) {
  // should be alright
  char *expression = malloc(500 * sizeof(char));
  int i = 0;
  int k = 0;
  int bin = 0;
  struct Stack* stack = createStack(400);

  while(*(input + i) != '\0') {
    // if char is letter or new line push it
    if(*(input + i) >= 97 && *(input + i) <= 122) {
      *(expression + k) = *(input + i);
      k++;
    }
    // + - * / ^
    if(*(input + i) == 43 || \
       *(input + i) == 45 || \
       *(input + i) == 42 || \
       *(input + i) == 47 || \
       *(input + i) == 94) {
         while((stack->array[stack->top]) != 40 && stack->top != -1) {
           *(expression + k) = pop(stack);
           k++;
         }
         push(stack, *(input + i));
       }
    if(*(input + i) == 40) {
      push(stack, *(input + i));
    }
    if(*(input + i) == 41) {
      while((stack->array[stack->top]) != 40 && stack->top != -1) {
        *(expression + k) = pop(stack);
        k++;
      }
      // pop the left bracket
      bin = pop(stack);
    }
    // next char
    i++;
  }

  while(stack->top != -1) {
    *(expression + k) = pop(stack);
    k++;
  }

  *(expression + k) = '\n';

  return expression;
}

int main() {

  int t;
  scanf("%d\n", &t);

  char *input = calloc(400, sizeof(char));
  char *output = calloc(400, sizeof(char));

  while(t > 0) {
    input = get_line();
    output = convert_expression(input);
    printf("%s", output);
    t--;
  }

  free(input);
  free(output);

  return 0;
}
