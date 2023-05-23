all: clean build

clean:
	@echo "Deleting class files"
	@find bin -type f -name "*.class" -delete

build:
	@echo "Compiling new class files"
	@javac -cp bin:lib/argparse4j-0.7.0.jar -d bin `find . -type f -name "*.java"`
