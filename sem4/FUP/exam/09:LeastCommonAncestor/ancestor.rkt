#lang racket

(provide find-path
         common-ancestor
         (struct-out node)
         (struct-out leaf))

(struct node (val left right) #:transparent)
(struct leaf (val) #:transparent)

(define (find-path x tree)
  (match tree
    [(leaf v) (if (equal? x v) (list x) '())]
    [(node v l r) (if (equal? x v) (list x)
                                (let* ([lpath (find-path x l)]
                                       [rpath (find-path x r)]
                                       [bpath (append lpath rpath)])
                                    (if (empty? bpath) '() (cons v bpath))))]
  )
)

(define (common-ancestor x y tree)
    (let* ([px (find-path x tree)]
           [py (find-path y tree)]
           [common (take-common-prefix px py)])
        (if (empty? common) #f (last common)))
)

(define tree2 (node 1 (node 2 (leaf 3)
                              (node 4 (leaf 5)
                                      (leaf 6)))
                      (node 7 (leaf 8)
                              (leaf 9))))