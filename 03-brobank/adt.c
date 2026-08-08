#include "adt.h"

void stackInit(Stack *s) { s->top = -1; }
int stackIsEmpty(const Stack *s) { return s->top < 0; }
int stackIsFull(const Stack *s) { return s->top == CAPACITY - 1; }
int stackPush(Stack *s, int value) {
    if (stackIsFull(s)) {
        return 0;
    }
    s->top += 1;
    s->data[s->top] = value;
    return 1;
}
int stackPop(Stack *s, int *value) {
    if (stackIsEmpty(s)) {
        return 0;
    }
    *value = s->data[s->top];
    s->top -= 1;
    return 1;
}

void queueInit(Queue *q) { q->front = 0; q->rear = -1; q->count = 0; }
int queueIsEmpty(const Queue *q) { return q->count == 0; }
int queueIsFull(const Queue *q) { return q->count == CAPACITY; }
int enqueue(Queue *q, int value) {
    if (queueIsFull(q)) return 0;
    q->rear = (q->rear + 1) % CAPACITY;
    q->data[q->rear] = value;
    q->count++;
    return 1;
}
int dequeue(Queue *q, int *value) {
    if (queueIsEmpty(q)) {
        return 0;
    }
    *value = q->data[q->front];
    q->front = (q->front + 1) % CAPACITY;
    q->count -= 1;
    return 1;
}
