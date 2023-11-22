# To-Do List

- [ ] Semantic Analysis
  - [ ] Type Checking
  - [ ] Scope Checking
  - [ ] Symbol Table
    - [ ] Symbol Table for Variables
    - [ ] Symbol Table for Functions
    - [ ] Symbol Table for Structs
- [ ] Remove redundant code
- [ ] Add more tests
- [ ] Add more comments
- [ ] Reduce Tokens?
- [ ] Simplify Regex?

```text
CYK Algorithm

let the input be a string I consisting of n characters: a1 ... an.
let the grammar contain r nonterminal symbols R1 ... Rr, with start symbol R1.
let P[n,n,r] be an array of booleans. Initialize all elements of P to false.
let back[n,n,r] be an array of lists of backpointing triples. Initialize all elements of back to the empty list.

for each s = 1 to n
    for each unit production Rv → as
        set P[1,s,v] = true

for each l = 2 to n -- Length of span
    for each s = 1 to n-l+1 -- Start of span
        for each p = 1 to l-1 -- Partition of span
            for each production Ra    → Rb Rc
                if P[p,s,b] and P[l-p,s+p,c] then
                    set P[l,s,a] = true,
                    append <p,b,c> to back[l,s,a]

if P[n,1,1] is true then
    I is member of language
    return back -- by retracing the steps through back, one can easily construct all possible parse trees of the string.
else
    return "not a member of language"
```
