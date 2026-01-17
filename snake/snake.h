
typedef struct SnakeNode {
  int x;
  int y;
  SnakeNode *next;
} SnakeNode;

enum Operation { MoveLeft, MoveRight, MoveUp, MoveDown , Quit , Restart , Pause };

enum Direction { UP, DOWN, LEFT, RIGHT };

void snake();

void init_snake(SnakeNode *head, const int startX, const int startY,
                const int size = 1);
void moves_snake(SnakeNode *head, const Direction direction);
void grow_snake(SnakeNode *head, const int size = 1);
void free_snake(SnakeNode *head);