all: clean build

clean:
	@echo "Deleting class files"
	@find bin -type f -name "*.class" -delete

build:
	@echo "Compiling new class files"
	@javac -cp lib/json-20170516.jar:lib/argparse4j-0.7.0.jar -d bin `find . -type f -name "*.java"`

check:
	@echo "Checking coding style compliance"
	@java -jar lib/checkstyle-7.8.2-all.jar -c data/google_checks.xml `find src -type f -name "*.java"`
