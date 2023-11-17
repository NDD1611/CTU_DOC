(define (domain gripper)
  (:predicates
    (room ?room)
    (ball ?ball) 
    (gripper ?gripper)
    (at ?ball ?room)
    (at-robby ?room)
    (free ?gripper)
    (carry ?ball ?gripper)
  )
  
    (:action move
        :parameters (?rooma ?roomb)
    
        :precondition (and 
        (room ?rooma)(room ?roomb)(at-robby ?rooma)
        )
    
        :effect (and
        (at-robby ?roomb)(not (at-robby ?rooma))))
    
    (:action pick
        :parameters(?ball ?room ?gripper)
        :precondition(and
            (ball ?ball)(room ?room)(gripper ?gripper)
            (at ?ball ?room)(free ?gripper)(at-robby ?room)
        )
        :effect(and
            (carry ?ball ?gripper)(not(at ?ball ?room))
            (not(free ?gripper))
        )
    )
    (:action drop
        :parameters(?ball ?room ?gripper)
        :precondition(and 
            (ball ?ball)(room ?room)(gripper ?gripper)
            (carry ?ball ?gripper)
            (at-robby ?room)
        )
        :effect(and
            (at ?ball ?room)
            (free ?gripper)
            (not (carry ?ball ?gripper))
        )
    )
    
)