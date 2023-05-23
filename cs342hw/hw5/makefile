all: clean build

clean:
	@echo "Deleting class files"
	@find bin -type f -name "*.class" -delete

build:
	@echo "Compiling new class files"
	@javac -cp lib/argparse4j-0.7.0.jar:lib/json-20170516.jar:lib/junit-4.12.jar -d bin `find . -type f -name "*.java"`

check:
	@echo "Checking coding style compliance"
	@java -jar lib/checkstyle-7.8.2-all.jar -c data/google_checks.xml `find . -type f -name "*.java"`

cases: clean build
	@java -cp bin:lib/hamcrest-core-1.3.jar:lib/junit-4.12.jar org.junit.runner.JUnitCore `find tests -type f -name "*.java" | sed 's/\.java//g' | sed 's/tests\///g'`
