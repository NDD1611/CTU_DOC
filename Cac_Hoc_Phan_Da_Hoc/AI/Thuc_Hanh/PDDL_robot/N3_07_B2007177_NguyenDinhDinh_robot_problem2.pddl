(define (problem gripperpickball)
  (:domain gripper)
  
  (:objects rooma roomb ball1 ball2 ball3 ball4 ball5 ball6 left right)
  
  (:init
  (room rooma) (room roomb) 
  (ball ball1)(ball ball2)
  (ball ball3)(ball ball4)
  (ball ball5)(ball ball6)
  (gripper left)(gripper right)
  (at-robby rooma)
  (free left)(free right)
  (at ball1 rooma)(at ball2 rooma)
  (at ball3 rooma)(at ball4 rooma)
  (at ball5 rooma)(at ball6 rooma)
  )

  (:goal (and
    (at ball1 roomb)(at ball2 roomb)
    (at ball3 roomb)
  ))
)