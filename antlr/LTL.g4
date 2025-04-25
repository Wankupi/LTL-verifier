grammar LTL;
program: formula EOF;
formula:
	op = Not child = formula						# Not
	| op = Always child = formula					# Always
	| op = Eventually child = formula				# Eventually
	| op = Next child = formula						# Next
	| lhs = formula op = Until rhs = formula		# Until
	| lhs = formula op = Implication rhs = formula	# Implication
	| lhs = formula op = Disjunction rhs = formula	# Disjunction
	| lhs = formula op = Conjunction rhs = formula	# Conjunction
	| True											# True
	| False											# False
	| '(' child = formula ')'						# Parenthesis
	| Atom											# Atom;
Eventually: 'F';
Always: 'G';
Next: 'X';
Until: 'U';
Not: '!';
Conjunction: '/\\';
Disjunction: '\\/';
Implication: '->';
True: 'true';
False: 'false';
Atom: [a-z]+;
Whitespace: [ \t\r\n]+ -> skip;