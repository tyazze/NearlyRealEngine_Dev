SRC = NRE_ColorBuffer.cpp
OBJ = $(OBJDIR)NRE_ColorBuffer.o
OBJDIR = ../../../../../../obj/Debug/GL_Wrapper/Buffer/AttributeBuffer/ArrayBuffer/ColorBuffer/

all : $(TARGET)

debug : $(OBJ)

$(OBJDIR)%.o : %.cpp %.hpp
	@$(CXX) -o $@ -c $< $(CFLAGS) $(INC)
