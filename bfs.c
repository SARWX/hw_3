#include <stdio.h>
#include <stdlib.h>

// Структура вершины
struct vertex
{
    char name[20];
    int* neighbors;
};


int pop (int *arr, int end) {
    int x = arr[0];
    arr[0] = 0;
    for (int i = 0; i < end; i++){
            arr[i] = arr[(i+1)];
    }
    return (x);
}

int is_x_uniqe(int x, int *arr, int N) {
    for (int i = 0; i < N; i++) {
            if (arr[i] == x)
                return (0);
    }
    return (1);
}

/*int add_neighbors(int *queue, int *neighbors, int end, int sear, int *searched, int size) {
    for (int i = 0; i < size; i++) {
        if (neighbors[i] != 0) {
            if (is_x_uniqe((i+1), searched, sear)) {
                queue[end++] = (i+1);
            }
        }
    }
    return (end);
}
*/

int bfs(struct vertex *matrix, int start, char *name, int size) {
    start += 1;
    int *queue = calloc((size + 1), sizeof(int));
    int *searched = calloc(size, sizeof(int));
    int end = 0, sear = 0;    // end указывает на последний эл. + 1

    queue[end++] += start;
    while (queue[0] != 0) {
        int x = pop(queue, end--);// Достаем из очереди первый эллемент и двигаем очередь
        printf ("%s = %s\n", matrix[(x-1)].name, name);
        if (*matrix[(x-1)].name == *name)
            return ((x-1));     // Нашли индекс искомого имени
        searched[sear++] = x;   // X проверен
        for (int i = 0; i < size; i++) {
            if (matrix[(x-1)].neighbors[i] != 0) {
                if (is_x_uniqe((i+1), searched, sear)) {
                    queue[end++] = (i+1);
                }
            }
        }

        printf("\nqueue : ");
        for (int i = 0; i < size; i++)
            printf("%d, ", queue[i]);
        printf ("\nsearched : ");
            for (int i = 0; i < size; i++)
        printf("%d, ", searched[i]);
    }
    return (-4); // Не нашли
}

int main() {
    // Заполняем матрицу смежности
    int N;
    printf("\nInput the number of your vertices: ");
    scanf("%d", &N);
    printf("%d", N);    //rm



    struct vertex *matrix;      // Объявили указатель на структуру
    matrix = (struct vertex *) calloc(N, (sizeof(struct vertex) ) );
    if(!matrix) {
        printf ("Allocation failure.");
        exit (1);
    }

    printf("\nInput names of yours vertices via Enter: \n");
    for (int i = 0; i < N; i++) {
        scanf("%s", matrix[i].name);
        matrix[i].neighbors = (int*) calloc(N, sizeof(int));
            if(!matrix[i].neighbors) {
                printf ("Allocation failure.");
                exit (1);
        }
    }
    printf("\t ");
    for (int i = 0; i < N; i++) {
        printf("%s\t", matrix[i].name);
    }
    printf("\n");
    for (int i = 0; i < N; i++) {
        printf("%s\t|", matrix[i].name);
        for (int j = 0; j < N; j++) {
                        getchar();
        int x = (getchar() - '0');
            matrix[i].neighbors[j] = x;
        }
    }
    // Имеем заполненую матрицу
    int *vertices = calloc(N, (sizeof(int) ) ); // создаем список всех верин, все ячейки равны 0
    if(!vertices) {
        printf ("Allocation failure.");
        exit (1);
      }

    FILE *file;
    file = fopen("./graph.gv", "w+t");
    //Пишем в файл
    fprintf(file, "graph HomeWork {\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (!matrix[i].neighbors[j]) // Если 0
                ;
            else {
              vertices[i] = 1;  // Помечаем связные вершины
              vertices[j] = 1;
              fprintf(file, "\t%s -> %s\n", matrix[i].name, matrix[j].name);
            }

        }
    }
    for (int i = 0; i < N; i++) {
      if (vertices[i] == 0)
        fprintf(file, "\t%s\n", matrix[i].name);
    }
    fprintf(file, "}");
    //Закрываем файл
    fclose(file);

    // Сам поиск в ширину :
    printf("\nInput the name :\n");
    char name[20];
    scanf("%s", name);
    printf("\nInput the start point :\n");
    int start = 0;
    scanf("%d", &start);
    printf("%s - %d", name, start);
    int res = bfs(matrix, start, name, N);
    printf ("\n%d\n", res);
    if (res < 0)
        printf("No such name\n");
    else
        printf("%d - is the vertex with the name %s\n", res, name);
   return 0;
}
