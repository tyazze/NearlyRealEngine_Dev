export CXX = g++.exe
export LD = g++.exe

export CFLAGS = -Wall -std=c++14
export LDFLAGS = -lopengl32 -lglu32

export INC = -I"C:\lib\TDM-GCC-64\include" -I"C:\lib\Glew\include" -I"C:\lib\GLM" -I"C:\lib\SDL2-2.0.7\x86_64-w64-mingw32\include"
export LIBDIR = -L"C:\lib\TDM-GCC-64\lib" -L"C:\lib\Glew\lib" -L"C:\lib\SDL2-2.0.7\x86_64-w64-mingw32\lib"
export LIB = "C:\lib\TDM-GCC-64\x86_64-w64-mingw32\lib\libmingw32.a" "C:\lib\Glew\lib\libglew32.dll.a" "C:\lib\SDL2-2.0.7\x86_64-w64-mingw32\lib\libSDL2main.a" "C:\lib\SDL2-2.0.7\x86_64-w64-mingw32\lib\libSDL2.dll.a"

export TARGET = debug

ifeq ($(TARGET), debug)
	OBJDIR = obj/Debug/
	BIN = bin/Debug/
	SOURCE = Source
	OBJ =  $(OBJDIR)SDL_Wrapper/Window/NRE_Window.o $(OBJDIR)SDL_Wrapper/Event/NRE_Event.o $(OBJDIR)GL_Wrapper/BufferObject/NRE_BufferObject.o $(OBJDIR)GL_Wrapper/BufferObject/Buffer/NRE_Buffer.o $(OBJDIR)GL_Wrapper/BufferObject/Buffer/Vertex/NRE_VertexBuffer.o $(OBJDIR)GL_Wrapper/BufferObject/Buffer/Color/NRE_ColorBuffer.o $(OBJDIR)GL_Wrapper/BufferObject/Buffer/Index/NRE_IndexBuffer.o $(OBJDIR)GL_Wrapper/BufferObject/Buffer/Normal/NRE_NormalBuffer.o $(OBJDIR)GL_Wrapper/BufferObject/VBO/NRE_VBO.o $(OBJDIR)GL_Wrapper/VAO/NRE_VAO.o $(OBJDIR)Renderer/Color/RGB/NRE_RGB.o $(OBJDIR)Renderer/Color/HSL/NRE_HSL.o $(OBJDIR)Renderer/Color/RGB/NRE_RGBA.o $(OBJDIR)Renderer/Color/HSL/NRE_HSLA.o $(OBJDIR)Renderer/Color/NRE_ColorConverter.o $(OBJDIR)Renderer/Shader/NRE_Shader.o $(OBJDIR)Camera/Input/KeyBinder/Key/NRE_Key.o $(OBJDIR)Camera/Input/KeyBinder/NRE_KeyBinder.o $(OBJDIR)Camera/Input/Keyboard/NRE_Keyboard.o $(OBJDIR)Camera/Input/EventHandler/NRE_EventHandler.o $(OBJDIR)Camera/Input/Mouse/NRE_Mouse.o $(OBJDIR)Camera/Input/NRE_Input.o $(OBJDIR)Camera/FixedCamera/NRE_FixedCamera.o $(OBJDIR)Camera/NRE_MoveableCamera.o $(OBJDIR)World/Voxel/NRE_Voxel.o $(OBJDIR)World/Voxel/Type/NRE_VoxelType.o $(OBJDIR)Support/Viewport/NRE_Viewport.o $(OBJDIR)Support/Scene/NRE_Scene.o $(OBJDIR)NRE_Main.o

else
	OBJDIR = obj/Test/
	BIN = bin/Test/
	SOURCE = Source_Test
	OBJ = $(OBJDIR)NRET_Main.o

endif

OUT = NearlyRealEngine_Dev

all : before out

before:
	@(cd $(SOURCE) && $(MAKE))

out : $(OBJ)
	@$(LD) $(LIBDIR) -o $(BIN)$(OUT) $^ $(LDFLAGS) $(LIB)
	@echo "Jobs done."

clean :
	@echo "Clear of obj/"
	@rm -r obj
	@mkdir obj
	@mkdir obj/Debug
	@mkdir obj/Debug/Camera
	@mkdir obj/Debug/Camera/FixedCamera
	@mkdir obj/Debug/Camera/Input
	@mkdir obj/Debug/Camera/Input/EventHandler
	@mkdir obj/Debug/Camera/Input/Keyboard
	@mkdir obj/Debug/Camera/Input/Mouse
	@mkdir obj/Debug/Camera/Input/KeyBinder
	@mkdir obj/Debug/Camera/Input/KeyBinder/Key
	@mkdir obj/Debug/GL_Wrapper
	@mkdir obj/Debug/GL_Wrapper/BufferObject
	@mkdir obj/Debug/GL_Wrapper/BufferObject/VBO
	@mkdir obj/Debug/GL_Wrapper/BufferObject/Buffer
	@mkdir obj/Debug/GL_Wrapper/BufferObject/Buffer/Color
	@mkdir obj/Debug/GL_Wrapper/BufferObject/Buffer/Index
	@mkdir obj/Debug/GL_Wrapper/BufferObject/Buffer/Normal
	@mkdir obj/Debug/GL_Wrapper/BufferObject/Buffer/Vertex
	@mkdir obj/Debug/GL_Wrapper/VAO
	@mkdir obj/Debug/Renderer
	@mkdir obj/Debug/Renderer/Color
	@mkdir obj/Debug/Renderer/Color/RGB
	@mkdir obj/Debug/Renderer/Color/HSL
	@mkdir obj/Debug/Renderer/Shader
	@mkdir obj/Debug/SDL_Wrapper
	@mkdir obj/Debug/SDL_Wrapper/Event
	@mkdir obj/Debug/SDL_Wrapper/Window
	@mkdir obj/Debug/Support
	@mkdir obj/Debug/Support/Viewport
	@mkdir obj/Debug/Support/Scene
	@mkdir obj/Debug/World
	@mkdir obj/Debug/World/Voxel
	@mkdir obj/Debug/World/Voxel/Type
	@echo "obj/-Tree creation done."
	@echo "Clean done."

clean_Test :
	@echo "Clear of obj/"
	@rm -r obj
	@mkdir obj
	@mkdir obj/Test
	@mkdir obj/Test/Camera
	@mkdir obj/Test/Camera/FixedCamera
	@mkdir obj/Test/Camera/Input
	@mkdir obj/Test/Camera/Input/EventHandler
	@mkdir obj/Test/Camera/Input/Keyboard
	@mkdir obj/Test/Camera/Input/Mouse
	@mkdir obj/Test/Camera/Input/KeyBinder
	@mkdir obj/Test/Camera/Input/KeyBinder/Key
	@mkdir obj/Test/GL_Wrapper
	@mkdir obj/Test/GL_Wrapper/BufferObject
	@mkdir obj/Test/GL_Wrapper/BufferObject/VBO
	@mkdir obj/Test/GL_Wrapper/BufferObject/Buffer
	@mkdir obj/Test/GL_Wrapper/BufferObject/Buffer/Color
	@mkdir obj/Test/GL_Wrapper/BufferObject/Buffer/Index
	@mkdir obj/Test/GL_Wrapper/BufferObject/Buffer/Normal
	@mkdir obj/Test/GL_Wrapper/BufferObject/Buffer/Vertex
	@mkdir obj/Test/GL_Wrapper/VAO
	@mkdir obj/Test/Renderer
	@mkdir obj/Test/Renderer/Color
	@mkdir obj/Test/Renderer/Color/RGB
	@mkdir obj/Test/Renderer/Color/HSL
	@mkdir obj/Test/Renderer/Shader
	@mkdir obj/Test/SDL_Wrapper
	@mkdir obj/Test/SDL_Wrapper/Event
	@mkdir obj/Test/SDL_Wrapper/Window
	@mkdir obj/Test/Support
	@mkdir obj/Test/Support/Viewport
	@mkdir obj/Test/Support/Scene
	@mkdir obj/Test/World
	@mkdir obj/Test/World/Voxel
	@mkdir obj/Test/World/Voxel/Type
	@echo "obj/-Tree creation done."
	@echo "Clean done."
