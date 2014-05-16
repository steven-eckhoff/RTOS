#ifndef BOARD_H
#define BOARD_H


void board_init(void);

void board_launch(unsigned long slice);

unsigned long *stack_init(unsigned long *sp, void(*task)(void));

#endif // BOARD_H
