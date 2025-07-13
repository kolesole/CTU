#lang racket

(define (interleave el lst)
    (if (null? lst) 
        (list (list el))
        (cons (cons el lst) (map (curry cons (car lst)) (interleave el (cdr lst))))
    )
)

(define (permutations lst)
    (if (null? lst)
        '(())
        (apply append 
            (map (curry interleave (car lst)) (permutations (cdr lst))))
    )
)


(struct node (var left right) #:transparent)

(define (evaluate tree vals)
    (match vals
        [(list) tree]
        [(list 0 vs ...) (evaluate (node-left tree) vs)]
        [(list 1 vs ...) (evaluate (node-right tree) vs)]
    )
)



(struct assignment (var val) #:transparent)

(define (satisficing-evaluations tree [ev '()])
    (match tree
        [1 (list (reverse ev))]
        [0 '()]
        [(node v l r)
            (append 
                (satisficing-evaluations l (cons (assignment v 0) ev))
                (satisficing-evaluations r (cons (assignment v 1) ev)))]
    )
)


(define (interleave el lst)
    (if (null? lst) 
        '((el))
        (cons (cons el lst) (map (curry cons (car lst)) (interleave el (cdr lst))))
    )
)

(define (permutations lst)
    (if (null? lst)
        '(())
        (apply append 
            (map (curry interleave (car lst)) (permutations (cdr lst))))
    )
)

(define (sub-seq lst)
    (if (null? lst)
        '(())
        (let ([el (car lst)]
              [rest-sub-seq (sub-seq (cdr lst))])
            (append rest-sub-seq (map (curry cons el) rest-sub-seq)) 
        )
    )
)
