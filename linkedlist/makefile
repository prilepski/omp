# 

include make.def

EXES=linked$(EXE) 
#pi_recur$(EXE) mandel$(EXE)

all: $(EXES)

#hello_world$(EXE)_DEBUG: CFLAGS += -g
hello_world$(EXE)_DEBUG: OPTFLAGS += -g

hello_world$(EXE): hello_world.$(OBJ) 
	$(CPPLINKER) $(OPTFLAGS) -o hello_world$(EXE) hello_world.$(OBJ) $(LIBS)

hello_world$(EXE)_DEBUG: hello_world.$(OBJ) 
	$(CPPLINKER) $(OPTFLAGS) -o hello_world$(EXE) hello_world.$(OBJ) $(LIBS)

pi$(EXE): pi.$(OBJ) 
	$(CPPLINKER) $(OPTFLAGS) -o pi$(EXE) pi.$(OBJ) $(LIBS)

mandel$(EXE): mandel.$(OBJ) 
	$(CPPLINKER) $(OPTFLAGS) -o mandel$(EXE) mandel.$(OBJ) $(LIBS)

linked$(EXE): linked.$(OBJ) 
	$(CPPLINKER) $(OPTFLAGS) -o linkedlist$(EXE) linked.$(OBJ) $(LIBS)

#pi_recur$(EXE): pi_recur.$(OBJ) 
#	$(CLINKER) $(OPTFLAGS) -o pi_recur pi_recur.$(OBJ) $(LIBS)

#mandel$(EXE):  mandel.$(OBJ) 
#	$(CLINKER) $(OPTFLAGS) -o mandel mandel.$(OBJ) $(LIBS)

test: $(EXES)
#	$(PRE)hello$(EXE) 
#	$(PRE)pi$(EXE) 
#	$(PRE)pi_recur$(EXE) 
#	$(PRE)mandel$(EXE)

clean:
	$(RM) $(EXES) *.$(OBJ)

.SUFFIXES:
.SUFFIXES: .c .cpp .$(OBJ)

.c.$(OBJ):
	$(GCC) $(CFLAGS) -c $<

.cpp.$(OBJ):
	$(GCC) $(CFLAGS) -c $<
