#lang racket

(provide add-edge
         build-tree
         (struct-out node)
         (struct-out leaf))

(struct node (val kids) #:transparent)
(struct leaf (val) #:transparent)

(define (get-val t)
    (match t 
        [(leaf v) v]
        [(node v ks) v])
)

(define (sort-kids ks)
    (sort ks (lambda (p q) (< (get-val p) (get-val q))))
)

(define (add-edge edge tree)
    (define s (car edge))
    (define t (cadr edge))
    (match tree
        [(leaf v) (if (= v s) (node v (list (leaf t))) 
                      (leaf v))]
        [(node v ks) (if (= v s) (node v (sort-kids (cons (leaf t) ks)))
                         (node v (map (curry add-edge edge) ks)))]
    )
)

(define (build-tree init edges)
  (foldl add-edge init edges)
)

