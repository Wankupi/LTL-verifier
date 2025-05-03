# LTL-Verifier

This project is the assignment of the Model Checking Course.

In the following text, the word "we" is referring to myself only.

## Overview

There are mainly 4 steps,

- Parse the Transition System and LTL formula.
- Transform the LTL formula $\varphi$ to a GNBA (Generalized Nondeterministic Buechi Automaton) which accepts input satisfying $\neg \varphi$.
- Simplify the GNBA to a NBA. See file <src/NBA/GNBA.cpp>
- Check whether the traces of TS has any intersection with the accepted inputs of NBA. The intersection is the counterexample of $\varphi$. See file <src/loop.cpp>

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

Finally, we set the initial states and the final states list.

## GNBA to NBA

We use the simple duplicating method to ensure if one final states $\mathcal{F_0}$ is fulfilled, all final states $\{\mathcal{F_i}\}$ are fulfilled.

## Finding Intersection

Finding some $t \in \operatorname{Trace}(TS) \bigcap \mathcal{L}(NBA)$ is equivalent to finding an infinite walk on $TS \otimes NBA$ whose NBA partial-walk should be accepted by the NBA, i.e. the walk should pass the final states infinite times.

That means to find a reachable loop with at least one final state.
