.PHONY: all clean distclean build gyp run

# Default target
all: build

# Generate the GYP Makefile
build/Makefile: hge.gyp
	@echo "Generating build files with GYP..."
	@mkdir -p build
	@./tools/gyp/gyp_main.py -f make --depth=. --generator-output=build hge.gyp

# Build the project
build: build/Makefile
	@echo "Building the project..."
	@$(MAKE) -C build

# Run the test application
run: build
	@echo "Running test application..."
	@./build/out/Default/test_app

# Clean the build output
clean:
	@if [ -f build/Makefile ]; then \
		echo "Cleaning build output..."; \
		$(MAKE) -C build clean; \
	fi

# Remove all generated files
distclean:
	@echo "Removing all generated files..."
	@rm -rf build/
