#lang racket
(require "lambda-calculus.rkt")

(draw-expr '((λ x : (y (x x))) (λ y : (y (x x)))))

(reduce '(((λ x : (x y)) z) ((λ u : u) ((λ v : v) z))))


(define T '(λ x : (λ y : x)))
(define F '(λ x : (λ y : y)))

(define CONS
  '(λ a : (λ b : (λ z : ((z a) b)))))

(eval `(((,CONS a) b) ,T))
(eval `(((,CONS a) b) ,F))