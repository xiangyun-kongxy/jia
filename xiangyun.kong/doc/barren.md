# symbol deriving based knowledge present
## § what do I want to do

I want to create an extendable program which can simulate all human abilities. so what can human do?

* they can communication

	communication means behavior and response. this is the most important ability. without communication, even genius is worthless. communication requires human behavior and response in the same way, so they can understand each others, and then cooperate to work for the same task.

* they can think

	Thought is the way to know each others. It watches behavior and watches response. It tries to find out the relation between behavior and response. The way to learn is to watch, to simulate, to match again and again.

## things behind thought
basic concept in thought

* whatever are object
* quantity
* probability
* recursion (trend, change and time)
* set

## object for present basic concepts
* barren • **_B_**

	a **_barren_** is used for present an object. a **_barren_** may have a set of **_facts_** associated with it. and it has a unique id.

* predicate • **_P_**

	a **_predicate_** present a status or a relation. the formula is $predicate=relation<subject>$ where **_subject_** can be one of $\begin{cases}barren\\predicate\\variable\end{cases}$. **_predicate_** is a kind of barren

* fact • **_F_**

	a **_fact_** is a kind of **_predicate_**. the difference is **_fact_** is always the truth. the **_predicated_** may be true or may be not.

* variable • **_v_**

	a **_variable_** is actually one of $\begin{cases}barren\\predicate\end{cases}$, but it can not determined what it is so far

## operators on basic objects
### super operators
* EXIST • $\exists$

	* $\exists B$

	* $\exists F$

	* $\exists v$

	* $\exists P
		\Leftarrow
		\begin{cases}
			\Leftarrow
			\begin{cases}
				P = P_1 \\
				\exists P_1
			\end{cases} \\
			\Leftarrow
			\begin{cases}
				P \cong P_1 \\
				\exists P_1
			\end{cases} \\
			\Leftarrow
			\begin{cases}
				\exists (P_1 \Rightarrow P) \\
				\exists P_1
			\end{cases} \\
		\end{cases}$

* MATCH • $\cong$

	* $v \cong \begin{cases} B \\ P \\ v_1 \end{cases}$

	* $P_1 \cong P_2 \Leftarrow
		\begin{cases}
			P_1.relation \cong P_2.relation \\
			P_1.subject \cong P_2.subject
		\end{cases}$

	* $B_1 \cong B_2 \Leftarrow B_1.fact \cong B_2.fact$

## special barren

* INFER • $\Rightarrow$

	* $\exists P_1 \Rightarrow \exists P_2$

* NOT • $\lnot$

	* $\lnot P = \exists \lnot \exists P$

* AND • $\land$

	* $\exists(P_1 \land P_2) = \exists P_1 \land \exists P_2$

* OR • $\lor$

	* $\exists(P_1 \lor P_2) = \exists P_1 \lor \exists P_2$

* APPLY • $|$

	* $P | P_x \Rightarrow P_1 \text{with k replaced with v in }P_x$

* is $=$

	* $O_1=O_2 \Rightarrow (\exists F(O_2, \cdots) \Rightarrow \exists F(O_1,\cdots))$

_________________________________________________________

* belong-to $\in$

	* $O_1 \in O_2 \Rightarrow O_2 = <set, \dots O_1, \dots>$

* kind-of $\subset$

	* $O_1 \subset O_2 \Rightarrow \begin{cases} O_1=<set,O_l> \\ O_2=<set,O_l,O_m>\end{cases}$

* barren • $\forall$

	* $\forall \exists B$

* quantity • $|\dots|$

	* $\begin{cases} |O| = 1 \\ |<set,\dots>| = length(\dots) \end{cases}$

* sequence • $\vert$

	* presentation for sequence

* position

	* presentation for position

_____________________________________________________________

* probability

	* presentation for probabilit

* set

	* presentation for set

* divide

	* presentation for divide

* estimate(number, thing to be happen)

	* presentation for estimate

* recurrence

	* presentation for recurrence

* trend

	* presentation for trend

* represents
	* presentation for representation

## fact determining

* matching result from current memory cache.

* matching result from rule set cache.

* matching result from purpose directly related.

## fact instance determining

* matching condition from current memory cache.

* matching condition from what fact directly related.

## barren set

a barren set is where to search and also a barren. search result is also a barren set. so searching method can be compiled by gradually searching

## searching program formula

formula: [where to search, what to search, result set]

* where to search: barren set

* what to search: barren | barren tree

* result set: barren set

## forget method
## basic problem

1. what is appeared

	* what type it is

2. who are you

3. what you want

4. do you know

5. what should I do

## barren function

* <size, function id, nullptr, define function, function id, param1, param2...>

* <size, param1, function id, call function, function id, param11, param22...>

