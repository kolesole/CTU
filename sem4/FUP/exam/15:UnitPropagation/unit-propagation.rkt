#lang racket
(provide propagate-units (struct-out pos) (struct-out neg))

(struct pos (variable) #:transparent)
(struct neg (variable) #:transparent)

(define (get-unit cls)
    (ormap (lambda (cl) (if (= (length cl) 1) (first cl) #f)) cls)  
)

(define/match (inv u)
    (([pos v]) [neg v])
    (([neg v]) [pos v])
)

(define (filt u cl)
    (define u-inv (inv u))
    (remove u-inv cl)
)

(define (propagate-units cls)
    (define u (get-unit cls))
    (if u
        (let* ([filtred1 (map (curry filt u) cls)]
               [filtred2 (filter-not (curry member u) filtred1)])
            (propagate-units filtred2))
        (remove-duplicates (filter-not null? cls))
    )
)