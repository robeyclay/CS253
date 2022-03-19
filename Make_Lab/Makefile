# This is a Makefile.  Its purpose is to create the program “small”.
#
# The rules, below, indicate what depends on what, and how to build
# things when they get out-of-date.  It is VERY important to know that
# what looks like eight leading spaces is really a leading tab
# character.  Leading spaces won’t work--it MUST be a tab character.
#
# For the following questions, do the command if there is one,
# and then answer the question.  If you need another line for you
# answer, continue it on the next line, indented.
#
# As an example, I’ve already answered (1), which has nothing to do
# with anything else in this lab.
#
# Question 1 is worth 0.09 points; questions 2–14 are worth 0.07
# points each.
#
#  1) Command:  date +%A
#     Question: Describe the output of that command.
#     Answer:   It’s today’s day of the week.
#
#  2) Command:  make
#     Question: Describe what happens.  Don’t just write the commands;
#     		describe what each command does.
#     Answer:   g++ -c main.cc   creates a main.o file based on main.cc for the computer to read
#		g++ -c foo.cc   creates a foo.o file based on foo.cc for the computer to read
#		g++ main.o foo.o -o small   creates a program named small that is dependant on foo.o and main.o
# 
#  3) Command:  ./small
#     Question: What is the output?  Reproduce the output exactly.
#     Answer:   Hi from main at main.cc:15
#		Hi from foo at foo.cc:14
#
#  4) Command:  make
#     Question: Why did nothing much happen?
#     Answer:   Because no changes were made ot the *.cc files 
#		that would warrant an update to the *.o files
#
#  5) Command:  rm small; make
#     Question: What got remade, and why?
#     Answer:   Removed small with the rm command, then called make again. 
#		Because the *.o files exist and had no changes the only line 
#		in the Makefile that was excuted was the one that creates small
#		which is dependant on foo.o and main.o
#
#  6) Command:  rm foo.o; make 
#     Question: What got remade, and why?
#     Answer:   foo.o got deleted. Calling make again remade the file foo.o,
#		this cause it to also remake small so it could still function 
#		based off the "new" foo.o
#
#  7) Command:  make clean 
#     Question: What did that do?
#     Answer:   Essentially undid everything make does. 
#		It deleted all of the *.o files and small.
#
#  8) Command:  make 
#     Question: What got remade, and why?
#     Answer:   main.o, foo.o, and small get remade becuase 
#		they were all deleted in the previous command "make clean"
#
#  9) Question: Why does main.o depend on foo.h?
#		I know that it’s because the Makefile says so.
#		Why was that dependency put into the Makefile?
#     Answer:   main uses foo.h because foo.h declares what functions 
#		are a part of foo.cc. foo.cc contains the definition 
#		of the declarations in foo.h
#
# 10) Command:  Create a new function bar() in bar.cc & bar.h,
# 		similar to foo.cc.  Change main.cc to call the new
# 		bar() function, make sure to #include the proper .h
# 		files everywhere, and type “make”.  Don’t alter Makefile.
#     Question: Why did it fail?
#     Answer:   It failed because bar.cc and bar.h weren't made into a 
#		readable *.o file in the MakeFile. This causes the MakeFile 
#		to get confused when trying to construct main.o since it 
#		finds a function it doesn't know exists.
#
# 11) Command:  Fix the Makefile; verify with “make” until it compiles.
#     Question: Describe your changes.  Don’t just show the changed
#     		lines--describe the purpose of each change.
#     Answer:   bar.o: bar.cc bar.h	 created a bar.o file that
#					 depends on bar.cc and bar.h.
#
#		small: main.o foo.o bar.o	 Adding the bar.o to the program small. 
#						 so it can be excuted alongside foo.o and main.o. 
#						 You have to add bar.o to the small executable list 
#						 otherwise the program will be confused by the
#						 bar() in the main.o file.
#
# 12) Command:  Uncomment the CXXFLAGS= line, and type “make”.
#     Question: Why didn't anything happen?
#     Answer:   The MakeFile did not need to run the *.cc files, because
#		of this the flags never set off 
#
# 13) Command:  Force a rebuild with: make clean; make 
#     Question: What’s new about the commands executed?
#     Answer:   It ran all the debugging scripts listed against the *.cc files.
#		It's referenced in the *.o file creation as $(CXXFLAGS) 
#		g++ -std=c++17 -Wall -Wextra -Wpedantic -Werror -Wfatal-errors -Winit-self -Wshadow -Wlogical-op -Wcomment -Wctor-dtor-privacy -Wold-style-cast -D_GLIBCXX_DEBUG -fno-diagnostics-show-option -c main.cc
#
# 14) Command: 	make clean; ls -l clean
#     Question: The target is “clean”, but no file “clean” got created.
#     		Why not?
#     Answer:   The MakeFile specifies that clean is a command used to 
#		delete the program small and any *.o files in the directory. 
#		It does not have any command that creates a file named "clean"
#
# For extra fame & glory (but no extra points):
#
# 15) Command:  Consult the make manual at
# 		https://www.gnu.org/software/make/manual/make.html
#		and improve this Makefile by using $@ in the rule
#		that creates “small” itself.

# The CXX variable contains the name of the C++ compiler.  You can’t
# have plus signs in a Make variable, so X is a rotated plus sign.
CXX=g++

 CXXFLAGS=-std=c++17 -Wall -Wextra -Wpedantic -Werror -Wfatal-errors -Winit-self -Wshadow -Wlogical-op -Wcomment -Wctor-dtor-privacy -Wold-style-cast -D_GLIBCXX_DEBUG -fno-diagnostics-show-option

small: main.o foo.o bar.o
	$(CXX) $(CXXFLAGS) main.o foo.o bar.o -o small

main.o: main.cc foo.h
	$(CXX) $(CXXFLAGS) -c main.cc

foo.o: foo.cc foo.h
	$(CXX) $(CXXFLAGS) -c foo.cc

bar.o: bar.cc bar.h
	$(CXX) $(CXXFLAGS) -c bar.cc

clean:
	-rm -f small *.o
