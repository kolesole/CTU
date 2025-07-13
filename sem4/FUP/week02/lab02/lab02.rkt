#lang racket

(define (my-reverse lst [acc '()])
    (if (null? lst)
        acc
        (my-reverse (cdr lst) (cons (car lst) acc))
    )
)

(my-reverse '(1 2 3 4))



(define (iter l gr)
    (cond
        [(null? l) (list gr)]
        [(eq? (car l) (car gr)) (iter (cdr l) (cons (car gr) gr))]
        [else (cons gr (iter (cdr l) (list (car l))))]
    )
)    
    
(define (group-same lst)
    (if (null? lst)
        '()
        (iter (cdr lst) (list (car lst)))
    )
)

(define (join-length grs)
    (map (lambda (g) (cons (car g) (length g))) grs)
)

(define (letter-frequencies str)
    
    (sort (join-length(group-same(sort
        (filter char-alphabetic? (string->list (string-downcase str)))
        char<?))) 
    > 
    #:key cdr)    
)

(define (average-list lst [acc 0] [acc1 0])
    (if (null? lst)
        (/ (exact->inexact acc) acc1)
        (average-list (rest lst) (+ acc (first lst)) (+ acc1 1))
    )
)

(average-list '(1 2 3 4 5 6))

(define (helper lst [acc1 '()] [acc2 n])


)

(define (split-list n lst)
    (define (iter lst1 [res '()] [acc1 '()] [acc2 n])
        (cond
            [(null? lst1) (append res (list acc1))]
            [(= acc2 0) (iter (append res (list acc1)))]
            [else (iter (rest lst1) res (cons (first lst1) acc1) (- acc2 1))]
        )
    )

    (iter lst)
)

