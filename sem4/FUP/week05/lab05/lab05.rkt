#lang racket

(define (stream-add s1 s2)
    (stream-cons (+ (stream-first s1) (stream-first s2))
                 (stream-add (stream-rest s1) (stream-rest s2)))
)

(define s1 (in-naturals 1))
(stream-add s1 s1)
(stream->list (stream-take (stream-add s1 s1) 10))

(define fib-stream
    (stream-cons 0 
        (stream-cons 1
            (stream-add fib-stream (stream-rest fib-stream))))
)

(stream->list (stream-take fib-stream 10))



(struct graph (nodes edges) #:transparent)

(define gr
  (graph
    '(1 2 3 4 5 6)
    '((1 2) (1 5) (2 3) (2 5) (3 4) (4 5) (4 6))))

(define (interleave el lst)
  (if (null? lst)
      ; there is only a single way one can insert el into '()
      (list (list el))
      ; otherwise one possibility is to prepend el to lst
      (cons (cons el lst)
            ; for the rest take all possible insertions of el into (cdr lst)
            (map (curry cons (car lst))
                 ; and prepend (car lst) to each of them
                 (interleave el (cdr lst)))))
)

(define (permutations lst)
  (if (null? lst)
      '(())
      (apply append
             ; into each permutation of (cdr lst) interleave (car last)
             (map (curry interleave (car lst)) (permutations (cdr lst)))))
)

(define (edge? g)
    (lambda (e)
        (define edges (graph-edges g))
        (or (member e edges) (member (reverse e) edges))
    )
)

(define (check-path g)
    (lambda (lst)
        (define but-last (take lst (- (length lst) 1)))
        (if (andmap (edge? g) (map list but-last (cdr lst)))
            lst
            #f        
        )
    )
)

(define (find-hamiltonian-path g)
    (define perms (permutations (graph-nodes g)))
    (let ([paths (filter identity (map (check-path g) perms))])
        (if (null? paths)
            #f
            (car paths)
        )
    )
)



(define (stream-mul s1 s2)
    (stream-cons (* (stream-first s1) (stream-first s2))
                 (stream-mul (stream-rest s1) (stream-rest s2))
    )
)

(define factorial-stream
    (stream-cons 1
        (stream-mul (in-naturals 1) factorial-stream)
    )
)

(define (exp-stream x)
    (stream-cons (stream-mul (expt x)))
    (stream-cons (/ (expt x (stream-first (in-naturals 0))) 
                    (stream-first factorial-stream)))
                 (/ ())   
    
)


