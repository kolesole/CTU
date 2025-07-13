#lang racket

(provide cheap-flight)

; some convenience functions
(define (nodes gr) (car gr))
(define (edges gr) (cadr gr))
(define (cost edge) (caddr edge))

(define (neighbours n gr)
    (define (iter n es ns)
        (if (empty? es) 
            ns
            (let* ([e car es]
                   [x (car e)]
                   [y (cadr e)]
                   [rest-es (cdr es)])
                (cond ([= n x] [iter n rest-es (cons y ns)])
                      ([= n y] [iter n rest-es (cons x ns)]
                      (else (iter n rest-es ns)))))
        )
    )
)

(define (extend path gr)
    (if (empty? path) 
        '()
        (map (lambda (n) (cons n path)) (neighbors (car path) gr)))
)

(define (unvisited path gr)
    (define  (cont? ns) (not (member (car ns) (cdr ns))))
    (filter cont? (extend path gr))
)

(define (split ))

(define (cheaper? x y)
    (< (cadr x) (cadr y))
)

(define (cheap-flight init goal graph)

)

; list of nodes
(define ns '(1 2 3 4 5 6)) ; listofnodes
; list of edges where each edge contains (start end cost)
(define es '((1 2 0.5) (1 3 1.0) (2 3 2.0) (2 5 1.0) (3 4 4.0) (4 5 1.0)))
; the graph; a list of nodes and edges
(define gr (list ns es))