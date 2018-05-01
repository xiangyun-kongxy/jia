## BSP issue list

### how to keep barren id consistent

1. name to id relation is recorded in configure database.
2. name is expanded to scope.name
3. name should not repeated
4. unnamed barren use \_[a-z]\* instead of \_
5. top level barren must be named

### how to implement local parameter and global parameter

1. local parameter range is [-99999999, -10000001]
2. global parameter range is [-100, -1]

### how to update barren

1. barren based on should be updated or removed

### structure of a barren

`
barren: (id, parent, creator, predicates)
predicate: function, parameter list
`

### special item in barren with negative

1. reference
    reference by name
    reference by variable
2. call function parameter
3. number
