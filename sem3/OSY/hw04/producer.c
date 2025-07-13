#include "producer.h"

void* producer_function(void* arg) {
    int ret, num;
    char* text;
    //reading input and performing action
    while ((ret = scanf("%d %ms", &num, &text)) == 2) {
        if (num < 0) {
            free(text);
            break;
        }

        if (!add_node(num, text)) {
            free(text);
            return (void*)2;
        }
    }
    //increasing the semaphore value to allow consumers to finish their work
    for (int i = 0; i < num_of_cons; i++) {
        sem_post(&semaphore);
    }
    //checking if some input was incorrect
    if (ret != EOF) {
        fprintf(stderr, "Error: Wrong input!\n");
        return (void*)1;
    }

    return NULL;
}
