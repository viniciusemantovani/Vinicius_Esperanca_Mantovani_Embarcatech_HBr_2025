#ifndef DISPLAY_TASK_H
#define DISPLAY_TASK_H

#define MAX_TIME_UPDATE_DISPLAY 1000000

void write_in_display(uint32_t x, uint32_t y, uint32_t scale, const char *s);

void draw_line_in_display(int32_t x1, int32_t y1, int32_t x2, int32_t y2);

void draw_empty_square_in_display(uint32_t x, uint32_t y, uint32_t width, uint32_t height);

void time_in_display();

void time_stop();

void clear_display();

void display_task(void *params);

#endif