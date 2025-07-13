#include "work.h"

void get_and_do_work_nuzky(char* name) {
    pthread_mutex_lock(&var_mutex);
    if (parts[1][1] > 0) {
        pthread_mutex_unlock(&var_mutex);

        pthread_mutex_lock(&var_mutex);
        num_of_est_works[1][2]++;              //adding expected work
        pthread_mutex_unlock(&var_mutex);

        pthread_mutex_lock(&stdout_mutex);
        printf("%s nuzky 2 B\n", name);
        pthread_mutex_unlock(&stdout_mutex);

        pthread_mutex_lock(&var_mutex);
        parts[1][1]--;
        pthread_mutex_unlock(&var_mutex);

        usleep(100000);

        pthread_mutex_lock(&var_mutex);
        num_of_est_works[1][1]--;
        parts[1][2]++;
        available_works[6]++;
        pthread_mutex_unlock(&var_mutex);
    }
    else if (parts[0][0] > 0) {
        pthread_mutex_unlock(&var_mutex);

        pthread_mutex_lock(&var_mutex);
        num_of_est_works[0][1]++;              //adding expected work
        pthread_mutex_unlock(&var_mutex);

        pthread_mutex_lock(&stdout_mutex);
        printf("%s nuzky 1 A\n", name);
        pthread_mutex_unlock(&stdout_mutex);

        pthread_mutex_lock(&var_mutex);
        parts[0][0]--;
        pthread_mutex_unlock(&var_mutex);

        usleep(100000);

        pthread_mutex_lock(&var_mutex);
        num_of_est_works[0][0]--;
        parts[0][1]++;
        available_works[1]++;
        pthread_mutex_unlock(&var_mutex);
    }
}

void get_and_do_work_vrtacka(char* name) {
    pthread_mutex_lock(&var_mutex);
    if (parts[0][4] > 0) {
        pthread_mutex_unlock(&var_mutex);

        pthread_mutex_lock(&var_mutex);
        num_of_est_works[0][5]++;              //adding expected work
        pthread_mutex_unlock(&var_mutex);

        pthread_mutex_lock(&stdout_mutex);
        printf("%s vrtacka 5 A\n", name);
        pthread_mutex_unlock(&stdout_mutex);

        pthread_mutex_lock(&var_mutex);
        parts[0][4]--;
        pthread_mutex_unlock(&var_mutex);

        usleep(200000);

        pthread_mutex_lock(&var_mutex);
        num_of_est_works[0][4]--;
        parts[0][5]++;
        available_works[4]++;
        pthread_mutex_unlock(&var_mutex);
    }
    else if (parts[1][3] > 0) {
        pthread_mutex_unlock(&var_mutex);

        pthread_mutex_lock(&var_mutex);
        num_of_est_works[1][4]++;              //adding expected work
        pthread_mutex_unlock(&var_mutex);

        pthread_mutex_lock(&stdout_mutex);
        printf("%s vrtacka 4 B\n", name);
        pthread_mutex_unlock(&stdout_mutex);

        pthread_mutex_lock(&var_mutex);
        parts[1][3]--;
        pthread_mutex_unlock(&var_mutex);

        usleep(200000);

        pthread_mutex_lock(&var_mutex);
        num_of_est_works[1][3]--;
        parts[1][4]++;
        available_works[4]++;
        pthread_mutex_unlock(&var_mutex);
    }
    else if (parts[2][3] > 0) {
        pthread_mutex_unlock(&var_mutex);

        pthread_mutex_lock(&var_mutex);
        num_of_est_works[2][4]++;              //adding expected work
        pthread_mutex_unlock(&var_mutex);

        pthread_mutex_lock(&stdout_mutex);
        printf("%s vrtacka 4 C\n", name);
        pthread_mutex_unlock(&stdout_mutex);

        pthread_mutex_lock(&var_mutex);
        parts[2][3]--;
        pthread_mutex_unlock(&var_mutex);

        usleep(200000);

        pthread_mutex_lock(&var_mutex);
        num_of_est_works[2][3]--;
        parts[2][4]++;
        available_works[6]++;
        pthread_mutex_unlock(&var_mutex);
    }
    else if (parts[0][1] > 0) {
        pthread_mutex_unlock(&var_mutex);

        pthread_mutex_lock(&var_mutex);
        num_of_est_works[0][2]++;              //adding expected work
        pthread_mutex_unlock(&var_mutex);

        pthread_mutex_lock(&stdout_mutex);
        printf("%s vrtacka 2 A\n", name);
        pthread_mutex_unlock(&stdout_mutex);

        pthread_mutex_lock(&var_mutex);
        parts[0][1]--;
        pthread_mutex_unlock(&var_mutex);

        usleep(200000);

        pthread_mutex_lock(&var_mutex);
        num_of_est_works[0][1]--;
        parts[0][2]++;
        available_works[2]++;
        pthread_mutex_unlock(&var_mutex);
    }
    else if (parts[2][1] > 0) {
        pthread_mutex_unlock(&var_mutex);

        pthread_mutex_lock(&var_mutex);
        num_of_est_works[2][2]++;              //adding expected work
        pthread_mutex_unlock(&var_mutex);

        pthread_mutex_lock(&stdout_mutex);
        printf("%s vrtacka 2 C\n", name);
        pthread_mutex_unlock(&stdout_mutex);

        pthread_mutex_lock(&var_mutex);
        parts[2][1]--;
        pthread_mutex_unlock(&var_mutex);

        usleep(200000);

        pthread_mutex_lock(&var_mutex);
        num_of_est_works[2][1]--;
        parts[2][2]++;
        available_works[5]++;
        pthread_mutex_unlock(&var_mutex);
    }
    else if (parts[1][0] > 0) {
        pthread_mutex_unlock(&var_mutex);

        pthread_mutex_lock(&var_mutex);
        num_of_est_works[1][1]++;              //adding expected work
        pthread_mutex_unlock(&var_mutex);

        pthread_mutex_lock(&stdout_mutex);
        printf("%s vrtacka 1 B\n", name);
        pthread_mutex_unlock(&stdout_mutex);

        pthread_mutex_lock(&var_mutex);
        parts[1][0]--;
        pthread_mutex_unlock(&var_mutex);

        usleep(200000);

        pthread_mutex_lock(&var_mutex);
        num_of_est_works[1][0]--;
        parts[1][1]++;
        available_works[0]++;
        pthread_mutex_unlock(&var_mutex);
    }
}

void get_and_do_work_ohybacka(char* name) {
    pthread_mutex_lock(&var_mutex);
    if (parts[0][2] > 0) {
        pthread_mutex_unlock(&var_mutex);

        pthread_mutex_lock(&var_mutex);
        num_of_est_works[0][3]++;              //adding expected work
        pthread_mutex_unlock(&var_mutex);

        pthread_mutex_lock(&stdout_mutex);
        printf("%s ohybacka 3 A\n", name);
        pthread_mutex_unlock(&stdout_mutex);

        pthread_mutex_lock(&var_mutex);
        parts[0][2]--;
        pthread_mutex_unlock(&var_mutex);

        usleep(150000);

        pthread_mutex_lock(&var_mutex);
        num_of_est_works[0][2]--;
        parts[0][3]++;
        available_works[3]++;
        pthread_mutex_unlock(&var_mutex);
    }
}

void get_and_do_work_svarecka(char* name) {
    pthread_mutex_lock(&var_mutex);
    if (parts[0][3] > 0) {
        pthread_mutex_unlock(&var_mutex);

        pthread_mutex_lock(&var_mutex);
        num_of_est_works[0][4]++;              //adding expected work
        pthread_mutex_unlock(&var_mutex);

        pthread_mutex_lock(&stdout_mutex);
        printf("%s svarecka 4 A\n", name);
        pthread_mutex_unlock(&stdout_mutex);

        pthread_mutex_lock(&var_mutex);
        parts[0][3]--;
        pthread_mutex_unlock(&var_mutex);

        usleep(300000);

        pthread_mutex_lock(&var_mutex);
        num_of_est_works[0][3]--;
        parts[0][4]++;
        available_works[1]++;
        pthread_mutex_unlock(&var_mutex);
    }
}

void get_and_do_work_lakovna(char* name) {
    pthread_mutex_lock(&var_mutex);
    if (parts[0][5] > 0) {
        pthread_mutex_unlock(&var_mutex);

        pthread_mutex_lock(&stdout_mutex);
        printf("%s lakovna 6 A\n", name);
        pthread_mutex_unlock(&stdout_mutex);

        pthread_mutex_lock(&var_mutex);
        parts[0][5]--;
        pthread_mutex_unlock(&var_mutex);

        usleep(400000);

        pthread_mutex_lock(&var_mutex);
        num_of_est_works[0][5]--;
        pthread_mutex_unlock(&var_mutex);

        pthread_mutex_lock(&stdout_mutex);
        printf("done A\n");
        pthread_mutex_unlock(&stdout_mutex);
    }
    else if (parts[2][5] > 0) {
        pthread_mutex_unlock(&var_mutex);

        pthread_mutex_lock(&stdout_mutex);
        printf("%s lakovna 6 C\n", name);
        pthread_mutex_unlock(&stdout_mutex);

        pthread_mutex_lock(&var_mutex);
        parts[2][5]--;
        pthread_mutex_unlock(&var_mutex);

        usleep(400000);

        pthread_mutex_lock(&var_mutex);
        num_of_est_works[2][5]--;
        pthread_mutex_unlock(&var_mutex);

        pthread_mutex_lock(&stdout_mutex);
        printf("done B\n");
        pthread_mutex_unlock(&stdout_mutex);
    }
    else if (parts[1][4] > 0) {
        pthread_mutex_unlock(&var_mutex);

        pthread_mutex_lock(&var_mutex);
        num_of_est_works[1][5]++;              //adding expected work
        pthread_mutex_unlock(&var_mutex);

        pthread_mutex_lock(&stdout_mutex);
        printf("%s lakovna 5 B\n", name);
        pthread_mutex_unlock(&stdout_mutex);

        pthread_mutex_lock(&var_mutex);
        parts[1][4]--;
        pthread_mutex_unlock(&var_mutex);

        usleep(400000);

        pthread_mutex_lock(&var_mutex);
        num_of_est_works[1][4]--;
        parts[1][5]++;
        available_works[5]++;
        pthread_mutex_unlock(&var_mutex);
    }
}

void get_and_do_work_sroubovak(char* name) {
    pthread_mutex_lock(&var_mutex);
    if (parts[1][5] > 0) {
        pthread_mutex_unlock(&var_mutex);

        pthread_mutex_lock(&stdout_mutex);
        printf("%s sroubovak 6 B\n", name);
        pthread_mutex_unlock(&stdout_mutex);

        pthread_mutex_lock(&var_mutex);
        parts[1][5]--;
        pthread_mutex_unlock(&var_mutex);

        usleep(250000);

        pthread_mutex_lock(&var_mutex);
        num_of_est_works[1][5]--;
        pthread_mutex_unlock(&var_mutex);

        pthread_mutex_lock(&stdout_mutex);
        printf("done B\n");
        pthread_mutex_unlock(&stdout_mutex);
    }
    else if (parts[2][2] > 0) {
        pthread_mutex_unlock(&var_mutex);

        pthread_mutex_lock(&var_mutex);
        num_of_est_works[2][3]++;              //adding expected work
        pthread_mutex_unlock(&var_mutex);

        pthread_mutex_lock(&stdout_mutex);
        printf("%s sroubovak 3 C\n", name);
        pthread_mutex_unlock(&stdout_mutex);

        pthread_mutex_lock(&var_mutex);
        parts[2][2]--;
        pthread_mutex_unlock(&var_mutex);

        usleep(250000);

        pthread_mutex_lock(&var_mutex);
        num_of_est_works[2][2]--;
        parts[2][3]++;
        available_works[1]++;
        pthread_mutex_unlock(&var_mutex);
    }
}

void get_and_do_work_freza(char* name) {
    pthread_mutex_lock(&var_mutex);
    if (parts[2][4] > 0) {
        pthread_mutex_unlock(&var_mutex);

        pthread_mutex_lock(&var_mutex);
        num_of_est_works[2][5]++;              //adding expected work
        pthread_mutex_unlock(&var_mutex);

        pthread_mutex_lock(&stdout_mutex);
        printf("%s freza 5 C\n", name);
        pthread_mutex_unlock(&stdout_mutex);

        pthread_mutex_lock(&var_mutex);
        parts[2][4]--;
        pthread_mutex_unlock(&var_mutex);

        usleep(500000);

        pthread_mutex_lock(&var_mutex);
        num_of_est_works[2][4]--;
        parts[2][5]++;
        available_works[4]++;
        pthread_mutex_unlock(&var_mutex);
    }
    else if (parts[1][2] > 0) {
        pthread_mutex_unlock(&var_mutex);

        pthread_mutex_lock(&var_mutex);
        num_of_est_works[1][3]++;              //adding expected work
        pthread_mutex_unlock(&var_mutex);

        pthread_mutex_lock(&stdout_mutex);
        printf("%s freza 3 B\n", name);
        pthread_mutex_unlock(&stdout_mutex);

        pthread_mutex_lock(&var_mutex);
        parts[1][2]--;
        pthread_mutex_unlock(&var_mutex);

        usleep(500000);

        pthread_mutex_lock(&var_mutex);
        num_of_est_works[1][2]--;
        parts[1][3]++;
        available_works[1]++;
        pthread_mutex_unlock(&var_mutex);
    }
    else if (parts[2][0] > 0) {
        pthread_mutex_unlock(&var_mutex);

        pthread_mutex_lock(&var_mutex);
        num_of_est_works[2][1]++;              //adding expected work
        pthread_mutex_unlock(&var_mutex);

        pthread_mutex_lock(&stdout_mutex);
        printf("%s freza 1 C\n", name);
        pthread_mutex_unlock(&stdout_mutex);

        pthread_mutex_lock(&var_mutex);
        parts[2][0]--;
        pthread_mutex_unlock(&var_mutex);

        usleep(500000);

        pthread_mutex_lock(&var_mutex);
        num_of_est_works[2][0]--;
        parts[2][1]++;
        available_works[1]++;
        pthread_mutex_unlock(&var_mutex);
    }
}

bool should_worker_wait(int place) {
    //iterate over each product
    for (int product = 0; product < 3; product++) {
        bool flag = false; //flag to indicate if prev. worker has to wait for work

        //iterate over each step in the process for the current product
        for (int step = 0; step < 6; step++) {
            pthread_mutex_lock(&var_mutex);
            int cur_place = processes[product][step]; //get the current step for the process

            //check if there is any work available and if there is some worker who can do it
            if (num_of_workers[cur_place] <= 0 || num_of_places[cur_place] <= 0) {    //if no
                flag = false; //reset the flag as conditions are not met
                pthread_mutex_unlock(&var_mutex);
                continue; //move to the next step
            }

            //if there are estimated works for the current product and step, set the flag
            if (!flag && num_of_est_works[product][step] > 0) {
                flag = true;
            }
            pthread_mutex_unlock(&var_mutex);

            //if the current place matches the workers place and the flag is set, return true
            if (cur_place == place && flag) {
                return true; //worker should wait
            }
        }
    }

    return false; //if no conditions are met, the worker should not wait
}