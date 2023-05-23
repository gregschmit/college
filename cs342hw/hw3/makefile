all: clean build

clean:
	@echo "Deleting class files"
	@find bin -type f -name "*.class" -delete

build:
	@echo "Compiling new class files"
	@javac -cp lib/pdfbox-app-2.0.6.jar -d bin `find . -type f -name "*.java"`

run:
	@echo "Running your program"
	@java -cp bin Main

