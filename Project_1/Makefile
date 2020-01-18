# Khai Nguyen
#

# define a target for the application
#
all: myNLP

# define a target to link the application
#
myNLP: word-frequency-count.cpp function.cpp
	g++ word-frequency-count.cpp function.cpp -o myNLP -lpthread

# define a target to clean the directory
#
clean:
	rm -f *.o *.exe
#
# end of file
