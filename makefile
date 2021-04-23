#CXX = g++-10
CXX = clang++

CXXFLAGS = -Ofast -ffast-math --std=c++17 -MMD

src = cmdline.cpp
obj = $(src:.cpp=.o)

demo : $(obj)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

dep = $(obj:.o=.d)
-include $(dep)

clean :
	-@rm demo *.o *.d 2>/dev/null || true
