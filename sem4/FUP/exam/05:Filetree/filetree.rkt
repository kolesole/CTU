#lang racket
(provide parse exists)

(define (split-path path) (string-split path "/"))

(define (insert path tree)
    (if (empty? path)
        tree 
        (let* ([key (car path)]
               [branch (if (dict-has-key? tree key) (dict-ref tree key) #hash())]
               [new-branch (insert (cdr path) branch)])
            (dict-set tree key new-branch)))
)

(define (parse paths)
    (define (helper path tree) (insert (split-path path) tree))
    (foldl helper #hash() paths)
)

(define (exists path tree)
    (define (helper spl-path ctree)
        (cond [(empty? spl-path) #t]
              [(= (length spl-path) 1) (dict-has-key? ctree (car spl-path))]
              [else 
                    (let ([key (car spl-path)])
                        (if (dict-has-key? ctree key)
                            (helper (cdr spl-path) (dict-ref ctree key))
                            #f))])
    )
    (helper (split-path path) tree)
)

(define files (list "src/tree.hs" "src/complex.hs" "scripts/ex1/test.ss" "scripts/ex1/eval.ss" "scripts/emptydir" "scripts/ex2/test.ss" "tests/test_tree.hs"))