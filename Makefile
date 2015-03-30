CFLAGS=
FILES=0hh1 animate

all: $(FILES)

%: %.c
	gcc $(CFLAGS) -o $@ $<

pdf: doc.tex
	pdflatex doc.tex

clean:
	rm *.aux *.log *.synctex.gz $(FILES)

