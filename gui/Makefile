MOC_HEADERS = PrivatKeyFixatator.h  ClockDial.h Candidate.h Canditates.h Number.h Numbers.h SetUpWindow.h MainWindow.h AppManager.h
HEADERS     = 
MOC_SRCS  	= $(patsubst %.h,moc_%.cpp,$(MOC_HEADERS) )
SRC 		= main.cpp $(subst .h,.cpp,$(MOC_HEADERS)) $(subst .h,.cpp,$(HEADERS))  $(MOC_SRCS)   
OBJECTS		= $(patsubst %.cpp,obj/%.o,$(SRC))
INCLUDES 	=-I../third_parth/gmp/include -I. -I../core/ -I/usr/include/qt4/QtGui -I/usr/include/qt4/QtCore -I/usr/include/qt4/ -I/usr/local/qwt-6.0.2-svn/include/
# -L../third_parth/gmp/lib
QTPATH = /usr/lib/i386-linux-gnu/
# QTPATH =  ../third_parth/lib
LDFLAGS 	=  -Wl,-rpath ../third_parth/lib -g -L$(QTPATH)  -lQtCore -lQtGui -std=c++0x ../core/libargithmetics.a -lgmp -L../third_parth/lib -lqwt
CCFLAGS 	= -Wall -std=c++0x -g -pipe -c 

#all:: $(MOC_SRC) out $(OBJECTS) 

out : $(OBJECTS) 
	g++ $(OBJECTS) $(INCLUDES) $(LDFLAGS) -o out
								   
obj/%.o : %.cpp
	   g++ $(INCLUDES) $(CCFLAGS)   $< -o $@

moc_%.cpp : %.h 
	moc $< -o $@

clean:
	rm obj/*o moc* out -rf
