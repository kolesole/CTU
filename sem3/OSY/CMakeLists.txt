cmake_minimum_required(VERSION 3.4)
project(OSY C)

set(CMAKE_C_STANDARD 11)

add_executable(OSY
        hw03/main.c
        hw03/nd.c
        hw03/nd.h
        hw03/nsd.c
        hw03/nsd.h
        hw03/nsd_main.c
        hw03/help_sigterm.h
        hw03/help_sigterm.c
        hw04/main.c
        hw04/producer.h
        hw04/producer.c
        hw04/consumer.h
        hw04/consumer.c
        hw04/linked_list.h
        hw04/linked_list.c
        hw05/main.c
        hw05/main.c
        hw05/worker.h
        hw05/worker.c
        hw05/utils.h
        hw05/utils.c
        hw05/work.h
        hw05/work.c
        hw05/workers_list.h
        hw05/workers_list.c)
