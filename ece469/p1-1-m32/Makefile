# Makefile for doc generator

# Gregory N. Schmit
# 11 Feb 2018

# build targets

.PHONY: help
help:
	printf "To generate document, use 'make pdf' or 'make all'\n"

.PHONY: all
all: pdf

.PHONY: pdf
pdf: report.pdf

report.pdf: report.tex
	pdflatex report.tex

.PHONY: clean
clean:
	rm -rf report.pdf report.log report.aux
