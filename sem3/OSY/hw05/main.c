#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "worker.h"
#include "workers_list.h"

enum place {
    NUZKY, VRTACKA, OHYBACKA, SVARECKA, LAKOVNA, SROUBOVAK, FREZA
};

const char* place_str[7] = {
    [NUZKY] = "nuzky",
    [VRTACKA] = "vrtacka",
    [OHYBACKA] = "ohybacka",
    [SVARECKA] = "svarecka",
    [LAKOVNA] = "lakovna",
    [SROUBOVAK] = "sroubovak",
    [FREZA] = "freza",
};

enum product {
    A, B, C,
};

const char* product_str[3] = {
    [A] = "A",
    [B] = "B",
    [C] = "C",
};

const int processes[3][6] = {
    {NUZKY, VRTACKA, OHYBACKA, SVARECKA, VRTACKA, LAKOVNA},            //steps to create product A
    {VRTACKA, NUZKY, FREZA, VRTACKA, LAKOVNA, SROUBOVAK},              //steps to create product B
    {FREZA, VRTACKA, SROUBOVAK, VRTACKA, FREZA, LAKOVNA}               //steps to create product C
};

int num_of_places[7] = {0};                   //global array to save inf. about num. of places
int ready_places[7] = {0};                    //global array to save inf. about num. of free places
int available_works[7] = {0};                 //global array to save inf. about num. of available works
int num_of_workers[7] = {0};                  //global array to save inf. about num. of workers
int parts[3][6] = {0};                        //global array to save inf. about num. of products on every step
int num_of_est_works[3][6] = {0};             //global array to save inf. about num of estimated works

worker_t* workers_head = NULL;                //global workers list head
worker_t* workers_tail = NULL;                //global workers list tail

pthread_mutex_t var_mutex;                    //global mutex to change variables
pthread_mutex_t work_mutex;                   //global mutex for workers
pthread_cond_t work_cond;                     //global condition for workers
pthread_mutex_t stdout_mutex;                 //global mutex to write on stdout
pthread_mutex_t workers_list_mutex;           //global mutex for workers list

bool eof = false;                             //global variable for EOF

int main(int argc, char **argv) {
    int threads_array_size = 10;
    int num_of_threads = 0;
    pthread_t* threads_array = (pthread_t*)malloc(threads_array_size * sizeof(pthread_t));
    if (threads_array == NULL) {
        fprintf(stderr, "Error: Cannot allocate memory for threads_array\n");
        return 1;
    }

    if (pthread_mutex_init(&work_mutex, NULL) != 0) {
        fprintf(stderr, "Error: Failed to initialize mutex!\n");
        free(threads_array);
        return 1;
    }

    if (pthread_cond_init(&work_cond, NULL) != 0) {
        fprintf(stderr, "Error: Failed to initialize condition variable!\n");
        free(threads_array);
        pthread_mutex_destroy(&work_mutex);
        return 1;
    }

    if (pthread_mutex_init(&stdout_mutex, NULL) != 0) {
        fprintf(stderr, "Error: Failed to initialize mutex!\n");
        free(threads_array);
        pthread_mutex_destroy(&work_mutex);
        pthread_cond_destroy(&work_cond);
        return 1;
    }

    if (pthread_mutex_init(&workers_list_mutex, NULL) != 0) {
        fprintf(stderr, "Error: Failed to initialize mutex!\n");
        free(threads_array);
        pthread_mutex_destroy(&work_mutex);
        pthread_cond_destroy(&work_cond);
        pthread_mutex_destroy(&stdout_mutex);
        return 1;
    }

    if (pthread_mutex_init(&var_mutex, NULL) != 0) {
        fprintf(stderr, "Error: Failed to initialize mutex!\n");
        free(threads_array);
        pthread_mutex_destroy(&work_mutex);
        pthread_cond_destroy(&work_cond);
        pthread_mutex_destroy(&stdout_mutex);
        pthread_mutex_destroy(&workers_list_mutex);
        return 1;
    }

    char *line = NULL;
    size_t sz = 0;
    while (1) {
        char *cmd, *arg1, *arg2, *arg3, *saveptr;

        if (getline(&line, &sz, stdin) == -1) {
            break; /* Error or EOF */
        }

        cmd = strtok_r(line, " \r\n", &saveptr);
        arg1 = strtok_r(NULL, " \r\n", &saveptr);
        arg2 = strtok_r(NULL, " \r\n", &saveptr);
        arg3 = strtok_r(NULL, " \r\n", &saveptr);

        if (!cmd) {
            continue; /* Empty line */
        }
        else if (strcmp(cmd, "start") == 0 && arg1 && arg2 && !arg3) {
            int place = find_string_in_array(place_str, 7, arg2);
            if (place == -1) {
                fprintf(stderr, "Error: Invalid place!\n");
                continue;
            }
            if (!add_worker(arg1, place)) {
                fprintf(stderr, "Error: Failed to add worker!\n");
                free(threads_array);
                pthread_mutex_destroy(&work_mutex);
                pthread_cond_destroy(&work_cond);
                pthread_mutex_destroy(&stdout_mutex);
                pthread_mutex_destroy(&workers_list_mutex);
                pthread_mutex_destroy(&var_mutex);
                free_list();
                return 1;
            }

            if (pthread_create(&workers_tail->thread, NULL, worker_function, workers_tail) != 0) {
                fprintf(stderr, "Error: Failed to create worker thread!\n");
                free(threads_array);
                pthread_mutex_destroy(&work_mutex);
                pthread_cond_destroy(&work_cond);
                pthread_mutex_destroy(&stdout_mutex);
                pthread_mutex_destroy(&workers_list_mutex);
                pthread_mutex_destroy(&var_mutex);
                free_list();
                return 1;
            }

            if (threads_array_size == num_of_threads) {
                threads_array_size *= 2;
                pthread_t* tmp = (pthread_t*)realloc(threads_array, threads_array_size * sizeof(pthread_t));
                if (tmp == NULL) {
                    fprintf(stderr, "Error: Cannot reallocate memory for threads_array!\n");
                    pthread_mutex_destroy(&work_mutex);
                    pthread_cond_destroy(&work_cond);
                    pthread_mutex_destroy(&stdout_mutex);
                    pthread_mutex_destroy(&workers_list_mutex);
                    pthread_mutex_destroy(&var_mutex);
                    free_list();
                    free(threads_array);
                    return 1;
                }
                threads_array = tmp;
            }

            threads_array[num_of_threads++] = workers_tail->thread;

            pthread_mutex_lock(&var_mutex);
            num_of_workers[place]++;
            pthread_mutex_unlock(&var_mutex);
        }
        else if (strcmp(cmd, "make") == 0 && arg1 && !arg2) {
            int product = find_string_in_array(product_str, 7, arg1);
            if (product == -1) {
                fprintf(stderr, "Error: Invalid product!\n");
                continue;
            }

            pthread_mutex_lock(&var_mutex);
            switch (product) {
                case A:
                    available_works[0]++;
                    num_of_est_works[0][0]++;
                    parts[0][0]++;
                    break;
                case B:
                    available_works[1]++;
                    num_of_est_works[1][0]++;
                    parts[1][0]++;
                    break;
                case C:
                    available_works[6]++;
                    num_of_est_works[2][0]++;
                    parts[2][0]++;
                    break;
                default:
                    break;
            }
            pthread_mutex_unlock(&var_mutex);

            pthread_cond_broadcast(&work_cond);
        }
        else if (strcmp(cmd, "end") == 0 && arg1 && !arg2) {
            worker_t* worker = find_worker(arg1);
            if (worker == NULL) {
                fprintf(stderr, "Error: Failed to find worker named %s\n", arg1);
            } else {
                pthread_mutex_lock(&workers_list_mutex);
                worker->end = true;
                pthread_mutex_unlock(&workers_list_mutex);
                pthread_cond_broadcast(&work_cond);
            }
        }
        else if (strcmp(cmd, "add") == 0 && arg1 && !arg2) {
            int place = find_string_in_array(place_str, 7, arg1);
            if (place == -1) {
                fprintf(stderr, "Error: Invalid place!\n");
                continue;
            }

            pthread_mutex_lock(&var_mutex);
            num_of_places[place]++;
            ready_places[place]++;
            pthread_mutex_unlock(&var_mutex);

            pthread_cond_broadcast(&work_cond);
        }
        else if (strcmp(cmd, "remove") == 0 && arg1 && !arg2) {
            int place = find_string_in_array(place_str, 7, arg1);
            if (place == -1) {
                fprintf(stderr, "Error: Invalid place!\n");
                continue;
            }

            pthread_mutex_lock(&var_mutex);
            num_of_places[place]--;
            ready_places[place]--;
            pthread_mutex_unlock(&var_mutex);
        } else {
            fprintf(stderr, "Invalid command: %s\n", line);
        }
    }
    free(line);

    pthread_mutex_lock(&var_mutex);
    eof = true;
    pthread_mutex_unlock(&var_mutex);

    pthread_mutex_lock(&work_mutex);
    pthread_cond_broadcast(&work_cond);
    pthread_mutex_unlock(&work_mutex);

    for (int thread_indx = 0; thread_indx < num_of_threads; thread_indx++) {
        pthread_join(threads_array[thread_indx], NULL);
    }

    free(threads_array);

    if (pthread_mutex_destroy(&work_mutex) != 0) {
        fprintf(stderr, "Error: Failed to destroy mutex!\n");
        pthread_cond_destroy(&work_cond);
        pthread_mutex_destroy(&stdout_mutex);
        pthread_mutex_destroy(&var_mutex);
        pthread_mutex_destroy(&workers_list_mutex);
        return 1;
    }

    if (pthread_cond_destroy(&work_cond) != 0) {
        fprintf(stderr, "Error: Failed to destroy condition variable!\n");
        pthread_mutex_destroy(&stdout_mutex);
        pthread_mutex_destroy(&var_mutex);
        pthread_mutex_destroy(&workers_list_mutex);
        return 1;
    }

    if (pthread_mutex_destroy(&stdout_mutex) != 0) {
        fprintf(stderr, "Error: Failed to destroy mutex!\n");
        pthread_mutex_destroy(&var_mutex);
        pthread_mutex_destroy(&workers_list_mutex);
        return 1;
    }

    if (pthread_mutex_destroy(&var_mutex) != 0) {
        fprintf(stderr, "Error: Failed to destroy mutex!\n");
        pthread_mutex_destroy(&workers_list_mutex);
        return 1;
    }

    if (pthread_mutex_destroy(&workers_list_mutex) != 0) {
        fprintf(stderr, "Error: Failed to destroy mutex!\n");
        return 1;
    }

    return 0;
}