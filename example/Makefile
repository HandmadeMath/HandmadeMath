BUILD_DIR=build

CXXFLAGS+=-std=c++11

clean:
	rm -rf $(BUILD_DIR)

glfw:
	mkdir -p $(BUILD_DIR)/glfw
	cd $(BUILD_DIR)/glfw \
		&& cmake -DGLFW_BUILD_TESTS=off -DGLFW_BUILD_DOCS=off -DGLFW_BUILD_EXAMPLES=off ../../external/glfw \
		&& make

example:
	mkdir -p $(BUILD_DIR)/example
	cd $(BUILD_DIR)/example \
		&& $(CXX) $(CPPFLAGS) $(CXXFLAGS) -ohmmexample \
			-I../../external/glfw/include -I../../.. \
			-L../glfw/src \
			-lglew -lglfw3 \
			-framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo \
			../../src/*.cpp
