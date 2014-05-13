CXX = g++				# compiler
CXXFLAGS = -g -Wall -MMD		# compiler flags
OBJECTS = 1.o 2.o 3.o 4.o ...           # all .o files
DEPENDS = ${OBJECTS:.o=.d}              # get dependency
EXEC = soda


${EXEC} : ${OBJECTS}                          # link step
	${CXX} ${OBJECTS} -o ${EXEC}


-include ${DEPENDS}


.PHONY : clean

clean :					# remove files that can be regenerated
	rm -f ${DEPENDS} ${OBJECTS} ${EXECS}
