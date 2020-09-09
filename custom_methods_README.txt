------------------------------------------------------------------------------------------
-----------------------------------Custom Methods README----------------------------------
------------------------------------------------------------------------------------------

This version of HARCS is equipped with the ability to identify stepwise optimal solutions to 
custom user-defined methods. The sole requirement of these methods is that their steps consist
exclusively of orienting and positioning pieces in the conventional sense (reducing to a 
certain CP-state is not currently supported). 

Currently, custom methods can have up to 8 individual steps. 

This is accomplished by defining the method steps in terms of several parameters, by modifying 
the custom.txt file or creating your own. For example, I will explain each line of the 
definition of the first step of the SSC (Shadowslice Snow Columns) method:

step eoedge
movegroup 1
prunedepth 5
searchdepth 5
epmask 0x0000ff0f0000
eomask 0xffffffffffff
cpmask 0x00000000
comask 0x00000000
cnmask 0xfff

---------------------------------line-by-line explanation---------------------------------

step eoedge 	: this names the step "eoedge". 

movegroup 1 	: the movegroup of the set - options are shown below:
				: 1=<UDFBRL>, 2=<UDFBRLMr>, 3=<RUMr>, 4=<RUD>, 5=<RULD>, 
				: 6=<FURB>, 7=<MU>, 8=<U>, 9=<MUD>, 10=<LUD>
				: it is also possible to prescribe a custom moveset directly with 
				: "movegroup <RU>",
				: but this *may* be significantly slower than precompiled movesets

prunedepth 5 	: how deep to store sequences in that movegroup
searchdepth 5 	: how deep to search for a pruned solution
				: the sum should be greater than or equal to the upper bound of the step

epmask 0x0000ff0f0000 	: what edge pieces should be permuted in this step
eomask 0xffffffffffff	: what edge pieces should be oriented in this step
			: keep the leading "0x". HARCS uses hexadecimal
			: "f" marks a piece to solve, "0" leaves it open
			: the order is UB UR UF UL BL BR FR FL DB DR DF DL

cpmask 0x00000000	: what corner pieces should be permuted in this step
comask 0x00000000	: what corner pieces should be oriented in this step
					: the order is ULB UBR URF UFL DBL DRB DFR DLF

cnmask 0xfff		: what center pieces should be solved in this step 
					: the order is U R F
					: EO solutions require relevant centers to be solved.

------------------------------------------------------------------------------------------

Consider, also this step from a user-defined Roux Method:

step cmll
algset CMLL.txt
Udisplacement
epmask 0x0000ffff0f0f
eomask 0x0000ffff0f0f
cpmask 0xffffffff
comask 0xffffffff
cnmask 0x0f0

---------------------------------line-by-line explanation---------------------------------

algset CMLL.txt		: This loads a custom algorithm set into the program.
					: Keep algorithms line-separated.
					: You can add comments starting with // after each algorithm.
					: Currently ONLY ONE algorithm set (.txt) is permitted, but this can be
					: circumvented by putting algs for multiple steps (i.e. OLL/PLL) into
					: a single combined file, defining it as an "algset" for both methods.
					
Udisplacement		: This allows the masked cube to be a U-move away from solved after 
					: this step. This works for non-algorithm sets as well
					
					: Note - there is no need to prescribe movedepths for custom algsets.
								
------------------------------------------------------------------------------------------

Other supported commands include:

2genreduction		: This reduces the cube corners to states solvable with <RU> moves.
					: Simply include this along with the other commands for a step.
					
eps					: Set a custom "solved" edge permutation in hex format (default: 0x123456789abc)
eos					: Set a custom "solved" edge orientation in hex format (default: 0x222222222222)
cps					: Set a custom "solved" corner permutation in hex format (default: 0x12345678)
cos					: Set a custom "solved" corner orientation in hex format (default: 0x44444444)
cns					: Set a custom "solved" center permutation in hex format (default: 0x123)

------------------------------------------------------------------------------------------

Include all the steps that you would like HARCS to solve in this *.txt file. 

You can optionally put the "all" command at the end of the code, followed by the steps that, 
when executed in the given order, will return the cube to the solved state. For example: 
"all eoedge co cp l8e". This will allow you to simply type "all" at the command line later
to instantly generate complete solutions to applied scrambles using your custom method.

Any line in the custom.txt file that does not begin with one of these commands will be ignored
(like a comment).

To solve the cube using this custom method, type load *, where * is the filename without filetype
at the HARCS command line to prune for the custom method as you would for zz/petrus/roux/cfop.
Then, type the names of the steps (or "all"), as defined in the file to solve the steps, as usual.

------------------------------------------------------------------------------------------

To search for algorithms, include "algsearch step1 step2" somewhere in the input file.

In the program, typing "algsearch *" will save the first * solutions for each unique state
between "step1" and "step2" to a text file. It will use the movegroup and depths assigned
for resolution of "step 2". It can take a while when there are very many states.

Use the option --NO-ISO at the end of the input-file command to remove cases that are 
isomorphic through a U move ("algsearch step1 step2 --NO-ISO").

Algsearch requires solved centers.