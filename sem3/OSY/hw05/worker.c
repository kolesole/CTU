#include "worker.h"

void* worker_function(void* arg) {
    worker_t* worker = (worker_t*)arg;

    while (1) {
        pthread_mutex_lock(&work_mutex);

        //wait until there is work available, a place available, or termination conditions are met
        while ((!is_available_work(worker) || !is_available_place(worker)) && !check_end(worker) && !check_eof()) {
            pthread_cond_wait(&work_cond, &work_mutex);      //wait for the condition signal
        }

        //check if worker must go home
        if (check_end(worker)) {
            pthread_mutex_lock(&stdout_mutex);
            printf("%s goes home\n", worker->name);
            pthread_mutex_unlock(&stdout_mutex);
            pthread_mutex_unlock(&work_mutex);
            break;
        }

        //check if was received EOF
        if (check_eof()) {
            bool wait = true;
            while ((!is_available_work(worker) || !is_available_place(worker)) && (wait = should_worker_wait(worker->place)) == true) {
                pthread_cond_wait(&work_cond, &work_mutex);     //wait for the condition signal
            }

            //if a worker cannot get a new work, he goes home
            if (!wait) {
                pthread_mutex_lock(&stdout_mutex);
                printf("%s goes home\n", worker->name);
                pthread_mutex_unlock(&stdout_mutex);
                pthread_mutex_unlock(&work_mutex);
                break;
            }
        }

        //taking up place for work and work
        pthread_mutex_lock(&var_mutex);
        ready_places[worker->place]--;
        available_works[worker->place]--;
        pthread_mutex_unlock(&var_mutex);

        pthread_mutex_unlock(&work_mutex);

        get_and_do_work(worker);
    }

    pthread_mutex_lock(&var_mutex);
    num_of_workers[worker->place]--;
    pthread_mutex_unlock(&var_mutex);

    delete_worker(worker);

    return NULL;
}

bool is_available_work(worker_t* worker) {
    pthread_mutex_lock(&var_mutex);
    //check if there is some available work for a worker specialization
    bool ret = available_works[worker->place] > 0;
    pthread_mutex_unlock(&var_mutex);

    return ret;
}

bool is_available_place(worker_t* worker) {
    pthread_mutex_lock(&var_mutex);
    //check if there is some available place for a worker specialization
    bool ret = ready_places[worker->place] > 0;
    pthread_mutex_unlock(&var_mutex);
    return ret;
}

void get_and_do_work(worker_t* worker) {
    //depending on a worker specialization, a function is called from the work.h
    switch (worker->place) {
        case 0:
            get_and_do_work_nuzky(worker->name);
            break;
        case 1:
            get_and_do_work_vrtacka(worker->name);
            break;
        case 2:
            get_and_do_work_ohybacka(worker->name);
            break;
        case 3:
            get_and_do_work_svarecka(worker->name);
            break;
        case 4:
            get_and_do_work_lakovna(worker->name);
            break;
        case 5:
            get_and_do_work_sroubovak(worker->name);
            break;
        case 6:
            get_and_do_work_freza(worker->name);
            break;
        default:
            break;
    }

    pthread_mutex_lock(&var_mutex);
    //return place for work
    ready_places[worker->place]++;
    pthread_mutex_unlock(&var_mutex);

    pthread_cond_broadcast(&work_cond);
}
