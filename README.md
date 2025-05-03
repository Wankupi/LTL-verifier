# LTL-Verifier

This project is the assignment of the Model Checking Course.

In the following text, the word "we" is referring to myself only.

## Overview

There are mainly 4 steps,

- Parse the Transition System and LTL formula.
- Transform the LTL formula $\varphi$ to a GNBA (Generalized Nondeterministic Buechi Automaton) which accepts input satisfying $\neg \varphi$.
- Simplify the GNBA to a NBA. See file <src/NBA/GNBA.cpp>
- Check whether the traces of TS has any intersection with the accepted inputs of NBA. The intersection is the counterexample of $\varphi$. See file <src/loop.cpp>

## Compile and Run

First install required packages: `xmake`, `gcc`, `g++`, `wget`, `zip`.

Then run the following command to build,

```shell
xmake
```

Before running, you should put files `TS.txt` and `benchmark.txt` to the root folder of this repo.
Run it by

```shell
xmake run
```

Then `result.txt` will be created.

## Implementation

## LTL parse

Using Antlr for parsing. See grammar file <antlr/LTL.g4>.

Permit using words besides single character, such as `and`, `not`.

While building the LTL expression tree, we adopt an allocator to ensure the same expression will have only one object.
So that we could compare pointers to determine whether two expression are the same one.

## LTL to GNBA

First all closure of $\varphi$ are uniquely collected by DFS, and sorted from simple to complex.

Then we will enumerate all subset of closure and check whether the set is inner conflict, to find all element set.

The element sets are regarded as the states of the GNBA.

With locality, we generate the transitions.
For all element set, we first get a subset of the closure, in which the states' existence in the transited element set are fixed.
Then we filter all element sets satisfying the constrains.

Finally, we set the initial states and the final states list.

## GNBA to NBA

We use the simple duplicating method to ensure if one final states $\mathcal{F_0}$ is fulfilled, all final states $\{\mathcal{F_i}\}$ are fulfilled.

## Finding Intersection

Finding some $t \in \operatorname{Trace}(TS) \bigcap \mathcal{L}(NBA)$ is equivalent to finding an infinite walk on $TS \otimes NBA$ whose NBA partial-walk should be accepted by the NBA, i.e. the walk should pass the final states infinite times.

That means to find a reachable loop with at least one final state.

We use a simple DFS with stack. When we meet an already reached state $t$ and we found that the state $t$ is still in progress of dfs, a loop is found.
We use a memoried count $c$ to check whether there is any final state in the loop.
We set $c[s] = c$ when reach state $s$.
When go into a final state $s_f$, we set $c=c+1$. When leave the final state $s_f$, we minus it back $c=c-1$.
As we meet $t$ again, if $c != c[t]$, at least one final state is in the loop.
