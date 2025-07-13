#include "utils.h"

int find_string_in_array(const char** array, int length, char* what) {
    for (int i = 0; i < length; i++) {
        if (strcmp(array[i], what) == 0) {
            return i;
        }
    }
    return -1;
}

bool check_eof() {
    pthread_mutex_lock(&var_mutex);
    bool ret = eof;
    pthread_mutex_unlock(&var_mutex);

    return ret;
}

bool check_end(worker_t* worker) {
    bool ret = false;

    pthread_mutex_lock(&workers_list_mutex);
    if (worker) {
        ret = worker->end;
    }
    pthread_mutex_unlock(&workers_list_mutex);

    return ret;
}

int check_num_of_workers() {
    int ret = 0;
    pthread_mutex_lock(&var_mutex);
    for (int i  = 0; i < 7; i++) {
        ret += num_of_workers[i];
    }
    pthread_mutex_unlock(&var_mutex);

    return ret;
}